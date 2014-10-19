#ifndef AUDIO_H
#define AUDIO_H

namespace audio {

bool initialize(const char* device, unsigned int N);
void terminate();

void read();

const float* const get_buffer();

}

#endif
