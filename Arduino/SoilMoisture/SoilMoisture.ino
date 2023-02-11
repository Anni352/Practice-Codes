#define soilWet 300    //Define max. value we consider soil 'wet'
#define soilDry 900   //Define min. value we consider soil 'dry'

#define sensorPin A0

void setup() 
{
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  //get the reading from the function below and print it
  int moisture = analogRead(sensorPin);
  Serial.print("Analog Output : ");
  Serial.println(moisture);

  //Determine the status of soil
  if(moisture < soilWet)
  {
      Serial.println("Status : Soil is Extremely Wet");
  }
  else if(moisture >= soilWet && moisture < soilDry)
  {
      Serial.println("Status : Soil Moisture is Perfect");
  }
  else
  {
      Serial.println("Status : Soil is too dry - Time to Water!");
  }
}
