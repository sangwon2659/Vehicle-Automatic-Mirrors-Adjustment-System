import time
import serial

ser=serial.Serial("/dev/ttyUSB0",9600,timeout=0.2)

time.sleep(1)

print("motor on")

theta_1=90  # L_LR
theta_2=90  # L_UD
theta_3=90  # B_LR
theta_4=90  # B_UD
theta_5=90  # R_LR
theta_6=90  # R_UD

ser.write(chr(150).encode())
print(ser.readline().decode())

ser.write(chr(161).encode())
print(ser.readline().decode())
ser.write(chr(151).encode())
print(ser.readline().decode())
ser.write(chr(theta_1).encode())
print(ser.readline().decode())

ser.write(chr(161).encode())
print(ser.readline().decode())
ser.write(chr(152).encode())
print(ser.readline().decode())
ser.write(chr(theta_2).encode())
print(ser.readline().decode())

ser.write(chr(160).encode())
print(ser.readline().decode())
ser.write(chr(151).encode())
print(ser.readline().decode())
ser.write(chr(theta_3).encode())
print(ser.readline().decode())

ser.write(chr(160).encode())
print(ser.readline().decode())
ser.write(chr(152).encode())
print(ser.readline().decode())
ser.write(chr(theta_4).encode())
print(ser.readline().decode())

ser.write(chr(162).encode())
print(ser.readline().decode())
ser.write(chr(151).encode())
print(ser.readline().decode())
ser.write(chr(theta_5).encode())
print(ser.readline().decode())

ser.write(chr(162).encode())
print(ser.readline().decode())
ser.write(chr(152).encode())
print(ser.readline().decode())
ser.write(chr(theta_6).encode())
print(ser.readline().decode())

print("motor off")
print(ser.readline().decode())