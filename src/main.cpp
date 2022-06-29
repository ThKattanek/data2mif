// Code by Thorsten Kattanek //
// A consol tool to create a mif (memory init file) for fpga and eeprom. //

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


#include "./command_line_class.h"
#include "./command_list.h"

using namespace std;

int convert_file(string in_filename, string out_filename, int format, int bits_per_line, int hex_size);

enum formats {FORMAT_BIN, FORMAT_HEX};

bool compareChar(char & c1, char & c2);
bool compareChar(char & c1, char & c2)
{
	if (c1 == c2)
		return true;
	else if (std::toupper(c1) == std::toupper(c2))
		return true;
	return false;
}

bool caseInSensStringCompare(std::string & str1, std::string &str2);
bool caseInSensStringCompare(std::string & str1, std::string &str2)
{
	return ( (str1.size() == str2.size() ) &&
			 std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar) );
}

int main(int argc, char *argv[])
{
	CommandLineClass *cmd_line = new CommandLineClass(argc, argv, "data2mif", command_list, command_list_count);

	string in_filename;
	string out_filename;

	int format = FORMAT_HEX;
	int bits_per_line = 8;
	int hex_size = 16;

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

			if(cmd_line->GetCommand(i) == CMD_FORMAT)
			{
				string format_str = cmd_line->GetArg(i+1);
				string cmp = "hex";
				if(caseInSensStringCompare(format_str, cmp))
				format = FORMAT_HEX;

				cmp = "bin";
				if(caseInSensStringCompare(format_str, cmp))
				format = FORMAT_BIN;
			}

			if(cmd_line->GetCommand(i) == CMD_HEX_SIZE)
			{
				bool err;
				int hex_size_tmp = cmd_line->GetArgInt(i+1, &err);
				if(err)
					return(0x0);

				if(((hex_size_tmp % 4) != 0) || (hex_size_tmp < 4))
				{
					cout << "Hex Size must 4,8,12,16,..." << endl;
					return(0x0);
				}
				else
					hex_size = hex_size_tmp;
			}

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

	convert_file(in_filename, out_filename, format, bits_per_line, hex_size);

	return (0);
}

int convert_file(string in_filename, string out_filename, int format, int bits_per_line, int hex_size)
{
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
	/// export as bin

	if(format == FORMAT_BIN)
	{
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
	}


	////////////////////////////////////////////////////////
	/// export as hex

	const char hex_tbl[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

	if(format == FORMAT_HEX)
	{
		int hex_counter = 0;

		uint8_t in;

		while (!in_stream.eof())
		{
			in = in_stream.get();
			for(int i=0; i<2; i++)
			{
				out_stream << hex_tbl[(in >> 4*(1-i)) & 0x0f];
				hex_counter++;
				if(hex_counter == hex_size/4)
				{
					hex_counter = 0;
					out_stream << endl;
				}
			}
		}
	}

	in_stream.close();
	out_stream.close();

	return 0;
}
