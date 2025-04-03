#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>

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
  int selected_zone_LN = 0;
  std::vector<std::string> BS_Zones = {
    "Gridania",
    "Central Shroud",
    "East Shroud",
    "South Shroud",
    "North Shroud",
    "The Lavender Beds",
  };
  int selected_zone_BS = 0;
  std::vector<std::string> Than_Zones = {
    "Ul'dah",
    "Western Thanalan",
    "Central Thanalan",
    "Eastern Thanalan",
    "Southern Thanalan",
    "Northern Thanalan",
    "The Goblet",
  };
  int selected_zone_T = 0;
  std::vector<std::string> Mor_Zones = {
    "Mor Dhona",
  };
  int selected_zone_MD = 0;

  auto tabs = Container::Tab(
      {
        Window("La Nocea Zones",Radiobox(&LN_Zones,&selected_zone_LN)),
        Window("Thanalan Zones",Radiobox(&Than_Zones,&selected_zone_T)),
        Window("The Black Shroud Zones",Radiobox(&BS_Zones,&selected_zone_BS)),
        Window("Mor Dhona Zone",Radiobox(&Mor_Zones,&selected_zone_MD)),
      },
      &selected_region);
  
  auto screen = ScreenInteractive::Fullscreen();

  //auto middle = Renderer([&] { return paragraph(uw) | center; });
  //auto middle = Renderer([&] { return text("Selected Region: " + Regions[selected_region]) | center; });
  auto container = Container::Vertical({ 
      Renderer([&]{
        return text("Current Weather goes here") | center,
      }),
      Container::Horizontal({
        tabs,
        Renderer([&]{ return text("Forecast goes here") | center | flex; }),
      }),
    });
  int left_size = 20;
  auto left = Window("Regions", region_menu);
  container = ResizableSplitLeft(left, container, &left_size);
  auto renderer =
      Renderer(container, [&] { return window(text("FFXIV Weather Forcast"), container->Render()); });

  screen.Loop(renderer);
  
  return EXIT_SUCCESS;
}
