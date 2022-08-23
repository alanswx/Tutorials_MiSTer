
#include "sim_video.h"

#include <string>

#ifndef _MSC_VER
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <sys/time.h>
#else
#define WIN32
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#endif

// Renderer variables
// ------------------

int output_width = 512;
int output_height = 512;
int output_rotate = 0;
bool output_vflip = false;
bool output_usevsync = 1;

uint32_t* output_ptr = NULL;
unsigned int output_size;
#ifdef WIN32
HWND hwnd;
WNDCLASSEX wc;
#else
SDL_Window* window;
SDL_GLContext gl_context;
GLuint tex;
#endif
ImTextureID texture_id;
ImGuiIO io;

ImVec4 clear_color = ImVec4(0.25f, 0.35f, 0.40f, 0.80f);

int count_pixel;
int count_line;
int count_frame;
bool last_hblank;
bool last_vblank;
bool last_hsync;
bool last_vsync;
bool frame_ready = 1;

// Statistics
#ifdef WIN32
SYSTEMTIME actualtime;
LONG time_ms;
LONG old_time;
LONG stats_frameTime;
#else
double time_ms;
double old_time;
double stats_frameTime;
#endif
float stats_fps;
int stats_xMax;
int stats_yMax;
int stats_xMin;
int stats_yMin;


#ifndef WIN32
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
#else
// DirectX data
static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGIFactory* g_pFactory = NULL;
static ID3D11Buffer* g_pVB = NULL;
static ID3D11Buffer* g_pIB = NULL;
static ID3D10Blob* g_pVertexShaderBlob = NULL;
static ID3D11VertexShader* g_pVertexShader = NULL;
static ID3D11InputLayout* g_pInputLayout = NULL;
static ID3D11Buffer* g_pVertexConstantBuffer = NULL;
static ID3D10Blob* g_pPixelShaderBlob = NULL;
static ID3D11PixelShader* g_pPixelShader = NULL;
static ID3D11SamplerState* g_pFontSampler = NULL;
static ID3D11ShaderResourceView* g_pFontTextureView = NULL;
static ID3D11RasterizerState* g_pRasterizerState = NULL;
static ID3D11BlendState* g_pBlendState = NULL;
static ID3D11DepthStencilState* g_pDepthStencilState = NULL;
static int                      g_VertexBufferSize = 5000, g_IndexBufferSize = 10000;
static ID3D11Texture2D* texture = NULL;
#endif

#ifdef WIN32
// Data
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

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
	sd.BufferDesc.Width = output_width;
	sd.BufferDesc.Height = output_height;
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

SimVideo::SimVideo(int width, int height, int rotate)
{
	output_width = width;
	output_height = height;
	output_size = output_width * output_height * 4;
	output_rotate = rotate;
	output_vflip = 0;

	count_pixel = 0;
	count_line = 0;
	count_frame = 0;
	last_hblank = 0;
	last_vblank = 0;

	old_time = 0;
	stats_frameTime = 0;
	stats_fps = 0.0;
	stats_xMax = -1000;
	stats_yMax = -1000;
	stats_xMin = 1000;
	stats_yMin = 1000;
}

SimVideo::~SimVideo()
{

}

int SimVideo::Initialise(const char* windowTitle) {

	// Setup pointers for video texture
	output_ptr = (uint32_t*)malloc(output_size);

#ifdef WIN32
	// Create application window
	wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T(windowTitle), NULL };
	RegisterClassEx(&wc);
	hwnd = CreateWindow(wc.lpszClassName, _T(windowTitle), WS_OVERLAPPEDWINDOW, 100, 100, 1600, 1100, NULL, NULL, wc.hInstance, NULL);

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

	// Setup window
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
	gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(0);
