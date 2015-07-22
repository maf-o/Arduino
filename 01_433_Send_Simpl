#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int led = 13;

void setup() {

  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  
}

void loop() {
  
  /* See Example: TypeA_WithDIPSwitches */
  
/*                 Codierung           */
/*                 Fern-               */
/*                 bedienung           */
/*                            Taste    */
/*                   12345    ABCD     */
  mySwitch.switchOn("10000", "10000");
  delay(2000);
  mySwitch.switchOff("10000", "10000");
  delay(1000);

}
