// Advanced Microcontroller-based Audio Workshop
// 
// Part 1-4: Blink LED while Playing Music
//
// Do something while playing a music file.  Admittedly
// only blink Teensy's LED and print info about the
// playing time in the file.  The point is that Arduino
// sketch code is free to do other work while the audio
// library streams data from the SD card to the headphones.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav           playSdWav1;
AudioOutputI2S           audioOutput;
AudioConnection          patchCord1(playSdWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playSdWav1, 1, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;

void setup() {
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.45);
  SPI.setMOSI(7);
  SPI.setSCK(14);
  if (!(SD.begin(10))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  pinMode(13, OUTPUT); // LED on pin 13
  delay(1000);
}

void loop() {
  if (playSdWav1.isPlaying() == false) {
    Serial.println("Start playing");
    playSdWav1.play("SDTEST3.WAV");
    delay(10); // wait for library to parse WAV info
  }
  // blink LED and print info while playing
  digitalWrite(13, HIGH);
  Serial.print("Playing, now at ");
  Serial.print(playSdWav1.positionMillis());
  Serial.println(" ms");
  delay(250);
  digitalWrite(13, LOW);
  delay(250);
}




