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

#define     THERMISTOR_PIN     A1      
#define     SERIES_RESISTOR    1000  
#define     ADC_SAMPLES        5      
typedef float (*TempConversion)(float);
TempConversion ToKelvin; 
TempConversion FromKelvin;
char* TempUnit;
// Steinhart-Hart coefficients.
float A, B, C;

void setup() {
  EspSerial.begin(ESP8266_BAUD);
  Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(1000L,tempmeasurement); 
  
  analogReference(DEFAULT);
  ToKelvin = &fahrenheitToKelvin;
  FromKelvin = &kelvinToFahrenheit;
  TempUnit = "Fahrenheit";
  A=.007430338382;
  B=-.001156812787;
  C=.000010851770;
}

void loop() {
  Blynk.run();
  timer.run();
  float temp = FromKelvin(readTemp());


}
double readResistance() {
  float reading = 0;
  for (int i = 0; i < ADC_SAMPLES; ++i) {
    reading += analogRead(THERMISTOR_PIN);
  }
  reading /= (float)ADC_SAMPLES;
  reading = (1023 / reading) - 1;
  return SERIES_RESISTOR / reading;
}
float readTemp() {
  float R = readResistance();
  float kelvin = 1.0/(A + B*log(R) + C*pow(log(R), 3.0));
  return kelvin;
}
void tempmeasurement() {
//    byte t1 = ;
//    byte t2 = ;
//    byte t3 = ;

//    Blynk.virtualWrite(V0, t1);               //  Set Virtual Pin 0 frequency to PUSH in Blynk app
//    Blynk.virtualWrite(V1, t2);               //  Set Virtual Pin 1 frequency to PUSH in Blynk app
//    Blynk.virtualWrite(V2, t3);               
        
}

float kelvinToFahrenheit(float kelvin) {
  return kelvin*(9.0/5.0) - 459.67;
}

float fahrenheitToKelvin(float fahrenheit) {
  return (fahrenheit + 459.67)*(5.0/9.0);
}

float kelvinToCelsius(float kelvin) {
  return kelvin - 273.15;
}

float celsiusToKelvin(float celsius) {
  return celsius + 273.15; 
}
