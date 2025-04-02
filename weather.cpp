#include "weather.h"
#include <iostream> //for debug TODO remove this

uint32_t get_weather_value(double hrs=0){//algorithm based on https://github.com/xivapi/ffxiv-datamining/blob/master/docs/Weather.md which is in turn based on the SaintCoinach library
	using namespace std::chrono;
	auto local_time = duration_cast<seconds>(system_clock::now().time_since_epoch()).count() + (hrs*8*175*1000);
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
					unsigned int weather_value = get_weather_value();
					std::cout<<"Weather Val:"<<weather_value<<std::endl;
					unsigned int total_rate = 0;
					for (size_t i = 0; i < zd.Rates.size()-1; i++){
						total_rate += zd.Rates[i].rate;
						if(weather_value < total_rate){
							forecast.push_back(zd.Rates[i].name);
							return forecast;//just for testing, remove and add more calls for longer forecast
						}
					}
				}
			}
		}
	}
	return forecast;
};
