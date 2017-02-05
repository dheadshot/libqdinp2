#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>

#include "qdinpm.h"

/*
Key Formats:
Key Name	Key Value	Description (if needed)
---------------------------------------------------------
OK_ESC 		256+0		Escape (2 consecutive is returned as 1)
OK_F0 		256+1		Function Keys...
OK_F1 		256+2
OK_F2 		256+3
OK_F3 		256+4
OK_F4 		256+5
OK_F5 		256+6
OK_F6 		256+7
OK_F7 		256+8
OK_F8	 	256+9
OK_F9 		256+10
OK_F10 		256+11
OK_F11 		256+12
OK_F12 		256+13
OK_F13 		256+14
OK_F14 		256+15
OK_F15 		256+16
OK_F16 		256+17
OK_F17 		256+18
OK_F18 		256+19
OK_F19 		256+20
OK_F20 		256+21
OK_PS 		256+22		Print Screen
OK_SLOCK 	256+23		Scroll Lock
OK_PAUSE 	256+24		Pause/Break
OK_BS 		256+25		Backspace
OK_INS 		256+26		Insert
OK_HOME 	256+27
OK_PGUP 	256+28		Page Up
OK_NLOCK 	256+29		Num Lock
OK_NDIV 	256+30		Numpad /
OK_NMUL 	256+31		Numpad *
OK_NSUB 	256+32		Numpad -
OK_HT 		256+33		Tab
OK_RHT 		256+34		Reverse Tab (?)
OK_DEL 		256+35		Delete
OK_END 		256+36
OK_PGDOWN 	256+37		Page Down
OK_NADD 	256+38		Numpad +
OK_CLOCK 	256+39		Caps Lock
OK_NENTER 	256+40		Numpad Enter
OK_NDEL 	256+41		Numpad .
OK_N0 		256+42		Numpad 0
OK_N1 		256+43		Numpad 1
OK_N2 		256+44		Numpad 2
OK_N3 		256+45		Numpad 3
OK_N4 		256+46		Numpad 4
OK_N5 		256+47		Numpad 5
OK_N6 		256+48		Numpad 6
OK_N7 		256+49		Numpad 7
OK_N8 		256+50		Numpad 8
OK_N9 		256+51		Numpad 9
OK_UP 		256+52
OK_LEFT 	256+53
OK_DOWN 	256+54
OK_RIGHT 	256+55
OK_NSP 		256+56		Numpad Space
OK_NHT 		256+57		Numpad Tab
OK_PF1 		256+58		P Function Keys...
OK_PF2 		256+59
OK_PF3 		256+60
OK_PF4 		256+61
OK_NCOMMA 	256+62		Numpad ,
OK_NEQ 		256+63		Numpad =
OK_BLUE 	256+64		Colour Keys...
OK_RED 		256+65
OK_GREY 	256+66
OK_GRAY 	256+66
OK_WHITE 	256+67
OK_QF1 		256+68		QDOS Function Keys...
OK_QF2 		256+69
OK_QF3 		256+70
OK_QF4 		256+71
OK_QF5 		256+72
OK_CLEAR 	256+73
OK_FIND 	256+74
OK_SELECT 	256+75
OK_HELP 	256+76
OK_EHV 		256+77		?
OK_EHF 		256+78
OK_EHB 		256+79
OK_EHR 		256+80
OK_EHU 		256+81
OK_ECV 		256+82
OK_ECF 		256+83
OK_ECB 		256+84		? (Don't remember what this was)
OK_ECR 		256+85
OK_ECP 		256+86
OK_ECG 		256+87
OK_ECT 		256+88
OK_ECY 		256+89
OK_ECN 		256+90
OK_ENL 		256+91		Escaped New Line

OK_F21 		256+92		Extended Function Keys...
OK_F22 		256+93
OK_F23 		256+94
OK_F24 		256+95
OK_F25 		256+96
OK_F26 		256+97
OK_F27 		256+98
OK_F28 		256+99
OK_F29 		256+100
OK_F30 		256+101
OK_F31 		256+102
OK_F32 		256+103
OK_F33 		256+104
OK_F34 		256+105
OK_F35 		256+106
OK_F36 		256+107
OK_F37 		256+108
OK_F38 		256+109
OK_F39 		256+110
OK_F40 		256+111
OK_F41 		256+112
OK_F42 		256+113
OK_F43 		256+114
OK_F44 		256+115
OK_F45 		256+116
OK_F46 		256+117
OK_F47 		256+118
OK_F48 		256+119

OK_IND 		256+128		Escape Sequence Definitions...
OK_NEL 		256+129
OK_HTS 		256+130
OK_RI 		256+131
OK_SS2 		256+132
OK_OSC 		256+133
OK_APC 		256+134
OK_DCS 		256+135
OK_SPA 		256+136
OK_EPA 		256+137
OK_SOS 		256+138
OK_DECID 	256+139
OK_ST 		256+140
OK_PM 		256+141

OK_NOMODMAX	511		(Maximum unmodified key number)
OK_SHIFT 	512		Shift Modifier
OK_CTRL 	1024		Ctrl Modifier
OK_ALT 		2048		Alt Modifier
OK_META 	4096		Meta Modifier

OK_UNK_1	-1		Unknown Key
OK_UNK_2 	-2		Unknown 2 Key Sequence
OK_UNK_3 	-3		Unknown 3 Key Sequence
OK_UNK_4 	-4		Unknown 4 Key Sequence
OK_UNK_5 	-5		Unknown 5 Key Sequence
OK_UNK_6 	-6		Unknown 6 Key Sequence
OK_UNK_7 	-7		Unknown 7 Key Sequence
OK_UNK_8 	-8		Unknown 8 Key Sequence
*/


