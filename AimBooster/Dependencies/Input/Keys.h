#pragma once
#include <Windows.h>
//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

struct Keys {
	// Mouse and other non-alphabet keys
	static constexpr UINT IK_LBUTTON = VK_LBUTTON; // 0x01
	static constexpr UINT IK_RBUTTON = VK_RBUTTON; // 0x02
	static constexpr UINT IK_CANCEL = VK_CANCEL; // 0x03
	static constexpr UINT IK_MBUTTON = VK_MBUTTON; // 0x04
	static constexpr UINT IK_XBUTTON1 = VK_XBUTTON1; // 0x05
	static constexpr UINT IK_XBUTTON2 = VK_XBUTTON2; // 0x06
	// VK_BACK to VK_MENU
	static constexpr UINT IK_BACK = VK_BACK; // 0x08
	static constexpr UINT IK_TAB = VK_TAB; // 0x09
	static constexpr UINT IK_CLEAR = VK_CLEAR; // 0x0C
	static constexpr UINT IK_RETURN = VK_RETURN; // 0x0D
	static constexpr UINT IK_SHIFT = VK_SHIFT; // 0x10
	static constexpr UINT IK_CONTROL = VK_CONTROL; // 0x11
	static constexpr UINT IK_MENU = VK_MENU; // 0x12
	static constexpr UINT IK_PAUSE = VK_PAUSE; // 0x13
	static constexpr UINT IK_CAPITAL = VK_CAPITAL; // 0x14
	// IME and system keys
	static constexpr UINT IK_KANA = VK_KANA; // 0x15 IME Kana mode
	static constexpr UINT IK_HANGUL = VK_HANGUL; // 0x15 IME Hangul mode
	static constexpr UINT IK_IME_ON = VK_IME_ON; // 0x16 IME On
	static constexpr UINT IK_JUNJA = VK_JUNJA; // 0x17 IME Junja mode
	static constexpr UINT IK_FINAL = VK_FINAL; // 0x18 IME final mode
	static constexpr UINT IK_HANJA = VK_HANJA; // 0x19 IME Hanja mode
	static constexpr UINT IK_KANJI = VK_KANJI; // 0x19 IME Kanji mode
	static constexpr UINT IK_IME_OFF = VK_IME_OFF; // 0x1A IME Off
	static constexpr UINT IK_ESCAPE = VK_ESCAPE; // 0x1B ESC key
	static constexpr UINT IK_CONVERT = VK_CONVERT; // 0x1C IME convert
	static constexpr UINT IK_NONCONVERT = VK_NONCONVERT; // 0x1D IME nonconvert
	static constexpr UINT IK_ACCEPT = VK_ACCEPT; // 0x1E IME accept
	static constexpr UINT IK_MODECHANGE = VK_MODECHANGE; // 0x1F IME mode change request

	// Navigation keys
	static constexpr UINT IK_SPACE = VK_SPACE; // 0x20 SPACEBAR
	static constexpr UINT IK_PRIOR = VK_PRIOR; // 0x21 PAGE UP key
	static constexpr UINT IK_NEXT = VK_NEXT; // 0x22 PAGE DOWN key
	static constexpr UINT IK_END = VK_END; // 0x23 END key
	static constexpr UINT IK_HOME = VK_HOME; // 0x24 HOME key
	static constexpr UINT IK_LEFT = VK_LEFT; // 0x25 LEFT ARROW key
	static constexpr UINT IK_UP = VK_UP; // 0x26 UP ARROW key
	static constexpr UINT IK_RIGHT = VK_RIGHT; // 0x27 RIGHT ARROW key
	static constexpr UINT IK_DOWN = VK_DOWN; // 0x28 DOWN ARROW key

	// Function keys
	static constexpr UINT IK_SELECT = VK_SELECT; // 0x29 SELECT key
	static constexpr UINT IK_PRINT = VK_PRINT; // 0x2A PRINT key
	static constexpr UINT IK_EXECUTE = VK_EXECUTE; // 0x2B EXECUTE key
	static constexpr UINT IK_SNAPSHOT = VK_SNAPSHOT; // 0x2C PRINT SCREEN key
	static constexpr UINT IK_INSERT = VK_INSERT; // 0x2D INS key
	static constexpr UINT IK_DELETE = VK_DELETE; // 0x2E DEL key
	static constexpr UINT IK_HELP = VK_HELP; // 0x2F HELP key

