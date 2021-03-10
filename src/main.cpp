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
  { 255,3,0,33,0,216,0,10,13,0,
  2,0,39,46,22,11,2,26,31,31,
  79,78,0,79,70,70,0,4,144,3,
  21,66,8,2,26,129,0,4,13,78,
  6,17,208,162,208,181,208,188,208,191,
  208,181,209,128,208,176,209,130,209,131,
  209,128,208,176,32,208,178,208,186,208,
  187,209,142,209,135,47,208,178,209,139,
  208,186,208,187,209,142,209,135,0,4,
  144,3,34,66,8,2,26,129,0,4,
  13,78,6,17,208,162,208,181,208,188,
  208,191,208,181,209,128,208,176,209,130,
  209,131,209,128,208,176,32,208,178,208,
  186,208,187,209,142,209,135,47,208,178,
  209,139,208,186,208,187,209,142,209,135,
  0,129,0,2,3,78,6,17,208,162,
  208,181,208,186,209,131,209,137,208,176,
  209,143,32,209,130,208,181,208,188,208,
  191,208,181,209,128,208,176,209,130,209,
  131,209,128,208,176,0,67,4,68,1,
  30,9,2,26,11,67,4,67,20,30,
  9,2,26,11,67,4,67,33,30,9,
  2,26,11 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

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
{   int setTempOn = RemoteXY.slider_on/100.0*30.0+10.0;
  int setTempOff = RemoteXY.slider_off/100.0*30.0+10.0;
   itoa (setTempOn, RemoteXY.text_on, 10);
 itoa (setTempOff, RemoteXY.text_off, 10);
  RemoteXY_Handler ();
  


// переменная для хранения температуры
  float temperature;
  // отправляем запрос на измерение температуры
  sensor.requestTemperatures();
  // считываем данные из регистра датчика
  temperature = sensor.getTempCByIndex(0);

  itoa (temperature, RemoteXY.text_1, 10);

  digitalWrite(PIN_SWITCH_1, (temperature>setTempOff)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_1, (temperature<setTempOn)?HIGH:LOW);

  
  // TODO you loop code
  // используйте структуру RemoteXY для передачи данных
  // не используйте функцию delay() 


}