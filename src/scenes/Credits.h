#include "raylib.h"
#include "tools/tools.h"
#include "tools/Buttons.h"
#include "tools/Cursor.h"

#include "scenes/SceneSetter.h"

static bool isCreditsButtonsCreated = false;
static bool CreditsRosurcesLoaded = false;

void CreditsScene();

void UpdateCredits();

void DrawCredits();

void CreateButtonsCredits();

void LoadResourcesCredits();

void UnloadResourcesCredits();