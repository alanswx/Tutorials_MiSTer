#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include <atomic>
//#include <fstream>

#include <verilated.h>
#include "Vtop.h"


#include "../imgui/imgui.h"
#ifndef WINDOWS
#include "../imgui/imgui_impl_sdl.h"
#include "../imgui/imgui_impl_opengl2.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

#else
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#endif

#include "../imgui/imgui_memory_editor.h"

FILE *ioctl_file=NULL;
int ioctl_next_addr = 0x0;

#ifndef WINDOWS
SDL_Renderer * renderer =NULL;
SDL_Texture * texture =NULL;
#else
// DirectX data
static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGIFactory*            g_pFactory = NULL;
static ID3D11Buffer*            g_pVB = NULL;
static ID3D11Buffer*            g_pIB = NULL;
static ID3D10Blob*              g_pVertexShaderBlob = NULL;
static ID3D11VertexShader*      g_pVertexShader = NULL;
static ID3D11InputLayout*       g_pInputLayout = NULL;
static ID3D11Buffer*            g_pVertexConstantBuffer = NULL;
static ID3D10Blob*              g_pPixelShaderBlob = NULL;
static ID3D11PixelShader*       g_pPixelShader = NULL;
static ID3D11SamplerState*      g_pFontSampler = NULL;
static ID3D11ShaderResourceView*g_pFontTextureView = NULL;
static ID3D11RasterizerState*   g_pRasterizerState = NULL;
static ID3D11BlendState*        g_pBlendState = NULL;
static ID3D11DepthStencilState* g_pDepthStencilState = NULL;
static int                      g_VertexBufferSize = 5000, g_IndexBufferSize = 10000;
#endif


// Instantiation of module.
Vtop* top = NULL;

char my_string[1024];
int str_i = 0;

unsigned int file_size;

unsigned int row;
unsigned int col;
unsigned int bank;
unsigned int dram_address;

int pix_count = 0;

unsigned char rgb[3];
bool prev_vsync = 0;
int frame_count = 0;

bool vga_file_select = 0;

bool prev_hsync = 0;
int line_count = 0;

bool prev_sram_we_n = 0;

uint32_t inst_data_temp;

uint32_t prev_pc = 0xDEADBEEF;

unsigned int avm_byte_addr;
unsigned int avm_word_addr;

unsigned int burstcount;
unsigned int byteenable;
unsigned int writedata;

unsigned int datamux;	// What the aoR3000 core is actually reading from the bus! Only valid when avm_readdata_valid is High!
unsigned int datatemp;

unsigned int old_pc;
unsigned int inst_count = 0;

unsigned int old_hw_addr;
unsigned int hw_count = 0;

bool trigger1 = 0;
bool trigger2 = 0;

int trig_count = 0;

uint16_t byteena_bits;

bool ram_read_flag = 0;
bool ram_write_flag = 0;

FILE *vgap;

int last_sdram_writedata = 0;
int last_sdram_byteaddr = 0;
int last_sdram_ben = 0;

bool run_enable = 0;
bool single_step = 0;
bool multi_step = 0;
int multi_step_amount = 1024;

void ioctl_download_before_eval(void);
void ioctl_download_after_eval(void);


#ifdef WINDOWS
// Data
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

void CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
}

void CleanupRenderTarget()
{
	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

HRESULT CreateDeviceD3D(HWND hWnd)
{
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
		return E_FAIL;

	CreateRenderTarget();

	return S_OK;
}

void CleanupDeviceD3D()
{
	CleanupRenderTarget();
	if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
	if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
#else
#endif


static float values[90] = { 0 };
static int values_offset = 0;


vluint64_t main_time = 0;	// Current simulation time.

unsigned char buffer[16];

unsigned int bios_size = 1024 * 256 * 4;		// 1MB. (32-bit wide).
uint32_t *bios_ptr = (uint32_t *) malloc(bios_size);

unsigned int cart_size = 1024 * 1024 * 4;		// 16MB. (32-bit wide).
uint32_t *cart_ptr = (uint32_t *)malloc(cart_size);

unsigned int ram_size = 1024 * 512 * 4;		// 2MB. (32-bit wide).
uint32_t *ram_ptr = (uint32_t *) malloc(ram_size);

unsigned int vram_size = 1024 * 1024 * 4;	// 4MB. (32-bit wide).
uint32_t *vram_ptr = (uint32_t *) malloc(vram_size);

#define VGA_WIDTH 1024
#define VGA_HEIGHT 1024

unsigned int disp_size = 1024 * 1024 * 4;	// 4MB. (32-bit wide).
uint32_t *disp_ptr = (uint32_t *)malloc(disp_size);

uint32_t vga_size  = 1024 * 1024 * 4;		// 4MB. (32-bit wide).
uint32_t *vga_ptr  = (uint32_t *) malloc(vga_size);


uint32_t first_cmd_word = 0;

bool bios_rom_loaded = 0;
bool cart_rom_loaded = 0;


uint8_t clk_cnt = 0;

double sc_time_stamp () {	// Called by $time in Verilog.
	return main_time;
}


ImVector<char*>       Items;
static char* Strdup(const char *str) { size_t len = strlen(str) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)str, len); }

#if 0
void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
	// FIXME-OPT
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);
	Items.push_back(Strdup(buf));
}
#endif

// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, here we are using a more C++ like approach of declaring a class to hold the data and the functions.
struct ExampleAppConsole
{
	char                  InputBuf[256];
	ImVector<const char*> Commands;
	ImVector<char*>       History;
	int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
	ImGuiTextFilter       Filter;
	bool                  AutoScroll;
	bool                  ScrollToBottom;
void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
	// FIXME-OPT
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);
	Items.push_back(Strdup(buf));
}
	ExampleAppConsole()
	{
		ClearLog();
		memset(InputBuf, 0, sizeof(InputBuf));
		HistoryPos = -1;
		Commands.push_back("HELP");
		Commands.push_back("HISTORY");
		Commands.push_back("CLEAR");
		Commands.push_back("CLASSIFY");  // "classify" is only here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
		AutoScroll = true;
		ScrollToBottom = false;
		AddLog("GBA Core Sim start");
		AddLog("");
	}
	~ExampleAppConsole()
	{
		ClearLog();
		for (int i = 0; i < History.Size; i++)
			free(History[i]);
	}

	// Portable helpers
	static int   Stricmp(const char* str1, const char* str2) { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
	static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
//	static char* Strdup(const char *str) { size_t len = strlen(str) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)str, len); }
	static void  Strtrim(char* str) { char* str_end = str + strlen(str); while (str_end > str && str_end[-1] == ' ') str_end--; *str_end = 0; }

	void    ClearLog()
	{
		for (int i = 0; i < Items.Size; i++)
			free(Items[i]);
		Items.clear();
	}

/*
	void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		// FIXME-OPT
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
		buf[IM_ARRAYSIZE(buf) - 1] = 0;
		va_end(args);
		Items.push_back(Strdup(buf));
	}
*/

	void    Draw(const char* title, bool* p_open)
	{
		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}

		// As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar. So e.g. IsItemHovered() will return true when hovering the title bar.
		// Here we create a context menu only available from the title bar.
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Close Console"))
				*p_open = false;
			ImGui::EndPopup();
		}

		//ImGui::TextWrapped("This example implements a console with basic coloring, completion and history. A more elaborate implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
		//ImGui::TextWrapped("Enter 'HELP' for help, press TAB to use text completion.");

		// TODO: display items starting from the bottom

		//if (ImGui::SmallButton("Add Dummy Text")) { AddLog("%d some text", Items.Size); AddLog("some more text"); AddLog("display very important message here!"); } ImGui::SameLine();
		//if (ImGui::SmallButton("Add Dummy Error")) { AddLog("[error] something went wrong"); } ImGui::SameLine();
		if (ImGui::SmallButton("Clear")) { ClearLog(); } ImGui::SameLine();
		bool copy_to_clipboard = ImGui::SmallButton("Copy");
		//static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

		ImGui::Separator();

		// Options menu
		if (ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll", &AutoScroll);
			ImGui::EndPopup();
		}

		// Options, Filter
		if (ImGui::Button("Options"))
			ImGui::OpenPopup("Options");
		ImGui::SameLine();
		Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
		ImGui::Separator();

		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
		ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("Clear")) ClearLog();
			ImGui::EndPopup();
		}

		// Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
		// NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping to only process visible items.
		// You can seek and display only the lines that are visible using the ImGuiListClipper helper, if your elements are evenly spaced and you have cheap random access to the elements.
		// To use the clipper we could replace the 'for (int i = 0; i < Items.Size; i++)' loop with:
		//     ImGuiListClipper clipper(Items.Size);
		//     while (clipper.Step())
		//         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		// However, note that you can not use this code as is if a filter is active because it breaks the 'cheap random-access' property. We would need random-access on the post-filtered list.
		// A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices that passed the filtering test, recomputing this array when user changes the filter,
		// and appending newly elements as they are inserted. This is left as a task to the user until we can manage to improve this example code!
		// If your items are of variable size you may want to implement code similar to what ImGuiListClipper does. Or split your data into fixed height items to allow random-seeking into your list.
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
		if (copy_to_clipboard)
			ImGui::LogToClipboard();
		for (int i = 0; i < Items.Size; i++)
		{
			const char* item = Items[i];
			if (!Filter.PassFilter(item))
				continue;

			// Normally you would store more information in your item (e.g. make Items[] an array of structure, store color/type etc.)
			bool pop_color = false;
			if (strstr(item, "[error]")) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f)); pop_color = true; }
			else if (strncmp(item, "# ", 2) == 0) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.6f, 1.0f)); pop_color = true; }
			ImGui::TextUnformatted(item);
			if (pop_color)
				ImGui::PopStyleColor();
		}
		if (copy_to_clipboard)
			ImGui::LogFinish();

		if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
			ImGui::SetScrollHereY(1.0f);
		ScrollToBottom = false;

		ImGui::PopStyleVar();
		ImGui::EndChild();
		ImGui::Separator();

		// Command-line
		bool reclaim_focus = false;
		if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this))
		{
			char* s = InputBuf;
			Strtrim(s);
			if (s[0])
				ExecCommand(s);
			strcpy(s, "");
			reclaim_focus = true;
		}

		// Auto-focus on window apparition
		ImGui::SetItemDefaultFocus();
		if (reclaim_focus)
			ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

		ImGui::End();
	}

	void    ExecCommand(const char* command_line)
	{
		AddLog("# %s\n", command_line);

		// Insert into history. First find match and delete it so it can be pushed to the back. This isn't trying to be smart or optimal.
		HistoryPos = -1;
		for (int i = History.Size - 1; i >= 0; i--)
			if (Stricmp(History[i], command_line) == 0)
			{
				free(History[i]);
				History.erase(History.begin() + i);
				break;
			}
		History.push_back(Strdup(command_line));

		// Process command
		if (Stricmp(command_line, "CLEAR") == 0)
		{
			ClearLog();
		}
		else if (Stricmp(command_line, "HELP") == 0)
		{
			this->AddLog("Commands:");
			for (int i = 0; i < Commands.Size; i++)
				this->AddLog("- %s", Commands[i]);
		}
		else if (Stricmp(command_line, "HISTORY") == 0)
		{
			int first = History.Size - 10;
			for (int i = first > 0 ? first : 0; i < History.Size; i++)
				this->AddLog("%3d: %s\n", i, History[i]);
		}
		else
		{
			this->AddLog("Unknown command: '%s'\n", command_line);
		}

		// On commad input, we scroll to bottom even if AutoScroll==false
		ScrollToBottom = true;
	}

	static int TextEditCallbackStub(ImGuiInputTextCallbackData* data) // In C++11 you are better off using lambdas for this sort of forwarding callbacks
	{
		ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
		return console->TextEditCallback(data);
	}

	int     TextEditCallback(ImGuiInputTextCallbackData* data)
	{
		//AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
		switch (data->EventFlag)
		{
		case ImGuiInputTextFlags_CallbackCompletion:
		{
			// Example of TEXT COMPLETION

			// Locate beginning of current word
			const char* word_end = data->Buf + data->CursorPos;
			const char* word_start = word_end;
			while (word_start > data->Buf)
			{
				const char c = word_start[-1];
				if (c == ' ' || c == '\t' || c == ',' || c == ';')
					break;
				word_start--;
			}

			// Build a list of candidates
			ImVector<const char*> candidates;
			for (int i = 0; i < Commands.Size; i++)
				if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
					candidates.push_back(Commands[i]);

			if (candidates.Size == 0)
			{
				// No match
				this->AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
			}
			else if (candidates.Size == 1)
			{
				// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
				data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
				data->InsertChars(data->CursorPos, candidates[0]);
				data->InsertChars(data->CursorPos, " ");
			}
			else
			{
				// Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
				int match_len = (int)(word_end - word_start);
				for (;;)
				{
					int c = 0;
					bool all_candidates_matches = true;
					for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
						if (i == 0)
							c = toupper(candidates[i][match_len]);
						else if (c == 0 || c != toupper(candidates[i][match_len]))
							all_candidates_matches = false;
					if (!all_candidates_matches)
						break;
					match_len++;
				}

				if (match_len > 0)
				{
					data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
					data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
				}

				// List matches
				this->AddLog("Possible matches:\n");
				for (int i = 0; i < candidates.Size; i++)
					this->AddLog("- %s\n", candidates[i]);
			}

			break;
		}
		case ImGuiInputTextFlags_CallbackHistory:
		{
			// Example of HISTORY
			const int prev_history_pos = HistoryPos;
			if (data->EventKey == ImGuiKey_UpArrow)
			{
				if (HistoryPos == -1)
					HistoryPos = History.Size - 1;
				else if (HistoryPos > 0)
					HistoryPos--;
			}
			else if (data->EventKey == ImGuiKey_DownArrow)
			{
				if (HistoryPos != -1)
					if (++HistoryPos >= History.Size)
						HistoryPos = -1;
			}

			// A better implementation would preserve the data on the current input line along with cursor position.
			if (prev_history_pos != HistoryPos)
			{
				const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
				data->DeleteChars(0, data->BufTextLen);
				data->InsertChars(0, history_str);
			}
		}
		}
		return 0;
	}
};

