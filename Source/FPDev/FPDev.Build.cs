/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).

This code based on work under 
Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
*/

using UnrealBuildTool;

public class FPDev : ModuleRules
{
	public FPDev(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayTasks" });
	}
}
