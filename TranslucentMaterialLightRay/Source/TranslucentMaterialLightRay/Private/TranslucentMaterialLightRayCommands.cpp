// Copyright:       Copyright (C) 2022 kebwlmbhee

#include "TranslucentMaterialLightRayCommands.h"

#define LOCTEXT_NAMESPACE "FTranslucentMaterialLightRayModule"

void FTranslucentMaterialLightRayCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "TranslucentMaterialLightRay", "Execute TranslucentMaterialLightRay action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
