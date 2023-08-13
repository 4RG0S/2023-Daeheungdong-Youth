#include <stdlib.h>
#include <time.h>

#define ledRed       13
#define ledRedBtn     6
#define ledWhite     12
#define ledWhiteBtn   5
#define ledGreen     11
#define ledGreenBtn   4
#define ledYellow    10
#define ledYellowBtn  3
#define ledBlue       9 
#define ledBlueBtn    2

#define GameStartBtn  8


int idleLED = 13;
byte currentOutput = HIGH;

void turnOffAllLEDs() {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledWhite, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
}

void turnOnAllLEDs() {
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledWhite, HIGH);
  digitalWrite(ledBlue, HIGH);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledYellow, HIGH);
}

void Idle() {
  if(idleLED == 8 ) {
    idleLED = 13;
    currentOutput = !currentOutput;
  } else {
    digitalWrite(idleLED, currentOutput); 
  }
  
  idleLED--;
}

void GameOver() {
  turnOffAllLEDs();
  Serial.print("GameOVer!!!\n");
  turnOffAllLEDs();
}

void GameClear() {
  turnOffAllLEDs();

  for(int i = 0; i < 3; i++) {
    turnOnAllLEDs();

    delay(500);
    
    turnOffAllLEDs();
  }
}

bool Game() {
  turnOffAllLEDs();
  int currentLED = 0;
  int curStage = 0;
  bool checkCurStage = false;
  //Serial.print("GameSTart!!\n");
  long time_ = millis();
  byte LEDStates[5] = {LOW, };

  while(1) {
    checkCurStage = false;
    currentLED = (rand() % 5) + 9;

    if(curStage == 20) {
      return true;
    } 

    if((millis() - time_) >= (1000)) {
      time_ = millis();
  
      digitalWrite(currentLED, HIGH);
      Serial.print("ON!!!!\n");
      
      while((millis() - time_) < (3000 - (50 * curStage))) { // waiting for button inputs (digitalRead)
        if(digitalRead(currentLED - 7) == 0) {
          Serial.print(currentLED - 7);
          Serial.print("Button Pressed!\n");
          checkCurStage = true;
          curStage++;
          break;
        }
      }

      if(!checkCurStage) {
        break;
      }

      time_ = millis();
      digitalWrite(currentLED, LOW);
      Serial.print("OFF!!!!\n");
    
    }

    turnOffAllLEDs();
  }
  
  return false;

}

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledWhite, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  pinMode(ledRedBtn, INPUT_PULLUP);
  pinMode(ledWhiteBtn, INPUT_PULLUP);
  pinMode(ledGreenBtn, INPUT_PULLUP);
  pinMode(ledYellowBtn, INPUT_PULLUP);
  pinMode(ledBlueBtn, INPUT_PULLUP);

  pinMode(GameStartBtn, INPUT_PULLUP);

  //srand((unsigned int)time(NULL));
  turnOffAllLEDs();
  //MsTimer2::set(1000, Idle);
  //MsTimer2::start();
  Serial.begin(9600);
}

void loop() {
  turnOffAllLEDs();
  if(digitalRead(GameStartBtn) == 0) {
    Serial.print("GameStart!\n");
    if(Game()) {
      Serial.print("Game Clear! Congrats!\n");
      GameClear();
    } else {
      GameOver();
    }
  }
}

