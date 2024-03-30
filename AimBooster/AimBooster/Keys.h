#pragma once
#pragma once
#include <Windows.h>
//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

struct Keys {
	// Mouse and other non-alphabet keys
	static constexpr UINT MOUSE_LEFT = VK_LBUTTON; // 0x01
	static constexpr UINT MOURSE_RIGHT = VK_RBUTTON; // 0x02
	static constexpr UINT PAUSEBREAK = VK_CANCEL; // 0x03
	static constexpr UINT MOUSE_MIDDLE = VK_MBUTTON; // 0x04
	static constexpr UINT MOUSE_X1 = VK_XBUTTON1; // 0x05
	static constexpr UINT MOUSE_X2 = VK_XBUTTON2; // 0x06

	// VK_BACK to VK_MENU
	static constexpr UINT BACK = VK_BACK; // 0x08
	static constexpr UINT TAB = VK_TAB; // 0x09
	static constexpr UINT CLEAR = VK_CLEAR; // 0x0C
	static constexpr UINT RETURN = VK_RETURN; // 0x0D
	static constexpr UINT SHIFT = VK_SHIFT; // 0x10
	static constexpr UINT CONTROL = VK_CONTROL; // 0x11
	static constexpr UINT MENU = VK_MENU; // 0x12
	static constexpr UINT PAUSE = VK_PAUSE; // 0x13
	static constexpr UINT CAPITAL = VK_CAPITAL; // 0x14

	// IME and system keys
	static constexpr UINT KANA = VK_KANA; // 0x15 IME Kana mode
	static constexpr UINT HANGUL = VK_HANGUL; // 0x15 IME Hangul mode
	static constexpr UINT IME_ON = VK_IME_ON; // 0x16 IME On
	static constexpr UINT JUNJA = VK_JUNJA; // 0x17 IME Junja mode
	static constexpr UINT FINAL = VK_FINAL; // 0x18 IME final mode
	static constexpr UINT HANJA = VK_HANJA; // 0x19 IME Hanja mode
	static constexpr UINT KANJI = VK_KANJI; // 0x19 IME Kanji mode
	static constexpr UINT IME_OFF = VK_IME_OFF; // 0x1A IME Off
	static constexpr UINT ESCAPE = VK_ESCAPE; // 0x1B ESC key
	static constexpr UINT CONVERT = VK_CONVERT; // 0x1C IME convert
	static constexpr UINT NONCONVERT = VK_NONCONVERT; // 0x1D IME nonconvert
	static constexpr UINT ACCEPT = VK_ACCEPT; // 0x1E IME accept
	static constexpr UINT MODECHANGE = VK_MODECHANGE; // 0x1F IME mode change request

	// Navigation keys
	static constexpr UINT SPACE = VK_SPACE; // 0x20 SPACEBAR
	static constexpr UINT PRIOR = VK_PRIOR; // 0x21 PAGE UP key
	static constexpr UINT NEXT = VK_NEXT; // 0x22 PAGE DOWN key
	static constexpr UINT END = VK_END; // 0x23 END key
	static constexpr UINT HOME = VK_HOME; // 0x24 HOME key
	static constexpr UINT LEFTARROW = VK_LEFT; // 0x25 LEFT ARROW key
	static constexpr UINT UPARROW = VK_UP; // 0x26 UP ARROW key
	static constexpr UINT RIGHTARROW = VK_RIGHT; // 0x27 RIGHT ARROW key
	static constexpr UINT DOWNARROW = VK_DOWN; // 0x28 DOWN ARROW key

	// Function keys
	static constexpr UINT SELECT = VK_SELECT; // 0x29 SELECT key
	static constexpr UINT PRINT = VK_PRINT; // 0x2A PRINT key
	static constexpr UINT EXECUTE = VK_EXECUTE; // 0x2B EXECUTE key
	static constexpr UINT SNAPSHOT = VK_SNAPSHOT; // 0x2C PRINT SCREEN key
	static constexpr UINT INSERT = VK_INSERT; // 0x2D INS key
	static constexpr UINT DELKEY = VK_DELETE; // 0x2E DEL key
	static constexpr UINT HELP = VK_HELP; // 0x2F HELP key

