all: lab2 worker broker 

#fworker.o: fworker.c fworker.h
#	gcc -c fworker.c  -lm

#fbroker.o: fbroker.c fbroker.h
#	gcc -c fbroker.c  -lm

worker: worker.c
	g++ worker.c fworker.c -o worker

broker: broker.c
	g++ broker.c fbroker.c -o broker

lab2: lab2.c
	gcc -o lab2 lab2.c -lm

clear:
	rm -f *.o lab2 worker broker fworker fbroker