#define pin_led 7
void setup() 
{
  pinMode(pin_led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
    const int recebido = Serial.parseInt();
    if(recebido == 1)
    {
      digitalWrite(7,HIGH);
    }
    else
    {
      digitalWrite(7,LOW);
    }
  }
}
