#ifndef TCP_CONNECTION_HXX
#define TCP_CONNECTION_HXX

#include <string>

#include "InetGlobals.hxx"
#include "Ipv4Address.hxx"

namespace komancs {
    class TcpConnection
    {
    public:
        enum How { ShutRead, ShutWrite, ShutReadWrite };
        TcpConnection(int, const Ipv4Address &);
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
        int descriptor() const { return m_clientFd; }
        const Ipv4Address &address() const { return m_address; }

    private:
        TcpConnection(const TcpConnection &);
        TcpConnection &operator =(const TcpConnection &);

        int m_clientFd;
        Ipv4Address m_address;
    };
}

#endif // TCP_CONNECTION_HXX
