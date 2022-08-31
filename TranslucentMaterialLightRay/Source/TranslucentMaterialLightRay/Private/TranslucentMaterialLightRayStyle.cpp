// Copyright:       Copyright (C) 2022 kebwlmbhee

#include "TranslucentMaterialLightRayStyle.h"
#include "TranslucentMaterialLightRay.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FTranslucentMaterialLightRayStyle::StyleInstance = nullptr;

void FTranslucentMaterialLightRayStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FTranslucentMaterialLightRayStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FTranslucentMaterialLightRayStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("TranslucentMaterialLightRayStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FTranslucentMaterialLightRayStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("TranslucentMaterialLightRayStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("TranslucentMaterialLightRay")->GetBaseDir() / TEXT("Resources"));

	Style->Set("TranslucentMaterialLightRay.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FTranslucentMaterialLightRayStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FTranslucentMaterialLightRayStyle::Get()
{
	return *StyleInstance;
}
