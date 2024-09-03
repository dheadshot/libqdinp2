#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "qdinpm.h"

#ifdef COHERENT /* For compatibility with Coherent and other older *NIXes, define COHERENT! */
#include <termio.h>
#elif !defined(WINDOWS)
#include <termios.h>
#endif
#ifndef WINDOWS
#include <unistd.h>
#include <signal.h>
#else
#include <Windows.h>
#include <Wincon.h>
#include <winuser.h>
#endif

/* Redefs for older WinCons */
#if defined (WINDOWS) && (! defined (VK_XBUTTON1) )
#define VK_XBUTTON1 0x05
#endif
#if defined (WINDOWS) && (! defined ( VK_XBUTTON2 ) )
#define VK_XBUTTON2 0x06
#endif
#if defined (WINDOWS) && (! defined ( VK_HANGUL ) )
#define VK_HANGUL 0x15
#endif
#if defined (WINDOWS) && (! defined ( VK_JUNJA ) )
#define VK_JUNJA 0x17
#endif
#if defined (WINDOWS) && (! defined ( VK_FINAL ) )
#define VK_FINAL 0x18
#endif
#if defined (WINDOWS) && (! defined ( VK_HANJA ) )
#define VK_HANJA 0x19
#endif
#if defined (WINDOWS) && (! defined ( VK_KANJI ) )
#define VK_KANJI 0x19
#endif
#if defined (WINDOWS) && (! defined ( VK_CONVERT ) )
#define VK_CONVERT 0x1C
#endif
#if defined (WINDOWS) && (! defined ( VK_NONCONVERT ) )
#define VK_NONCONVERT 0x1D
#endif
#if defined (WINDOWS) && (! defined ( VK_ACCEPT ) )
#define VK_ACCEPT 0x1E
#endif
#if defined (WINDOWS) && (! defined ( VK_MODECHANGE ) )
#define VK_MODECHANGE 0x1F
#endif
#if defined (WINDOWS) && (! defined ( VK_SLEEP ) )
#define VK_SLEEP 0x5F
#endif
#if defined (WINDOWS) && (! defined ( VK_BROWSER_BACK ) )
#define VK_BROWSER_BACK 0xA6
#endif
#if defined (WINDOWS) && (! defined ( VK_BROWSER_FORWARD ) )
#define VK_BROWSER_FORWARD 0xA7
#endif
#if defined (WINDOWS) && (! defined ( VK_BROWSER_REFRESH ) )
#define VK_BROWSER_REFRESH 0xA8
#endif
#if defined (WINDOWS) && (! defined ( VK_BROWSER_STOP ) )
#define VK_BROWSER_STOP 0xA9
#endif
#if defined (WINDOWS) && (! defined ( VK_BROWSER_SEARCH ) )
#define VK_BROWSER_SEARCH 0xAA
#endif
#if defined (WINDOWS) && (! defined ( VK_BROWSER_FAVORITES ) )
#define VK_BROWSER_FAVORITES 0xAB
#endif
#if defined (WINDOWS) && (! defined ( VK_BROWSER_HOME ) )
#define VK_BROWSER_HOME 0xAC
#endif
#if defined (WINDOWS) && (! defined ( VK_VOLUME_MUTE ) )
#define VK_VOLUME_MUTE 0xAD
#endif
#if defined (WINDOWS) && (! defined ( VK_VOLUME_DOWN ) )
#define VK_VOLUME_DOWN 0xAE
#endif
#if defined (WINDOWS) && (! defined ( VK_VOLUME_UP ) )
#define VK_VOLUME_UP 0xAF
#endif
#if defined (WINDOWS) && (! defined ( VK_MEDIA_NEXT_TRACK ) )
#define VK_MEDIA_NEXT_TRACK 0xB0
#endif
#if defined (WINDOWS) && (! defined ( VK_MEDIA_PREV_TRACK ) )
#define VK_MEDIA_PREV_TRACK 0xB1
#endif
#if defined (WINDOWS) && (! defined ( VK_MEDIA_STOP ) )
#define VK_MEDIA_STOP 0xB2
#endif
#if defined (WINDOWS) && (! defined ( VK_MEDIA_PLAY_PAUSE ) )
#define VK_MEDIA_PLAY_PAUSE 0xB3
#endif
#if defined (WINDOWS) && (! defined ( VK_LAUNCH_MAIL ) )
#define VK_LAUNCH_MAIL 0xB4
#endif
#if defined (WINDOWS) && (! defined ( VK_LAUNCH_MEDIA_SELECT ) )
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#endif
#if defined (WINDOWS) && (! defined ( VK_LAUNCH_APP1 ) )
#define VK_LAUNCH_APP1 0xB6
#endif
#if defined (WINDOWS) && (! defined ( VK_LAUNCH_APP2 ) )
#define VK_LAUNCH_APP2 0xB7
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_1 ) )
#define VK_OEM_1 0xBA
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_PLUS ) )
#define VK_OEM_PLUS 0xBB
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_COMMA ) )
#define VK_OEM_COMMA 0xBC
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_MINUS ) )
#define VK_OEM_MINUS 0xBD
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_PERIOD ) )
#define VK_OEM_PERIOD 0xBE
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_2 ) )
#define VK_OEM_2 0xBF
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_3 ) )
#define VK_OEM_3 0xC0
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_4 ) )
#define VK_OEM_4 0xDB
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_5 ) )
#define VK_OEM_5 0xDC
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_6 ) )
#define VK_OEM_6 0xDD
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_7 ) )
#define VK_OEM_7 0xDE
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_8 ) )
#define VK_OEM_8 0xDF
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_102 ) )
#define VK_OEM_102 0xE2
#endif
#if defined (WINDOWS) && (! defined ( VK_PROCESSKEY ) )
#define VK_PROCESSKEY 0xE5
#endif
#if defined (WINDOWS) && (! defined ( VK_PACKET ) )
#define VK_PACKET 0xE7
#endif
#if defined (WINDOWS) && (! defined ( VK_ATTN ) )
#define VK_ATTN 0xF6
#endif
#if defined (WINDOWS) && (! defined ( VK_CRSEL ) )
#define VK_CRSEL 0xF7
#endif
#if defined (WINDOWS) && (! defined ( VK_EXSEL ) )
#define VK_EXSEL 0xF8
#endif
#if defined (WINDOWS) && (! defined ( VK_EREOF ) )
#define VK_EREOF 0xF9
#endif
#if defined (WINDOWS) && (! defined ( VK_PLAY ) )
#define VK_PLAY 0xFA
#endif
#if defined (WINDOWS) && (! defined ( VK_ZOOM ) )
#define VK_ZOOM 0xFB
#endif
#if defined (WINDOWS) && (! defined ( VK_NONAME ) )
#define VK_NONAME 0xFC
#endif
#if defined (WINDOWS) && (! defined ( VK_PA1 ) )
#define VK_PA1 0xFD
#endif
#if defined (WINDOWS) && (! defined ( VK_OEM_CLEAR ) )
#define VK_OEM_CLEAR 0xFE
#endif


/*
Key Formats:
Key Name        Key Value       Description (if needed)
---------------------------------------------------------
OK_ESC          256+0           Escape (2 consecutive is returned as 1)
OK_F0           256+1           Function Keys...
OK_F1           256+2
OK_F2           256+3
OK_F3           256+4
OK_F4           256+5
OK_F5           256+6
OK_F6           256+7
OK_F7           256+8
OK_F8           256+9
OK_F9           256+10
OK_F10          256+11
OK_F11          256+12
OK_F12          256+13
OK_F13          256+14
OK_F14          256+15
OK_F15          256+16
OK_F16          256+17
OK_F17          256+18
OK_F18          256+19
OK_F19          256+20
OK_F20          256+21
OK_PS           256+22          Print Screen
OK_SLOCK        256+23          Scroll Lock
OK_PAUSE        256+24          Pause/Break
OK_BS           256+25          Backspace
OK_INS          256+26          Insert
OK_HOME         256+27          Home
OK_PGUP         256+28          Page Up
OK_NLOCK        256+29          Num Lock
OK_NDIV         256+30          Numpad /
OK_NMUL         256+31          Numpad *
OK_NSUB         256+32          Numpad -
OK_HT           256+33          Tab
OK_RHT          256+34          Reverse Tab (?)
OK_DEL          256+35          Delete
OK_END          256+36          End
OK_PGDOWN       256+37          Page Down
OK_NADD         256+38          Numpad +
OK_CLOCK        256+39          Caps Lock
OK_NENTER       256+40          Numpad Enter
OK_NDEL         256+41          Numpad .
OK_N0           256+42          Numpad 0
OK_N1           256+43          Numpad 1
OK_N2           256+44          Numpad 2
OK_N3           256+45          Numpad 3
OK_N4           256+46          Numpad 4
OK_N5           256+47          Numpad 5
OK_N6           256+48          Numpad 6
OK_N7           256+49          Numpad 7
OK_N8           256+50          Numpad 8
OK_N9           256+51          Numpad 9
OK_UP           256+52          Up
OK_LEFT         256+53          Left
OK_DOWN         256+54          Down
OK_RIGHT        256+55          Right
OK_NSP          256+56          Numpad Space
OK_NHT          256+57          Numpad Tab
OK_PF1          256+58          P Function Keys...
OK_PF2          256+59
OK_PF3          256+60
OK_PF4          256+61
OK_NCOMMA       256+62          Numpad ,
OK_NEQ          256+63          Numpad =
OK_BLUE         256+64          Colour Keys...
OK_RED          256+65
OK_GREY         256+66
OK_GRAY         256+66
OK_WHITE        256+67
OK_QF1          256+68          QDOS Function Keys...
OK_QF2          256+69
OK_QF3          256+70
OK_QF4          256+71
OK_QF5          256+72
OK_CLEAR        256+73
OK_FIND         256+74
OK_SELECT       256+75
OK_HELP         256+76
OK_EHV          256+77          ?
OK_EHF          256+78
OK_EHB          256+79
OK_EHR          256+80
OK_EHU          256+81
OK_ECV          256+82
OK_ECF          256+83
OK_ECB          256+84          ? (Don't remember what this was)
OK_ECR          256+85
OK_ECP          256+86
OK_ECG          256+87
OK_ECT          256+88
OK_ECY          256+89
OK_ECN          256+90
OK_ENL          256+91          Escaped New Line

OK_F21          256+92          Extended Function Keys...
OK_F22          256+93
OK_F23          256+94
OK_F24          256+95
OK_F25          256+96
OK_F26          256+97
OK_F27          256+98
OK_F28          256+99
OK_F29          256+100
OK_F30          256+101
OK_F31          256+102
OK_F32          256+103
OK_F33          256+104
OK_F34          256+105
OK_F35          256+106
OK_F36          256+107
OK_F37          256+108
OK_F38          256+109
OK_F39          256+110
OK_F40          256+111
OK_F41          256+112
OK_F42          256+113
OK_F43          256+114
OK_F44          256+115
OK_F45          256+116
OK_F46          256+117
OK_F47          256+118
OK_F48          256+119

OK_IND          256+128         Escape Sequence Definitions...
OK_NEL          256+129
OK_HTS          256+130
OK_RI           256+131
OK_SS2          256+132
OK_OSC          256+133
OK_APC          256+134
OK_DCS          256+135
OK_SPA          256+136
OK_EPA          256+137
OK_SOS          256+138
OK_DECID        256+139
OK_ST           256+140
OK_PM           256+141

OK_NOMODMAX     511             (Maximum unmodified key number)
OK_SHIFT        512             Shift Modifier
OK_CTRL         1024            Ctrl Modifier
OK_ALT          2048            Alt Modifier
OK_META         4096            Meta Modifier

OK_UNK_1        -1              Unknown Key
OK_UNK_2        -2              Unknown 2 Key Sequence
OK_UNK_3        -3              Unknown 3 Key Sequence
OK_UNK_4        -4              Unknown 4 Key Sequence
OK_UNK_5        -5              Unknown 5 Key Sequence
OK_UNK_6        -6              Unknown 6 Key Sequence
OK_UNK_7        -7              Unknown 7 Key Sequence
OK_UNK_8        -8              Unknown 8 Key Sequence
*/

