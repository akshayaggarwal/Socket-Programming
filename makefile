all:
	gcc -o serverAA serverA.c -lsocket -lnsl -lresolv
	gcc -o serverBB serverB.c -lsocket -lnsl -lresolv
	gcc -o serverCC serverC.c -lsocket -lnsl -lresolv
	gcc -o awss aws.c -lsocket -lnsl -lresolv
	gcc -o client client.c -lsocket -lnsl -lresolv
.PHONY: serverA serverB serverC aws

serverA:
	./serverAA 21034

serverB:
	./serverBB 22034

serverC:
	./serverCC 23034

aws:	
	./awss 25034
