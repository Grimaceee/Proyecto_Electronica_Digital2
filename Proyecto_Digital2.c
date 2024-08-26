#include <Arduino.h>
#include <ESP32Servo.h>
#include <config.h>

const int lm35_pin = 4;       // Pin del LM35
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

//AdafruitIO_Feed *temperCanal = io.feed("temp");
//AdafruitIO_Feed *verde = io.feed("servoverde");
//AdafruitIO_Feed *amarillo = io.feed("amarillo");
//AdafruitIO_Feed *rojo = io.feed("rojo");

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

// Digitos en el display
void mostrarDigito(byte valor, bool punto) {
    // Asignar cada segmento
    digitalWrite(segA, valor & 0b00000001);
    digitalWrite(segB, valor & 0b00000010);
    digitalWrite(segC, valor & 0b00000100);
    digitalWrite(segD, valor & 0b00001000);
    digitalWrite(segE, valor & 0b00010000);
    digitalWrite(segF, valor & 0b00100000);
    digitalWrite(segG, valor & 0b01000000);
    digitalWrite(dp, punto ? HIGH : LOW);  // Encender o apagar el punto decimal
}


void mostrarNumero(int numero) {
    int decimales = (numero * 10) % 10;
    int decenas = (numero / 10);
    int unidades = numero % 10;

  // Mostrar decenas
    digitalWrite(digito1, HIGH); // Encender el display 1
    mostrarDigito(segmentos[decenas], false); // Mostrar digito 1
    delay(5); // delay
    digitalWrite(digito1, LOW); // Apagar digito 1

    // Mostrar unidade
    digitalWrite(digito2, HIGH); // Encender el display 2
    mostrarDigito(segmentos[unidades], true); // Mostrar digito 1
    delay(5); // delay
    digitalWrite(digito2, LOW); // apagar digito 2


    // Mostrar decimales
    digitalWrite(digito3, HIGH); // Encender el display 3
    mostrarDigito(segmentos[decimales], false); // Mostrar digito 3
    delay(5); // delay
    digitalWrite(digito3, LOW); // apagar digito 3
}


void setup() {

  // Configurar PWM
  ledcSetup(pwm_channel_rojo, pwm_freq, pwm_resolution);
  ledcAttachPin(pin_rojo, pwm_channel_rojo);

  ledcSetup(pwm_channel_amarillo, pwm_freq, pwm_resolution);
  ledcAttachPin(pin_amarillo, pwm_channel_amarillo);

  ledcSetup(pwm_channel_verde, pwm_freq, pwm_resolution);
  ledcAttachPin(pin_verde, pwm_channel_verde);

  // pin del servo
  mi_servo.attach(32);

  // Configurar boton
  pinMode(button_pin, INPUT_PULLUP);

  // Segmentos
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(dp, OUTPUT);

  // Digitos
  pinMode(digito1, OUTPUT);
  pinMode(digito2, OUTPUT);
  pinMode(digito3, OUTPUT);

  // Puerto serial
  Serial.begin(115200);

  //while(! Serial);

  //Serial.print("Connecting to Adafruit IO");

  //io.connect();

  //while(io.status() < AIO_CONNECTED) {
    //Serial.print(".");
    //delay(500);
  //}


   //we are connected
  //Serial.println();
  //Serial.println(io.statusText());
}

void loop() {
  
  if (digitalRead(button_pin) == LOW) {
    float lectura_analogica = analogRead(lm35_pin);
    float voltaje = lectura_analogica * (3.3 / 4095.0);
    float temperatura = voltaje * 100.0 + 23; 
    //io.run();
    Serial.print("Lectura ADC: ");
    Serial.print(lectura_analogica);
    Serial.print(" | Voltaje: ");
    Serial.print(voltaje);
    Serial.print(" V | Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");
    


    // LEDs y Servo
    if (temperatura > 37.5) {
      ledcWrite(pwm_channel_rojo, 255);  // LED rojo encendido
      ledcWrite(pwm_channel_amarillo, 0); // LED amarillo apagado
      ledcWrite(pwm_channel_verde, 0);    // LED verde apagado
      mi_servo.write(0);    // Rotar 0 grados
      //verde ->save(0); 
      //rojo ->save(1);
      //amarillo ->save(0);            
    } else if (temperatura > 37.0 && temperatura <= 37.5) {
      ledcWrite(pwm_channel_rojo, 0);     // LED rojo apagado
      ledcWrite(pwm_channel_amarillo, 255); // LED amarillo encendido 
      ledcWrite(pwm_channel_verde, 0);    // LED verde apagado
      mi_servo.write(90); // rotar 90 grados
      //verde ->save(0); 
      //rojo ->save(0);
      //amarillo ->save(1);                    
    } else if(temperatura < 37) {
      ledcWrite(pwm_channel_rojo, 0);     // LED rojo apagado
      ledcWrite(pwm_channel_amarillo, 0); // LED amarillo apagado
      ledcWrite(pwm_channel_verde, 255);  // LED verde encendido 
      mi_servo.write(180);  // rotar 180 grados
      //verde ->save(1); 
      //rojo ->save(0);
      //amarillo ->save(0);                     
    }
    mostrarNumero(temperatura);
    //temperCanal ->save(temperatura);
    delay(5); 

  }
  //delay(5); 
}