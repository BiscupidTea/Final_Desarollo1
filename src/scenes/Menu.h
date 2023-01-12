#pragma once
#include "raylib.h"
#include "tools/tools.h"

#include "scenes/SceneSetter.h"
#include "Game.h"

static bool buttonsCreated = false;
static int totButtons = 5;

struct optionsButtons
{
	Rectangle rectangle;
	Color color;
	bool selected;
};


void MenuScene();

void UpdateMenu(optionsButtons button[]);

void DrawMenu(optionsButtons button[]);

void CreateButtons(optionsButtons button[]);