/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.3 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.5.1 or later version;
     - for iOS 1.4.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <RemoteXY.h>
#include <DallasTemperature.h>
#include <string>
#include <bits/basic_string.h>

// настройки соединения 
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"
#define ONE_WIRE_BUS 23   //D23
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensor(&oneWire);


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,22,0,22,0,5,1,10,13,0,
  129,0,2,18,73,6,17,208,162,208,
  181,208,188,208,191,208,181,209,128,208,
  176,209,130,209,131,209,128,208,176,32,
  208,178,208,186,208,187,209,142,209,135,
  208,181,208,189,208,184,209,143,0,67,
  4,67,1,20,9,2,26,11,7,36,
  75,18,16,5,2,26,2,11,129,0,
  2,29,73,6,17,208,162,208,181,208,
  188,208,191,208,181,209,128,208,176,209,
  130,209,131,209,128,208,176,32,208,178,
  209,139,208,187,209,142,209,135,208,181,
  208,189,208,184,209,143,0,7,36,77,
  30,15,5,2,26,2,11,129,0,2,
  48,78,6,17,208,162,208,181,208,186,
  209,131,209,137,208,181,208,181,32,209,
  129,208,190,209,129,209,130,208,190,209,
  143,208,189,208,184,208,181,0,67,4,
  68,46,30,9,2,26,11,129,0,2,
  3,78,6,17,208,162,208,181,208,186,
  209,131,209,137,208,176,209,143,32,209,
  130,208,181,208,188,208,191,208,181,209,
  128,208,176,209,130,209,131,209,128,208,
  176,0,129,0,88,3,7,6,17,194,
  176,208,161,0,129,0,91,18,7,6,
  17,194,176,208,161,0,129,0,92,30,
  7,6,17,194,176,208,161,0 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  char edit_1[11];  // =строка UTF8 оканчивающаяся нулем  
  char edit_2[11];  // =строка UTF8 оканчивающаяся нулем  

    // output variables
  char text_1[11];  // =строка UTF8 оканчивающаяся нулем 
  char OUT[11];  // =строка UTF8 оканчивающаяся нулем 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 5   //D5


void setup() 
{

  
  RemoteXY_Init (); 
  
  pinMode (PIN_SWITCH_1, OUTPUT);
  

    // начинаем работу с датчиком
  sensor.begin();
  // устанавливаем разрешение датчика от 9 до 12 бит
  sensor.setResolution(12);
  // TODO you setup code
  
  
}
int timer = 0;


void loop() 
{   
  int value_On = atoi (RemoteXY.edit_1);
  int value_Off = atoi (RemoteXY.edit_2);
  RemoteXY_Handler ();
  
  // переменная для хранения температуры
  float temperature;
  
  // отправляем запрос на измерение температуры
  sensor.requestTemperatures();
  
  // считываем данные из регистра датчика
  temperature = sensor.getTempCByIndex(0);

  itoa (temperature, RemoteXY.text_1, 10);

  if (temperature>value_Off)
  {
    digitalWrite(PIN_SWITCH_1,LOW);
  }
  
  if (temperature<value_On)
  {
    digitalWrite(PIN_SWITCH_1,HIGH);
  }


  if (PIN_SWITCH_1==LOW) strcpy (RemoteXY.OUT, "OFF"); 
    else  strcpy (RemoteXY.OUT, "ON"); 

}