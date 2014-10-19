#include <cstdio>

#include "audio.h"

int main(int argc, const char* argv[]) {
	const char* device = nullptr;
	if(argc > 1) device = argv[1];
	audio::initialize(device);
	while(true) { audio::read(); }
	audio::terminate();
	return 0;
}
