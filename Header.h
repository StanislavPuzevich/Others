#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

class Solution
{
public:
	std::ifstream image;
	std::ofstream newimage;

	int temp(int x);
	char users_choice();
	void work_func(Solution& s, char ans);
	int check_open_file_error(Solution&s , std::string fname1, std::string fname2);
};