#ifdef WINDOWS
WORD vk_array[] = { VK_LBUTTON, VK_RBUTTON, VK_CANCEL, VK_MBUTTON, VK_XBUTTON1, 
                    VK_XBUTTON2, VK_BACK, VK_TAB, VK_CLEAR, VK_RETURN, VK_SHIFT,
                    VK_CONTROL, VK_MENU, VK_PAUSE, VK_CAPITAL, VK_KANA, 
                    VK_HANGUL, VK_JUNJA, VK_FINAL, VK_HANJA, VK_KANJI, 
                    VK_ESCAPE, VK_CONVERT, VK_NONCONVERT, VK_ACCEPT, 
                    VK_MODECHANGE, VK_SPACE, VK_PRIOR, VK_NEXT, VK_END, VK_HOME,
                    VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN, VK_SELECT, VK_PRINT, 
                    VK_EXECUTE, VK_SNAPSHOT, VK_INSERT, VK_DELETE, VK_HELP, '0',
                    '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
                    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                    VK_LWIN, VK_RWIN, VK_APPS, VK_SLEEP, VK_NUMPAD0, VK_NUMPAD1,
                    VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6,
                    VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9, VK_MULTIPLY, VK_ADD, 
                    VK_SEPARATOR, VK_SUBTRACT, VK_DECIMAL, VK_DIVIDE, VK_F1, 
                    VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, 
                    VK_F10, VK_F11, VK_F12, VK_F13, VK_F14, VK_F15, VK_F16, 
                    VK_F17, VK_F18, VK_F19, VK_F20, VK_F21, VK_F22, VK_F23, 
                    VK_F24, VK_NUMLOCK, VK_SCROLL, VK_LSHIFT, VK_RSHIFT, 
                    VK_LCONTROL, VK_RCONTROL, VK_LMENU, VK_RMENU, 
                    VK_BROWSER_BACK, VK_BROWSER_FORWARD, VK_BROWSER_REFRESH, 
                    VK_BROWSER_STOP, VK_BROWSER_SEARCH, VK_BROWSER_FAVORITES, 
                    VK_BROWSER_HOME, VK_VOLUME_MUTE, VK_VOLUME_DOWN, 
                    VK_VOLUME_UP, VK_MEDIA_NEXT_TRACK, VK_MEDIA_PREV_TRACK, 
                    VK_MEDIA_STOP, VK_MEDIA_PLAY_PAUSE, VK_LAUNCH_MAIL, 
                    VK_LAUNCH_MEDIA_SELECT, VK_LAUNCH_APP1, VK_LAUNCH_APP2, 
                    VK_OEM_1, VK_OEM_PLUS, VK_OEM_COMMA, VK_OEM_MINUS, 
                    VK_OEM_PERIOD, VK_OEM_2, VK_OEM_3, VK_OEM_4, VK_OEM_5, 
                    VK_OEM_6, VK_OEM_7, VK_OEM_8, VK_OEM_102, VK_PROCESSKEY, 
                    VK_PACKET, VK_ATTN, VK_CRSEL, VK_EXSEL, VK_EREOF, VK_PLAY, 
                    VK_ZOOM, VK_NONAME, VK_PA1, VK_OEM_CLEAR, 0 };
int ok_array[] = { OK_MLB, OK_MRB, OK_CANCEL, OK_MMB, OK_MX1B, OK_MX2B, OK_BS, 
                   OK_HT, OK_CLEAR, OK_CRETURN, OK_SHIFT, OK_CTRL, OK_AMENU, 
                   OK_PAUSE, OK_CLOCK, OK_KANA, OK_HANGUL, OK_JUNJA, OK_FINAL,
                   OK_HANJA, OK_KANJI, OK_ESC, OK_CONVERT, OK_NONCONVERT, 
                   OK_ACCEPT, OK_MODECHANGERQ, OK_SPACE, OK_PGUP, OK_PGDOWN, 
                   OK_END, OK_HOME, OK_LEFT, OK_UP, OK_RIGHT, OK_DOWN, OK_SELECT,
                   OK_PRINT, OK_EXECUTE, OK_PS, OK_INS, OK_DEL, OK_HELP, OK_0, 
                   OK_1, OK_2, OK_3, OK_4, OK_5, OK_6, OK_7, OK_8, OK_9, 'A', 
                   'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
                   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
                   'Z', OK_LWIN, OK_RWIN, OK_APPS, OK_SLEEP, OK_N0, OK_N1, OK_N2,
                   OK_N3, OK_N4, OK_N5, OK_N6, OK_N7, OK_N8, OK_N9, OK_NMUL, 
                   OK_NADD, OK_SEPARATOR, OK_NSUB, OK_NDEL, OK_NDIV, OK_F1, 
                   OK_F2, OK_F3, OK_F4, OK_F5, OK_F6, OK_F7, OK_F8, OK_F9, 
                   OK_F10, OK_F11, OK_F12, OK_F13, OK_F14, OK_F15, OK_F16, 
                   OK_F17, OK_F18, OK_F19, OK_F20, OK_F21, OK_F22, OK_F23, 
                   OK_F24, OK_NLOCK, OK_SLOCK, OK_LSHIFT, OK_RSHIFT, OK_CTRL, 
                   OK_RCTRL, OK_LMENU, OK_RMENU, OK_BROWSERBACK, OK_BROWSERFWD, 
                   OK_BROWSERREF, OK_BROWSERSTOP, OK_BROWSERSEARCH, OK_BROWSERFAV,
                   OK_BROWSERHOME, OK_VOLMUTE, OK_VOLDOWN, OK_VOLUP, OK_MEDIANEXT,
                   OK_MEDIAPREV, OK_MEDIASTOP, OK_MEDIAPLAY, OK_STARTMAIL, 
                   OK_STARTMEDIA, OK_STARTAPP1, OK_STARTAPP2, OK_OEM1, OK_OEMPLUS,
                   OK_OEMMINUS, OK_OEMCOMMA, OK_PERIOD, OK_OEM2, OK_OEM3, OK_OEM4,
                   OK_OEM5, OK_OEM6, OK_OEM7, OK_OEM8, OK_OEM102, OK_PROCESSKEY,
                   OK_PACKET, OK_ATTENTION, OK_CRSEL, OK_EXSEL, OK_ERASEEOF, 
                   OK_PLAY, OK_ZOOM, OK_NONAME, OK_PA1, OK_OEMCLEAR, 0 };

#endif


char qdinplibver[] = "0.02.11"
#ifdef COHERENT
"C"
#endif
#ifdef WIN32
"W"
#endif
#ifdef WIN64
"W64"
#endif
;
char termtype[256] = "";
int modsasfuncs = 0; /* Interpret function key modifiers as additional function keys? */
int exitreadqdline = 0; /* Exit the readqdline function? */
int qdgetchmode = 0; /* Mode 0 = Block, Mode 1 = Poll, Mode 2 = Get Immediate, Mode 3 = Block but ignore Breaks and Core dumps, Mode 4 = Mode 2 without xon/xoff enabled and with legacy terminal features disabled.  */
#ifdef WINDOWS
int cx, cy, cxmax, cymax;
BOOL breakhandlerset = FALSE;
#endif
char tabstack[TABSTACKSIZE];
int tabstackptr=0;


char *qdinpver()
{
  /* Returns the Library version number */
  return qdinplibver;
}

void setmodsasfuncs()
{
  modsasfuncs = 1;
}


void resetmodsasfuncs()
{
  modsasfuncs = 0;
}


int getterm()
{
  char *aterm;
  aterm = getenv("TERM");
  if (aterm == NULL) aterm = getenv("term");
  if (aterm != NULL)
  {
    strcpy(termtype,aterm);
  }
  else
  {
    termtype[0] = 0;
    return 1;
  }
  return 0;
}


#ifdef WINDOWS
void SetCursorState(int CSize, BOOL Visible)
{
  CONSOLE_CURSOR_INFO cci;
  cci.dwSize = CSize;
  cci.bVisible = Visible;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);  //Or should it be STD_INPUT_HANDLE?
}

void SetCursorPos_(int x, int y)
{
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void SetTextColour(int fg, int bg, int inverse)
{
  int colour = 0;
  if ((fg & CURCOL_BLUE)!=0) colour |= FOREGROUND_BLUE;
  if ((fg & CURCOL_GREEN)!=0) colour |= FOREGROUND_GREEN;
  if ((fg & CURCOL_RED)!=0) colour |= FOREGROUND_RED;
  if ((fg & CURCOL_BRIGHT)!=0) colour |= FOREGROUND_INTENSITY;
  if ((bg & CURCOL_BLUE)!=0) colour |= BACKGROUND_BLUE;
  if ((bg & CURCOL_GREEN)!=0) colour |= BACKGROUND_GREEN;
  if ((bg & CURCOL_RED)!=0) colour |= BACKGROUND_RED;
  if ((bg & CURCOL_BRIGHT)!=0) colour |= BACKGROUND_INTENSITY;
#ifdef COMMON_LVB_REVERSE_VIDEO
  if (inverse) colour |= COMMON_LVB_REVERSE_VIDEO;
#endif
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour);
}

int GetFgTextColour()
{
  WORD Attribs = GetCursorAttribs();
  int colour = 0;
  if ((Attribs & FOREGROUND_BLUE)!=0) colour |= CURCOL_BLUE;
  if ((Attribs & FOREGROUND_GREEN)!=0) colour |= CURCOL_GREEN;
  if ((Attribs & FOREGROUND_RED)!=0) colour |= CURCOL_RED;
  if ((Attribs & FOREGROUND_INTENSITY)!=0) colour |= CURCOL_BRIGHT;
  return colour;
}

int GetBgTextColour()
{
  WORD Attribs = GetCursorAttribs();
  int colour = 0;
  if ((Attribs & BACKGROUND_BLUE)!=0) colour |= CURCOL_BLUE;
  if ((Attribs & BACKGROUND_GREEN)!=0) colour |= CURCOL_GREEN;
  if ((Attribs & BACKGROUND_RED)!=0) colour |= CURCOL_RED;
  if ((Attribs & BACKGROUND_INTENSITY)!=0) colour |= CURCOL_BRIGHT;
  return colour;
}

int GetWinSize(int *width, int *height)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  BOOL ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
  if (ret)
  {
    (*width) = csbi.dwSize.X;
    (*height) = csbi.dwSize.Y;
    return 1;
  }
  else return 0;
}

int GetCursorPos_(int *x, int *y)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  BOOL ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
  if (ret)
  {
    (*x) = csbi.dwCursorPosition.X;
    (*y) = csbi.dwCursorPosition.Y;
    return 1;
  }
  else return 0;
}

WORD GetCursorAttribs()
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  BOOL ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
  if (ret)
  {
    return csbi.wAttributes;
  }
  else return 0;
}

void setcvars()
{
  GetCursorPos_(&cx, &cy);
  GetWinSize(&cxmax, &cymax);
  /*cxmax--;
    cymax--;*/
}

