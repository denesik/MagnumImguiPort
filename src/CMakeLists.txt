# Build library
file(GLOB ImGui_SRC "../imgui/*.cpp")

add_library(MagnumImGui MagnumImGui.cpp ${ImGui_SRC})

file(GLOB include_files . "*.h" "../imgui/*.h")
install(TARGETS MagnumImGui DESTINATION "lib/")
install(FILES ${include_files} DESTINATION "include/MagnumImGui")

# Build exmaple

add_executable(Example Example.cpp)

target_link_libraries(Example
  Magnum::Application
  Magnum::Magnum
  Magnum::Shaders
  MagnumImGui)
