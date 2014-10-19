#ifndef RENDER_H
#define RENDER_H

namespace render {

void initialize(unsigned int N);
void terminate();

bool update();
void render(const float* const amplitudes);

}

#endif