	// Numeric keys
	static constexpr UINT Alpha0 = 0x30;
	static constexpr UINT Alpha1 = 0x31;
	static constexpr UINT Alpha2 = 0x32;
	static constexpr UINT Alpha3 = 0x33;
	static constexpr UINT Alpha4 = 0x34;
	static constexpr UINT Alpha5 = 0x35;
	static constexpr UINT Alpha6 = 0x36;
	static constexpr UINT Alpha7 = 0x37;
	static constexpr UINT Alpha8 = 0x38;
	static constexpr UINT Alpha9 = 0x39;

	// Alphabet keys
	static constexpr UINT A = 0x41;
	static constexpr UINT B = 0x42;
	static constexpr UINT C = 0x43;
	static constexpr UINT D = 0x44;
	static constexpr UINT E = 0x45;
	static constexpr UINT F = 0x46;
	static constexpr UINT G = 0x47;
	static constexpr UINT H = 0x48;
	static constexpr UINT I = 0x49;
	static constexpr UINT J = 0x4A;
	static constexpr UINT K = 0x4B;
	static constexpr UINT L = 0x4C;
	static constexpr UINT M = 0x4D;
	static constexpr UINT N = 0x4E;
	static constexpr UINT O = 0x4F;
	static constexpr UINT P = 0x50;
	static constexpr UINT Q = 0x51;
	static constexpr UINT R = 0x52;
	static constexpr UINT S = 0x53;
	static constexpr UINT T = 0x54;
	static constexpr UINT U = 0x55;
	static constexpr UINT V = 0x56;
	static constexpr UINT W = 0x57;
	static constexpr UINT X = 0x58;
	static constexpr UINT Y = 0x59;
	static constexpr UINT Z = 0x5A;

	// Windows keys
	static constexpr UINT WINLEFT = VK_LWIN; // 0x5B Left Windows key
	static constexpr UINT WINRIGHT = VK_RWIN; // 0x5C Right Windows key
	static constexpr UINT APPS = VK_APPS; // 0x5D Applications key
	static constexpr UINT SLEEP = VK_SLEEP; // 0x5F Computer Sleep key

	// Numeric keypad keys
	static constexpr UINT NUMPAD0 = VK_NUMPAD0; // 0x60 Numeric keypad 0 key
	static constexpr UINT NUMPAD1 = VK_NUMPAD1; // 0x61 Numeric keypad 1 key
	static constexpr UINT NUMPAD2 = VK_NUMPAD2; // 0x62 Numeric keypad 2 key
	static constexpr UINT NUMPAD3 = VK_NUMPAD3; // 0x63 Numeric keypad 3 key
	static constexpr UINT NUMPAD4 = VK_NUMPAD4; // 0x64 Numeric keypad 4 key
	static constexpr UINT NUMPAD5 = VK_NUMPAD5; // 0x65 Numeric keypad 5 key
	static constexpr UINT NUMPAD6 = VK_NUMPAD6; // 0x66 Numeric keypad 6 key
	static constexpr UINT NUMPAD7 = VK_NUMPAD7; // 0x67 Numeric keypad 7 key
	static constexpr UINT NUMPAD8 = VK_NUMPAD8; // 0x68 Numeric keypad 8 key
	static constexpr UINT NUMPAD9 = VK_NUMPAD9; // 0x69 Numeric keypad 9 key