static ExampleAppConsole console;

static void ShowExampleAppConsole(bool* p_open)
{
//	static ExampleAppConsole console;
	console.Draw("Debug Log", p_open);
}



int verilate() {
static int clkdiv=3;

	if (!Verilated::gotFinish()) {
		//while ( top->FL_ADDR < 0x0100 ) {		// Only run for a short time.
		if (main_time < 48) {
			top->reset = 1;   	// Assert reset (active HIGH)
		}
		if (main_time == 48) {	// Do == here, so we can still reset it in the main loop.
			top->reset = 0;		// Deassert reset.
		}
		if ((main_time & 1) == 0) {
//			top->clk_sys = 0;       // Toggle clock
			if (!clkdiv) {
			}
				top->clk_sys=0;
			top->clk_vid = 0;				
		}
		if ((main_time & 1) == 1) {
//			top->clk_sys = 1;
			if (!clkdiv) {
				clkdiv=3;
			}
			clkdiv--;
			top->clk_sys=1;
			top->clk_vid = 1;

#if 0
			if (top->bus_system_read && top->bus_mem_addr>>2 < bios_size)  {
				/*if (top->bus_mem_addr>>2==0x0260>>2 || top->bus_mem_addr>>2==0x0310>>2) top->bus_system_rdata = 0x00000000;	// NOP out some BNEs, which are used loop which clear SDRAM. Help speed up the sim!
				else*/
					top->bus_system_rdata = bios_ptr[top->bus_mem_addr>>2];	// Read Flash data from our loaded BIOS ROM file.

				// Byteswap! (32-bit)
				//uint32_t bios_word = bios_ptr[top->bus_mem_addr >> 2];
				//top->bus_system_rdata = (bios_word & 0xFF000000) >> 24 | (bios_word & 0x00FF0000) >> 8 | (bios_word & 0x0000FF00) << 8 | (bios_word & 0x000000FF) << 24;

				// Byteswap! (16-bit)
				//uint32_t bios_word = bios_ptr[top->bus_mem_addr >> 2];
				//top->bus_system_rdata = (bios_word & 0xFF000000) >> 8 | (bios_word & 0x00FF0000) << 8 | (bios_word & 0x0000FF00) >> 8 | (bios_word & 0x000000FF) << 8;
			}
#endif
			/*
			else if (top->in_PPORT && top->bus_mem_addr < bios_size) {
				top->bus_system_rdata = exp_ptr[top->bus_mem_addr];
				//top->bus_system_rdata = exp_ptr[top->bus_mem_addr>>2];
				//top->bus_system_rdata = (top->bus_system_rdata & 0xFF000000) >> 8 | (top->bus_system_rdata & 0x00FF0000) << 8 | (top->bus_system_rdata & 0x0000FF00) >> 8 | (top->bus_system_rdata & 0x000000FF) << 8;

				printf("Expansion ROM read, from 0x%08X, data=0x%08X\n", top->bus_mem_addr>>2, top->bus_system_rdata);

				//run_enable = 0;
			}
			*/
#if 0
			if (top->bus_mem_addr >= 0x02000000 && top->bus_mem_addr <= 0x03FFFFFF && top->gba_top__DOT__bus_write) {
				ram_ptr[(top->bus_mem_addr&0x00FFFFFF) >> 2] = top->gba_top__DOT__bus_wdata;
			}

			if (top->bus_game_read && top->bus_mem_addr >> 2 < cart_size) {
				/*if (top->bus_mem_addr>>2==0x0260>>2 || top->bus_mem_addr>>2==0x0310>>2) top->bus_system_rdata = 0x00000000;	// NOP out some BNEs, which are used loop which clear SDRAM. Help speed up the sim!
				else*/ top->bus_game_rdata = cart_ptr[top->bus_mem_addr >> 2];	// Read Flash data from our loaded BIOS ROM file.
			}
#endif
			//printf("bus_mem_addr>>2: %08X  bus_system_rdata: %08X\n", top->bus_mem_addr>>2<<2, top->bus_system_rdata);

			//if (old_pc != top->pc) printf("pc: %08X  inst_read: %d  mdr: %d  mem_addr: %08X  inst: %08X  mem_data_in: %08X  mem_data_out: %08X\n", top->pc<<2, top->inst_read, top->mem_data_read, top->bus_mem_addr<<2, top->inst, top->mem_data_in, top->mem_data_out);

			// This code MUST go BEFORE the SDRAM READ code below!
			// The PSX core needs to see sd_valid go Low before it will continue the read.
			// We check ram_read_flag here, then set sd_valid High only after the NEXT tick of CLOCK_50.
			/*
			if (ram_read_flag == 1) {
				ram_read_flag = 0;
				top->sd_valid = 1;
				top->sd_waitrequest = 0;
			}

			if (ram_write_flag == 1) {
				ram_write_flag = 0;
				top->sd_waitrequest = 0;
			}

			if (top->sd_wen) {
				//if ( top->pc == 0x80059DE0 >> 2 ) ram_ptr[0x001FFD2E >> 2] = 0x0001;	// Cancel out the annoying delay loop.

				if (top->data_ben & 8) ram_ptr[top->sd_addr] = (ram_ptr[top->sd_addr] & 0x00FFFFFF) | (top->sd_data_i & 0xFF000000);
				if (top->data_ben & 4) ram_ptr[top->sd_addr] = (ram_ptr[top->sd_addr] & 0xFF00FFFF) | (top->sd_data_i & 0x00FF0000);
				if (top->data_ben & 2) ram_ptr[top->sd_addr] = (ram_ptr[top->sd_addr] & 0xFFFF00FF) | (top->sd_data_i & 0x0000FF00);
				if (top->data_ben & 1) ram_ptr[top->sd_addr] = (ram_ptr[top->sd_addr] & 0xFFFFFF00) | (top->sd_data_i & 0x000000FF);

				top->sd_waitrequest = 1;
				ram_write_flag = 1;
				//printf("SDRAM WRITE. sd_addr: %08X  byte_addr: %08X  data_from_core: %08X  data_ben: %01X\n", top->sd_addr, top->sd_addr<<2, top->sd_data_i, top->data_ben);	//  Note sd_data_i is OUT of the sim!

				last_sdram_writedata = top->sd_data_i;
				last_sdram_byteaddr  = top->sd_addr << 2;
				last_sdram_ben       = top->data_ben;

				if (top->sd_addr == 0x0006EE0) {
					printf("SDRAM WRITE. sd_addr: %08X  byte_addr: %08X  data_from_core: %08X  data_ben: %01X\n", top->sd_addr, top->sd_addr << 2, top->sd_data_i, top->data_ben);	//  Note sd_data_i is OUT of the sim!
					// AJS // printf("data read back from SDRAM: %08X\n", bios_ptr[top->bus_mem_addr>>2]);
				}
			}

			if (top->sd_ren) {
				if (top->sd_addr == 0x00002834 >> 2	// NOP out the Kernel IO debug thingy routine (SCPH1001 BIOS. Normally has a jal $00002870 there).
					|| top->sd_addr == 0x0005418C >> 2	// NOP out an SPU init routine (SCPH1001 BIOS).
					|| top->sd_addr == 0x000545C8 >> 2 	// NOP out some SPU sample transfer stuff (SCPH1001 BIOS).
					top->sd_data_o = 0x00000000;	// The NOP itself. (SDRAM access is 32-bit wide on the core, btw!)
				else top->sd_data_o = ram_ptr[top->sd_addr];	// Else, normal read from SDRAM.
				top->sd_valid = 0;
				ram_read_flag = 1;
				//printf("SDRAM READ.  sd_addr: %08X  sd_data_in: %08X  sd_valid: %d  sd_wait: %d  state: %d  next_state: %d  ack: %d  next_ack: %d\n", top->sd_addr, top->sd_data_o, top->sd_valid, top->sd_waitrequest, top->addr_curr_state, top->addr_next_state, top->addr_curr_ack, top->addr_next_ack);	//  Note sd_data_o is IN to the sim!
			}
			*/

			/*
			if (top->pc == 0x000005F4>>2) {
				char my_byte;
				my_byte = top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[4];

				printf("my_byte %s\n", my_byte);

				if (my_byte == 0x0A) {
					for (int i = 0; i < str_i; i++) {
						printf("%s", my_string[i]);
					}
					printf("\n");
					str_i = 0;
				}
				else my_string[str_i] = my_byte;
				
				if (str_i < 400) str_i++;
			}
			*/

			//printf("ID_Cfc2: %d, ID_Ctc2: %d, ID_Mfc2: %d, ID_Mtc2: %d, ID_Lwc2: %d, ID_Swc2: %d ID_Mfc0: %d, ID_Mtc0: %d, ID_Eret: %d\n", top->ID_Cfc2, top->ID_Ctc2, top->ID_Mfc2, top->ID_Mtc2, top->ID_Lwc2, top->ID_Swc2, top->ID_Mfc0, top->ID_Mtc0, top->ID_Eret);


			/*
			if (old_pc == top->pc) {
				if (inst_count < 10000) inst_count++;
				else {
					//printf("Stuck on instruction: %08X  bus_mem_addr: %08X  pc: %08X  sd_addr: %08X\n", top->inst, top->bus_mem_addr<<2, top->pc<<2, top->sd_addr);

					
					uint32_t opcode = (top->inst & 0xFC000000) >> 26;
					uint32_t rs = (top->inst & 0x03E00000) >> 21;
					uint32_t rt = (top->inst & 0x001F0000) >> 16;
					uint32_t rd = (top->inst & 0x0000F800) >> 11;
					uint32_t funct = (top->inst & 0x0000003F) >> 0;
					uint32_t immediate = (top->inst & 0x0000FFFF) >> 0;
					uint32_t jumpaddress = (top->inst & 0x03FFFFFF) >> 0;
					uint32_t cp0_sel = (top->inst & 0x00000007) >> 0;
					
					//printf("Stuck at pc: %08X  addr: %08X  inst: %08X  opc: %02x  rs: %02x  rt: %02x  rd: %02x  func: %02x  imm: %04x  jumpadr: %08X  cp0: %01x\n", top->pc << 2, top->bus_mem_addr, top->inst, opcode, rs, rt, rd, funct, immediate, jumpaddress, cp0_sel);

					//printf("Stuck at pc: %08X  addr: %08X  inst: %08X\n", top->pc << 2, top->bus_mem_addr, top->inst);

					//printf("IF_S %d, IFE_S: %d,  ID_S: %d,  ID_E: %d,  EX_ALU_S: %d,  EX_S: %d,  EX_E_S: %d,  M_S: %d,  M_S_Cont: %d,  M_E_S: %d,  WB_S:  %d  IP: %02X\n", top->IF_Stall, top->IF_Exception_Stall, top->ID_Stall, top->ID_Exception_Stall, top->EX_ALU_Stall, top->EX_Stall, top->EX_Exception_Stall, top->M_Stall, top->M_Stall_Controller, top->M_Exception_Stall, top->WB_Stall, top->IP);

					//printf("ID_Cfc2: %d, ID_Ctc2: %d, ID_Mfc2: %d, ID_Mtc2: %d, ID_Lwc2: %d, ID_Swc2: %d ID_Mfc0: %d, ID_Mtc0: %d, ID_Eret: %d\n", top->ID_Cfc2, top->ID_Ctc2, top->ID_Mfc2, top->ID_Mtc2, top->ID_Lwc2, top->ID_Swc2, top->ID_Mfc0, top->ID_Mtc0, top->ID_Eret);

					//printf("bus_system_read: %d, in_MAIN: %d, in_PPORT: %d, in_SCPAD: %d, bus_io_reg_read: %d\n", top->bus_system_read, top->in_MAIN, top->in_PPORT, top->in_SCPAD, top->bus_io_reg_read);

					printf("GPUBUS: %08X  GPUREAD: %08X  GPUSTAT: %08X\n", top->gpu_main_bus, top->gpu_read, top->gpu_stat);
					inst_count = 0;
				}
			}
			else {
				inst_count = 0;
				//printf("addr: %08X  inst: %08X\n", top->bus_mem_addr, top->inst);
			}
			*/

			/*
			if (top->service_DMA) {
				printf("service_DMA: %d  dma_addr: %08X  dma_ren: %d  dma_wen: %d  dma_req: %d  dma_done: %d  ack_o: %d\n", top->service_DMA, top->dma_addr, top->dma_ren, top->dma_wen, top->dma_req, top->dma_done, top->ack_o);
				run_enable = 0;
			}
			*/

			//if (top->halted) printf("CPU Halted!\n");

			//if (top->pc==0x80051050>>2) trigger1 = 1;
			/*
			if (top->pc == 0x8005a4c4 >> 2) trigger1 = 1;
			if (trigger1) {
				if (top->pc != old_pc) {
					// AJS // printf("pc: %08X  bus_mem_addr: %08X   mem_addr: %08X  inst: %08X  mem_data_in: %08X  mem_data_out: %08X  GPUBUS: %08X  GPUREAD_1810: %08X  GPUSTAT_1814: %08X  gpu_fifo_full: %d\n", top->pc << 2, top->bus_mem_addr, top->bus_mem_addr, top->inst, top->mem_data_in, top->mem_data_out, top->gpu_main_bus, top->gpu_read, top->gpu_stat, top->gpu_fifo_full);

					printf("service_DMA: %d  dma_addr: %08X  dma_ren: %d  dma_wen: %d  dma_req: %d  dma_done: %d  ack_o: %d\n", top->service_DMA, top->dma_addr<<2, top->dma_ren, top->dma_wen, top->dma_req, top->dma_done, top->ack_o);

					//printf("Stall flags: IF:%d IFE:%d ID:%d IDE:%d EX_ALU:%d EX:%d EXE:%d MS:%d MSC:%d ME:%d WB:%d\n", top->IF_Stall, top->IF_Exception_Stall, top->ID_Stall, top->ID_Exception_Stall, top->EX_ALU_Stall, top->EX_Stall, top->EX_Exception_Stall, top->M_Stall, top->M_Stall_Controller, top->M_Exception_Stall, top->WB_Stall);

					//printf("ID: CFC2:%d CTC2:%d MFC:%d MTC:%d LWC2:%d SWC2:%d MFC0:%d MTC0:%d ERET:%d\n", top->ID_Cfc2, top->ID_Ctc2, top->ID_Mfc2, top->ID_Mtc2, top->ID_Lwc2, top->ID_Swc2, top->ID_Mfc0, top->ID_Mtc0, top->ID_Eret);

					//printf("Addr CS flags: BIOS:%d  MAIN:%d  PPORT:%d  SCPAD:%d  HWREG:%d\n", top->bus_system_read, top->in_MAIN, top->in_PPORT, top->in_SCPAD, top->bus_io_reg_read);

					trig_count++;
				}
				//if (trig_count==2000) exit(0);
				if (frame_count == 50) exit(0);
			}
			*/

//			old_pc = top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCOut;
			if (0  /*top->bus_io_reg_read AJS *//*&& top->bus_mem_addr != old_hw_addr*/) {
				unsigned int my_data;
#if 0
				
				if (top->gba_top__DOT__cpu__DOT__cpu__DOT__WRITE) {
					// AJS  // sprintf(my_string, "WRITE to IO  0x%08X  ", top->bus_mem_addr); console.AddLog(my_string);
					my_data = top->gba_top__DOT__cpu__DOT__cpu__DOT__WDATA;
				}
				else {
					sprintf(my_string, "READ from IO 0x%08X  ", top->bus_mem_addr); console.AddLog(my_string);
					my_data = top->gba_top__DOT__cpu__DOT__cpu__DOT__RDATA;
				}
#endif			
#if 0	
				switch (top->bus_mem_addr) {
					case 0x04000208: sprintf(my_string, "IME:     (PC=0x%08X) (data=0x%08X)\n", top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCOut, my_data); console.AddLog(my_string); break;
					case 0x04000300: sprintf(my_string, "POSTFLG: (PC=0x%08X) (data=0x%08X)\n", top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCOut, my_data); console.AddLog(my_string); break;
					default:         sprintf(my_string, "         (PC=0x%08X) (data=0x%08X)\n", top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCOut, my_data); console.AddLog(my_string); break;
				}
#endif
//				sprintf(my_string, "bus_addr_lat1=0x%08X\n", top->gba_top__DOT__mem__DOT__bus_addr_lat1); console.AddLog(my_string);
			}

			//if (top->bus_io_reg_read) old_hw_addr = top->bus_mem_addr;
			// AJS // old_hw_addr = top->bus_mem_addr;
			

			pix_count++;

			// Write VGA output to a file. RAW RGB!
			rgb[0] = top->VGA_B ;	// GBA core outputs 4 bits per VGA colour channel (12 bpp).
			rgb[1] = top->VGA_G ;
			rgb[2] = top->VGA_R ;
			//fwrite(rgb, 1, 3, vgap);		// Write 24-bit values to the file.
			uint32_t vga_addr = (line_count * 1024) + pix_count;
			if (vga_addr <= vga_size) vga_ptr[vga_addr] = (rgb[0] << 16) | (rgb[1] << 8) | (rgb[2] << 0);
			
			
			//disp_ptr[vga_addr] = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8;	// Our debugger framebuffer is in the 32-bit RGBA format.
			disp_ptr[vga_addr] = 0xFF000000 | rgb[0] << 16 | rgb[1] << 8 | rgb[2] ;	// Our debugger framebuffer is in the 32-bit RGBA format.
			//fprintf(stderr,"vga_addr: %d %d %d %x\n",vga_addr,line_count,pix_count,disp_ptr[vga_addr]);
			//fprintf(stderr,"vga: %x %x %x\n",rgb[0],rgb[1],rgb[1]);

				 // (line_count * width) + pixel_count.
			//uint32_t disp_addr = (top->gba_top__DOT__gfx__DOT__gfx__DOT__vcount * 240) + top->gba_top__DOT__gfx__DOT__gfx__DOT__hcount;
			//disp_ptr[disp_addr] = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8;	// Our debugger framebuffer is in the 32-bit RGBA format.


			//printf("dis_w: %d  dis_h: %d  dis_x: %d  dis_y: %d\n", top->dis_w, top->dis_h, top->dis_x, top->dis_y);

			/*
			if (top->system_top__DOT__gp__DOT__vram_we) {
				rgb[0] = (top->system_top__DOT__gp__DOT__vram_bus_out & 0x001F) << 3;	// [4:0] Red.
				rgb[1] = (top->system_top__DOT__gp__DOT__vram_bus_out & 0x03E0) >> 2;	// [9:5] Green.
				rgb[2] = (top->system_top__DOT__gp__DOT__vram_bus_out & 0x7C00) >> 7;	// [14:10] Blue. Remember, the PS1 15 bpp format is in BGR order, so the upper bits are for Blue!
				disp_ptr[top->system_top__DOT__gp__DOT__vram_addr] = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8;	// Our debugger framebuffer is in the 32-bit RGBA format.

				if ((frame_count & 1) == 0) {
					vram_ptr[top->system_top__DOT__GPU_addr] = top->system_top__DOT__gp__DOT__vram_bus_out;
				}
				//else vram_ptr[top->system_top__DOT__GPU_addr] = 0xFFFF0000;	// Force a colour, because it's broken atm, and I can't see anything. ElectronAsh.
			}
			*/

			/*
			if (prev_sram_we_n == 0 && top->SRAM_WE_N == 1) {
				vram_ptr[top->SRAM_ADDR] = top->system_top__DOT__sram_dq_out;
				//printf("SRAM_WE_N: %d  SRAM_ADDR: %06x  SRAM_DQ: %04x\n", top->SRAM_WE_N, top->SRAM_ADDR, top->SRAM_DQ);
			}
			prev_sram_we_n = top->SRAM_WE_N;
			*/
			
			/*
			if (top->SRAM_OE_N == 0) {
				//rgb[0] = (vram_ptr[top->SRAM_ADDR] & 0xFF000000) >> 24;
				//rgb[1] = (vram_ptr[top->SRAM_ADDR] & 0x00FF0000) >> 16;
				//rgb[2] = (vram_ptr[top->SRAM_ADDR] & 0x0000FF00) >> 8;
				//top->SRAM_DQ = (rgb[0]<<7) | (rgb[1] << 2) | (rgb[0] >> 3);

				top->SRAM_DQ = vram_ptr[top->SRAM_ADDR];

				//printf("SRAM_OE_N: %d  SRAM_ADDR: %06x  SRAM_DQ: %04x\n", top->SRAM_OE_N, top->SRAM_ADDR, vram_ptr[top->SRAM_ADDR]);
			}
			*/

			if (prev_hsync && !top->VGA_HS) {
				//printf("Line Count: %d\n", line_count);
				//printf("Pix count: %d\n", pix_count);
				line_count++;
				pix_count = 0;
			}
			prev_hsync = top->VGA_HS;
			
			if (prev_vsync && !top->VGA_VS) {
				frame_count++;
				line_count = 0;
				sprintf(my_string, "Frame: %06d  VSync! ", frame_count); console.AddLog(my_string);
				
				//if (frame_count > 46) {
#if 0
					printf("Dumping framebuffer to vga_out.raw!\n");
					char vga_filename[40];
					sprintf(vga_filename, "vga_frame_%d.raw", frame_count);
					vgap = fopen(vga_filename, "w");
					if (vgap != NULL) {
						sprintf(my_string, "\nOpened %s for writing OK.\n", vga_filename); console.AddLog(my_string);
					}
					else {
						sprintf(my_string, "\nCould not open %s for writing!\n\n", vga_filename); console.AddLog(my_string);
						return 0;
					};
					fseek(vgap, 0L, SEEK_SET);
				//}
				
				for (int i = 0; i < (1600 * 521); i++) {	// Pixels per line * total lines.
					//rgb[0] = vram_ptr[i] & 0x7C00 >> 7;
					//rgb[1] = vram_ptr[i] & 0x03E0 >> 2;
					//rgb[2] = vram_ptr[i] & 0x001F << 3;

					rgb[0] = (vga_ptr[i] & 0xFF000000) >> 24;
					rgb[1] = (vga_ptr[i] & 0x00FF0000) >> 16;
					rgb[2] = (vga_ptr[i] & 0x0000FF00) >> 8;

					//if (frame_count > =75) fwrite(rgb, 1, 3, vgap);	// Write pixels to the file.
					fwrite(rgb, 3, 1, vgap);	// Write pixels to the file.
				}
				//if (frame_count > 46) fclose(vgap);
				fclose(vgap);
#endif

				//printf("pc: %08X  addr: %08X  inst: %08X\n", top->pc << 2, top->bus_mem_addr, top->inst);
			}
			prev_vsync = top->VGA_VS;

			//if (top->VGA_we==1) printf("VGA_we is High!\n");

			//if (top->SRAM_DQ > 0) printf("SRAM_DQ is High!!!\n");
			//if (top->VGA_R > 0 || top->VGA_G > 0 || top->VGA_B > 0) printf("VGA is High!!!\n");
		}


	if (top->clk_sys ) 
		ioctl_download_before_eval();
	else if (ioctl_file)
		printf("skipping download this cycle %d\n",top->clk_sys);



		top->eval();            // Evaluate model!

	if (top->clk_sys ) 
		ioctl_download_after_eval();




		main_time++;            // Time passes...

		return 1;
	}
	// Stop Verilating...
	top->final();
	delete top;
	exit(0);
	return 0;
}

