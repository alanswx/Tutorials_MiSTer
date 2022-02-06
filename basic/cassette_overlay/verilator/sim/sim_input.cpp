#include "sim_input.h"

#include <string>

#ifndef _MSC_VER
#include <SDL2/SDL.h>

 const Uint8 *m_keyboardState;


#else
#define WIN32
#include <dinput.h>
//#define DIRECTINPUT_VERSION 0x0800
IDirectInput8* m_directInput;
IDirectInputDevice8* m_keyboard;
unsigned char m_keyboardState[256];
#endif

#include <vector>


// - Core inputs
//#define VSW1    top->top__DOT__sw1
//#define VSW2    top->top__DOT__sw2
//#define PLAYERINPUT top->top__DOT__playerinput
//#define JS      top->top__DOT__joystick
//void js_assert(int s) { JS &= ~(1 << s); }
//void js_deassert(int s) { JS |= 1 << s; }
//void playinput_assert(int s) { PLAYERINPUT &= ~(1 << s); }
//void playinput_deassert(int s) { PLAYERINPUT |= (1 << s); }


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
   m_keyboardState= SDL_GetKeyboardState(NULL);
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
}

void SimInput::SetMapping(int index, int code) {
printf("index %d code %d\n",index,code);
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

SimInput::SimInput(int count)
{
	inputCount = count;
}

SimInput::~SimInput()
{

}

