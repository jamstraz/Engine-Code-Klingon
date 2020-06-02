//#include <Adafruit_NeoPixel.h>
#include "FastLED.h"
#define PIN        9 // LED pin
#define BTN        A3 // Button Pin
#define NUM_LEDS  7
CRGB leds[NUM_LEDS];
//Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);

uint8_t state = 0;

uint8_t currentR = 0;
uint8_t currentG = 255;
uint8_t currentB = 255;

uint8_t setR = 0;
uint8_t setG = 255;
uint8_t setB = 255;

uint32_t frametime = 0;
uint8_t fps = 30;

void setup() {
  Serial.begin(9600);
  pinMode(BTN, INPUT_PULLUP); // Button as input with pullup
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  //FastLED.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  FastLED.clear();

  // apply boot up colors
  /*pixels.setPixelColor(0, pixels.Color(0,255,255));
    pixels.setPixelColor(1, pixels.Color(0,255,255));*/
}

void loop() {
  if (digitalRead(BTN) == LOW) { // button is pressed
    Serial.println(digitalRead(BTN));
    state++;
    Serial.println(state);
    if (state > 1) { // limit to the two states (0 | 1) we have for now
      state = 0;
    }
    while (digitalRead(BTN) == LOW) {
      delay(1);  // wait until button is released to avoid accidental double pressing
    }
  }

  // set color appropriate to state
  if (state == 0) {
    setR = 0;
    setG = 255;
    setB = 255;
  } else if (state == 1) {
    setR = 255;
    setG = 0;
    setB = 0;
  }

  if (millis() - frametime >= 100 / fps) { // do something <fps> times per second
    frametime = millis();

    // calculate changes to fade to the set color from the current color
    if (setR > currentR) {
      currentR++;
    } else if (setR < currentR) {
      currentR--;
    }
    if (setG > currentG) {
      currentG++;
    } else if (setG < currentG) {
      currentG--;
    }
    if (setB > currentB) {
      currentB++;
    } else if (setB < currentB) {
      currentB--;
    }

    // display current color
    leds[0] = (currentR, currentG, currentB);
    /*pixels.setPixelColor(3, pixels.Color(currentR,currentG,currentB));
      pixels.setPixelColor(4, pixels.Color(currentR,currentG,currentB));    /*pixels.setPixelColor(1, pixels.Color(0,0,0));
      pixels.setPixelColor(2, pixels.Color(0,0,0));
      pixels.setPixelColor(3, pixels.Color(0,0,0));
      pixels.setPixelColor(4, pixels.Color(0,0,0));
      pixels.setPixelColor(5, pixels.Color(0,0,0));
      FastLED.setPixelColor(5, Color(currentR,currentG,currentB));*/
    FastLED.show();
  }
}