void ioctl_download_setfile(char *file, int index)
{
	ioctl_next_addr = -1;
	top->ioctl_addr=ioctl_next_addr;
	top->ioctl_index = index;
    ioctl_file=fopen(file,"rb");
    if (!ioctl_file) printf("error opening %s\n",file);
}
int nextchar = 0;
void ioctl_download_before_eval()
{
	if (ioctl_file) {
printf("ioctl_download_before_eval %x\n",top->ioctl_addr);
	    if (top->ioctl_wait==0) {
	    top->ioctl_download=1;
	    top->ioctl_wr = 1;
	    
	    if (feof(ioctl_file)) {
		    fclose(ioctl_file);
		    ioctl_file=NULL;
			top->ioctl_download=0;
	    	top->ioctl_wr = 0;
			printf("finished upload\n");

	    }
	    	if (ioctl_file) {
	    		int curchar = fgetc(ioctl_file);
		
	    		if (curchar!=EOF) {
	    		//top->ioctl_dout=(char)curchar;
	    		nextchar=curchar;
printf("ioctl_download_before_eval: dout %x \n",top->ioctl_dout);
	    		ioctl_next_addr++;
	    		}
	    	}
		}
	}
	else {
	top->ioctl_download=0;
	top->ioctl_wr=0;
	}

}
void ioctl_download_after_eval()
{
    top->ioctl_addr=ioctl_next_addr;
   top->ioctl_dout=(unsigned char)nextchar;
if (ioctl_file) printf("ioctl_download_after_eval %x wr %x dl %x\n",top->ioctl_addr,top->ioctl_wr,top->ioctl_download);
}

