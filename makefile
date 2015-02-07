CC := clang
# CC := gcc # for wingnuts
CFLAGS := -fvisibility=hidden
CPPFLAGS := -std=gnu11 -Iinc

#CPPFLAGS := $(CPPFLAGS) -Wall -Wextra
#CPPFLAGS := $(CPPFLAGS) -Weverything
CPPFLAGS := $(CPPFLAGS) -w

#CFLAGS := $(CFLAGS) -ggdb
CFLAGS := $(CFLAGS) -O2

LDFLAGS :=
LIBRARIES := -lpoly `pkg-config --cflags --static --libs allegro-static-5 allegro_acodec-static-5 allegro_ttf-static-5 allegro_font-static-5 allegro_audio-static-5 allegro_color-static-5 allegro_dialog-static-5 allegro_image-static-5 allegro_main-static-5 allegro_primitives-static-5`

SOURCES := $(wildcard src/*.c) $(wildcard src/editor/*.c)
OBJECTS := $(SOURCES:.c=.o)
EDITOR_EXEC := msf

.PHONY: all clean

all: $(EDITOR_EXEC)

clean:
	$(RM) $(OBJECTS) $(EDITOR_EXEC)

$(EDITOR_EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)

.c.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
