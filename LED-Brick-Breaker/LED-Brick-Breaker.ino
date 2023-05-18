// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        10 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 144 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

#define BUTTON_PIN 7

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {

  //checkInput(0);
  delay(100);

  pixels.clear(); // Set all pixel colors to 'off'
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=NUMPIXELS; i>0; i--) { // For each pixel...
    checkInput(i);
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.setPixelColor(checkInput(i), 0, 0, 0);

    pixels.show();   // Send the updated pixel colours to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    pixels.clear();
    
  }
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.setPixelColor(checkInput(i), 0, 0, 0);

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    pixels.clear();
    
  }
// Have the white dot bash the center & Light up center
  for(int i=0; i<NUMPIXELS/2; i++) { // For each pixel...
    checkInput(i);
    pixels.setPixelColor(71, pixels.Color(255, 255, 0));
    pixels.setPixelColor(72, pixels.Color(255, 255, 0));
    pixels.setPixelColor(73, pixels.Color(255, 255, 0));

    pixels.setPixelColor(i, pixels.Color(0, 0, 255));

    pixels.setPixelColor(checkInput(i), 0, 0, 0);

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    pixels.clear();
    
  }

  for(int i=NUMPIXELS/2; i>0; i--) { // For each pixel...

    //pixels.setPixelColor(71, pixels.Color(255, 255, 0));
    pixels.setPixelColor(72, pixels.Color(255, 255, 0));
    pixels.setPixelColor(73, pixels.Color(255, 255, 0));

    // Eat the pixel and add 1 to chain
    pixels.setPixelColor(i-1, pixels.Color(255, 255, 0, 0));

    pixels.setPixelColor(i, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(checkInput(i), 0, 0, 0);

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    pixels.clear();
    
  }
  // Left side dot colour change
  for(int i=144; i>NUMPIXELS/2; i--) { // For each pixel...

    //pixels.setPixelColor(71, pixels.Color(255, 255, 0));
    pixels.setPixelColor(72, pixels.Color(255, 255, 0));
    pixels.setPixelColor(73, pixels.Color(255, 255, 0));

    // Eat the pixel and add 1 to chain
    pixels.setPixelColor(i-1, pixels.Color(255, 255, 0, 0));

    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.setPixelColor(checkInput(i), 0, 0, 0);

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    pixels.clear();
    
  }

  for(int i=NUMPIXELS/2; i<NUMPIXELS; i++) { // For each pixel...

    //pixels.setPixelColor(71, pixels.Color(255, 255, 0));
    pixels.setPixelColor(72, pixels.Color(255, 255, 0));
    //pixels.setPixelColor(73, pixels.Color(255, 255, 0));

// SHow that the light has eaten the barrier
    pixels.setPixelColor(i-2, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(i-1, pixels.Color(0, 0, 0, 255));

    pixels.setPixelColor(i, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(checkInput(i), 0, 0, 0);

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    pixels.clear();
    
  }

  // Clear the last pixel
    for(int i=144; i>NUMPIXELS/2; i--) { // For each pixel...

    //pixels.setPixelColor(71, pixels.Color(255, 255, 0));
    pixels.setPixelColor(72, pixels.Color(255, 255, 0));
    //pixels.setPixelColor(73, pixels.Color(255, 255, 0));

    pixels.setPixelColor(i-2, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(i-1, pixels.Color(0, 0, 0, 255));

    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.setPixelColor(checkInput(i), 0, 0, 0);

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    pixels.clear();
    
  }

  for(int i=NUMPIXELS/2; i<NUMPIXELS; i++) { // For each pixel from the middle...

    pixels.setPixelColor(i-3, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(i-2, pixels.Color(0, 0, 0, 255));
    pixels.setPixelColor(i-1, pixels.Color(0, 0, 0, 255));  // Show the trail of eaten blobs
    pixels.setPixelColor(i, pixels.Color(0, 0, 0, 255));

    pixels.setPixelColor(checkInput(i), 0, 0, 0);

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    pixels.clear();
    
  }

}

int checkInput(int idx) {
    Serial.println(digitalRead(BUTTON_PIN));
     
    byte buttonState, lastButtonState = HIGH; //Unpressed
    byte buttonState2, lastButtonState2 = HIGH;
    buttonState = digitalRead(BUTTON_PIN);

    if(digitalRead(BUTTON_PIN) == 0){
      Serial.println("Button Clicked");
    }

    if(buttonState != lastButtonState){
      Serial.println("Button Clicked");
      for (int i = NUMPIXELS; i < NUMPIXELS; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 255, 0));
        return 255;
      }
    }
}
