#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<Wire.h>
#include<time.h>
#include "ThingSpeak.h"

ESP8266WebServer server (80);

unsigned long ch_no = 1884500;
const char * write_api = "MT9WXY82MXWMQ4CN";
const char* ssid = "SHASHANK@1-2.4G";
const char* password = "ROHINI@12";

//const char* ssid = "Galaxy M32 5GFC49";
//const char* password = "dzfa7141";

//const char* ssid = "Galaxy M312C8E";
//const char* password = "qbgw8748";

//const char* ssid = "Galaxy M314528";
//const char* password = "swwr4536";

WiFiClient client;

char input[12];
int count = 0;
int a;
int p1=0,p2=0,p3=0,p4=0;
int c1=0,c2=0,c3=0,c4=0;

int total = 0;
int count_prod = 0;
String page = "";
void setup()
{ 
  pinMode(D6,INPUT_PULLUP);
  pinMode(D0,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  
  Serial.begin(9600);
  configTime(11 * 1800, 0, "pool.ntp.org", "time.nist.gov");
  
  Wire.begin(D2, D1);
  server.on("/", []()
  {
    page = "<html><head><title>E Cart using IoT</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  #3498db ;color: white;}table,td {border: 1px solid black;font-size: x-large;";
    page += "text-align:center;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Shopping Cart</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr><tr><td>Biscuit</td><td>"+String(p1)+"</td><td>"+String(c1)+"</td></tr>";
    page += "<tr><td>Soap</td><td>"+String(p2)+"</td><td>"+String(c2)+"</td></tr><tr><td>Rice(1KG)</td><td>"+String(p3)+"</td><td>"+String(c3)+"</td>";
    page += "</tr><tr><td>Milk(50g)</td><td>"+String(p4)+"</td><td>"+String(c4)+"</td></tr><tr><th>Grand Total</th><th>"+String(count_prod)+"</th><th>"+String(total)+"</th>";
    page += "</tr></table><br><input type=\"button\" name=\"Paytm\" onclick = \"window.location.href='https://paytm.com/'\" value=\"Paytm\" style=\"width: 200px;height: 50px;\"></body></html>";
    page += "<input type=\"button\" name=\"Cash Payment\" onclick = \"\" value=\"Cash Payment\" style=\"width: 200px;height: 50px;\"></body></html>";
    page += "<meta http-equiv=\"refresh\" content=\"2\">";
    server.send(200, "text/html", page);
  });
  server.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("WiFi Connecting...  ");
  }
  Serial.print(WiFi.localIP());
  Serial.println("WiFi Connected");
  delay(2000);
  ThingSpeak.begin(client);
}
void loop()
{
  int a=digitalRead(D6);
  time_t now = time(nullptr);
  if (Serial.available())
  {
    count = 0;
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    Serial.println(input);
    if (count == 12)
    {
      if ((strncmp(input, "4C00965C50D6", 12) == 0) && (a == 1))
      {
        p1++;
        c1 = p1 * 24.00;
        digitalWrite(D0,HIGH);
        digitalWrite(D4,HIGH);
        delay(2000);
        total = total + 24.00;
        count_prod++;
        digitalWrite(D0,LOW);
        digitalWrite(D4,LOW);
        senddata("Biscuit");
      }
      else if ((strncmp(input, "4C00965C50D6", 12) == 0) && (a == 0))
      {
        if(p1>0)
        {
        digitalWrite(D0,HIGH);
        digitalWrite(D3,HIGH);
        delay(2000);
        p1--;
        c1 = p1 * 24.00;
        total = total - 24.00;
        count_prod--;
        
        digitalWrite(D0,LOW);
        digitalWrite(D3,LOW);
        }
        else
        {
        digitalWrite(D0,HIGH);
        digitalWrite(D3,HIGH);
        delay(2000);
        digitalWrite(D0,LOW);
        digitalWrite(D3,LOW);
       
        }
      }
      else if ((strncmp(input, "4C0095B5016D", 12) == 0) && (a == 1))
      {
        total = total + 30.00;
        digitalWrite(D0,HIGH);
        digitalWrite(D4,HIGH);
        delay(2000);
        p2++;
        c2 = p2 * 30.00;
        count_prod++;
        digitalWrite(D0,LOW);
        digitalWrite(D4,LOW);
        senddata("Soap");
      }
      else if ((strncmp(input, "4C0095B5016D", 12) == 0) && (a == 0))
      {
         if(p2>0)
        {
        digitalWrite(D0,HIGH);
        digitalWrite(D3,HIGH);
        delay(2000);
        p2--;
        c2 = p2 * 30.00;
        total = total - 30.00;
        count_prod--;
        digitalWrite(D0,LOW);
        digitalWrite(D3,LOW);
        }
        else
        {
        digitalWrite(D0,HIGH);
        digitalWrite(D3,HIGH);
        delay(2000);
        
        digitalWrite(D0,LOW);
        digitalWrite(D3,LOW);
        }
      }
      else if ((strncmp(input, "4C00963E06E2", 12) == 0) && (a == 1))
      {
        total = total + 60.00;
        digitalWrite(D0,HIGH);
        digitalWrite(D4,HIGH);
        delay(2000);
        p3++;
        c3 = p3 * 60.00;
        count_prod++;
        digitalWrite(D0,LOW);
        digitalWrite(D4,LOW);
        senddata("Rice");
      }
      else if ((strncmp(input, "4C00963E06E2", 12) == 0) && (a == 0))
      {
         if(p3>0)
        {
        digitalWrite(D0,HIGH);
        digitalWrite(D3,HIGH);
        delay(2000);
        p3--;
        c3 = p3 * 60.00;
        total = total - 60.00;
        count_prod--;
        digitalWrite(D0,LOW);
        digitalWrite(D3,LOW);
        }
        else
        {
        digitalWrite(D0,HIGH);
        digitalWrite(D3,HIGH);
        delay(2000);
        
        digitalWrite(D0,LOW);
        digitalWrite(D3,LOW);
        }
      }
      else if ((strncmp(input, "4C0095AC7603", 12) == 0) && (a == 1))
      {
        total = total + 50.00;
        digitalWrite(D0,HIGH);
        digitalWrite(D4,HIGH);
        delay(2000);
        p4++;
        c4 = p4 * 50.00;
        count_prod++;
        digitalWrite(D0,LOW);
        digitalWrite(D4,LOW);
        senddata("Milk");
      }
      else if ((strncmp(input, "4C0095AC7603", 12) == 0) && (a == 0))
      {
         if(p4>0)
        {
        digitalWrite(D0,HIGH);
        digitalWrite(D3,HIGH);
        delay(2000);
        p4--;
        c4 = p4 * 50.00;
        total = total - 50.00;
        count_prod--;
        digitalWrite(D0,LOW);
        digitalWrite(D3,LOW);
        }
        else
        {
        digitalWrite(D0,HIGH);
        digitalWrite(D3,HIGH);
        delay(2000);
        
        digitalWrite(D0,LOW);
        digitalWrite(D3,LOW);
        }
      }
      else if (strncmp(input, "4000351B7B15", 12) == 0)
      {
        
        digitalWrite(D0,HIGH);
        digitalWrite(D4,HIGH);
        delay(5000);
        digitalWrite(D0,LOW);
        digitalWrite(D4,LOW);
        digitalWrite(D0,LOW);
        digitalWrite(D4,LOW);
      }
    }
   
  }
  
server.handleClient();
}
void senddata(String input)
{
//  ThingSpeak.setField(1,p1);
  ThingSpeak.setField(1,c1);
//  ThingSpeak.setField(2,p2);
  ThingSpeak.setField(2,c2);
//  ThingSpeak.setField(5,p3);
  ThingSpeak.setField(3,c3);
//  ThingSpeak.setField(7,p4);
  ThingSpeak.setField(4,c4);
  ThingSpeak.setField(5,count_prod);
  ThingSpeak.setField(6,total);
//  ThingSpeak.setField(2, str);
  ThingSpeak.writeFields(ch_no, write_api);
}

