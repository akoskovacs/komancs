#ifndef TCP_SERVER_HXX
#define TCP_SERVER_HXX

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace komancs
{
    class Connection;
    class TcpServer
    {
    public:
        TcpServer(int); 
        ~TcpServer();
        void bind();
        void setPort(int);
        void listen(int);
        Connection *accept();

    private:
        int m_port;
        int m_fd;
        struct ::sockaddr_in m_address;
    };
}

#endif // TCP_SERVER_HXX
