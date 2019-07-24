#pragma once
#include <iostream>
#include <ctime>

#include "windows.h"


class engine 
{
private:
	float Moment_iner = 10;
	int Superheat_t = 110;
	float heating_ratio = 0.1;  
	float velocity_ratio = 0.001;
	float velocity = 0;
	float cooling_ratio = 0.1;																				
	float engine_temp ;
	float engine_heating(float torque, float heating_ratio, float velocity, float velocity_ratio);
	float engine_cooling(float cooling_ratio, float ambient_temperature, float engine_temp);
	float uskor(float moment_iner, float torque,float time);
	float moment(float velocity);
public:
	
	float ambient_temperature;
	void Engine_work(float ambient_t);
};

float engine::engine_heating(float torque, float heating_ratio, float velocity, float velocity_ratio)
{
	return torque * heating_ratio + velocity * velocity * velocity_ratio;
}

float engine::engine_cooling(float cooling_ratio, float ambient_temperature, float engine_temp)
{
	return cooling_ratio * (ambient_temperature - engine_temp);
}

float engine::uskor(float moment_iner, float torque,float time)
{
	return (torque / moment_iner)*time;
}

float engine::moment(float velocity)
{
	if (velocity < 75) return (1500 + 55 * velocity) / 75;
	else if (velocity < 150) return (3750 + 25 * velocity) / 75;
	else if (velocity < 200) return (4250 + 5 * velocity) / 50;
	else if (velocity < 250) return (11250 - 30 * velocity) / 50;
	else if (velocity < 300)	return (22500 - 75 * velocity) / 50;

}

void engine::Engine_work(float ambient) 
{
	clock_t t;
	t = clock();
	engine_temp = ambient;
	float Torque = 20;
	float time=0;
	bool flag = false;
	
	while (engine_temp <= Superheat_t)

	{
		
		time = (float)(clock() - t) / CLOCKS_PER_SEC;
		velocity = uskor(Moment_iner, Torque,time);
		Torque = moment(velocity);



		float heating_velocity = engine_heating(Torque, heating_ratio, velocity, velocity_ratio);
		float cooling_velocity = engine_cooling(cooling_ratio, ambient_temperature, engine_temp);


		engine_temp += (heating_velocity + cooling_velocity);
		
		system("cls");
		std::cout <<std::endl<< "Текущая температура двигателя = " << engine_temp<<"С°";
		std::cout << std::endl << "Текущая скорость оборотов двигателя = " << velocity << "рад/c ";
		if (velocity > 300)
		{
			system("cls");
			std::cout << std::endl << "Сбой работы двигателя"<<std::endl;
			flag = true;
			break;
			
		}
	}
	if(!flag)std::cout << std::endl << "Двигатель проработал до переграва " << time << "cек." << std::endl;
}
