// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RPGGame : ModuleRules
{
	public RPGGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "GameplayTasks", "NavigationSystem" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});
    }
}
