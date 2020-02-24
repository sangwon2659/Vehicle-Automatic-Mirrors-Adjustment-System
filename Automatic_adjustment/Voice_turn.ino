void turn_left(){
   unsigned char angle=0;
   if (right_mirror==1) angle=right_LR_servo_fix;
   else if(left_mirror==1) angle=left_LR_servo_fix;
   else if(back_mirror==1) angle=back_LR_servo_fix;
      
   while(angle>0){
     if(Serial.available()){
       f=Serial.read();
       if(f==183){
         servo_left_turn=0;
         right_mirror==0, left_mirror==0, back_mirror==0;
         break;
       }
     }
     if (right_mirror==1){
     right_LR_servo.write(angle);
     angle-=1;
     delay(100);
     }else if (left_mirror==1){
     left_LR_servo.write(angle);
     angle-=1;
     delay(100);
     }else if (back_mirror==1){
     back_LR_servo.write(angle);
     angle-=1;
     delay(100);
     }

   }
   servo_left_turn=0;
   if (right_mirror==1){
     right_LR_servo_fix=angle;
     right_mirror==0;
   }else if (left_mirror==1){
     left_LR_servo_fix=angle;
     left_mirror==0;
   }else if (back_mirror==1){
     back_LR_servo_fix=angle;
     back_mirror==0;
   }
}

void turn_right(){
   unsigned char angle=0;
   if (right_mirror==1) angle=right_LR_servo_fix;
   else if(left_mirror==1) angle=left_LR_servo_fix;
   else if(back_mirror==1) angle=back_LR_servo_fix;
      
   while(angle<180){
     if(Serial.available()){
       f=Serial.read();
       if(f==183){
         servo_right_turn=0;
         right_mirror==0, left_mirror==0, back_mirror==0;
         break;
       }
     }
     if (right_mirror==1){
     right_LR_servo.write(angle);
     angle+=1;
     delay(100);
     }else if (left_mirror==1){
     left_LR_servo.write(angle);
     angle+=1;
     delay(100);
     }else if (back_mirror==1){
     back_LR_servo.write(angle);
     angle+=1;
     delay(100);
     }

   }
   servo_right_turn=0;
   if (right_mirror==1){
     right_LR_servo_fix=angle;
     right_mirror==0;
   }else if (left_mirror==1){
     left_LR_servo_fix=angle;
     left_mirror==0;
   }else if (back_mirror==1){
     back_LR_servo_fix=angle;
     back_mirror==0;
   }
}


void turn_up(){
   unsigned char angle=0;
   if (right_mirror==1) angle=right_UD_servo_fix;
   else if(left_mirror==1) angle=left_UD_servo_fix;
   else if(back_mirror==1) angle=back_UD_servo_fix;
      
   while(angle>0){
     if(Serial.available()){
       f=Serial.read();
       if(f==183){
         servo_up_turn=0;
         right_mirror==0, left_mirror==0, back_mirror==0;
         break;
       }
     }
     if (right_mirror==1){
     right_UD_servo.write(angle);
     angle-=1;
     delay(100);
     }else if (left_mirror==1){
     left_UD_servo.write(angle);
     angle-=1;
     delay(100);
     }else if (back_mirror==1){
     back_UD_servo.write(angle);
     angle-=1;
     delay(100);
     }

   }
   servo_up_turn=0;
   if (right_mirror==1){
     right_UD_servo_fix=angle;
     right_mirror==0;
   }else if (left_mirror==1){
     left_UD_servo_fix=angle;
     left_mirror==0;
   }else if (back_mirror==1){
     back_UD_servo_fix=angle;
     back_mirror==0;
   }
}


void turn_down(){
   unsigned char angle=0;
   if (right_mirror==1) angle=right_UD_servo_fix;
   else if(left_mirror==1) angle=left_UD_servo_fix;
   else if(back_mirror==1) angle=back_UD_servo_fix;
      
   while(angle<180){
     if(Serial.available()){
       f=Serial.read();
       if(f==183){
         servo_down_turn=0;
         right_mirror==0, left_mirror==0, back_mirror==0;
         break;
       }
     }
     if (right_mirror==1){
     right_UD_servo.write(angle);
     angle+=1;
     delay(100);
     }else if (left_mirror==1){
     left_UD_servo.write(angle);
     angle+=1;
     delay(100);
     }else if (back_mirror==1){
     back_UD_servo.write(angle);
     angle+=1;
     delay(100);
     }

   }
   servo_down_turn=0;
   if (right_mirror==1){
     right_UD_servo_fix=angle;
     right_mirror==0;
   }else if (left_mirror==1){
     left_UD_servo_fix=angle;
     left_mirror==0;
   }else if (back_mirror==1){
     back_UD_servo_fix=angle;
     back_mirror==0;
   }
}
