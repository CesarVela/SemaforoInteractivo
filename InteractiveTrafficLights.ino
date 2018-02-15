/*  
 *   Interactive Traffic Lights
 *   
 *   Este ejemplo muestra un conjunto de semáforos que cambiarán de verde a rojo, ámbar y viceversa, 
 *   luego de un período de tiempo establecido, utilizando el sistema de cuatro estados de Mexico.
 *   Este se extiende para incluir un conjunto de luces peatonales y un botón peatonal para solicitar 
 *   cruzar la calle. El Arduino reaccionará cuando se presione el botón cambiando el estado de las 
 *   luces para que los autos se detengan y permitan que el peatón cruce con seguridad.
 *   
 *   This example code is in the public domain.
 */
const int CAR_RED = 12; // assign the car lights
const int CAR_YELLOW = 11;
const int CAR_GREEN = 10;
const int PED_RED = 9; // assign the pedestrian lights
const int PED_GREEN = 8;
const int BUTTON = 2; // button pin
unsigned long crossTime = 10000; // time alloyoud to cross
unsigned long changeTime; // time since BUTTON pressed
int state = LOW; //If is push buttom

void setup() {
  pinMode(CAR_RED, OUTPUT);
  pinMode(CAR_YELLOW, OUTPUT);
  pinMode(CAR_GREEN, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT); // button on pin 2
  // turn on the green light
  digitalWrite(CAR_GREEN, HIGH);
  digitalWrite(PED_RED, HIGH);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BUTTON)) // Change of state is button is pressed
    state = HIGH;
  /* check if BUTTON is pressed and it is over 5 seconds since last button press */
  if (state == HIGH && (millis() - changeTime) > crossTime) {
    int valor= analogRead(A0);
    crossTime = map(valor, 0, 1023, 10, 60)*1000; //Calcula el valor del tiempo de cruze
    Serial.println(crossTime);
    Serial.println(valor);
    changeLights(); // change the lights
    state = LOW; //Reset state
  }
}


/*
 * Rutina que realiza el cambio de color en los semaforos cuando el boton es presionado
 */
void changeLights() {
  flash(CAR_GREEN); // flash green
  digitalWrite(CAR_YELLOW, HIGH); // yellow on
  delay(2000); // wait 2 seconds
  digitalWrite(CAR_YELLOW, LOW); // yellow off
  digitalWrite(CAR_RED, HIGH); // red on
  delay(1000); // wait 1 second till its safe
  digitalWrite(PED_RED, LOW); // ped red off
  digitalWrite(PED_GREEN, HIGH); // ped green on
  delay(crossTime); // wait for preset time period
  flash(PED_GREEN); // flash the ped green
  // turn ped red on
  digitalWrite(PED_RED, HIGH);
  delay(1000);
  digitalWrite(CAR_RED, LOW); // red off
  digitalWrite(CAR_GREEN, HIGH);

  // record the time since last change of lights
  changeTime = millis();
  // then return to the main program loop
}


// flash the light in pin n
void flash(int pin){
  
  for (int x=0; x<6; x++) {
    digitalWrite(pin, HIGH);
    delay(250);
    digitalWrite(pin, LOW);
    delay(250);
  }
}
