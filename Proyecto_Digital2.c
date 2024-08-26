#include <Arduino.h>
#include <ESP32Servo.h>
#include <config.h>

const int lm35_pin = 4;       // Pin de lectura del LM35
const int pin_rojo = 25;      // Pin para el LED rojo
const int pin_amarillo = 26;  // Pin para el LED amarillo
const int pin_verde = 27;     // Pin para el LED verde
const int button_pin = 15;    // Pin del botón
const int pwm_freq = 5000;    // Frecuencia PWM
const int pwm_resolution = 8; // Resolución PWM
const int pwm_channel_rojo = 3;
const int pwm_channel_amarillo = 1;
const int pwm_channel_verde = 2;

const int segA = 21;
const int segB = 23;
const int segC = 0;
const int segD = 18;
const int segE = 19;
const int segF = 22;
const int segG = 2;
const int dp = 5;

const int digito1 = 14;
const int digito2 = 12;
const int digito3 = 13;