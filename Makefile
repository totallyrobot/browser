TARGET=browser
CCFLAGS=-pthread -pipe -W -Wall
LIBS=`pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`
LD=gcc
LDFLAGS=-pthread $(LIBS) -export-dynamic
CC=gcc

all: main.o
	$(LD) -o $(TARGET) $(LDFLAGS) main.o
main.o:
	$(CC) -c $(CCFLAGS) $(LIBS) src/main.c -o main.o
clean:
	rm main.o
