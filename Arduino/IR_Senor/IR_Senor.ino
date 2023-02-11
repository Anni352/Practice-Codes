int IRSensor = 9; //Connect IR Sensor Module to Arduino Pin 9
int LED = 7;     //Connect LED to Arduino Pin 13

void setup() 
{  
  Serial.begin(115200); //Init Seriala at 115200 Baud
  Serial.println("Serial Working"); //Test to check if Serial is working or not
  pinMode(IRSensor, INPUT); //IR Sensor Pin INPUT
  pinMode(LED, OUTPUT); //LED Pin output
}

void loop() 
{
  int sensorStatus = digitalRead(IRSensor); //Set the GPIO as Input
  if(sensorStatus == 1) //Check if the Pin is High or not
  {
    //If Pin is High Turn OFF the onboard LED
    digitalWrite(LED, LOW); //LED Low
    Serial.println("Motion Ended!");  //print Motion Ended! on the Serial Monitor Window
  }

  else
  {
    //else turn ON the onboard LED
    digitalWrite(LED, HIGH); //LED HIGH
    Serial.println("Motion Detected!"); //print Motion Detected! on the Serial Monitor Window
  }
}
