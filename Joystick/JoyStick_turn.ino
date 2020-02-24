void turn_left_joy(){
   unsigned char angle=0;
   if (right_mirror_button==1) angle=right_LR_servo_fix;
   else if(left_mirror_button==1) angle=left_LR_servo_fix;
   else if(back_mirror_button==1) angle=back_LR_servo_fix;

   if(angle<=1) angle=1;
   else if(angle>=179) angle=179;
   
   if (angle>0 and angle <180){
   if (right_mirror_button==1){
     angle-=1;
     right_LR_servo.write(angle);
     right_LR_servo_fix=angle;
     delay(100);
   }else if (left_mirror_button==1){
     angle-=1;
     left_LR_servo.write(angle);
     left_LR_servo_fix=angle;
     delay(100);
   }else if (back_mirror_button==1){
     angle-=1;
     back_LR_servo.write(angle);
     back_LR_servo_fix=angle;
     delay(100);
   }
   }
}

void turn_right_joy(){
   unsigned char angle=0;
   if (right_mirror_button==1) angle=right_LR_servo_fix;
   else if(left_mirror_button==1) angle=left_LR_servo_fix;
   else if(back_mirror_button==1) angle=back_LR_servo_fix;
   
   if(angle<=1) angle=1;
   else if(angle>=179) angle=179;
   
   if (angle>0 and angle <180){
   if (right_mirror_button==1){
     angle+=1;
     right_LR_servo.write(angle);
     right_LR_servo_fix=angle;
     delay(100);
   }else if (left_mirror_button==1){
     angle+=1;
     left_LR_servo.write(angle);
     left_LR_servo_fix=angle;
     delay(100);
   }else if (back_mirror_button==1){
     angle+=1;
     back_LR_servo.write(angle);
     back_LR_servo_fix=angle;
     delay(100);
   }
   }
}


void turn_up_joy(){
   unsigned char angle=0;
   if (right_mirror_button==1) angle=right_UD_servo_fix;
   else if(left_mirror_button==1) angle=left_UD_servo_fix;
   else if(back_mirror_button==1) angle=back_UD_servo_fix;

   if(angle<=1) angle=1;
   else if(angle>=179) angle=179;
   
   if (angle>0 and angle <180){
   if (right_mirror_button==1){
     angle-=1;
     right_UD_servo.write(angle);
     right_UD_servo_fix=angle;
     delay(100);
   }else if (left_mirror_button==1){
     angle-=1;
     left_UD_servo.write(angle);
     left_UD_servo_fix=angle;
     delay(100);
   }else if (back_mirror_button==1){
     angle-=1;
     back_UD_servo.write(angle);
     back_UD_servo_fix=angle;
     delay(100);
   }
   }
}


void turn_down_joy(){
   unsigned char angle=0;
   if (right_mirror_button==1) angle=right_UD_servo_fix;
   else if(left_mirror_button==1) angle=left_UD_servo_fix;
   else if(back_mirror_button==1) angle=back_UD_servo_fix;

   if(angle<=1) angle=1;
   else if(angle>=179) angle=179;
   
   if (angle>0 and angle <180){
   if (right_mirror_button==1){
     angle+=1;
     right_UD_servo.write(angle);
     right_UD_servo_fix=angle;
     delay(100);
   }else if (left_mirror_button==1){
     angle+=1;
     left_UD_servo.write(angle);
     left_UD_servo_fix=angle;
     delay(100);
   }else if (back_mirror_button==1){
     angle+=1;
     back_UD_servo.write(angle);
     back_UD_servo_fix=angle;
     delay(100);
   }
   }
}
