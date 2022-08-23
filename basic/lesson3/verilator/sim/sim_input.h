#pragma once
#ifndef _MSC_VER
#else
#define WIN32
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#endif
#include "verilated_heavy.h"
#include <queue>
#include <vector>


struct SimInput_PS2KeyEvent {
public:
	char code;
	bool pressed;
	bool extended;
	unsigned int mapped;

	SimInput_PS2KeyEvent(char code, bool pressed, bool extended, unsigned int mapped) {
		this->code = code;
		this->pressed = pressed;
		this->extended = extended;
		this->mapped = mapped;
	}
};

struct SimInput {
public:

	int inputCount = 0;
	bool inputs[16];
	int mappings[16];

	SData* ps2_key = NULL;
	std::queue<SimInput_PS2KeyEvent> keyEvents;
	unsigned int keyEventTimer = 0;
	unsigned int keyEventWait = 50000;

#define NONE         0xFF
#define LCTRL        0x000100
#define LSHIFT       0x000200
#define LALT         0x000400
#define LGUI         0x000800
#define RCTRL        0x001000
#define RSHIFT       0x002000
#define RALT         0x004000
#define RGUI         0x008000
#define MODMASK      0x00FF00
#define OSD          0x010000  // to be used by OSD, not the core itself
#define OSD_OPEN     0x020000  // OSD key not forwarded to core, but queued in arm controller
#define CAPS_TOGGLE  0x040000  // caps lock toggle behaviour
#define EXT          0x080000
#define EMU_SWITCH_1 0x100000
#define EMU_SWITCH_2 0x200000


	void Read();
	int Initialise();
	void CleanUp();
	void SetMapping(int index, int code);
	void BeforeEval(void);
	SimInput(int count, DebugConsole c);
	~SimInput();
};
