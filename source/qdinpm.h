#ifndef __INC_QDINPM_H__
#define __INC_QDINPM_H__ 1

#if ( defined ( WIN32 ) || defined ( WIN64 ) ) && ( ! defined ( WINDOWS ) )
#define WINDOWS
#endif

#ifdef WINDOWS
#include <Windows.h>


#define OK_CRETURN 13      /* CR */
#define OK_SPACE 32        /* Space Bar */
#define OK_HASH 35         /* Hash sign */
#define OK_APOSTROPHE 39   /* Apostrophe or single quote */
#define OK_PLUS 43         /* Plus sign */
#define OK_COMMA 44        /* Comma */
#define OK_MINUS 45        /* Minus sign */
#define OK_FSTOP 46        /* Full stop */
#define OK_FSLASH 47       /* Forward Slash */
#define OK_0 48
#define OK_1 49
#define OK_2 50
#define OK_3 51
#define OK_4 52
#define OK_5 53
#define OK_6 54
#define OK_7 55
#define OK_8 56
#define OK_9 57
#define OK_COLON 58
#define OK_SEMICOLON 59

/* Capital letters = 65-90 */
#define OK_OPENSQBRACKET 91 /* Open square bracket */
#define OK_BACKSLASH 92    /* Backslash */
#define OK_CLOSESQBRACKET 93 /* Close square bracket */
#define OK_GRAVE 96        /* ` = Grave symbol */
#endif

#define OK_ESC 256+0
#define OK_F0 256+1
#define OK_F1 256+2
#define OK_F2 256+3
#define OK_F3 256+4
#define OK_F4 256+5
#define OK_F5 256+6
#define OK_F6 256+7
#define OK_F7 256+8
#define OK_F8 256+9
#define OK_F9 256+10
#define OK_F10 256+11
#define OK_F11 256+12
#define OK_F12 256+13
#define OK_F13 256+14
#define OK_F14 256+15
#define OK_F15 256+16
#define OK_F16 256+17
#define OK_F17 256+18
#define OK_F18 256+19
#define OK_F19 256+20
#define OK_F20 256+21
#define OK_PS 256+22
#define OK_SLOCK 256+23
#define OK_PAUSE 256+24
#define OK_BS 256+25
#define OK_INS 256+26
#define OK_HOME 256+27
#define OK_PGUP 256+28
#define OK_NLOCK 256+29
#define OK_NDIV 256+30
#define OK_NMUL 256+31
#define OK_NSUB 256+32
#define OK_HT 256+33
#define OK_RHT 256+34
#define OK_DEL 256+35
#define OK_END 256+36
#define OK_PGDOWN 256+37
#define OK_NADD 256+38
#define OK_CLOCK 256+39
#define OK_NENTER 256+40
#define OK_NDEL 256+41
#define OK_N0 256+42
#define OK_N1 256+43
#define OK_N2 256+44
#define OK_N3 256+45
#define OK_N4 256+46
#define OK_N5 256+47
#define OK_N6 256+48
#define OK_N7 256+49
#define OK_N8 256+50
#define OK_N9 256+51
#define OK_UP 256+52
#define OK_LEFT 256+53
#define OK_DOWN 256+54
#define OK_RIGHT 256+55
#define OK_NSP 256+56
#define OK_NHT 256+57
#define OK_PF1 256+58
#define OK_PF2 256+59
#define OK_PF3 256+60
#define OK_PF4 256+61
#define OK_NCOMMA 256+62
#define OK_NEQ 256+63
#define OK_BLUE 256+64
#define OK_RED 256+65
#define OK_GREY 256+66
#define OK_GRAY 256+66
#define OK_WHITE 256+67
#define OK_QF1 256+68
#define OK_QF2 256+69
#define OK_QF3 256+70
#define OK_QF4 256+71
#define OK_QF5 256+72
#define OK_CLEAR 256+73
#define OK_FIND 256+74
#define OK_SELECT 256+75
#define OK_HELP 256+76
#define OK_EHV 256+77
#define OK_EHF 256+78
#define OK_EHB 256+79
#define OK_EHR 256+80
#define OK_EHU 256+81
#define OK_ECV 256+82
#define OK_ECF 256+83
#define OK_ECB 256+84
#define OK_ECR 256+85
#define OK_ECP 256+86
#define OK_ECG 256+87
#define OK_ECT 256+88
#define OK_ECY 256+89
#define OK_ECN 256+90
#define OK_ENL 256+91

