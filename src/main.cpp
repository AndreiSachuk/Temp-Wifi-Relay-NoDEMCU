#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(14);// D5 вход датчика 18b20
DallasTemperature t(&oneWire);
MDNSResponder mdns;
const char* ssid = "Andi";
const char* password = "11111118";
ESP8266WebServer server(81);
 
int temper,reg_t=20,gis=1;
String ind;

void web(){
String webPage = "<!DOCTYPE HTML><html>";
       webPage += "<meta charset='utf-8'><meta name='viewport' content='width=480, user-scalable=no' />";
       webPage += "<style>table {background-color:#F5F5F5;border-radius: 5px;}</style>";
       webPage += "<TABLE align='center' width='450' BORDER='1' cellspacing='0' cellpadding='5'><td colspan='3' align='center'>";
       webPage += "<h1>Терморегулятор 0...125 &#176;C</td><tr></h1>";
       webPage += "<meta http-equiv='Refresh' content='10; URL=/obn' />"; // автоматическое обновление страницы каждые 10 секунд
       webPage += "<td align='center'>Температура</td><td align='center'><a href=\"obn\"><button>Обновить</button></a></td><td align='center'>";
       webPage += temper;
       webPage += "<tr><td align='center'>Регулировка температуры</td><td align='center'><a href=\"reg+\"><button>+1&nbsp;&nbsp;</button>";
       webPage += "</a><a href=\"reg-\"><button>-1&nbsp;&nbsp;</button></a><br><a href=\"reg+10\"><button>+10</button></a>";
       webPage += "<a href=\"reg-10\"><button>-10</button></a></td><td align='center'>";
       webPage += reg_t;
       webPage += " &#176;C</td>";
       webPage += "<tr><td colspan='3' align='center'>Нагрев: ";
       webPage += ind;
       webPage += "</td></html>"; 
 
  server.send(200, "text/html", webPage);delay(300);
}
 
void setup(void){
 
  pinMode(2, OUTPUT);// D4 выход управления нагрузкой
  t.begin();t.setResolution(10);//10 бит 
 
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  while (WiFi.status() != WL_CONNECTED) {delay(500);Serial.print(".");}
  Serial.println("");
  Serial.print("Connected to ");  
  Serial.println(ssid);
  Serial.print("IP address: ");  
  Serial.println(WiFi.localIP());
 
  if (mdns.begin("esp8266", WiFi.localIP())) {Serial.println("MDNS responder started");}
 
  server.on("/", [](){web();});
  server.on("/obn", [](){web();});
  server.on("/reg+", [](){reg_t++;web();});
  server.on("/reg-", [](){reg_t--;web();});
  server.on("/reg+10", [](){reg_t=reg_t+10;web();});
  server.on("/reg-10", [](){reg_t=reg_t-10;web();});
 
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
  t.requestTemperatures();temper=t.getTempCByIndex(0);
   if(reg_t<=0){reg_t=0;}if(reg_t>=125){reg_t=125;}
   if(reg_t >= temper + gis){digitalWrite(2,HIGH);ind=" ВКЛ";}
   if(reg_t <= temper - gis){digitalWrite(2,LOW);ind=" ВЫКЛ";}
  Serial.println(reg_t);
}
 

