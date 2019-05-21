/*
 Using RCWL-0516 microwave proximity switch module
 PINs
 RCWL-0516 PIN           ESP32 PIN
     GND                    GND
     OUT                     0
     VIN                     5V
 Info
  RCWL-0516 (https://github.com/jdesbonnet/RCWL-0516/)
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
*/


#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

#if OLED==1
    #include <U8g2lib.h>
    #ifdef U8X8_HAVE_HW_SPI
        #include <SPI.h>
    #endif
    #ifdef U8X8_HAVE_HW_I2C
        #include <Wire.h>
    #endif
    U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16); 
#endif 



void setup(void) {
  // Start the serial
  Serial.begin(115200);
 
  // Define sensor
  pinMode(SensorPin, INPUT);
  #if BUILTINLED==1
      pinMode(LED_BUILTIN, OUTPUT);
  #endif
  #if OLED==1  
      u8g2.begin();
  #endif
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);

}

void loop(void) {
  #if OLED==1
    // Clear OLED buffer
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_lucasfont_alternate_tf);
  #endif
  int sensorValue = digitalRead(SensorPin);
  if (sensorValue == HIGH) {
    #if BUILTINLED==1
        digitalWrite(LED_BUILTIN, HIGH);
    #endif
    Serial.println("Motion detected!");
    #if OLED==1
        u8g2.drawStr(0,15,"Motion");
        u8g2.sendBuffer();
    #endif
    #if BUZZER==1
      digitalWrite(BuzzerPin, HIGH);
      delay(1000);
    #endif
  }
  else {
    #if BUILTINLED==1
        digitalWrite(LED_BUILTIN, LOW);
    #endif
    //Serial.println("No motion!");
    #if OLED==1
        u8g2.drawStr(0,15,"NO motion");
        u8g2.sendBuffer();
    #endif
  }
  delay(1000);  
}
