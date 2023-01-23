#pragma once
#include "raylib.h"
#include "tools/tools.h"
#include "tools/Buttons.h"

#include "scenes/SceneSetter.h"
#include "Game.h"

static bool isButtonsCreated = false;

void MenuScene();

void UpdateMenu();

void DrawMenu();

void CreateButtons();