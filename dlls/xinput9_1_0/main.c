#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "windef.h"
#include "winbase.h"
#include "winerror.h"
#include "winuser.h"
#include "winreg.h"
#include "wingdi.h"
#include "winnls.h"
#include "winternl.h"

#include "dbt.h"
#include "setupapi.h"
#include "devpkey.h"
#include "hidusage.h"
#include "ddk/hidsdi.h"
#include "initguid.h"
#include "devguid.h"

#include "wine/debug.h"

#include "xinput.h"
#include "xinput9_1_0.h"

WINE_DEFAULT_DEBUG_CHANNEL(xinput);

namespace xinput9_1_0
{
	
	BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved) 
	{
		switch (reason)
    		{
    		case DLL_PROCESS_ATTACH:
			if (!LoadLibraryA("xinput1_4.dll"))
			{
				return FALSE;
			}
        		DisableThreadLibraryCalls(inst);
        		break;
    		case DLL_PROCESS_DETACH:
        		if (reserved) break;
			break;
    		}
    		return TRUE;
	}

	DWORD WINAPI DECLSPEC_HOTPATCH XInputGetCapabilities(DWORD index, DWORD flags, XINPUT_CAPABILITIES *capabilities) 
	{
		return ::XInputGetCapabilities(index, flags, capabilities);
	}
	
	DWORD WINAPI DECLSPEC_HOTPATCH XInputGetDSoundAudioDeviceGuids(DWORD index, GUID *render_guid, GUID *capture_guid) 
	{
		return ::XInputGetDSoundAudioDeviceGuids(index, render_guid, capture_guid);
	}

	DWORD WINAPI DECLSPEC_HOTPATCH XInputSetState(DWORD index, XINPUT_VIBRATION *vibration)
	{
		return ::XInputGetState(index, vibration);
	}
	
	DWORD WINAPI DECLSPEC_HOTPATCH XInputGetState(DWORD index, XINPUT_STATE *state) 
	{
		return ::XInputGetState(index, state);
	}
}
