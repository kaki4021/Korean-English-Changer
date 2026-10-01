#pragma once
#include <Windows.h>
#include <vector>

// 클립보드 백업용 구조체
struct ClipboardBackupItem {
	UINT format;
	HGLOBAL hData;
};

class ClipboardManager
{
public:
	static int CopyText2Clipboard(const char* p_text);
	static int CopyText2Clipboard(const wchar_t* p_text);
	static char* GetClipboardText();

	static std::vector<ClipboardBackupItem> BackupClipboard();
	static void RestoreClipboard(const std::vector<ClipboardBackupItem>& backupList);

	static char* Wchar2Char(const wchar_t* p_wchar_string);
	static wchar_t* Char2Wchar(const char* p_char_string);
};

