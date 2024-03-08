/*
  Simple analogue power meter to measure current transformer (CT)
  output and calculate mains active power cost per kWHr

  Note: Works best for resistive loads as voltage phase shift
  is not taken into account

  Adapted from code by Open Energy Monitor project
  https://github.com/openenergymonitor/EmonLib

  Author: Peter Milne
  Date: 31 May 2022

  Copyright 2022 Peter Milne
  Released under GNU GENERAL PUBLIC LICENSE
  Version 3, 29 June 2007

 ****************************************************/

#include <SPI.h>
#include "lowpass.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
/*
  Irms conversion ratio derived from
  CT number of turns / Burden resistor
  Adjust this value to calibrate - make sure to
  use decimal places to avoid integer division!
*/
const float current_ratio = 0.693;

//2000.0 / 47;

// Resistor divider bias value
int16_t adc_bias = 512;

// Actual Arduino voltage measured across 5V pin & GND
#define ARDUINO_V 3.3

// Electricity cost per kWHr, not including standing charge
#define COST_PER_KWHR 25.00  // Cost per kWHr (cents)

// Mains RMS voltage - can be adjusted
#define MAINS_V_RMS  220.0

#define NUM_OF_SAMPLES 1600
#define ADC_PIN A1


// define pins for screen
#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif

// setup screen for use
// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
float p = 3.1415926;

// Variable to store total energy used
int total_energy = 0.0;
double active_power;
double rnd_cost;

void setup() {
  Serial.begin(115200);
  Serial.print(F("Hello! ST77xx TFT Test"));

    // OR use this initializer (uncomment) if using a 1.14" 240x135 TFT:
  tft.init(135, 240);           // Init ST7789 240x135

  Serial.println("done");
  delay(1000);
}

void loop() {

  unsigned long start = millis();
  int32_t adc_sum_sqr = 0;
  for (int n = 0; n < NUM_OF_SAMPLES; n++)
  {
    int16_t adc_raw = analogRead(ADC_PIN);

    // Remove ADC bias - low pass filter
    int16_t adc_filtered = intLowPass(&adc_bias, adc_raw);

    // Accumulate square of filtered ADC readings
    adc_sum_sqr += adc_filtered * adc_filtered;
  }
  unsigned long finish = millis();

  // Calculate measured RMS (Root Mean Square) voltage across burden resistor
  double vrms = sqrt(adc_sum_sqr / NUM_OF_SAMPLES) * ARDUINO_V / 1024.0;

  // Scale to mains current RMS (measured vrms * CT turns / Burden R)
  double Irms = vrms * current_ratio;

  // Calculate active power (Irms * Vrms)
  active_power = (Irms * MAINS_V_RMS);

  // Calculate cost per kWHr
  rnd_cost = round(active_power * COST_PER_KWHR / 1000.0);

  // Calculate the energy for this interval in watt-hours
  int interval_duration_hours = (finish - start) / 3600000.0; // Convert milliseconds to hours
  int interval_energy = active_power * interval_duration_hours;
  total_energy += interval_energy;

    
  // tft print function!
  tftPrintTest();
  //char power_str[] = {'0', '0', '0', '0', '0', 'W', '\0'};
  //val_to_str(active_power, power_str);

  //char cost_str[] = {'0', '0', '0', '0', '0', 'p', '\0'};
  //val_to_str(rnd_cost, cost_str);

  Serial.print("Arduino V: ");
  Serial.println(ARDUINO_V);
  Serial.print(" Accumulated ADC: ");
  Serial.println(adc_sum_sqr);
  Serial.print(" Samples: ");
  Serial.println(NUM_OF_SAMPLES);
  Serial.print(" Measured V: ");
  Serial.println(vrms, 3);
  Serial.print(" Irms: ");
  Serial.println(Irms);
  Serial.print(" Active Power: ");
  Serial.println(active_power);
  Serial.print(" Rnd Cost: ");
  Serial.println(rnd_cost);
  Serial.print(" Time: ");
  Serial.println(finish - start);
  
  // Displaying the total energy used
  Serial.print("Total Energy Used (Wh): ");
  Serial.println(total_energy);

  delay(2000);
}


// Convert integer value to display string
//void val_to_str(unsigned long v, char * s) {
  //if (v > 99999) {
   // return;
  //}
  //s[0] = v / 1000 / 10 + '0';
 // s[1] = v / 1000 % 10 + '0';
  //s[2] = v / 100 % 10 + '0';
 // s[3] = v % 100 / 10 + '0';
 // s[4] = v % 100 % 10 + '0';
//}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);

  // Rotate the display to landscape mode
  tft.setRotation(-3); // Adjust the rotation value as needed
  
  // Print Active Power
  tft.setCursor(0, 10);
  tft.println("Active Power: ");
  tft.print(active_power);
  tft.println(" Watts");
  
  // Print Todays Energy
  tft.setCursor(0, 50);
  tft.println("Todays Energy: ");
  tft.print(total_energy);
  tft.println(" Watts");
  
  // Print Electrical Cost
  tft.setCursor(0, 90);
  tft.println("Electrical Cost: ");
  tft.print(rnd_cost);
  tft.println(" Cents");
}