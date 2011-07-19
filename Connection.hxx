#ifndef CONNECTION_HXX
#define CONNECTION_HXX

#include <cstring>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace komancs {
    class Connection
    {
    public:
        enum How { ShutRead, ShutWrite, ShutReadWrite };
        Connection(int, struct sockaddr_in *);
        ~Connection() { shutdown(); delete m_address; }

        void send(const char *);
        void send(const void *, int);
        void send(const std::string &);
        void receive(char *, int);
        std::string &receive();
        void setDescriptor(int fd) { m_clientFd = fd; }
        void setAddress(struct sockaddr_in *addr)
            { m_address = addr; }
        void shutdown(How h = ShutReadWrite);

    private:
        int m_clientFd;
        struct sockaddr_in *m_address;
    };
}

#endif // CONNECTION_HXX
