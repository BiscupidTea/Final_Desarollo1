#include "raylib.h"
#include "tools/tools.h"
#include "tools/Buttons.h"
#include "tools/Cursor.h"

#include "scenes/SceneSetter.h"

static bool isCreditsButtonsCreated = false;

void CreditsScene();

void UpdateCredits();

void DrawCredits();

void CreateButtonsCredits();