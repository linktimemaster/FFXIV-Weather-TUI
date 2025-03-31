//more headers to be added as needed
#ifndef WEATHER_H
#define WEATHER_H

#include <string>
#include <vector>

struct Weather_Rates{
	std::string name;
	int rate;
};
struct Zone_Data{
	std::string Zone;
	std::vector<Weather_Rates> Rates;
};
struct Weather_Data{
	std::string Region;
	std::vector<Zone_Data> Zones;
};
//weather data
//La Noscea
const std::vector<Weather_Rates> Limsa = {
	{"clouds",20},
	{"clear skies",30},
	{"fair skies",30},
	{"fog",10},
	{"rain",10}
};
const std::vector<Weather_Rates> MiddleLN = {
	{"clouds",20},
	{"clear skies",30},
	{"fair skies",20},
	{"wind",10},
	{"fog",10},
	{"rain",10}
};
const std::vector<Weather_Rates> LowerLN = {
	{"clouds",20},
	{"clear skies",30},
	{"fair skies",20},
	{"wind",10},
	{"fog",10},
	{"rain",10}
};
const std::vector<Weather_Rates> EasternLN = {
	{"fog",5},
	{"clear skies",45},
	{"fair skies",30},
	{"clouds",10},
	{"rain",5},
	{"showers",5}
};
const std::vector<Weather_Rates> WesternLN = {
	{"fog",10},
	{"clear skies",30},
	{"fair skies",20},
	{"clouds",20},
	{"wind",10},
	{"gales",10}
};
const std::vector<Weather_Rates> UpperLN = {
	{"clear skies",30},
	{"fair skies",20},
	{"clouds",20},
	{"fog",10},
	{"thunder",10},
	{"thunderstorms",10}
};
const std::vector<Weather_Rates> OuterLN = {
	{"clear skies",30},
	{"fair skies",20},
	{"clouds",20},
	{"fog",15},
	{"rain",15}
};
const std::vector<Weather_Rates> WolvesDen = {
	{"clouds",20},
	{"clear skies",30},
	{"fair skies",30},
	{"fog",10},
	{"thunderstorms",10}
};
const std::vector<Weather_Rates> Mist = {
	{"clouds",20},
	{"clear skies",30},
	{"fair skies",30},
	{"fog",10},
	{"rain",10}
};
//The Black Shroud
const std::vector<Weather_Rates> Gridania = {
	{"rain",20},
	{"fog",10},
	{"clouds",10},
	{"fair skies",15},
	{"clear skies",30},
	{"fair skies",15}
};
const std::vector<Weather_Rates> CentralS = {
	{"thunder",5},
	{"rain",15},
	{"fog",10},
	{"clouds",10},
	{"fair skies",15},
	{"clear skies",30},
	{"fair skies",15}
};
const std::vector<Weather_Rates> EastS = {
	{"thunder",5},
	{"rain",15},
	{"fog",10},
	{"clouds",10},
	{"fair skies",15},
	{"clear skies",30},
	{"fair skies",15}
};
const std::vector<Weather_Rates> SouthS = {
	{"fog",5},
	{"thunderstorms",5},
	{"thunder",15},
	{"fog",5},
	{"clouds",10},
	{"fair skies",30},
	{"clear skies",30}
};
const std::vector<Weather_Rates> NorthS = {
	{"fog",5},
	{"showers",5},
	{"rain",15},
	{"fog",5},
	{"clouds",10},
	{"fair skies",30},
	{"clear skies",30}
};
const std::vector<Weather_Rates> LavBeds = {
	{"clouds",5},
	{"rain",15},
	{"fog",10},
	{"clouds",10},
	{"fairSkies",15},
	{"clearSkies",30},
	{"fairSkies",15}
};
//Thanalan
const std::vector<Weather_Rates> Uldah = {
	{"clear skies",40},
	{"fair skies",20},
	{"clouds",25},
	{"fog",10},
	{"rain",5}
};
const std::vector<Weather_Rates> WesternThan = {
	{"clear skies",40},
	{"fair skies",20},
	{"clouds",25},
	{"fog",10},
	{"rain",5}
};
const std::vector<Weather_Rates> EasternThan = {
	{"clear skies",40},
	{"fair skies",20},
	{"clouds",10},
	{"fog",10},
	{"rain",5},
	{"showers",15}
};
const std::vector<Weather_Rates> CentralThan = {
	{"dust storms",15},
	{"clear skies",40},
	{"fair skies",20},
	{"clouds",10},
	{"fog",10},
	{"rain",5}
};
const std::vector<Weather_Rates> SouthernThan = {
	{"heat waves",20},
	{"clear skies",40},
	{"fair skies",20},
	{"clouds",10},
	{"fog",10}
};
const std::vector<Weather_Rates> NorthernThan = {
	{"clear skies",5},
	{"fair skies",15},
	{"clouds",30},
	{"fog",50}
};
const std::vector<Weather_Rates> Goblet = {
	{"clear skies",40},
	{"fair skies",20},
	{"clouds",25},
	{"fog",10},
	{"rain",5}
};
//Mor Dhona
const std::vector<Weather_Rates> MorDhona = {
	{"clouds",15},
	{"fog",15},
	{"gloom",30},
	{"clear skies",15},
	{"fair skies",25}
};
//zones
const std::vector<Zone_Data> LN_Zones = {
	{"Limsa Lominsa", Limsa},
	{"Middle La Noscea", MiddleLN},
	{"Lower La Noscea", LowerLN},
	{"Eastern La Noscea", EasternLN},
	{"Western La Noscea", WesternLN},
	{"Upper La Noscea", UpperLN},
	{"Outer La Noscea", OuterLN},
	{"Wolves Den Pier", WolvesDen},
	{"The Mist", Mist}
};
const std::vector<Zone_Data> BS_Zones = {
	{"Gridania", Gridania},
	{"Central Shroud", CentralS},
	{"East Shroud", EastS},
	{"South Shroud", SouthS},
	{"North Shroud", NorthS},
	{"The Lavender Beds", LavBeds}
};
const std::vector<Zone_Data> Than_Zones = {
	{"Ul'dah", Uldah},
	{"Western Thanalan", WesternThan},
	{"Central Thanalan", CentralThan},
	{"Eastern Thanalan", EasternThan},
	{"Southern Thanalan", SouthernThan},
	{"Northern Thanalan", NorthernThan},
	{"The Goblet", Goblet}
};
const std::vector<Zone_Data> Mor_Zones = {
	{"Mor Dhona", }
};
//regions
const std::vector<Weather_Data> WData = {
	//2.0
	{"La Noscea", LN_Zones},
	{"The Black Shroud", BS_Zones},
	{"Thanalan", Than_Zones},
	{"Mor Dhona", Mor_Zones},
	//3.0
	{"Coerthas", },
	{"Abalathia's Spine", },
	{"Dravania", },
	//4.0
	{"Gyr Abania", },
	{"Hingashi", },
	{"Othard", },
	//5.0
	//6.0
	//7.0
	/*
	 * I'll do these later,
	 * not up to it in game so I'll worry about it another day :)
	 */
};

#endif //WEATHER_H
