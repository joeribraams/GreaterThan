#define inPin 14
#define outPin 13

int gate = 2000;
void setup()
{
  pinMode(outPin, OUTPUT);
  analogReadResolution(12);
}

void loop()
{
  if(analogRead(inPin) > gate)
  {
    digitalWrite(outPin, HIGH);
  }
  else
  {
    digitalWrite(outPin, LOW);
  }

  delayMicroseconds(30);    
}
