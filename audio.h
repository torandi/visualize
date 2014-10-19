#ifndef AUDIO_H
#define AUDIO_H

namespace audio {

bool initialize(const char* device);
void terminate();

void read();

}

#endif
