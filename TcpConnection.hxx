#ifndef CONNECTION_HXX
#define CONNECTION_HXX

#include <string>

namespace komancs {
    class TcpConnection
    {
    public:
        enum How { ShutRead, ShutWrite, ShutReadWrite };
        TcpConnection(int);
        ~TcpConnection() { shutdown(); }

        void send(const char *);
        void send(const void *, int);
        void send(const std::string &);
        void receive(char *, int);
        std::string &receive();
        void shutdown(How h = ShutReadWrite);
        bool operator ==(const TcpConnection &c)
        { return m_clientFd == c.descriptor(); }

        void setDescriptor(int fd) { m_clientFd = fd; }
        int descriptor() { return m_clientFd; }

    private:
        TcpConnection(const TcpConnection &);
        TcpConnection &operator =(const TcpConnection &);

        int m_clientFd;
    };
}

#endif // CONNECTION_HXX
