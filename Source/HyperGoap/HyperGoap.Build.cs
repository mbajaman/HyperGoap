// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HyperGoap : ModuleRules
{
	public HyperGoap(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"Slate",
			"SlateCore",
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput", 
			"ProceduralMeshComponent",
			"AIModule",
		});
	}
}
