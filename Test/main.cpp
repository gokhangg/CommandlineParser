/*
Written by Gokhan Gunay
Contact: ghngunay@gmail.com
*/
#include <iostream>  // I/O 
#include "gtest/gtest.h"
#include "ArgumentParser.hpp"


using namespace std;

int main(int argc,char * argv[])
{
	Cparser parser;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(TEST1, TEST11)
{
}