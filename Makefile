final: flock.o boid.o physics.o
	gcc -Wall final.c flock.o boid.o physics.o -o final

flock.o: boid.o
	gcc -Wall -c flock.c -o flock.o

boid.o: physics.o
	gcc -Wall -c boid.c -o boid.o

physics.o:
	gcc -Wall -c physics.c -o physics.o