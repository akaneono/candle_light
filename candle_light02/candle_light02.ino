#include <avr/pgmspace.h>

const int PROGMEM gamma8[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
  1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,
  2,3,3,3,3,3,3,3,4,4,4,4,4,5,5,5,
  5,6,6,6,6,7,7,7,7,8,8,8,9,9,9,10,
  10,10,11,11,11,12,12,13,13,13,14,14,15,15,16,16,
  17,17,18,18,19,19,20,20,21,21,22,22,23,24,24,25,
  25,26,27,27,28,29,29,30,31,32,32,33,34,35,35,36,
  37,38,39,39,40,41,42,43,44,45,46,47,48,49,50,50,
  51,52,54,55,56,57,58,59,60,61,62,63,64,66,67,68,
  69,70,72,73,74,75,77,78,79,81,82,83,85,86,87,89,
  90,92,93,95,96,98,99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
};

const int led_pin_1 = 26;
const int led_pin_2 = 27;

float value = 0.7;
float target_value = 0.7;

const int max_value = 255;
const int dimming_range = 90;

void setup() {
  pinMode(led_pin_1, OUTPUT);
  pinMode(led_pin_2, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  if (random(0, 100) < 10) { 
    target_value = random(25, 100) / 100.0;  // 扩大波动范围
  }

  value += (target_value - value) * 0.06;  // 提高主亮度变化速率

  float flicker = (random(-35, 46)) / 255.0;  // 放大flicker幅度
  float combined_value = value + flicker;

  if (combined_value < 0.0) combined_value = 0.0;
  if (combined_value > 1.0) combined_value = 1.0;

  // 暂时去掉二次曲线公式以观察效果
  // 如果想再加回来可恢复这一段
  /*
  if (combined_value < 0.5) {
    combined_value = combined_value + 2.0 * combined_value * combined_value;
  } else {
    combined_value = combined_value - 2.0 * (1.0 - combined_value) * (1.0 - combined_value);
  }
  */

  int value_1 = max_value - dimming_range + (combined_value * dimming_range);
  int value_2 = max_value - (combined_value * dimming_range);

  analogWrite(led_pin_1, pgm_read_byte(&(gamma8[value_1])));
  analogWrite(led_pin_2, pgm_read_byte(&(gamma8[value_2])));

  delay(80);  // 刷新慢一点，更自然
}
