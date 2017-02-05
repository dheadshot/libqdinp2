#ifndef __INC_QDINPM_H__
#define __INC_QDINPM_H__ 1

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

#define OK_NOMODMAX 511
#define OK_SHIFT 512
#define OK_CTRL 1024
#define OK_ALT 2048
#define OK_META 4096

#define OK_UNK_1 -1
#define OK_UNK_2 -2
#define OK_UNK_3 -3
#define OK_UNK_4 -4
#define OK_UNK_5 -5
#define OK_UNK_6 -6
#define OK_UNK_7 -7
#define OK_UNK_8 -8


#define clearstring(astring, aslength) memset(astring, 0, aslength)
#define termbs() termbsn(1)
/* For compatibility with the original library, define a macro for 
   readline() as readqdline() */

char *qdinpver();
void setmodsasfuncs();
void resetmodsasfuncs();
int getterm();
int qdgetch();
int regsiginthandler();
int deregsiginthandler();
int termbsn(int n);
int qdinstrch(char *targstring, char findchar, int startoffset);
int firstletter(char *cmdstring);
int getkeyn();
int readqdline(char *targetstring, char *templatestring, int eofiscancel);
int NEWreadqdline(char *targetstring, char *templatestring, int stringlen, int eofiscancel);
int keypause();
int yesnomsg(char *amsg);


#endif
