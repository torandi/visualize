#include <cstdio>

#include "audio.h"
#include "analyze.h"
#include "render.h"

#define BUFFER_SIZE 1024

int main(int argc, const char* argv[]) {
	const char* device = nullptr;
	if(argc > 1) device = argv[1];
	audio::initialize(device, BUFFER_SIZE);
	analyze::initialize(BUFFER_SIZE);
	render::initialize(BUFFER_SIZE);
	while(true) {
		audio::read();
		analyze::copy(audio::get_buffer());
		analyze::execute();
		if(!render::update()) break;
		render::render(analyze::get_amplitudes());
	}
	render::terminate();
	analyze::terminate();
	audio::terminate();
	return 0;
}
