// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include <FastLED.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

int sensor_value;

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 30 // Popular NeoPixel ring size
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.

CRGB leds[NUMPIXELS];

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUMPIXELS);
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  
#endif
  // END of Trinket-specific code.
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  Serial.println("Initialized");
}

void loop() {
  int sensor_value;
  sensor_value = analogRead(A0);
 

  int mapping_value = map(sensor_value,0,300,0,4);
  mapping_value = constrain(mapping_value,0,4);

   
  // Convert envelope value into a message
 
  Serial.print("Status: ");
  Serial.println(sensor_value);

 
  FastLED.clear();
  switch (mapping_value){
  
  case 0:  
  break;
  
  case 1:  
  fill_solid(leds + 0,  3, CRGB::Green); 
  break;

  case 2:  
  fill_solid(leds + 0,  6, CRGB::Purple);
  break;

  case 3: 
  fill_solid(leds + 0,  9, CRGB::Yellow);
  break;
  
  case 4: 
  fill_solid(leds + 0,  13, CRGB::Blue);
  break;

  }
  FastLED.show(); 
}