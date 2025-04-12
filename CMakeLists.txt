cmake_minimum_required (VERSION 3.11)
 
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_Declare(ftxui-image-view
  GIT_REPOSITORY https://github.com/ljrrjl/ftxui-image-view
  GIT_TAG master
)
FetchContent_MakeAvailable(ftxui ftxui-image-view)

add_library(ffxiv_weather include/weather.h src/weather.cpp)

project(ffxiv-wtui LANGUAGES CXX VERSION 1.0.0)
add_executable(ffxiv-wtui src/TUI.cpp)
target_link_libraries(ffxiv-wtui
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  ffxiv_weather
  ftxui-image-view
)
