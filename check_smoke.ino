int readSmokeSensor(){ //Sharp Optical Dust Sensor GP2Y1010AU0F

 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
byte samples=10;
int smoke = 0;
  
  for(int i=0; i<samples;i++){
     digitalWrite(smokeLed_PIN,LOW); // power on the IR LED
     delayMicroseconds(samplingTime);
     smoke=smoke+analogRead(smokeSens_PIN);
     delayMicroseconds(deltaTime);
     digitalWrite(smokeLed_PIN,HIGH); // turn the IR LED off
     delayMicroseconds(sleepTime);
  }
 
 
  smoke = smoke/samples;
  return smoke;
}


void check_smoke() {

smokeVal=readSmokeSensor();              // read smoke sensor
if (smokeVal>maxSmoke){   delay(400);    // if it is higher than previsouly readed max values wait for 400ms and check again to be sure its realy smoke and not measurment error 
                          smokeVal=readSmokeSensor();
                          if (smokeVal>maxSmoke){  maxSmoke=smokeVal;
                                                   Serial.print("++max: ");
                                                   Serial.println(maxSmoke); 
                                                   }
                         }


if (maxSmoke>smokeLimit ){ //&& !alarm
                              digitalWrite(relay_PIN,LOW);   // if its greater than the threshold ( smoke limit) trigers the ALARM and actions
                              color=1;
                              if(!alarm){  alarm=true;  
                                           Serial.print(F("SMOKE DETETECTED: "));
                                           Serial.println(smokeVal);
                                           if(!disconected && !offline){  strip.setPixelColor(0,RGB[4][0],RGB[4][1],RGB[4][2]);                   // LED is White  when when message send
                                                                          strip.show();   
                                                                          bot.sendMessage(chat_id, "SMOKE DETECTED !");
                                                           }
                                        }
    }
 
  // Serial.print(smokeVal);
  // Serial.println(smokeLimit);
  

}
