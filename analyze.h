#ifndef ANALYZE_H
#define ANALYZE_H

namespace analyze {
	void initialize(unsigned int N);
	void terminate();

	void copy(const float* const buffer);
	void execute();

	const float* const get_amplitudes();
	const float* const get_range_values();
}

#endif
