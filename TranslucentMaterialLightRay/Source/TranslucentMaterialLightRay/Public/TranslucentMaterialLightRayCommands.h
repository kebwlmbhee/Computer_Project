// Copyright:       Copyright (C) 2022 kebwlmbhee

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TranslucentMaterialLightRayStyle.h"

class FTranslucentMaterialLightRayCommands : public TCommands<FTranslucentMaterialLightRayCommands>
{
public:

	FTranslucentMaterialLightRayCommands()
		: TCommands<FTranslucentMaterialLightRayCommands>(TEXT("TranslucentMaterialLightRay"), NSLOCTEXT("Contexts", "TranslucentMaterialLightRay", "TranslucentMaterialLightRay Plugin"), NAME_None, FTranslucentMaterialLightRayStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
