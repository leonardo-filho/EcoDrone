#include <Arduino.h>
#include <EEPROM.h>
#include "GravityTDS.h"

#define TdsSensorPin A1
GravityTDS gravityTds;
float temperatura = 25;
float tdsValue = 0;
int pHSense          = A0;
int sensorTemp       = A2;
int samples          = 40;
int from_ad          = 0;
float adc_resolution = 1024.0;

void setup()
{
  pinMode(sensorTemp, OUTPUT);
  Serial.begin(9600);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  
  gravityTds.setAdcRange(1024);
  gravityTds.begin(); 
}

float ph (float voltage) {
  return 7 + ((2.5 - voltage) / 0.18);
}

void loop () {
  int measurings=0;
  
  for (int i = 0; i < samples; i++)
  {
    from_ad = analogRead(pHSense);
    measurings += from_ad;
    delay(10);
    Serial.println(analogRead(from_ad));
  }
    float voltage = 5 / adc_resolution * measurings/samples;
    Serial.print("pH: ");
    Serial.println(ph(voltage));
    

    float valorsensorTemp = analogRead(sensorTemp);
    float tensaoSaida = (valorsensorTemp * 2500) / 1024;
    float temperaturaC = tensaoSaida / 10;
    Serial.print("Temperatura: ");
    Serial.print(temperaturaC);
    Serial.println(" °C");
    
    
    gravityTds.setTemperature(temperaturaC); 
    gravityTds.update();  
    tdsValue = gravityTds.getTdsValue();  
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    delay(500);
}