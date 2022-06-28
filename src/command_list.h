#ifndef DATA2MIF_COMMANDS_H
#define DATA2MIF_COMMANDS_H

// Defineren aller Kommandozeilen Parameter
enum CMD_COMMAND {CMD_HELP,CMD_VERSION};

static const CMD_STRUCT command_list[]{
	{CMD_HELP,"?","help","This text.",0},
	{CMD_VERSION,"","version","Show the current version number.",0}
};

#define command_list_count sizeof(command_list) / sizeof(command_list[0])

#endif // DATA2MIF_COMMANDS_H
