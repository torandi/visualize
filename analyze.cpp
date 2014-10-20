#include "analyze.h"
#include <fftw3.h>
#include <cmath>
#include <complex>
#include <algorithm>

namespace analyze {

std::complex<float>* in;
std::complex<float>* out;
float* amplitude;

fftwf_plan plan;

unsigned int buffer_size;

float inv_n;

float clamp(float v, float low, float high) {
	return std::max(std::min(v, high), low);
}

void initialize(unsigned int N) {
	printf("Initializing fftw for DFT of size %d.\n", N);

	buffer_size = N;
	inv_n = 1.f / (float)buffer_size;

	in = static_cast<std::complex<float>*>(fftwf_malloc(sizeof(fftwf_complex) * N));
	out = static_cast<std::complex<float>*>(fftwf_malloc(sizeof(fftwf_complex) * N));
	plan = fftwf_plan_dft_1d(N, reinterpret_cast<fftwf_complex*>(in), reinterpret_cast<fftwf_complex*>(out), FFTW_FORWARD, FFTW_MEASURE);

	amplitude = new float[buffer_size/2];
}

void terminate() {
	fftwf_destroy_plan(plan);
	fftwf_free(in);
	fftwf_free(out);

	delete[] amplitude;
}

void copy(const float* const buffer) {
	for(unsigned int i=0; i<buffer_size; ++i) {
		in[i] = std::complex<float>(buffer[i], 0.f);
	}
}

void execute() {
	fftwf_execute(plan);

	// Calculate amplitude
	for(unsigned int i=0; i<buffer_size/2; ++i) {
		amplitude[i] = clamp(log10(std::abs(out[i]) * inv_n), -100, 100);
	}
}

void print() {
	for(unsigned int i=0; i<buffer_size; ++i) {
		printf("%f ", amplitude[i]);
	}
	printf("\n");
}

const float* const get_amplitudes() {
	return amplitude;
}

}
