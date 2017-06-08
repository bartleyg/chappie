int mouthLEDPin = 5; // arduino pins 5 and 6 analogwrite are interfered with by delay function

void setup()
{
  pinMode(mouthLEDPin, OUTPUT);
}

void loop()
{
  digitalWrite(mouthLEDPin, HIGH);
  delay(20);
  digitalWrite(mouthLEDPin, LOW);
  delay(20);
}
