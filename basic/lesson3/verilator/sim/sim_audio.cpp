#include "sim_audio.h"
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

SimClock clk;
bool outputToFile;
ofstream audioFile;

SimAudio::SimAudio(int systemClockFrequency, bool saveToFile)
{
	clk = SimClock(systemClockFrequency / 44100);
	outputToFile = saveToFile;
}

SimAudio::~SimAudio()
{

}

void SimAudio::Clock(signed short left, signed short right) {
	clk.Tick();
	if (clk.IsRising()) {
		// Output audio (left channel only for now)
		float l = left / 32768.0f;
		if (outputToFile) {
			audioFile.write((const char*)&l, sizeof(float));
		}
	}
}

void SimAudio::CollectDebug(signed short left, signed short right) {
	float vol_l = left / 32768.0f;
	float vol_r = right / 32768.0f;
	debug_pos++;
	if (debug_pos == debug_max_samples) { debug_pos = 0; }
	debug_wave_l[debug_pos] = vol_l;
	debug_wave_r[debug_pos] = vol_r;

}

void SimAudio::Initialise() {
	// Reset plot data
	for (int c = 0; c < debug_max_samples; c++) {
		debug_wave_l[c] = 0;
		debug_wave_r[c] = 0;
		debug_positions[c] = (double)c / (double)debug_max_samples;
	}
	if (outputToFile)
	{
		// Setup Audio output stream
		audioFile.open("audio.wav", ios::binary);
	}
}
void SimAudio::CleanUp() {
	if (outputToFile)
	{
		audioFile.close();
	}
}

