#include "sim_clock.h"
#include <string>

SimClock::SimClock() {
	ratio = 1;
	count = 0;
	clk = false;
	old = false;
}

SimClock::SimClock(int r) {
	ratio = r;
	count = 0;
	clk = false;
	old = false;
}


SimClock::~SimClock() {
}

void SimClock::Tick() {
	old = clk;
	count++;
	if (count > ratio) {
		count = 0;
	}
	clk = (count == 0);
}

void SimClock::Reset() {
	count = 0;
	clk = false;
	old = false;
}

bool SimClock::IsRising() {
	return clk && !old;
}
