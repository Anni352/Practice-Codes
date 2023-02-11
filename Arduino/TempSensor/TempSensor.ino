#include<SimpleDHT.h>

//for DHT11
//VCC:5V or 3V
//GND: GND
// DATA: 2

int pinDHT11 = A0;
SimpleDHT11 dht11(pinDHT11);


void setup() {
  // put your setup code here, to run once: 
  // start working.... 
  Serial.println("Temperature & Humidity Data : ");
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

byte temperature = 0;
byte humidity = 0;
int err = SimpleDHTErrSuccess;
if((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
  
  Serial.print("Read DHT11 failed, err = ");
  Serial.print(SimpleDHTErrCode(err));
  Serial.print(", ");
  Serial.println(SimpleDHTErrDuration(err));
  delay(1000);
  return;
  
  }
  
  Serial.print((int)temperature);
  Serial.print("*C");
  Serial.print(", ");
  Serial.print((int)humidity);
  Serial.println("H");

  //DHT11 Sampling Rate is 1Hz

  delay(1500);


}
