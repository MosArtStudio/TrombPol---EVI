//  Trombpol.ino - Arduino program for Electronic Valve Instrument called Trombpol.
//  Created by R. Mosurek, March 2020.
//  Released into the public domain.
//  
//  I used a HX711 circuit and tensometric beam to enable Pitch Modulation.
//  You can play using a 6 valve buttons and octave potentiometer or 3 valve buttons, "fifth button" and octave potentiometer.
//  radekxqv@gmail.com
//  Pozdrawiam całą Przeginię i studio MosArt Studio.

#include <HX711.h>
#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>
#include "Trombpol.h"
MIDI_CREATE_DEFAULT_INSTANCE();

#define DOUT  3
#define CLK  4
HX711 scale(DOUT, CLK);
#define valve1 10
#define valve2 9
#define valve3 8
#define valveUP1 7
#define valveUP2 6
#define valveUP3 5
#define fifthButton 2
#define arpeggioMode 11


Trombpol trombpol;


void setup()
{
  
  Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OFF);
  pinMode(valve3, INPUT_PULLUP); 
  pinMode(valve2, INPUT_PULLUP); 
  pinMode(valve1, INPUT_PULLUP); 
  pinMode(valveUP3, INPUT_PULLUP);     
  pinMode(valveUP2, INPUT_PULLUP); 
  pinMode(valveUP1, INPUT_PULLUP); 
  pinMode(fifthButton, INPUT_PULLUP);  
  pinMode(arpeggioMode, INPUT_PULLUP);
  trombpol.blowTreshold = trombpol.CalibrateBlow(trombpol.calibrationTreshold);
  trombpol.setKey = 46;                // set transpose C root note (for Bb trumpet -> C = 46)
  trombpol.calibrationTreshold = 50;   // set treshold in CalibrateBlow method;

    //HX711 commands 
  scale.set_scale();
  scale.tare();  
  float calibration_factor = -2855; 
  long zero_factor = scale.read_average(); 
  scale.set_scale(calibration_factor); 
  trombpol.checkArpeggio = trombpol.ArpeggioMode(arpeggioMode);
}

void loop()
{
 
  trombpol.pitch = trombpol.MakeNote(trombpol.setKey);      
  trombpol.velocity = trombpol.MakeVelocity(trombpol.blowTreshold);
  trombpol.pitchBand = trombpol.MakePitchband(scale.get_units());
   
        if(trombpol.checkArpeggio != trombpol.ArpeggioMode(arpeggioMode))
       {
         if(trombpol.ArpeggioMode(arpeggioMode))
         {
           MIDI.send(trombpol.controlersOn, 64, 100, 1);
         }
         else
         {
           MIDI.send(trombpol.controlersOn, 64, 0, 1);
         }
         trombpol.checkArpeggio = trombpol.ArpeggioMode(arpeggioMode);
       }
        
  while(trombpol.velocity > 0)
  {
    MIDI.send(trombpol.noteOn, trombpol.pitch, 100, 1);

   do
   {
    
     if(trombpol.checkArpeggio != trombpol.ArpeggioMode(arpeggioMode))
       {
         if(trombpol.ArpeggioMode(arpeggioMode))
         {
           MIDI.send(trombpol.controlersOn, 64, 100, 1);
         }
         else
         {
           MIDI.send(trombpol.controlersOn, 64, 0, 1);
         }
         trombpol.checkArpeggio = trombpol.ArpeggioMode(arpeggioMode);
       }
       
       MIDI.send(trombpol.controlersOn, 2, trombpol.velocity, 1) ;    
       MIDI.send(trombpol.controlersOn, 1, trombpol.velocity, 1) ;    
       trombpol.velocity = trombpol.MakeVelocity(trombpol.blowTreshold);
       MIDI.send(trombpol.pitchOn, ((trombpol.pitchBand)&127), ((trombpol.pitchBand)>>7), 1);  
       trombpol.pitchBand = trombpol.MakePitchband(scale.get_units());
         
      if(trombpol.velocity == 0)
      {
        MIDI.send(trombpol.controlersOn, 2, trombpol.velocity, 1);
        break;
      }
   }
   while(trombpol.pitch == trombpol.MakeNote(trombpol.setKey));
   MIDI.send(trombpol.noteOn, trombpol.pitch, 0, 1);
  trombpol.pitch = trombpol.MakeNote(trombpol.setKey);       
  trombpol.velocity = trombpol.MakeVelocity(trombpol.blowTreshold);
  trombpol.pitchBand = trombpol.MakePitchband(scale.get_units());

  }
  
}
