// Подключаем библиотеку Adafruit NeoPixel.
#include "Adafruit_NeoPixel.h"
 
// Указываем, какое количество пикселей у нашей ленты.
#define LED_COUNT 10
 
// Указываем, к какому порту подключен вход ленты DIN.
// 21 = A7 для Nano
#define LED_PIN 19 // 19 = A5
 
// Создаем переменную strip для управления нашей лентой.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// начало пробега по диодам
int iStart = 0;
// направление пробега
int iDirect = 1;
// задержка главного цикла (loop())
int delayMs = 20;
// момент последнего срабатывания программы
unsigned long previosMs = 0;

 
void setup()
{
  // Инициализируем ленту.
  strip.begin();

  // устанавливаем яркость (до 255)
  strip.setBrightness(200);

  randomSeed(analogRead(0));
}
 
void loop()
{
  // время исполнения текущей итерации loop()
  unsigned long currentMs = millis();

  // вместо delay() 
  if (delayMs < (currentMs - previosMs)) {
    previosMs = currentMs;

    rgbSwitch();
  }
}

void rgbSwitch() {
    if (LED_COUNT == iStart) {
    iDirect = 0;
  }
  if (0 == iStart) {
    iDirect = 1;
  }
  
  if (1 == iDirect) {
    iStart++;  
  } else {
    iStart--;  
  }
  
  // Перебираем все светодиоды.
  for (int i = 0; i < LED_COUNT; i++)
  { 
    //if (i == iStart || i == (LED_COUNT - iStart)) {
    if (i == iStart) {
      // бегущий диод
      strip.setPixelColor(i, strip.Color(250, 0, 100));
    } else {
      // остальные, фоновые диоды
      strip.setPixelColor(i, strip.Color(250, 0, 0));
    }
  }
  
  // Передаем цвета ленте.
  strip.show();
  
  // Ждем (мс).
  //delay(delayMs);
}
