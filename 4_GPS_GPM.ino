#include <TinyGPS++.h>

char buffer1[32];
char buffer2[32];
char phone_no[] = "+84342086819";

#define RXD2 16
#define TXD2 17
#define BUZZER_PIN 4
HardwareSerial neogps(1);
TinyGPSPlus gps;

String message; 
String text1 , text2, text3, text4, text5, speed;
void setup() 
{
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("neogps serial initialize");
  Serial.println("AT+CMGF=1\r"); //Lệnh này đưa tin nhắn về dạng text, phải có lệnh này mới đọc, gửi tin nhắn dạng text đc nhé :)
  delay(1000);
  Serial.println("AT+CNMI=2,2,0,0,0\r"); //Hiển thị ngay nếu tin nhắn gửi đến
  delay(1000);
  delay(1000);
  text1 ="";
  text2 = String("http://maps.google.com/maps?q=loc:");
  text3 = String(",");
  text4 = String("ON WARNING");
  text5 = String("OFF WARNING");
  Serial.println();
}

void sendmessage() 
{
  if (Serial.available()>0)
  {
  message = Serial.readString();
  }

  if(message.indexOf("FIND") > -1)
  {
    Serial.println("AT+CMGF=1");   
    delay(1000);
    Serial.println("AT+CMGS=\"+84342086819\"\r"); //Mobile phone number to send message
    delay(1000);
    String SMS1 = speed;
    Serial.println(SMS1);
    delay(100);
    String SMS = text1;
    Serial.println(SMS);
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    delay(500);
    Serial.println("GPS Location SMS Sent Successfully.");
    message="";
  }
}

void on_buzzer() 
{
  if (Serial.available() > 0) 
  {
    message = Serial.readString();
  }
  if (message.indexOf("ON") > -1) 
  {
    Serial.println("AT+CMGF=1");   
    delay(1000);
    Serial.println("AT+CMGS=\"+84342086819\"\r"); //Mobile phone number to send message
    delay(1000);
    delay(100);
    String SMS = text4 ;
    Serial.println(SMS);
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    delay(500);
    Serial.println("BUZZER ON.");
    message="";
    digitalWrite(BUZZER_PIN, HIGH);
  } 
}

void off_buzzer() 
{
  if (Serial.available() > 0) 
  {
    message = Serial.readString();
  }
  if (message.indexOf("OFF") > -1) 
  {
    Serial.println("AT+CMGF=1");   
    delay(1000);
    Serial.println("AT+CMGS=\"+84342086819\"\r"); //Mobile phone number to send message
    delay(1000);
    delay(100);
    String SMS = text5 ;
    Serial.println(SMS);
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    delay(500);
    Serial.println("BUZZER OFF.");
    message="";
    digitalWrite(BUZZER_PIN, LOW);
  } 
}

void loop() 
{
  speed = "";
  text1 = "";
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
         newData = true;
      }
    }
  }
  speed += String("Speed: ");
  speed += String(gps.speed.kmph());
  speed += String(" km/h");
  //Serial.println(speed);
  text1 += text2;   
  text1 += String(gps.location.lat(), 6);;
  text1 += text3;
  text1 += String(gps.location.lng(), 6);
  //Serial.println(text1);
  sendmessage(); 
  on_buzzer();
  off_buzzer();
}