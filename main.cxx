#include <iostream>
#include "locale.h"
#include "TcpServer.hxx"
#include "TcpConnection.hxx"
#include "Ipv4Address.hxx"
#include "Exceptions.hxx"

int main()
{
    setlocale(LC_ALL, "");
    try {
        komancs::Ipv4Address local(komancs::Any, 3000);
        std::cout << "Starting Komancs Webserver...\n\nListening for connections at port 3000...\n\n";
        komancs::TcpServer serv(&local);
        komancs::TcpConnection *c = 0;
        char buffer[800];
        buffer[799] = '\0';
        while (1) {
            c = serv.accept();
            c->receive(buffer, 199);
            c->send("HTTP/1.1 200 OK\r\n\r\n<html><head><title>It works!</title></head><body><h1>Hello, world!</h1>"
                    "<hr><i>Powered by Komancs Webserver</i><br><i>Copyleft (C) Akos Kovacs"
                    "</i></body></html>\r\n\r\n");
            delete c;
            std::cout << "Received: " << buffer << std::endl;
        }
    } catch (komancs::error::Exception &e) {
        std::cout << e.what() << std::endl;
    }
}
