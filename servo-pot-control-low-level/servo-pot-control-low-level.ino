
#define POT A1
#define LED 11

unsigned int adcOut;
unsigned int adcOutMapped;


void setup() {
  // declarando porta D9 como SAIDA
  //        76543210
  DDRB |= 0b00001000;
  // declarando porta analogica A0 como entrada
  //        76543210  
  DDRC |= 0b0000000;
  // habilitando conversor analogico digital
  // (isso nao inicia uma conversao)
  //          76543210
  ADCSRA |= 0b10000000;
  // selecionando a entrada A1 no multiplexador do 
  // conversor analogico-digital
  ADMUX |= 0b00000001;

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

  digitalWrite(LED, HIGH);
  delayMicroseconds(adcOutMapped);
  digitalWrite(LED, LOW);
  delayMicroseconds(1000 - adcOutMapped);
  
}
