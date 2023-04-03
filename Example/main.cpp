/*********************
* Copyright [2018] Written by Gokhan Gunay
* Feel free to modify, distribute and whatever you want to do.
* The author cannot be held responsible for the failure/damage
* any user sustains using this library.
* Contact: ghngunay@gmail.com
**********************/

#include <iostream>
#include "argument_parser.hpp"

template<typename T>
void prnt(const T& in, const std::string first_message) {
    std::cout << first_message;
    for (auto& item : in) std::cout << item << " ";
    std::cout << std::endl;
}

int main(int argc, char * argv[])
{
    Cparser parser(argc, argv);
    parser.save_key("in_file", "-in", "Input");
    parser.save_key("out_file", "-out", "Output");
    parser.save_key("param1", "-p1", "Parameter 1");
    parser.save_key("param2", "-p2", "Parameter 2");
    parser.save_key("param3", "-p3", "7.7", "Parameter 3");

    parser.set_epilog(
                    "Copyright [2018] Written by Gokhan Gunay\n"
                    "Feel free to modify, distribute and whatever you want to do.\n"
                    "The author cannot be held responsible for the failure/damage\n"
                    "any user sustains using this library.\n"
                    "Contact: ghngunay@gmail.com\n");
    parser.parse();
    std::cout << "With " << parser.get_saved_key_num() << " saved keys." << std::endl;
    prnt(parser["in_file"].get_as_string(), "-in arguments: ");
    prnt(parser["out_file"].get_as_string(), "-out arguments: ");
    prnt(parser["param1"].get_as_float(), "-p1 arguments: ");
    prnt(parser["param1"].get_as_double(), "-p1 arguments: ");
    prnt(parser["param2"].get_as_integer(), "-p2 arguments: ");
    prnt(parser["param3"].get_as_float(), "-p3 arguments (from default val): ");
    return 0;
}
