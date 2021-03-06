/*
Written by Gokhan Gunay
Contact: ghngunay@gmail.com
*/

#ifndef parser_hpp
#define parser_hpp

#include <string>
#include <vector>
#include <utility>
#include <map>

/*Class to manipulate output of found parameters.*/
template<typename In_T>
class ParserReturnType
{
public:
	ParserReturnType() = delete;
	explicit ParserReturnType(const std::vector<In_T>& return_val)
		: m_called{ !std::empty(return_val) }
		, m_return_val{ std::empty(return_val) ? return_val : std::vector<In_T>(std::next(std::begin(return_val), 1), std::end(return_val)) }
	{
	}
	/*Return true if the relevant parameter is in the commandline argumens.*/
	auto is_called() const noexcept
	{
		return m_called;
	}

	auto size() const noexcept
	{
		return m_sz;
	}

	std::vector<double> get_as_double() const
	{
		return translate<double>([](const std::string& str) {return std::stod(str); });
	}

	std::vector<float> get_as_float() const
	{
		return translate<float>([](const std::string& str) {return std::stof(str); });
	}

	std::vector<int> get_as_integer() const
	{
		return translate<int>([](const std::string& str) {return std::stoi(str); });
	}

	std::vector<std::string> get_as_string() const noexcept
	{
		return m_return_val;
	}

private:
	/*
	* @brief Used to translate input string vector to output typed vector.
	*/
	template<typename Out_T, typename Funct_T>
	std::vector<Out_T> translate(Funct_T&& funct) const
	{
		std::vector<Out_T> ret_val(std::size(m_return_val));
		auto it_out = std::begin(ret_val);
		try
		{
			for (auto it = std::begin(m_return_val); it != std::end(m_return_val);)
			{
				*it_out++ = funct(*it++);
			}
		}
		/*In case of any type of exception just return with empty vector.*/
		catch (...)
		{
			ret_val = std::vector<Out_T>{};
		}
		return ret_val;
	}

	bool m_called;
	std::size_t m_sz;
	std::vector<In_T> m_return_val;
};

class Cparser {
	using ArgMapType = std::map<std::string, std::vector<std::string>>;
	using CorrespondanceMapType = std::map<std::string, std::string>;
public:
	Cparser() = default;
	explicit Cparser(const int argc, char ** const argv)
	{
		std::vector<std::string> v_string(argc);
		for (auto ind = 0; ind < argc; ++ind)
		{
			v_string[ind] = argv[ind];
		}
		input(v_string);
	}

	explicit Cparser(const std::vector<std::string> v_string)
	{
		input(v_string);
	}

	~Cparser() = default;
	Cparser& operator=(const Cparser&) = delete;
	Cparser(const Cparser&) = delete;
	Cparser(Cparser&&) = default;
	Cparser& operator=(Cparser&&) = default;
	void input(const std::vector<std::string> argv);
	void save_key(const std::string key, const std::string in_arg);
	auto operator[](const std::string key) const noexcept->ParserReturnType<std::string>;
	unsigned int get_saved_key_num() const noexcept;

private:
	auto find(const std::string& key) const noexcept->std::vector<std::string>;
	ArgMapType m_arg_map;
	CorrespondanceMapType m_correspondance_map;
};

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

#endif
