#ifndef ANSI_H
#define ANSI_H

// ANSI/VT100 Terminal Control Escape Sequences
// taken from http://www.termsys.demon.co.uk/vtansi.htm 
//
#define  ANSI_RESET             "\033[2;37;0m"
#define  ANSI_CURSOR_OFF        "\033[?25l"
#define  ANSI_CURSOR_ON         "\033[?25h"

#define  ANSI_CLEAR             "\033[2J"
#define  ANSI_ERASE_EOL         "\033[K"
#define  ANSI_ERASE_SOL         "\033[1K"
#define  ANSI_ERASE_LINE        "\033[2K"
#define  ANSI_ERASE_DOWN        "\033[J"
#define  ANSI_ERASE_UP          "\033[1J"

#define  ANSI_DEL               "\033[P"
#define  ANSI_DELn(n)           "\033[" #n "P"

#define  ANSI_HOME              "\033[H"
#define  ANSI_SCROLL_UP         "\033M"
#define  ANSI_FREEZE(top, btm)  "\033[" #top ";" #btm "r"
#define  ANSI_UNFREEZE          "\033[r"
#define  ANSI_GOTO(x, y)        "\033[" #y ";" #x "H"

#define  ANSI_UP                "\033[A"
#define  ANSI_DOWN              "\033[B"
#define  ANSI_RIGHT             "\033[C"
#define  ANSI_LEFT              "\033[D"

#define  ANSI_UPn(n)            "\033[" #n "A"
#define  ANSI_DOWNn(n)          "\033[" #n "B"
#define  ANSI_RIGHTn(n)         "\033[" #n "C"
#define  ANSI_LEFTn(n)          "\033[" #n "D"

#define  ANSI_SAVE_CURSOR       "\033[s"
#define  ANSI_RESTORE_CURSOR    "\033[u"
#define  ANSI_SAVE_ALL          "\033[7"
#define  ANSI_RESTORE_ALL       "\033[8"

#define  ANSI_ENABLE_INSERT     "\033[4h"
#define  ANSI_DISABLE_INSERT    "\033[4l"

#define  ANSI_ENABLE_ECHO       "\033[12l"
#define  ANSI_DISABLE_ECHO      "\033[12h"

#define  ANSI_NORMAL            "\033[0m"
#define  ANSI_BOLD              "\033[1m"
#define  ANSI_ITALICS           "\033[3m"
#define  ANSI_UNDERLINE         "\033[4m"
#define  ANSI_BLINK             "\033[5m"
#define  ANSI_INVERSE           "\033[7m"
#define  ANSI_STRIKE            "\033[9m"
#define  ANSI_BOLD_OFF          "\033[22m"
#define  ANSI_ITALICS_OFF       "\033[23m"
#define  ANSI_UNDERLINE_OFF     "\033[24m"
#define  ANSI_BLINK_OFF         "\033[25m"
#define  ANSI_INVERSE_OFF       "\033[27m"
#define  ANSI_STRIKE_OFF        "\033[29m"

#define  ANSI_FG_BLACK          "\033[0;30m"
#define  ANSI_FG_RED            "\033[0;31m"
#define  ANSI_FG_GREEN          "\033[0;32m"
#define  ANSI_FG_ORANGE         "\033[0;33m"
#define  ANSI_FG_BLUE           "\033[0;34m"
#define  ANSI_FG_MAGENTA        "\033[0;35m"
#define  ANSI_FG_CYAN           "\033[0;36m"
#define  ANSI_FG_GRAY           "\033[0;37m"
#define  ANSI_FG_DEFAULT        "\033[0;39m" 

#define  ANSI_FG_DKGRAY         "\033[1;30m"
#define  ANSI_FG_LTRED          "\033[1;31m"
#define  ANSI_FG_LTGREEN        "\033[1;32m"
#define  ANSI_FG_YELLOW         "\033[1;33m"
#define  ANSI_FG_LTBLUE         "\033[1;34m"
#define  ANSI_FG_LTMAGENTA      "\033[1;35m"
#define  ANSI_FG_LTCYAN         "\033[1;36m"
#define  ANSI_FG_WHITE          "\033[1;37m"

#define  ANSI_BG_BLACK          "\033[0;40m"
#define  ANSI_BG_RED            "\033[0;41m"
#define  ANSI_BG_GREEN          "\033[0;42m"
#define  ANSI_BG_ORANGE         "\033[0;43m"
#define  ANSI_BG_BLUE           "\033[0;44m"
#define  ANSI_BG_MAGENTA        "\033[0;45m"
#define  ANSI_BG_CYAN           "\033[0;46m"
#define  ANSI_BG_GRAY           "\033[0;47m"
#define  ANSI_BG_DEFAULT        "\033[0;49m"

#define  ANSI_BG_DKGRAY         "\033[1;40m"
#define  ANSI_BG_LTRED          "\033[1;41m"
#define  ANSI_BG_LTGREEN        "\033[1;42m"
#define  ANSI_BG_YELLOW         "\033[1;43m"
#define  ANSI_BG_LTBLUE         "\033[1;44m"
#define  ANSI_BG_LTMAGENTA      "\033[1;45m"
#define  ANSI_BG_LTCYAN         "\033[1;46m"
#define  ANSI_BG_WHITE          "\033[1;47m"

#endif
