#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "image_view.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include "../include/weather.h"

using namespace ftxui;

Component Window(std::string title, Component component) {
  return Renderer(component, [component, title] {
    return window(text(title), component->Render());
  });
}
Component Window_Frame(std::string title, Component component) {
  return Renderer(component, [component, title] {
    return window(text(title), component->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10));
  });
}

int main(void) { 
  std::vector<std::string> Regions{
    "La Noscea",
    "Thanalan",
    "The Black Shroud",
    "Mor Dhona",
    "Coerthas",
    "Abalathia's Spine",
    "Dravania",
    "Gyr Abania",
    "Hingashi",
    "Othard",
    "Eureka",
  };
  int selected_region = 0;
  
  auto region_menu = Menu(&Regions, &selected_region);

  std::vector<std::string> LN_Zones = {
    "Limsa Lominsa",
    "Middle La Noscea",
    "Lower La Noscea",
    "Eastern La Noscea",
    "Western La Noscea",
    "Upper La Noscea",
    "Outer La Noscea",
    "Wolves Den Pier",
    "The Mist",
  };
  int selected_zone = 0;
  std::vector<std::string> BS_Zones = {
    "Gridania",
    "Central Shroud",
    "East Shroud",
    "South Shroud",
    "North Shroud",
    "The Lavender Beds",
  };
  std::vector<std::string> Than_Zones = {
    "Ul'dah",
    "Western Thanalan",
    "Central Thanalan",
    "Eastern Thanalan",
    "Southern Thanalan",
    "Northern Thanalan",
    "The Goblet",
  };
  std::vector<std::string> Mor_Zones = {
    "Mor Dhona",
  };
  std::vector<std::string> Coerthas_Zones = {
    "Ishgard",
    "Coerthas Central Highlands",
    "Coerthas Western Highlands",
  };
  std::vector<std::string> Abalathia_Zones = {
    "The Sea of Clouds",
    "Azys Lla",
  };
  std::vector<std::string> Dravania_Zones = {
    "Idyllshire",
    "The Dravanian Forelands",
    "The Dravanian Hinterlands",
    "The Churning Mists",
  };
  std::vector<std::string> Gyr_Zones = {
    "Rhalgr's Reach",
    "The Fringes",
    "The Peaks",
    "The Lochs",
  };
  std::vector<std::string> Hingashi_Zones = {
    "Kugane",
    "Shirogane",
  };
  std::vector<std::string> Othard_Zones = {
    "The Ruby Sea",
    "Yanxia",
    "The Azim Steppe",
  };
  std::vector<std::string> Eureka_Zones = {
    "Anemos",
    "Pagos",
    "Pyros",
    "Hydatos",
  };
  

  auto tabs = Container::Tab(
      {
        Window("La Nocea Zones",Radiobox(&LN_Zones,&selected_zone)),
        Window("Thanalan Zones",Radiobox(&Than_Zones,&selected_zone)),
        Window("The Black Shroud Zones",Radiobox(&BS_Zones,&selected_zone)),
        Window("Mor Dhona Zone",Radiobox(&Mor_Zones,&selected_zone)),
        Window("Coerthas Zones",Radiobox(&Coerthas_Zones,&selected_zone)),
        Window("Abalathia's Spine Zones",Radiobox(&Abalathia_Zones,&selected_zone)),
        Window("Dravania Zones",Radiobox(&Dravania_Zones,&selected_zone)),
        Window("Gyr Abania Zones",Radiobox(&Gyr_Zones,&selected_zone)),
        Window("Hingashi Zones",Radiobox(&Hingashi_Zones,&selected_zone)),
        Window("Othard Zones",Radiobox(&Othard_Zones,&selected_zone)),
        Window("Eureka Zones",Radiobox(&Eureka_Zones,&selected_zone)),
      },
      &selected_region);
  
  auto screen = ScreenInteractive::Fullscreen();

  std::vector<std::string> forecasts;
  std::string curr_zone;
  switch(selected_region){
    case 0:
      curr_zone = LN_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region], LN_Zones[selected_zone]);
      break;
    case 1:
      curr_zone = Than_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region], Than_Zones[selected_zone]);
      break;
    case 2:
      curr_zone = BS_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region], BS_Zones[selected_zone]);
      break;
    case 3:
      curr_zone = Mor_Zones[0];
      forecasts = weather_forecast(Regions[selected_region], Mor_Zones[0]);
      break;
    case 4:
      curr_zone = Coerthas_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region], Coerthas_Zones[selected_zone]);
      break;
    case 5:
      curr_zone = Abalathia_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region], Abalathia_Zones[selected_zone]);
      break;
    case 6:
      curr_zone = Dravania_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region], Dravania_Zones[selected_zone]);
      break;
    case 7:
      curr_zone = Gyr_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region], Gyr_Zones[selected_zone]);
      break;
    case 8:
      curr_zone = Hingashi_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region], Hingashi_Zones[selected_zone]);
      break;
    case 9:
      curr_zone = Othard_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region],Othard_Zones[selected_zone]);
      break;
    case 10:
      curr_zone = Eureka_Zones[selected_zone];
      forecasts = weather_forecast(Regions[selected_region],Eureka_Zones[selected_zone]);
      break;
    default:
      curr_zone = LN_Zones[0];
      forecasts = weather_forecast("La Nocea", "Limsa Lominsa");
  }
  auto h_container = Container::Horizontal({
    Renderer([&]{ return text(forecasts[1]) | center | flex; }),
  });
  auto lcont = Container::Vertical({
      Window_Frame("Regions", region_menu),
      tabs,
      });
  auto container = Container::Vertical({ 
      Renderer([&]{
        std::string img_path = forecasts[0];    
        std::transform(img_path.begin(), img_path.end(), img_path.begin(), [](char ch) {
          return ch == ' ' ? '_' : ch;
        });
        img_path = "../FFXIV_Weather_Icons/" + img_path + "_icon.webp";
        return hflow({
          window(text(forecasts[0]),image_view(img_path),EMPTY) | size(WIDTH, LESS_THAN, 65),// | size(HEIGHT, EQUAL, 20),
          text("The weather in " + curr_zone + ", " + Regions[selected_region] + " is " + forecasts[0]) | center | flex
        }); 
      }),
      h_container,
  });
  int left_size = 30;
  auto left = lcont;
  container = ResizableSplitLeft(left, container, &left_size);
  auto renderer =
      Renderer(container, [&] { 
          switch(selected_region){
            case 0:
              if(selected_zone >= LN_Zones.size()) selected_zone = LN_Zones.size()-1;
              curr_zone = LN_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region], LN_Zones[selected_zone]);
              break;
            case 1:
              if(selected_zone >= Than_Zones.size()) selected_zone = Than_Zones.size()-1;
              curr_zone = Than_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region], Than_Zones[selected_zone]);
              break;
            case 2:
              if(selected_zone >= BS_Zones.size()) selected_zone = BS_Zones.size()-1;
              curr_zone = BS_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region], BS_Zones[selected_zone]);
              break;
            case 3:
              curr_zone = Mor_Zones[0];
              forecasts = weather_forecast(Regions[selected_region], Mor_Zones[0]);
              break;
            case 4:
              if(selected_zone >= Coerthas_Zones.size()) selected_zone = Coerthas_Zones.size()-1;
              curr_zone = Coerthas_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region], Coerthas_Zones[selected_zone]);
              break;
            case 5:
              if(selected_zone >= Abalathia_Zones.size()) selected_zone = Abalathia_Zones.size()-1;
              curr_zone = Abalathia_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region], Abalathia_Zones[selected_zone]);
              break;
            case 6:
              if(selected_zone >= Dravania_Zones.size()) selected_zone = Dravania_Zones.size()-1;
              curr_zone = Dravania_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region], Dravania_Zones[selected_zone]);
              break;
            case 7:
              if(selected_zone >= Gyr_Zones.size()) selected_zone = Gyr_Zones.size()-1;
              curr_zone = Gyr_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region], Gyr_Zones[selected_zone]);
              break;
            case 8:
              if(selected_zone >= Hingashi_Zones.size()) selected_zone = Hingashi_Zones.size()-1;
              curr_zone = Hingashi_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region], Hingashi_Zones[selected_zone]);
              break;
            case 9:
              if(selected_zone >= Othard_Zones.size()) selected_zone = Othard_Zones.size()-1;
              curr_zone = Othard_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region],Othard_Zones[selected_zone]);
              break;
            case 10:
              if(selected_zone >= Eureka_Zones.size()) selected_zone = Eureka_Zones.size()-1;
              curr_zone = Eureka_Zones[selected_zone];
              forecasts = weather_forecast(Regions[selected_region],Eureka_Zones[selected_zone]);
              break;
            default:
              curr_zone = LN_Zones[0];
              forecasts = weather_forecast("La Nocea", "Limsa Lominsa");
          }
          return window(text("FFXIV Weather Forecast"), container->Render());
      });

  screen.Loop(renderer);
  
  return EXIT_SUCCESS;
}
