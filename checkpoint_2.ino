// DECLARANDO BIBLIOTECAS USADAS NO DISPLAY LCD E NO SENSOR DHT
#include <LiquidCrystal.h>
#include "DHT.h"

// DECLARANDO PINO E TIPO NO SENSOR DHT
#define pinDHT 6
#define typeDHT DHT22

// DECLARANDO PINOS DO LED E DO BUZZER
#define ledGreen 7
#define ledYellow 8
#define ledRed 9
#define buzzer A1

// DECLARANDO PINO DO SENSOR LDR
#define pinLDR A0

// INICIANDO OBJETO PARA COMUNICAÇÃO COM O DHT E COM O DISPLAY LCD
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
DHT dht(pinDHT, typeDHT);

// DECLARANDO VARIÁVEL DE SOMA, USADA EM TODAS AS FUNÇÕES
float sum;

// DECLARANDO VARIÁVEIS REFERENTES A LEITURA DE TEMPEMPERATURA E HUMIDADE
float temperature;
int humidity;
float readings_temp[5];
int readings_humid[5];
int index_temp = 0;
int index_humid = 0;

// DECLARANDO VARIÁVEIS REFERENTES A LEITURA DA LUMINOSIDADE
int valueLDR;
int valueLight;
int index_light = 0;
int readings_light[5];

// DEFININDO CARACTERES PERSONALIZADOS PARA MOSTRAR NO DISPLAY LCD
byte top1[8] = { B00000, B00000, B00000, B00001, B00010, B00010, B00100, B01000 };
byte top2[8] = { B00000, B00000, B11111, B00000, B00000, B00000, B00000, B00100 };
byte top3[8] = { B00000, B00000, B11000, B00100, B00010, B00001, B00001, B00001 };
byte base1[8] = { B00000, B00000, B00001, B00010, B00010, B00100, B01000, B10000 };
byte base2[8] = { B10000, B10000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte base3[8] = { B00100, B00110, B00001, B00010, B00010, B00001, B00000, B00000 };
byte base4[8] = { B00001, B00010, B10010, B01100, B00000, B00000, B10000, B01100 };
byte degree[8] = { B00110, B01001, B00110, B00000, B00000, B00000, B00000, B00000 };


void setup()
{
  // INICIANDO COMUNICAÇÃO COM MONITOR SERIAL, DISPLAY LCD E DHT
  Serial.begin(9600);
  lcd.begin(16,2);   
  dht.begin();

  // CRIANDO OS CARACTERES DECLARADOS ANTERIORMENTE
  lcd.createChar(1, top1);
  lcd.createChar(2, top2);
  lcd.createChar(3, top3);
  lcd.createChar(4, base1);
  lcd.createChar(5, base2);
  lcd.createChar(6, base3);
  lcd.createChar(7, base4);
  lcd.createChar(8, degree);

  // FAZENDO A SAÍDA DOS PINOS LED E ENTRADA DO PINO LDR
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pinLDR, INPUT);

  // CHAMANDO FUNÇÃO PARA EXECUTAR A LOGO DO DISPLAY LCD E LIMPANDO O LCD
  dynamicLogo();
  lcd.clear();
}

void loop()
{
  // CHAMANDO FUNÇÕES PARA CHECAR LUMINOSIDADE, TEMPERATURA E HUMIDADE
  checkingLighting();
  checkingAmbience();
  delay(100);
}

// CRIANDO FUNÇÃO PARA ANIMAR A LOGO
void dynamicLogo(){
  lcd.clear();                  
  lcd.setCursor(6,0);           
  lcd.print("TECH");    
  lcd.setCursor(6,1);           
  lcd.print("WAVE");
  delay(1000);
  
  // LIMPANDO CASAS ONDE A ANIMAÇÃO JÁ FOI FEITA
  for(int x=0; x<16; x++){
    delay(250);
    lcd.setCursor(x,0);
    lcd.write(" ");
    lcd.setCursor(x-1,1);
    lcd.write(" ");

    // MOSTRANDO A ONDA NO DISPLAY LCD
    lcd.setCursor(x+1,0);
    lcd.write(byte(1));
    lcd.write(byte(2));
    lcd.write(byte(3));
    lcd.setCursor(x,1);
    lcd.write(byte(4));
    lcd.write(byte(5));
    lcd.write(byte(6));
    lcd.write(byte(7));
  }
}

