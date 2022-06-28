// Code by Thorsten Kattanek //
// A consol tool to create a mif (memory init file) for fpga and eeprom. //

#include <cstdio>
#include <iostream>
#include <fstream>


#include "./command_line_class.h"
#include "./command_list.h"

using namespace std;

int convert_file(string in_filename, string out_filename, int bits_per_line);

int main(int argc, char *argv[])
{
	CommandLineClass *cmd_line = new CommandLineClass(argc, argv, "data2mif", command_list, command_list_count);

	string in_filename;
	string out_filename;

	int bits_per_line = 4;

	if(cmd_line->GetCommandCount() < 0)
	{
		cout << "\"data2mif --help\" for more information." << endl;
		return(0x0);
	}

	if(cmd_line->GetCommandCount() == 0)
	{
		cout << "Arguments are required!" << endl;
		cout << "\"data2mif --help\" for more information." << endl;
		return (0x0);
	}

	if(cmd_line->GetCommandCount() > 0)
	{
		if(cmd_line->GetCommand(0) == CMD_HELP)
		{
			cmd_line->ShowHelp();
			return(0x0);
		}

		if(cmd_line->GetCommand(0) == CMD_VERSION)
		{
			cout << "Version: " << VERSION_STRING << endl << endl;
			return(0x0);
		}

		for(int i=0; i < cmd_line->GetCommandCount(); i++)
		{
			if(cmd_line->GetCommand(i) == CMD_INPUTFILE)
				in_filename = cmd_line->GetArg(i+1);

			if(cmd_line->GetCommand(i) == CMD_OUTPUTFILE)
				out_filename = cmd_line->GetArg(i+1);

			if(cmd_line->GetCommand(i) == CMD_BIT_PER_LINE)
			{
				bool err;
				bits_per_line = cmd_line->GetArgInt(i+1, &err);
				if(err)
					return(0x0);
				if(bits_per_line < 1)
				{
					cout << "'Bits per line' must greather as 0!" << endl;
					return(0x0);
				}
			}
		}
	}

	if (in_filename == "" || out_filename == "")
	{
		cout << "In- and Outputfile are required." << endl;
		return (-1);
	}

	convert_file(in_filename, out_filename, bits_per_line);

	return (0);
}

int convert_file(string in_filename, string out_filename, int bits_per_line)
{
	FILE *in_file = NULL;

	fstream in_stream(in_filename.c_str(), ios::binary | ios::in);
	fstream out_stream(out_filename.c_str(), ios::out);

	if(!in_stream.is_open())
	{
		cout << "Could not open Input File." << endl;
		return -1;
	}

	if(!out_stream.is_open())
	{
		cout << "Could not open Output File." << endl;
		return -1;
	}


	////////////////////////////////////////////////////////

	int bit_counter = 0;

	uint8_t in;

	while (!in_stream.eof())
	{
		in = in_stream.get();
		uint8_t mask = 0b10000000;
		for(int i=0; i<8; i++)
		{
			if(in & mask)
				out_stream << "1";
			else
				out_stream << "0";

			bit_counter++;
			if(bit_counter == bits_per_line)
			{
				bit_counter = 0;
				out_stream << endl;
			}

			mask >>= 1;
		}
	}


	////////////////////////////////////////////////////////

	in_stream.close();
	out_stream.close();

	return 0;
}
