# -*- coding: utf-8 -*-

#!/usr/bin/env python

# Copyright 2017 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Google Cloud Speech API sample application using the streaming API.

NOTE: This module requires the additional dependency `pyaudio`. To install
using pip:

    pip install pyaudio

Example usage:
    python transcribe_streaming_mic.py
"""

# [START speech_transcribe_streaming_mic]
from __future__ import division

import re
import sys

from google.cloud import speech
from google.cloud.speech import enums
from google.cloud.speech import types
import pyaudio
from six.moves import queue

import os
import time
import subprocess

import serial

# Audio recording parameters
RATE = 16000
CHUNK = int(RATE / 10)  # 100ms

power=True

select_mirror=False
choose=False

#ser=serial.Serial("/dev/ttyUSB0",9600,timeout=0.2)

class MicrophoneStream(object):
    """Opens a recording stream as a generator yielding the audio chunks."""
    def __init__(self, rate, chunk):
        self._rate = rate
        self._chunk = chunk

        # Create a thread-safe buffer of audio data
        self._buff = queue.Queue()
        self.closed = True

    def __enter__(self):
        self._audio_interface = pyaudio.PyAudio()
        self._audio_stream = self._audio_interface.open(
            format=pyaudio.paInt16,
            # The API currently only supports 1-channel (mono) audio
            # https://goo.gl/z757pE
            channels=1, rate=self._rate,
            input=True, frames_per_buffer=self._chunk,
            # Run the audio stream asynchronously to fill the buffer object.
            # This is necessary so that the input device's buffer doesn't
            # overflow while the calling thread makes network requests, etc.
            stream_callback=self._fill_buffer,
        )

        self.closed = False

        return self

    def __exit__(self, type, value, traceback):
        self._audio_stream.stop_stream()
        self._audio_stream.close()
        self.closed = True
        # Signal the generator to terminate so that the client's
        # streaming_recognize method will not block the process termination.
        self._buff.put(None)
        self._audio_interface.terminate()

    def _fill_buffer(self, in_data, frame_count, time_info, status_flags):
        """Continuously collect data from the audio stream, into the buffer."""
        self._buff.put(in_data)
        return None, pyaudio.paContinue

    def generator(self):
        while not self.closed:
            # Use a blocking get() to ensure there's at least one chunk of
            # data, and stop iteration if the chunk is None, indicating the
            # end of the audio stream.
            chunk = self._buff.get()
            if chunk is None:
                return
            data = [chunk]

            # Now consume whatever other data's still buffered.
            while True:
                try:
                    chunk = self._buff.get(block=False)
                    if chunk is None:
                        return
                    data.append(chunk)
                except queue.Empty:
                    break

            yield b''.join(data)


def listen_print_loop(responses):
    """Iterates through server responses and prints them.

    The responses passed is a generator that will block until a response
    is provided by the server.

    Each response may contain multiple results, and each result may contain
    multiple alternatives; for details, see https://goo.gl/tjCPAU.  Here we
    print only the transcription for the top alternative of the top result.

    In this case, responses are provided for interim results as well. If the
    response is an interim one, print a line feed at the end of it, to allow
    the next result to overwrite it, until the response is a final one. For the
    final one, print a newline to preserve the finalized transcription.
    """
    
    global power
    
    num_chars_printed = 0
    for response in responses:
        if not response.results:
            continue

        # The `results` list is consecutive. For streaming, we only care about
        # the first result being considered, since once it's `is_final`, it
        # moves on to considering the next utterance.
        result = response.results[0]
        if not result.alternatives:
            continue

        # Display the transcription of the top alternative.
        transcript = result.alternatives[0].transcript
        # line, so subsequent lines will overwrite them.
        #
        # If the previous result was longer than this one, we need to print
        # some extra spaces to overwrite the previous result
        overwrite_chars = ' ' * (num_chars_printed - len(transcript))

        if not result.is_final:
            sys.stdout.write(transcript + overwrite_chars + '\r')
            sys.stdout.flush()

            num_chars_printed = len(transcript)

        else:
            print(transcript)
            
            text=transcript.strip()
            if text[-1]=='.':
                temp2=text[:-1]
                text=temp2
#            if text=='백미러':
#                print("백미러 선택")
#                select_mirror=True
#                ser.write(chr(160).encode())
#                os.system("omxplayer Back.wav")
#            elif text in ['왼쪽 사이드 미러','왼쪽 사이드미러','좌측 사이드미러','좌측 사이드 미러']:
#                print("왼쪽 사이드 미러 선택")
#                select_mirror=True
#                ser.write(chr(161).encode())
#                os.system("omxplayer L_side.wav")
#            elif text in ['오른쪽 사이드 미러','오른쪽 사이드미러','우측 사이드미러','우측 사이드 미러']:
#                print("오른쪽 사이드 미러 선택")
#                select_mirror=True
#                ser.write(chr(162).encode())
#                os.system("omxplayer R_side.wav")
#                
#            if text in ['사이드미러','사이드 미러']:
#                print("어느쪽 사이드미러?")
#                choose=True
#                select_mirror=False
#                os.system("omxplayer What_side.wav")
#            elif text in['오른쪽','우측'] and choose==True:
#                print("오른쪽 사이드 미러 선택")
#                select_mirror=True
#                choose=False
#                ser.write(chr(162).encode())
#                os.system("omxplayer R_side.wav")
#            elif text in['왼쪽','좌측'] and choose==True:
#                print("왼쪽 사이드 미러 선택")
#                select_mirror=True
#                choose=False
#                ser.write(chr(161).encode())
#                os.system("omxplayer L_side.wav")
                
#            if text in ['우회전','오른쪽','우로'] and select_mirror==True:
#                print("우회전")
#                ser.write(chr(179).encode())
#            elif text in ['좌회전','왼쪽','좌로'] and select_mirror==True:
#                print("좌회전")
#                ser.write(chr(178).encode())
#            elif text in ['위로','위로 회전'] and select_mirror==True:
#                print("위로 회전")
#                ser.write(chr(176).encode())
#            elif text in ['아래로','아래로 회전'] and select_mirror==True:
#                print("아래로 회전")
#                ser.write(chr(177).encode())
#            elif text in ['멈춰','중지','스톱']:
#                print('회전 중지')
#                ser.write(chr(183).encode())
#                select_mirror=False
#            elif text in ['종료','보이스 종료']:
#                print("종료")
#                power=False
#                break
            if text in ['시작']:
                select_mirror=False
                print("촬영 시작")
                os.system("omxplayer Start.wav")
                os.system("python Calculation.py")
                power=False
                break
            else:
                os.system("omxplayer NoCommand.wav")
                print("No command")
                power=False
                break
            

            # Exit recognition if any of the transcribed phrases could be
            # one of our keywords.
            """if re.search(r'\b(exit|quit)\b', transcript, re.I):
                print('Exiting..')
                break"""

            num_chars_printed = 0


def main():
    # See http://g.co/cloud/speech/docs/languages
    # for a list of supported languages.
    language_code ='ko-KR'  # a BCP-47 language tag

    client = speech.SpeechClient()
    config = types.RecognitionConfig(
        encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=RATE,
        language_code=language_code)
    streaming_config = types.StreamingRecognitionConfig(
        config=config,
        interim_results=True)

    with MicrophoneStream(RATE, CHUNK) as stream:
        audio_generator = stream.generator()
        requests = (types.StreamingRecognizeRequest(audio_content=content)
                    for content in audio_generator)

        responses = client.streaming_recognize(streaming_config, requests)

        # Now, put the transcription responses to use.
        listen_print_loop(responses)


if __name__ == '__main__':
    os.system("omxplayer yes.wav")
    starttime=time.time()
    while True:
        main()
        if power==False:
            break
        else:
            endtime=time.time()
            if int(endtime-starttime)>30:
                power==False
                break
# [END speech_transcribe_streaming_mic]
