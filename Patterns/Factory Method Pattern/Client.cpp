// Factory Method Pattern
//---------------------------------------------------------------------------------------------------------
// Суть патерна заключается в том, что "клиент" работает исключительно с функцией MAIN,
// он не вникает в суть процессов(кода), его интересует только конечный результат.
// Мы можем добиться этого создав некий "каталог" продуктов с помощью интрефесов(абстрактных классов),
// переопределив "рабочие" виртуальные методы в подклассах, и предложить пользователю выбор.
// Также если пользователю понадобится новый продукт, нам не придется ломать видимый пользователю код, 
// всего лишь нужно будет добавить определённую логику в скрытых от пользователя участках программы.
//----------------------------------------------------------------------------------------------------------
// PS В данном учебном проекте плюсы паттерна совсем неочевидны, проект носит лишь ознакомительных характер.
//----------------------------------------------------------------------------------------------------------

#include "Developer.h"
#include "DeveloperFactory.h"

static DeveloperFactory* createDeveloperBySpecialty(const std::string specialty);

int main()
{
	DeveloperFactory* factory = createDeveloperBySpecialty("java");  // C++/c++/Java/java
	Developer* developer = factory->createDeveloper();               // if (factory == nullptr) std::cerr << "Incorrect input!" << std::endl;
	developer->writeCode();

	delete developer;
	delete factory;
	
	return 0;
}

static DeveloperFactory* createDeveloperBySpecialty(const std::string specialty)
{
	if (specialty == "C++" || specialty == "c++")
		return new CppDeveloperFactory();
	else if (specialty == "Java" || specialty == "java")
		return new JavaDeveloperFactory();

	return nullptr;
}
