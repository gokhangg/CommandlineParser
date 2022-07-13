/*
Written by Gokhan Gunay
Contact: ghngunay@gmail.com
*/

#include "argument_parser.hpp"


Cparser::Cparser(const int argc, char ** const argv) {
    std::vector<std::string> v_string(argc);
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
				m_arg_map.insert(std::make_pair(key, vals));
			}
			key = std::string{ argv[ind] };
			vals = { std::string("") };
			key_found_lock = true;
		}
		else if (key_found_lock)
		{
			vals.emplace_back(std::string(argv[ind]));
		}
	}
	if (key_found_lock)
	{
		m_arg_map.insert(std::make_pair(key, vals));
	}
}

/*
* @brief Saves a key and corresponding possible input argument.
*/
void Cparser::save_key(const std::string key, const std::string in_arg)
{
	if (std::empty(key) || std::empty(in_arg))//If one of the arguments are invalid return without any action.
		return;
	m_correspondance_map.insert(std::make_pair(key, in_arg));
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
		CorrespondanceMapType::const_iterator ret_val = m_correspondance_map.find(key);
		if (ret_val == std::end(m_correspondance_map))
		{
			return std::end(m_arg_map);
		}
		return m_arg_map.find(ret_val->second);
	};

	auto ret_val = sub_find();
	if (ret_val == std::end(m_arg_map))
		return std::vector<std::string>();
	return ret_val->second;
}

/*
* @brief Gets number of the saved keys.
*/
unsigned int Cparser::get_saved_key_num() const noexcept
{
	return std::size(m_correspondance_map);
}
