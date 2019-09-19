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
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_COUNT);
}

void loop() {
  int availableBytes = Serial.available();
  if (availableBytes > 0) {
    Serial.readBytes(packet, availableBytes);
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
    FastLED.show();
  }
}

void eraseAll() {
  color = CRGB(0, 0, 0);
  for (i = 0; i < LED_COUNT; i++) {
    leds[i] = color;
  }
}

void pushLED() {
  color = CRGB(0, 0, 0);
}

void overwriteLEDs() {

}