#define OK_F21 256+92
#define OK_F22 256+93
#define OK_F23 256+94
#define OK_F24 256+95
#define OK_F25 256+96
#define OK_F26 256+97
#define OK_F27 256+98
#define OK_F28 256+99
#define OK_F29 256+100
#define OK_F30 256+101
#define OK_F31 256+102
#define OK_F32 256+103
#define OK_F33 256+104
#define OK_F34 256+105
#define OK_F35 256+106
#define OK_F36 256+107
#define OK_F37 256+108
#define OK_F38 256+109
#define OK_F39 256+110
#define OK_F40 256+111
#define OK_F41 256+112
#define OK_F42 256+113
#define OK_F43 256+114
#define OK_F44 256+115
#define OK_F45 256+116
#define OK_F46 256+117
#define OK_F47 256+118
#define OK_F48 256+119

#define OK_IND 256+128
#define OK_NEL 256+129
#define OK_HTS 256+130
#define OK_RI 256+131
#define OK_SS2 256+132
#define OK_OSC 256+133
#define OK_APC 256+134
#define OK_DCS 256+135
#define OK_SPA 256+136
#define OK_EPA 256+137
#define OK_SOS 256+138
#define OK_DECID 256+139
#define OK_ST 256+140
#define OK_PM 256+141

#ifdef WINDOWS
#define OK_MLB 256+160 /* Left Mouse Button */
#define OK_MRB 256+161 /* Right Mouse Button */
#define OK_MMB 256+162 /* Middle Mouse Button */
#define OK_MX1B 256+163 /* X1 Mouse Button */
#define OK_MX2B 256+164 /* X2 Mouse Button */
#define OK_KANA 256+165 /* Kana key */
#define OK_HANGUL 256+166 /* Hangul Key */
#define OK_JUNJA 256+167 /* Junja key */
#define OK_FINAL 256+168 /* IME Final key */
#define OK_HANJA 256+169 /* Hanja Key */
#define OK_KANJI 256+170 /* Kanji Key */
#define OK_CONVERT 256+171 /* IME Convert Key */
#define OK_NONCONVERT 256+172 /* IME Non-Convert Key */
#define OK_ACCEPT 256+173 /* IME Accept Key */
#define OK_MODECHANGERQ 256+174 /* IME Mode Change Request Key */
#define OK_PRINT 256+175 /* Print Key */
#define OK_EXECUTE 256+176 /* Execute Key */
#define OK_SLEEP 256+177 /* Sleep key */
#define OK_SEPARATOR 256+178 /* Numpad Separator key */
#define OK_LSHIFT 256+179 /* Left Shift Key, 0x1B3 */
#define OK_RSHIFT 256+180 /* Right shift key, 0x1B4 */
#define OK_APPS 256+181 /* Applications key */
#define OK_LMENU 256+182 /* Left Menu Key */
#define OK_RMENU 256+183 /* Right Menu Key */
#define OK_BROWSERBACK 256+184 /* Browser Back key */
#define OK_BROWSERFWD 256+185 /* Browser Forward key */
#define OK_BROWSERREF 256+186 /* Browser Refresh key */
#define OK_BROWSERSTOP 256+187 /* Browser Stop key */
#define OK_BROWSERSEARCH 256+188 /* Browser Search key */
#define OK_BROWSERFAV 256+189 /* Browser Favourites key */
#define OK_BROWSERHOME 256+190 /* Browser Home key */
#define OK_VOLMUTE 256+191 /* Volume Mute Key */
#define OK_VOLDOWN 256+192 /* Volume Down Key */
#define OK_VOLUP 256+193 /* Volume Up Key */
#define OK_MEDIANEXT 256+194 /* Media Next Track key */
#define OK_MEDIAPREV 256+195 /* Media Previous Track key */
#define OK_MEDIASTOP 256+196 /* Media Stop key */
#define OK_MEDIAPLAY 256+197 /* Media Play/Pause key */
#define OK_STARTMAIL 256+198 /* Start email key */
#define OK_STARTMEDIA 256+199 /* Start media player key */
#define OK_STARTAPP1 256+200 /* Start Application 1 key */
#define OK_STARTAPP2 256+201 /* Start Application 2 key */
#define OK_OEM8 256+202 /* OEM key varies by country */
#define OK_PROCESSKEY 256+203 /* IME Process Key */
#define OK_ATTENTION 256+204 /* Attention Key */
#define OK_CRSEL 256+205 /* CrSel Key */
#define OK_EXSEL 256+206 /* ExSel Key */
#define OK_ERASEEOF 256+207 /* Erase EOF key */
#define OK_PLAY 256+208 /* Play Key */
#define OK_ZOOM 256+209 /* Zoom key */
#define OK_PA1 256+210 /* PA1 key */
#define OK_OEMCLEAR 256+211 /* OEM Clear key */
#define OK_NONAME 256+212 /* Reserved */
#define OK_PACKET 256+213 /* Miscellaneous keys */
#endif

