#pragma once

#include <string>
#ifndef _MSC_VER
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#else
#define WIN32
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#endif

struct SimVideo {
public:

	int output_width;
	int output_height;
	int output_rotate;
	bool output_vflip;

	int count_pixel;
	int count_line;
	int count_frame;

	float stats_fps;
	float stats_frameTime;
	int stats_xMax;
	int stats_xMin;
	int stats_yMax;
	int stats_yMin;

	ImTextureID texture_id;

	SimVideo(int width, int height, int rotate);
	~SimVideo();
	void UpdateTexture();
	void CleanUp();
	void StartFrame();
	void Clock(bool hblank, bool vblank, bool hsync, bool vsync, uint32_t colour);
	int Initialise(const char* windowTitle);
};
