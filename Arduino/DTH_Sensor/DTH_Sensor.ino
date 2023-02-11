#include "dht.h"
#define DHTPIN 2 // Analog Pin sensor is connected to
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup(){
 
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 
}//end "setup()"
 
void loop(){
  //Start of Program 
 
    delay(2000);
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    
    if (isnan(h) || isnan(t) || isnan(f))
    {
      Serial.println(F("Failed to read from DHT Sensor !!"));
      return;
    }


    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(f, h, false);
    
    Serial.print(F("Current Humidity = ");
    Serial.print(h);
    Serial.print(F("% Current Temperature = ");
    Serial.print(t); 
    Serial.print(F("°C  "));
    Serial.print(f); 
    Serial.print(F("°F Heat Index = "));
    Serial.print(hic);
    Serial.print(F("°C  "));
    Serial.print(hif);
    Serial.print(F("°F  ")); 
     
    
    
    delay(5000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop()
