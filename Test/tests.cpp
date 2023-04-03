/*********************
* Copyright [2018] Written by Gokhan Gunay
* Feel free to modify, distribute and whatever you want to do.
* The author cannot be held responsible for the failure/damage
* any user sustains using this library.
* Contact: ghngunay@gmail.com
**********************/
#include <iostream>  // I/O
#include "gtest/gtest.h"
#include "argument_parser.hpp"


#include <string>  // NOLINT
#include <vector>  // NOLINT


using namespace std;  // NOLINT

constexpr auto kInFile = "inFileHere";

auto GenerateTestData() {
    std::vector<std::string> retVal = { "executableHere", "-in", kInFile,
        "-out", "outFileHere", "-p1", "ab", "bc", "cd", "de", "ef", "fg",
        "-p0", "-p2", "0", "1", "2", "3", "4", "5", "-p3", "0.1", "0.2",
        "0.3", "0.4", "0.5", "0.6", "-p4" };
    return retVal;
}

Cparser GetInitializedParser() {
    auto generatedTestData = GenerateTestData();
    Cparser parser(generatedTestData);
    parser.save_key("in_file", "-in");
    parser.save_key("out_file", "-out");
    parser.save_key("param0", "-p0");
    parser.save_key("param1", "-p1");
    parser.save_key("param2", "-p2");
    parser.save_key("param3", "-p3");
    parser.save_key("param4", "-p4");
    parser.parse();
    return parser;
}


TEST(CommandLineParser, TestString) {
    auto initializedParser = GetInitializedParser();
    EXPECT_EQ(initializedParser["in_file"].get_as_string(), std::vector<std::string>({ kInFile }));
    EXPECT_EQ(initializedParser["out_file"].get_as_string(), std::vector<std::string>({"outFileHere"}));
    EXPECT_EQ(initializedParser["param1"].get_as_string(), \
        std::vector<std::string>({"ab", "bc", "cd", "de", "ef", "fg"}));
}

TEST(CommandLineParser, TestInteger) {
    auto initializedParser = GetInitializedParser();
    EXPECT_TRUE(initializedParser["param2"].is_called());
    EXPECT_EQ(initializedParser["param2"].get_as_integer(), std::vector<int>({0, 1, 2, 3, 4, 5}));
}

TEST(CommandLineParser, TestFloat) {
    auto initializedParser = GetInitializedParser();
    EXPECT_TRUE(initializedParser["param3"].is_called());
    EXPECT_EQ(initializedParser["param3"].get_as_float(), std::vector<float>({ 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f}));
    }

TEST(CommandLineParser, TestDouble) {
    auto initializedParser = GetInitializedParser();
    EXPECT_TRUE(initializedParser["param3"].is_called());
    EXPECT_EQ(initializedParser["param3"].get_as_double(), std::vector<double>({ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 }));
}

TEST(CommandLineParser, MidArgumentlesParameter) {
    auto initializedParser = GetInitializedParser();
    EXPECT_TRUE(initializedParser["param0"].is_called());
    EXPECT_TRUE(std::empty(initializedParser["param0"].get_as_string()));
}

TEST(CommandLineParser, EndArgumentlesParameter) {
    auto initializedParser = GetInitializedParser();
    EXPECT_TRUE(initializedParser["param4"].is_called());
    EXPECT_TRUE(std::empty(initializedParser["param4"].get_as_string()));
}

TEST(CommandLineParser, DefaultArgumentValue) {
    constexpr auto kFloatVal = 3.2f;
    auto initializedParser = GetInitializedParser();
    initializedParser.save_key("param5", "-p5", std::to_string(kFloatVal));
    initializedParser.parse();
    EXPECT_TRUE(initializedParser["param5"].is_called());
    EXPECT_NEAR(initializedParser["param5"].get_as_float()[0], kFloatVal, 1e-5);
}
