#pragma once

#include <iostream>
#include <cstdint>
#include <Windows.h>


std::uintptr_t game = std::uintptr_t(0);

#include "memory.h"
#include "importer.hpp"
#include "game_miscs.h"
#include "vmthook.h"

#include "settings.h"
#include "sdk.h"
#include "render.h"
#include "ZeroGUI.h"
#include "hooking.h"
