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

Servo mi_servo;  // Objeto para controlar el servo

// segmentos para dígitos del 0-9
byte segmentos[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};