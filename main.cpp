#include <cstdio>
#include <sys/time.h>

#include "audio.h"
#include "analyze.h"
#include "render.h"

#define BUFFER_SIZE 1024

unsigned long util_utime() {
	struct timeval cur;
	gettimeofday(&cur, NULL);
	return (unsigned long)(cur.tv_sec * 1000000 + cur.tv_usec);
}

int main(int argc, const char* argv[]) {
	const char* device = nullptr;
	if(argc > 1) device = argv[1];
	audio::initialize(device, BUFFER_SIZE);
	analyze::initialize(BUFFER_SIZE);
	render::initialize(BUFFER_SIZE);
	int frames = 0;
	unsigned long time = util_utime();
	while(true) {
		audio::read();
		analyze::copy(audio::get_buffer());
		analyze::execute();
		if(!render::update()) break;
		render::render(analyze::get_amplitudes());
		++frames;
		unsigned long t = util_utime();
		if(t - time > 2000000)
		{
			float fps = (float)frames / ( (float)(t - time)/1000000.0);
			printf("fps: %f\n", fps);
			time = t;
			frames = 0;
		}
	}
	render::terminate();
	analyze::terminate();
	audio::terminate();
	return 0;
}
