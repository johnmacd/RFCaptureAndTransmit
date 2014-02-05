#include <EEPROM.h>

// These constants won't change.  They're used to give names
// to the pins used:
const int cutOff = 200;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int outPin = 13;
const int valuesSize =128;
const int numButtons =4;
byte values[numButtons][valuesSize];
unsigned long time;

void setup() {
  pinMode( outPin, OUTPUT );
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  delay(100);
  Serial.println("lets go");
}

void loop() {
  char buf[3];
  buf[3] = '/n';
  if (Serial.readBytes(buf, 2) )
  {
    int button = buf[1]-48;
    button = button<0? 0 : button;
    button = button>numButtons? 0 : button;
    if (buf[0] == 'w' )
    {
      Serial.println("waiting");
      while ( analogRead(analogInPin) < cutOff )
      {
      }
      buf[0] = 'r';
    }
    if (buf[0] == 'r' )
    {
      Serial.println("going");
      Serial.println(buf);
      Serial.println(button);
      
      // read the analog in value:
      time = micros();
      for( int i=0; i<valuesSize; ++i) 
      {
        for (int j=0; j<8; ++j )
        {
          int value = analogRead(analogInPin);
          if ( value > cutOff )
          {
            bitSet(values[button][i], j); 
          }
          else
          {
            bitClear(values[button][i], j);
          }  
        }
      }         
      time = micros() -time;
      Serial.print("Time: ");
      Serial.println(time);
    }
    if (buf[0] == 'p' )
    {
      int current(0);
      int last(0);
      int length(0);
      Serial.println("Start"); 
      for( int i=0; i<valuesSize; ++i) 
      {
        for (int j=0; j<8; ++j )
        {
          current = bitRead(values[button][i],j);
          if ( current == last )
          {
            ++length;
          }else
          {
            Serial.print( last );
            Serial.print( ", ");
            Serial.println( length );
            last = current;
            length = 0;
          }
        }
      }  
      Serial.print( last );
      Serial.print( ", ");
      Serial.println( length );
           
      Serial.println("End");
      Serial.print("Time: ");
      Serial.println(time);
    }
    if (buf[0] == 'b' )
    {
       Serial.println(button);
      unsigned long t = micros();
      for( int i=0; i<valuesSize; ++i) 
      {
        for (int j=0; j<8; ++j )
        {
          digitalWrite(outPin, bitRead(values[button][i],j));
          delayMicroseconds( 109 );
        }
      }  
      digitalWrite( outPin, LOW);
      t = micros() -t;
      Serial.print("Time: ");
      Serial.println(t);
    }
    if (buf[0]=='s' )
    {
      Serial.println("Saving");
      int k=0;
      for ( button=0; button< numButtons; button++ )
      {
        for( int i=0; i<valuesSize; ++i) 
        {
            EEPROM.write(k,values[button][i]);
            k++;
        }
      }
      Serial.println("Saved");
    }
    if (buf[0]=='l' )
    {
      Serial.println("Loading");
      int k=0;
      for ( button=0; button< numButtons; button++ )
      {
        for( int i=0; i<valuesSize; ++i) 
        {
            values[button][i] = EEPROM.read(k);
            k++;
        }
      }
      Serial.println("Loaded");
    }
   }
  
  delay(10);                     
}
