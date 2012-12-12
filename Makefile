final: ./graphics/graphics.c balloon.o ground.o sky.o tree.o bird.o flock.o errcheck.o fatal.o loadtexbmp.o
	gcc -g -Wall ./graphics/graphics.c balloon.o flock.o bird.o ground.o sky.o tree.o objutil.o quadobj.o linalg.o boid.o physics.o errcheck.o fatal.o loadtexbmp.o -o final  -framework GLUT -framework OpenGL

flock.o: ./graphics/flock.c
	gcc -g -Wall -c ./graphics/flock.c -o flock.o

bird.o: ./graphics/bird.c boid.o
	gcc -g -Wall -c ./graphics/bird.c -o bird.o

balloon.o: ./graphics/balloon.c objutil.o quadobj.o
	gcc -g -Wall -c ./graphics/balloon.c -o balloon.o

sky.o: ./graphics/sky.c objutil.o quadobj.o
	gcc -g -Wall -c ./graphics/sky.c -o sky.o

tree.o: ./graphics/tree.c objutil.o quadobj.o
	gcc -g -Wall -c ./graphics/tree.c -o tree.o

ground.o: ./graphics/ground.c objutil.o quadobj.o
	gcc -g -Wall -c ./graphics/ground.c -o ground.o

objutil.o: ./graphics/objutil.c quadobj.o
	gcc -g -Wall -c ./graphics/objutil.c -o objutil.o

quadobj.o: ./graphics/quadobj.c linalg.o
	gcc -g -Wall -c ./graphics/quadobj.c -o quadobj.o

linalg.o: ./graphics/linalg.c physics.o
	gcc -g -Wall -c ./graphics/linalg.c -o linalg.o

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

errcheck.o: ./errcheck.c
	gcc -g -Wall -c ./errcheck.c -o errcheck.o

fatal.o: ./fatal.c
	gcc -g -Wall -c ./fatal.c -o fatal.o

loadtexbmp.o: ./loadtexbmp.c
	gcc -g -Wall -c ./loadtexbmp.c -o loadtexbmp.o

clean:
	rm *.o
	rm -rf *.dSYM
	rm final