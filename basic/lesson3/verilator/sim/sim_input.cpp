#include "sim_input.h"

#include <string>
#include <stdlib.h>

#ifndef _MSC_VER
#include <SDL2/SDL.h>
int m_keyboardStateCount;
const Uint8* m_keyboardState;
Uint8* m_keyboardState_last = NULL;
#else
#define WIN32
#include <dinput.h>
//#define DIRECTINPUT_VERSION 0x0800
IDirectInput8* m_directInput;
IDirectInputDevice8* m_keyboard;
unsigned char m_keyboardState[256];
unsigned char m_keyboardState_last[256];
#endif

#include <vector>
#include "sim_console.h"

static DebugConsole console;

#ifdef WIN32
static const unsigned int ev2ps2[] =
{
	NONE, //0   KEY_RESERVED
	0x76, //1   KEY_ESC
	0x16, //2   KEY_1
	0x1e, //3   KEY_2
	0x26, //4   KEY_3
	0x25, //5   KEY_4
	0x2e, //6   KEY_5
	0x36, //7   KEY_6
	0x3d, //8   KEY_7
	0x3e, //9   KEY_8
	0x46, //10  KEY_9
	0x45, //11  KEY_0
	0x4e, //12  KEY_MINUS
	0x55, //13  KEY_EQUAL
	0x66, //14  KEY_BACKSPACE
	0x0d, //15  KEY_TAB
	0x15, //16  KEY_Q
	0x1d, //17  KEY_W
	0x24, //18  KEY_E
	0x2d, //19  KEY_R
	0x2c, //20  KEY_T
	0x35, //21  KEY_Y
	0x3c, //22  KEY_U
	0x43, //23  KEY_I
	0x44, //24  KEY_O
	0x4d, //25  KEY_P
	0x54, //26  KEY_LEFTBRACE
	0x5b, //27  KEY_RIGHTBRACE
	0x5a, //28  KEY_ENTER
	 0x14, //29  KEY_LEFTCTRL
	0x1c, //30  KEY_A
	0x1b, //31  KEY_S
	0x23, //32  KEY_D
	0x2b, //33  KEY_F
	0x34, //34  KEY_G
	0x33, //35  KEY_H
	0x3b, //36  KEY_J
	0x42, //37  KEY_K
	0x4b, //38  KEY_L
	0x4c, //39  KEY_SEMICOLON
	0x52, //40  KEY_APOSTROPHE
	0x0e, //41  KEY_GRAVE
	 0x12, //42  KEY_LEFTSHIFT
	0x5d, //43  KEY_BACKSLASH
	0x1a, //44  KEY_Z
	0x22, //45  KEY_X
	0x21, //46  KEY_C
	0x2a, //47  KEY_V
	0x32, //48  KEY_B
	0x31, //49  KEY_N
	0x3a, //50  KEY_M
	0x41, //51  KEY_COMMA
	0x49, //52  KEY_DOT
	0x4a, //53  KEY_SLASH
	 0x59, //54  KEY_RIGHTSHIFT
	0x7c, //55  KEY_KPASTERISK
	 0x11, //56  KEY_LEFTALT
	0x29, //57  KEY_SPACE
	0x58, //58  KEY_CAPSLOCK
	0x05, //59  KEY_F1
	0x06, //60  KEY_F2
	0x04, //61  KEY_F3
	0x0c, //62  KEY_F4
	0x03, //63  KEY_F5
	0x0b, //64  KEY_F6
	0x83, //65  KEY_F7
	0x0a, //66  KEY_F8
	0x01, //67  KEY_F9
	0x09, //68  KEY_F10
	EMU_SWITCH_2 | 0x77, //69  KEY_NUMLOCK
	EMU_SWITCH_1 | 0x7E, //70  KEY_SCROLLLOCK
	0x6c, //71  KEY_KP7
	0x75, //72  KEY_KP8
	0x7d, //73  KEY_KP9
	0x7b, //74  KEY_KPMINUS
	0x6b, //75  KEY_KP4
	0x73, //76  KEY_KP5
	0x74, //77  KEY_KP6
	0x79, //78  KEY_KPPLUS
	0x69, //79  KEY_KP1
	0x72, //80  KEY_KP2
	0x7a, //81  KEY_KP3
	0x70, //82  KEY_KP0
	0x71, //83  KEY_KPDOT
	NONE, //84  ???
	NONE, //85  KEY_ZENKAKU
	0x61, //86  KEY_102ND
	0x78, //87  KEY_F11
	0x07, //88  KEY_F12
	NONE, //89  KEY_RO
	NONE, //90  KEY_KATAKANA
	NONE, //91  KEY_HIRAGANA
	NONE, //92  KEY_HENKAN
	NONE, //93  KEY_KATAKANA
	NONE, //94  KEY_MUHENKAN
	NONE, //95  KEY_KPJPCOMMA
	EXT | 0x5a, //96  KEY_KPENTER
	 EXT | 0x14, //97  KEY_RIGHTCTRL
	EXT | 0x4a, //98  KEY_KPSLASH
	0xE2, //99  KEY_SYSRQ
	 EXT | 0x11, //100 KEY_RIGHTALT
	NONE, //101 KEY_LINEFEED
	EXT | 0x6c, //102 KEY_HOME
	EXT | 0x75, //103 KEY_UP
	EXT | 0x7d, //104 KEY_PAGEUP
	EXT | 0x6b, //105 KEY_LEFT
	EXT | 0x74, //106 KEY_RIGHT
	EXT | 0x69, //107 KEY_END
	EXT | 0x72, //108 KEY_DOWN
	EXT | 0x7a, //109 KEY_PAGEDOWN
	EXT | 0x70, //110 KEY_INSERT
	EXT | 0x71, //111 KEY_DELETE
	NONE, //112 KEY_MACRO
	NONE, //113 KEY_MUTE
	NONE, //114 KEY_VOLUMEDOWN
	NONE, //115 KEY_VOLUMEUP
	NONE, //116 KEY_POWER
	NONE, //117 KEY_KPEQUAL
	NONE, //118 KEY_KPPLUSMINUS
	0xE1, //119 KEY_PAUSE
	NONE, //120 KEY_SCALE
	NONE, //121 KEY_KPCOMMA
	NONE, //122 KEY_HANGEUL
	NONE, //123 KEY_HANJA
	NONE, //124 KEY_YEN
	 EXT | 0x1f, //125 KEY_LEFTMETA
	 EXT | 0x27, //126 KEY_RIGHTMETA
	NONE, //127 KEY_COMPOSE
	NONE, //128 KEY_STOP
	NONE, //129 KEY_AGAIN
	NONE, //130 KEY_PROPS
	NONE, //131 KEY_UNDO
	NONE, //132 KEY_FRONT
	NONE, //133 KEY_COPY
	NONE, //134 KEY_OPEN
	NONE, //135 KEY_PASTE
	NONE, //136 KEY_FIND
	NONE, //137 KEY_CUT
	NONE, //138 KEY_HELP
	NONE, //139 KEY_MENU
	NONE, //140 KEY_CALC
	NONE, //141 KEY_SETUP
	NONE, //142 KEY_SLEEP
	NONE, //143 KEY_WAKEUP
	NONE, //144 KEY_FILE
	NONE, //145 KEY_SENDFILE
	NONE, //146 KEY_DELETEFILE
	NONE, //147 KEY_XFER
	NONE, //148 KEY_PROG1
	NONE, //149 KEY_PROG2
	NONE, //150 KEY_WWW
	NONE, //151 KEY_MSDOS
	NONE, //152 KEY_SCREENLOCK
	NONE, //153 KEY_DIRECTION
	NONE, //154 KEY_CYCLEWINDOWS
	NONE, //155 KEY_MAIL
	NONE, //156 KEY_BOOKMARKS
	NONE, //157 KEY_COMPUTER
	NONE, //158 KEY_BACK
	NONE, //159 KEY_FORWARD
	NONE, //160 KEY_CLOSECD
	NONE, //161 KEY_EJECTCD
	NONE, //162 KEY_EJECTCLOSECD
	NONE, //163 KEY_NEXTSONG
	NONE, //164 KEY_PLAYPAUSE
	NONE, //165 KEY_PREVIOUSSONG
	NONE, //166 KEY_STOPCD
	NONE, //167 KEY_RECORD
	NONE, //168 KEY_REWIND
	NONE, //169 KEY_PHONE
	NONE, //170 KEY_ISO
	NONE, //171 KEY_CONFIG
	NONE, //172 KEY_HOMEPAGE
	NONE, //173 KEY_REFRESH
	NONE, //174 KEY_EXIT
	NONE, //175 KEY_MOVE
	NONE, //176 KEY_EDIT
	NONE, //177 KEY_SCROLLUP
	NONE, //178 KEY_SCROLLDOWN
	NONE, //179 KEY_KPLEFTPAREN
	NONE, //180 KEY_KPRIGHTPAREN
	NONE, //181 KEY_NEW
	NONE, //182 KEY_REDO
	NONE, //183 KEY_F13
	NONE, //184 KEY_F14
	NONE, //185 KEY_F15
	NONE, //186 KEY_F16
	EMU_SWITCH_1 | 1, //187 KEY_F17
	EMU_SWITCH_1 | 2, //188 KEY_F18
	EMU_SWITCH_1 | 3, //189 KEY_F19
	EMU_SWITCH_1 | 4, //190 KEY_F20
	NONE, //191 KEY_F21
	NONE, //192 KEY_F22
	NONE, //193 KEY_F23
	0x5D, //194 U-mlaut on DE mapped to backslash
	NONE, //195 ???
	NONE, //196 ???
	NONE, //197 ???
	NONE, //198 ???
	NONE, //199 ???
	EXT | 0x75, //200 KEY_UP
	NONE, //201 ???
	NONE, //202 ???
	EXT | 0x6b, //203 KEY_LEFT
	NONE, //204 ???
	EXT | 0x74, //205 KEY_RIGHT
	NONE, //206 ???
	NONE, //207 ???
	EXT | 0x72, //208 KEY_DOWN
	NONE, //209 ???
	NONE, //210 ???
	NONE, //211 ???
	NONE, //212 ???
	NONE, //213 ???
	NONE, //214 ???
	NONE, //215 ???
	NONE, //216 ???
	NONE, //217 ???
	NONE, //218 ???
	NONE, //219 ???
	NONE, //220 ???
	NONE, //221 ???
	NONE, //222 ???
	NONE, //223 ???
	NONE, //224 ???
	NONE, //225 ???
	NONE, //226 ???
	NONE, //227 ???
	NONE, //228 ???
	NONE, //229 ???
	NONE, //230 ???
	NONE, //231 ???
	NONE, //232 ???
	NONE, //233 ???
	NONE, //234 ???
	NONE, //235 ???
	NONE, //236 ???
	NONE, //237 ???
	NONE, //238 ???
	NONE, //239 ???
	NONE, //240 ???
	NONE, //241 ???
	NONE, //242 ???
	NONE, //243 ???
	NONE, //244 ???
	NONE, //245 ???
	NONE, //246 ???
	NONE, //247 ???
	NONE, //248 ???
	NONE, //249 ???
	NONE, //250 ???
	NONE, //251 ???
	NONE, //252 ???
	NONE, //253 ???
	NONE, //254 ???
	NONE  //255 ???
};
#else
static const int ev2ps2[] =
{
	NONE, //0   KEY_RESERVED
	NONE, //1   KEY_RESERVED
	NONE, //2   KEY_RESERVED
	NONE, //3   KEY_RESERVED
	0x1c, //4  KEY_A
	0x32, //5  KEY_B
	0x21, //6  KEY_C
	0x23, //7  KEY_D
	0x24, //8  KEY_E
	0x2b, //9  KEY_F
	0x34, //10  KEY_G
	0x33, //11  KEY_H
	0x43, //12  KEY_I
	0x3b, //13  KEY_J
	0x42, //14  KEY_K
	0x4b, //15  KEY_L
	0x3a, //16  KEY_M
	0x31, //17  KEY_N
	0x44, //18  KEY_O
	0x4d, //19  KEY_P
	0x15, //20  KEY_Q
	0x2d, //21  KEY_R
	0x1b, //22  KEY_S
	0x2c, //23  KEY_T
	0x3c, //24  KEY_U
	0x2a, //25  KEY_V
	0x1d, //26  KEY_W
	0x22, //27  KEY_X
	0x35, //28  KEY_Y
	0x1a, //29  KEY_Z
	0x16, //30   KEY_1
	0x1e, //31   KEY_2
	0x26, //32  KEY_3
	0x25, //33  KEY_4
	0x2e, //34  KEY_5
	0x36, //35  KEY_6
	0x3d, //36  KEY_7
	0x3e, //37  KEY_8
	0x46, //38  KEY_9
	0x45, //39  KEY_0
	0x5a, //40  KEY_ENTER
	0x76, //41  KEY_ESC
	0x66, //42  KEY_BACKSPACE
	0x0d, //43  KEY_TAB
	0x29, //44  KEY_SPACE
	0x4e, //45  KEY_MINUS
	0x55, //46  KEY_EQUAL
	0x54, //47  KEY_LEFTBRACE
	0x5b, //48  KEY_RIGHTBRACE
	0x5d, //49  KEY_BACKSLASH
	NONE, //50  KEY_RESERVED
	0x4c, //51  KEY_SEMICOLON
	0x52, //52  KEY_APOSTROPHE
	0x0e, //53  KEY_GRAVE
	0x41, //54  KEY_COMMA
	0x49, //55  KEY_DOT
	0x4a, //56  KEY_SLASH
	0x58, //57  KEY_CAPSLOCK
	0x05, //58  KEY_F1
	0x06, //59  KEY_F2
	0x04, //60  KEY_F3
	0x0c, //61  KEY_F4
	0x03, //62  KEY_F5
	0x0b, //63  KEY_F6
	0x83, //64  KEY_F7
	0x0a, //65  KEY_F8
	0x01, //66  KEY_F9
	0x09, //67  KEY_F10
	0x78, //68  KEY_F11
	0x07, //69  KEY_F12
	NONE, //70  KEY_PRINT
	EMU_SWITCH_1 | 0x7E, //71  KEY_SCROLLLOCK
	0xE1, //72 KEY_PAUSE
	EXT | 0x70, //73  KEY_INSERT
	EXT | 0x6c, //74  KEY_HOME
	EXT | 0x7d, //75  KEY_PAGEUP
	EXT | 0x71, //76  KEY_DELETE
	EXT | 0x69, //77  KEY_END
	EXT | 0x7a, //78  KEY_PAGEDOWN
	EXT | 0x74, //79  KEY_RIGHT
	EXT | 0x6b, //80  KEY_LEFT
	EXT | 0x72, //81  KEY_DOWN
	EXT | 0x75, //82  KEY_UP
	EMU_SWITCH_2 | 0x77, //83  KEY_NUMLOCK
	EXT | 0x4a, //84  KEY_KPSLASH
	0x7c, //85  KEY_KPASTERISK
	0x7b, //86  KEY_KPMINUS
	0x79, //87  KEY_KPPLUS
	EXT | 0x5a, //88  KEY_KPENTER
	0x69, //89  KEY_KP1
	0x72, //90  KEY_KP2
	0x7a, //91  KEY_KP3
	0x6b, //92  KEY_KP4
	0x73, //93  KEY_KP5
	0x74, //94  KEY_KP6
	0x6c, //95  KEY_KP7
	0x75, //96  KEY_KP8
	0x7d, //97  KEY_KP9
	0x70, //98  KEY_KP0
	0x71, //99  KEY_KPDOT
	NONE, //100 ???
	NONE, //101 ???
	NONE, //102 ???
	NONE, //103 KEY_KPEQUAL
	NONE, //104 KEY_F13
	NONE, //105 KEY_F14
	NONE, //106 KEY_F15
	NONE, //107 KEY_F16
	EMU_SWITCH_1 | 1, //108 KEY_F17
	EMU_SWITCH_1 | 2, //109 KEY_F18
	EMU_SWITCH_1 | 3, //110 KEY_F19
	EMU_SWITCH_1 | 4, //111 KEY_F20
	NONE, //112 KEY_F21
	NONE, //113 KEY_F22
	NONE, //114 KEY_F23
	NONE, //115 KEY_F24
	NONE, //116 
	NONE, //117 KEY_HELP
	NONE, //118 
	NONE, //119 
	NONE, //120 
	NONE, //121 
	NONE, //122 
	NONE, //123 
	NONE, //124 
	NONE, //125 
	NONE, //126 
	NONE, //127 
	NONE, //128 
	NONE, //129 
	NONE, //130 
	NONE, //131 
	NONE, //132 
	NONE, //133 
	NONE, //134 
	NONE, //135 
	NONE, //136 
	NONE, //137 
	NONE, //138 
	NONE, //139 
	NONE, //140 
	NONE, //141 
	NONE, //142 
	NONE, //143 
	NONE, //144 
	NONE, //145 
	NONE, //146 
	NONE, //147 
	NONE, //148 
	NONE, //149 
	NONE, //150 
	NONE, //151 
	NONE, //152 
	NONE, //153 
	NONE, //154 
	NONE, //155 
	NONE, //156 
	NONE, //157 
	NONE, //158 
	NONE, //159 
	NONE, //160 
	NONE, //161 
	NONE, //162 
	NONE, //163 
	NONE, //164 
	NONE, //165 
	NONE, //166 
	NONE, //167 
	NONE, //168 
	NONE, //169 
	NONE, //170 
	NONE, //171 
	NONE, //172 
	NONE, //173 
	NONE, //174 
	NONE, //175 
	NONE, //176 
	NONE, //177 
	NONE, //178 
	NONE, //179 
	NONE, //180 
	NONE, //181 
	NONE, //182 
	NONE, //183 
	NONE, //184 
	NONE, //185 
	NONE, //186 
	NONE, //187 
	NONE, //188 
	NONE, //189 
	NONE, //180 
	NONE, //191 
	NONE, //192 
	NONE, //193 
	NONE, //194 
	NONE, //195 
	NONE, //196 
	NONE, //197 
	NONE, //198 
	NONE, //109 
	NONE, //200 
	NONE, //201 
	NONE, //202 
	NONE, //203 
	NONE, //204 
	NONE, //205 
	NONE, //206 
	NONE, //207 
	NONE, //208 
	NONE, //209 
	NONE, //210 
	NONE, //211 
	NONE, //212 
	NONE, //213 
	NONE, //214 
	NONE, //215 
	NONE, //216 
	NONE, //217 
	NONE, //218 
	NONE, //219 
	NONE, //220 
	NONE, //221 
	NONE, //222 
	NONE, //223 
	NONE, //224 
	 0x12, //225  KEY_LEFTSHIFT
	 0x11, //226  KEY_LEFTALT
	NONE,          //227
	 EXT | 0x14, //228  KEY_RIGHTCTRL
	 0x59, //229  KEY_RIGHTSHIFT
	 EXT | 0x11, //230 KEY_RIGHTALT

};
/* http://www-personal.umich.edu/~bazald/l/api/_s_d_l__scancode_8h.html */
#endif
bool ReadKeyboard()
{
#ifdef WIN32
	HRESULT result;

	// Read the keyboard device.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) { m_keyboard->Acquire(); }
		else { return false; }
	}
