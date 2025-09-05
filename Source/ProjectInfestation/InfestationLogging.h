// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// General Log
PROJECTINFESTATION_API DECLARE_LOG_CATEGORY_EXTERN(LogInfestation, Log, All);

// Logging during game startup
PROJECTINFESTATION_API DECLARE_LOG_CATEGORY_EXTERN(LogInfestationInit, Log, All);

// Logging for your AI system
PROJECTINFESTATION_API DECLARE_LOG_CATEGORY_EXTERN(LogInfestationAISystem, Log, All);

// Logging for Critical Errors that must always be addressed
PROJECTINFESTATION_API DECLARE_LOG_CATEGORY_EXTERN(LogInfestationCriticalError, Log, All);
