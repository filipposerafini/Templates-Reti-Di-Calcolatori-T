.PHONY: all
all: server udp tcp

server:
	gcc Select_Server.c -o server

udp:
	gcc Select_Datagram_Client.c -o udp_client

tcp:
	gcc Select_Stream_Client.c -o tcp_client

clean:
	rm server udp_client tcp_client
