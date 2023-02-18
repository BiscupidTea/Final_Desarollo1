#pragma once
#include "raylib.h"
#include "tools/tools.h"
#include "tools/Buttons.h"
#include "tools/Cursor.h"

#include "scenes/SceneSetter.h"

static bool isOptionsButtonsCreated = false;
static bool OptionsRosurcesLoaded = false;

void OptionsScene();

void UpdateOptions();

void DrawOptions();

void DrawVolumeOptions();

void CreateButtonsOptions();

void LoadResourcesOptions();

void UnloadResourcesOptions();