void start_load_journey() {
printf("load journey here\n");
 ioctl_download_setfile("../romextract/sepways.wav",0);

}
void start_audio() {
printf("start\n");
	top->start = 1;

}

void start_load_wav() {
printf("load wav 00 here\n");
 ioctl_download_setfile("../romextract/00.wav",1);
}
void start_load_cart_3() {
printf("load cart here\n");
 ioctl_download_setfile("../release-WIP/DiagCart2.a78",1);
}
void start_load_cart_2() {
printf("load cart here 2\n");
 ioctl_download_setfile("../release-WIP/PolePositionII.a78",1);
}

int my_count = 0;

static MemoryEditor mem_edit_1;

int main(int argc, char** argv, char** env) {
#ifdef WINDOWS
	// Create application window
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX11 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (CreateDeviceD3D(hwnd) < 0)
	{
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	// Show the window
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
#else
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }
 top = new Vtop();

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
#endif

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

#ifdef WINDOWS
	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
#else
    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

#endif
	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);


	Verilated::commandArgs(argc, argv);
	
	memset(vram_ptr, 0x00, vram_size);
	memset(disp_ptr, 0xAA, disp_size);
	memset(vga_ptr,  0xAA, vga_size);

	memset(ram_ptr, 0x00, ram_size);


	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	// Build texture atlas
	int width = 1024;
	int height = 512;

