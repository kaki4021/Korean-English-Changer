#pragma once
#include <Windows.h>

class ClipboardManager
{
public:
	static int CopyText2Clipboard(const char* p_text);
	static int CopyText2Clipboard(const wchar_t* p_text);
	static char* GetClipboardText();

	static char* Wchar2Char(const wchar_t* p_wchar_string);
	static wchar_t* Char2Wchar(const char* p_char_string);
};

