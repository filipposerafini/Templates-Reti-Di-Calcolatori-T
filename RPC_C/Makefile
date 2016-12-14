.PHONY:all
all: client server 

gen:
	rpcgen RPC_xFile.x

client: gen
	gcc RPC_Client.c RPC_xFile_clnt.c RPC_xFile_xdr.c -o client

server: gen
	gcc RPC_Server.c RPC_xFile_svc.c RPC_xFile_xdr.c -o server

clean:
	rm server client RPC_xFile.h RPC_xFile_svc.c RPC_xFile_xdr.c RPC_xFile_clnt.c
