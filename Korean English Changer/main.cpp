#include <locale.h>
#include <Windows.h>
#include "ClipboardManager.h"
#include "KoreanMergeManager.h"
#include "KoreanDecompositionManager.h"

void UpShift()
{
	INPUT keyinput;
	keyinput.type = INPUT_KEYBOARD;
	keyinput.ki.wVk = VK_SHIFT;
	keyinput.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &keyinput, sizeof(INPUT));
}

void ExecuteCtrlC()
{
	INPUT keyinput[5];
	keyinput[0].type = INPUT_KEYBOARD;
	keyinput[0].ki.wVk = VK_CONTROL;
	keyinput[0].ki.dwFlags = KEYEVENTF_KEYUP;
	keyinput[1].type = INPUT_KEYBOARD;
	keyinput[1].ki.wVk = VK_CONTROL;
	keyinput[1].ki.dwFlags = 0;
	keyinput[2].type = INPUT_KEYBOARD;
	keyinput[2].ki.wVk = 'C';
	keyinput[2].ki.dwFlags = 0;
	keyinput[3].type = INPUT_KEYBOARD;
	keyinput[3].ki.wVk = 'C';
	keyinput[3].ki.dwFlags = KEYEVENTF_KEYUP;
	keyinput[4].type = INPUT_KEYBOARD;
	keyinput[4].ki.wVk = VK_CONTROL;
	keyinput[4].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(5, keyinput, sizeof(INPUT));
}

void ExecuteCtrlV()
{
	INPUT keyinput[5];
	keyinput[0].type = INPUT_KEYBOARD;
	keyinput[0].ki.wVk = VK_CONTROL;
	keyinput[0].ki.dwFlags = KEYEVENTF_KEYUP;
	keyinput[1].type = INPUT_KEYBOARD;
	keyinput[1].ki.wVk = VK_CONTROL;
	keyinput[1].ki.dwFlags = 0;
	keyinput[2].type = INPUT_KEYBOARD;
	keyinput[2].ki.wVk = 'V';
	keyinput[2].ki.dwFlags = 0;
	keyinput[3].type = INPUT_KEYBOARD;
	keyinput[3].ki.wVk = 'V';
	keyinput[3].ki.dwFlags = KEYEVENTF_KEYUP;
	keyinput[4].type = INPUT_KEYBOARD;
	keyinput[4].ki.wVk = VK_CONTROL;
	keyinput[4].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(5, keyinput, sizeof(INPUT));
}

int WINAPI
WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ char*, _In_ int)
{
	//중복 실행 방지
	HANDLE Mutex;
	const wchar_t ProgMutex[] = L"Korean English Changer";
	if ((Mutex = OpenMutex(MUTEX_ALL_ACCESS, false, ProgMutex)) == NULL)
		Mutex = CreateMutex(NULL, true, ProgMutex);
	else {
		MessageBox(NULL, L"이미 실행중입니다.", L"알림", MB_OK);
		return 0;
	}


	//한글 설정(char <-> wchar_t 변환에 필요함)
	setlocale(LC_ALL, "korean");


	//시작 프로그램 등록
	wchar_t exePath[MAX_PATH];
	GetModuleFileName(NULL, exePath, MAX_PATH);

	HKEY hKey;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {

		if (RegSetValueEx(hKey, L"Korean English Changer", 0, REG_SZ, (BYTE*)exePath, (DWORD)(wcslen(exePath) + 1) * sizeof(char)) != ERROR_SUCCESS) {
			MessageBox(NULL, L"Registry value setting failed", L"ERROR", MB_OK);
		}

		RegCloseKey(hKey);
	}
	else
	{
		MessageBox(NULL, L"Registry value setting failed", L"ERROR", MB_OK);
	}


	//단축키 등록
	RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x15); //Ctrl + 한/영
	RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 0x15); //Ctrl + Alt + 한/영
	RegisterHotKey(NULL, 3, MOD_SHIFT | MOD_NOREPEAT, 0x15); //Shift + 한/영
	RegisterHotKey(NULL, 4, MOD_SHIFT | MOD_ALT | MOD_NOREPEAT, 0x15); //Shift + Alt + 한/영
	

	//단축키 처리
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			if (msg.wParam == 1) //Ctrl + 한/영
			{
				ExecuteCtrlC();

				Sleep(10); //wating copy

				char* clipboard_text = ClipboardManager::GetClipboardText();
				if (clipboard_text == NULL) //check error
					continue;
				wchar_t* w_clipboard_text = ClipboardManager::Char2Wchar(clipboard_text);
				wchar_t* korean_char = KoreanMergeManager::KoreanMerge(w_clipboard_text);

				int copy_korean_char_2_clipboard_result = ClipboardManager::CopyText2Clipboard(korean_char);
				if (copy_korean_char_2_clipboard_result == -1) //check error
					continue;

				ExecuteCtrlV();
			}
			else if (msg.wParam == 2) //Ctrl + Alt + 한/영
			{
				char* clipboard_text = ClipboardManager::GetClipboardText();
				if (clipboard_text == NULL) //check error
					continue;
				wchar_t* w_clipboard_text = ClipboardManager::Char2Wchar(clipboard_text);
				wchar_t* korean_char = KoreanMergeManager::KoreanMerge(w_clipboard_text);

				int copy_korean_char_2_clipboard_result = ClipboardManager::CopyText2Clipboard(korean_char);
				if (copy_korean_char_2_clipboard_result == -1) //check error
					continue;
			}
			else if (msg.wParam == 3) //Shift + 한/영
			{
				UpShift();
				ExecuteCtrlC();

				Sleep(10); //wating copy

				char* clipboard_text = ClipboardManager::GetClipboardText();
				if (clipboard_text == NULL) //check error
					continue;
				wchar_t* w_clipboard_text = ClipboardManager::Char2Wchar(clipboard_text);
				wchar_t* english_char = KoreanDecompositionManager::KoreanDecomposition(w_clipboard_text);

				int copy_english_char_2_clipboard_result = ClipboardManager::CopyText2Clipboard(english_char);
				if (copy_english_char_2_clipboard_result == -1) //check error
					continue;

				ExecuteCtrlV();
			}
			else if (msg.wParam == 4) //Shift + Alt + 한/영
			{
				char* clipboard_text = ClipboardManager::GetClipboardText();
				if (clipboard_text == NULL) //check error
					continue;
				wchar_t* w_clipboard_text = ClipboardManager::Char2Wchar(clipboard_text);
				wchar_t* english_char = KoreanDecompositionManager::KoreanDecomposition(w_clipboard_text);

				int copy_english_char_2_clipboard_result = ClipboardManager::CopyText2Clipboard(english_char);
				if (copy_english_char_2_clipboard_result == -1) //check error
					continue;
			}
		}
	}


	//단축키 해제
	UnregisterHotKey(NULL, 1);
	UnregisterHotKey(NULL, 2);
	UnregisterHotKey(NULL, 3);
	UnregisterHotKey(NULL, 4);

	return 0;
}
