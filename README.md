# **Energy Awareness**

## **IoT Dashboard para Monitoramento e Controle de Consumo de Energia**

---

## **Descrição Resumida**

Este projeto IoT monitora e controla o consumo energético em tempo real utilizando um **ESP32** e **Node-RED**. O **ESP32** coleta dados de consumo de energia (simulado com um potenciômetro) e o estado de um LED (ligado/desligado). O **Node-RED** gerencia a comunicação entre os dispositivos via **MQTT** e exibe os dados em um **dashboard interativo**, permitindo o controle remoto do LED e a visualização do consumo de energia.


## **Funcionalidades**

- **Monitoramento de Consumo de Energia**: O valor do consumo de energia é simulado por um potenciômetro e exibido no **gauge** do **Node-RED**.
- **Controle Remoto do LED**: O estado do LED (ligado ou desligado) pode ser alterado remotamente via **MQTT**.
- **Dashboard Interativo**: O **Node-RED** fornece um painel para controlar e monitorar os dados em tempo real.


## **Tecnologias Utilizadas**

### **Hardware:**
- **ESP32**: Microcontrolador que coleta os dados de consumo e controla o LED.
- **LED**: Atuador controlado remotamente.
- **Potenciômetro**: Sensor usado para simular o consumo de energia.

### **Software:**
- **Node-RED**: Plataforma para integração e controle dos dispositivos IoT.
- **MQTT**: Protocolo de comunicação entre o ESP32 e o Node-RED.
- **Wokwi**: Simulador usado para testar o circuito do ESP32 e simular o comportamento do projeto.


## **Configuração do Ambiente**

### **Configuração do ESP32 (para testes)**
- Use o [Wokwi](https://wokwi.com/) para simular o ESP32 ou carregue o código para o ESP32 real.
- O ESP32 publica os dados no **MQTT** e responde aos comandos para ligar/desligar o LED.

**Link do Projeto no Wokwi**: [Energy Awareness Simulation](https://wokwi.com/projects/415114719159456769)


### **Pré-requisitos**
- **Node.js** e **Node-RED** instalados.
- **Broker MQTT**: Utilizamos o broker público **HiveMQ**. Não é necessário instalar um broker localmente.

---

### **Passos para rodar o projeto**

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/santosmgs/GS-EnergyAwarenessIA.git
   cd GS-EnergyAwarenessIA
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
   - Acesse o dashboard interativo do Node-RED: [http://localhost:1880/ui](http://localhost:1880/ui)

3. **Configuração dos tópicos MQTT:**
   - O ESP32 publica dados no tópico `fiap/iot/consumoea`.
   - O Node-RED usa este tópico para receber os dados de consumo e controle do LED.
   - No Node-RED, os nós MQTT são configurados para:
     - Assinar o tópico `fiap/iot/consumoea` para receber dados.
     - Publicar no tópico `fiap/iot/led` para controlar o LED.

4. **Carregar o fluxo do Node-RED:**
   - Importe o arquivo de fluxo JSON do Node-RED, localizado no repositório, para configurar a comunicação e os widgets do dashboard.

5. **Teste o ESP32 (Simulador ou Hardware Real):**
   - No Wokwi, carregue o circuito e o código do ESP32 para simulação.
   - Se usar um ESP32 real, conecte-o ao Wi-Fi e ao broker MQTT.

---

## **Diagrama do Projeto**

### **Descrição do Diagrama**
- O ESP32 lê o valor do potenciômetro, coleta o consumo de energia e publica no broker MQTT.
- O Node-RED se conecta ao broker MQTT, recebe os dados e exibe no dashboard.
- O LED pode ser controlado remotamente via o switch no dashboard, enviando comandos para o ESP32.


## **Passo a Passo de Execução**

1. **Simular o consumo:**
   - Gire o potenciômetro no ESP32 para alterar o consumo de energia.
   - O consumo é exibido no gauge no Node-RED.

2. **Controlar o LED:**
   - Use o switch no dashboard para ligar/desligar o LED.
   - O estado do LED será atualizado no painel e no ESP32.

3. **Verificar os dados:**
   - Confirme que o consumo e o estado do LED estão sendo atualizados em tempo real no dashboard.


## **Documentação do Código**

### **Código do ESP32**
O ESP32 coleta os dados do potenciômetro e publica no MQTT. Ele também escuta comandos MQTT para controlar o LED. O código está organizado com comentários para facilitar o entendimento:

```cpp
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// Configurações de WiFi e MQTT
#define PIN_POTENTIOMETER 34  // Pino do potenciômetro
#define PIN_LED 2             // Pino do LED

void setup() {
  // Inicialização de Wi-Fi e MQTT
}

void loop() {
  // Publicar consumo de energia no MQTT
  // Escutar comandos para o LED
}
```

### **Fluxo do Node-RED**
O fluxo do Node-RED contém:
- Nó MQTT In: Recebe dados de consumo e LED do ESP32.
- Nó Function: Processa os dados JSON e separa consumo e estado do LED.
- Nó Gauge: Exibe o consumo de energia.
- Nó Text: Mostra o estado do LED.
- Nó Switch + MQTT Out: Controla o LED remotamente.


## **Demonstração em Vídeo**

**Link para o vídeo demonstrativo**

O vídeo explica como o Node-RED e o ESP32 interagem, com exemplos de consumo e controle do LED.

---

## **Integrantes do Grupo**

- João Gabriel - RM 552078
- Felipe Morais - RM 551463
- Ian Navas - RM 550133
- Miguel Santos - RM 551640
- Renan Vieira - RM 551813
