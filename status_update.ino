void status_update (int seconds){
  
  static String SMV=" ";
  if (timer.hasPassed(seconds)){ timer.restart();                                                                                       // send the Smoke Values every x seconds
                                 if(!alarm ){ SMV="| "; }else{ SMV="O ";}                                                               //if there is NO ALARM then "|"=ON, "O"=OFF
                                 SMV=SMV+smokeVal;
                                 Serial.println(SMV);
                                 if(!disconected && !offline){  strip.setPixelColor(0,RGB[4][0],RGB[4][1],RGB[4][2]);                   // LED is White  when when message send
                                                                strip.show();
                                                                bot.sendMessage(chat_id, SMV); }        
                                          }
}
