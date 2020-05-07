# TrombPol
  It's an Electronic Valve Instrument called Trombpol.

  
 ## Creating an instrument
 
  To bulid an EVI you have to use a microcontroler, 7 buttons, potentiometer 10k, pressure sensor and tensometric beam with HX711 circuit.
  
  I used a HX711 circuit and tensometric beam to enable Pitch Modulation and MPX5010dp for breath controller.
  
  ## Usage
  You can play using a 6 valve buttons and octave potentiometer or 3 valve buttons, "fifth button" and octave potentiometer.
  
  Arpeggio button alowes you to hold a few notes (like a sustain pedal).
  
  Potentiometer changes an octave.
  
  Valves 1, 2 and 3 are decresing a notes (like on a trumpet).
  
  Valves up1, up2 and up3 are increasing a notes.
  
  Fifth button changes a notes to fifth interval. 
  
  
  ## Connection
  Make a simple MIDI output circuit. 
  
  Pin map:
  
  DOUT  3, CLK  4 (from HX711)
  

  valve1 - pin 10
  
  valve2 - pin 9
  
  valve3 - pin 8
  
  valveUP1 - pin 7
  
  valveUP2 - pin 6
  
  valveUP3 - pin 5
  
  fifthButton - pin 2
  
  arpeggioMode - pin 11
  

  Octave potentiometer - A0
  
  Pressure sensor - A1

## HAVE FUN

  Created by R. Mosurek, March 2020.
  
  Released into the public domain.
  
  Contact me for details - radekxqv@gmail.com
  
  Pozdrawiam całą Przeginię i studio MosArt Studio.
  
  IG - @radoslawmosart