int keytranslate(WORD vkey, DWORD modkey, TCHAR keychar)
{
  int keyn = 0;
  if ((modkey & CAPSLOCK_ON) != 0) keyn |= OK_CLOCKON;
  if ((modkey & ENHANCED_KEY) != 0) keyn |= OK_META;
  if ((modkey & LEFT_ALT_PRESSED) != 0) keyn |= OK_ALT;
  if ((modkey & LEFT_CTRL_PRESSED) != 0) keyn |= OK_CTRL;
  if ((modkey & NUMLOCK_ON) != 0) keyn |= OK_NLOCKON;
  if ((modkey & RIGHT_ALT_PRESSED) != 0) keyn = ((keyn & ~(OK_CTRL)) | (OK_ALTGR)); /* AltGr engages LCtrl automatically */
  if ((modkey & RIGHT_CTRL_PRESSED) != 0) keyn |= OK_RCTRL;
  if ((modkey & SCROLLLOCK_ON) != 0) keyn |= OK_SLOCKON;
  if ((modkey & SHIFT_PRESSED) != 0) keyn |= OK_SHIFT;
  
  
  int i;
  for (i=0;vk_array[i]!=0;i++)
  {
    if (vk_array[i] == vkey) break;
  }
  if (vk_array[i] == 0)
  {
      keyn = OK_UNK_1;
      /*  printf("0x%X\n\n", vkey);  For Debugging*/
  }
  else
  {
    keyn |= ok_array[i];
  }
  
  if ((keyn & OK_NOMODMAX) < 256 || (keyn & OK_NOMODMAX) == OK_OEM8)
  {
    if (( ((keyn & OK_LETTERMODIFIERS) == 0)
         || (((keyn & OK_SHIFT) != 0 && (keyn & OK_CLOCKON) != 0
              && (keyn & OK_LETTERCMDMODIFIERS) == 0 )
         ))  /* If it is only modified by things that don't affect letters,
                or it is but the shift and capslock cancel each other out, ... */
        && (keyn & OK_NOMODMAX) >= 'A' 
        && (keyn & OK_NOMODMAX) <= 'Z' /* ... And it's A to Z then... */
        ) keyn += 32; /* Make it lowercase */
    if ( (keyn & OK_LETTERCMDNOCTRLMODIFIERS) == 0
        && (keyn & OK_CTRLS) != 0
        && (keyn & OK_NOMODMAX) >= 'A' 
        && (keyn & OK_NOMODMAX) <= 'Z' ) keyn -= 64;
    if ((keyn & OK_SYMBOLCMDMODIFIERS) == 0
        && (keyn & OK_NOMODMAX) >= '0' 
        && (keyn & OK_NOMODMAX) <= '9') keyn = (((int) keychar) & 255);
    if ((keyn & OK_ALTGR) != 0 && (keyn & OK_LETTERCMDMODIFIERS) == 0
        && (keyn & OK_NOMODMAX) >= '0'  && (keyn & OK_NOMODMAX) <= '9') keyn = (((int) keychar) & 255);
    if ((keyn & OK_ALTGR) != 0 && (keyn & OK_LETTERCMDMODIFIERS) == 0
        && (keyn & OK_NOMODMAX) >= 'A'  && (keyn & OK_NOMODMAX) <= 'Z') keyn = (((int) keychar) & 255);
    if ((keyn & OK_ALTGR) != 0 && (keyn & OK_LETTERCMDMODIFIERS) == 0
        && (keyn & OK_NOMODMAX) >= 'a'  && (keyn & OK_NOMODMAX) <= 'z') keyn = (((int) keychar) & 255);
    if ((keyn & OK_SYMBOLCMDMODIFIERS) == 0)
    {
      switch(keyn & OK_NOMODMAX)
      {
        case OK_OEM8:  /* Why is this not getting a keychar for shifted values?! Answer = (TCHAR) is signed! & it with 255 to fix!
          printf("kn=0x%X, kc=%d, knm=0x%X\n\n", keyn, keychar, (keyn & OK_ALLMODS)); */
        case OK_OEM1:
        case OK_OEM2:
        case OK_OEM3:
        case OK_OEM4:
        case OK_OEM5:
        case OK_OEM6:
        case OK_OEM7:
#if OK_OEM102 != OK_OEM5
        case OK_OEM102:
#endif
        case OK_OEMPLUS:
        case OK_OEMCOMMA:
        case OK_OEMMINUS:
        case OK_OEMPERIOD:
          keyn = (keyn & OK_ALLMODS) | (((int) keychar) & 255);
        break;
      }
    }
  }
  switch(keyn & OK_NOMODMAX)
  {
    case OK_NDIV:
    case OK_NMUL:
    case OK_NSUB:
    case OK_NADD:
    case OK_NENTER:
    case OK_NDEL:
    case OK_N0:
    case OK_N1:
    case OK_N2:
    case OK_N3:
    case OK_N4:
    case OK_N5:
    case OK_N6:
    case OK_N7:
    case OK_N8:
    case OK_N9:
    case OK_NSP:
    case OK_NHT:
    case OK_NCOMMA:
      if ((keyn & OK_NUMPADCMDMODIFIERS) == 0)
      {
        if (((keyn & OK_NUMPADSHIFTS) == 0) || ((keyn & OK_SHIFT) != 0
             && (keyn & OK_NLOCKON) != 0))
        {
          switch (keyn & OK_NOMODMAX)
          {
            case OK_N0:
              keyn = (keyn & OK_ALLMODS) | (OK_INS);
            break;
            
            case OK_N1:
              keyn = (keyn & OK_ALLMODS) | (OK_END);
            break;
            
            case OK_N2:
              keyn = (keyn & OK_ALLMODS) | (OK_DOWN);
            break;
            
            case OK_N3:
              keyn = (keyn & OK_ALLMODS) | (OK_PGDOWN);
            break;
            
            case OK_N4:
              keyn = (keyn & OK_ALLMODS) | (OK_LEFT);
            break;
            
            case OK_N6:
              keyn = (keyn & OK_ALLMODS) | (OK_RIGHT);
            break;
            
            case OK_N7:
              keyn = (keyn & OK_ALLMODS) | (OK_HOME);
            break;
            
            case OK_N8:
              keyn = (keyn & OK_ALLMODS) | (OK_UP);
            break;
            
            case OK_N9:
              keyn = (keyn & OK_ALLMODS) | (OK_PGUP);
            break;
            
            case OK_NDEL:
              keyn = (keyn & OK_ALLMODS) | (OK_DEL);
            break;
          }
        }
        else
        {
          keyn = (keyn & OK_ALLMODS) | (((int) keychar) & 255);
        }
      }
    break;
  }

  /* if (keyn<0)  printf("0x%X, 0x%X, %c\n\n", vkey, modkey, keychar); For Debugging */
  return keyn;
}

BOOL GetKeynWin(int *keyn, int *repeat)
{
  HANDLE inh = GetStdHandle(STD_INPUT_HANDLE);
  DWORD numevents;
  GetNumberOfConsoleInputEvents(inh , &numevents);
  INPUT_RECORD anir;
  DWORD numread;
  WORD keycode = 0;
  DWORD modkeys = 0;
  BOOL hasreadkey = FALSE;
  while (numevents > 0)
  {
    ReadConsoleInput(inh, &anir, 1, &numread);
    if (anir.EventType == KEY_EVENT)
    {
      if (anir.Event.KeyEvent.bKeyDown)
      {
        *keyn = keytranslate(anir.Event.KeyEvent.wVirtualKeyCode,
                             anir.Event.KeyEvent.dwControlKeyState,
#ifdef UNICODE
                             (TCHAR) anir.Event.KeyEvent.uChar.UnicodeChar);
#else
                             (TCHAR) anir.Event.KeyEvent.uChar.AsciiChar);
#endif
                             /* Expands the key number from stuff like (OK_SHIFT|OK_1) to '!' */
        *repeat = (int) anir.Event.KeyEvent.wRepeatCount;
        hasreadkey = TRUE;
        break;
      }
    }
    GetNumberOfConsoleInputEvents(inh , &numevents);
  }
  return hasreadkey;
}
#endif


void cls()
{
#ifdef WINDOWS
  HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coordScreen = { 0, 0 };    // home for the cursor 
  int swidth, sheight;
  if (!GetWinSize(&swidth, &sheight)) return;
  DWORD cCharsWritten;
  DWORD ConSize = swidth * sheight;
  if( !FillConsoleOutputCharacter( outh, (TCHAR) ' ', ConSize , coordScreen, &cCharsWritten )) return;
  if( !FillConsoleOutputAttribute( outh, GetCursorAttribs(), ConSize , coordScreen, &cCharsWritten )) return;
  SetConsoleCursorPosition( outh, coordScreen );
  return;
#else
  write(STDOUT_FD,"\033[2J\033[H",7);
  return;
#endif
}




int qdgetch()
{
#ifndef WINDOWS
  int ch;
  
#ifdef COHERENT
  struct termio oldt, newt;
  ioctl(STDIN_FILENO, TCGETA, &oldt);  /*tcgetattr equivalent*/
#else
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
#endif
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
/*  newt.c_iflag &= ~(IGNBRK | BRKINT ); /* Return NULL on Ctrl+C */
#ifndef COHERENT
  newt.c_iflag &= ~(IGNBRK  ); /* According to manpage at http://www.nesssoftware.com/home/mwc/manpage.php?page=termio, this probably won't work with Coherent. */
#endif
  newt.c_iflag |=  (BRKINT ); /* Return SIGINT on Ctrl+C */
  switch (qdgetchmode)
  {
    case 0:
      newt.c_cc[VMIN] = oldt.c_cc[VMIN];
      newt.c_cc[VTIME] = oldt.c_cc[VTIME];
#ifdef COHERENT
      ioctl(STDIN_FILENO, TCSETA, &newt); /*tcsetattr TCSANOW equivalent*/
#else
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
      ch = getchar();
    break;
    
    case 1:
      /*  printf("-");*/
      newt.c_cc[VMIN] = 0;
      newt.c_cc[VTIME] = 1;
#ifdef COHERENT
      ioctl(STDIN_FILENO, TCSETA, &newt); /*tcsetattr TCSANOW equivalent*/
#else
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
      do
      {
        ch = getchar();
      } while (ch==0 && exitreadqdline==0);
      if (ch==0 && exitreadqdline != 0) ch = 3;
    break;
    
    case 2:
      newt.c_cc[VMIN] = 0;
      newt.c_cc[VTIME] = 2;
#ifdef COHERENT
      ioctl(STDIN_FILENO, TCSETA, &newt); /*tcsetattr TCSANOW equivalent*/
#else
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
      ch = getchar();
      if (ch==0 && exitreadqdline != 0) ch = 3;
    break;
    
    case 3:
      newt.c_cc[VMIN] = oldt.c_cc[VMIN];
      newt.c_cc[VTIME] = oldt.c_cc[VTIME];
      newt.c_lflag &= ~(ISIG);
      /*newt.c_iflag &= ~(IGNBRK | BRKINT ); /* Return NULL on Ctrl+C */
#ifdef COHERENT
      ioctl(STDIN_FILENO, TCSETA, &newt); /*tcsetattr TCSANOW equivalent*/
#else
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
      ch = getchar();
      if (ch==3) exitreadqdline = 1;
    break;
    
    case 4:
      newt.c_cc[VMIN] = 0;
      newt.c_cc[VTIME] = 2;
      newt.c_iflag &= ~(INPCK | ISTRIP | IXON); /* Turn off Parity Checks, XON/XOFF and stripping of 8th bit (probably already off) */
      newt.c_lflag &= ~(IEXTEN); /* Turn off literal quotes */
      newt.c_cflag |= (CS8); /* Use 8bit Chars */
#ifdef COHERENT
      ioctl(STDIN_FILENO, TCSETA, &newt); /*tcsetattr TCSANOW equivalent*/
#else
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
      ch = getchar();
      if (ch==0 && exitreadqdline != 0) ch = 3;
    break;
  }
#ifdef COHERENT
  ioclt(STDIN_FILENO, TCSETA, &oldt); /*tcsetattr TCSANOW equivalent*/
#else
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
  
/*  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  newt.c_iflag &= ~(IGNBRK | BRKINT ); /* Return NULL on Ctrl+C */
/*  newt.c_iflag &= ~(IGNBRK  );
  newt.c_iflag |=  (BRKINT ); /* Return SIGINT on Ctrl+C */
  /*switch (qdgetchmode)
  {
    case 0:
      newt.c_cc[VMIN] = oldt.c_cc[VMIN];
      newt.c_cc[VTIME] = oldt.c_cc[VTIME];
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      ch = getchar();
    break;
    
    case 1:
      newt.c_cc[VMIN] = 0;
      newt.c_cc[VTIME] = 1;
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      do
      {
        ch = getchar();
      } while (ch==0 && exitreadqdline==0);
    break;
  }
  /*tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();*/
  /*tcsetattr(STDIN_FILENO, TCSANOW, &oldt);*/
  
  if (qdgetchmode==3 && ch==26) raise(SIGTSTP);
  
  if (ch) return ch;
  return 3;
#else
  /* Mode 0 = Block, Mode 1 = Poll, Mode 2 = Get Immediate, Mode 3 = Block but ignore Breaks and Core dumps.  */
  int keyn=0, repeat;
  switch (qdgetchmode)
  {
      case 0:
      case 1:
        while (!GetKeynWin(&keyn, &repeat)) continue;
        return keyn;
      break;
      
      case 2:
        if (GetKeynWin(&keyn, &repeat)) return keyn;
        return 3;
      break;
      
      case 3:
        /* TODO: Write this one properly!  For the moment, do the same as 0 and 1 */
        while (!GetKeynWin(&keyn, &repeat)) continue;
        return keyn;
      break;
      
      default:
        return 3;
      break;
  }
#endif
}


