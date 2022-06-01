#pragma once
#include "Developer.h"

// interface
class DeveloperFactory
{
public:
	virtual Developer* createDeveloper() = 0;
	virtual ~DeveloperFactory() {};
};


class CppDeveloperFactory : public DeveloperFactory
{
public:
	Developer* createDeveloper() override
	{
		return new CppDeveloper();
	}
};


class JavaDeveloperFactory : public DeveloperFactory
{
public:
	Developer* createDeveloper() override
	{
		return new JavaDeveloper();
	}
};