/*
  Trombpol.cpp - Library for Electronic Valve Instrument called Trombpol.
  Created by R. Mosurek, March 2020.
  Released into the public domain.
  
  I used a HX711 circuit and tensometric beam to enable Pitch Modulation.
  You can play using a 6 valve buttons and octave potentiometer or 3 valve buttons, "fifth button" and octave potentiometer.
  radekxqv@gmail.com
  Pozdrawiam całą Przeginię i studio MosArt Studio.
*/

#include "Arduino.h"
#include "Trombpol.h"


Trombpol::Trombpol()
{

}


bool Trombpol::ArpeggioMode(int button)         
{
  int value;
  if(digitalRead(button) == LOW)
  {
    value = true;
  }
  else
  {
    value = false;
  }
  return value;
}

int Trombpol::CalibrateBlow(int calibrationTreshold)
{
  int a;
  int value = 0;
  for(int i=0; i<2000; i++)
  {
    a = analogRead(A1);
    if(a > value)
    {
      value = a;
    }
    delay(1);
  }
  
  return value + calibrationTreshold;
}

int Trombpol::MakeVelocity(int blowTreshold)
{
  
  int value = analogRead(A1);
  value = map(value, blowTreshold, blowTreshold + 127, 0, 127); //przeskalowanie
  if(value > 127)
  {
    value = 127;
  }
  if(value < 0)
  {
    value = 0;
  }
  return value;
}


int Trombpol::MakePitchband(double getValue)
{
  int tresh = 100;
  int value = getValue;
  value = map(value, -800, 800, 0 - tresh, 16383 + tresh);//pierwsza wartość = treshold, środek 64


  if (value < (8192 + tresh)  & value > (8192 - tresh))
  {
    value = 8192;
  }
  if(value >= (8192 + tresh) & value < (16383 + tresh))
  {
    value = value - tresh;
  }
  if(value > -tresh & value <= (8192 - tresh))
  {
    value = value + tresh;
  }
  if(value <= -tresh)
  {
    value = -0;
  }
  if(value >= 16383 + tresh)
  {
    value = 16383;
  }

  Serial.println(value);
  return value;
}

int Trombpol::MakeNote(int setKey)
{
  key = setKey;
  lips = analogRead(A0);
  lips = map(lips, 0, 1023, 0, 6); 
  bool octave;

  if(digitalRead(fifthButton) == LOW) 
  {
  key = key + 7;
  octave = false;
  }
  else
  {
  octave = true;
  }
  switch (lips)   //octave changes
  {

    case 1:
      key = key + 12;
      break;
  
    case 2:
      key = key + 24;
      break;
  
    case 3:
      key = key + 36;
      break;
     
    case 4:
      key = key + 48;
      break;
  
    case 5:
      key = key + 60;
      break;
  
    case 6:
      key = key + 72;
      break;
  
     default:
     break;
  }



                
  if(digitalRead(valve3) == LOW) 
  {
    key = key - 3;
    }
  if(digitalRead(valve2) == LOW) 
    {
    key = key - 1;
    }
  if(digitalRead(valve1) == LOW) 
    {
    key = key - 2;
    }
    
  if(digitalRead(valveUP3) == LOW || digitalRead(valveUP2) == LOW || digitalRead(valveUP1) == LOW) 
    {
      if(octave)    
      {
        key = key + 7;
      } 
      else        
      {
        key = key + 5;
      }
     if(digitalRead(valveUP3) == LOW) 
       {
       key = key - 3;
       }
     if(digitalRead(valveUP2) == LOW) 
       {
       key = key - 1;
       }
     if(digitalRead(valveUP1) == LOW) 
       {
       key = key - 2;
       }
    }
  //Serial.println(key);
  return key;
}
