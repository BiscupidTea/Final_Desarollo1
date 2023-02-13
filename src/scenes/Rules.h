#include "raylib.h"
#include "tools/tools.h"
#include "tools/Buttons.h"
#include "tools/Cursor.h"

#include "scenes/SceneSetter.h"

static bool isRulesButtonsCreated = false;
static bool RulesRosurcesLoaded = false;

void RulesScene();

void UpdateRules();

void DrawRules();

void CreateButtonsRules();

void LoadResourcesRules();

void UnloadResourcesRules();