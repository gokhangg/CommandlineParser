/*********************
* Copyright [2018] Written by Gokhan Gunay
* Feel free to modify, distribute and whatever you want to do.
* The author cannot be held responsible for the failure/damage
* any user sustains using this library.
* Contact: ghngunay@gmail.com
**********************/

#include "argument_parser.hpp"

#include <iostream>
#include <algorithm>

Cparser::Cparser(const int argc, char** const argv)
    : argStringVect_{ argv, argv + argc } {}

Cparser::Cparser(const std::vector<std::string>& v_string)
    : argStringVect_{ v_string } {}


void Cparser::input(const std::vector<std::string>& argv) {
    constexpr char cmd_option_start = '-';
    std::string key;
    std::vector<std::string> vals;

    for (const auto& it : argv) {
        if (it[0] == cmd_option_start) {
            if (!std::empty(vals) && it != "") {
                argMap_.emplace(key, vals);
                vals.clear();
            }
            key = it;
        } else if (!std::empty(key) && it != "") {
               vals.emplace_back(it);
        }
    }
    if (!std::empty(vals)) {
        argMap_.emplace(key, vals);
        vals.clear();
    }
}

void Cparser::save_key(const std::string key, const std::string in_arg) {
    save_key(key, in_arg, "", "");
}

void Cparser::save_key(const std::string key, const std::string in_arg, const std::string defVal) {
    save_key(key, in_arg, defVal, "");
}

void Cparser::save_key(const std::string key, const std::string in_arg, \
        const std::string defVal, const std::string help) {
    // If one of the arguments are invalid return without any action.
    if (std::empty(key) || std::empty(in_arg)) return;
    correspondanceMap_.emplace(key, in_arg);
    helpMap_.emplace(key, std::make_pair(defVal, help));
}

void Cparser::set_epilog(std::string epilog) {
    epilog_ = std::move(epilog);
}

auto Cparser::operator[](const std::string key) const noexcept-> ParserReturnType<std::string> {
    auto retval = find(key);
    return ParserReturnType<std::string>(retval.first != "", retval.second);
}

auto Cparser::find(const std::string& key) const noexcept -> std::pair<std::string, std::vector<std::string>> {
    auto sub_find = [&]() {
        const auto& ret_val = correspondanceMap_.find(key);
        if (ret_val == std::end(correspondanceMap_)) {
            return std::end(argMap_);
        }
        return argMap_.find(ret_val->second);
    };

    auto& ret_val = sub_find();
    if (ret_val == std::end(argMap_)) return std::make_pair(std::string{}, std::vector<std::string>{});
    return *ret_val;
}

size_t Cparser::get_saved_key_num() const noexcept {
    return std::size(correspondanceMap_);
}

void Cparser::parse(const std::string usageExtra) {
    if (std::size(argStringVect_) > 1) {
        input(argStringVect_);
        for (auto& [key, val] : helpMap_) {
            auto& linkedKey = correspondanceMap_[key];
            if (argMap_.count(linkedKey) == 0) {
                auto vl = val.first != "" ? std::vector<std::string>{ val.first } : std::vector<std::string>{};
                argMap_.emplace(linkedKey, vl);
            }
        }
        if (argMap_.count("--help") > 0 || argMap_.count("-h")) {
            print_help(usageExtra);
        }
    } else {
        print_help(usageExtra);
    }
}

void Cparser::print_help(const std::string usageExtra) {
    constexpr auto kSpaceOffset = 1;
    std::string helpMenu = "-h/--help";
    if (std::size(argStringVect_) <= 1)
        std::cout << "Incorrect parameters." << std::endl;
    std::cout << "Usage:" << std::endl;
    if (std::size(usageExtra)) std::cout << usageExtra << std::endl;
    std::cout << "Arguments:" << std::endl;
    auto it = std::max_element(std::begin(helpMap_), std::end(helpMap_), \
        [this](auto& val1, auto& val2) { return std::size(correspondanceMap_[val1.first]) < std::size(correspondanceMap_[val2.first]); });
    uint64_t maxSpaceSize = std::size(it->first);
    if (maxSpaceSize < std::size(helpMenu)) maxSpaceSize = std::size(helpMenu);
    maxSpaceSize += kSpaceOffset;

    std::cout << helpMenu << std::string(maxSpaceSize - std::size(helpMenu), ' ') \
        << ": " << "Help menu:" << std::endl;
    for (auto& it : helpMap_) {
        std::cout << correspondanceMap_[it.first] << std::string(maxSpaceSize - std::size(it.first), ' ') \
                << ": " << it.second.second << std::endl;
    }
    std::cout << std::endl << epilog_ << std::endl;
}
