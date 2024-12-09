// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AiTestSample : ModuleRules
{
	public AiTestSample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput"
		,"GameplayTasks", "UMG", "Slate", "SlateCore", "Paper2D"});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
