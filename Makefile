CXX = g++
RM = rm
SOURCES = Ipv4Address.cxx TcpConnection.cxx TcpServer.cxx main.cxx

all:
	$(CXX) $(SOURCES) -o komancs

clean:
	$(RM) komancs	
