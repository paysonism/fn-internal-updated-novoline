#include "includes.h"

/*
* Payson's Free Internal Drop | Paster's Academy
* 
* This is the #1 most ud internal on earth
* 
* Build as Release | Offsets in sdk.h | Main Cheat in hooking.h
* 
* github.com/paysonism
* 
*/

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		payson1337::init();
	}

	return TRUE;
}