#pragma once
#include "raylib.h"
#include "tools/tools.h"
#include "tools/Cursor.h"
#include "tools/Timer.h"

#include "scenes/SceneSetter.h"

static bool SplashScreenRosurcesLoaded = false;
static bool firstPhase = true;
static Color SplashScreenColor;
static int timesEndTimer = 0;

void SplashScreenScene();

void UpdateSplashScreen();

void DrawSplashScreen();

void LoadTextureSplashScreen();