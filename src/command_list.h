#ifndef DATA2MIF_COMMANDS_H
#define DATA2MIF_COMMANDS_H

// Defineren aller Kommandozeilen Parameter
#include "src/command_line_class.h"
enum CMD_COMMAND {CMD_HELP, CMD_VERSION, CMD_INPUTFILE, CMD_OUTPUTFILE, CMD_BIT_PER_LINE};

static const CMD_STRUCT command_list[]{
	{CMD_HELP,"?","help","This text.",0},
	{CMD_VERSION,"","version","Show the current version number.",0},
	{CMD_INPUTFILE,"i","inputfile","Input Filename.",1},
	{CMD_OUTPUTFILE,"o","outputfile","Output Filename (MIF).",1},
	{CMD_BIT_PER_LINE,"b","bitperline","Output bits per line in the mif file. (default: 4)",1}
};

#define command_list_count sizeof(command_list) / sizeof(command_list[0])

#endif // DATA2MIF_COMMANDS_H