#ifndef WINDOWS
void readqdlinehandle_sigint(int sig)
{
  exitreadqdline = 1;
  regsiginthandler();
}
#else
BOOL WINAPI CtrlCHandlerRoutine(DWORD dwCtrlType)
{
  switch (dwCtrlType)
  {
    case CTRL_C_EVENT:
      /* readingchars = FALSE; */
      exitreadqdline = 1;
    break;
    
    default:
      return FALSE;
    break;
  }
  return TRUE;
}
#endif


int regsiginthandler()
{
#ifndef WINDOWS
  if (signal(SIGINT,readqdlinehandle_sigint) == SIG_ERR) return -1;
  return 0;
#else
  if (SetConsoleCtrlHandler(CtrlCHandlerRoutine, TRUE)) return 0;
  return -1;
#endif
}


int deregsiginthandler()
{
#ifndef WINDOWS
  if (signal(SIGINT, SIG_DFL) == SIG_ERR) return -1;
  return 0;
#else
  if(SetConsoleCtrlHandler(NULL, FALSE)) return 0;
  return -1;
#endif
}

void gotoansixy(int x, int y)
{
#ifdef WINDOWS
  SetCursorPos_(x-1, y-1);
  setcvars();
#else
  /* CUP - ^[[<v>;<h>H */
  char astr[256];
  int n;
  sprintf(astr,"\033[%d;%dH",y,x);
  n = strlen(astr);
  write(STDOUT_FILENO, astr, n);
#endif
}

int getansicursorpos(int *rows, int *cols)
{
#ifndef WINDOWS
  if (!rows || !cols) return 0;
  char buffer[256] = "";
  int i=0, qdgm = qdgetchmode;
  if (write(STDOUT_FILENO, "\033[6n", 4) != 4) return 0;
  fsync(STDOUT_FILENO);
  fsync(STDIN_FILENO);
  qdgetchmode = 2;
  for (i=0; i<255; i++)
  {
    buffer[i] = qdgetch();
    if (buffer[i] < 10) break;
    if (buffer[i] == 'R') break;
  }
  buffer[i] = 0;
  qdgetchmode = qdgm;
  
  if (buffer[0] != '\033' || buffer[1] != '[') return 0;
  if (sscanf(buffer+(2*sizeof(char)), "%d;%d", rows, cols) != 2) return 0;
  return 1;
#else
  setcvars();
  *rows = cy + 1;
  *cols = cx + 1;
  return 1;
#endif
}


void pushtotabstack(char tabsnum)
{
    if (tabstackptr<TABSTACKSIZE)
    {
        tabstack[tabstackptr]=tabsnum;
        tabstackptr++;
    }
}


char popfromtabstack()
{
    if (tabstackptr>0)
    {
        tabstackptr--;
        return tabstack[tabstackptr];
    }
    return 0;
}

void cleartabstack()
{
    tabstackptr=0;
}

int writetab()
{
#ifdef WINDOWS
    setcvars();
    int ocx,ocy,dcx,dcy;
    ocx=cx;
    ocy=cy;
    printf("%c",9);
    setcvars();
    dcx=cx-ocx;
    dcy=cy-ocy;
    if (dcx<=0 && dcy==0) dcy++;
    while (dcy>0)
    {
        dcx+=cxmax;
        dcy--;
    }
    pushtotabstack((char) (dcx & 0xff));
#else
    printf("%c",9);
#endif
}


int termbsn(int n)
{
  if (n<1) return 0;
  
#ifndef WINDOWS
  /* Backspaces on screen a given number of times
     Returns the amount backspaced. */
  int i;
  int cpw = 0, cpx = 0, cpy;
  
  if ((strcmp(termtype,"vt52")!=0) && (strcmp(termtype,"VT52")!=0) && (strcmp(termtype,"Tektronix 4014")!=0) && (strcmp(termtype,"T4014")!=0))
  {
    if (getansicursorpos(&cpy,&cpx) == 1) cpw = 1; /* Get Cursor Position, or fail */
  }
  for (i = 0; i < n; i++)
  {
    if ((strcmp(termtype,"vt52")==0) || (strcmp(termtype,"VT52")==0))
    {
      printf("\033D \033D");
    }
    else if ((strcmp(termtype,"Tektronix 4014")==0) || (strcmp(termtype,"T4014")==0))
    {
      printf("\x08 \x08");
    }
    else
    {
      if (cpw && cpx <= 1)
      {
        /* Multiline backspace */
        printf("\033[%d;9999H \033[%d,9999H",cpy-1, cpy-1);
        if (!getansicursorpos(&cpy,&cpx)) cpw = 0; /* Get Cursor Position, or fail */
      }
      else
      {
        printf("\033[1D \033[1D");
        if (cpw) cpx--;
      }
    }
  }
  return i;
#else
  int i, ncx, ncy, m = 0;
  char *clrstr = (char *) malloc(sizeof(char) * (1 + n));
  if (clrstr)
  {
    clrstr[0] = 0;
    for (i=0;i<n;i++) clrstr[i] = ' ';
    clrstr[n] = 0;
    
    ncx = cx;
    ncy = cy;
    ncx -= n;
    while (ncx < 0)
    {
      ncy--;
      ncx += cxmax;
    }
    if (ncy < 0)
    {
      i = (n-((0-ncy)*cxmax));
      clrstr[i+1] = 0;
      ncy = 0;
    }
    
    gotoxy(ncx, ncy);
    printf("%s",clrstr);
    gotoxy(ncx,ncy);
    
    m = strlen(clrstr);
    
    free(clrstr);
  }
  else
  {
    for (i=0;i<n;i++)
    {
      if (cx > 0)
      {
        gotoxy(cx-1,cy);
        printf(" ");
        gotoxy(cx-1,cy);
        m++;
      }
      else if (cy > 0)
      {
        gotoxy(cxmax,cy-1);
        printf(" ");
        gotoxy(cxmax,cy-1);
        m++;
      }
      else break;
    }
  }
  return m;
#endif
}

void writechar(char c)
{
  printf("%c", c);
#ifdef WINDOWS
  setcvars();
#endif
}

void writestr(char *str)
{
  printf("%s", str);
#ifdef WINDOWS
  setcvars();
#endif
}

int qdinstrch(char *targstring, char findchar, int startoffset)
{
  int i=0;
  int ans=-1;
  i+=startoffset;
  while (targstring[i] != 0)
  {
    if (targstring[i] == findchar)
    {
      ans = i-startoffset;
      break;
    }
    i++;
  }
  return ans;
}


int firstletter(char *cmdstring)
{
  int i=0;
  while (cmdstring[i] != 0)
  {
    if (isalpha(cmdstring[i])) return cmdstring[i];
    i++;
  }
  return 0;
}


