// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TranslucentMaterialLightRay/Public/TMLR_CaptureCube.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTMLR_CaptureCube() {}
// Cross Module References
	TRANSLUCENTMATERIALLIGHTRAY_API UClass* Z_Construct_UClass_ATMLR_CaptureCube_NoRegister();
	TRANSLUCENTMATERIALLIGHTRAY_API UClass* Z_Construct_UClass_ATMLR_CaptureCube();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_TranslucentMaterialLightRay();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneCaptureComponentCube_NoRegister();
// End Cross Module References
	void ATMLR_CaptureCube::StaticRegisterNativesATMLR_CaptureCube()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATMLR_CaptureCube);
	UClass* Z_Construct_UClass_ATMLR_CaptureCube_NoRegister()
	{
		return ATMLR_CaptureCube::StaticClass();
	}
	struct Z_Construct_UClass_ATMLR_CaptureCube_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SceneComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SceneComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CaptureComponentCube_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CaptureComponentCube;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATMLR_CaptureCube_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_TranslucentMaterialLightRay,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATMLR_CaptureCube_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "TMLR_CaptureCube.h" },
		{ "ModuleRelativePath", "Public/TMLR_CaptureCube.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_SceneComponent_MetaData[] = {
		{ "Category", "TMLR_CaptureCube" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TMLR_CaptureCube.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_SceneComponent = { "SceneComponent", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATMLR_CaptureCube, SceneComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_SceneComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_SceneComponent_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_CaptureComponentCube_MetaData[] = {
		{ "Category", "TMLR_CaptureCube" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TMLR_CaptureCube.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_CaptureComponentCube = { "CaptureComponentCube", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATMLR_CaptureCube, CaptureComponentCube), Z_Construct_UClass_USceneCaptureComponentCube_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_CaptureComponentCube_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_CaptureComponentCube_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATMLR_CaptureCube_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_SceneComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATMLR_CaptureCube_Statics::NewProp_CaptureComponentCube,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATMLR_CaptureCube_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATMLR_CaptureCube>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATMLR_CaptureCube_Statics::ClassParams = {
		&ATMLR_CaptureCube::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ATMLR_CaptureCube_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ATMLR_CaptureCube_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATMLR_CaptureCube_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATMLR_CaptureCube_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATMLR_CaptureCube()
	{
		if (!Z_Registration_Info_UClass_ATMLR_CaptureCube.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATMLR_CaptureCube.OuterSingleton, Z_Construct_UClass_ATMLR_CaptureCube_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATMLR_CaptureCube.OuterSingleton;
	}
	template<> TRANSLUCENTMATERIALLIGHTRAY_API UClass* StaticClass<ATMLR_CaptureCube>()
	{
		return ATMLR_CaptureCube::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATMLR_CaptureCube);
	struct Z_CompiledInDeferFile_FID_RealisticRendering_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_CaptureCube_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RealisticRendering_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_CaptureCube_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATMLR_CaptureCube, ATMLR_CaptureCube::StaticClass, TEXT("ATMLR_CaptureCube"), &Z_Registration_Info_UClass_ATMLR_CaptureCube, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATMLR_CaptureCube), 2075239731U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RealisticRendering_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_CaptureCube_h_2359513037(TEXT("/Script/TranslucentMaterialLightRay"),
		Z_CompiledInDeferFile_FID_RealisticRendering_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_CaptureCube_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RealisticRendering_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_CaptureCube_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
