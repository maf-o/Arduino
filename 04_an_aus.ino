//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 9 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(9,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=250;
unsigned long time;

int an;
int aus;
int anzeige;
boolean ausgang = true;

void setup() {
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  
  
  an = 10;
  aus = 10;
  anzeige = 0;
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}


/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
void writeArduinoOn7Segment() {
  lc.setChar(0,0,'a',false);
  delay(delaytime);
  lc.setRow(0,0,0x05);
  delay(delaytime);
  lc.setChar(0,0,'d',false);
  delay(delaytime);
  lc.setRow(0,0,0x1c);
  delay(delaytime);
  lc.setRow(0,0,B00010000);
  delay(delaytime);
  lc.setRow(0,0,0x15);
  delay(delaytime);
  lc.setRow(0,0,0x1D);
  delay(delaytime);
  lc.clearDisplay(0);
  delay(delaytime);
} 



void loop() { 
  
  int down_an = digitalRead(2);
  int up_an = digitalRead(3);
  int down_aus = digitalRead(4);
  int up_aus = digitalRead(5);
  
  if (down_an == HIGH) {
    an = an - 10;
    if (an < 0){
      an = 0;
    }
    time = millis() + an* 1000;
  }
  
  if (up_an == HIGH) {
    an = an + 10;
    time = millis() + an* 1000;
  }
  
  
  
  if (down_aus == HIGH) {
    aus = aus - 10;
    if (aus < 0){
      aus = 0;
    }

  }
  
  if (up_aus == HIGH) {
    aus = aus + 10;

  }
  
  if (millis() == time){
    
    ausgang =! ausgang;
    
    if (ausgang == false){
      
      time = millis() + aus* 1000;
    
    } else {
      
      time = millis() + an* 1000;
    }
  
  }

  
    anzeige = an;
    lc.setDigit(0,0,anzeige %10,false);
    anzeige = anzeige/10;
    lc.setDigit(0,1,anzeige %10,false);
    anzeige = anzeige/10;
    lc.setDigit(0,2,anzeige %10,false);
    anzeige = anzeige/10;
    lc.setDigit(0,3,anzeige %10,false);
    
    anzeige = aus;
    lc.setDigit(0,4,anzeige %10,false);
    anzeige = anzeige/10;
    lc.setDigit(0,5,anzeige %10,false);
    anzeige = anzeige/10;
    lc.setDigit(0,6,anzeige %10,false);
    anzeige = anzeige/10;
    lc.setDigit(0,7,anzeige %10,false);
    
    delay(delaytime);
    digitalWrite(6,ausgang);

}