	// Numeric keys
	static constexpr UINT IK_0 = 0x30;
	static constexpr UINT IK_1 = 0x31;
	static constexpr UINT IK_2 = 0x32;
	static constexpr UINT IK_3 = 0x33;
	static constexpr UINT IK_4 = 0x34;
	static constexpr UINT IK_5 = 0x35;
	static constexpr UINT IK_6 = 0x36;
	static constexpr UINT IK_7 = 0x37;
	static constexpr UINT IK_8 = 0x38;
	static constexpr UINT IK_9 = 0x39;
	// Alphabet keys
	static constexpr UINT IK_A = 0x41;
	static constexpr UINT IK_B = 0x42;
	static constexpr UINT IK_C = 0x43;
	static constexpr UINT IK_D = 0x44;
	static constexpr UINT IK_E = 0x45;
	static constexpr UINT IK_F = 0x46;
	static constexpr UINT IK_G = 0x47;
	static constexpr UINT IK_H = 0x48;
	static constexpr UINT IK_I = 0x49;
	static constexpr UINT IK_J = 0x4A;
	static constexpr UINT IK_K = 0x4B;
	static constexpr UINT IK_L = 0x4C;
	static constexpr UINT IK_M = 0x4D;
	static constexpr UINT IK_N = 0x4E;
	static constexpr UINT IK_O = 0x4F;
	static constexpr UINT IK_P = 0x50;
	static constexpr UINT IK_Q = 0x51;
	static constexpr UINT IK_R = 0x52;
	static constexpr UINT IK_S = 0x53;
	static constexpr UINT IK_T = 0x54;
	static constexpr UINT IK_U = 0x55;
	static constexpr UINT IK_V = 0x56;
	static constexpr UINT IK_W = 0x57;
	static constexpr UINT IK_X = 0x58;
	static constexpr UINT IK_Y = 0x59;
	static constexpr UINT IK_Z = 0x5A;

	// Windows keys
	static constexpr UINT IK_LWIN = VK_LWIN; // 0x5B Left Windows key
	static constexpr UINT IK_RWIN = VK_RWIN; // 0x5C Right Windows key
	static constexpr UINT IK_APPS = VK_APPS; // 0x5D Applications key
	static constexpr UINT IK_SLEEP = VK_SLEEP; // 0x5F Computer Sleep key

	// Numeric keypad keys
	static constexpr UINT IK_NUMPAD0 = VK_NUMPAD0; // 0x60 Numeric keypad 0 key
	static constexpr UINT IK_NUMPAD1 = VK_NUMPAD1; // 0x61 Numeric keypad 1 key
	static constexpr UINT IK_NUMPAD2 = VK_NUMPAD2; // 0x62 Numeric keypad 2 key
	static constexpr UINT IK_NUMPAD3 = VK_NUMPAD3; // 0x63 Numeric keypad 3 key
	static constexpr UINT IK_NUMPAD4 = VK_NUMPAD4; // 0x64 Numeric keypad 4 key
	static constexpr UINT IK_NUMPAD5 = VK_NUMPAD5; // 0x65 Numeric keypad 5 key
	static constexpr UINT IK_NUMPAD6 = VK_NUMPAD6; // 0x66 Numeric keypad 6 key
	static constexpr UINT IK_NUMPAD7 = VK_NUMPAD7; // 0x67 Numeric keypad 7 key
	static constexpr UINT IK_NUMPAD8 = VK_NUMPAD8; // 0x68 Numeric keypad 8 key
	static constexpr UINT IK_NUMPAD9 = VK_NUMPAD9; // 0x69 Numeric keypad 9 key

