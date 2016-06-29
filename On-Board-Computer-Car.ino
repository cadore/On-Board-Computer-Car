//Global Escope
#define BUTTON_UP 3 //Depois colocamos o certo aqui
#define BUTTON_DOWN 5 //Aqui também
//Define all possible status that will be used, and the sequence for them
enum showing {
    OIL_PRESSURE,
    TURBINE_PRESSURE,
    MAP_SENSOR_STATUS,
    WATER_TEMPERATURE
};
    /*
      Assim acho que fica bem fácil a leitura porque no lugar de numeros
      deixamos os nomes do que cada caso vai fazer
    */
    //Control the current status base on this global var
    int current = 0; //Begin from 0 (OIL_PRESSURE)
    unsigned long counter; //Pra contar os Millis
    unsigned long previous; //Pra contar a ultima vez que o botao foi pressionado
    int last = sizeof(showing) - 1; //Assim sempre que colocar mais um sensor não precisamos mudar lá embaixo quando apertarmos um botão
    int interval = 10; //Intervalo em segundos que ele fica mostrando em cada sensor

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  
  verifyForPressedButton();
  
  switch (current) {
      case OIL_PRESSURE:
        showOilPressure();
        break;
      case TURBINE_PRESSURE:
        showTurbinePressure();
        break;
      case MAP_SENSOR_STATUS:
        showMapStatus();
        break;
      case WATER_TEMPERATURE:
        showWaterTemp();
        break;
  }
  
  jumpAutommatically();
  
}

void verifyForPressedButton() { //Ve se o botão for pressionado e altera o que é pra mostrar de acordo com isso
  if (digitalRead(BUTTON_UP) == 0) {
    jumpToNext();
  } else if (digitalRead(BUTTON_UP) == 0) {
    jumpToPrevious();
  }
}
void jumpToNext() { //Pula para o próximo se o estado atual não for o ultimo ou volta pro primeiro se ele for
  if (current == last) {
    current = 0;
  } else {
    current += 1;
  }
   previous = millis();
}
//TO DO, a função que retorna pro anterior
void jumpToPrevious() {
  
}
//TO DO, as funções que mostram cada leitura separadamente
void showOilPressure(){
  
}
void showTurbinePressure() {
  
}
void showMapStatus() {

}
void showWaterTemp() {

}
//Aqui a funcao que pula a cada 5 segundos o que vai ser mostrado
void jumpAutommatically() {
  if (millis() - previous >= interval * 1000) {
    jumpToNext();
  }
}
