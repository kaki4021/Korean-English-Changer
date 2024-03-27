#include <iostream>
#include <Windows.h>
#include "ClipboardManager.h"
#include "KoreanMergeManager.h"

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
	HANDLE Mutex;
	const wchar_t ProgMutex[] = L"Korean English Changer";
	if ((Mutex = OpenMutex(MUTEX_ALL_ACCESS, false, ProgMutex)) == NULL)
		Mutex = CreateMutex(NULL, true, ProgMutex);
	else {
		MessageBox(NULL, L"이미 실행중입니다.", L"알림", MB_OK);
		return 0;
	}

	setlocale(LC_ALL, "korean");
	RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x15); //Ctrl + 한/영
	RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 0x15); //Ctrl + Alt + 한/영
	RegisterHotKey(NULL, 3, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x15); //Ctrl + Shift + 한/영
	RegisterHotKey(NULL, 4, MOD_CONTROL | MOD_SHIFT | MOD_ALT | MOD_NOREPEAT, 0x15); //Ctrl + Shift + Alt + 한/영

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
				//MessageBox(NULL, L"get clipboard text error", L"ERROR", MB_OK);
				wchar_t* w_clipboard_text = ClipboardManager::Char2Wchar(clipboard_text);
				wchar_t* korean_char = KoreanMergeManager::KoreanMerge(w_clipboard_text);

				int copy_korean_char_2_clipboard_result = ClipboardManager::CopyText2Clipboard(korean_char);
				if (copy_korean_char_2_clipboard_result == -1) //check error
					continue;
				//MessageBox(NULL, L"copy text to clipboard error", L"ERROR", MB_OK);

				ExecuteCtrlV();
			}
			else if (msg.wParam == 2) //Ctrl + Alt + 한/영
			{
				char* clipboard_text = ClipboardManager::GetClipboardText();
				if (clipboard_text == NULL) //check error
					continue;
					//MessageBox(NULL, L"get clipboard text error", L"ERROR", MB_OK);
				wchar_t* w_clipboard_text = ClipboardManager::Char2Wchar(clipboard_text);
				wchar_t* korean_char = KoreanMergeManager::KoreanMerge(w_clipboard_text);

				int copy_korean_char_2_clipboard_result = ClipboardManager::CopyText2Clipboard(korean_char);
				if (copy_korean_char_2_clipboard_result == -1) //check error
					continue;
					//MessageBox(NULL, L"copy text to clipboard error", L"ERROR", MB_OK);
			}
			else if (msg.wParam == 3) //Ctrl + Shift + 한/영
			{

			}
			else if (msg.wParam == 4) //Ctrl + Shift + Alt + 한/영
			{

			}
		}
	}

	UnregisterHotKey(NULL, 1);
	UnregisterHotKey(NULL, 2);
	UnregisterHotKey(NULL, 3);
	UnregisterHotKey(NULL, 4);

	return 0;
}
