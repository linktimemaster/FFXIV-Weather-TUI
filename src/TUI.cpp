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
  return Renderer(component, [component, title] {  //
  return window(text(title), component->Render()) | flex;
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
  };
  int selected_region = 0;
  
  auto region_menu = Menu(&Regions, &selected_region);

  auto screen = ScreenInteractive::Fullscreen();

  //auto middle = Renderer([&] { return paragraph(uw) | center; });
  auto middle = Renderer([&] { return text("Selected Region: " + Regions[selected_region]) | center; });
  auto left = Window("Regions", region_menu);
  auto container = middle;
  int left_size = 20;
  container = ResizableSplitLeft(left, container, &left_size);
  auto renderer =
      Renderer(container, [&] { return window(text("FFXIV Weather Forcast"), container->Render()); });

  screen.Loop(renderer);
  
  return EXIT_SUCCESS;
}
