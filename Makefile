LDLIBS += $(shell pkg-config --libs libpulse-simple)
CXXFLAGS += -std=c++0x $(shell pkg-config --cflags libpulse-simple)

all: visualize

visualize: main.o audio.o
	g++ $(LDFLAGS) -o visualize main.o audio.o $(LDLIBS)

main.o: main.cpp audio.h

audio.o: audio.cpp audio.h

clean:
	rm -f visualize *.o

.PHONY: clean
