// Подключаем библиотеку Adafruit NeoPixel.
#include "Adafruit_NeoPixel.h"
 
// Указываем, какое количество пикселей у нашей ленты.
#define LED_COUNT 20
 
// Указываем, к какому порту подключен вход ленты DIN.
#define LED_PIN 14 // 14 = A0
 
// Создаем переменную strip для управления нашей лентой.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int iStart = 0;
int iDirect = 1;
int delayMs = 100;
 
void setup()
{
  // Инициализируем ленту.
  strip.begin();

  // устанавливаем яркость (до 255)
  strip.setBrightness(150);

  randomSeed(analogRead(0));
}
 
void loop()
{
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
  
  // Включаем все светодиоды.
  for (int i = 0; i < LED_COUNT; i++)
  {
    if (i != iStart) {
      // все огни
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    } else {
      // бегущий огонь
      strip.setPixelColor(i, strip.Color(0, rand255(), rand255()));
    }
  }
  
  // Передаем цвета ленте.
  strip.show();
  
  // Ждем (мс).
  delay(delayMs);
}

int rand255() {
  return random(0, 255);
}
