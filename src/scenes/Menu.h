#pragma once
#include "raylib.h"
#include "tools/tools.h"
#include "tools/Buttons.h"
#include "tools/Cursor.h"

#include "scenes/SceneSetter.h"
#include "Game.h"

static bool isButtonsCreated = false;
static bool menuRosurcesLoaded = false;

void MenuScene();

void UpdateMenu();

void DrawMenu();

void CreateButtons();

void LoadResourcesMenu();

void UnloadResourcesMenu();