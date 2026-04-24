#pragma once
#include "Engine/Window/Window.hpp"
#include "Engine/Renderer/Renderer.hpp"


void ImGuiStartup(Window* window, Renderer* renderer);
void ImGuiBeginFrame();
void ImGuiEndFrame();
void ImGuiShutDown();