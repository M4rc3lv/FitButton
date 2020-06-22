#include <NewRemoteTransmitter.h>

#define ADRES 200
#define ZENDER_PEN 0

NewRemoteTransmitter transmitter(ADRES, ZENDER_PEN, 180, 2);

void setup() { 
 transmitter.sendUnit(1, true);   
}

void loop() { 
 delay(15000);
}
