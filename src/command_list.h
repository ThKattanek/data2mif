#ifndef DATA2MIF_COMMANDS_H
#define DATA2MIF_COMMANDS_H

// definations all commandline parameters
#include "src/command_line_class.h"
enum CMD_COMMAND {CMD_HELP, CMD_VERSION, CMD_INPUTFILE, CMD_OUTPUTFILE, CMD_FORMAT, CMD_BIT_PER_LINE, CMD_HEX_SIZE};

static const CMD_STRUCT command_list[]{
	{CMD_HELP,"?","help","This text.",0},
	{CMD_VERSION,"","version","Show the current version number.",0},
	{CMD_INPUTFILE,"i","inputfile","Input Filename.",1},
	{CMD_OUTPUTFILE,"o","outputfile","Output Filename (MIF).",1},
	{CMD_FORMAT,"f","format","Output Format: 'bin' or 'hex' (default: 'hex').",1},
	{CMD_BIT_PER_LINE,"b","bitperline","Output bits per line when 'bin' format. (default: 8)",1},
	{CMD_HEX_SIZE,"h","hexsize","Output Hex size (4,8,12,16,...) when 'hex' format. (default: 16)",1}
};

#define command_list_count sizeof(command_list) / sizeof(command_list[0])

#endif // DATA2MIF_COMMANDS_H
