void go_online(){    //run during setup 
 Serial.print(F("Connecting to Wifi: "));  
 WiFi.begin(ssid, password);  // attempt to connect to Wifi network for 1 minute
 while(!timer.hasPassed(30) && (WiFi.status() != WL_CONNECTED)){ 
           delay(500);
             
          Serial.print(F("."));  
             
         
           if(blink_Flag){
                           blink_Flag=false;
                           strip.setPixelColor(0,RGB[0][0],RGB[0][1],RGB[0][2]); 
                           strip.show();
                           }else{
                           blink_Flag=true;
                           strip.setPixelColor(0,RGB[5][0],RGB[5][1],RGB[5][2]); 
                           strip.show();     
                                  }          
          }
          
     
    Serial.println(F(""));  
             
 
if (WiFi.status() != WL_CONNECTED) {     
    offline=true;
        
      Serial.println(F("OFFLINE MODE-conection timeout "));  
        
  }else{
        
      Serial.println(F("WiFi connected"));
       
     }
  
 if(!offline){
              bot.begin();
              strip.setPixelColor(0,RGB[4][0],RGB[4][1],RGB[4][2]); 
              strip.show();
              bot.sendMessage(chat_id, "Prusa WatchDog is ONLINE "); 
  }
}


void check_wifi(){
  if(offline){ color=3; } else{ 
                                if (WiFi.status() != WL_CONNECTED) {
                                                                    color=6; //(3)YELLOW 
                                                                    if (!disconected) {Serial.println("OFFLINE"); }
                                                                    disconected=true;  
                                        } else {  
                                                 if(disconected ){         //&& !alarm
                                                                           disconected=false;
                                                                           color=2; //CIAN ONLINE(2)
                                                                           strip.setPixelColor(0,RGB[4][0],RGB[4][1],RGB[4][2]);   // LED is White  when when message send
                                                                           strip.show();
                                                                           if(alarm){ bot.sendMessage(chat_id, "RECONECTED, OFF"); }else{   bot.sendMessage(chat_id, "RECONECTED, ON");}
                                                                           Serial.println(F("RECONECTED"));
                                                                           }
                                                }
        

                                  } 
     
} 