int getkeyn()
{
#ifndef WINDOWS
  /*
    Gets the key number for a specified key or escape sequence.
    (Apologies for the GOTO-based spaghetti code)
  */
  int ch;
  int ech;
  int eech;
  int e3ch;
  int e4ch;
  int e5ch;
  int e6ch;
  int e7ch;
   
  while ((ch=qdgetch()) == EOF)
  {
    /* Do Nuttin' */
    
    /* Except... */
    if (exitreadqdline != 0)
    {
      ch=3;
      break;
    }
  }
  if (ch != EOF )
   {
      if (ch==27)
      {
        ech=qdgetch();
        switch (ech)
        {
          case 13:
          case 10:
            return OK_ENL;
          break;
          
          case 27:
            return OK_ESC;
          break;
          
          case '0':
            return OK_N0;
          break;

          case '1':
            return OK_N1;
          break;

          case '2':
            return OK_N2;
          break;

          case '3':
            return OK_N3;
          break;

          case '4':
            return OK_N4;
          break;

          case '5':
            return OK_N5;
          break;

          case '6':
            return OK_N6;
          break;

          case '7':
            if ((strcmp(termtype, "ansipc")==0) || 
                (strcmp(termtype, "ANSIPC")==0))
              return OK_N5;
            return OK_N7;
          break;

          case '8':
            return OK_N8;
          break;

          case '9':
            return OK_N9;
          break;

          case 'A':
            /* VT52 Up */
            return OK_UP;
          break;
          
          case 'B':
            /* VT52 Down */
            if ((strcmp(termtype,"vt52")==0) || (strcmp(termtype,"VT52")==0)) return OK_DOWN;
            return OK_ECB;
          break;
          
          case 'C':
            /* VT52 Right */
            return OK_RIGHT;
          break;
          
          case 'D':
            /* IND */
            /* VT52 Left */
            if ((strcmp(termtype,"vt52")==0) || (strcmp(termtype,"VT52")==0)) return OK_LEFT;
XTIND:
            return OK_IND;
          break;
          
          case 'E':
            /* NEL */
XTNEL:
            return OK_NEL;
          break;
          
          case 'F':
            /* ECF */
            return OK_ECF;
          break;
          
          case 'G':
            /* ECG */
            return OK_ECG;
          break;
          
          case 'H':
            /* HTS */
XTHTS:
            return OK_HTS;
          break;
          
          case 'M':
            /* RI */
XTRI:
            return OK_RI;
          break;
          
          case 'N':
            /* ECN */
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0)) 
              return OK_ECN;
XTSS2:
            /* SS2 */
            return OK_SS2;
          break;
          
          case 79:
XTSS3:
            /* ESC O - SS3 */
            eech = qdgetch();
            switch (eech)
            {
              case 32:
                return OK_NSP;
              break;

              case '2':
                e3ch = qdgetch();
                switch (e3ch)
                {
                  case 'P':
                    return OK_F13;
                  break;
                  
                  case 'Q':
                    return OK_F14;
                  break;
                  
                  case 'R':
                    return OK_F15;
                  break;
                  
                  case 'S':
                    return OK_F16;
                  break;
                  
                  default:
                    return OK_UNK_4;
                  break;
                }
              break;

              case '5':
                e3ch = qdgetch();
                switch (e3ch)
                {
                  case 'P':
                    return OK_F25;
                  break;
                  
                  case 'Q':
                    return OK_F26;
                  break;
                  
                  case 'R':
                    return OK_F27;
                  break;
                  
                  case 'S':
                    return OK_F28;
                  break;
                  
                  default:
                    return OK_UNK_4;
                  break;
                }
              break;

              case '6':
                e3ch = qdgetch();
                switch (e3ch)
                {
                  case 'P':
                    return OK_F37;
                  break;
                  
                  case 'Q':
                    return OK_F38;
                  break;
                  
                  case 'R':
                    return OK_F39;
                  break;
                  
                  case 'S':
                    return OK_F40;
                  break;
                  
                  default:
                    return OK_UNK_4;
                  break;
                }
              break;

              case 'A':
                return OK_UP;
              break;

              case 'B':
                return OK_DOWN;
              break;

              case 'C':
                return OK_RIGHT;
              break;

              case 'D':
                return OK_LEFT;
              break;

              case 'F':
                return OK_END;
              break;

              case 'H':
                return OK_HOME;
              break;

              case 'I':
                return OK_NHT;
              break;

              case 'M':
                return OK_NENTER;
              break;

              case 'P':
                return OK_F1;
              break;

              case 'Q':
                return OK_F2;
              break;

              case 'R':
                return OK_F3;
              break;

              case 'S':
                return OK_F4;
              break;

/* I really ought to get rid of this commented out code, but I don't have the heart... */
/*              case 80:
XTF1:
                /* F1 = ESC OP *
                if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); else
                printf("%c",itemplate[itpos]);
                if ((itemplate[itpos] != 0) && (tlpos < 255))
                {
                  theline[tlpos] = itemplate[itpos];
                  tlpos++;
                }
                if ((itpos < 255) && (insmode == 0) && (itemplate[itpos] != 0)) itpos++;
              break;
              
              case 81:
XTF2:
                /* F2 = ESC OQ *
                e5ch = qdgetch();
                e5ch = qdinstrch(itemplate,e5ch,itpos);
                if (e5ch>0)
                {
                  e4ch=e5ch+itpos;
                  while ((itpos < e4ch) && (itpos<255))
                  {
                    if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); else
                    printf("%c",itemplate[itpos]);
                    if ((itemplate[itpos] != 0) && (tlpos < 255))
                    {
                      theline[tlpos] = itemplate[itpos];
                      tlpos++;
                    }
                    itpos++;
                  }
                  if (insmode != 0) itpos = e4ch - e5ch;
                }
              break;
              
              case 82:
XTF3:
                /* F3 = ESC OR *
                if ((itpos<255) && (itemplate[itpos] != 0))
                {
                  e5ch=itpos;
                  while ((itpos < 255) && (itemplate[itpos] !=0) && (tlpos < 255))
                  {
                    theline[tlpos]=itemplate[itpos];
                    if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); else
                    printf("%c",itemplate[itpos]);
                    tlpos++;
                    itpos++;
                  }
                  if (insmode != 0) itpos = e5ch;
                }
              break;
              
              case 83:
XTF4:
                /* F4 = ESC OS *
                if (itpos < 255) itpos++;
              break;*/
              
              case 'X':
                return OK_NEQ;
              break;

              case 'j':
                return OK_NMUL;
              break;
              
              case 'k':
                return OK_NADD;
              break;
              
              case 'l':
                return OK_NCOMMA;
              break;
              
              case 'm':
                return OK_NSUB;
              break;
              
              case 110:
XTNDel:
                /* NumDEL = ESC On */
                return OK_NDEL;
              break;
              
              case 'o':
                return OK_NDIV;
              break;
              
              case 112:
XTNIns:
                /* NumINS = ESC Op */
                return OK_N0;
              break;
              
              case 'q':
                return OK_N1;
              break;
              
              case 'r':
                return OK_N2;
              break;
              
              case 's':
                return OK_N3;
              break;
              
              case 't':
                return OK_N4;
              break;
              
              case 'u':
                return OK_N5;
              break;
              
              case 'v':
                return OK_N6;
              break;
              
              case 'w':
                return OK_N7;
              break;
              
              case 'x':
                return OK_N8;
              break;
              
              case 'y':
                return OK_N9;
              break;
              
              default:
                /* ESC O */
                return OK_UNK_3;
              break;
            }
          break;
          
          
          case (64+16):
            if ((strcmp(termtype,"vt52")==0) || 
                (strcmp(termtype,"VT52")==0)) 
              return OK_PF1;
            /* ECP */
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0)) 
              return OK_ECP;
            /* DCS */
            if ((memcmp(termtype,"vt",2)==0) || 
                (memcmp(termtype,"VT",2)==0)) 
              return OK_DCS;
          case (96+16):
            /* ESC P - INS On*/
            return OK_BLUE;
          break;
          
          case (64+17):
            if ((strcmp(termtype,"vt52")==0) || 
                (strcmp(termtype,"VT52")==0)) 
              return OK_PF2;
          case (96+17):
            /* ESC Q - INS Off */
            return OK_RED;
          break;
          
          case (64+18):
            if ((strcmp(termtype,"vt52")==0) || 
                (strcmp(termtype,"VT52")==0)) 
              return OK_PF3;
            /* ECR */
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0)) 
              return OK_ECR;
          case (96+18):
            /* ESC R */
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0)) 
              return OK_EHR;
            return OK_GREY;
          break;
          
          case (64+19):
            if ((strcmp(termtype,"vt52")==0) || 
                (strcmp(termtype,"VT52")==0)) 
              return OK_PF4;
          case (96+19):
            /* ESC S */
            return OK_QF1;
          break;
          
          case (64+20):
            /* ECT */
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0)) 
              return OK_ECT;
          case (96+20):
            /* ESC T - write 'til char */
            return OK_QF2;
          break;
          
          case (96+21):
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0)) 
              return OK_EHU;
          case (64+21):
            /* ESC U */
            return OK_QF3;
          break;
          
          case (64+22):
            /* ECV */
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0)) 
              return OK_ECV;
            /* SPA */
            if ((memcmp(termtype,"vt",2)==0) || 
                (memcmp(termtype,"VT",2)==0)) 
              return OK_SPA;
          case (96+22):
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0)) 
              return OK_EHV;
            /* ESC V */
            return OK_QF4;
          break;
          
          case (64+23):
            /* EPA */
            if ((memcmp(termtype,"vt",2)==0) || 
                (memcmp(termtype,"VT",2)==0)) 
              return OK_EPA;
          case (96+23):
            /* ESC W */
            return OK_QF5;
          break;
          
          case 'X':
XTSOS:
            /* SOS */
            return OK_SOS;
          break;
          
          case 'Y':
            /* ECY */
            return OK_ECY;
          break;
          
          case 'Z':
XTDECID:
            /* DECID */
            return OK_DECID;
          break;
          
          case 'a':
            eech = qdgetch();
            switch (eech)
            {
              case '1':
                return OK_NSUB;
              break;
              
              case '2':
                return OK_NCOMMA;
              break;
              
              case '3':
                return OK_F20;
              break;
              
              default:
                return OK_UNK_3;
              break;
            }
          break;
          
          case 'b':
            /* EHB */
            return OK_EHB;
          break;
          
          case 'f':
            /* EHF */
            return OK_EHF;
          break;
          
          case 91:
            /* ESC [ - CSI */
