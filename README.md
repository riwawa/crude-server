# Crude Server

Este projeto é uma implementação simples de um servidor HTTP em C++ que utiliza sockets para manipular conexões TCP e responder requisições HTTP. A ideia é entender como funciona um servidor HTTP do zero, sem utilizar bibliotecas de alto nível como frameworks.
Utilizando o tutorial de [Bharat Chauhan](https://bhch.github.io/), [Writing an HTTP Server from Scratch](https://bhch.github.io/posts/2017/11/writing-an-http-server-from-scratch/).

## Objetivo

O principal objetivo deste projeto é aprender mais sobre o funcionamento de servidores HTTP, TCP/IP e como gerenciar conexões em C++. A implementação segue a estrutura básica de um servidor HTTP, onde ele pode lidar com requisições `GET` e retornar respostas de status, como `200 OK`, `404 Not Found`, entre outras.

## Rodando o server...

Se o g++ não estiver instalado, instale-o com:

```
Para Ubuntu/Debian: sudo apt-get install g++\
Para MacOS: brew install gcc
```

Para compilar o servidor HTTP, use o seguinte comando:
```
g++ -Wall -Wextra -g3 crude_server.cpp -o crude_server
```

Após a compilação, execute o servidor com o comando:
```
./crude_server
```

O servidor vai ficar ouvindo na porta 8888 por conexões. Para testar, basta abrir o navegador e acessar:
```
http://127.0.0.1:8888/
```
Isso deverá exibir o conteúdo do arquivo index.html. Para testar o outro arquivo, vá até a URL:
```
http://127.0.0.1:8888/hello
```
