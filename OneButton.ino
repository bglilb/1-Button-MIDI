#include <DigiMIDI.h>

DigiMIDIDevice midi;
byte x;
byte lastX = 1;
void setup() {
  DDRB &= ~(1 << 0); //Sets Pin 0 to Input
  PORTB |= 1 << 0; //Sets Internal Pull Up High
}

void loop() {
  
  x = PINB;
  x = x & B00000001;
  
  if (x == 0 && lastX == 1) {
    lastX = x;
    midi.send(0x90,60,100,1); //Note On, Note #, Velocity, Channel
  } else if (x == 1 && lastX == 0) {
    lastX = x;
    midi.send(0x80,60,0,1); //Note Off, Note #, Velocity, Channel
  }
  midi.update();
  delayMicroseconds(500);
}
