#ifndef HOST_HXX
#define HOST_HXX

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace komancs {
    enum HostType {
          Any = INADDR_ANY
        , None = INADDR_NONE
        , LoopBack = INADDR_LOOPBACK
        , BroadCast = INADDR_BROADCAST };

    class Ipv4Address
    {
    public:
        Ipv4Address(const Ipv4Address &);
        Ipv4Address(const struct ::sockaddr_in &);
        Ipv4Address(const char *ip, int port);
        Ipv4Address(HostType type, int port);
        void setPort(int);
        void setAddress(const char *);
        void setAddress(const struct ::sockaddr_in &);
        void setHostType(HostType);
        const struct ::sockaddr_in &address() const { return m_address; }
        struct ::sockaddr_in *addressPointer() { return &m_address; }
        size_t size() const { return sizeof(m_address); }
        Ipv4Address &operator =(const Ipv4Address &);
        bool operator ==(const Ipv4Address &);

    private:
        void init();
        struct ::sockaddr_in m_address;
    };
}

#endif // HOST_HXX
