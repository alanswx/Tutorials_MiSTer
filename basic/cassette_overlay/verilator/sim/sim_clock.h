#pragma once

class SimClock
{

public:
	bool clk, old;

	SimClock(int r);
	~SimClock();
	void Tick();
	void Reset();

private:
	int ratio, count;
};