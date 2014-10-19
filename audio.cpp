#include "audio.h"

#include <pulse/simple.h>
#include <pulse/error.h>
#include <cstdio>

namespace audio {

pa_simple* hndl;

bool initialize(const char* device) {
	pa_sample_spec ss;
	//pa_buffer_attr attr;
	int err;

	ss.format = PA_SAMPLE_S16NE;
	ss.channels = 2;
	ss.rate = 44100;

	//attr.maxlength = ;
	//attr.fragsize = BUFSIZE;

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
}

void read() {
	int16_t buffer[512];
	int err;
	if(pa_simple_read(hndl, &buffer, sizeof(buffer), &err) < 0) {
		printf("Failed to read sound: %s\n", pa_strerror(err));
	} else {
		for(int i=0; i<512; ++i) {
			printf("%d ", buffer[i]);
			if(i%10 == 9) printf("\n");
		}
	}
}


}