	// Numeric keypad function keys
	static constexpr UINT MULTIPLY = VK_MULTIPLY; // 0x6A Multiply key
	static constexpr UINT ADD = VK_ADD; // 0x6B Add key
	static constexpr UINT SEPARATOR = VK_SEPARATOR; // 0x6C Separator key
	static constexpr UINT SUBTRACT = VK_SUBTRACT; // 0x6D Subtract key
	static constexpr UINT DECIMAL = VK_DECIMAL; // 0x6E Decimal key
	static constexpr UINT DIVIDE = VK_DIVIDE; // 0x6F Divide key

	// Function keys
	static constexpr UINT F1 = VK_F1; // 0x70 F1 key
	static constexpr UINT F2 = VK_F2; // 0x71 F2 key
	static constexpr UINT F3 = VK_F3; // 0x72 F3 key
	static constexpr UINT F4 = VK_F4; // 0x73 F4 key
	static constexpr UINT F5 = VK_F5; // 0x74 F5 key
	static constexpr UINT F6 = VK_F6; // 0x75 F6 key
	static constexpr UINT F7 = VK_F7; // 0x76 F7 key
	static constexpr UINT F8 = VK_F8; // 0x77 F8 key
	static constexpr UINT F9 = VK_F9; // 0x78 F9 key
	static constexpr UINT F10 = VK_F10; // 0x79 F10 key
	static constexpr UINT F11 = VK_F11; // 0x7A F11 key
	static constexpr UINT F12 = VK_F12; // 0x7B F12 key
	static constexpr UINT F13 = VK_F13; // 0x7C F13 key
	static constexpr UINT F14 = VK_F14; // 0x7D F14 key
	static constexpr UINT F15 = VK_F15; // 0x7E F15 key
	static constexpr UINT F16 = VK_F16; // 0x7F F16 key
	static constexpr UINT F17 = VK_F17; // 0x80 F17 key
	static constexpr UINT F18 = VK_F18; // 0x81 F18 key
	static constexpr UINT F19 = VK_F19; // 0x82 F19 key
	static constexpr UINT F20 = VK_F20; // 0x83 F20 key
	static constexpr UINT F21 = VK_F21; // 0x84 F21 key
	static constexpr UINT F22 = VK_F22; // 0x85 F22 key
	static constexpr UINT F23 = VK_F23; // 0x86 F23 key
	static constexpr UINT F24 = VK_F24; // 0x87 F24 key

	// Lock keys
	static constexpr UINT NUMLOCK = VK_NUMLOCK; // 0x90 NUM LOCK key
	static constexpr UINT SCROLL = VK_SCROLL; // 0x91 SCROLL LOCK key

	// Modifier keys
	static constexpr UINT SHIFT_LEFT = VK_LSHIFT; // 0xA0 Left SHIFT key
	static constexpr UINT SHIFT_RIGHT = VK_RSHIFT; // 0xA1 Right SHIFT key
	static constexpr UINT CONTROL_LEFT = VK_LCONTROL; // 0xA2 Left CONTROL key
	static constexpr UINT CONTROL_RIGHT = VK_RCONTROL; // 0xA3 Right CONTROL key
	static constexpr UINT ALT_LEFT = VK_LMENU; // 0xA4 Left ALT key
	static constexpr UINT ALT_RIGHT = VK_RMENU; // 0xA5 Right ALT key

	// Browser keys
	static constexpr UINT BROWSER_BACK = VK_BROWSER_BACK; // 0xA6 Browser Back key
	static constexpr UINT BROWSER_FORWARD = VK_BROWSER_FORWARD; // 0xA7 Browser Forward key
	static constexpr UINT BROWSER_REFRESH = VK_BROWSER_REFRESH; // 0xA8 Browser Refresh key
	static constexpr UINT BROWSER_STOP = VK_BROWSER_STOP; // 0xA9 Browser Stop key
	static constexpr UINT BROWSER_SEARCH = VK_BROWSER_SEARCH; // 0xAA Browser Search key
	static constexpr UINT BROWSER_FAVORITES = VK_BROWSER_FAVORITES; // 0xAB Browser Favorites key
	static constexpr UINT BROWSER_HOME = VK_BROWSER_HOME; // 0xAC Browser Start and Home key

