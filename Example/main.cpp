/*
Written by Gokhan Gunay
Contact: ghngunay@gmail.com
*/
#include <iostream>  // I/O 
#include "../ArgumentParser.hpp"

using namespace std;


int main(int argc,char * argv[])
{
	cparser parser(argc, argv);
	parser.save_keys("in_file", "-in");
	parser.save_keys("out_file", "-out");
	parser.save_keys("param1", "-p1");
	parser.save_keys("param2", "-p2");
	cout << "With " << parser.get_saved_key_num() << " saved keys\n";
	cout << "\n";
	cout << parser["in_file"];
	cout << "\n";
	cout << parser["out_file"];
	cout << "\n";
	cout << parser["param1"];
	cout << "\n";
	cout << parser["param2"];
}
