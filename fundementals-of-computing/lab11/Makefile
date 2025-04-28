battleship: project.o battlefunc.o gfx2.o
	gcc project.o battlefunc.o gfx2.o -o project -lX11

project.o: project.c battlefunc.h gfx2.h
	gcc -c project.c -o project.o

battlefunc.o: battlefunc.c battlefunc.h gfx2.h
	gcc -c battlefunc.c -o battlefunc.o

run: project
	./project

clean:
	rm *.o
	rm project
