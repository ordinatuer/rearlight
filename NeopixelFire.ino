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
bool colorDirect = true;
// задержка главного цикла (loop())
int delayMs = 30;
// момент последнего срабатывания программы
unsigned long previosMs = 0;

int color[] = {255, 0, 0};
int colorStep = 20;

 
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

    runningLigth();
  }
}

void runningLigth() {
  if (LED_COUNT == iStart) {
    iDirect = 0;
  }
  if (0 == iStart) {
    iDirect = 1;
  }

  bool oldColorDirect = colorDirect;
  
  if (255 <= color[0]) {
    colorDirect = false;
  }
  if (0 >= color[0]) {
    colorDirect = true;
  }

  if (colorDirect) {
    color[0] = color[0] + colorStep;
    color[1] = color[1] - colorStep;
  } else {
    color[0] = color[0] - colorStep;
    color[1] = color[1] + colorStep;
  }

  if ((oldColorDirect != colorDirect) && !colorDirect) {
    if (1 == iDirect) {
      iStart++;  
    } else {
      iStart--;  
    }
  }

  // Перебираем все светодиоды.
  for (int i = 0; i < LED_COUNT; i++)
  { 
    if (i == iStart || i == (LED_COUNT - iStart)) {
    //if (i == iStart) {
      // бегущий диод
      strip.setPixelColor(i, strip.Color(toColorInt(color[0]), toColorInt(color[1]), 0));
    } else {
      // остальные, фоновые диоды
      strip.setPixelColor(i, strip.Color(250, 0, 0));
    }
  }
  
  // Передаем цвета ленте.
  strip.show();
}

int toColorInt(int num) {
  if (255 < num) {
    num = 255;
  }

  if (num < 0) {
    num = 0;
  }

  return num;
}
