// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TranslucentMaterialLightRay/Public/TMLR_Actor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTMLR_Actor() {}
// Cross Module References
	TRANSLUCENTMATERIALLIGHTRAY_API UClass* Z_Construct_UClass_ATMLR_Actor_NoRegister();
	TRANSLUCENTMATERIALLIGHTRAY_API UClass* Z_Construct_UClass_ATMLR_Actor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_TranslucentMaterialLightRay();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
// End Cross Module References
	void ATMLR_Actor::StaticRegisterNativesATMLR_Actor()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATMLR_Actor);
	UClass* Z_Construct_UClass_ATMLR_Actor_NoRegister()
	{
		return ATMLR_Actor::StaticClass();
	}
	struct Z_Construct_UClass_ATMLR_Actor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_GenerateSceneCaptureMaterial_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GenerateSceneCaptureMaterial_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_GenerateSceneCaptureMaterial;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATMLR_Actor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_TranslucentMaterialLightRay,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATMLR_Actor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "TMLR_Actor.h" },
		{ "ModuleRelativePath", "Public/TMLR_Actor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATMLR_Actor_Statics::NewProp_GenerateSceneCaptureMaterial_Inner = { "GenerateSceneCaptureMaterial", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATMLR_Actor_Statics::NewProp_GenerateSceneCaptureMaterial_MetaData[] = {
		{ "Category", "GenerateSceneCaptureMaterial" },
		{ "Comment", "// Add AActor from level to Array\n" },
		{ "ModuleRelativePath", "Public/TMLR_Actor.h" },
		{ "ToolTip", "Add AActor from level to Array" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ATMLR_Actor_Statics::NewProp_GenerateSceneCaptureMaterial = { "GenerateSceneCaptureMaterial", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATMLR_Actor, GenerateSceneCaptureMaterial), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ATMLR_Actor_Statics::NewProp_GenerateSceneCaptureMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATMLR_Actor_Statics::NewProp_GenerateSceneCaptureMaterial_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATMLR_Actor_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATMLR_Actor_Statics::NewProp_GenerateSceneCaptureMaterial_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATMLR_Actor_Statics::NewProp_GenerateSceneCaptureMaterial,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATMLR_Actor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATMLR_Actor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATMLR_Actor_Statics::ClassParams = {
		&ATMLR_Actor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ATMLR_Actor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ATMLR_Actor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATMLR_Actor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATMLR_Actor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATMLR_Actor()
	{
		if (!Z_Registration_Info_UClass_ATMLR_Actor.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATMLR_Actor.OuterSingleton, Z_Construct_UClass_ATMLR_Actor_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATMLR_Actor.OuterSingleton;
	}
	template<> TRANSLUCENTMATERIALLIGHTRAY_API UClass* StaticClass<ATMLR_Actor>()
	{
		return ATMLR_Actor::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATMLR_Actor);
	struct Z_CompiledInDeferFile_FID_HostProject_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_Actor_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_Actor_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATMLR_Actor, ATMLR_Actor::StaticClass, TEXT("ATMLR_Actor"), &Z_Registration_Info_UClass_ATMLR_Actor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATMLR_Actor), 3917759811U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_Actor_h_732867025(TEXT("/Script/TranslucentMaterialLightRay"),
		Z_CompiledInDeferFile_FID_HostProject_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_Actor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_HostProject_Plugins_TranslucentMaterialLightRay_Source_TranslucentMaterialLightRay_Public_TMLR_Actor_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
