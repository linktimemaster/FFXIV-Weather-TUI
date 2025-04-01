#include "weather.h"
#include <iostream> //for debug TODO remove this

unsigned int get_weather_value(uint64_t hrs=0){//algorithm based on https://github.com/xivapi/ffxiv-datamining/blob/master/docs/Weather.md which is in turn based on the SaintCoinach library
	using namespace std::chrono;
	uint64_t local_time = (uint64_t)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() + (hrs*8*175*1000);
	uint64_t local_sec = local_time/1000;
	uint64_t bell = local_sec/175;
	uint64_t increment = (bell + 8 - (bell%8)) % 24;
	uint64_t total_days = local_sec / 4200;
	//total_days = (total_days << 32) >> 0;
	uint64_t base = total_days * 100 + increment;
	uint64_t s1 = (base << 11) ^ base;
	uint64_t s2 = (s1 >> 8) ^ s1;
	return (unsigned int)s2 % 100;
}

std::vector<std::string> weather_forecast(std::string r, std::string z){
	std::vector<std::string> forecast;
	for (auto& wd : WData){
		if(wd.Region == r){
			for (auto& zd : wd.Zones){
				if(zd.Zone == z){
					unsigned int weather_value = get_weather_value();
					std::cout<<weather_value<<std::endl;
					unsigned int total_rate = 0;
					for (size_t i = 0; i < zd.Rates.size()-1; i++){
						total_rate += zd.Rates[i].rate;
						if(weather_value < total_rate){
							std::cout << total_rate << std::endl;
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
