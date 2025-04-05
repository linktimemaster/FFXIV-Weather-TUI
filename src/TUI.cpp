#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "image_view.hpp"
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include "../include/weather.h"

using namespace ftxui;

Component Window(std::string title, Component component) {
  return Renderer(component, [component, title] {
    return window(text(title), component->Render());
  });
}

int main(void) {

  //std::ifstream ifs ("../icons/umbral_wind.ans");
  std::ifstream ifs ("../ascii-art.txt");
  std::string uw = {std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>{}};
  
  std::vector<std::string> Regions{
    "La Noscea",
    "Thanalan",
    "The Black Shroud",
    "Mor Dhona",
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

  auto tabs = Container::Tab(
      {
        Window("La Nocea Zones",Radiobox(&LN_Zones,&selected_zone)),
        Window("Thanalan Zones",Radiobox(&Than_Zones,&selected_zone)),
        Window("The Black Shroud Zones",Radiobox(&BS_Zones,&selected_zone)),
        Window("Mor Dhona Zone",Radiobox(&Mor_Zones,&selected_zone)),
      },
      &selected_region);
  
  auto screen = ScreenInteractive::Fullscreen();

  //auto middle = Renderer([&] { return paragraph(uw) | center; });
  //auto middle = Renderer([&] { return text("Selected Region: " + Regions[selected_region]) | center; });
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
    default:
      curr_zone = LN_Zones[0];
      forecasts = weather_forecast("La Nocea", "Limsa Lominsa");
  }
  auto h_container = Container::Horizontal({
    tabs,
    Renderer([&]{ return text(forecasts[1]) | center | flex; }),
  });
  auto container = Container::Vertical({ 
      Renderer([&]{
        std::string img_path = forecasts[0];    
        std::transform(img_path.begin(), img_path.end(), img_path.begin(), [](char ch) {
          return ch == ' ' ? '_' : ch;
        });
        img_path = "../FFXIV_Weather_Icons/" + img_path + "_icon.webp";
        return hflow({
          window(text(forecasts[0]),image_view(img_path)) | size(WIDTH, LESS_THAN, 65),// | size(HEIGHT, EQUAL, 20),
          text("The weather in " + curr_zone + ", " + Regions[selected_region] + " is " + forecasts[0]) | center | flex
        }); 
      }),
      h_container,
  });
  int left_size = 20;
  auto left = Window("Regions", region_menu);
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
            default:
              curr_zone = LN_Zones[0];
              forecasts = weather_forecast("La Nocea", "Limsa Lominsa");
          }
          return window(text("FFXIV Weather Forcast"), container->Render());
      });

  screen.Loop(renderer);
  
  return EXIT_SUCCESS;
}
