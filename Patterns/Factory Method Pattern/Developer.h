#pragma once
#include <iostream>

// interface
class Developer
{
public:
	virtual void writeCode() = 0;
	virtual ~Developer() {};
};


class CppDeveloper : public Developer
{
public:
	void writeCode() override
	{
		std::cout << "C++ developer writes code!"<< std::endl;
	}
};


class JavaDeveloper : public Developer
{
public:
	void writeCode() override
	{
		std::cout << "Java developer writes code!" << std::endl;
	}
};