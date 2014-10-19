LDLIBS += $(shell pkg-config --libs libpulse-simple) -lfftw3f -lm -lSDL -lSDL_gfx
CXXFLAGS += -std=c++0x $(shell pkg-config --cflags libpulse-simple)

all: visualize

visualize: main.o audio.o analyze.o render.o
	g++ $(LDFLAGS) -o visualize main.o audio.o analyze.o render.o $(LDLIBS)

main.o: main.cpp audio.h analyze.h render.h

audio.o: audio.cpp audio.h

analyze.o: analyze.cpp analyze.h

render.o: render.cpp render.h

clean:
	rm -f visualize *.o

.PHONY: clean