char qdinplibver[] = "0.02.00";

char termtype[256] = "";
int modsasfuncs = 0; /* Interpret function key modifiers as additional function keys? */
int exitreadqdline = 0; /* Exit the readqdline function? */


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


int qdgetch()
{
  struct termios oldt, newt;
  int ch;
  
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}


void readqdlinehandle_sigint(int sig)
{
  exitreadqdline = 1;
  regsiginthandler();
}


int regsiginthandler()
{
  if (signal(SIGINT,readqdlinehandle_sigint) == SIG_ERR) return -1;
  return 0;
}


int deregsiginthandler()
{
  if (signal(SIGINT, SIG_DFL) == SIG_ERR) return -1;
  return 0;
}


int termbsn(int n)
{
  /* Backspaces on screen a given number of times
     Returns the amount backspaced. */
  int i;
  for (i = 0; i < n; i++)
  {
    if ((strcmp(termtype,"vt52")==0) || (strcmp(termtype,"VT52")==0))
    {
      printf("\033D \033D");
    }
    else if ((strcmp(termtype,"Tektronix 4014")==0) || (strcmp(termtype,"T4014")==0))
    {
      printf("\008 \008");
    }
    else
    {
      printf("\033[1D \033[1D");
    }
  }
  return i;
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
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0)) return OK_ECN;
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
            if ((strcmp(termtype,"vt52")==0) || (strcmp(termtype,"VT52")==0)) return OK_PF1;
            /* ECP */
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0)) return OK_ECP;
            /* DCS */
            if ((memcmp(termtype,"vt",2)==0) || (memcmp(termtype,"VT",2)==0)) return OK_DCS;
          case (96+16):
            /* ESC P - INS On*/
            return OK_BLUE;
          break;
          
          case (64+17):
            if ((strcmp(termtype,"vt52")==0) || (strcmp(termtype,"VT52")==0)) return OK_PF2;
          case (96+17):
            /* ESC Q - INS Off */
            return OK_RED;
          break;
          
          case (64+18):
            if ((strcmp(termtype,"vt52")==0) || (strcmp(termtype,"VT52")==0)) return OK_PF3;
            /* ECR */
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0)) return OK_ECR;
          case (96+18):
            /* ESC R */
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0)) return OK_EHR;
            return OK_GREY;
          break;
          
          case (64+19):
            if ((strcmp(termtype,"vt52")==0) || (strcmp(termtype,"VT52")==0)) return OK_PF4;
          case (96+19):
            /* ESC S */
            return OK_QF1;
          break;
          
          case (64+20):
            /* ECT */
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0)) return OK_ECT;
          case (96+20):
            /* ESC T - write 'til char */
            return OK_QF2;
          break;
          
          case (96+21):
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0)) return OK_EHU;
          case (64+21):
            /* ESC U */
            return OK_QF3;
          break;
          
          case (64+22):
            /* ECV */
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0)) return OK_ECV;
            /* SPA */
            if ((memcmp(termtype,"vt",2)==0) || (memcmp(termtype,"VT",2)==0)) return OK_SPA;
          case (96+22):
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0)) return OK_EHV;
            /* ESC V */
            return OK_QF4;
          break;
          
          case (64+23):
            /* EPA */
            if ((memcmp(termtype,"vt",2)==0) || (memcmp(termtype,"VT",2)==0)) return OK_EPA;
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
                                if (e7ch==126) return (OK_F0 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F0 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F0 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F0 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F0 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F0 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F0 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F0 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F1 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F1 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F1 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F1 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F1 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F1 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F1 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F1 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F2 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F2 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F2 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F2 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F2 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F2 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F2 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F2 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F3 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F3 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F3 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F3 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F3 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F3 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F3 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F3 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F4 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F4 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F4 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F4 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F4 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F4 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F4 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F4 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F5 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F5 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F5 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F5 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F5 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F5 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F5 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F5 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F6 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F6 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F6 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F6 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F6 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F6 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F6 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F6 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F7 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F7 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F7 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F7 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F7 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F7 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F7 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F7 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F8 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F8 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F8 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F8 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F8 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F8 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F8 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F8 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                    if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0) || (strcmp(termtype,"vt102")==0) || (strcmp(termtype,"VT102")==0)) return OK_FIND;
                    else return OK_HOME;
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
                                if (e7ch==126) return (OK_F9 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F9 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F9 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F9 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F9 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F9 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F9 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F9 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F10 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F10 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F10 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F10 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F10 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F10 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F10 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F10 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F11 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F11 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F11 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F11 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F11 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F11 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F11 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F11 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F12 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F12 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F12 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F12 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F12 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F12 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F12 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F12 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F13 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F13 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F13 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F13 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F13 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F13 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F13 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F13 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F14 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F14 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F14 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F14 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F14 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F14 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F14 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F14 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                        if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0) || (strcmp(termtype,"vt102")==0) || (strcmp(termtype,"VT102")==0)) return OK_HELP;
                        else return OK_F15;
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
                                if (e7ch==126) return (OK_F15 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F15 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F15 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F15 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F15 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F15 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F15 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F15 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F16 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F16 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F16 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F16 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F16 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F16 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F16 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F16 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F17 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F17 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F17 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F17 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F17 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F17 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F17 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F17 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F18 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F18 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F18 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F18 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F18 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F18 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F18 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F18 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F19 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F19 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F19 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F19 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F19 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F19 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F19 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F19 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                                if (e7ch==126) return (OK_F20 | OK_META | OK_SHIFT);
                                return OK_UNK_8;
                              break;
                              
                              case '1':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F20 | OK_META | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '2':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F20 | OK_META | OK_SHIFT | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '3':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F20 | OK_META | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '4':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F20 | OK_META | OK_SHIFT | OK_CTRL);
                                return OK_UNK_8;
                              break;
                              
                              case '5':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F20 | OK_META | OK_CTRL | OK_ALT);
                                return OK_UNK_8;
                              break;
                              
                              case '6':
                                e7ch = qdgetch();
                                if (e7ch==126) return (OK_F20 | OK_META | OK_SHIFT | OK_CTRL | OK_ALT);
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
                            if (e6ch==126) return (OK_F20 | OK_SHIFT | OK_ALT | OK_CTRL);
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
                    if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0) || (strcmp(termtype,"vt102")==0) || (strcmp(termtype,"VT102")==0)) return OK_SELECT;
                    else return OK_END;
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
                    if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0) || (strcmp(termtype,"vt102")==0) || (strcmp(termtype,"VT102")==0)) return OK_RHT;
                    else return OK_PGUP;
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
                    if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0) || (strcmp(termtype,"vt102")==0) || (strcmp(termtype,"VT102")==0)) return OK_CLEAR;
                    else return OK_PGDOWN;
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
                return OK_N5;
              break;
              
              case 'H':
                return OK_HOME;
              break;
              
              case 'P':
                return OK_PAUSE;
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
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0))  return OK_F9;
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
            if ((strcmp(termtype,"vt100")==0) || (strcmp(termtype,"VT100")==0)) return OK_F18;
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
          if ((memcmp(termtype,"vt",2)==0) || (memcmp(termtype,"VT",2)==0)) return OK_DCS;
          return ch;
        }
        else if (ch == 0x96)
        {
          if ((memcmp(termtype,"vt",2)==0) || (memcmp(termtype,"VT",2)==0)) return OK_SPA;
          return ch;
        }
        else if (ch == 0x97)
        {
          if ((memcmp(termtype,"vt",2)==0) || (memcmp(termtype,"VT",2)==0)) return OK_EPA;
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
}


