<h1 align='center'>
    Arduino Wine Quality Monitor
<h1>

<h3> 
    Este é um projeto de monitoramento de qualidade de vinhos usando Arduino, desenvolvido para atender às necessidades de uma vinícola tradicional que busca expandir seus negócios para o comércio eletrônico, mantendo a mesma experiência de qualidade oferecida em sua loja física.
</h3>

<p align="center">
  <a href="#participantes">Participantes</a> |
  <a href="#objetivos">Objetivos</a> |
  <a href="#hardware-utilizado">Hardware Utilizado</a> |
  <a href="#funcionamento-do-código">Funcionamento do Código</a> |
  <a href="#instalação-e-utilização">Instalação e Utilização</a> |
  <a href="#aviso">Aviso</a> 
</p>

![tinkercad-checkpoint1](img/wokwi_checkpoint_2.png)

## Participantes
* João Henrique Sena Hoffmann (RM550763)
* Lucas Ludovico Cabral (RM554589)
* Vinicius Fernandes Tavares Bittencourt (RM558909)
* Weslley Oliveira Cardoso (RM557927)

## Objetivos
O objetivo deste projeto é capturar a iluminação, temperatura e humidade no ambiente de armazenamento de vinhos e monitorar a qualidade com base nesse fator. Um local adequado para a armazenagem dos vinhos é um fator crítico na preservação da qualidade, e este sistema visa alertar os responsáveis quando algum desses fatores estiver fora dos níveis recomendados.

## Hardware Utilizado
* Arduino Uno
* Sensor de temperatura e umidade (DHT22)
* Sensor de Luminosidade (LDR)
* LEDs (Verde, Amarelo e Vermelho)
* Buzzer
* Display LCD 16x2

## Funcionamento do Código
O código lê os valores do sensor de temperatura e humidade (DHT22), verificando se os valores recebidos estão entre a faixa adequada para o armazenamento dos vinhos. O mesmo ocorre com o sensor de luminosidade (LDR), nele os valores são convertidos em porcentagem, representando a intensidade da luz no ambiente. Com base em todos esses aspectos há um sistema que, ao receber valores fora da faixa recomendada, acende os LEDs e toca um buzzer, além de apresentar os valores no display lcd implantado.
O código é executado em um loop contínuo, monitorando constantemente a temperatura, humidade e iluminação no ambiente, e fornecendo feedback visual e sonoro sobre a qualidade da mesma.

## Instalação e Utilização
* Conecte os componentes conforme o esquema de ligação.
* Carregue o código para a placa Arduino.
* Certifique-se de que o sensor de temperatura e humidade esteja posicionado em um local representativo do ambiente de armazenamento de vinhos.
* Certifique-se de que o sensor de luminosidade esteja posicionado em um local representativo da iluminação do ambiente de armazenamento de vinhos.
* Ligue a alimentação da placa Arduino.
* Observe o display, os LEDs e ouça o buzzer para determinar a qualidade da iluminação ambiente.

## Aviso
Este projeto é uma prova de conceito e deve ser adaptado e aprimorado conforme as necessidades específicas da aplicação e do ambiente de uso.