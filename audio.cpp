#include "audio.h"

#include <pulse/simple.h>
#include <pulse/error.h>
#include <cstdio>

namespace audio {

pa_simple* hndl;
static unsigned int buffer_size;

float* buffer;

bool initialize(const char* device, unsigned int N) {
	printf("Initializing pulse audio.\n");
	pa_sample_spec ss;
	pa_buffer_attr attr;
	int err;

	buffer_size = N;

	buffer = new float[buffer_size];

	ss.format = PA_SAMPLE_FLOAT32NE;
	ss.channels = 1;
	ss.rate = 44100;

	attr.maxlength = N*sizeof(float);
	attr.fragsize = N*sizeof(float);

	hndl = pa_simple_new(NULL,
	                     "Frobnicators Visualizer",
						 PA_STREAM_RECORD,
						 device,
						 "Capture Stream",
						 &ss,
						 NULL,
						 NULL,
						 &err);
	if(hndl == nullptr) {
		printf("Failed to initialize pulse audio, %s (%d)\n", pa_strerror(err), err);
		return false;
	}
	return true;

}

void terminate() {
	if(hndl == nullptr) return;
	pa_simple_free(hndl);

	delete[] buffer;
}

void read() {
	int err;
	if(pa_simple_read(hndl, buffer, buffer_size * sizeof(float), &err) < 0) {
		printf("Failed to read sound: %s\n", pa_strerror(err));
	}/* else {
		for(int i=0; i<1024; ++i) {
			printf("%f ", buffer[i]);
			if(i%16 == 15) printf("\n");
		}
	}*/
}

const float* const get_buffer() { return buffer; }


}
