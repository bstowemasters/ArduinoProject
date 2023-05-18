// Libraries
#include <Adafruit_NeoPixel.h>

#define SPEAKER 12
#define LLED_PIN A4
#define RLED_PIN A3
#define NUM_LEDS 144


// Global Variables
int delayVal = 300;
int playerPosition = 0;

uint32_t color; // Used to check colour of pixels.

// Levels & enemy Positions

// Level 1

int l1Max = 71;
int l1Min = 66;
int LLhit = l1Max;
int Lhit = l1Max;
int Rhit = l1Max;
int RRhit = l1Max;

int enemyPosLL[6] = {1, 1, 1, 1, 1, 1};
int enemyPosL[6] = {1, 1, 1, 1, 1, 1};
int enemyPosR[6] = {1, 1, 1, 1, 1, 1};
int enemyPosRR[6] = {1, 1, 1, 1, 1, 1};

// Define button variables
const int LEFT_BUTTON = 13;
const int RIGHT_BUTTON = A5;
const int SHOOT = 11;

// Objects
Adafruit_NeoPixel lStrip = Adafruit_NeoPixel(NUM_LEDS, LLED_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel rStrip = Adafruit_NeoPixel(NUM_LEDS, RLED_PIN, NEO_GRBW + NEO_KHZ800);



void setup() {

  pinMode(SPEAKER, OUTPUT);

   // Initialize LED strip
  lStrip.begin();
  rStrip.begin();

  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(SHOOT, INPUT_PULLUP);

  loadLevelOne();
  Serial.begin(9600);
}

void loop() {
/*
  tone(SPEAKER, 130.8);
  delay(delayVal);
  tone(SPEAKER, 155.6);
  delay(delayVal);
  tone(SPEAKER, 174.6);
  delay(delayVal);
  tone(SPEAKER, 207.7);
  delay(delayVal);
  tone(SPEAKER, 233.1);
  delay(delayVal);
  tone(SPEAKER, 261.6);
  delay(delayVal);
  tone(SPEAKER, 233.1);
  delay(delayVal);
  tone(SPEAKER, 207.7);
  delay(delayVal);
  tone(SPEAKER, 174.6);
  delay(delayVal);
  tone(SPEAKER, 155.6);
  delay(delayVal);
  tone(SPEAKER, 130.8);
  delay(delayVal);

  noTone(SPEAKER);
  //delayVal(delayVal);
*/

  playerPos();

  // Show changes on LED strips
  lStrip.show();
  rStrip.show();


}

void loadLevelOne(){
  // setPixel(1, 74, 255, 0, 0); // LL
  // setPixel(2, 74, 255, 0, 0); // L
  // setPixel(3, 74, 255, 0, 0); // R
  // setPixel(4, 74, 255, 0, 0); // RR
  

  // Write out enemies for Level 1

  // LL strip
  for (int i = 0; i < sizeof(enemyPosLL) / sizeof(enemyPosLL[0]); i++){
    if (enemyPosLL[i] == 1){
      setPixel(1, l1Max-i, 100, 0, 0);
    } else {
      setPixel(1, l1Max-i, 0, 0, 0);
    }
  }

  // L strip
  for (int i = 0; i < sizeof(enemyPosL) / sizeof(enemyPosL[0]); i++){
    if (enemyPosL[i] == 1){
      setPixel(2, l1Max-i, 100, 0, 0);
    } else {
      setPixel(2, l1Max-i, 0, 0, 0);
    }
  }

  // R strip
  for (int i = 0; i < sizeof(enemyPosR) / sizeof(enemyPosR[0]); i++){
    if (enemyPosR[i] == 1){
      setPixel(3, l1Max-i, 100, 0, 0);
    } else {
      setPixel(3, l1Max-i, 0, 0, 0);
    }
  }

  // RR strip
  for (int i = 0; i < sizeof(enemyPosRR) / sizeof(enemyPosRR[0]); i++){
    if (enemyPosRR[i] == 1){
      setPixel(4, l1Max-i, 100, 0, 0);
    } else {
      setPixel(4, l1Max-i, 0, 0, 0);
    }
  }


}

// Function to move player
void playerPos(){
  delay(200);
  // Check for button presses
  if (checkBtn() == 'L' && playerPosition != 0) {
    playerPosition--;
    Serial.println("GOING LEFT");
  } else if (checkBtn() == 'R' && playerPosition != 3) {
    playerPosition++;
    Serial.println("GOING RIGHT");
  }

  switch(playerPosition){
    case 0:
      clearOldPos();
      setPixel(1, 1, 0, 0, 255);
      break;
    case 1:
      clearOldPos();
      setPixel(2, 1, 0, 0, 255);
      break;
    case 2:
      clearOldPos();
      setPixel(3, 1, 0, 0, 255);
      break;
    case 3:
      clearOldPos();
      setPixel(4, 1, 0, 0, 255);
      break;
  }

}

void clearOldPos(){
      setPixel(1, 1, 0, 0, 0);  // LL
      setPixel(2, 1, 0, 0, 0);  // L
      setPixel(3, 1, 0, 0, 0);  // R
      setPixel(4, 1, 0, 0, 0);  // RR
}

void shoot(){

  playShootSound();

  switch(playerPosition){
    case 0:
      for(int i = 0; i < lStrip.numPixels()/2; i++){

        color = checkPixelColor(1, i+1);
        if (color == 0x00640000){


          enemyPosLL[LLhit-l1Min] = 0;

          // Debug Code
          // Serial.println("Found Color red");
          // Serial.print("Removing idx at: ");
          // Serial.print(hit);
          // Serial.print(" - ");
          // Serial.print(l1Min);
          // Serial.print(" = ");
          // Serial.print(hit-l1Min);
          // Serial.println();
          if(LLhit != l1Min){
            LLhit--;
          }
          break;

              
        } else {
          shootAnimation(1, i);
        }
      }
      
      // Update LED Strip
      loadLevelOne();
      lStrip.show();

      break;
    case 1:
      for(int i = 0; i < lStrip.numPixels()/2; i++){
        color = checkPixelColor(2, i+1);
        if (color == 0x00640000){

          enemyPosL[Lhit-l1Min] = 0;

          if(Lhit != l1Min){
            Lhit--;
          }
          break;

        } else {
          shootAnimation(2, i);
        }
      }
      
      // Update LED Strip
      loadLevelOne();
      lStrip.show();
      break;
    case 2:
      for(int i = 0; i < rStrip.numPixels()/2; i++){
        color = checkPixelColor(3, i+1);
        if (color == 0x00640000){

          enemyPosR[Rhit-l1Min] = 0;

          if(Rhit != l1Min){
            Rhit--;
          }
          break;
        } else {
          shootAnimation(3, i);
        }
      }
      
      // Update LED Strip
      loadLevelOne();
      rStrip.show();
      break;
    case 3:
      for(int i = 0; i < rStrip.numPixels()/2; i++){
        color = checkPixelColor(4, i+1);
        if (color == 0x00640000){

          enemyPosRR[RRhit-l1Min] = 0;

          if(RRhit != l1Min){
            RRhit--;
          }
          break;
        } else {
          shootAnimation(4, i);
        }
      }
      
      // Update LED Strip
      loadLevelOne();
      rStrip.show();
      break;
  }

}

void killEnemy(){
  
}

void playShootSound(){
  tone(SPEAKER, 440);
  delay(10);
  noTone(SPEAKER);
  tone(SPEAKER, 550);
  delay(10);
  tone(SPEAKER, 587);
  delay(10);
  tone(SPEAKER, 660);
  delay(10);
  noTone(SPEAKER);
}

void shootAnimation(int strip, int idx){
  if(strip == 1 || strip == 2){
    setPixel(strip, 1, 0, 0, 255); // Keep player pos while shooting

    setPixel(strip, idx, 0, 0, 255);  // Shooting LED blob
    setPixel(strip, idx-1, 0, 0, 25); // dim trail
    setPixel(strip, idx-2, 0, 0, 10); // dim trail

    lStrip.show();

    setPixel(strip, idx-2, 0, 0, 0);  // Clearing prev pixels to show animation
    setPixel(strip, idx-1, 0, 0, 0);
    setPixel(strip, idx, 0, 0, 0);

          // Reset player position
    setPixel(strip, 1, 0, 0, 255);

  } else {
    setPixel(strip, 1, 0, 0, 255); // Keep player pos while shooting

    setPixel(strip, idx, 0, 0, 255);  // Shooting LED blob
    setPixel(strip, idx-1, 0, 0, 25); // dim trail
    setPixel(strip, idx-2, 0, 0, 10); // dim trail

    rStrip.show();

    setPixel(strip, idx-2, 0, 0, 0);  // Clearing prev pixels to show animation
    setPixel(strip, idx-1, 0, 0, 0);
    setPixel(strip, idx, 0, 0, 0);

    // Reset player position
    setPixel(strip, 1, 0, 0, 255);
  }

}

char checkBtn(){

  if(digitalRead(LEFT_BUTTON) == LOW){
    return 'L';
  } else if (digitalRead(SHOOT) == LOW){
    shoot();
    return 'S';
  } else if (digitalRead(RIGHT_BUTTON) == LOW){
    return 'R';
  }
}

uint32_t checkPixelColor(int strip, int idx) {

  uint32_t color;

  switch(strip){
    case 1:
      color = lStrip.getPixelColor(idx-1);
      break;
    case 2:
      color = lStrip.getPixelColor(NUM_LEDS - idx);
      break;
    case 3:
      color = rStrip.getPixelColor(idx-1);
      break;
    case 4:
      color = rStrip.getPixelColor(NUM_LEDS - idx);
      break;
  }

  return color;

}




void setPixel(int strip, int idx, int r, int g, int b){

  switch(strip){
    case 1:
      lStrip.setPixelColor(idx - 1, lStrip.Color(r, g, b));
      break;
    case 2:
      lStrip.setPixelColor(NUM_LEDS - idx, lStrip.Color(r, g, b));
      break;
    case 3:
      rStrip.setPixelColor(idx - 1, rStrip.Color(r, g, b));
      break;
    case 4:
      rStrip.setPixelColor(NUM_LEDS - idx, rStrip.Color(r, g, b));
      break;
  }

}