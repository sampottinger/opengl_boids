final: flock.o boid.o physics.o
	gcc -Wall final.c flock.o boid.o physics.o -o final

flock.o: flock.c
	gcc -Wall -c flock.c -o flock.o

boid.o: boid.c physics.o
	gcc -Wall -c boid.c -o boid.o
	gcc -Wall boid_test.c boid.o physics.o -o boid_test
	./boid_test
	rm boid_test

physics.o: physics.c
	gcc -Wall -c physics.c -o physics.o
	gcc -Wall physics_test.c physics.o -o physics_test
	./physics_test
	rm physics_test

clean:
	rm *.o
	rm final