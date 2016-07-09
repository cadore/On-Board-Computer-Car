/*
  
 please take a look on the licence file !
 
 Electric Diagram (schematics)
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
 
 sensors pinouts
 Oxygen sensor (Narrowband 4wire bosh type) -----------------------PIN A0
 Vaccum/Pressure Sensor (SENSOR MAP -1+6bar - PANDOO EFI-4)--------PIN A1
 WATER TEMPERATURE SENSOR (LM35)-----------------------------------PIN A2
 AIR TEMPERATURE SENSOR (LM35)-------------------------------------PIN A3
 OIL TEMPERATURE SENSOR (LM35)-------------------------------------PIN A4
 OIL PRESSURE SENSOR 0-30BAR (5V)----------------------------------PIN A5
 SPST PUSH SWITCH -------------------------------------------------PIN 7
 SPST PUSH SWITCH -------------------------------------------------PIN 6
 MOSFET N-CHANNEL TO LCD BACKLIGHT --------------------------------PIN 9
 */

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int LCD_NB_ROWS = 2;
const int LCD_NB_COLUMNS = 16;
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
// custom lcd chars

byte START_DIV_0_OF_4[8] = {
  B01111,
  B11000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11000,
  B01111
};

byte START_DIV_1_OF_4[8] = {
  B01111,
  B11000,
  B10000,
  B10000,
  B10000,
  B10011,
  B11000,
  B01111
};

byte START_DIV_2_OF_4[8] = {
  B01111,
  B11000,
  B10000,
  B10000,
  B10111,
  B10011,
  B11000,
  B01111
}; 

byte START_DIV_3_OF_4[8] = {
  B01111,
  B11000,
  B10000,
  B10111,
  B10111,
  B10011,
  B11000,
  B01111
};

byte START_DIV_4_OF_4[8] = {
  B01111,
  B11000,
  B10011,
  B10111,
  B10111,
  B10011,
  B11000,
  B01111
};

byte DIV_0_OF_8[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};

byte DIV_1_OF_8[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B00000,
  B11111
};

byte DIV_2_OF_8[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B11000,
  B11000,
  B00000,
  B11111
};

byte DIV_3_OF_8[8] = {
  B11111,
  B00000,
  B00000,
  B11000,
  B11000,
  B11000,
  B00000,
  B11111
};

byte DIV_4_OF_8[8] = {
  B11111,
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
  B00000,
  B11111
};

byte DIV_5_OF_8[8] = {
  B11111,
  B00000,
  B11000,
  B11000,
  B11000,
  B11011,
  B00000,
  B11111
};

byte DIV_6_OF_8[8] = {
  B11111,
  B00000,
  B11000,
  B11000,
  B11011,
  B11011,
  B00000,
  B11111
};

byte DIV_7_OF_8[8] = {
  B11111,
  B00000,
  B11000,
  B11011,
  B11011,
  B11011,
  B00000,
  B11111
};

byte DIV_8_OF_8[8] = {
  B11111,
  B00000,
  B11011,
  B11011,
  B11011,
  B11011,
  B00000,
  B11111
};

byte END_DIV_0_OF_4[8] = {
  B11110,
  B00011,
  B00001,
  B00001,
  B00001,
  B00001,
  B00011,
  B11110
};

byte END_DIV_1_OF_4[8] = {
  B11110,
  B00011,
  B00001,
  B00001,
  B00001,
  B11001,
  B00011,
  B11110
};

byte END_DIV_2_OF_4[8] = {
  B11110,
  B00011,
  B00001,
  B00001,
  B11101,
  B11001,
  B00011,
  B11110
};

byte END_DIV_3_OF_4[8] = {
  B11110,
  B00011,
  B00001,
  B11101,
  B11101,
  B11001,
  B00011,
  B11110
};

byte END_DIV_4_OF_4[8] = {
  B11110,
  B00011,
  B11001,
  B11101,
  B11101,
  B11001,
  B00011,
  B11110
};



void setup_progressbar() {
  lcd.createChar(0, START_DIV_4_OF_4);
  lcd.createChar(1, DIV_0_OF_8);
  lcd.createChar(2, DIV_8_OF_8);
  lcd.createChar(3, END_DIV_0_OF_4);
}

void switch_progressbar_bank(byte bank) {
  switch (bank) {
  case 0:
    lcd.createChar(4, START_DIV_0_OF_4);
    lcd.createChar(5, START_DIV_1_OF_4);
    lcd.createChar(6, START_DIV_2_OF_4);
    lcd.createChar(7, START_DIV_3_OF_4);
    break;

  case 1:
    lcd.createChar(4, DIV_1_OF_8);
    lcd.createChar(5, DIV_2_OF_8);
    lcd.createChar(6, DIV_3_OF_8);
    lcd.createChar(7, DIV_4_OF_8);
    break;

  case 2:
    lcd.createChar(4, DIV_4_OF_8);
    lcd.createChar(5, DIV_5_OF_8);
    lcd.createChar(6, DIV_6_OF_8);
    lcd.createChar(7, DIV_7_OF_8);
    break;

  case 3:
    lcd.createChar(4, END_DIV_1_OF_4);
    lcd.createChar(5, END_DIV_2_OF_4);
    lcd.createChar(6, END_DIV_3_OF_4);
    lcd.createChar(7, END_DIV_4_OF_4);
    break;
  }
}

