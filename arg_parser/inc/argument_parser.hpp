/*
Written by Gokhan Gunay
Contact: ghngunay@gmail.com
*/

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
    , std::end(return_val)) }
{
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
    return translate<int>([](const std::string& str) {return std::stoi(str); });
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
 public:
    Cparser() = default;
    explicit Cparser(const int argc, char ** const argv);
    explicit Cparser(const std::vector<std::string> v_string);
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
