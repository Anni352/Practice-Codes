#include "Wire.h" // This library allows you to communicate with I2C devices.
#include <ESP8266WiFi.h>
#include <string>

#ifndef STASSID
#define STASSID "***"   //Enter Wifi Name here
#define STAPSK  "***"   //Enter Wifi Password here
#endif

int disc = 15;

int pres = 14;
int erase = 13;

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.1.7";
const uint16_t port = 5050;

const char* DISCONNECT_MESSAGE = "!DISCONNECT";
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t ax, ay, az; // variables for accelerometer raw data
int16_t gx, gy, gz; // variables for gyro raw data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  Serial.begin(115200);
  pinMode(pres , INPUT);
  pinMode(erase , INPUT);
  pinMode(disc , INPUT);
  pinMode(12 , OUTPUT);
  digitalWrite(12 , HIGH);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());//"192.168.1.7"
}

String readings(){
  Wire.beginTransmission(MPU_ADDR);
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
        Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
        Wire.requestFrom(MPU_ADDR, 72, true); // request a total of 72=14 registers

        // "Wire.read()<<8 | Wire.read();" 
        ax = Wire.read()<<8 | Wire.read(); 
        ay = Wire.read()<<8 | Wire.read(); 
        az = Wire.read()<<8 | Wire.read(); 
        gx = Wire.read()<<8 | Wire.read(); 
        gy = Wire.read()<<8 | Wire.read(); 
        gz = Wire.read()<<8 | Wire.read();
        float p = analogRead(pres);
        int e = digitalRead(erase);

        String JSONtext = String("'{\"accX\" : ")+=String(convert_int16_to_str(ax))+=String(", \"accY\" : ")+=String(convert_int16_to_str(ay/100))+=String(", \"accZ\" : ")+=String(convert_int16_to_str(az/100))+=String(",\"gyroX\" : ")+=String(convert_int16_to_str(gx))+=String(", \"gyroY\" : ")+=String(convert_int16_to_str(gy))+=String(", \"gyroZ\" : ")+=String(convert_int16_to_str(gz))+=String(" , \"pressure\" : ")+=String(p)+=String(" , \"erase\" : ")+=String(e)+=String("}'");
        //String JSONtext = "'{\"accX\" : ".concat(convert_int16_to_str(ax/100)).concat(", \"accY\" : ").concat(convert_int16_to_str(ay/100)).concat(", \"accZ\" : ").concat(convert_int16_to_str(az/100)).concat(",\"gyroX\" : ").concat(convert_int16_to_str(gx)).concat(", \"gyroY\" : ")).concat(convert_int16_to_str(gy)).concat(", \"gyroZ\" : ").concat(convert_int16_to_str(gz)).concat("}'");
  // delay
  //delay(1000);
  return JSONtext;  
}
void loop() {
  static bool wait = true;

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  while(client.connected()) {
    String data=readings();
    client.print("");
    client.print(data);
    Serial.println(data);
    if(digitalRead(disc))
    {
      client.print(DISCONNECT_MESSAGE);
    }
    delay(100);
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  if (wait) {
    delay(60000); // execute once every 1 minutes, don't flood remote service
  }
  wait = true;    
}