#define OK_NOMODMAX 511
#define OK_SHIFT 512        /* Any Shift modifier, 0x0200 */
#define OK_CTRL 1024        /* Any Ctrl modifier in *nix, Left Ctrl in Windows, 0x0400 */
#define OK_ALT 2048         /* Any Alt modifier, 0x0800 */
#define OK_META 4096        /* Any Meta modifier in *nix, Enhanced Key in Windows, 0x1000 */

#ifdef WINDOWS
#define OK_LWIN 8192        /* Left Windows key, 0x2000 */
#define OK_RWIN 16384       /* Right Windows key, 0x4000 */
#define OK_AMENU 32768      /* Menu key, 0x8000 */
#define OK_ALTGR 65536      /* Alt Gr key, 0x010000 */
#define OK_RCTRL 131072     /* Right Ctrl key, 0x020000 */
#define OK_NLOCKON   262144 /* Numlock is on, 0x040000 */
#define OK_CLOCKON   524288 /* Caps Lock is on, 0x080000 */
#define OK_SLOCKON  1048576 /* Scroll lock is on, 0x100000 */

#define OK_CANCEL ((OK_CTRL) | (OK_PAUSE)) /* Ctrl+Break */
#define OK_HANGUEL OK_HANGUL

/* English language layouts */
#define OK_OEM1 OK_SEMICOLON
#define OK_OEM2 OK_FSLASH
#define OK_OEM3 OK_GRAVE
#define OK_OEM4 OK_OPENSQBRACKET
#ifdef __UK__
#define OK_OEM5 OK_HASH
#else
#define OK_OEM5 OK_BACKSLASH
#endif
#define OK_OEM6 OK_CLOSESQBRACKET
#define OK_OEM7 OK_APOSTROPHE
#define OK_OEM102 OK_BACKSLASH
#define OK_ADD OK_PLUS
#define OK_SUB OK_MINUS
#define OK_OEMPLUS OK_PLUS
#define OK_OEMCOMMA OK_COMMA
#define OK_OEMMINUS OK_MINUS
#define OK_PERIOD OK_FSTOP
#define OK_OEMPERIOD OK_FSTOP
#endif

#define OK_ALLMODS ~(OK_NOMODMAX)

#if (! defined ( WINDOWS ) ) && defined ( OTHER_OS )
#define OK_LETTERMODIFIERS ((OK_SHIFT) | (OK_CTRL) | (OK_META) | (OK_ALT) | (OK_ALTGR) | (OK_LWIN) | (OK_RWIN) | (OK_AMENU) | (OK_RCTRL) | (OK_CLOCKON))
#elif (! defined ( WINDOWS ) ) && ( ! defined ( OTHER_OS ) )
#define OK_LETTERMODIFIERS ((OK_SHIFT) | (OK_CTRL) | (OK_META) | (OK_ALT))
#else
#define OK_LETTERMODIFIERS ((OK_SHIFT) | (OK_CTRL) | (OK_ALT) | (OK_ALTGR) | (OK_LWIN) | (OK_RWIN) | (OK_AMENU) | (OK_RCTRL) | (OK_CLOCKON))
#endif

#ifdef WINDOWS
#define OK_LETTERINFOS ((OK_LETTERMODIFIERS) | (OK_NOMODMAX))
#define OK_CAPSSHIFTS ((OK_SHIFT) | (OK_CLOCKON))
#define OK_LETTERCMDMODIFIERS ((OK_LETTERMODIFIERS) & ~OK_CAPSSHIFTS & ~(OK_ALTGR))
#define OK_LETTERCMDMODIFIERINFOS (OK_LETTERCMDMODIFIERS | OK_NOMODMAX)
#define OK_SYMBOLCMDMODIFIERS ((OK_LETTERMODIFIERS) & ~(OK_SHIFT) & ~(OK_ALTGR))
#define OK_CTRLS ((OK_CTRL) | (OK_RCTRL))
#define OK_LETTERCMDNOCTRLMODIFIERS ((OK_LETTERCMDMODIFIERS) & ~OK_CTRLS)
#define OK_LETTERINFOSNOCTRLS (OK_LETTERINFOS & ~(OK_CTRLS))
#define OK_LETTERCMDMODIFIERINFOSNOCTRLS (OK_LETTERCMDMODIFIERINFOS & ~(OK_CTRLS))
#define OK_LETTERCMDMODIFIERINFOSNOCTRLSNOMETA (OK_LETTERCMDMODIFIERINFOSNOCTRLS & ~(OK_META))
#endif

