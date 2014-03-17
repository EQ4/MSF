CC = gcc
CFLAGS = -O0 -g -std=gnu99
LDFLAGS = -pthreads -lm -lao -lpoly
SOURCES = src/main.c src/frame.c src/instrument.c src/ll.c src/phrase.c src/player.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = msf

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
