# Global Solution - Edge Computing & IoT
Solucao da Global Solution 2 semestre realizada por:
- Pedro Henrique Batista Bergamin, 559443
- Ícaro de Oliveira Santos, 559950

Mapeia é uma plataforma digital colaborativa desenvolvida para ajudar no combate às enchentes em São Paulo. O sistema permite que cidadãos bueiros entupidos e outros riscos urbanos com localização geográfica e imagens. As informações são enviadas em tempo real para um painel administrativo usado por gestores públicos, permitindo respostas rápidas e baseadas em dados. A solução integra tecnologias como React, Node-RED, Arduino e Python, combinando participação cidadã com automação para tornar as cidades mais seguras e resilientes.

## Video:
Video demonstracao da Global Solution

[Youtube](https://youtu.be/BWQ322RRqx8)

## Componentes
Lista de componentes usados no projeto

- 1x ESP-32
- 1x Board
- 9x Fios 
- 1x Sensor LDR
- 1x Sensor ultrassonico (HC-SR04)

## Como rodar
Acesse o link abaixo:

[Projeto WokiWi](https://wokwi.com/projects/432790418776832001)

Verifique se as bibliotecas abaixo estao instaladas
- WiFi
- PubSubClient

Instale o [Node.js](https://nodejs.org/pt)

Instale o Node-Red atraves do comando:

```JSON
npm i -g node-red
```

Inicie um servidor no Node-Red com:

```JSON
node-red
```

Acesse o link: http://127.0.0.1:1880/ e faca o import dos [flows](./flows.json)
> Atencao, a porta pode mudar, por isso acesse o link fornecido no terminal apos iniciar o node-red

Acesse a dashboard atraves do link: http://127.0.0.1:1880/ui
> Atencao, a porta pode mudar, por isso acesse o link fornecido no terminal apos iniciar o node-red

## Referencias
Principais referencias utilizadas para realizacao do projeto

[Conexao Esp32 - Node-red](https://www.youtube.com/watch?v=fbQRF_IKuo4)

## Fotos do Projeto:

<img src="./circuito.png" style="height:500px;width:550px"/>
<img src="./dashboard.png" style="height:500px;width:950px"/>
