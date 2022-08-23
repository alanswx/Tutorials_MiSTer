#pragma once
#include "imgui.h"

struct DebugConsole {
public:
	void AddLog(const char* fmt, ...) IM_FMTARGS(2);
	DebugConsole();
	~DebugConsole();
	void ClearLog();
	void Draw(const char* title, bool* p_open, ImVec2 size);
	void    ExecCommand(const char* command_line);
	int     TextEditCallback(ImGuiInputTextCallbackData* data);
};
