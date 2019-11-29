//test//
#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <RSCG12864B.h>

char auth[] = "8I5EtnAfCRot-_e_Rux6eyVwpiPnrOTL";
char ssid[] = "Benders Scotland";
char pass[] = "$ingapore14";

#define EspSerial Serial

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);
BlynkTimer timer;


// Thermistor configuration
#define     SERIES_RESISTOR        10000   // Resistor value (in Ohms) in series with the thermistor.
#define     ADC_SAMPLES            5       // Number of ADC samples to average for a reading.
#define     A0_COEFFICIENT          0.000871981716
#define     B0_COEFFICIENT          0.000214324808
#define     C0_COEFFICIENT          0.000000137017
#define     A1_COEFFICIENT          0.000254628705
#define     B1_COEFFICIENT          0.000375180983
#define     C1_COEFFICIENT          -0.000000069774

void setup() {
  EspSerial.begin(ESP8266_BAUD);
  Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(3000L,tempmeasurement);  
  //Serial.begin(115200);
}

void loop() {
  Blynk.run();
  timer.run(); 
}
void tempmeasurement() {
  float R = 0;
  for (int i = 0; i < ADC_SAMPLES; ++i) {
    R += analogRead(A0);
  }
  R /= (float)ADC_SAMPLES;
  R = (1023 / R) - 1;
  R = SERIES_RESISTOR / R;
  float t1 = 1/(A0_COEFFICIENT + B0_COEFFICIENT*log(R) + C0_COEFFICIENT*pow(log(R), 3));
  t1=(t1-273.15)*9/5+32;

  R = 0;
  for (int i = 0; i < ADC_SAMPLES; ++i) {
    R += analogRead(A1);
  }
  R /= (float)ADC_SAMPLES;
  R = (1023 / R) - 1;
  R = SERIES_RESISTOR / R;
  float t2 = 1/(A0_COEFFICIENT + B0_COEFFICIENT*log(R) + C0_COEFFICIENT*pow(log(R), 3));
  t2=(t2-273.15)*9/5+32;
    
  R = 0;
  for (int i = 0; i < ADC_SAMPLES; ++i) {
    R += analogRead(A2);
  }
  R /= (float)ADC_SAMPLES;
  R = (1023 / R) - 1;
  R = SERIES_RESISTOR / R;
  float t3 = 1/(A0_COEFFICIENT + B0_COEFFICIENT*log(R) + C0_COEFFICIENT*pow(log(R), 3));
  t3=(t3-273.15)*9/5+32;
    
/*  R = 0;
  for (int i = 0; i < ADC_SAMPLES; ++i) {
  R += analogRead(A0);
  }
  R /= (float)ADC_SAMPLES;
  R = (1023 / R) - 1;
  R = SERIES_RESISTOR / R;
  float t4 = 1/(A1_COEFFICIENT + B1_COEFFICIENT*log(R) + C1_COEFFICIENT*pow(log(R), 3)); 
  t1=(t1-273.15)*9/5+32;
*/
  Blynk.virtualWrite(V0, t1);               //  Set Virtual Pin 0 frequency to PUSH in Blynk app
  Blynk.virtualWrite(V1, t2);               //  Set Virtual Pin 1 frequency to PUSH in Blynk app
  Blynk.virtualWrite(V2, t3);               
//  Blynk.virtualWrite(V3, t4);   
  
  char temp1[4];
  itoa(t1,temp1,10);  
  char temp2[3];
  itoa(t2,temp2,10);
  char temp3[2];
  itoa(t3,temp3,10);
  RSCG12864B.begin();
  RSCG12864B.brightness(255);
  RSCG12864B.clear();
  RSCG12864B.font_revers_on();
  RSCG12864B.font_revers_off();
  RSCG12864B.print_string_6x12_xy(0,0,"Probe 1 Temp:");
  if (t1>=-15){
  RSCG12864B.print_string_6x12(temp1);
  RSCG12864B.print_string_6x12(" F");
  }   
  RSCG12864B.print_string_6x12_xy(0,17,"Probe 2 Temp:");
  if (t2>=-15){  
  RSCG12864B.print_string_6x12(temp2);
  RSCG12864B.print_string_6x12(" F");  
  }
  RSCG12864B.print_string_6x12_xy(0,33,"Probe 3 Temp:");
  if (t3>=-15){    
  RSCG12864B.print_string_6x12(temp3);
  RSCG12864B.print_string_6x12(" F");   
  }
//   RSCG12864B.display_off();  
//   RSCG12864B.display_on();  
          
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
//  C = ((gamma3 - gamma2)/(L3 - L2))*pow((L1 + L2 + L3), -1.0);
//  B = gamma2 - C*(pow(L1, 2.0) + L1*L2 + pow(L2, 2.0));
//  A = Y1 - (B + pow(L1, 2.0)*C)*L1;

}
void waitForOk() {
  Serial.println(F("Type OK <enter> to continue.\n"));
  while (!(Serial.findUntil("OK", "\n")));
}
void notifytemp(){
  Blynk.notify("Target Temperature has been reached");
}
