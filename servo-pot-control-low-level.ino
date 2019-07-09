#include <Servo.h>

#define POT A0
#define SERVO 9

unsigned int adcOut;
unsigned int adcOutMapped;
Servo meuServo;

void setup() {
  // declarando porta D9 como SAIDA
  //      76543210
  DDRB |= 0b00000010;
  // declarando porta analogica A0 como entrada
  //      76543210  
  DDRC |= 0b0000000;
  // habilitando conversor analogico digital
  // (isso nao inicia uma conversao)
  //        76543210
  ADCSRA |= 10000000;
  // selecionando a entrada A0 no multiplexador do 
  // conversor analogico-digital
  ADMUX |= B00000000;
  // ligando o servo motor ao pino 9
  meuServo.attach(9);
}

void loop() {
  // iniciando a conversao analogico-digital
  ADCSRA |= (1 << ADSC);
  // esperando o fim da conversao
  while((ADCSRA & (1 << ADSC)));
  // armazenando o resultado da conversão
  adcOut = ADC;

  adcOutMapped = map(adcOut, 0, 1023, 0, 180);

  
}
