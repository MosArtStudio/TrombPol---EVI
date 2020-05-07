/*
  Trombpol.h - Library for Electronic Valve Instrument called Trombpol.
  Created by R. Mosurek, March 2020.
  Released into the public domain.
  
  I used a HX711 circuit and tensometric beam to enable Pitch Modulation.
  You can play using a 6 valve buttons and octave potentiometer or 3 valve buttons, "fifth button" and octave potentiometer.
  radekxqv@gmail.com
  Pozdrawiam całą Przeginię i studio MosArt Studio.
*/

#ifndef Trombpol_h
#define Trombpol_h
#include "Arduino.h"

#define DOUT  3
#define CLK  4
#define valve1 10
#define valve2 9
#define valve3 8
#define valveUP1 7
#define valveUP2 6
#define valveUP3 5
#define arpeggioMode 11
#define fifthButton 2
class Trombpol
{
  public:
    Trombpol();
    bool ArpeggioMode(int button);
    int CalibrateBlow(int calibrationTreshold);
    int MakeVelocity(int blowTreshold);
    int MakePitchband(double getValue);
    int MakeNote(int setKey);
    bool checkArpeggio;
    int setKey = 46;
    int calibrationTreshold = 50;
    double getValue;
    int pitch = 0; 
    int velocity = 0;
    int upVelocity = 0;
    int pitchBand = 0;
    int blowTreshold = 0;
    int noteOn = 144;
    int controlersOn = 176;
    int pitchOn = 224;
  private:
    
    int key;
    int lips;
};

#endif
