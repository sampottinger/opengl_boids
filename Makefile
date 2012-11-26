final: final.c flock.o boid.o physics.o
	gcc -Wall final.c flock.o boid.o physics.o -o final

graphics_test: ./graphics/graphics.c balloon.o ground.o
	gcc -Wall ./graphics/graphics.c balloon.o ground.o objutil.o quadobj.o linalg.o -o graphics_test  -framework GLUT -framework OpenGL

balloon.o: ./graphics/balloon.c objutil.o quadobj.o
	gcc -Wall -c ./graphics/balloon.c -o balloon.o

ground.o: ./graphics/ground.c objutil.o quadobj.o
	gcc -Wall -c ./graphics/ground.c -o ground.o

objutil.o: ./graphics/objutil.c quadobj.o
	gcc -Wall -c ./graphics/objutil.c -o objutil.o

quadobj.o: ./graphics/quadobj.c linalg.o
	gcc -Wall -c ./graphics/quadobj.c -o quadobj.o

linalg.o: ./graphics/linalg.c
	gcc -Wall -c ./graphics/linalg.c -o linalg.o

flock.o: ./flocking/flock.c
	gcc -Wall -c ./flocking/flock.c -o flock.o

boid.o: ./flocking/boid.c physics.o
	gcc -Wall -c ./flocking/boid.c -o boid.o
	gcc -Wall ./flocking/boid_test.c boid.o physics.o -o boid_test
	./boid_test
	rm boid_test

physics.o: ./flocking/physics.c
	gcc -Wall -c ./flocking/physics.c -o physics.o
	gcc -Wall ./flocking/physics_test.c physics.o -o physics_test
	./physics_test
	rm physics_test

clean:
	rm *.o
	rm final