XTCSI:
            eech = qdgetch();
            switch (eech)
            {
              case 49:
                /* ESC [1 */
                e3ch = qdgetch();
                switch (e3ch)
                {
                  case 48:
                    /* ESC [10 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F0;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F0;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F0;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F0 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F0 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F0 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return 
                                  (OK_F0 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F0 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126)
                                  return (OK_F0 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F0 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F0 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F0 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F0 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F0 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F0 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F0 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F0 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F0 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 49:
                    /* ESC [11 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F1;
                      break;
                      
                      case '^':
                        return OK_F23;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F1;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F1;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F1 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F1 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F1 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F1 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F1 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F1 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F1 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F13;
                            if (e6ch==126) return (OK_F1 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F1 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F1 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F25;
                            if (e6ch==126) return (OK_F1 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F37;
                            if (e6ch==126) return (OK_F1 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F1 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F1 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F1 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 50:
                    /* ESC [12 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F2;
                      break;
                      
                      case '^':
                        return OK_F24;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F2;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F2;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F2 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F2 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F2 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F2 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F2 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F2 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F2 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F14;
                            if (e6ch==126) return (OK_F2 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F2 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F2 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F26;
                            if (e6ch==126) return (OK_F2 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F38;
                            if (e6ch==126) return (OK_F2 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F2 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F2 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F2 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 51:
                    /* ESC [13 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F3;
                      break;
                      
                      case '^':
                        return OK_F25;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F3;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F3;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F3 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F3 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F3 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F3 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F3 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F3 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F3 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F15;
                            if (e6ch==126) return (OK_F3 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F3 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F3 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F27;
                            if (e6ch==126) return (OK_F3 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F39;
                            if (e6ch==126) return (OK_F3 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F3 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F3 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F3 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 52:
                    /* ESC [14 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F4;
                      break;
                      
                      case '^':
                        return OK_F26;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F4;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F4;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F4 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F4 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F4 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F4 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F4 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F4 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F4 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F16;
                            if (e6ch==126) return (OK_F4 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F4 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F4 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F28;
                            if (e6ch==126) return (OK_F4 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F40;
                            if (e6ch==126) return (OK_F4 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F4 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F4 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F4 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 53:
                    /* ESC [15 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F5;
                      break;
                      
                      case '^':
                        return OK_F27;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F5;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F5;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F5 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F5 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F5 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F5 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F5 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F5 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F5 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F17;
                            if (e6ch==126) return (OK_F5 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F5 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F5 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F29;
                            if (e6ch==126) return (OK_F5 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F41;
                            if (e6ch==126) return (OK_F5 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F5 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F5 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F5 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 55:
                    /* ESC [17 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F6;
                      break;
                      
                      case '^':
                        return OK_F28;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F6;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F6;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F6 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F6 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F6 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F6 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F6 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F6 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F6 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F18;
                            if (e6ch==126) return (OK_F6 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F6 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F6 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F30;
                            if (e6ch==126) return (OK_F6 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F42;
                            if (e6ch==126) return (OK_F6 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F6 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F6 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F6 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;

                  
                  case 56:
                    /* ESC [18 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F7;
                      break;
                      
                      case '^':
                        return OK_F29;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F7;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F7;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F7 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F7 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F7 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F7 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F7 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F7 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F7 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F19;
                            if (e6ch==126) return (OK_F7 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F7 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F7 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F31;
                            if (e6ch==126) return (OK_F7 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F43;
                            if (e6ch==126) return (OK_F7 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F7 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F7 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F7 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 57:
                    /* ESC [19 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F8;
                      break;
                      
                      case '^':
                        return OK_F30;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F8;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F8;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F8 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F8 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F8 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F8 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F8 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F8 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F8 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F20;
                            if (e6ch==126) return (OK_F8 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F8 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F8 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F32;
                            if (e6ch==126) return (OK_F8 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F44;
                            if (e6ch==126) return (OK_F8 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F8 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F8 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F8 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case '~':
                    if ((strcmp(termtype,"vt100")==0) || 
                        (strcmp(termtype,"VT100")==0) || 
                        (strcmp(termtype,"vt102")==0) || 
                        (strcmp(termtype,"VT102")==0)) 
                      return OK_FIND;
                    else 
                      return OK_HOME;
                  break;
                  
                  default:
                    /* ESC [1 UNKNOWN */
                    return OK_UNK_4;
                  break;
                }
              break;
              
              case 50:
                /* ESC [2 */
                e3ch = qdgetch();
                switch (e3ch)
                {
                  case 48:
                    /* ESC [20 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F9;
                      break;
                      
                      case '^':
                        return OK_F31;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F9;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F9;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F9 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F9 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F9 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F9 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F9 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F9 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F9 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F21;
                            if (e6ch==126) return (OK_F9 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F9 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F9 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F33;
                            if (e6ch==126) return (OK_F9 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F45;
                            if (e6ch==126) return (OK_F9 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F9 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F9 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F9 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 49:
                    /* ESC [21 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F10;
                      break;
                      
                      case '^':
                        return OK_F32;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F10;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F10;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F10 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F10 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F10 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F10 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F10 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F10 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F10 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F22;
                            if (e6ch==126) return (OK_F10 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F10 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F10 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F34;
                            if (e6ch==126) return (OK_F10 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F46;
                            if (e6ch==126) return (OK_F10 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F10 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F10 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F10 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 51:
                    /* ESC [23 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F11;
                      break;
                      
                      case '$':
                        return OK_F21;
                      break;
                      
                      case '@':
                        return OK_F43;
                      break;
                      
                      case '^':
                        return OK_F33;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F11;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F11;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F11 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F11 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F11 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F11 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F11 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F11 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F11 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F23;
                            if (e6ch==126) return (OK_F11 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F11 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F11 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F35;
                            if (e6ch==126) return (OK_F11 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F47;
                            if (e6ch==126) return (OK_F11 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F11 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F11 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F11 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 52:
                    /* ESC [24 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F12;
                      break;
                      
                      case '$':
                        return OK_F22;
                      break;
                      
                      case '@':
                        return OK_F44;
                      break;
                      
                      case '^':
                        return OK_F34;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F12;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F12;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F12 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F12 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F12 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F12 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F12 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F12 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F12 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F24;
                            if (e6ch==126) return (OK_F12 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F12 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F12 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F36;
                            if (e6ch==126) return (OK_F12 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if ((modsasfuncs==1) && (e6ch==126)) return OK_F48;
                            if (e6ch==126) return (OK_F12 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F12 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F12 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F12 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 53:
                    /* ESC [25 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F13;
                      break;
                      
                      case '^':
                        return OK_F35;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F13;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F13;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F13 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F13 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F13 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F13 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F13 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F13 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F13 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F13 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F13 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F13 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F13 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F13 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F13 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F13 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F13 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 54:
                    /* ESC [26 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F14;
                      break;
                      
                      case '^':
                        return OK_F36;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F14;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F14;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F14 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F14 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F14 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F14 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F14 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F14 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F14 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F14 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F14 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F14 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F14 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F14 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F14 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F14 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F14 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 56:
                    /* ESC [28 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        if ((strcmp(termtype,"vt100")==0) || 
                            (strcmp(termtype,"VT100")==0) || 
                            (strcmp(termtype,"vt102")==0) || 
                            (strcmp(termtype,"VT102")==0)) 
                          return OK_HELP;
                        else 
                          return OK_F15;
                      break;
                      
                      case '^':
                        return OK_F37;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F15;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F15;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F15 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F15 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F15 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F15 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F15 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F15 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F15 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F15 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F15 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F15 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F15 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F15 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F15 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F15 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F15 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 57:
                    /* ESC [29 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F16;
                      break;
                      
                      case '^':
                        return OK_F38;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F16;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F16;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F16 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F16 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F16 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F16 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F16 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F16 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F16 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F16 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F16 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F16 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F16 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F16 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F16 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F16 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F16 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 126:
XTIns:
                    /* INS = ESC [2~ */
                    return OK_INS;
                  break;
                  
                  default:
                    /* ESC [2 UNKNOWN */
                    return OK_UNK_4;
                  break;
                }
              break;
              
              case 51:
                /* ESC [3 */
                e3ch=qdgetch();
                switch (e3ch)
                {
                  case 49:
                    /* ESC [31 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F17;
                      break;
                      
                      case '^':
                        return OK_F39;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F17;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F17;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F17 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F17 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F17 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F17 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F17 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F17 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F17 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                            }
                            return OK_UNK_7;
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F17 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F17 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F17 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F17 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F17 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F17 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F17 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F17 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 50:
                    /* ESC [32 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F18;
                      break;
                      
                      case '^':
                        return OK_F40;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F18;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F18;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F18 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F18 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F18 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F18 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F18 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F18 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F18 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              default:
                                return OK_UNK_7;
                              break;
                            }
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F18 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F18 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F18 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F18 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F18 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F18 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F18 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F18 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 51:
                    /* ESC [33 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F19;
                      break;
                      
                      case '^':
                        return OK_F41;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F19;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F19;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F19 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F19 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F19 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F19 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F19 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F19 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F19 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              default:
                                return OK_UNK_7;
                              break;
                            }
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F19 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F19 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F19 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F19 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F19 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F19 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F19 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F19 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 52:
                    /* ESC [34 */
                    e4ch = qdgetch();
                    switch (e4ch)
                    {
                      case '~':
                        return OK_F20;
                      break;
                      
                      case '^':
                        return OK_F42;
                      break;
                      
                      case ';':
                        e5ch = qdgetch();
                        switch (e5ch)
                        {
                          case '~':
                            return OK_F20;
                          break;
                          
                          case '1':
                            e6ch = qdgetch();
                            switch (e6ch)
                            {
                              case '~':
                                return OK_F20;
                              break;
                              
                              case '0':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F20 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F20 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F20 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F20 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F20 | OK_META | OK_SHIFT | 
                                          OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F20 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) 
                                  return (OK_F20 | OK_META | OK_SHIFT | 
                                          OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              default:
                                return OK_UNK_7;
                              break;
                            }
                          break;
                          
                          case '2':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F20 | OK_SHIFT);
                            return OK_UNK_7;
                          break;
                          
                          case '3':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F20 | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '4':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F20 | OK_SHIFT | OK_ALT);
                            return OK_UNK_7;
                          break;
                          
                          case '5':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F20 | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '6':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F20 | OK_SHIFT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '7':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F20 | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '8':
                            e6ch = qdgetch();
                            if (e6ch==126) 
                              return (OK_F20 | OK_SHIFT | OK_ALT | OK_CTRL);
                            return OK_UNK_7;
                          break;
                          
                          case '9':
                            e6ch = qdgetch();
                            if (e6ch==126) return (OK_F20 | OK_META);
                            return OK_UNK_7;
                          break;
                          
                          default:
                            return OK_UNK_6;
                          break;
                        }
                      break;
                      
                      default:
                        return OK_UNK_5;
                      break;
                    }
                  break;
                  
                  case 126:
XTDel:
                    /* DEL = ESC [3~ */
                    return OK_DEL;
                  break;
                  
                  default:
                    /* ESC [3 UNKNOWN */
                    return OK_UNK_4;
                  break;
                }
              break;
              
              case '4':
                /* ESC [4 */
                e3ch = qdgetch();
                switch (e3ch)
                {
                  case '~':
                    if ((strcmp(termtype,"vt100")==0) || 
                        (strcmp(termtype,"VT100")==0) || 
                        (strcmp(termtype,"vt102")==0) || 
                        (strcmp(termtype,"VT102")==0)) 
                      return OK_SELECT;
                    else 
                      return OK_END;
                  break;
                  
                  default:
                    return OK_UNK_4;
                  break;
                }
              break;
              
              case '5':
                /* ESC [5 */
                e3ch = qdgetch();
                switch (e3ch)
                {
                  case '~':
                    if ((strcmp(termtype,"vt100")==0) || 
                        (strcmp(termtype,"VT100")==0) || 
                        (strcmp(termtype,"vt102")==0) || 
                        (strcmp(termtype,"VT102")==0)) 
                      return OK_RHT;
                    else 
                      return OK_PGUP;
                  break;
                  
                  default:
                    return OK_UNK_4;
                  break;
                }
              break;
              
              case '6':
                /* ESC [6 */
                e3ch = qdgetch();
                switch (e3ch)
                {
                  case '~':
                    if ((strcmp(termtype,"vt100")==0) || 
                        (strcmp(termtype,"VT100")==0) || 
                        (strcmp(termtype,"vt102")==0) || 
                        (strcmp(termtype,"VT102")==0)) 
                      return OK_CLEAR;
                    else 
                      return OK_PGDOWN;
                  break;
                  
                  default:
                    return OK_UNK_4;
                  break;
                }
              break;
              
              case 'A':
                return OK_UP;
              break;
              
              case 'B':
                return OK_DOWN;
              break;
              
              case 'C':
                return OK_RIGHT;
              break;
              
              case 'D':
                return OK_LEFT;
              break;
              
              case 'E':
                return OK_N5;
              break;
              
              case 'F':
                return OK_END;
              break;
              
              case 'G':
                if ((strcmp(termtype, "ansipc")==0) ||
                    (strcmp(termtype, "ANSIPC")==0))
                  return OK_PGDOWN;
                return OK_N5;
              break;
              
              case 'H':
                return OK_HOME;
              break;
              
              case 'I':
                return OK_PGUP;
              break;
              
              case 'L':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_INS;
                return OK_UNK_3;
              break;
              
              case 'M':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F1;
                return OK_UNK_3;
              break;
              
              case 'N':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F2;
                return OK_UNK_3;
              break;
              
              case 'O':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F3;
                return OK_UNK_3;
              break;
              
              case 'P':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F4;
                return OK_PAUSE;
              break;
              
              case 'Q':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F5;
                return OK_UNK_3;
              break;
              
              case 'R':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F6;
                return OK_UNK_3;
              break;
              
              case 'S':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F7;
                return OK_UNK_3;
              break;
              
              case 'T':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F8;
                return OK_UNK_3;
              break;
              
              case 'U':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F9;
                return OK_UNK_3;
              break;
              
              case 'V':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return OK_F10;
                return OK_UNK_3;
              break;
              
              case 'Y':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F1);
                return OK_UNK_3;
              break;
              
              case 'Z':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F2);
                return OK_UNK_3;
              break;
              
              case 'a':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F3);
                return OK_UNK_3;
              break;
              
              case 'b':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F4);
                return OK_UNK_3;
              break;
              
              case 'c':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F5);
                return OK_UNK_3;
              break;
              
              case 'd':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F6);
                return OK_UNK_3;
              break;
              
              case 'e':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F7);
                return OK_UNK_3;
              break;
              
              case 'f':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F8);
                return OK_UNK_3;
              break;
              
              case 'g':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F9);
                return OK_UNK_3;
              break;
              
              case 'h':
                if ((strcmp(termtype, "ansipc") == 0) ||
                    (strcmp(termtype, "ANSIPC") == 0))
                  return (OK_SHIFT | OK_F10);
                return OK_UNK_3;
              break;
              
              
              
              case '[':
                e3ch = qdgetch();
                switch (e3ch)
                {
                  case 'A':
                    return OK_F1;
                  break;
                  
                  case 'B':
                    return OK_F2;
                  break;
                  
                  case 'C':
                    return OK_F3;
                  break;
                  
                  case 'D':
                    return OK_F4;
                  break;
                  
                  case 'E':
                    return OK_F5;
                  break;
                  
                  default:
                    return OK_UNK_4;
                  break;
                }
              break;
              
              default:
                /* ESC [ UNKNOWN */
                return OK_UNK_3;
              break;
            }
          break;
          
          case 92:
XTST:
            /* ST */
            return OK_ST;
          break;
          
          case ']':
XTOSC:
            return OK_OSC;
          break;
          
          case '!':
            return OK_NDEL;
          break;
          
          case '@':
            return OK_NENTER;
          break;
          
          case '#':
            return OK_F6;
          break;
          
          case '$':
            return OK_F7;
          break;
          
          case '%':
            return OK_F8;
          break;
          
          case '^':
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0))  
              return OK_F9;
XTPM:
            /* PM */
            return OK_PM;
          break;
          
          case '&':
            return OK_F10;
          break;
          
          case '*':
            return OK_F11;
          break;
          
          case '(':
            return OK_F12;
          break;
          
          case ')':
            return OK_F13;
          break;
          
          case '-':
            return OK_F14;
          break;
          
          case '=':
            return OK_F17;
          break;
          
          case '_':
            /* VT100 F18 ONLY! */
            if ((strcmp(termtype,"vt100")==0) || 
                (strcmp(termtype,"VT100")==0)) 
              return OK_F18;
