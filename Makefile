final: ./graphics/graphics.c balloon.o ground.o bird.o flock.o errcheck.o fatal.o loadtexbmp.o
	gcc -g -Wall ./graphics/graphics.c balloon.o flock.o bird.o ground.o objutil.o quadobj.o linalg.o boid.o physics.o errcheck.o fatal.o loadtexbmp.o -o final -lglut -lGLU

flock.o: ./graphics/flock.c
	gcc -g -Wall -c ./graphics/flock.c -o flock.o

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

boid.o: ./flocking/boid.c physics.o
	gcc -g -Wall -c ./flocking/boid.c -o boid.o

physics.o: ./flocking/physics.c
	gcc -g -Wall -c ./flocking/physics.c -o physics.o

errcheck.o: ./errcheck.c
	gcc -g -Wall -c ./errcheck.c -o errcheck.o

fatal.o: ./fatal.c
	gcc -g -Wall -c ./fatal.c -o fatal.o

loadtexbmp.o: ./loadtexbmp.c
	gcc -g -Wall -c ./loadtexbmp.c -o loadtexbmp.o

clean:
	rm *.o
	rm final