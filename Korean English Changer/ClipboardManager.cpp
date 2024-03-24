#include "ClipboardManager.h"

int ClipboardManager::CopyText2Clipboard(const char* p_string)
{
	size_t string_length = strlen(p_string) + 1;

	HANDLE h_data = GlobalAlloc(GMEM_MOVEABLE, string_length);
	if (h_data == NULL)
		return -1;

	char* p_data = (char*)GlobalLock(h_data);
	if (p_data == NULL)
		return -1;

	memcpy(p_data, p_string, string_length);
	GlobalUnlock(h_data);

	if (!OpenClipboard(NULL))
		return -1;
	EmptyClipboard();
	SetClipboardData(CF_TEXT, h_data);
	CloseClipboard();

    return 0;
}

int ClipboardManager::CopyText2Clipboard(const wchar_t* p_text)
{
	const char* p_text_char = ClipboardManager::Wchar2Char(p_text);
	return CopyText2Clipboard(p_text_char);
}

char* ClipboardManager::GetClipboardText()
{
	unsigned int priority_list = CF_TEXT;
	if (GetPriorityClipboardFormat(&priority_list, 1) != CF_TEXT)
		return NULL;

	char* p_string = NULL;
	if (!OpenClipboard(NULL))
		return NULL;

	HANDLE h_clipboard_data = GetClipboardData(CF_TEXT);
	if (h_clipboard_data == NULL)
		return NULL;

	char* p_clipboard_data = (char*)GlobalLock(h_clipboard_data);
	if (p_clipboard_data == NULL)
		return NULL;
	size_t string_len = strlen(p_clipboard_data) + 1;
	p_string = new char[string_len];

	memcpy(p_string, p_clipboard_data, string_len);
	GlobalUnlock(h_clipboard_data);
	CloseClipboard();

	return p_string;
}

char* ClipboardManager::Wchar2Char(const wchar_t* p_wchar_string)
{
	size_t converted_chars = 0;
	size_t str_param_len = (wcslen(p_wchar_string) * 2) + 1;

	char* p_char_string = new char[str_param_len];
	wcstombs_s(&converted_chars, p_char_string, str_param_len, p_wchar_string, str_param_len);

	return p_char_string;
}