#ifdef WINDOWS
	// Upload texture to graphics system
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//desc.Format = DXGI_FORMAT_B5G5R5A1_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Texture2D *pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = disp_ptr;
	//subResource.pSysMem = vga_ptr;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &g_pFontTextureView);
	pTexture->Release();

	// Store our identifier
	ImTextureID my_tex_id = (ImTextureID)g_pFontTextureView;

	
	// Create texture sampler
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.MipLODBias = 0.f;
		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		desc.MinLOD = 0.f;
		desc.MaxLOD = 0.f;
		g_pd3dDevice->CreateSamplerState(&desc, &g_pFontSampler);
	}
#else
    // the texture should match the GPU so it doesn't have to copy
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);



	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VGA_WIDTH, VGA_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE,disp_ptr);
    ImTextureID my_tex_id = (ImTextureID) tex;


//    ImTextureID my_tex_id = (ImTextureID) renderedTexture;
#endif

	bool follow_writes = 0;
	int write_address = 0;

	static bool show_app_console = true;

#ifdef WINDOWS
	// imgui Main loop stuff...
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		// Poll and handle messages (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
#else
    // Main loop
    bool done = false;
    while (!done)
    {
    	// Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);

#endif

		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (show_demo_window)
		//	ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		static float f = 0.1f;
		static int counter = 0;

		ImGui::Begin("Virtual Dev Board v1.0");		// Create a window called "Virtual Dev Board v1.0" and append into it.

		ShowExampleAppConsole(&show_app_console);

#if 0
		if (!bios_rom_loaded) {
			FILE *biosfile;
			const char* bios_filename = "gbabios.bin";
			biosfile = fopen(bios_filename, "r");
			if (biosfile != NULL) {
				sprintf(my_string, "GBA BIOS %s loaded OK.\n\n", bios_filename); console.AddLog(my_string);
				fseek(biosfile, 0L, SEEK_END);
				file_size = ftell(biosfile);
				fseek(biosfile, 0L, SEEK_SET);
				fread(bios_ptr, 1, bios_size, biosfile);	// Read the whole ROM file into RAM.
			}
			else { 
			fprintf(stderr,"GBA BIOS NOT FOUND!\n");
				sprintf(my_string, "GBA BIOS file not found!\n\n");  console.AddLog(my_string); return 0;
			}
			bios_rom_loaded = 1;
		}
#endif
#if 0
		if (!cart_rom_loaded) {
			FILE *cartfile;
			const char* cart_filename = "pong.gba";
			cartfile = fopen(cart_filename, "r");
			if (cartfile != NULL) {
				sprintf(my_string, "GBA CART %s loaded OK.\n\n", cart_filename); console.AddLog(my_string);
				fseek(cartfile, 0L, SEEK_END);
				file_size = ftell(cartfile);
				fseek(cartfile, 0L, SEEK_SET);
				fread(cart_ptr, 1, cart_size, cartfile);	// Read the whole ROM file into RAM.
			}
			else {
				fprintf(stderr,"GBA CART file not found!\n");
			sprintf(my_string, "GBA CART file not found!\n\n"); console.AddLog(my_string); return 0;
			}
			cart_rom_loaded = 1;
		}
#endif

		//ImGui::Text("Verilator sim running... ROM_ADDR: 0x%05x", top->ROM_ADDR);               // Display some text (you can use a format strings too)
																							   //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
																							   //ImGui::Checkbox("Another Window", &show_another_window);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

																//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
																//counter++;

																//ImGui::SameLine();
																//ImGui::Text("counter = %d", counter);
		//ImGui::Text("samp_index = %d", samp_index);
		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "sample", -1.0f, 1.0f, ImVec2(0, 80));
		if (ImGui::Button("RESET")) main_time = 0;
		if (ImGui::Button("LOAD JOURNEY")) start_load_journey();
		if (ImGui::Button("Start Audio")) start_audio();
		ImGui::SameLine(); if (ImGui::Button("LOAD WAV 00")) start_load_wav();
		//ImGui::SameLine(); if (ImGui::Button("LOAD CART POLE")) start_load_cart_2();
		//ImGui::SameLine(); if (ImGui::Button("LOAD CART DIAG")) start_load_cart_3();
		ImGui::Text("main_time %d", main_time);
		ImGui::Text("frame_count: %d  line_count: %d", frame_count, line_count);
		// AJS // ImGui::Text("Addr:   0x%08X", top->bus_mem_addr);
		//ImGui::Text("PC:     0x%08X", top->pc << 2);
		//ImGui::Text("Inst:   0x%08X", top->system_top__DOT__core__DOT__InstMem_In);

		//if (ImGui::Button("Reset!")) top->KEY = 0;
		//else top->KEY = 1;

		ImGui::Checkbox("RUN", &run_enable);

		if (single_step == 1) single_step = 0;
		if (ImGui::Button("Single Step")) {
			run_enable = 0;
			single_step = 1;
		}

		if (multi_step == 1) multi_step = 0;
		if (ImGui::Button("Multi Step")) {
			run_enable = 0;
			multi_step = 1;
		}
		ImGui::SameLine(); ImGui::SliderInt("Step amount", &multi_step_amount, 8, 1024);
		ImGui::Text("Last SDRAM WRITE. byte_addr: 0x%08X  write_data: 0x%08X  data_ben: 0x%01X\n", last_sdram_byteaddr, last_sdram_writedata, last_sdram_ben);	//  Note sd_data_i is OUT of the sim!

		//ImGui::Image(my_tex_id, ImVec2(width, height), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
		ImGui::Image(my_tex_id, ImVec2(width, height));
		ImGui::End();


		ImGui::Begin("RAM Editor - Offset is 0x02000000");
		ImGui::Checkbox("Follow Writes", &follow_writes);
		// AJS // if (follow_writes) write_address = (top->bus_mem_addr & 0x00FFFFFF) >> 2;
		mem_edit_1.DrawContents(ram_ptr, ram_size, 0);
		ImGui::End();
		

		ImGui::Begin("CPU Registers");
		ImGui::Spacing();
		//ImGui::Text("PC       0x%04X", top->top__DOT__main__DOT__cpu_inst__DOT__core__DOT__PC);
		//ImGui::Text("AB       0x%02X%02X", top->top__DOT__main__DOT__cpu_inst__DOT__core__DOT__ABH,top->top__DOT__main__DOT__cpu_inst__DOT__core__DOT__ABL);
		//ImGui::Text("DI       0x%02X", top->top__DOT__main__DOT__cpu_inst__DOT__core__DOT__DI);
		//ImGui::Text("DO       0x%02X", top->top__DOT__main__DOT__cpu_inst__DOT__core__DOT__DO);
		//ImGui::Spacing();
		ImGui::Separator();
