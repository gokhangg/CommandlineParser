/*
Written by Gokhan Gunay
Contact: ghngunay@gmail.com
*/


#ifndef parser_hpp
#define parser_hpp

#include <string>


using namespace std;

class cparser {
public:
	cparser(const int argc, char ** const argv);
	cparser() = default;
	~cparser() = default;
	cparser& operator=(const cparser&) = delete;
	cparser(const cparser&) = delete;
	cparser(cparser&&) = default;
	cparser& operator=(cparser&&) = default;
	void input(const int argc, char ** const arg);
	void save_keys(const char* const in_arg, const char* const key);
	string operator[](const char* const key);
	unsigned int get_saved_key_num();
	
private:
	string get_cstr_arg(const string& str, const char * const arg);
	string input_args;
	string keys;
	unsigned int saved_key_num;
};

cparser::cparser(const int argc, char ** const argv)
{
	input(argc, argv);
	saved_key_num = 0;
}

/*
* @brief Imports input arguments and count to the argument pool.
*/
void cparser::input(const int argc, char ** const arg)
{
	for (auto cnt = 0u; cnt < argc; cnt++)
	{
		input_args.append(" ");
		input_args.append(arg[cnt]);
	}
}

/*
* @brief Saves a key and corresponding possible input argument.
*/
void cparser::save_keys(const char* const key, const char* const in_arg)
{
	if ((key == NULL) || (in_arg == NULL))//If one of the arguments are invalid return without any action.
		return;
	keys.append(key);//append the key after the input argument
	keys.append(" ");//add one space
	keys.append(in_arg);//save input argument
	keys.append(" ");//add one space
	saved_key_num++;//Save the number of saved keys
}

/*
* @brief Retrieves input argument corresponding to the given key.
*/
string cparser::operator[](const char* const key)
{
	return get_cstr_arg(input_args, get_cstr_arg(keys, key).c_str());
}

/*
* @brief Gets number of the saved keys.
*/
unsigned int cparser::get_saved_key_num()
{
	return saved_key_num;
}

/**
* @brief Retrieves input argument corresponding to the given key.
*/
string cparser::get_cstr_arg(const string& str, const char * const arg)
{
	size_t pos = str.find(arg);
	if (pos == -1)
		return static_cast<string>("");//if not found return null
	pos=str.find(" ", pos + 1);
	return str.substr(pos + 1,str.find(" ", pos + 1) - pos - 1);
}


#endif