	// Multimedia keys
	static constexpr UINT VOLUME_MUTE = VK_VOLUME_MUTE; // 0xAD Volume Mute key
	static constexpr UINT VOLUME_DOWN = VK_VOLUME_DOWN; // 0xAE Volume Down key
	static constexpr UINT VOLUME_UP = VK_VOLUME_UP; // 0xAF Volume Up key
	static constexpr UINT MEDIA_NEXT_TRACK = VK_MEDIA_NEXT_TRACK; // 0xB0 Next Track key
	static constexpr UINT MEDIA_PREV_TRACK = VK_MEDIA_PREV_TRACK; // 0xB1 Previous Track key
	static constexpr UINT MEDIA_STOP = VK_MEDIA_STOP; // 0xB2 Stop Media key
	static constexpr UINT MEDIA_PLAY_PAUSE = VK_MEDIA_PLAY_PAUSE; // 0xB3 Play/Pause Media key

	// Launch keys
	static constexpr UINT LAUNCH_MAIL = VK_LAUNCH_MAIL; // 0xB4 Start Mail key
	static constexpr UINT LAUNCH_MEDIA_SELECT = VK_LAUNCH_MEDIA_SELECT; // 0xB5 Select Media key
	static constexpr UINT LAUNCH_APP1 = VK_LAUNCH_APP1; // 0xB6 Start Application 1 key
	static constexpr UINT LAUNCH_APP2 = VK_LAUNCH_APP2; // 0xB7 Start Application 2 key

	// OEM keys
	static constexpr UINT OEM_1 = VK_OEM_1; // 0xBA ;: key
	static constexpr UINT OEM_PLUS = VK_OEM_PLUS; // 0xBB + key
	static constexpr UINT OEM_COMMA = VK_OEM_COMMA; // 0xBC , key
	static constexpr UINT OEM_MINUS = VK_OEM_MINUS; // 0xBD - key
	static constexpr UINT OEM_PERIOD = VK_OEM_PERIOD; // 0xBE . key
	static constexpr UINT OEM_2 = VK_OEM_2; // 0xBF /? key
	static constexpr UINT OEM_3 = VK_OEM_3; // 0xC0 `~ key
	static constexpr UINT OEM_4 = VK_OEM_4; // 0xDB [{ key
	static constexpr UINT OEM_5 = VK_OEM_5; // 0xDC \| key
	static constexpr UINT OEM_6 = VK_OEM_6; // 0xDD ]} key
	static constexpr UINT OEM_7 = VK_OEM_7; // 0xDE '" key
	static constexpr UINT OEM_8 = VK_OEM_8; // 0xDF Miscellaneous characters; varies by keyboard
	static constexpr UINT OEM_102 = VK_OEM_102; // 0xE2 <> or \| key on 102-key keyboard
	static constexpr UINT PROCESSKEY = VK_PROCESSKEY; // 0xE5 IME PROCESS key
	static constexpr UINT PACKET = VK_PACKET; // 0xE7 Used to pass Unicode characters as keystrokes
	static constexpr UINT ATTN = VK_ATTN; // 0xF6 Attn key
	static constexpr UINT CRSEL = VK_CRSEL; // 0xF7 CrSel key
	static constexpr UINT EXSEL = VK_EXSEL; // 0xF8 ExSel key
	static constexpr UINT EREOF = VK_EREOF; // 0xF9 Erase EOF key
	static constexpr UINT PLAY = VK_PLAY; // 0xFA Play key
	static constexpr UINT ZOOM = VK_ZOOM; // 0xFB Zoom key
	static constexpr UINT NONAME = VK_NONAME; // 0xFC Reserved
	static constexpr UINT PA1 = VK_PA1; // 0xFD PA1 key
	static constexpr UINT OEM_CLEAR = VK_OEM_CLEAR; // 0xFE Clear key
};
