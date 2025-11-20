Projeto IoT: Monitoramento da Qualidade do Ar em São Paulo

Este documento descreve a implementação técnica do sistema de monitoramento de qualidade do ar, integrando sensores virtuais (ESP32), API externa (OpenWeather), processamento em Node-RED, armazenamento em InfluxDB e visualização em Grafana.

1. Arquitetura da Solução

Fontes de Dados:

API OpenWeather: Fornece dados reais de qualidade do ar (PM2.5, PM10, CO, etc.) para a latitude/longitude de São Paulo.

Arduino Virtual (Wokwi + ESP32): Simula um sensor local enviando dados via MQTT.

Middleware (Node-RED):

Assina tópicos MQTT do ESP32.

Realiza requisições HTTP periódicas à API.

Aplica Regras de Negócio (Avaliação da qualidade: Bom, Moderado, Ruim).

Formata e envia dados para o banco.

Armazenamento (InfluxDB): Banco de dados de séries temporais.

Visualização (Grafana): Dashboards para análise histórica e tempo real.

2. Configuração do Node-RED

O Node-RED atua como o "cérebro" da operação. Ele possui três responsabilidades principais:

A. Coleta da API OpenWeather

Nó Inject: Dispara a cada 10 ou 30 minutos.

Nó HTTP Request:

URL: http://api.openweathermap.org/data/2.5/air_pollution?lat=-23.5505&lon=-46.6333&appid={SUA_API_KEY}

Método: GET

Nó Function: Extrai o índice AQI (Air Quality Index) e componentes poluentes.

B. Coleta do Arduino (MQTT)

Nó MQTT In: Conecta ao broker (ex: test.mosquitto.org ou local) no tópico sp/sensor/qualidade.

Nó JSON: Converte a string recebida em objeto JavaScript.

C. Regra de Negócio (Semáforo)

No Node-RED, aplicamos a lógica de classificação baseada no AQI (Índice de Qualidade do Ar):

AQI 1-2 (Ótimo/Bom): Status "Bom" (Cor Verde).

AQI 3 (Moderado): Status "Moderado" (Cor Amarela).

AQI 4-5 (Ruim/Péssimo): Status "Ruim" (Cor Vermelha).

3. Configuração do Dashboard (Grafana)

O Grafana deve ser conectado ao InfluxDB (DataSource) para gerar os painéis solicitados:

Painel 1: Gráfico de Linha (Histórico)

Tipo: Time Series.

Query A: SELECT mean("aqi") FROM "ar_sp_api" WHERE time > now() - 24h GROUP BY time(1h) (Dados da API).

Query B: SELECT mean("valor_sensor") FROM "ar_sp_sensor" WHERE time > now() - 24h GROUP BY time(1h) (Dados do Arduino).

Objetivo: Comparar a "qualidade média" (sensor local) com a "qualidade oficial" (API) ao longo do tempo.

Painel 2: Valor Atual (Gauge)

Tipo: Gauge.

Query: SELECT last("aqi") FROM "ar_sp_api".

Objetivo: Mostrar o valor numérico instantâneo do AQI em SP.

Painel 3: Semáforo (Stat / Traffic Light)

Tipo: Stat (com Background Color habilitado) ou Plugin "Traffic Light".

Mapeamento de Cores (Thresholds):

0 a 2: Verde (Positivo/Ótimo).

3: Amarelo (Neutro/Atenção).

4 a 5: Vermelho (Negativo/Crítico).

4. Documentação e Referências

Conforme solicitado para o projeto acadêmico, seguem as referências formatadas e as citações baseadas no documento objetos_inteligentes_conectados.pdf.

Citações para o Trabalho

"A qualidade do ar é um dos principais fatores que afetam o bem-estar da população em grandes metrópoles. Em São Paulo, a poluição atmosférica é marcada por ser um dos maiores desafios ambientais e de saúde pública." (Igari et al., 2025, p. 1).

"O projeto busca demonstrar como soluções de Internet das Coisas (IoT) podem auxiliar a sociedade ao fornecer dados acessíveis e em tempo real sobre a qualidade do ar, promovendo conscientização e subsidiando políticas públicas." (Igari et al., 2025, p. 1).

