Sistema IoT para Monitoramento da Qualidade do Ar em SP

Este projeto visa monitorar a qualidade do ar na cidade de São Paulo utilizando conceitos de Internet das Coisas (IoT). O sistema integra dados de sensores locais simulados (ESP32) com dados oficiais de APIs externas, processando as informações para avaliação de riscos à saúde conforme padrões ambientais.

 Tecnologias Utilizadas

Node-RED: Orquestração do fluxo de dados e regras de negócio (Low-code).

![Imagem do WhatsApp de 2025-11-24 à(s) 02 45 02_6e7623dd](https://github.com/user-attachments/assets/5604f084-9f01-466e-b231-e389a3b4bf95)


OpenWeather API: Fonte de dados meteorológicos e de poluição em tempo real.

InfluxDB: Banco de dados temporal para armazenamento histórico.

ESP32 (ATUADOR): Receptor de dados de sensores via MQTT.

![Imagem do WhatsApp de 2025-11-24 à(s) 02 45 25_4c72a8ec](https://github.com/user-attachments/assets/91601f00-b6da-4431-bc05-695d9f0e9c93)


ESP32 (SENSOR): Coletor de dados de sensores via MQTT.
<img width="827" height="770" alt="image" src="https://github.com/user-attachments/assets/b1a74348-3071-4feb-9a3b-0ba206290f4c" />


Grafana: Visualização de dados (Dashboards).

![Imagem do WhatsApp de 2025-11-24 à(s) 02 45 15_059b1764](https://github.com/user-attachments/assets/e45c524a-1b07-4f86-bdab-58824ad1b2a9)


Funcionalidades

Coleta Híbrida: Recebe dados tanto de sensores físicos (simulados) quanto de fontes oficiais.

Semáforo de Qualidade: Classificação automática do ar em "Bom", "Moderado" ou "Ruim" baseada no índice AQI.

Dashboard: Monitoramento visual com histórico e indicadores em tempo real.




