// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AIPracticeProject : ModuleRules
{
	public AIPracticeProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "GameplayTasks" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput",
			"NavigationSystem"
		});
	}
}
