# Energy Awareness

## IoT Dashboard para Monitoramento e Controle de Consumo de Energia

## Descrição Resumida
Este projeto IoT monitora e controla o consumo energético em tempo real utilizando um ESP32 e Node-RED. O ESP32 coleta dados de consumo de energia (simulado com um potenciômetro) e o estado de um LED (ligado/desligado). O Node-RED gerencia a comunicação entre os dispositivos via MQTT e exibe os dados em um dashboard interativo, permitindo o controle remoto do LED e a visualização do consumo de energia.

## Funcionalidades
- **Monitoramento de Consumo de Energia**: O valor do consumo de energia é simulado por um potenciômetro e exibido no gauge do Node-RED.
- **Controle Remoto do LED**: O estado do LED (ligado ou desligado) pode ser alterado remotamente via MQTT.
- **Dashboard Interativo**: O Node-RED fornece um painel para controlar e monitorar os dados em tempo real.

## Tecnologias Utilizadas

### Hardware:
- **ESP32**: Microcontrolador que coleta os dados de consumo e controla o LED.
- **LED**: Atuador controlado remotamente.
- **Potenciômetro**: Sensor usado para simular o consumo de energia.

### Software:
- **Node-RED**: Plataforma para integração e controle dos dispositivos IoT.
- **MQTT**: Protocolo de comunicação entre o ESP32 e o Node-RED.
- **Wokwi**: Simulador usado para testar o circuito do ESP32 e simular o comportamento do projeto.

## Configuração do Ambiente

### Pré-requisitos:
- Node.js e Node-RED instalados.
- Broker MQTT: Utilizamos o broker HiveMQ para a comunicação MQTT. Não é necessário instalar um broker localmente, pois usamos o broker público.

### Passos para rodar o projeto:
1. **Clone o repositório:**
   ```bash
   git clone https://github.com/seu-usuario/nome-do-repositorio.git
   cd nome-do-repositorio
   ```

2. **Configuração do Node-RED:**
   - Instale o Node-RED se ainda não tiver:
     ```bash
     npm install -g --unsafe-perm node-red
     ```
   - Inicie o Node-RED:
     ```bash
     node-red
     ```
   - Acesse o Node-RED no navegador: [http://localhost:1880](http://localhost:1880).

3. **Configuração dos tópicos MQTT:**
   - O ESP32 publica dados no tópico `fiap/iot/consumoea`.
   - O Node-RED usa este tópico para receber os dados de consumo e controle do LED.
   - No Node-RED, os nós MQTT são configurados para assinar o tópico `fiap/iot/consumoea` e publicar no tópico `fiap/iot/led`.

4. **Carregar o fluxo do Node-RED:**
   - Importe o fluxo do Node-RED que está no repositório para configurar a comunicação e os widgets do dashboard.

5. **Configuração do ESP32 (para testes):**
   - Use o Wokwi para simular o ESP32 ou carregue o código para o ESP32 real.
   - O ESP32 publica os dados no MQTT e responde aos comandos para ligar/desligar o LED.

## Diagrama do Projeto

### Descrição do Diagrama:
- O ESP32 lê o potenciômetro, coleta o consumo e envia os dados para o broker MQTT.
- O Node-RED se conecta ao broker MQTT, recebe os dados e os exibe no dashboard.
- O LED pode ser controlado através do switch no dashboard, enviando comandos via MQTT.

## Passo a Passo de Execução
1. **Gire o potenciômetro no ESP32**: Simule o consumo de energia no painel do Node-RED (gauge).
2. **Controle o LED**: Use o switch no Node-RED para ligar ou desligar o LED. O estado será refletido no painel do dashboard e no ESP32.
3. **Verifique os dados**: O consumo e o estado do LED são atualizados em tempo real no dashboard do Node-RED.

## Documentação do Código

### Código do ESP32:
O código do ESP32 coleta os dados do potenciômetro e publica no MQTT. Ele também escuta o tópico do LED para controlar seu estado. O código foi comentado para descrever cada etapa:

```cpp
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// Configurações de WiFi e MQTT
// Defina o SSID e a senha do Wi-Fi
// Broker MQTT: broker.hivemq.com
// Tópicos MQTT: fiap/iot/consumoea e fiap/iot/led

// Configuração do Hardware
#define PIN_POTENTIOMETER 34  // Pino analógico para o potenciômetro
#define PIN_LED 2             // Pino para o LED

void setup() {
  // Inicialização do Wi-Fi e MQTT
}

void loop() {
  // Lê o valor do potenciômetro, mapeia para consumo e publica no MQTT
  // Escuta comandos MQTT para controlar o LED
}
```

### Código do Node-RED:
O fluxo do Node-RED é composto por:
- Nó MQTT In para receber dados de consumo e controle do LED.
- Nó Function para processar os dados JSON e separar o consumo e o estado do LED.
- Nó Gauge para mostrar o consumo de energia.
- Nó Text para mostrar o estado do LED.
- Nó Switch e MQTT Out para controlar o LED.

## Demonstração em Vídeo
[Link para o vídeo demonstrativo](#)

O vídeo de 3 minutos apresenta o funcionamento do Node-RED e a interação com o ESP32, mostrando como os dados são coletados, processados e visualizados no dashboard.
```
LINK YOUTUBE
```

## Integrantes do grupo
- João Gabriel - RM
- Felipe Morais - RM
- Ian Navas - RM
- Miguel Santos - RM
- Renan Vieira - RM