	// Numeric keypad function keys
	static constexpr UINT IK_MULTIPLY = VK_MULTIPLY; // 0x6A Multiply key
	static constexpr UINT IK_ADD = VK_ADD; // 0x6B Add key
	static constexpr UINT IK_SEPARATOR = VK_SEPARATOR; // 0x6C Separator key
	static constexpr UINT IK_SUBTRACT = VK_SUBTRACT; // 0x6D Subtract key
	static constexpr UINT IK_DECIMAL = VK_DECIMAL; // 0x6E Decimal key
	static constexpr UINT IK_DIVIDE = VK_DIVIDE; // 0x6F Divide key

	// Function keys
	static constexpr UINT IK_F1 = VK_F1; // 0x70 F1 key
	static constexpr UINT IK_F2 = VK_F2; // 0x71 F2 key
	static constexpr UINT IK_F3 = VK_F3; // 0x72 F3 key
	static constexpr UINT IK_F4 = VK_F4; // 0x73 F4 key
	static constexpr UINT IK_F5 = VK_F5; // 0x74 F5 key
	static constexpr UINT IK_F6 = VK_F6; // 0x75 F6 key
	static constexpr UINT IK_F7 = VK_F7; // 0x76 F7 key
	static constexpr UINT IK_F8 = VK_F8; // 0x77 F8 key
	static constexpr UINT IK_F9 = VK_F9; // 0x78 F9 key
	static constexpr UINT IK_F10 = VK_F10; // 0x79 F10 key
	static constexpr UINT IK_F11 = VK_F11; // 0x7A F11 key
	static constexpr UINT IK_F12 = VK_F12; // 0x7B F12 key
	static constexpr UINT IK_F13 = VK_F13; // 0x7C F13 key
	static constexpr UINT IK_F14 = VK_F14; // 0x7D F14 key
	static constexpr UINT IK_F15 = VK_F15; // 0x7E F15 key
	static constexpr UINT IK_F16 = VK_F16; // 0x7F F16 key
	static constexpr UINT IK_F17 = VK_F17; // 0x80 F17 key
	static constexpr UINT IK_F18 = VK_F18; // 0x81 F18 key
	static constexpr UINT IK_F19 = VK_F19; // 0x82 F19 key
	static constexpr UINT IK_F20 = VK_F20; // 0x83 F20 key
	static constexpr UINT IK_F21 = VK_F21; // 0x84 F21 key
	static constexpr UINT IK_F22 = VK_F22; // 0x85 F22 key
	static constexpr UINT IK_F23 = VK_F23; // 0x86 F23 key
	static constexpr UINT IK_F24 = VK_F24; // 0x87 F24 key

	// Lock keys
	static constexpr UINT IK_NUMLOCK = VK_NUMLOCK; // 0x90 NUM LOCK key
	static constexpr UINT IK_SCROLL = VK_SCROLL; // 0x91 SCROLL LOCK key

	// Modifier keys
	static constexpr UINT IK_LSHIFT = VK_LSHIFT; // 0xA0 Left SHIFT key
	static constexpr UINT IK_RSHIFT = VK_RSHIFT; // 0xA1 Right SHIFT key
	static constexpr UINT IK_LCONTROL = VK_LCONTROL; // 0xA2 Left CONTROL key
	static constexpr UINT IK_RCONTROL = VK_RCONTROL; // 0xA3 Right CONTROL key
	static constexpr UINT IK_LMENU = VK_LMENU; // 0xA4 Left ALT key
	static constexpr UINT IK_RMENU = VK_RMENU; // 0xA5 Right ALT key

	// Browser keys
	static constexpr UINT IK_BROWSER_BACK = VK_BROWSER_BACK; // 0xA6 Browser Back key
	static constexpr UINT IK_BROWSER_FORWARD = VK_BROWSER_FORWARD; // 0xA7 Browser Forward key
	static constexpr UINT IK_BROWSER_REFRESH = VK_BROWSER_REFRESH; // 0xA8 Browser Refresh key
	static constexpr UINT IK_BROWSER_STOP = VK_BROWSER_STOP; // 0xA9 Browser Stop key
	static constexpr UINT IK_BROWSER_SEARCH = VK_BROWSER_SEARCH; // 0xAA Browser Search key
	static constexpr UINT IK_BROWSER_FAVORITES = VK_BROWSER_FAVORITES; // 0xAB Browser Favorites key
	static constexpr UINT IK_BROWSER_HOME = VK_BROWSER_HOME; // 0xAC Browser Start and Home key