#else
	m_keyboardState = SDL_GetKeyboardState(&m_keyboardStateCount);
	if (!m_keyboardState_last) m_keyboardState_last = (Uint8*)calloc(m_keyboardStateCount, sizeof(Uint8));
	////fprintf(stderr,"count: %d\n",m_keyboardStateCount);
#endif

	return true;
}

int SimInput::Initialise() {

#ifdef WIN32
	m_directInput = 0;
	m_keyboard = 0;
	HRESULT result;
	// Initialize the main direct input interface.
	result = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result)) { return false; }
	// Initialize the direct input interface for the keyboard.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result)) { return false; }
	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result)) { return false; }
	// Now acquire the keyboard.
	result = m_keyboard->Acquire();
	if (FAILED(result)) { return false; }
#endif
	return 0;
}

void SimInput::Read() {
	// Read keyboard state
	bool pr = ReadKeyboard();

	// Collect inputs
	for (int i = 0; i < inputCount; i++) {
#ifdef WIN32
		inputs[i] = m_keyboardState[mappings[i]] & 0x80;
#else
		inputs[i] = m_keyboardState[mappings[i]];
#endif
	}

#ifdef WIN32
	for (unsigned char k = 0; k < 220; k++) {

		if (m_keyboardState_last[k] != m_keyboardState[k]) {
			unsigned int ext = ev2ps2[k] & EXT;
			//fprintf(stderr, "ev2ps2[k] = %x  ext = %x  temp = %x\n", ev2ps2[k], ext, EXT | 0x6b);
			SimInput_PS2KeyEvent evt = SimInput_PS2KeyEvent(k, m_keyboardState[k], ext, ev2ps2[k]);
			keyEvents.push(evt);
		}
		m_keyboardState_last[k] = m_keyboardState[k];
	}
#else
	for (int k = 0; k < m_keyboardStateCount; k++) {
		if (m_keyboardState_last[k] != m_keyboardState[k]) {
			bool ext = 0;
			SimInput_PS2KeyEvent evt = SimInput_PS2KeyEvent(k, m_keyboardState[k], ext);
			keyEvents.push(evt);
		}
		m_keyboardState_last[k] = m_keyboardState[k];
	}
#endif

}

