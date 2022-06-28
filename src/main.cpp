// Code by Thorsten Kattanek //
// A consol tool to create a mif (memory init file) for fpga and eeprom. //

#include <iostream>
#include <fstream>

#include "./command_line_class.h"
#include "./command_list.h"

using namespace std;

int main(int argc, char *argv[])
{
	CommandLineClass *cmd_line = new CommandLineClass(argc, argv, "data2mif", command_list, command_list_count);

	if(cmd_line->GetCommandCount() < 0)
	{
		printf("\"data2mif --help\" for more information.\n");
		return(-1);
	}

	if(cmd_line->GetCommandCount() > 0)
	{
		for(int i=0; i < cmd_line->GetCommandCount(); i++)
		{

		if(cmd_line->GetCommand(0) == CMD_HELP)
		{
			cmd_line->ShowHelp();
			return(0x0);
		}

		if(cmd_line->GetCommand(0) == CMD_VERSION)
		{
			printf("Version: %s\n\n",VERSION_STRING);
			return(0x0);
		}
		}
	}

	return (0);
}