	// Multimedia keys
	static constexpr UINT IK_VOLUME_MUTE = VK_VOLUME_MUTE; // 0xAD Volume Mute key
	static constexpr UINT IK_VOLUME_DOWN = VK_VOLUME_DOWN; // 0xAE Volume Down key
	static constexpr UINT IK_VOLUME_UP = VK_VOLUME_UP; // 0xAF Volume Up key
	static constexpr UINT IK_MEDIA_NEXT_TRACK = VK_MEDIA_NEXT_TRACK; // 0xB0 Next Track key
	static constexpr UINT IK_MEDIA_PREV_TRACK = VK_MEDIA_PREV_TRACK; // 0xB1 Previous Track key
	static constexpr UINT IK_MEDIA_STOP = VK_MEDIA_STOP; // 0xB2 Stop Media key
	static constexpr UINT IK_MEDIA_PLAY_PAUSE = VK_MEDIA_PLAY_PAUSE; // 0xB3 Play/Pause Media key

	// Launch keys
	static constexpr UINT IK_LAUNCH_MAIL = VK_LAUNCH_MAIL; // 0xB4 Start Mail key
	static constexpr UINT IK_LAUNCH_MEDIA_SELECT = VK_LAUNCH_MEDIA_SELECT; // 0xB5 Select Media key
	static constexpr UINT IK_LAUNCH_APP1 = VK_LAUNCH_APP1; // 0xB6 Start Application 1 key
	static constexpr UINT IK_LAUNCH_APP2 = VK_LAUNCH_APP2; // 0xB7 Start Application 2 key

	// OEM keys
	static constexpr UINT IK_OEM_1 = VK_OEM_1; // 0xBA ;: key
	static constexpr UINT IK_OEM_PLUS = VK_OEM_PLUS; // 0xBB + key
	static constexpr UINT IK_OEM_COMMA = VK_OEM_COMMA; // 0xBC , key
	static constexpr UINT IK_OEM_MINUS = VK_OEM_MINUS; // 0xBD - key
	static constexpr UINT IK_OEM_PERIOD = VK_OEM_PERIOD; // 0xBE . key
	static constexpr UINT IK_OEM_2 = VK_OEM_2; // 0xBF /? key
	static constexpr UINT IK_OEM_3 = VK_OEM_3; // 0xC0 `~ key
	static constexpr UINT IK_OEM_4 = VK_OEM_4; // 0xDB [{ key
	static constexpr UINT IK_OEM_5 = VK_OEM_5; // 0xDC \| key
	static constexpr UINT IK_OEM_6 = VK_OEM_6; // 0xDD ]} key
	static constexpr UINT IK_OEM_7 = VK_OEM_7; // 0xDE '" key
	static constexpr UINT IK_OEM_8 = VK_OEM_8; // 0xDF Miscellaneous characters; varies by keyboard
	static constexpr UINT IK_OEM_102 = VK_OEM_102; // 0xE2 <> or \| key on 102-key keyboard
	static constexpr UINT IK_PROCESSKEY = VK_PROCESSKEY; // 0xE5 IME PROCESS key
	static constexpr UINT IK_PACKET = VK_PACKET; // 0xE7 Used to pass Unicode characters as keystrokes
	static constexpr UINT IK_ATTN = VK_ATTN; // 0xF6 Attn key
	static constexpr UINT IK_CRSEL = VK_CRSEL; // 0xF7 CrSel key
	static constexpr UINT IK_EXSEL = VK_EXSEL; // 0xF8 ExSel key
	static constexpr UINT IK_EREOF = VK_EREOF; // 0xF9 Erase EOF key
	static constexpr UINT IK_PLAY = VK_PLAY; // 0xFA Play key
	static constexpr UINT IK_ZOOM = VK_ZOOM; // 0xFB Zoom key
	static constexpr UINT IK_NONAME = VK_NONAME; // 0xFC Reserved
	static constexpr UINT IK_PA1 = VK_PA1; // 0xFD PA1 key
	static constexpr UINT IK_OEM_CLEAR = VK_OEM_CLEAR; // 0xFE Clear key
};
