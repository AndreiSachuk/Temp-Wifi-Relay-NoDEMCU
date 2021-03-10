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

// настройки соединения 
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"
#define ONE_WIRE_BUS 36
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensor(&oneWire);


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,1,0,0,0,11,0,10,13,0,
  4,128,26,25,40,8,2,26 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {
  int8_t slider_1; // =0..100 slider position 
    // input variables
  uint8_t switch_1; // =1 если переключатель включен и =0 если отключен 
  int8_t slider_on; // =0..100 положение слайдера 
  int8_t slider_off; // =0..100 положение слайдера 

    // output variables
  char text_1[11];  // =строка UTF8 оканчивающаяся нулем 
  char text_on[11];  // =строка UTF8 оканчивающаяся нулем 
  char text_off[11];  // =строка UTF8 оканчивающаяся нулем 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 22


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

void loop() 
{   
  RemoteXY_Handler ();


  // TODO you loop code
  // используйте структуру RemoteXY для передачи данных
  // не используйте функцию delay() 
  
  if(timer < millis()){
    timer = millis() + 200;
    Serial.printf("%6d>", millis());
    Serial.println(RemoteXY.to_string());
    RemoteXY.slider_on = (millis() / 100) % 100;

    float temperature;
    sensor.requestTemperatures();
    temperature = sensor.getTempCByIndex(0);

    int setTempOn = RemoteXY.slider_on/100.0*30.0+10.0;
    int setTempOff = RemoteXY.slider_off/100.0*30.0+10.0;
    
    itoa (setTempOn, RemoteXY.text_on, 10);
    itoa (setTempOff, RemoteXY.text_off, 10);
    itoa (temperature, RemoteXY.text_1, 10);

    digitalWrite(PIN_SWITCH_1, (temperature>setTempOff)?LOW:HIGH);
    digitalWrite(PIN_SWITCH_1, (temperature<setTempOn)?HIGH:LOW);
  }
  
}