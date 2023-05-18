// BUTTON SETUP

#define BUTTON_PIN    13

// LED STRIP DECLARATIONS

#include <Adafruit_NeoPixel.h>

#define LED_Right         A5
#define LED_MRight        A4  // On Trinket or Gemma, suggest changing this to 1
#define LED_MLeft         A3  // Mid two currently being used
#define LED_Left          A2

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 144 // Amount of LEDs Per Strip

Adafruit_NeoPixel rightMidStrip(NUMPIXELS, LED_MRight, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel leftMidStrip(NUMPIXELS, LED_MLeft, NEO_GRBW + NEO_KHZ800);

// 2 more NEOPIXEL led strips to be added called rightStrip and leftStrip
Adafruit_NeoPixel leftStrip(NUMPIXELS, LED_Left, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel rightStrip(NUMPIXELS, LED_Right, NEO_GRBW + NEO_KHZ800);

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;

// POINTS SCORE STORAGE
int points = 0;

// Current Position LED
bool leftMidEnabled = false;  // This is the starting strip, set to true in setup()
bool rightMidEnabled = false;
bool leftEnabled = false;
bool rightEnabled = false;

int enemyCount = 0;
bool enemy1;
bool enemy2;
bool enemy3;
bool enemy4;

// the setup routine  runs once when you press reset:
void setup() {
  // initialize  the digital pins as outputs.
  pinMode(pinA, OUTPUT);
  pinMode(pinB,  OUTPUT); 
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG,  OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3,  OUTPUT);  
  pinMode(D4, OUTPUT);  

  

  rightMidStrip.begin(); // INITIALIZE NeoPixel strip object
  leftMidStrip.begin();

  rightMidStrip.clear();
  rightMidStrip.show();

  // Initialise Button With PIN
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  leftMidEnabled = true;
  rightMidEnabled = false;

  enemy1 = true;
  enemy2 = true;
  enemy3 = true;
  enemy4 = true;

}

// the loop routine runs over  and over again forever:
void loop() {

  delay(100);
  rightMidStrip.clear(); // Reset LED Strips to 'off'
  leftMidStrip.clear();
  

  for(int i=NUMPIXELS; i>0; i--) {
    checkInput(i);
    if(rightMidEnabled){
      rightMidStrip.setPixelColor(i, rightMidStrip.Color(0, 255, 0, 0));
      
      // Lives
      rightMidStrip.setPixelColor(143, rightMidStrip.Color(0, 255, 0, 0));
      rightMidStrip.setPixelColor(142, rightMidStrip.Color(0, 255, 0, 0));
      rightMidStrip.setPixelColor(141, rightMidStrip.Color(0, 255, 0, 0));
      rightMidStrip.setPixelColor(140, rightMidStrip.Color(0, 255, 0, 0));

      // Enemies
      if (enemy1){
      rightMidStrip.setPixelColor(1, rightMidStrip.Color(255, 0, 0, 0));

      } if (enemy2){
      rightMidStrip.setPixelColor(2, rightMidStrip.Color(255, 0, 0, 0));

      } if(enemy3){
      rightMidStrip.setPixelColor(3, rightMidStrip.Color(255, 0, 0, 0));

      } if(enemy4){
      rightMidStrip.setPixelColor(4, rightMidStrip.Color(255, 0, 0, 0));

      }

      uint32_t nextPixelColor = rightMidStrip.getPixelColor(i+1); // Get the color of the next pixel

      if (nextPixelColor == rightMidStrip.Color(255, 0, 0)) { // Check if the next pixel is red
        // Do something if the next pixel is red
        enemyCount++;
        switch(enemyCount){
          case 1:
            enemy1 = false;
          break;
          case 2:
            enemy2 = false;
          break;
          case 3:
            enemy3 = false;
          break;
          case 4:
            enemy4 = false;
          break;
        }
      }

      rightMidStrip.show();
    
    } else {
      
    }

    if (leftMidEnabled) {
      leftMidStrip.setPixelColor(i, leftMidStrip.Color(0, 0, 255, 0));

      // Enemies
      leftMidStrip.setPixelColor(1, leftMidStrip.Color(255, 0, 0, 0));
      leftMidStrip.setPixelColor(2, leftMidStrip.Color(255, 0, 0, 0));
      leftMidStrip.setPixelColor(3, leftMidStrip.Color(255, 0, 0, 0));
      leftMidStrip.setPixelColor(4, leftMidStrip.Color(255, 0, 0, 0));

      leftMidStrip.show();
    } else{
      leftMidStrip.clear();
      leftMidStrip.show();
    }

    delay(10);
    rightMidStrip.clear();
    leftMidStrip.clear();
  }

  /*
  for(int i = 9; i > 0; i--){
    for(int j = 9; j > 0; j--){
      delay(200);
      setWritePosition(2);
      numberSelector(j);
      delay(200);
      setWritePosition(1);
      numberSelector(i);
    }
  }
  */

}

void setWritePosition(int pos){
  switch(pos){
    case 1:
      digitalWrite(D1, LOW);
      digitalWrite(D2,  HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH); 
      break;
    case 2:
      digitalWrite(D1, HIGH);
      digitalWrite(D2,  LOW);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH); 
      break;
    case 3:
      digitalWrite(D1, HIGH);
      digitalWrite(D2,  HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(D4, HIGH); 
      break;
    case 4:
      digitalWrite(D1, HIGH);
      digitalWrite(D2,  HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW); 
      break;
  }
}

void numberSelector(int num){
  
  switch(num){
    case 0:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
  }
  
}

void zero(){

  //writePosition(pos);

  //0
  digitalWrite(pinA,  HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF,  HIGH);   
  digitalWrite(pinG, LOW);
}

void one(){
  
  //writePosition(pos);

  //1
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD,  LOW);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, LOW);

}

void two(){

  //writePosition(pos);

  //2
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD,  HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);
}

void three(){

  //writePosition(pos);

  //3
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD,  HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);
}

void four(){

  //writePosition(pos);

  // 4
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD,  LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);
  
}

void five(){

  //writePosition(pos);

  // 5
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD,  HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);
}

void six(){
  
  //writePosition(pos);

  // 6
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD,  HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);
}

void seven(){

  //writePosition(pos);

  // 7
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD,  LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);

}

void eight(){

  //writePosition(pos);

  // 8
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD,  HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);

}

void nine(){

  //writePosition(pos);

  // 9
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD,  HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);

}

// Button Press Checker

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
      leftMidEnabled = false;
      rightMidEnabled = true;
      delay(20);
    }
}



