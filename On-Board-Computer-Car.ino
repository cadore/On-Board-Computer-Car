#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//GLOBAL ESCOPE
const int SEN_LAMBDA = A0;
const int SEN_MAP = A1; //ADITIONAL SENSOR MAP -1+6bar - PANDOO EFI-4
const int SEN_TEMP_WATER = A2;
const int SEN_TEMP_AIR = A3;
const int SEN_TEMP_OIL = A4;
const int SEN_PRESS_OIL = A5;
const int BUTTON_UP = 7;
const int BUTTON_DOWN = 6;
const int DISPLAY_BACKLIGHT = 9;

//VARIABLES OF MIN AND MAX VALUES
float F_MIN_LAMBDA = 1000;
float F_MAX_LAMBDA = 0;
float F_MIN_MAP = 0;
float F_MAX_MAP = 0;
float F_MIN_TEMP_WATER = 0;
float F_MAX_TEMP_WATER = 0;
float F_MIN_TEMP_AIR = 0;
float F_MAX_TEMP_AIR = 0;
float F_MIN_TEMP_OIL = 0;
float F_MAX_TEMP_OIL = 0;
float F_MIN_PRESS_OIL = 0;
float F_MAX_PRESS_OIL = 0;

unsigned int CurrentMenu = 0;
unsigned long previousMillisClear = 0;

void StartPins() {
  pinMode(SEN_LAMBDA, INPUT);
  pinMode(SEN_MAP, INPUT);
  pinMode(SEN_TEMP_WATER, INPUT_PULLUP);
  pinMode(SEN_TEMP_AIR, INPUT_PULLUP);
  pinMode(SEN_TEMP_OIL, INPUT_PULLUP);
  pinMode(SEN_PRESS_OIL, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(DISPLAY_BACKLIGHT, OUTPUT);
}
void LcdCfg() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("ON BOARD CAR CPU");
  lcd.setCursor(1, 1);
  lcd.print("VERSAO BASICA");
  delay(3000);
  lcd.clear();
}
//CLEAR ALL VARIABLES MIN AND MAX
void clearMinMax() {
  F_MIN_LAMBDA = 0;
  F_MAX_LAMBDA = 0;
  F_MIN_MAP = 0;
  F_MAX_MAP = 0;
  F_MIN_TEMP_WATER = 0;
  F_MAX_TEMP_WATER = 0;
  F_MIN_TEMP_AIR = 0;
  F_MAX_TEMP_AIR = 0;
  F_MIN_TEMP_OIL = 0;
  F_MAX_TEMP_OIL = 0;
  F_MIN_PRESS_OIL = 0;
  F_MAX_PRESS_OIL = 0;
}

/*
  Electric Diagram
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)
*/

//Define all possible status that will be used, and the sequence for them
enum showing {
  MENU_PRESSURE,
  MENU_OIL_TEMPERATURE,
  MENU_MAP_SENSOR,
  MENU_WATER_TEMPERATURE,
  MENU_LAMBDA,
  CHANGE_BACKLIGHT
};
/*
  Assim acho que fica bem fácil a leitura porque no lugar de numeros
  deixamos os nomes do que cada caso vai fazer
*/
//Control the current status base on this global var
unsigned long counter; //Pra contar os Millis
unsigned long previous; //Pra contar a ultima vez que o botao foi pressionado
int last = sizeof(showing) - 1; //Assim sempre que colocar mais um sensor não precisamos mudar lá embaixo quando apertarmos um botão
unsigned int IntervalShowMenu = 5; //Intervalo em segundos que ele fica mostrando em cada sensor

void setup() {
  StartPins();

}

void loop() {

  verifyForPressedButton();

  switch (CurrentMenu) {
  }

  jumpAutommatically();

}

void verifyForPressedButton() { //Ve se o botão for pressionado e altera o que é pra mostrar de acordo com isso
  if (digitalRead(BUTTON_UP) == 0) {
    if (digitalRead(BUTTON_DOWN) == 0) {
      while (true) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillisClear >= 5000) {
          previousMillisClear = currentMillis;
          clearMinMax();
        }
        if (digitalRead(BUTTON_DOWN) == 1 && digitalRead(BUTTON_UP) == 1) {
          break;
        }
      }
    } else
      jumpToNext();
  }

  if (digitalRead(BUTTON_DOWN) == 0) {
    jumpToPrevious();
  }
}

//TODO, função que avanca para o proximo menu
void jumpToNext() { 
}
//TO DO, função que retorna pro anterior
void jumpToPrevious() {
}

//TO DO, as funções que mostram cada leitura separadamente
void showLambda() {
  int value_lambda = map(analogRead(SEN_LAMBDA), 0, 1023, 0, 5000);
  if (value_lambda > F_MAX_LAMBDA) F_MAX_LAMBDA = value_lambda; //store values from lambda
  if (value_lambda < F_MIN_LAMBDA) F_MIN_LAMBDA = value_lambda; // MAX AND MIN
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LAMBDA: ");
  lcd.print(value_lambda);
  lcd.print("mV");
  lcd.setCursor(0, 1);
  lcd.print("MIN ");
  lcd.print(F_MIN_LAMBDA);
  lcd.print(" MAX ");
  lcd.print(F_MAX_LAMBDA);
  delay(5); // give some time to a/d converter
}
void showOilPressure() {

}
void showMapStatus() {

}
void showWaterTemp() {

}
//Aqui a funcao que pula a cada 5 segundos o que vai ser mostrado
void jumpAutommatically() {
  if (millis() - previous >= IntervalShowMenu * 1000) {
    jumpToNext();
  }
}
