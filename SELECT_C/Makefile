.PHONY: all
all: server udp tcp

server:
	gcc Select_Server.c -o server

datagram:
	gcc Select_Client_Datagram.c -o datagram_client

stream:
	gcc Select_Client_Stream.c -o stream_client

clean:
	rm server udp_client tcp_client
