/*********************
* Copyright [2018] Written by Gokhan Gunay
* Feel free to modify, distribute and whatever you want to do.
* The author cannot be held responsible for the failure/damage
* any user sustains using this library.
* Contact: ghngunay@gmail.com
**********************/

#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>

/*Class to manipulate output of found parameters.*/
template<typename In_T>
class ParserReturnType {
 public:
ParserReturnType() = delete;
explicit ParserReturnType(const std::vector<In_T>& return_val)
    : m_called{ !std::empty(return_val) }
    , m_return_val{ std::empty(return_val) ? return_val : std::vector<In_T>(std::next(std::begin(return_val), 1)
    , std::end(return_val)) } {
    }

/*Return true if the relevant parameter is in the commandline argumens.*/
auto is_called() const noexcept {
    return m_called;
}

auto size() const noexcept {
    return std::size(m_return_val);
}

std::vector<double> get_as_double() const {
    return translate<double>([](const std::string& str) {return std::stod(str); });
}

std::vector<float> get_as_float() const {
    return translate<float>([](const std::string& str) {return std::stof(str); });
}

std::vector<int> get_as_integer() const {
    return translate<int>([](const std::string& str) {return std::stoul(str); });
}

std::vector<uint64_t> get_as_uint64() const {
    return translate<uint64_t>([](const std::string& str) {return std::stoi(str); });
}

std::vector<std::string> get_as_string() const noexcept {
    return m_return_val;
}

 private:
/*
* @brief Used to translate input string vector to output typed vector.
*/
template<typename Out_T, typename Funct_T>
std::vector<Out_T> translate(Funct_T&& funct) const {
    std::vector<Out_T> ret_val(std::size(m_return_val));
    auto it_out = std::begin(ret_val);
    try {
        for (auto it = std::begin(m_return_val); it != std::end(m_return_val);) {
            *it_out++ = funct(*it++);
        }
    }
    /*In case of any type of exception just return with empty vector.*/
    catch (...) {
        ret_val = std::vector<Out_T>{};
    }
    return ret_val;
    }

    bool m_called;
    std::vector<In_T> m_return_val;
};

class Cparser {
    using ArgMapType = std::map<std::string, std::vector<std::string>>;
    using CorrespondanceMapType = std::map<std::string, std::string>;
    using HelpMapType = std::map<std::string, std::string>;

 public:
    /**
     * @brief Construct a new Cparser object with executable arguments.
     * 
     * @param argc Argument count.
     * @param argv Argument list.
     */
    explicit Cparser(const int argc, char ** const argv);

    /**
     * @brief Construct a new Cparser object with argument vector.
     * 
     * @param v_string 
     */
    explicit Cparser(const std::vector<std::string> v_string);

    /**
     * @brief To remove copy assignment.
     * 
     * @return Cparser& 
     */
    Cparser& operator=(const Cparser&) = delete;

    /**
     * @brief To remote copy construction.
     * 
     */
    Cparser(const Cparser&) = delete;

    /**
     * @brief To set move constructor.
     * 
     */
    Cparser(Cparser&&) = default;

    /**
     * @brief To set move assignement.
     * 
     * @return Cparser& 
     */
    Cparser& operator=(Cparser&&) = default;

    /**
     * @brief Used to import input arguments and add to the argument pool.
     * 
     * @param argv Argument vector.
     */
    void input(const std::vector<std::string> argv);

    /**
     * @brief Used to save a key and corresponding possible input argument.
     * 
     * @param key Key to save.
     * @param in_arg Input argument to be used at CL.
     * @param help Help to print if given.
     */
    void save_key(const std::string key, const std::string in_arg, const std::string help = "");

    /**
     * @brief Used to seet epilog.
     * 
     * @param epilog Epilog.
     */
    void set_epilog(const std::string epilog);

    /**
     * @brief Used to fetch CL argument values.
     * 
     * @param key Key of the argument.
     * @return ParserReturnType<std::string> Argument values as string.
     */
    auto operator[](const std::string key) const noexcept->ParserReturnType<std::string>;

    /**
     * @brief Used to get the saved key num object
     * 
     * @return unsigned int Key number.
     */
    size_t get_saved_key_num() const noexcept;

    /**
     * @brief To parse the arguments.
     * 
     */
    void parse();

    /**
     * @brief To print the help menu.
     * 
     */
    void print_help();

 private:
    /**
     * @brief Used to fetch CL argument values.
     * 
     * @param key Key of the argument.
     * @return std::vector<std::string> Argument values as string.
     */
    auto find(const std::string& key) const noexcept->std::vector<std::string>;
    ArgMapType argMap_;
    CorrespondanceMapType correspondanceMap_;
    HelpMapType helpMap_;
    std::string epilog_;
};
