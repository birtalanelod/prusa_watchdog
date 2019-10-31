void blink_led(){
  


R=RGB[color][0];
G=RGB[color][1];
B=RGB[color][2];
 
blink_Flag=!blink_Flag; 

 //if(power_status==2 || alarm){blink_Flag=false;} 
   
   
if(alarm){   
         strip.setPixelColor(1,RGB[1][0],RGB[1][1],RGB[1][2]);  //  BOTTOM LED is RED - ALARM SMOKE DETECTED   
         blink_Flag=false;                                      //  TOP STATUS LED stops blinking 
  }else{ strip.setPixelColor(1,RGB[4][0],RGB[4][1],RGB[4][2]);  //  BOTTOM LED is continous WHITE during normal operation
          
         }
 strip.show();

      
if(blink_Flag){    //TOP LED (STATUS)
              strip.setPixelColor(0,RGB[0][0],RGB[0][1],RGB[0][2]);  //BLACK OFF
       }else{ 
              strip.setPixelColor(0,R,G,B);                          //SOME COLOR from color[] matrix
   }   
 strip.show();

}
