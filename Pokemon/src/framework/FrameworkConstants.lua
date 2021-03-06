--[[
	Description: Framework constants
	Author: M.Wan
	Date: 07/06/2014
]]

pf = pf or {}

pf.Handler = pf.Handler or {}

pf.Handler.LISTMENU_ITEM_SELECTED = 0
pf.Handler.LISTMENU_ITEM_FOCUSED = 1
pf.Handler.LISTMENU_ITEM_BLURRED = 2
pf.Handler.LISTMENU_ITEM_WILL_RECYCLE = 3
pf.Handler.LISTMENU_ITEM_SIZE_FOR_MENU = 4
pf.Handler.LISTMENU_ITEM_AT_INDEX = 5
pf.Handler.LISTMENU_COUNT_OF_ITEMS = 6

pf.Handler.DIRECTIONCONTROLLER_ON_RIGHT = 0
pf.Handler.DIRECTIONCONTROLLER_ON_LEFT = 1
pf.Handler.DIRECTIONCONTROLLER_ON_UP = 2
pf.Handler.DIRECTIONCONTROLLER_ON_DOWN = 3
pf.Handler.DIRECTIONCONTROLLER_ON_STOP = 4

pf.Handler.CHECKEDBUTTON_ON_CHECKED = 0
pf.Handler.CHECKEDBUTTON_ON_UNCHECKED = 1

pf.Handler.WIN32_KEYBOARD_DOWN = 1
pf.Handler.WIN32_KEYBOARD_UP = 2

pf.Win32KeyCode = {
	VK_BACK = 0x08,
	VK_TAB = 0x09,
	VK_CLEAR = 0x0C,
	VK_RETURN = 0x0D,
	VK_SHIFT = 0x10,
	VK_CONTROL = 0x11,
	VK_ALT = 0x12,
	VK_PAUSE = 0x13,
	VK_CAPITAL = 0x14,
	VK_ESCAPE = 0x1B,
	VK_SPACE = 0x20,
	VK_PGUP = 0x21,
	VK_PGDOWN = 0x22,
	VK_END = 0x23,
	VK_HOME = 0x24,
	VK_LEFT = 0x25,
	VK_UP = 0x26,
	VK_RIGHT = 0x27,
	VK_DOWN = 0x28,
	VK_SELECT = 0x29,
	VK_PRINT = 0x2A,
	VK_EXECUTE = 0x2B,
	VK_SNAPSHOT = 0x2C,
	VK_INSERT = 0x2D,
	VK_DELETE = 0x2E,
	VK_HELP = 0x2F,
	VK_0 = '0',
	VK_1 = '1',
	VK_2 = '2',
	VK_3 = '3',
	VK_4 = '4',
	VK_5 = '5',
	VK_6 = '6',
	VK_7 = '7',
	VK_8 = '8',
	VK_9 = '9',
	VK_A = 'A',
	VK_B = 'B',
	VK_C = 'C',
	VK_D = 'D',
	VK_E = 'E',
	VK_F = 'F',
	VK_G = 'G',
	VK_H = 'H',
	VK_I = 'I',
	VK_J = 'J',
	VK_K = 'K',
	VK_L = 'L',
	VK_M = 'M',
	VK_N = 'N',
	VK_O = 'O',
	VK_P = 'P',
	VK_Q = 'Q',
	VK_R = 'R',
	VK_S = 'S',
	VK_T = 'T',
	VK_U = 'U',
	VK_V = 'V',
	VK_W = 'W',
	VK_X = 'X',
	VK_Y = 'Y',
	VK_Z = 'Z',
	VK_LWIN = 0x5B,
	VK_RWIN = 0x5C,
	VK_APPS = 0x5D,
	VK_NUMPAD0 = 0x60,
	VK_NUMPAD1 = 0x61,
	VK_NUMPAD2 = 0x62,
	VK_NUMPAD3 = 0x63,
	VK_NUMPAD4 = 0x64,
	VK_NUMPAD5 = 0x65,
	VK_NUMPAD6 = 0x66,
	VK_NUMPAD7 = 0x67,
	VK_NUMPAD8 = 0x68,
	VK_NUMPAD9 = 0x69,
	VK_MULTIPLY = 0x6A,
	VK_ADD = 0x6B,
	VK_SEPARATOR = 0x6C,
	VK_SUBSTRACT = 0x6D,
	VK_DECIMAL = 0x6E,
	VK_DIVIDE = 0x6F,
	VK_F1 = 0x70,
	VK_F2 = 0x71,
	VK_F3 = 0x72,
	VK_F4 = 0x73,
	VK_F5 = 0x74,
	VK_F6 = 0x75,
	VK_F7 = 0x76,
	VK_F8 = 0x77,
	VK_F9 = 0x78,
	VK_F10 = 0x79,
	VK_F11 = 0x7A,
	VK_F12 = 0x7B,
	VK_NUMLOCK = 0x90,
	VK_SCROLL = 0x91,
	VK_LSHIFT = 0xA0,
	VK_RSHIFT = 0xA1,
	VK_LCONTROL = 0xA2,
	VK_RCONTROL = 0xA3,
	VK_LMENU = 0xA4,
	VK_RMENU = 0xA5,
	VK_MINUS = 0xBD,
	VK_EQUAL = 0xBB,
}