XTAPC:
            /* APC */
            return OK_APC;
          break;
          
          case '+':
            return OK_F19;
          break;
          
          default:
            /* ESC UNKNOWN */
            return OK_UNK_2;
          break;
        }
      }
      else
      {
        if (ch == 0x90)
        {
          if ((memcmp(termtype,"vt",2)==0) || 
              (memcmp(termtype,"VT",2)==0)) 
            return OK_DCS;
          return ch;
        }
        else if (ch == 0x96)
        {
          if ((memcmp(termtype,"vt",2)==0) || (memcmp(termtype,"VT",2)==0)) 
            return OK_SPA;
          return ch;
        }
        else if (ch == 0x97)
        {
          if ((memcmp(termtype,"vt",2)==0) || (memcmp(termtype,"VT",2)==0)) 
            return OK_EPA;
          return ch;
        }
        else if (ch == 0x98)
        {
          ech = ch;
          goto XTSOS;
        }
        else if (ch == 0x9A)
        {
          ech = ch;
          goto XTDECID;
        }
        else if (ch == 0x9B)
        {
          ech = ch;
          goto XTCSI;
        }
        else if (ch == 0x9C)
        {
          ech = ch;
          goto XTST;
        }
        else if (ch == 0x9D)
        {
          ech = ch;
          goto XTOSC;
        }
        else if (ch == 0x9E)
        {
          ech = ch;
          goto XTPM;
        }
        else if (ch == 0x9F)
        {
          ech = ch;
          goto XTAPC;
        }
        else if (ch == 0x84)
        {
          ech = ch;
          goto XTIND;
        }
        else if (ch == 0x85)
        {
          ech = ch;
          goto XTNEL;
        }
        else if (ch == 0x88)
        {
          ech = ch;
          goto XTHTS;
        }
        else if (ch == 0x8D)
        {
          ech = ch;
          goto XTRI;
        }
        else if (ch == 0x8E)
        {
          ech = ch;
          goto XTSS2;
        }
        else if (ch == 0x8F)
        {
          ech = ch;
          goto XTSS3;
        }
        else if ((ch < 256) && (ch >= 0))
        {
          return ch;
        }
        else
        {
          return OK_UNK_1;
        }
      }
    }
  return OK_UNK_1;
#else
  int keyn, repeat;
  while (!GetKeynWin(&keyn, &repeat)) continue;
  return keyn;
#endif
}


int readqdline(char *targetstring, char *templatestring, int eofiscancel)
{
#ifdef WINDOWS
  char itarget[256] = "";
  char itemplate[256];
  int ilen = 256;
  strncpy(itemplate,templatestring, ilen-1);
  int ret = NEWreadqdline(itarget, itemplate, ilen, eofiscancel);
  strcpy(targetstring, itarget);
  return ret;
#else
  int ch;
  int e4ch;
  int e5ch;
  char itemplate[256];
  int itpos = 0;
  char theline[256] = "";
  int tlpos = 0;
  int insmode = 0;
  int retcond = 0;
  
  theline[255] = 0;
  memset(itemplate,0,256);
  strcpy(itemplate, templatestring);
  if ((ch = qdinstrch(itemplate,10,0))>=0) itemplate[ch]=0;
  exitreadqdline = 0;
  if (eofiscancel == 0)
  {
    if (regsiginthandler()==-1) return -1;
    qdgetchmode = 3;
  }
  
  while (exitreadqdline == 0)
  {
   ch=getkeyn();
   switch (ch)
   {
     case OK_BLUE:
       /* ESC P - INS On*/
       insmode = 1;
     break;
     
     case OK_RED:
       /* ESC Q - INS Off */
       insmode = 0;
     break;
     
     case OK_ENL:
     case OK_GREY:
     case OK_F8:
       /* ESC CR, ESC R, F8 */
       memset(itemplate,0,256);
       strcpy(itemplate,theline);
       memset(theline,0,256);
       strcpy(theline,"\0");  /* I don't think we even need this line! */
       tlpos=0;
       itpos=0;
       insmode = 0;
       printf("@\n");
     break;
     
     case OK_QF1:
     case OK_F1:
     case OK_PF1:
       /* ESC S, F1 */
       if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); 
       else if (itemplate[itpos]==4) printf("\033[7mD\033[27m"); 
       else  printf("%c",itemplate[itpos]);
       if ((itemplate[itpos] != 0) && (tlpos < 255))
       {
         theline[tlpos] = itemplate[itpos];
         tlpos++;
       }
       if ((itpos < 255) && (insmode == 0) && (itemplate[itpos] != 0)) itpos++;
     break;
     
     case OK_QF2:
     case OK_F2:
     case OK_PF2:
       /* ESC T, F2 - write 'til char */
       e5ch = qdgetch();
       e5ch = qdinstrch(itemplate,e5ch,itpos); /* This variable reuse will probably get me punched someday */
       if (e5ch>0)
       {
         e4ch=e5ch+itpos;
         while ((itpos < e4ch) && (itpos<255))
         {
           if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); 
           else if (itemplate[itpos]==4) printf("\033[7mD\033[27m"); 
           else printf("%c",itemplate[itpos]);
           if ((itemplate[itpos] != 0) && (tlpos < 255))
           {
             theline[tlpos] = itemplate[itpos];
             tlpos++;
           }
           itpos++;
         }
         if (insmode != 0) itpos = e4ch - e5ch;
       }
     break;
     
     case OK_QF3:
     case OK_F3:
     case OK_PF3:
       /* ESC U, F3 */
       if ((itpos<255) && (itemplate[itpos] != 0))
       {
         e5ch=itpos;
         while ((itpos < 255) && (itemplate[itpos] !=0) && (tlpos < 255))
         {
           theline[tlpos]=itemplate[itpos];
           if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); 
           else if (itemplate[itpos]==4) printf("\033[7mD\033[27m"); 
           else printf("%c",itemplate[itpos]);
           tlpos++;
           itpos++;
         }
         if (insmode != 0) itpos = e5ch;
       }
     break;
     
     case OK_QF4:
     case OK_F4:
     case OK_PF4:
       /* ESC V, F4 */
       if (itpos < 255) itpos++;
     break;
     
     case OK_QF5:
     case OK_F5:
       /* ESC W, F5 */
       e5ch = qdgetch();
       e5ch = qdinstrch(itemplate,e5ch,itpos); 
       if (e5ch>0)
       {
         itpos+=e5ch;
       }
     break;
     
     case OK_DEL:
     case OK_NDEL:
     case 8:
     case 127:
       /* DEL (NumDEL = ESC On) */
       if (tlpos>0)
       {
#ifdef WINDOWS
         int bses;
         if (theline[tlpos-1]==9)
         {
             bses = popfromtabstack();
             if (!bses)bses=1;
         }
         else bses=1;
         termbsn(bses);
#else
         termbsn(1);
#endif
         tlpos--;
         if ((theline[tlpos]==12) || (theline[tlpos]==4)) termbsn(1);
         theline[tlpos]=0;
       }
       if ((itpos > 0) && (insmode == 0)) itpos--;
     break;
     
     case OK_INS:
     case OK_N0:
       /* INS (NumINS = ESC Op) */
       if (insmode == 0) { insmode = 1; } else { insmode = 0; }
     break;
     
     case 12:
       /* ^L */
       printf("\033[7mL\033[27m");
       theline[tlpos]=12;
       tlpos++;
       if ((itpos < 255) && (insmode == 0)) itpos++;
     break;
     
     case 24:
       /* ^X */
       printf("\\\n");
       tlpos=0;
       strcpy(theline,"\x00");
     break;
     
     case OK_NENTER:
       ch = 10;
     case 13:
     case 10:
       /* CRLF */
       if (tlpos < 255)
        {
          printf("\n");
          theline[tlpos]=ch;
          tlpos++;
          theline[tlpos]=0;
          goto ReturnPt;
        }
     break;
     
     case 25:
       /* ^Y */
       theline[tlpos]=0;
       goto ReturnPt;
     break;
            
     case 9:
     case 11:
     case OK_NHT:
       /* Tabs */
       if (tlpos < 255)
       {
         writetab();
         if ((itpos < 255) && (insmode == 0)) itpos++;
         theline[tlpos]=9;
         tlpos++;
       }
     break;
            
     case 4:
       /* ^D = Cancel Mode or EOF */
       if (eofiscancel != 0)
       {
         tlpos=0;
         memset(theline,0,256);
         strcpy(theline,"\x04\x00"); /* Old way of signalling cancellation */
         goto ReturnPt;
       }
       else
       {
         printf("\033[7mD\033[27m");
         theline[tlpos]=4;
         tlpos++;
         if ((itpos < 255) && (insmode == 0)) itpos++;
       }
     break;
            
     case 3:
       /* ^C = Cancel Mode */
       if (eofiscancel == 0)
       {
         tlpos=0;
         memset(theline,0,256);
         strcpy(theline,"\x03\x00"); /* Old way of signalling cancellation */
         retcond = 3;
         goto ReturnPt;
       }
       /* Otherwise ignore it! */
     break;
            
     default:
       if ((tlpos < 255) && (ch<256) && (ch >= 32))
       {
         printf("%c",ch);
         if ((itpos < 255) && (insmode == 0)) itpos++;
         theline[tlpos]=ch;
         tlpos++;
       }
     break;
   }
  }
  retcond = 3;
ReturnPt:
  exitreadqdline = 0;
  qdgetchmode = 0;
  strcpy(targetstring, theline);
  cleartabstack();
  if (eofiscancel == 0) deregsiginthandler();
  else if (theline[0] == 4) return 4;
  else if (theline[0] == 3) return 3;
  return retcond;
#endif
}


