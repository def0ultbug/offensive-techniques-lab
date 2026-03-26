
/*
IsDebuggerPresent Replacement (1)
*/

BOOL IsDebuggerPresent2() {

  // getting the PEB structure
#ifdef _WIN64
	PPEB					pPeb = (PEB*)(__readgsqword(0x60));
#elif _WIN32
	PPEB					pPeb = (PEB*)(__readfsdword(0x30));
#endif

  // checking the 'BeingDebugged' element
  if (pPeb->BeingDebugged == 1) 
    return TRUE;
	
   return FALSE;
}


/*
IsDebuggerPresent Replacement (2)
*/


BOOL IsDebuggerPresent2() {

  // getting the PEB structure
#ifdef _WIN64
  PPEB          pPeb = (PEB*)(__readgsqword(0x60));
#elif _WIN32
  PPEB          pPeb = (PEB*)(__readfsdword(0x30));
#endif

  // checking the 'BeingDebugged' element
  if (pPeb->BeingDebugged == 1) 
    return TRUE;
  
   return FALSE;
}