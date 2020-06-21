#include <NewRemoteReceiver.h>
#include <Keyboard.h>

#define ADRES1 100
#define ADRES2 200
#define ADRES3 300
#define ADRES4 400

#define LEDINDICATOR 9
#define SCHAKELAAR   8
// Ontvanger zit aan Pen 3!

bool Actief=false;

void setup() { 
 Serial.begin(115200); // Voorkomt hangen!
 pinMode(LEDINDICATOR,OUTPUT);
 digitalWrite(LEDINDICATOR,LOW);
 pinMode(SCHAKELAAR,INPUT_PULLUP);
 
  // Initialize receiver on interrupt 0 (= digital pin 2*), calls the callback "showCode"
  // after 2 identical codes have been received in a row. (thus, keep the button pressed
  // for a moment)
  //
  // See the interrupt-parameter of attachInterrupt for possible values (and pins)
  // to connect the receiver.
  // *Let op: bij LEONARDO moet de ontvanger aan pen 3!!
  NewRemoteReceiver::init(0, 1, showCode); //NewRemoteReceiver::init(0,2, showCode);
  Keyboard.begin(); 
}

bool Onbekend=false;
void loop() {
 if(digitalRead(SCHAKELAAR)==LOW) {
  Actief = !Actief;
  digitalWrite(LEDINDICATOR,Actief); 
  delay(400);
 } 
 if(Onbekend) {
  for(int i=0; i<4; i++) {
   digitalWrite(LEDINDICATOR,LOW);
   delay(80);
   digitalWrite(LEDINDICATOR,HIGH);
   delay(80);    
  }
  digitalWrite(LEDINDICATOR,Actief);
  Onbekend=false;
 }
}

void showCode(NewRemoteCode receivedCode) {
 // Note: interrupts are disabled. You can re-enable them if needed.  
 if(!Actief) return;

 if(receivedCode.address==ADRES1)
  Keyboard.print("1");
 else if(receivedCode.address==ADRES2)
  Keyboard.print("2");
 else if(receivedCode.address==ADRES3)
  Keyboard.print("3");
 else if(receivedCode.address==ADRES4)
  Keyboard.print("4");
 else   
  Onbekend=true;  
}
