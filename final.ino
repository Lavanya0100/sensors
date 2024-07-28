#include<servo.h>
servo myservo;
int pot=0;
int vol;
void setup()
{
  Serial.begin(9600);
  myservoattach(9);

}
void loop()
{
  
}