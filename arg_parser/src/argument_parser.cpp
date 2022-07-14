/*
Written by Gokhan Gunay
Contact: ghngunay@gmail.com
*/

#include "argument_parser.hpp"

#include <iostream>

Cparser::Cparser(const int argc, char ** const argv) {
    std::vector<std::string> v_string(argc + 1);
    for (auto ind = 0; ind < argc; ++ind) {
        v_string[ind] = argv[ind];
    }
    input(v_string);
}

Cparser::Cparser(const std::vector<std::string> v_string) {
    input(v_string);
}

/*
* @brief Imports input arguments and add to the argument pool.
*/
void Cparser::input(const std::vector<std::string> argv)
{
	const int argc = std::size(argv);
	constexpr char cmd_option_start = '-';
	bool key_found_lock{ false };
	std::string key;
	std::vector<std::string> vals;
	for (auto ind = 0; ind < argc; ++ind)
	{
		if (argv[ind][0] == cmd_option_start)
		{
			if (key_found_lock)
			{
				argMap_.insert(std::make_pair(key, vals));
			}
			key = std::string{ argv[ind] };
			vals = { "" };
			key_found_lock = true;
		}
		else if (key_found_lock)
		{
			if (argv[ind] != "")
			vals.emplace_back(argv[ind]);
		}
	}
	if (key_found_lock)
	{
		argMap_.insert(std::make_pair(key, vals));
	}
}

/*
* @brief Saves a key and corresponding possible input argument.
*/
void Cparser::save_key(const std::string key, const std::string in_arg, const std::string help)
{
	if (std::empty(key) || std::empty(in_arg))//If one of the arguments are invalid return without any action.
		return;
	correspondanceMap_.insert(std::make_pair(key, in_arg));
    helpMap_.insert(std::make_pair(correspondanceMap_[key], help));
}

/*
* @brief Retrieves translated input argument corresponding to the given key.
*/
auto Cparser::operator[](const std::string key) const noexcept-> ParserReturnType<std::string>
{
	return ParserReturnType<std::string>(find(key));
}

/*
* @brief Retrieves input argument corresponding to the given key.
*/
auto Cparser::find(const std::string& key) const noexcept -> std::vector<std::string>
{
	auto sub_find = [&]()
	{
		CorrespondanceMapType::const_iterator ret_val = correspondanceMap_.find(key);
		if (ret_val == std::end(correspondanceMap_))
		{
			return std::end(argMap_);
		}
		return argMap_.find(ret_val->second);
	};

	auto ret_val = sub_find();
	if (ret_val == std::end(argMap_))
		return std::vector<std::string>();
	return ret_val->second;
}

/*
* @brief Gets number of the saved keys.
*/
unsigned int Cparser::get_saved_key_num() const noexcept
{
	return std::size(correspondanceMap_);
}

/*
* @brief Parses all arguments.
*/
void Cparser::parse() {
    if (std::size(argMap_) == 0 || argMap_.count("--help") > 0 || argMap_.count("-h")) {
        print_help();
    }
}

void Cparser::print_help(){
    std::cout << "Help menu !!" << std::endl;
    for (auto& it : helpMap_) {
        std::cout << std::endl << it.first << " : " << it.second << std::endl;
    }
}