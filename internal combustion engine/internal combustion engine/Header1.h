#pragma once
#include "Header.h"


class test 
{
public: 
	engine Engine_for_test;
		
		void start_engine(engine x);
};



void test::start_engine(engine x)
{
	std::cout << "¬ведите температуру окружающей среды: ";
	std::cin >> x.ambient_temperature;
	x.Engine_work(x.ambient_temperature);
	
	
}