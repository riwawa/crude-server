#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <sys/socket.h>   // Para a função socket() e bind()
#include <netinet/in.h>    // Para sockaddr_in
#include <arpa/inet.h>     // Para inet_pton()
#include <unistd.h>        // Para close()

class HTTPServer {
private:
    int server_fd;
    const std::string server_name;  // Removido o inicializador aqui
    const std::string http_version = "HTTP/1.1";
    std::map<int, std::string> status_codes;

public:
    HTTPServer() : server_name("CrudeServer") {  // Inicializando no construtor
        // Inicializa o mapa de status HTTP
        status_codes[200] = "OK";
        status_codes[404] = "Not Found";
        status_codes[501] = "Not Implemented";
    }

    void start() {
        struct sockaddr_in address;

        // Cria o socket
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            std::cerr << "Failed to create socket!" << std::endl;
            return;
        }

        // Configura o endereço para bind
        address.sin_family = AF_INET;
        address.sin_port = htons(8888); // Porta 8888
        inet_pton(AF_INET, "127.0.0.1", &address.sin_addr); // Endereço IP 127.0.0.1

        // Faz o bind
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            std::cerr << "Failed to bind!" << std::endl;
            return;
        }

        // Começa a escutar na porta
        if (listen(server_fd, 10) < 0) {
            std::cerr << "Failed to listen!" << std::endl;
            return;
        }

        std::cout << "Server is listening on port 8888..." << std::endl;

        while (true) {
            // Aceita conexões
            int new_socket = accept(server_fd, nullptr, nullptr);
            if (new_socket < 0) {
                std::cerr << "Failed to accept connection!" << std::endl;
                continue;
            }

            // Lê os dados recebidos
            char buffer[1024] = {0};
            read(new_socket, buffer, sizeof(buffer));
            std::string request = buffer;

            // Processa a requisição
            std::string response = handle_request(request);

            // Envia a resposta
            send(new_socket, response.c_str(), response.length(), 0);
            close(new_socket);
        }
    }

private:
    std::string handle_request(const std::string& data) {
        // Simula um método simples de requisição
        if (data.find("GET") != std::string::npos) {
            return handle_GET();
        } else {
            return handle_501();
        }
    }

    std::string handle_GET() {
        std::string response = response_line(200);
        response += response_headers();
        response += "\r\n";
        response += "<html><body><h1>Request Received!</h1></body></html>";
        return response;
    }

    std::string handle_501() {
        std::string response = response_line(501);
        response += response_headers();
        response += "\r\n";
        response += "<html><body><h1>501 Not Implemented</h1></body></html>";
        return response;
    }

    std::string response_line(int status_code) {
        return http_version + " " + std::to_string(status_code) + " " + status_codes[status_code] + "\r\n";
    }

    std::string response_headers() {
        return "Server: " + server_name + "\r\n" +
               "Content-Type: text/html\r\n";
    }
};

int main() {
    HTTPServer server;
    server.start();
    return 0;
}