int NEWreadqdline(char *targetstring, char *templatestring, int stringlen, int eofiscancel)
{
  /*
  * targetstring is the target string
  * templatestring is the template
  * templatestring cannot be longer than the size allocated to targetstring
  * The size in chars of targetstring must be specified in stringlen
  * eofiscancel must be 1 or 0
  *
  * Returns  3 if Ctrl+C was used to cancel text entry, 
  *          4 if Ctrl+D was used to exit text entry,
  *         -1 if signal-handler registration failed, -2 if inputs are bad, 
  *         -3 if out of memory, otherwise 0.
  */
  int ch;
  int e4ch;
  int e5ch;
  char *itemplate;
  int itpos = 0;
  int tlpos = 0;
  int insmode = 0;
  int retcond = 0;
#ifdef WINDOWS
  int lastesc = 0;
#endif
  
  if (stringlen <= strlen(templatestring) || stringlen < 2)
  {
    /* Output string length is too short! */
    return -2;
  }
  itemplate = (char *) malloc(stringlen * sizeof(char));
  if (itemplate == NULL) return -3; /* Out of Memory */
  
  targetstring[stringlen-1] = 0;
  memset(itemplate,0,stringlen);
  strcpy(itemplate, templatestring);
#ifdef WINDOWS
  if ((ch = qdinstrch(itemplate,13,0))>=0) itemplate[ch]=0;
#endif
  if ((ch = qdinstrch(itemplate,10,0))>=0) itemplate[ch]=0;
  exitreadqdline = 0;
  if (eofiscancel == 0)
  {
    if (regsiginthandler()==-1)
    {
      free(itemplate);
#ifdef WINDOWS
      breakhandlerset = FALSE;
#endif
      return -1;
    }
#ifdef WINDOWS
    breakhandlerset = TRUE;
#else
    qdgetchmode = 1;
#endif
  }
  
  while (exitreadqdline == 0)
  {
   ch=getkeyn();
#ifdef WINDOWS
   if (lastesc)
   {
     switch ((ch & OK_LETTERCMDMODIFIERINFOS))
     {
       case 'P':
         ch = OK_BLUE;
       break;
       
       case 'Q':
         ch = OK_RED;
       break;
       
       case 'R':
         ch = OK_GREY;
       break;
       
       case OK_CRETURN:
         ch = OK_ENL;
       break;
       
       case 'S':
         ch = OK_QF1;
       break;
       
       case 'T':
         ch = OK_QF2;
       break;
       
       case 'U':
         ch = OK_QF3;
       break;
       
       case 'V':
         ch = OK_QF4;
       break;
       
       case 'W':
         ch = OK_QF5;
       break;
     }
   }
   switch ((ch & OK_LETTERCMDMODIFIERINFOSNOCTRLSNOMETA))
   {
     case OK_ESC:
       if (lastesc)
       {
           lastesc = 0;
           /* Do an ESC function */
       }
       else lastesc = 1;
     break;
     
#else
   switch (ch)
   {
#endif
     case OK_BLUE:
       /* ESC P - INS On*/
       insmode = 1;
     break;
     
     case OK_RED:
       /* ESC Q - INS Off */
       insmode = 0;
     break;
     
     case OK_ENL:
     case OK_GREY:
     case OK_F8:
       /* ESC CR, ESC R, F8 */
       memset(itemplate,0,stringlen);
       strcpy(itemplate,targetstring);
       memset(targetstring,0,stringlen);
       strcpy(targetstring,"\x00");  /* Is this line necessary? */
       tlpos=0;
       itpos=0;
       insmode = 0;
       printf("@\n");
     break;
     
     case OK_QF1:
     case OK_F1:
     case OK_PF1:
       /* ESC S, F1 - Write */
#ifdef WINDOWS
       if (itemplate[itpos]==12)
       {
           SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
           printf("L");
           SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
       }
       else if (itemplate[itpos]==4)
       {
           SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
           printf("D");
           SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
       }
#else
       if (itemplate[itpos]==12) printf("\033[7mL\033[27m");
       else if (itemplate[itpos]==4) printf("\033[7mD\033[27m");
#endif
       else  printf("%c",itemplate[itpos]);
       if ((itemplate[itpos] != 0) && (tlpos < stringlen-1))
       {
         targetstring[tlpos] = itemplate[itpos];
         tlpos++;
       }
       if ((itpos < stringlen-1) && (insmode == 0) && (itemplate[itpos] != 0)) itpos++;
     break;
     
     case OK_QF2:
     case OK_F2:
     case OK_PF2:
       /* ESC T, F2 - write 'til char */
       e5ch = qdgetch();
       e5ch = qdinstrch(itemplate,e5ch,itpos); /* This variable reuse will probably get me punched someday */
       if (e5ch>0)
       {
         e4ch=e5ch+itpos;
         while ((itpos < e4ch) && (itpos<stringlen-1))
         {
#ifdef WINDOWS
           if (itemplate[itpos]==12)
           {
               SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
               printf("L");
               SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
           }
           else if (itemplate[itpos]==4)
           {
               SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
               printf("D");
               SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
           }
#else
           if (itemplate[itpos]==12) printf("\033[7mL\033[27m");
           else if (itemplate[itpos]==4) printf("\033[7mD\033[27m");
#endif
           else  printf("%c",itemplate[itpos]);
           if ((itemplate[itpos] != 0) && (tlpos < stringlen-1))
           {
             targetstring[tlpos] = itemplate[itpos];
             tlpos++;
           }
           itpos++;
         }
         if (insmode != 0) itpos = e4ch - e5ch;
       }
     break;
     
     case OK_QF3:
     case OK_F3:
     case OK_PF3:
       /* ESC U, F3 */
       if ((itpos<stringlen) && (itemplate[itpos] != 0))
       {
         e5ch=itpos;
         while ((itpos < stringlen) && (itemplate[itpos] !=0) && (tlpos < stringlen))
         {
           targetstring[tlpos]=itemplate[itpos];
#ifdef WINDOWS
           if (itemplate[itpos]==12)
           {
               SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
               printf("L");
               SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
           }
           else if (itemplate[itpos]==4)
           {
               SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
               printf("D");
               SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
           }
#else
           if (itemplate[itpos]==12) printf("\033[7mL\033[27m");
           else if (itemplate[itpos]==4) printf("\033[7mD\033[27m");
#endif
           else printf("%c",itemplate[itpos]);
           tlpos++;
           itpos++;
         }
         if (insmode != 0) itpos = e5ch;
       }
     break;
     
     case OK_QF4:
     case OK_F4:
     case OK_PF4:
       /* ESC V, F4 */
       if (itpos < stringlen-1) itpos++;
     break;
     
     case OK_QF5:
     case OK_F5:
       /* ESC W, F5 */
       e5ch = qdgetch();
       e5ch = qdinstrch(itemplate,e5ch,itpos);
       if (e5ch>0)
       {
         itpos+=e5ch;
       }
     break;
     
     case OK_DEL:
     case OK_NDEL:
     case 8:
#ifdef WINDOWS
     case OK_BS:
#endif
     case 127:
       /* DEL (NumDEL = ESC On) */
#ifdef WINDOWS
       setcvars();
#endif
       if (tlpos>0)
       {
#ifdef WINDOWS
         int bses;
         if (targetstring[tlpos-1]==9)
         {
             bses = popfromtabstack();
             if (!bses)bses=1;
         }
         else bses=1;
         termbsn(bses);
#else
         termbsn(1);
#endif
         tlpos--;
#ifndef WINDOWS
         if ((targetstring[tlpos]==12) || (targetstring[tlpos]==4)) termbsn(1);
#endif
         targetstring[tlpos]=0;
       }
       if ((itpos > 0) && (insmode == 0)) itpos--;
     break;
     
     case OK_INS:
     case OK_N0:
       /* INS (NumINS = ESC Op) */
       if (insmode == 0) { insmode = 1; } else { insmode = 0; }
     break;
     
     case 12:
       /* ^L */
#ifdef WINDOWS
       SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
       printf("L");
       SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
#else
       printf("\033[7mL\033[27m");
#endif
       targetstring[tlpos]=12;
       tlpos++;
       if ((itpos < stringlen-1) && (insmode == 0)) itpos++;
     break;
     
     case 24:
       /* ^X */
       printf("\\\n");
       tlpos=0;
       strcpy(targetstring,"\x00");
     break;

#ifdef WINDOWS
     case 26:
       /* ^Z */
       SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
       printf("Z");
       SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
       targetstring[tlpos]=26;
       tlpos++;
       if ((itpos < stringlen-1) && (insmode == 0)) itpos++;
     break;
#endif
     
     case OK_NENTER:
       ch = 10;
#ifdef WINDOWS
     case OK_CRETURN:
#else
     case 13:
#endif
     case 10:
       /* CRLF */
#if defined(WINDOWS) && defined(NOTRANSLATE)
       if (tlpos < stringlen-2)
#else
       if (tlpos < stringlen-1)
#endif
       {
          printf("\n");
#if defined(WINDOWS) && defined(NOTRANSLATE)
          targetstring[tlpos]=13;
          tlpos++;
#endif
          targetstring[tlpos]=10; /* Not sure if to keep linux-specific behaviour of having this be ch instead of 10? */
          tlpos++;
          targetstring[tlpos]=0;
          goto ReturnPt;
       }
     break;
     
     case 25:
       /* ^Y */
       targetstring[tlpos]=0;
       goto ReturnPt;
     break;
            
     case 9:
     case 11:
     case OK_NHT:
       /* Tabs */
       if (tlpos < stringlen-1)
       {
         writetab();
         if ((itpos < stringlen-1) && (insmode == 0)) itpos++;
         targetstring[tlpos]=9;
         tlpos++;
       }
     break;
            
     case 4:
       /* ^D = Cancel Mode or EOF */
       if (eofiscancel != 0)
       {
         tlpos=0;
         memset(targetstring,0,stringlen);
         strcpy(targetstring,"\x04\x00"); /* Old way of signalling cancellation */
         goto ReturnPt;
       }
       else
       {
#ifdef WINDOWS
         SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
         printf("D");
         SetTextColour(GetBgTextColour(),GetFgTextColour(),0);
#else
         printf("\033[7mD\033[27m");
#endif
         targetstring[tlpos]=4;
         tlpos++;
         if ((itpos < stringlen-1) && (insmode == 0)) itpos++;
       }
     break;
            
     case 3:
       /* ^C = Cancel Mode */
       if (eofiscancel == 0)
       {
         tlpos=0;
         memset(targetstring,0,stringlen);
         strcpy(targetstring,"\x03\x00"); /* Old way of signalling cancellation */
         goto ReturnPt;
       }
       /* Otherwise ignore it! */
     break;
            
     default:
#ifdef WINDOWS
       if ((tlpos < stringlen-1) && ((ch & OK_LETTERCMDMODIFIERINFOS)<256) && ((ch & OK_LETTERCMDMODIFIERINFOS) >= 32))
       {
         printf("%c",(ch & OK_LETTERCMDMODIFIERINFOS));
         if ((itpos < stringlen-1) && (insmode == 0)) itpos++;
         targetstring[tlpos]=(ch & OK_LETTERCMDMODIFIERINFOS);
#else
       if ((tlpos < stringlen-1) && (ch<256) && (ch >= 32))
       {
         printf("%c",ch);
         if ((itpos < stringlen-1) && (insmode == 0)) itpos++;
         targetstring[tlpos]=ch;
#endif
         tlpos++;
       }
     break;
   }
#ifdef WINDOWS
    if ((ch & OK_NOLOCKS) == OK_ESC) lastesc = 1;
    else if ((ch & OK_NOMODMAX) != OK_LSHIFT
             && (ch & OK_NOMODMAX) != OK_RSHIFT
             && (ch & OK_NOMODMAX) != OK_CLOCK
             && (ch & OK_NOMODMAX) != OK_NLOCK
             && (ch & OK_NOMODMAX) != OK_SLOCK
             && (ch & OK_NOMODMAX) != 0
             ) lastesc = 0;
#endif
  }
  retcond = 3;
ReturnPt:
#ifdef WINDOWS
  if (exitreadqdline) retcond = 3;
#endif
  free(itemplate);
#ifndef WINDOWS
  qdgetchmode = 0;
#endif
  exitreadqdline = 0;
  cleartabstack();
  if (eofiscancel == 0) deregsiginthandler();
  else if (targetstring[0] == 4) return 4;
  else if (targetstring[0] == 3) return 3;
  return retcond;
}




int keypause()
{
  int tempi=0;
  writestr("[Press a key to continue...]\n");
  tempi = getkeyn();
#ifdef WINDOWS
  setcvars();
  gotoxy(cx,cy-1);
  writestr("                               \n");
  gotoxy(cx,cy-1);
#else
  printf("\033[1A");
  printf("                               \n");
  printf("\033[1A");
#endif
  return 0;
}


int yesnomsg( char *amsg)
{
  char lastanswer[256] = "\x00";
  char answer[256] = "\x00";
  while (1==1)
  {
    printf("%s\n", amsg);
    if (readqdline(answer,lastanswer,1)==0)
    {
      switch (firstletter(answer))
      {
        case (64+25):
        case (96+25):
          return 1;
        break;
        
        case (64+14):
        case (96+14):
          return 0;
        break;
      }
      printf("Invalid answer!\n");
      strcpy(lastanswer,answer);
    }
  }
}


int NEWyesnomsg( char *amsg, int eofiscancel)
{
  char lastanswer[256] = "\x00";
  char answer[256] = "\x00";
  while (1==1)
  {
    printf("%s\n", amsg);
    if (NEWreadqdline(answer,lastanswer,256,eofiscancel)==0)
    {
      switch (firstletter(answer))
      {
        case (64+25):
        case (96+25):
          return 1;
        break;
        
        case (64+14):
        case (96+14):
          return 0;
        break;
      }
      printf("Invalid answer!\n");
      strcpy(lastanswer,answer);
    }
  }
}


void DoNothing()
{
  return;
}

int GiveOne()
{
  return 1;
}