/*
		ImGui::Text("Maria Registers");
		ImGui::Spacing();
		ImGui::Text("ctrl     0x%02X", top->top__DOT__main__DOT__maria_inst__DOT__ctrl);
		ImGui::Text("WM       0x%02X", top->top__DOT__main__DOT__maria_inst__DOT__line_ram_inst__DOT__wm);
		ImGui::Text("CK       0x%02X", (top->top__DOT__main__DOT__maria_inst__DOT__ctrl&0x80)>>7);
		ImGui::Text("DM1      0x%02X", (top->top__DOT__main__DOT__maria_inst__DOT__ctrl&0x40)>>6);
		ImGui::Text("DM0      0x%02X", (top->top__DOT__main__DOT__maria_inst__DOT__ctrl&0x20)>>5);
		ImGui::Text("CW       0x%02X", (top->top__DOT__main__DOT__maria_inst__DOT__ctrl&0x10)>>4);
		ImGui::Text("BC       0x%02X", (top->top__DOT__main__DOT__maria_inst__DOT__ctrl&0x08)>>3);
		ImGui::Text("KM       0x%02X", (top->top__DOT__main__DOT__maria_inst__DOT__ctrl&0x04)>>2);
		ImGui::Text("RM1      0x%02X", (top->top__DOT__main__DOT__maria_inst__DOT__ctrl&0x02)>>1);
		ImGui::Text("RM0      0x%02X", top->top__DOT__main__DOT__maria_inst__DOT__ctrl&0x01);
*/
#if 0
		ImGui::Text("r0       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r0);
		ImGui::Text("r1       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r1);
		ImGui::Text("r2       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r2);
		ImGui::Text("r3       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r3);
		ImGui::Text("r4       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r4);
		ImGui::Text("r5       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r5);
		ImGui::Text("r6       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r6);
		ImGui::Text("r7       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r7);
		ImGui::Text("r8       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r8);
		ImGui::Text("r9       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r9);
		ImGui::Text("r10      0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r10);
		ImGui::Text("r11      0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r11);
		ImGui::Text("r12      0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r12);
		ImGui::Text("r13 (sp) 0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__sp);
		ImGui::Text("r14 (lr) 0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__lr);
		ImGui::Text("r15 (pc) 0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCIn);
		ImGui::Spacing();
		//ImGui::Text("bus_addr: 0x%08X", top->gba_top__DOT__bus_addr);
		//ImGui::Text("bus_mem_addr: 0x%08X", top->gba_top__DOT__bus_mem_addr);
		ImGui::Text("ADDR:    0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__ADDR);
		ImGui::Text("RDATA:   0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__RDATA);
		ImGui::Text("WDATA:   0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__WDATA);
		ImGui::Text("SIZE:    0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__SIZE);
		ImGui::Spacing();
		ImGui::Text("InstLat: 0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__controllogic_Inst__DOT__InstForDecodeLatched);
		ImGui::Spacing();
		ImGui::Text("ALU_AND:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_AND_Op);
		ImGui::Text("ALU_ORR:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_ORR_Op);
		ImGui::Text("ALU_EOR:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_EOR_Op);
		ImGui::Text("ALU_Ain:   0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__ABM_ABusOut);
		ImGui::Text("ALU_Bin:   0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__Shifter_ShOut);
		ImGui::Text("ALU_Dout:  0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_DataOut);
		ImGui::Text("ALU_InvA:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_InvA);
		ImGui::Text("ALU_InvB:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_InvB);
		ImGui::Text("ALU_PassA: %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_PassA);
		ImGui::Text("ALU_PassB: %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_PassB);
		ImGui::Spacing();
		ImGui::Text("C_flag:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_CFlagOut);
		ImGui::Text("V_flag:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_VFlagOut);
		ImGui::Text("N_flag:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_NFlagOut);
		ImGui::Text("Z_flag:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_ZFlagOut);
		ImGui::Spacing();
		ImGui::Text("AdrToPC: %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__AMI_AdrToPCSel);
		ImGui::Text("AdrInc:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__AMI_AdrIncStep);
		ImGui::Text("AdrCnt:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__AMI_AdrCntEn);
		ImGui::Text("PCInc:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__AMI_PCIncStep);
		ImGui::Spacing();
		ImGui::Text("nRESET:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__nRESET);
		ImGui::Text("pause:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__PAUSE);
		ImGui::Text("nIRQ:    %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__nIRQ);
		ImGui::Text("nFIQ:    %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__nFIQ);
		ImGui::Text("write:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__WRITE);
		ImGui::Text("abort:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ABORT);
		ImGui::Spacing();
		ImGui::Text("IDC_B:    %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__controllogic_Inst__DOT__IDC_B);
		ImGui::Text("IDC_BL:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__controllogic_Inst__DOT__IDC_BL);
		ImGui::Text("IDC_BX:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__controllogic_Inst__DOT__IDC_BX);
#endif
		ImGui::End();

#ifdef WINDOWS
		// Update the texture!
		// D3D11_USAGE_DEFAULT MUST be set in the texture description (somewhere above) for this to work.
		// (D3D11_USAGE_DYNAMIC is for use with map / unmap.) ElectronAsh.
		g_pd3dDeviceContext->UpdateSubresource(pTexture, 0, NULL, disp_ptr, width * 4, 0);

		// Rendering
		ImGui::Render();
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		//g_pSwapChain->Present(1, 0); // Present with vsync
		g_pSwapChain->Present(0, 0); // Present without vsync
#else

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VGA_WIDTH, VGA_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE,disp_ptr);

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
#endif
		if (run_enable) for (int step = 0; step < 1024; step++) verilate();	// Simulates MUCH faster if it's done in batches.
		else {																// But, that will affect the values we can grab for the GUI.
			if (single_step) verilate();
			if (multi_step) for (int step = 0; step < multi_step_amount; step++) verilate();
		}
	}
#ifdef WINDOWS
	// Close imgui stuff properly...
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	DestroyWindow(hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
#else
    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif
	return 0;
}
