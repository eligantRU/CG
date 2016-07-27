#include "stdafx.h"
#include "consts.h"
#include "Window.h"

/*template<class Base> class ObjectFactory {
public:
	ObjectFactory() = default;
	~ObjectFactory() = default;
	template<class Derived> std::unique_ptr<Base> add()
	{
		return std::make_unique<Derived>();
	}
};

class Hero
{
public:
	virtual void Bla() = 0;
};

class Man : public Hero
{
public:
	Man() = default;
	~Man() = default;
	void Bla() { std::cout << "I'm a man" << std::endl; }
};

class Woman : public Hero
{
public:
	Woman() = default;
	~Woman() = default;
	void Bla() { std::cout << "I'm not a man" << std::endl; }
};

int main()
{
	ObjectFactory<Hero> factory;
	std::vector<std::unique_ptr<Hero>> heroes;
	heroes.push_back(factory.add<Man>());
	heroes.push_back(factory.add<Woman>());
	for (auto &hero : heroes)
	{
		hero->Bla();
	}

	return 0;
}
*/

int main(int argc, char * argv[])
{
	(void)argc;
	(void)argv;
    glewInit();

    CWindow window;
    window.Show(WINDOW_SIZE);
    window.DoGameLoop();

	return 0;
}
