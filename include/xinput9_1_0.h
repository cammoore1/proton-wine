#ifndef __WINE_XINPUT9_1_0_H
#define __WINE_XINPUT9_1_0_H

DWORD WINAPI XInputSetState(DWORD, XINPUT_VIBRATION*);
DWORD WINAPI XInputGetState(DWORD, XINPUT_STATE*);
DWORD WINAPI XInputGetCapabilities(DWORD, DWORD, XINPUT_CAPABILITIES*);
DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD, GUID*, GUID*);



#endif /* __WINE_XINPUT9_1_0_H */
