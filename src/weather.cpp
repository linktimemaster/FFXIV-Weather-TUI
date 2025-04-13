#include "../include/weather.h"
//#include <iostream>

uint32_t get_weather_value(int hrs){//algorithm based on https://github.com/xivapi/ffxiv-datamining/blob/master/docs/Weather.md which is in turn based on the SaintCoinach library
	using namespace std::chrono;
	auto base_time = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
	auto local_time = base_time + (hrs*8*175);
	double bell = local_time/175;
	uint32_t increment = (uint32_t)fmod((bell + 8 - fmod(bell,8.0)), 24.0);
	uint32_t total_days = (uint32_t)((double)local_time / 4200.0);
	uint32_t base = total_days * 100 + increment;
	int32_t signed_base = (int32_t)base;
	int32_t signed_s1 = (signed_base << 11) ^ signed_base;
	uint32_t s1 = (uint32_t)signed_s1;
	uint32_t s2 = (s1 >> 8) ^ s1;
	return s2 % 100;
}

std::vector<std::string> weather_forecast(std::string r, std::string z){
	std::vector<std::string> forecast;
	for (auto& wd : WData){
		if(wd.Region == r){
			for (auto& zd : wd.Zones){
				if(zd.Zone == z){
					for(int h = 0; h < 10; h ++){
						//std::cout<<h<<std::endl;
						unsigned int weather_value = get_weather_value(h);
						unsigned int total_rate = 0;
						for (size_t i = 0; i < zd.Rates.size(); i++){
							total_rate += zd.Rates[i].rate;
							if(weather_value < total_rate){
								forecast.push_back(zd.Rates[i].name);
								//std::cout<<"wv:"<<weather_value<<'\n'<<zd.Rates[i].name<<std::endl;
								break;
							}
						}
					}
				}
			}
		}
	}
	return forecast;
};
