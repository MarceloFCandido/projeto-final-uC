
#define POT A0
#define LED 11

unsigned int adcOut;
unsigned int adcOutMapped;

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

void setup() {
  // declarando porta D9 como SAIDA
  //        76543210
  DDRB |= 0b00001000;
  
  // declarando porta analogica A0 como entrada
  //        76543210  
  DDRC |= 0b0000000;
  // habilitando conversor analogico digital
  // (isso nao inicia uma conversao)
  //           76543210
  ADCSRA |= 0b10000000;
  // selecionando a entrada A0 no multiplexador do 
  // conversor analogico-digital
  ADMUX |= 0b00000000;

  setPwmFrequency(LED, 256);

  Serial.begin(9600);
}

void loop() {
//  // iniciando a conversao analogico-digital
//  ADCSRA |= (1 << ADSC);
//  // esperando o fim da conversao
//  while((ADCSRA & (1 << ADSC)) && !(ADCSRA & (1 << ADIF)));
//  // armazenando o resultado da conversão
//  adcOut = ADC;

  adcOut = analogRead(POT);

  adcOutMapped = map(adcOut, 0, 1023, 0, 1000);

  Serial.print("adcOut: ");
  Serial.print(adcOut);
  Serial.print('\n');
  Serial.print("adcOutMapped: ");
  Serial.print(adcOutMapped);
  Serial.print('\n');

  digitalWrite(LED, HIGH);
  delayMicroseconds(adcOutMapped);
  digitalWrite(LED, LOW);
  delayMicroseconds(1000 - adcOutMapped);
  
}