void SimInput::SetMapping(int index, int code) {
	//printf("index %d code %d\n", index, code);
	if (code < 256)
		mappings[index] = code;
	else
		mappings[index] = 0;
}

void SimInput::CleanUp() {

#ifdef WIN32
	// Release keyboard
	if (m_keyboard) { m_keyboard->Unacquire(); m_keyboard->Release(); m_keyboard = 0; }
	// Release direct input
	if (m_directInput) { m_directInput->Release(); m_directInput = 0; }
#endif
}

unsigned int ps2_key_temp;
bool ps2_clock = 1;


void SimInput::BeforeEval()
{
	if (ps2_key == NULL) {
		return;
	}
	if (keyEventTimer == 0) {

		if (keyEvents.size() > 0) {
			// Get chunk from queue
			SimInput_PS2KeyEvent evt = keyEvents.front();
			keyEvents.pop();
			ps2_key_temp = evt.mapped;
			if (evt.extended) { ps2_key_temp |= (1UL << 8); }
			if (evt.pressed) { ps2_key_temp |= (1UL << 9); }
			if (ps2_clock) { ps2_key_temp |= (1UL << 10); }
			ps2_clock = !ps2_clock;
			*ps2_key = ps2_key_temp;
			keyEventTimer = keyEventWait;
		}
	}
	else {
		keyEventTimer--;
	}
}

SimInput::SimInput(int count, DebugConsole c)
{
	inputCount = count;
	console = c;
}

SimInput::~SimInput()
{

}

