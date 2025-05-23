// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CaptureTheFlag : ModuleRules
{
	public CaptureTheFlag(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTasks",
			"UMG",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		// Essa definição é fundamental para o uso da macro CTFGAME_API funcionar corretamente
		PublicDefinitions.Add("CTFGAME_API=DLLEXPORT");
	}
}