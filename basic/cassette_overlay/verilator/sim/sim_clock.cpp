#include "sim_clock.h"
#include <string>

//bool clk, old;
//int ratio, count;

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
	if (count >= ratio) {
		clk = !clk; count = 0;
	}
}

void SimClock::Reset() {
	count = 0;
	clk = false;
	old = false;
}
