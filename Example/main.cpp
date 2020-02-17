/*
Written by Gokhan Gunay
Contact: ghngunay@gmail.com
*/
#include <iostream>
#include "ArgumentParser.hpp"

template<typename T>
void prnt(T& in, const std::string first_message)
{
	std::cout << first_message;
	for (auto& item : in)
	{
		std::cout << item << " ";
	}
	std::cout << std::endl;
}

int main(int argc,char * argv[])
{
	Cparser parser(argc, argv);
	parser.save_key("in_file", "-in");
	parser.save_key("out_file", "-out");
	parser.save_key("param1", "-p1");
	parser.save_key("param2", "-p2");
	std::cout << "With " << parser.get_saved_key_num() << " saved keys."<<std::endl;

	prnt(parser["in_file"].get_as_string(), "-in arguments: ");
	prnt(parser["out_file"].get_as_string(), "-out arguments: ");
	prnt(parser["param1"].get_as_float(), "-p1 arguments: ");
	prnt(parser["param1"].get_as_double(), "-p1 arguments: ");
	prnt(parser["param2"].get_as_integer(), "-p2 arguments: ");
	return 0;
}
