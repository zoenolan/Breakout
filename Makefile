CC = g++
CFLAGS = -pipe -fpic -O3 -DSHM -o tester

INCLUDES = -I/usr/local/include

GL_LIBS = -L/usr/local/lib -lMesaaux -lMesatk -lMesaGLU -lMesaGL
X11_LIBS = -L/usr/X11R6/lib -lX11 -lXext
EXTRA_LIBS = -lm
LIBS = $(GL_LIBS) $(X11_LIBS) $(EXTRA_LIBS)

CFLAGS = $(INCLUDES) $(LIBS) -o tester

test:main.o colour.o vector.o cube.o main.o object.o line.o surface.o ball.o timer.o
	$(CC) $(CFLAGS) vector.o colour.o main.o cube.o object.o line.o surface.o ball.o timer.o

main.o:main.cpp
	$(CC) -c main.cpp

colour.cpp:colour.h
	touch colour.cpp

colour.o:colour.cpp
	$(CC) -c colour.cpp

vector.cpp:vector.h
	touch vector.cpp

vector.o:vector.cpp
	$(CC) -c vector.cpp

cube.cpp:cube.h
	touch cube.cpp

cube.o:cube.cpp
	$(CC) -c cube.cpp

ball.cpp:ball.h
	touch ball.cpp

ball.o:ball.cpp
	$(CC) -c ball.cpp

timer.cpp:timer.h
	touch timer.cpp

timer.o:timer.cpp
	$(CC) -c timer.cpp

line.cpp:line.h vector.h
	touch line.cpp

line.o:line.cpp
	$(CC) -c line.cpp

object.cpp:object.h
	touch object.cpp

object.o:object.cpp
	$(CC) -c object.cpp

surface.cpp:surface.h
	touch surface.cpp

surface.o:surface.cpp
	$(CC) -c surface.cpp

main.cpp:
	touch main.cpp