int readqdline(char *targetstring, char *templatestring, int eofiscancel)
{
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
  exitreadqdline = 0;
  if (eofiscancel == 0)
  {
    if (regsiginthandler()==-1) return -1;
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
       strcpy(theline,"\0");
       tlpos=0;
       itpos=0;
       insmode = 0;
       printf("@\n");
     break;
     
     case OK_QF1:
     case OK_F1:
     case OK_PF1:
       /* ESC S, F1 */
       if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); else
       if (itemplate[itpos]==4) printf("\033[7mD\033[27m"); else
       printf("%c",itemplate[itpos]);
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
           if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); else
           if (itemplate[itpos]==4) printf("\033[7mD\033[27m"); else
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
           if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); else
           if (itemplate[itpos]==4) printf("\033[7mD\033[27m"); else
           printf("%c",itemplate[itpos]);
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
         termbsn(1);
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
         printf("%c",9);
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
         theline[tlpos]=12;
         tlpos++;
         if ((itpos < 255) && (insmode == 0)) itpos++;
       }
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
  strcpy(targetstring, theline);
  if (eofiscancel == 0) deregsiginthandler();
  else if (theline[0] == 4) return 4;
  return retcond;
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
  exitreadqdline = 0;
  if (eofiscancel == 0)
  {
    if (regsiginthandler()==-1)
    {
      free(itemplate);
      return -1;
    }
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
       memset(itemplate,0,stringlen);
       strcpy(itemplate,targetstring);
       memset(targetstring,0,stringlen);
       strcpy(targetstring,"\x00");
       tlpos=0;
       itpos=0;
       insmode = 0;
       printf("@\n");
     break;
     
     case OK_QF1:
     case OK_F1:
     case OK_PF1:
       /* ESC S, F1 */
       if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); else
       if (itemplate[itpos]==4) printf("\033[7mD\033[27m"); else
       printf("%c",itemplate[itpos]);
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
           if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); else
           if (itemplate[itpos]==4) printf("\033[7mD\033[27m"); else
           printf("%c",itemplate[itpos]);
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
           if (itemplate[itpos]==12) printf("\033[7mL\033[27m"); else
           if (itemplate[itpos]==4) printf("\033[7mD\033[27m"); else
           printf("%c",itemplate[itpos]);
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
     case 127:
       /* DEL (NumDEL = ESC On) */
       if (tlpos>0)
       {
         termbsn(1);
         tlpos--;
         if ((targetstring[tlpos]==12) || (targetstring[tlpos]==4)) termbsn(1);
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
       printf("\033[7mL\033[27m");
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
     
     case OK_NENTER:
       ch = 10;
     case 13:
     case 10:
       /* CRLF */
       if (tlpos < stringlen-1)
        {
          printf("\n");
          targetstring[tlpos]=ch;
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
         printf("%c",9);
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
         printf("\033[7mD\033[27m");
         targetstring[tlpos]=12;
         tlpos++;
         if ((itpos < stringlen-1) && (insmode == 0)) itpos++;
       }
     break;
            
     default:
       if ((tlpos < stringlen-1) && (ch<256) && (ch >= 32))
       {
         printf("%c",ch);
         if ((itpos < stringlen-1) && (insmode == 0)) itpos++;
         targetstring[tlpos]=ch;
         tlpos++;
       }
     break;
   }
  }
  retcond = 3;
ReturnPt:
  free(itemplate);
  if (eofiscancel == 0) deregsiginthandler();
  else if (targetstring[0] == 4) return 4;
  return retcond;
}




int keypause()
{
  int tempi=0;
  printf("[Press a key to continue...]\n");
  tempi = getkeyn();
  printf("\033[1A");
  printf("                               \n");
  printf("\033[1A");
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


