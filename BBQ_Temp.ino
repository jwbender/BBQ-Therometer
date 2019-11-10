#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = "8I5EtnAfCRot-_e_Rux6eyVwpiPnrOTL";
char ssid[] = "Benders Scotland";
char pass[] = "$ingapore14";

#define EspSerial Serial

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);
BlynkTimer timer;

float A, B, C;

void setup() {
    EspSerial.begin(ESP8266_BAUD);
 Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(1000L,tempmeasurement); 
}

void loop() {
  Blynk.run();
  timer.run();
}
void tempmeasurement() {
//    byte t1 = ;
//    byte t2 = ;
//    byte t3 = ;
//    byte t4 = ;  
//    Blynk.virtualWrite(V0, t1);               //  Set Virtual Pin 0 frequency to PUSH in Blynk app
//    Blynk.virtualWrite(V1, t2);               //  Set Virtual Pin 1 frequency to PUSH in Blynk app
//    Blynk.virtualWrite(V2, t3);               
//    Blynk.virtualWrite(V2, t4);  
    timer1();             
}
void timer1(){
  
}
void tempset(){
  
}
void tempcheck(int targettemp1,int tempset1){
  
}
void calibrator(){

float R1;
float R2;
float R3;

int THERMISTOR_PIN = 1;

waitForOk();
float CT1 =0; //read the value from blynk
  float reading = 0;
  for (int i = 0; i < 5; ++i) {
    reading += analogRead(THERMISTOR_PIN);
  }
  reading /= (float)5;
  R1 = (1023 / reading) - 1;
waitForOk();   

waitForOk();
float CT2 =0; //read the value from blynk
reading = 0;
  for (int i = 0; i < 5; ++i) {
    reading += analogRead(THERMISTOR_PIN);
  }
  reading /= (float)5;
  R2 = (1023 / reading) - 1;
waitForOk();   

waitForOk();
float CT3 =0; //read the value from blynk
reading = 0;
  for (int i = 0; i < 5; ++i) {
    reading += analogRead(THERMISTOR_PIN);
  }
  reading /= (float)5;
  R3 = (1023 / reading) - 1;
waitForOk();   
  float L1 = log(R1);
  float L2 = log(R2);
  float L3 = log(R3);
  float Y1 = 1.0 / (CT1+ 273.15);
  float Y2 = 1.0 / (CT2+ 273.15);
  float Y3 = 1.0 / (CT3+ 273.15);
  float gamma2 = ((Y2 - Y1)/(L2 - L1));
  float gamma3 = ((Y3 - Y1)/(L3 - L1));
  C = ((gamma3 - gamma2)/(L3 - L2))*pow((L1 + L2 + L3), -1.0);
  B = gamma2 - C*(pow(L1, 2.0) + L1*L2 + pow(L2, 2.0));
  A = Y1 - (B + pow(L1, 2.0)*C)*L1;

}
void waitForOk() {
  Serial.println(F("Type OK <enter> to continue.\n"));
  while (!(Serial.findUntil("OK", "\n")));
}
void notifytemp(){
  Blynk.notify("Target Temperature has been reached");
}
