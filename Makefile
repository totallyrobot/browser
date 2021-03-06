TARGET=browser
CCFLAGS=-pthread -pipe -W -Wall -g -g3
LIBS=`pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`
LD=gcc
LDFLAGS=-pthread $(LIBS) -export-dynamic
CC=gcc

all: main.o urlbar.o tabs.o paths.o signalhandlers.o
	$(LD) -o $(TARGET) $(LDFLAGS) main.o urlbar.o tabs.o paths.o signalhandlers.o
main.o:
	$(CC) -c $(CCFLAGS) $(LIBS) src/main.c -o main.o
urlbar.o:
	$(CC) -c $(CCFLAGS) $(LIBS) src/urlbar.c -o urlbar.o
tabs.o:
	$(CC) -c $(CCFLAGS) $(LIBS) src/tabs.c -o tabs.o
paths.o:
	$(CC) -c $(CCFLAGS) $(LIBS) src/paths.c -o paths.o
signalhandlers.o:
	$(CC) -c $(CCFLAGS) $(LIBS) src/signalHandlers.c -o signalhandlers.o

clean:
	rm main.o
	rm tabs.o
	rm urlbar.o
	rm paths.o
	rm signalhandlers.o
