// https://www.youtube.com/watch?v=wk_pxRhVNgA

#define OUT 11          // OUT PIN

void setup()
{
  Serial.begin(9600);
  pinMode(OUT, OUTPUT);
}

void loop()
{
  if(Serial.available()) 
  {
    long frequency = Serial.parseInt();
    Serial.print(Set_frequency(frequency));
    Serial.println(" Hz");
    delay(3000);
  }
}


long Set_frequency(long freq)
{
//  if(freq <= 15)
//  {
//    Serial.println("Minimum Freq is 16 Hz") 
//    freq = 16;
//  }
  TCCR1A = 0b01000000; 
  uint16_t ocr;
  if(freq < 16){
    TCCR1B = 0b00001100; 
    ocr = 31250UL/freq - 1;
    freq = 31250UL/(ocr+1);    
  }
  else if(freq < 134) 
  {
    //pre-scaler = 8
    TCCR1B = 0b00001010; 
    ocr = 1000000UL/freq - 1;
    freq = 1000000UL/(ocr+1);
  }
  else 
  {
    //pre-scaler = 1
    TCCR1B = 0b00001001;
    ocr = 8000000UL/freq - 1;
    freq = 8000000UL/(ocr+1);
  }
  OCR1AH = highByte(ocr);
  OCR1AL = lowByte(ocr);
  TIMSK1 = 0;
  return freq;
}
