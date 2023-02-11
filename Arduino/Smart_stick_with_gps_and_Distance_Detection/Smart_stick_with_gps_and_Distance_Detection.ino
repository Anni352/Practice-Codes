#include <SoftwareSerial.h> 
#include <TinyGPS.h>
 
SoftwareSerial sgps(8, 9);
SoftwareSerial sgsm(7, 6);
TinyGPS gps;
 
int buttonpin = 13;
#define trigPin 2
#define echoPin 3
long duration;
int distance;
float gpslat, gpslon;
 
void setup()
 
{
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(5, OUTPUT);
  sgsm.begin(9600);
  sgps.begin(9600);
  Serial.begin(9600);
  delay(100);
  
  /*serial_connection.begin(9600);
  
  delay(100);
  Serial.print("—Tracking—");
  
  Serial.println("***Location***");
  /*gsmSerial.println("AT + CNMI = 2, 2, 0, 0, 0");
  delay(300);
  
  Serial.println("Initializing……");
  delay(200);
  
  Serial.println("System is Ready");
  delay(100);*/
  
}
 
void loop()
 
{
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance from Object : ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(10);
  
  if(distance <= 30 && distance > 15)
  {
    digitalWrite(5, HIGH);
    delay(10);
    
    digitalWrite(5, LOW);
    digitalWrite(5, HIGH);
    delay(10);

    digitalWrite(5, LOW);
    digitalWrite(5, HIGH);
    delay(10);
    
    digitalWrite(5, LOW);
  }
 
  else if(distance <= 15)
  {
    digitalWrite(5, HIGH);
    delay(1000);
  }
 
  else
    digitalWrite(5, LOW);
  
  if(digitalRead(buttonpin) == HIGH)
  {
    Serial.println("Button is Pressed.....");
    delay(2000);
    Serial.println("Sending Location......");
    delay(1000);
    SendMessage();
  }
}

void SendMessage()
{
  sgps.listen();
  while (sgps.available())
  {
    int c = sgps.read();
    if (gps.encode(c))
    {
      gps.f_get_position(&gpslat, &gpslon);
    }
  }
      sgsm.listen();
      sgsm.print("\r");
      delay(1000);
      sgsm.print("AT+CMGF=1\r");
      delay(1000);
      sgsm.print("AT+CMGS=\"+919319877255\"\r");
      delay(1000);
      //The text of the message to be sent.
      sgsm.print("Latitude : ");
      sgsm.println(gpslat, 6);
      sgsm.print("Longitude : ");
      sgsm.println(gpslon, 6);
      delay(1000);
      sgsm.write(0x1A);
      delay(1000);
      Serial.println("Location is sent......");
      delay(1000);
    
}
  /*if (serial_connection.available()>0)
    Serial.write(serial_connection.read());*/
 
  
  /*while(Serial.available())
  {
   Serial.read();
  }
 
  get_gsm();
}
 
float *get_gps()
 
{
    gpsSerial.listen(); 
    Serial.println("Get GPS location Inside");
 
    while(1)
    {
      while (gpsSerial.available() > 0)
      { 
        gps.encode(gpsSerial.read()); 
      }

      if(gps.location.isUpdated())
      {
        Serial.print("LATITUDE = "); Serial.println(gps.location.lat(), 6);
        Serial.print("LONGITUDE = "); Serial.println(gps.location.lng(), 6);
        lattitude=gps.location.lat();
        longitude=gps.location.lng();
        break;
      }
    }
 
    a[0] = lattitude;
    a[1]=longitude;
    return a;
}
 
void get_gsm()
{
  gsmSerial.listen();
  
  while(gsmSerial.available()>0)
  {
    Serial.println("INSIDE gsmSerial.available");
  
    if(gsmSerial.find("Track"))
    {
      Serial.println("INSIDE track");
      gsmSerial.println("AT + CMGF = 1");
      delay(1000);
      
      gsmSerial.println("AT + CMGS = \" +919319877255 \"\r"); //Phone Number
      delay(1000);
 
      p = get_gps();
      gsmSerial.listen();
 
      Serial.print("Your Car Location is: ");
      gsmSerial.print("Your Car Location : ");
 
      Serial.print("LATTITUDE = "); Serial.print(*p,6);
      gsmSerial.print("LATTITUDE = "); gsmSerial.print(*p,6); gsmSerial.print(",");// The SMS text you want to send
 
      Serial.print("LONGITUDE = "); Serial.print(*(p + 1),6);
      gsmSerial.print("LONGITUDE = ");gsmSerial.print(*(p + 1),6);// The SMS text you want to send
      delay(100);
 
      gsmSerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
      delay(1000);
    }
  }
}
*/ 
