final: final.c flock.o boid.o physics.o
	gcc -g -Wall final.c flock.o boid.o physics.o -o final

graphics_test: ./graphics/graphics.c balloon.o ground.o bird.o
	gcc -g -Wall ./graphics/graphics.c balloon.o bird.o ground.o objutil.o quadobj.o linalg.o boid.o physics.o -o graphics_test  -framework GLUT -framework OpenGL

bird.o: ./graphics/bird.c boid.o
	gcc -g -Wall -c ./graphics/bird.c -o bird.o

balloon.o: ./graphics/balloon.c objutil.o quadobj.o
	gcc -g -Wall -c ./graphics/balloon.c -o balloon.o

ground.o: ./graphics/ground.c objutil.o quadobj.o
	gcc -g -Wall -c ./graphics/ground.c -o ground.o

objutil.o: ./graphics/objutil.c quadobj.o
	gcc -g -Wall -c ./graphics/objutil.c -o objutil.o

quadobj.o: ./graphics/quadobj.c linalg.o
	gcc -g -Wall -c ./graphics/quadobj.c -o quadobj.o

linalg.o: ./graphics/linalg.c
	gcc -g -Wall -c ./graphics/linalg.c -o linalg.o

flock.o: ./flocking/flock.c
	gcc -g -Wall -c ./flocking/flock.c -o flock.o

boid.o: ./flocking/boid.c physics.o
	gcc -g -Wall -c ./flocking/boid.c -o boid.o
	gcc -g -Wall ./flocking/boid_test.c boid.o physics.o -o boid_test
	./boid_test
	rm boid_test

physics.o: ./flocking/physics.c
	gcc -g -Wall -c ./flocking/physics.c -o physics.o
	gcc -g -Wall ./flocking/physics_test.c physics.o -o physics_test
	./physics_test
	rm physics_test

clean:
	rm *.o
	rm final