void draw_progressbar(byte percent, byte line) {

  lcd.setCursor(0, line);

  byte nb_columns = map(percent, 0, 100, 0, (LCD_NB_COLUMNS - 4) * 2 * 4 - 2 * 4);
  for (byte i = 0; i < LCD_NB_COLUMNS - 4; ++i) {
    if (i == 0) { 
      if (nb_columns > 4) {
        lcd.write((byte) 0); 
        nb_columns -= 4;

      } 
      else if (nb_columns == 4) {
        lcd.write((byte) 0); 
        nb_columns = 0;

      } 
      else {
        switch_progressbar_bank(0);
        lcd.setCursor(i, line);
        lcd.write(nb_columns + 4); 
        nb_columns = 0;
      }

    } 
    else if (i == LCD_NB_COLUMNS - 5) { 


      if (nb_columns > 0) {
        switch_progressbar_bank(3);
        lcd.setCursor(i, line);
        lcd.write(nb_columns + 3);

      } 
      else {
        lcd.write(3);
      }

    } 
    else { 


      if (nb_columns == 0) {
        lcd.write(1);

      } 
      else if (nb_columns >= 8) {
        lcd.write(2); 
        nb_columns -= 8;

      } 
      else if (nb_columns >= 4 && nb_columns < 8) {
        switch_progressbar_bank(2);
        lcd.setCursor(i, line);
        lcd.write(nb_columns); 
        nb_columns = 0;

      } 
      else if (nb_columns < 4) {
        switch_progressbar_bank(1);
        lcd.setCursor(i, line);
        lcd.write(nb_columns + 3);
        nb_columns = 0;
      }
    }
  }


  char tmp[5];
  sprintf(tmp, "%3d%%", percent);
  lcd.print(tmp);
}


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
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
  setup_progressbar();
  lcd.clear();
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
  LcdCfg();

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
    } 
    else
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
  int Value_lambda_graph = map(analogRead(SEN_LAMBDA), 0, 1023, 0, 100);
  if (value_lambda > F_MAX_LAMBDA) F_MAX_LAMBDA = value_lambda; //store values from lambda
  if (value_lambda < F_MIN_LAMBDA) F_MIN_LAMBDA = value_lambda; // MAX AND MIN
  lcd.clear();
  if (value_lambda > 950){
    lcd.setCursor(2, 0);
    lcd.print("MISTURA RICA");
    lcd.setCursor(0, 1);
    lcd.print("LAMBDA: ");
    lcd.print(value_lambda);
    lcd.print("mV");
  }
  if (value_lambda < 450){
    lcd.setCursor(2, 0);
    lcd.print("MISTURA  POBRE");
    lcd.setCursor(0, 1);
    lcd.print("LAMBDA: ");
    lcd.print(value_lambda);
    lcd.print("mV");
  }

  lcd.setCursor(0, 0);
  lcd.print("LAMBDA: ");
  lcd.print(value_lambda);
  lcd.print("mV");
  draw_progressbar(Value_lambda_graph, 1);


  /*
  lcd.setCursor(0, 1);
   lcd.print("MIN ");
   lcd.print(F_MIN_LAMBDA);
   lcd.print(" MAX ");
   lcd.print(F_MAX_LAMBDA);
   
   */
  delay(5); // give some time to a/d converter
}
void showOilPressure() {
  int Value_PRESS_OIL = map(analogRead(SEN_PRESS_OIL), 0, 1023, 0, 30);
  if (Value_PRESS_OIL > F_MAX_PRESS_OIL) F_MAX_PRESS_OIL = Value_PRESS_OIL; //store values from lambda
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Oleo: ");
  lcd.print(Value_PRESS_OIL);
  lcd.setCursor(10, 0);
  lcd.print("BAR");
}
void showMapStatus() {
  int Value_map = map(analogRead(SEN_MAP), 0, 1023, 0, 6000);
  int Value_map_positive;
  int Value_map_negative;
  if (Value_map < 1000){
    Value_map_negative = map(Value_map, 0, 1000,1000,0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MAP: -");
    lcd.print(Value_map_negative);
    lcd.print(" GF");
    lcd.setCursor(0, 1);
    lcd.print(" MAX ");
    lcd.print(F_MAX_MAP);
    lcd.setCursor(10, 1);
    lcd.print(" GF");
  }
  if (Value_map > 1000){
    Value_map_positive = map(Value_map, 1000, 6000,0,6000);
    if (Value_map_positive > F_MAX_MAP) F_MAX_MAP = Value_map_positive; //store values from map
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MAP: ");
    lcd.print(Value_map_positive);
    lcd.print(" GF");
    lcd.setCursor(0, 1);
    lcd.print(" MAX ");
    lcd.print(F_MAX_MAP);
    lcd.setCursor(10, 1);
    lcd.print(" GF");
  }
  if (Value_map = 1000){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MAP: ");
    lcd.print("0000");
    lcd.print(" GF");
    lcd.setCursor(0, 1);
    lcd.print(" MAX ");
    lcd.print(F_MAX_MAP);
    lcd.setCursor(10, 1);
    lcd.print(" GF");
  }

}
void showWaterTemp() {
  float value_temperatura = (analogRead(SEN_TEMP_WATER)/1024.0)*500;
  if (value_temperatura > F_MAX_TEMP_WATER) F_MAX_TEMP_WATER = value_temperatura; //store values
  if (value_temperatura < F_MIN_TEMP_WATER) F_MIN_TEMP_WATER = value_temperatura; // MAX AND MIN
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.print(value_temperatura);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("MIN ");
  lcd.print(F_MIN_TEMP_WATER);
  lcd.print(" MAX ");
  lcd.print(F_MAX_TEMP_WATER);

}
//Aqui a funcao que pula a cada 5 segundos o que vai ser mostrado
void jumpAutommatically() {
  if (millis() - previous >= IntervalShowMenu * 1000) {
    jumpToNext();
  }
}
