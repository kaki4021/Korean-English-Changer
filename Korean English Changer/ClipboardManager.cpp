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

// 1. 현재 클립보드 전체 백업 (이미지, 파일 등 모든 포맷)
std::vector<ClipboardBackupItem> ClipboardManager::BackupClipboard() {
	std::vector<ClipboardBackupItem> backupList;
	if (!OpenClipboard(NULL)) return backupList;

	UINT format = 0;
	while ((format = EnumClipboardFormats(format)) != 0) {
		HGLOBAL hClipboardData = GetClipboardData(format);
		if (hClipboardData == NULL) continue;

		SIZE_T dataSize = GlobalSize(hClipboardData);
		if (dataSize == 0) continue;

		HGLOBAL hNewData = GlobalAlloc(GMEM_MOVEABLE, dataSize);
		if (hNewData == NULL) continue;

		void* pSource = GlobalLock(hClipboardData);
		void* pDest = GlobalLock(hNewData);
		if (pSource && pDest) {
			memcpy(pDest, pSource, dataSize);
		}
		GlobalUnlock(hClipboardData);
		GlobalUnlock(hNewData);

		backupList.push_back({ format, hNewData });
	}
	CloseClipboard();
	return backupList;
}

// 2. 백업된 데이터 원상복구
void ClipboardManager::RestoreClipboard(const std::vector<ClipboardBackupItem>& backupList) {
	if (backupList.empty()) return;
	if (!OpenClipboard(NULL)) {
		for (const auto& item : backupList) GlobalFree(item.hData);
		return;
	}

	EmptyClipboard(); // 새 공간 확보
	for (const auto& item : backupList) {
		if (!SetClipboardData(item.format, item.hData)) {
			GlobalFree(item.hData); // 실패 시에만 수동 해제
		}
	}
	CloseClipboard();
}

char* ClipboardManager::Wchar2Char(const wchar_t* p_wchar_string)
{
	size_t converted_chars = 0;
	size_t str_param_len = (wcslen(p_wchar_string) * 2) + 1;

	char* p_char_string = new char[str_param_len];
	wcstombs_s(&converted_chars, p_char_string, str_param_len, p_wchar_string, str_param_len);

	return p_char_string;
}

wchar_t* ClipboardManager::Char2Wchar(const char* p_char_string)
{
	size_t converted_wchars = 0;
	size_t str_param_len = strlen(p_char_string) + 1;

	wchar_t* p_wchar_string = new wchar_t[str_param_len];
	mbstowcs_s(&converted_wchars, p_wchar_string, str_param_len, p_char_string, str_param_len);

	return p_wchar_string;
}
