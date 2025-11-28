Sistema IoT para Monitoramento da Qualidade do Ar em SP

Este projeto visa monitorar a qualidade do ar na cidade de São Paulo utilizando conceitos de Internet das Coisas (IoT). O sistema integra dados de sensores locais simulados (ESP32) com dados oficiais de APIs externas, processando as informações para avaliação de riscos à saúde conforme padrões ambientais.

 Tecnologias Utilizadas

Node-RED: Orquestração do fluxo de dados e regras de negócio (Low-code).

ESP32 (Simulado): Coleta de dados de sensores via MQTT.

OpenWeather API: Fonte de dados meteorológicos e de poluição em tempo real.

InfluxDB: Banco de dados temporal para armazenamento histórico.

Grafana: Visualização de dados (Dashboards).

Funcionalidades

Coleta Híbrida: Recebe dados tanto de sensores físicos (simulados) quanto de fontes oficiais.

Semáforo de Qualidade: Classificação automática do ar em "Bom", "Moderado" ou "Ruim" baseada no índice AQI.

Dashboard: Monitoramento visual com histórico e indicadores em tempo real.

 Referências Bibliográficas

As referências abaixo foram utilizadas para embasar os critérios de classificação da qualidade do ar e o alinhamento com objetivos de sustentabilidade globais.

1. Padrões de Qualidade do Ar (Fonte Oficial)

Base para a classificação (Bom/Moderado/Ruim) utilizada no sistema.

CETESB. Padrões de Qualidade do Ar. São Paulo: Companhia Ambiental do Estado de São Paulo. Disponível em: https://cetesb.sp.gov.br/ar/padroes-de-qualidade-do-ar/. Acesso em: 20 nov. 2025.

2. Contexto Local (São Paulo)

Dados sobre a poluição veicular e industrial específica de SP.

IEMA. Qualidade do Ar no Município de São Paulo: Nota Técnica. São Paulo: Instituto de Energia e Meio Ambiente, 2022. Disponível em: https://energiaeambiente.org.br/wp-content/uploads/2022/05/IEMA_notatecnica_aremSP.pdf. Acesso em: 20 nov. 2025.

3. Objetivos de Desenvolvimento Sustentável (ONU)

Justificativa social do projeto (ODS 3 e 11).

ONU. Objetivo de Desenvolvimento Sustentável 3: Saúde e Bem-estar. Nações Unidas Brasil. Disponível em: https://brasil.un.org/pt-br/sdgs/3. Acesso em: 20 nov. 2025.

ONU. Objetivo de Desenvolvimento Sustentável 11: Cidades e Comunidades Sustentáveis. Nações Unidas Brasil. Disponível em: https://brasil.un.org/pt-br/sdgs/11. Acesso em: 20 nov. 2025.

4. Impactos na Saúde

Referência global sobre como a poluição afeta a saúde humana.

WORLD HEALTH ORGANIZATION (WHO). Ambient (outdoor) air pollution. 2024. Disponível em: https://www.who.int/news-room/fact-sheets/detail/ambient-(outdoor)-air-pollution. Acesso em: 20 nov. 2025.
