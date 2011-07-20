#ifndef CONNECTION_HXX
#define CONNECTION_HXX

#include <string>

namespace komancs {
    class Connection
    {
    public:
        enum How { ShutRead, ShutWrite, ShutReadWrite };
        Connection(int);
        ~Connection() { shutdown(); }

        void send(const char *);
        void send(const void *, int);
        void send(const std::string &);
        void receive(char *, int);
        std::string &receive();
        void shutdown(How h = ShutReadWrite);
        bool operator ==(const Connection &c)
        { return m_clientFd == c.descriptor(); }

        void setDescriptor(int fd) { m_clientFd = fd; }
        int descriptor() { return m_clientFd; }

    private:
        Connection(const Connection &);
        Connection &operator =(const Connection &);

        int m_clientFd;
    };
}

#endif // CONNECTION_HXX