#if (! defined ( WINDOWS ) ) && defined ( OTHER_OS )
#define OK_NUMPADMODIFIERS (OK_SHIFT) | (OK_CTRL) | (OK_META) | (OK_ALT) | (OK_ALTGR) | (OK_LWIN) | (OK_RWIN) | (OK_AMENU) | (OK_RCTRL) | (OK_NLOCKON)
#elif (! defined ( WINDOWS ) ) && ( ! defined ( OTHER_OS ) )
#define OK_NUMPADMODIFIERS (OK_SHIFT) | (OK_CTRL) | (OK_META) | (OK_ALT)
#else
#define OK_NUMPADMODIFIERS (OK_SHIFT) | (OK_CTRL) | (OK_ALT) | (OK_ALTGR) | (OK_LWIN) | (OK_RWIN) | (OK_AMENU) | (OK_RCTRL) | (OK_NLOCKON)
#endif

#ifdef WINDOWS
#define OK_NUMPADSHIFTS ((OK_SHIFT) | (OK_NLOCKON))
#define OK_NUMPADCMDMODIFIERS ((OK_LETTERMODIFIERS) & ~OK_NUMPADSHIFTS)
#define OK_LOCKS ((OK_CLOCKON) | (OK_NLOCKON) | (OK_SLOCKON))
#define OK_NOLOCKS ~OK_LOCKS
#endif

#define OK_UNK_1 -1
#define OK_UNK_2 -2
#define OK_UNK_3 -3
#define OK_UNK_4 -4
#define OK_UNK_5 -5
#define OK_UNK_6 -6
#define OK_UNK_7 -7
#define OK_UNK_8 -8

#ifndef STDOUT_FD
#define STDOUT_FD 1
#endif


#ifdef WINDOWS
#define CURCOL_BLUE 1
#define CURCOL_GREEN 2
#define CURCOL_RED 4
#define CURCOL_BRIGHT 8
#endif

#define TABSTACKSIZE 256

#define gotoxy(x,y) gotoansixy(x+1,y+1)
#define clearstring(astring, aslength) memset(astring, 0, aslength)
#define termbs() termbsn(1)
/* For compatibility with the original library, define a macro for 
   readline() as readqdline() */

#ifdef __cplusplus
extern "C" {
#endif

char *qdinpver();
void setmodsasfuncs();
void resetmodsasfuncs();
int getterm();
#ifdef WINDOWS
void SetCursorState(int CSize, BOOL Visible);
void SetCursorPos_(int x, int y);
void SetTextColour(int fg, int bg, int inverse);
int GetFgTextColour();
int GetBgTextColour();
int GetWinSize(int *width, int *height);
int GetCursorPos_(int *x, int *y);
WORD GetCursorAttribs();
void setcvars();
int keytranslate(WORD vkey, DWORD modkey, TCHAR keychar);
BOOL GetKeynWin(int *keyn, int *repeat);
#endif
void cls();
int qdgetch();
int regsiginthandler();
int deregsiginthandler();
void gotoansixy(int x, int y);
int getansicursorpos(int *rows, int *cols);
void pushtotabstack(char tabsnum);
char popfromtabstack();
void cleartabstack();
int writetab();
int termbsn(int n);
void writechar(char c);
void writestr(char *str);
int qdinstrch(char *targstring, char findchar, int startoffset);
int firstletter(char *cmdstring);
int getkeyn();
int readqdline(char *targetstring, char *templatestring, int eofiscancel);
int NEWreadqdline(char *targetstring, char *templatestring, int stringlen, int eofiscancel);
void setqdgetchmode(int amode); /* Dangerous function, only use if you know what you're doing! */
int keypause();
int yesnomsg(char *amsg);
int NEWyesnomsg( char *amsg, int eofiscancel);
void DoNothing();
int GiveOne();

#ifdef __cplusplus
}
#endif


#endif