// CRIANDO FUNÇÃO PARA CHECAR TEMPERATURA E HUMIDADE
void checkingAmbience(){
  delay(100);

  // FAZENDO A LEITURA E MÉDIA DA TEMPERATURA 
  readings_temp[index_temp] = dht.readTemperature();
  index_temp = (index_temp + 1) % 5;
  sum = 0;
  for(int x = 0; x < 5; x++){
    sum += readings_temp[x];
  }
  temperature = sum / 5;

  // FAZENDO A LEITURA E MÉDIA DA HUMIDADE
  readings_humid[index_humid] = dht.readHumidity();
  index_humid = (index_humid + 1) % 5;
  sum = 0;
  for(int x = 0; x < 5; x++){
    sum += readings_humid[x];
  }
  humidity = sum / 5;

  // CONDICIONAL CASO OS VALORES ACIMA NÃO SEJAM NÚMEROS
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // CONDICIONAL PARA EXECUTAR CASO JÁ TENHA FEITO 5 LEITURAS
  if(index_temp == 4){
    lcd.clear();
    lcd.setCursor(0,0);

    // CONDICIONAL PARA SABER SE A TEMPERATURA ESTÁ ENTRE O IDEAL
    if(temperature >= 10 && temperature <= 15){

      // APRESENTANDO TEMPERATURA NO DISPLAY LCD
      lcd.print("Temp. BOA");
      lcd.setCursor(0,1);
      lcd.print("Temp. = ");
      lcd.print(temperature);
      lcd.setCursor(12,1);

      // APAGANDO DEMAIS LEDs E LIGANDO VERDE
      digitalWrite(ledRed, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledGreen, HIGH);

    // CASO ESTEJA TEMPERATURA ESTEJA ACIMA ENTRA NESSE BLOCO
    } else if(temperature > 15){

      // APRESENTANDO TEMPERATURA NO DISPLAY LCD
      lcd.print("Temp. ALTA");
      lcd.setCursor(0,1);
      lcd.print("Temp. = ");
      lcd.print(temperature);
      lcd.setCursor(12,1);

      // APAGANDO DEMAIS LEDs E LIGANDO AMARELO
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledYellow, HIGH);

      // CHAMANDO A FUNÇÃO PARA TOCAR O BUZZER
      buzzerYellow();

    // CASO A TEMPERATURA ESTEJA ABAIXO ENTRA NESSE BLOCO
    } else{

      // APRESENTANDO TEMPERATURA NO DISPLAY LCD
      lcd.print("Temp. BAIXA");
      lcd.setCursor(0,1);
      lcd.print("Temp. = ");
      lcd.print(temperature);
      lcd.setCursor(11,1);

      // APAGANDO DEMAIS LEDs E LIGANDO AMARELO
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledYellow, HIGH);

      // CHAMANDO A FUNÇÃO PARA TOCAR O BUZZER
      buzzerYellow();
    }

    lcd.write(8);
    lcd.print("C");
    delay(3000);
  }

  // CONDICIONAL PARA EXECUTAR CASO JÁ TENHA FEITO 5 LEITURAS
  if(index_humid == 4){
    lcd.clear();
    lcd.setCursor(0,0);

    // CONDICIONAL PARA SABER SE A HUMIDADE ESTÁ ENTRE O IDEAL
    if(humidity >= 50 && humidity <= 70){
      lcd.print("Umidade BOA");

      // APAGANDO DEMAIS LEDs E LIGANDO VERDE
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, HIGH);

    // CASO ESTEJA HUMIDADE ESTEJA ACIMA ENTRA NESSE BLOCO
    } else if(humidity > 70){
      lcd.print("Umidade ALTA");

      // APAGANDO DEMAIS LEDs E LIGANDO VERMELHO
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, HIGH);

      // LIGANDO BUZZER
      digitalWrite(buzzer, HIGH);

    // CASO ESTEJA HUMIDADE ESTEJA ABAIXO ENTRA NESSE BLOCO
    } else{

      // APRESENTANDO CONDIÇÃO DA HUMIDADE 
      lcd.print("Umidade BAIXA");

      // APAGANDO DEMAIS LEDs E LIGANDO VERMELHO
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, HIGH);

      // LIGANDO BUZZER
      digitalWrite(buzzer, HIGH);
    }

    // APRESENTANDO VALOR DA HUMIDADE NO DISPLAY LCD
    lcd.setCursor(0,1);
    lcd.print("Umidade = ");
    lcd.print(humidity);
    lcd.print("%");
    delay(3000);

    // DESLIGANDO BUZZER
    digitalWrite(buzzer, LOW);
  }
}

// FUNÇÃO PARA CHECAR ILUMINAÇÃO
void checkingLighting(){
  delay(100);

  // FAZENDO LEITURA E MÉDIA DOS VALORES DO LDR
  readings_light[index_light] = analogRead(pinLDR);
  index_light = (index_light + 1) % 5;
  sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += readings_light[i];
  }
  valueLDR = sum / 5;

  // FAZENDO MAPEAMENTO DOS VALORES PARA PORCENTAGEM
  valueLight = map(valueLDR, 1015, 840, 0, 100);

  // CONDICIONAL PARA EXECUTAR CASO JÁ TENHA FEITO 5 LEITURAS
  if(index_light == 4){
    lcd.clear();
    lcd.setCursor(4,0);

    // CONDICIONAL PARA SABER SE A ILUMINAÇÃO ESTÁ ABAIXO DE 65% (IDEAL)
    if(valueLight <= 65){

      // APAGANDO DEMAIS LEDs E LIGANDO VERDE
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, HIGH);
    
    // CASO ILUMINAÇÃO ESTEJA ENTRE 65% E 90% ENTRA NESSE BLOCO
    } else if(valueLight > 65 && valueLight <= 90){

      // APRESENTANDO CONDIÇÃO DA ILUMINAÇÃO NO DISPLAY LCD
      lcd.print("Ambiente");
      lcd.setCursor(4,1);
      lcd.print("Meia Luz");

      // APAGANDO DEMAIS LEDs E LIGANDO AMARELO
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledYellow, HIGH);
    
      // CHAMANDO FUNÇÃO PARA TOCAR BUZZER
      buzzerYellow();
    
    // CASO ILUMINAÇÃO ESTEJA MAIOR QUE 90% ENTRA NESSE BLOCO
    } else{
      
      // APRESENTANDO CONDIÇÃO DA ILUMINAÇÃO NO DISPLAY LCD
      lcd.print("Ambiente");
      lcd.setCursor(2,1);
      lcd.print("Muito Claro");

      // APAGANDO DEMAIS LEDs E LIGANDO VERMELHO
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, HIGH);

      // LIGANDO E DESLIGANDO BUZZER
      digitalWrite(buzzer, HIGH);
      delay(3000);
      digitalWrite(buzzer, LOW);
    }
  }
}

// FUNÇÃO PARA TOCAR BUZZER COM PAUSAS
void buzzerYellow(){

  // EXECUTANDO BLOCO DURANTE 3 CICLOS
  for(int x=1; x <= 3; x++){
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(1000);
  }
}