#endif


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO();
	(void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

#ifdef WIN32
	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
#else
	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL2_Init();

#endif

	memset(output_ptr, 0xAA, output_size);


#ifdef WIN32
	// Upload texture to graphics system
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = output_width;
	desc.Height = output_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = output_ptr;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	g_pd3dDevice->CreateTexture2D(&desc, &subResource, &texture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_pd3dDevice->CreateShaderResourceView(texture, &srvDesc, &g_pFontTextureView);
	texture->Release();

	// Store our identifier
	texture_id = (ImTextureID)g_pFontTextureView;

	// Create texture sampler
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.MipLODBias = 0.f;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.MinLOD = 0.f;
		desc.MaxLOD = 0.f;
		g_pd3dDevice->CreateSamplerState(&desc, &g_pFontSampler);
	}
#else
	// the texture should match the GPU so it doesn't have to copy
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, output_width, output_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, output_ptr);
	texture_id = (ImTextureID)tex;
#endif
	return 0;
}

void SimVideo::UpdateTexture() {

#ifdef WIN32
	// Update the texture!
	// D3D11_USAGE_DEFAULT MUST be set in the texture description (somewhere above) for this to work.
	// (D3D11_USAGE_DYNAMIC is for use with map / unmap.) ElectronAsh.
	if (frame_ready) {
		g_pd3dDeviceContext->UpdateSubresource(texture, 0, NULL, output_ptr, output_width * 4, 0);
	}
	// Rendering
	ImGui::Render();
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	g_pSwapChain->Present(output_usevsync, 0); // Present without vsync
#else
	if (frame_ready) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, output_width, output_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, output_ptr);
	}
	// Rendering
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(window);
#endif

	frame_ready = 0;

}

void SimVideo::CleanUp() {
#ifdef WIN32
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
}


void SimVideo::StartFrame() {
#ifdef WIN32
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
#else
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);
#endif
}

void SimVideo::Clock(bool hblank, bool vblank, bool hsync, bool vsync, uint32_t colour) {

	bool de = !(hblank || vblank);

	// Next line on rising hsync
	if (!vblank) {
		if (last_hsync && !hsync) {
			// Increment line and reset pixel count
			count_line++;
			count_pixel = 0;
		}
		else {
			// Increment pixel counter when not blanked
			if (de) {
				count_pixel++;
			}
		}
	}

	// Reset on rising vsync
	if (last_vsync && !vsync) {
		frame_ready = 1;
		count_frame++;
		count_line = 0;
#ifdef WIN32
		GetSystemTime(&actualtime);
		time_ms = (actualtime.wSecond * 1000) + actualtime.wMilliseconds;
#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		time_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000; // convert tv_sec & tv_usec to millisecond
#endif
		stats_frameTime = time_ms - old_time;
		old_time = time_ms;
		stats_fps = (float)(1000.0 / stats_frameTime);
	}

	// Only draw outside of blanks
	if (de) {

		int ox = count_pixel - 1;
		int oy = count_line - 1;
		int x = ox, xs = output_width, y = oy;

		if (output_rotate == -1) {
			// Rotate output by 90 degrees clockwise
			y = output_height - ox;
			xs = output_width;
			x = oy;
		}
		if (output_rotate == 1) {
			// Rotate output by 90 degrees clockwise
			y = ox;
			xs = output_width;
			x = output_width - oy;
		}

		if (output_vflip) {
			y = output_height - y;
		}

		// Clamp values to stop access violations on texture
		if (x < 0) { x = 0; }
		if (x > output_width - 1) { x = output_width - 1; }
		if (y < 0) { y = 0; }
		if (y > output_height - 1) { y = output_height - 1; }

		// Generate texture address
		uint32_t vga_addr = (y * xs) + x;

		// Write pixel to texture
		output_ptr[vga_addr] = colour;

	}

	// Track bounds (debug)
	if (count_pixel > stats_xMax) { stats_xMax = count_pixel; }
	if (count_line > stats_yMax) { stats_yMax = count_line; }
	if (count_pixel < stats_xMin) { stats_xMin = count_pixel; }
	if (count_line < stats_yMin) { stats_yMin = count_line; }

	last_hblank = hblank;
	last_vblank = vblank;
	last_hsync = hsync;
	last_vsync = vsync;
}