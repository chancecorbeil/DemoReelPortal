#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif



// These are the same for every strip
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define FRAMES_PER_SECOND 120
#define ANALOG_PIN_FOR_ENTROPY 0

// These are different per strip
#define DATA_PIN_A 2
#define NUM_LEDS_A 43
CRGB ledsA[NUM_LEDS_A];
int TIMER_FOR_STRIP_A = 500;
uint8_t CurrentPatternA = 0;
uint8_t HueA = 0;

#define DATA_PIN_B 3
#define NUM_LEDS_B 61
CRGB ledsB[NUM_LEDS_B];
int TIMER_FOR_STRIP_B = 500;
uint8_t CurrentPatternB = 0;
uint8_t HueB = 0;

#define DATA_PIN_C 4
#define NUM_LEDS_C 82
CRGB ledsC[NUM_LEDS_C];
int TIMER_FOR_STRIP_C = 500;
uint8_t CurrentPatternC = 0;
uint8_t HueC = 0;

#define DATA_PIN_D 5
#define NUM_LEDS_D 104
CRGB ledsD[NUM_LEDS_D];
int TIMER_FOR_STRIP_D = 500;
uint8_t CurrentPatternD = 0;
uint8_t HueD = 0;

enum LED_STRIPS { a, b, c, d };


// CHANCE - look at the switch statement here when you add a new animation. It should look like this `rainbow()` function.
// Complete with the same signature.
void rainbow (LED_STRIPS strip) {
  // FastLED's built-in rainbow generator
  switch (strip) {
    case LED_STRIPS::a:
      fill_rainbow (ledsA, NUM_LEDS_A, HueA, 7);
      break;

    case LED_STRIPS::b:
      fill_rainbow (ledsB, NUM_LEDS_B, HueB, 7);
      break;

    case LED_STRIPS::c:
      fill_rainbow (ledsC, NUM_LEDS_C, HueC, 7);
      break;

    case LED_STRIPS::d:
      fill_rainbow (ledsD, NUM_LEDS_D, HueD, 7);
      break; 
  }
}

void confetti (LED_STRIPS strip) {
  // random colored speckles that blink in and fade smoothly
  int pos;
  switch (strip) {
    case LED_STRIPS::a:
      pos = random16(NUM_LEDS_A);
      fadeToBlackBy (ledsA, NUM_LEDS_A, 10);
      ledsA[pos] += CHSV (HueA + random8(64), 200, 255);
      break;

    case LED_STRIPS::b:
      pos = random16(NUM_LEDS_B);
      fadeToBlackBy (ledsB, NUM_LEDS_B, 10);
      ledsB[pos] += CHSV (HueB + random8(64), 200, 255);
      break;

    case LED_STRIPS::c:
      pos = random16(NUM_LEDS_C);
      fadeToBlackBy (ledsC, NUM_LEDS_C, 10);
      ledsC[pos] += CHSV (HueC + random8(64), 200, 255);
      break;

    case LED_STRIPS::d:
      pos = random16(NUM_LEDS_D);
      fadeToBlackBy (ledsD, NUM_LEDS_D, 10);
      ledsD[pos] += CHSV (HueD + random8(64), 200, 255);
      break;
  }
}

void sinelon (LED_STRIPS strip) {
  // a colored dot sweeping back and forth, with fading trails
  int pos;

  switch (strip) {
    case LED_STRIPS::a:
      pos = beatsin16( 13, 0, NUM_LEDS_A-1 );
      fadeToBlackBy (ledsA, NUM_LEDS_A, 20);
      ledsA[pos] += CHSV (HueA, 255, 192);
      break;

    case LED_STRIPS::b:
      pos = beatsin16( 13, 0, NUM_LEDS_B-1 );
      fadeToBlackBy (ledsB, NUM_LEDS_B, 20);
      ledsB[pos] += CHSV (HueB, 255, 192);
      break;

    case LED_STRIPS::c:
      pos = beatsin16( 13, 0, NUM_LEDS_C-1 );
      fadeToBlackBy (ledsC, NUM_LEDS_C, 20);
      ledsC[pos] += CHSV (HueC, 255, 192);
      break;

    case LED_STRIPS::d:
      pos = beatsin16( 13, 0, NUM_LEDS_D-1 );
      fadeToBlackBy (ledsD, NUM_LEDS_D, 20);
      ledsD[pos] += CHSV (HueD, 255, 192);
      break; 
  }
}

void bpm (LED_STRIPS strip) {
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);

  switch (strip) {
    case LED_STRIPS::a:
      for( int i = 0; i < NUM_LEDS_A; i++) {
        ledsA[i] = ColorFromPalette(palette, HueA+(i*2), beat-HueA+(i*10));
      }
      break;

    case LED_STRIPS::b:
      for( int i = 0; i < NUM_LEDS_B; i++) {
        ledsB[i] = ColorFromPalette(palette, HueB+(i*2), beat-HueB+(i*10));
      }
      break;

    case LED_STRIPS::c:
      for( int i = 0; i < NUM_LEDS_C; i++) {
        ledsC[i] = ColorFromPalette(palette, HueC+(i*2), beat-HueC+(i*10));
      }
      break;

    case LED_STRIPS::d:
      for( int i = 0; i < NUM_LEDS_D; i++) {
        ledsD[i] = ColorFromPalette(palette, HueD+(i*2), beat-HueD+(i*10));
      }
      break; 
  }
}

