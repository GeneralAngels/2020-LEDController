#include <FastLED.h>

#define LED_PIN 3
#define LED_COUNT 38
#define LOOP_DELAY 50 //50Hz

CRGB leds[LED_COUNT];

byte packet[256];
int availableBytes;

long i;
CRGB color;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, LED_COUNT);
}

void loop() {
  int availableBytes = Serial.available();
  if (availableBytes > 0) {
    Serial.readBytes(packet, availableBytes);
    Serial.println("Thing");
    switch (packet[0]) {
      case 0x00:
        eraseAll();
        break;
      case 0x01:
        pushLED();
        break;
      case 0x02:
        overwriteLEDs();
        break;
      case 0x03:
        break;
    }
    pushLED();
  }
  FastLED.show();
}

void eraseAll() {
  color = CRGB(0, 0, 0);
  for (i = 0; i < LED_COUNT; i++) {
    leds[i] = color;
  }
}

void pushLED() {
  for (i = LED_COUNT - 1; i > 0; i--) {
    leds[i] = leds[i - 1];
  }
  color = CRGB(packet[1], packet[2], packet[3]);
  leds[i] = color;
}

void overwriteLEDs() {

}
