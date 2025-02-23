#pragma once

#include <string>
#include "sim_clock.h"

struct SimAudio {
public:

	SimClock clock;
	
	static const unsigned short debug_max_samples = 600;
	float debug_positions[debug_max_samples];
	float debug_wave_l[debug_max_samples];
	float debug_wave_r[debug_max_samples];
	int debug_pos;

	SimAudio(int systemClockFrequency, bool saveToFile);
	~SimAudio();
	void Clock(signed short left, signed short right);
	void CollectDebug(signed short left, signed short right);
	void Initialise();
	void CleanUp();
};