void juggle (LED_STRIPS strip) {
  // ten colored dots, weaving in and out of sync with each other
  byte dothue = 0;
  switch (strip) {
    case LED_STRIPS::a:
      fadeToBlackBy(ledsA, NUM_LEDS_A, 20);
      for (int i = 0; i < 10; i++) {
        ledsA[beatsin16( i+7, 0, NUM_LEDS_A-1 )] |= CHSV(dothue, 200, 255);
        dothue += 32;
      }
      break;

    case LED_STRIPS::b:
      fadeToBlackBy(ledsB, NUM_LEDS_B, 20);
      for (int i = 0; i < 10; i++) {
        ledsB[beatsin16( i+7, 0, NUM_LEDS_B-1 )] |= CHSV(dothue, 200, 255);
        dothue += 32;
      }
      break;

    case LED_STRIPS::c:
      fadeToBlackBy(ledsC, NUM_LEDS_C, 20);
      for (int i = 0; i < 10; i++) {
        ledsC[beatsin16( i+7, 0, NUM_LEDS_C-1 )] |= CHSV(dothue, 200, 255);
        dothue += 32;
      }
      break;

    case LED_STRIPS::d:
      fadeToBlackBy(ledsD, NUM_LEDS_D, 20);
      for (int i = 0; i < 10; i++) {
        ledsD[beatsin16( i+7, 0, NUM_LEDS_D-1 )] |= CHSV(dothue, 200, 255);
        dothue += 32;
      }
      break; 
  }
}

int getNewTimer () {
  int minTime = 100 * 30;
  int maxTime = 100 * 60;
  return random(minTime, maxTime);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])(LED_STRIPS strip);
SimplePatternList Patterns = { rainbow, confetti, sinelon, juggle }; // CHANCE - add your function here.
# define NUMBER_OF_PATTERNS 4 // CHANCE - change this number



void setup () {
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(ANALOG_PIN_FOR_ENTROPY));

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN_A,COLOR_ORDER>(ledsA, NUM_LEDS_A);
  FastLED.addLeds<LED_TYPE,DATA_PIN_B,COLOR_ORDER>(ledsB, NUM_LEDS_B);
  FastLED.addLeds<LED_TYPE,DATA_PIN_C,COLOR_ORDER>(ledsC, NUM_LEDS_C);
  FastLED.addLeds<LED_TYPE,DATA_PIN_D,COLOR_ORDER>(ledsD, NUM_LEDS_D);

  // set our framerate. This will cause "waits" to happen if we run `show()` before
  // we've reached time for the next frame.
  // FastLED.setMaxRefreshRate(1000/FRAMES_PER_SECOND);
}

  
void loop () {
  nextFrameForStrip(LED_STRIPS::a);
  nextFrameForStrip(LED_STRIPS::b);
  nextFrameForStrip(LED_STRIPS::c);
  nextFrameForStrip(LED_STRIPS::d);

  FastLED.show();  
}

void nextFrameForStrip (LED_STRIPS strip) {
  switch (strip) {
    case LED_STRIPS::a:
      Patterns[CurrentPatternA](strip);
      EVERY_N_MILLISECONDS( 20 ) { HueA++; }
      if (TIMER_FOR_STRIP_A == 0) {
        nextPattern(strip);
      }
      TIMER_FOR_STRIP_A--;
      break;

    case LED_STRIPS::b:
      Patterns[CurrentPatternB](strip);
      EVERY_N_MILLISECONDS( 20 ) { HueB++; }
      if (TIMER_FOR_STRIP_B == 0) {
        nextPattern(strip);
      }
      TIMER_FOR_STRIP_B--;
      break;

    case LED_STRIPS::c:
      Patterns[CurrentPatternC](strip);
      EVERY_N_MILLISECONDS( 20 ) { HueC++; }
      if (TIMER_FOR_STRIP_C == 0) {
        nextPattern(strip);
      }
      TIMER_FOR_STRIP_C--;
      break;

    case LED_STRIPS::d:
      Patterns[CurrentPatternD](strip);
      EVERY_N_MILLISECONDS( 20 ) { HueD++; }
      if (TIMER_FOR_STRIP_D == 0) {
        nextPattern(strip);
      }
      TIMER_FOR_STRIP_D--;
      break;
  }
}

void nextPattern (LED_STRIPS strip) {
  // add one to the current pattern number, and wrap around at the end
  switch (strip) {
    case LED_STRIPS::a:
      CurrentPatternA = random(0, NUMBER_OF_PATTERNS-1);
      TIMER_FOR_STRIP_A = getNewTimer();
      // TODO - set the timer to SOMETHING.
      break;
    case LED_STRIPS::b:
      CurrentPatternB = random(0, NUMBER_OF_PATTERNS-1);
      TIMER_FOR_STRIP_B = getNewTimer();
      break;
    case LED_STRIPS::c:
      CurrentPatternC = random(0, NUMBER_OF_PATTERNS-1);
      TIMER_FOR_STRIP_C = getNewTimer();
      break;
    case LED_STRIPS::d:
      CurrentPatternD = random(0, NUMBER_OF_PATTERNS-1);
      TIMER_FOR_STRIP_D = getNewTimer();
      break;
  }
}
