Sistema IoT para Monitoramento da Qualidade do Ar em SP

A cidade de São Paulo enfrenta desafios constantes relacionados à poluição atmosférica, afetando a saúde pública. O monitoramento oficial muitas vezes carece de capilaridade (poucas estações para uma área enorme) e os dados nem sempre são traduzidos em alertas visuais imediatos para a população local.

Este projeto implementa uma arquitetura de IoT (Internet das Coisas) híbrida que combina:

Sensoriamento Local (Edge): Dispositivos ESP32 capturam dados microclimáticos.

Dados Oficiais (Cloud): Integração com a API OpenWeather para validação e enriquecimento dos dados.

Atuação Visual: Feedback físico imediato sobre a qualidade do ar via sinalização luminosa (semáforo).

O objetivo é democratizar o acesso à informação de qualidade do ar, permitindo a correlação entre dados coletados localmente e dados macroclimáticos.

O sistema segue uma arquitetura baseada em eventos utilizando o protocolo MQTT para comunicação leve e desacoplada.

A camada de hardware é baseada no microcontrolador ESP32, simulado via Wokwi, dividido em dois nós funcionais distintos.

Nó Sensor (Data Collector)
Responsável pela aquisição de dados brutos.

Hardware: ESP32 DevKit V1.

Periféricos Simulados:

DHT22: Leitura de Temperatura (°C) e Umidade (%).

Potenciômetro (Simulando MQ-135): Leitura analógica convertida para PPM (Partículas por Milhão) de CO2/Gases.

Protocolo de Comunicação: MQTT sobre TCP/IP.

Tópico de Publicação: sp/sensor/metrica

<img width="745" height="759" alt="image" src="https://github.com/user-attachments/assets/c08f4f07-615f-4865-a836-b8f20fb486f9" />

Nó Atuador (Alert System)
Responsável pela interface visual com o usuário local.

Hardware: ESP32 DevKit V1.

Periféricos: 3 LEDs (Verde, Amarelo, Vermelho).

Lógica de Operação: O dispositivo atua como um "Subscriber" passivo. Ele não decide a qualidade do ar; apenas executa o comando recebido do orquestrador.

Tópico de Subscrição: sp/alerta/comando

Payload Esperado (String): "BOM", "MODERADO", "RUIM".

<img width="578" height="522" alt="image" src="https://github.com/user-attachments/assets/d111f6ba-4d86-47fe-a6df-248e622d9079" />

O Node-RED atua como o Middleware e motor de regras do sistema. Ele elimina a necessidade de processamento complexo nos microcontroladores.

Fluxo de Integração
Entrada MQTT: O nó mqtt-in escuta o tópico dos sensores.

Entrada HTTP: Um nó http-request consulta a OpenWeather API a cada 10 minutos (para evitar rate-limiting) buscando dados de air_pollution baseados em latitude/longitude de SP.

<img width="916" height="235" alt="image" src="https://github.com/user-attachments/assets/5087439c-ecc7-43b5-9230-0b1bd5050fd8" />

Saídas de Dados
Persistência: Os dados tratados são formatados e enviados para o nó influxdb-out.

Regras de Negócio (Function Node)
O sistema utiliza um algoritmo de classificação baseado no índice AQI (Air Quality Index). A lógica implementada em JavaScript dentro do Node-RED segue a seguinte tabela de decisão:

Faixa AQI / CO2 (ppm),Classificação,Ação no Atuador,Risco à Saúde
AQI 1-2 ou CO2 < 600,BOM,LED Verde (High),Baixo
AQI 3 ou CO2 600-1000,MODERADO,LED Amarelo (High),Atenção para grupos sensíveis
AQI 4-5 ou CO2 > 1000,RUIM,LED Vermelho (High),Alerta de saúde geral

Comando: Baseado na classificação acima, uma mensagem é publicada no tópico sp/alerta/comando para acionar o hardware.

InfluxDB (Time Series Database)
Optou-se por um banco de dados temporal devido à natureza sequencial dos dados de sensores.
Bucket: monitoramento_sp
Measurement: qualidade_ar
Tags:
source: "sensor_local" ou "api_openweather"
location: "centro_sp"
Fields: temperatura, umidade, co2, aqi_index.

Visualização (Grafana)
A camada de apresentação consome dados diretamente do InfluxDB.
Indicadores Instantâneos : Exibem o último valor lido de Temperatura e CO2 para leitura rápida.
Gráficos de Histórico (Time Series): Permitem visualizar a evolução da poluição nas últimas 6, 12 ou 24 horas, facilitando a identificação de picos de poluição em horários de trânsito intenso.
Comparativo Híbrido: Um painel dedicado compara o dado "Real" (Sensor) com o dado "Estimado" (API) para fins de calibração.
