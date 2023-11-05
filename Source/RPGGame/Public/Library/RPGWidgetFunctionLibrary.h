// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGWidgetFunctionLibrary.generated.h"

/**
 * 
 */


UCLASS()
class RPGGAME_API URPGWidgetFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject"), Category = "Widget")
		static URPGUserWidgetBase* PushWidget(UObject* WorldContextObject, FName WidgetName, EWidgetLayoutType LayoutType);

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject"), Category = "Widget")
		static URPGUserWidgetBase* PopWidget(UObject* WorldContextObject, FName WidgetName, EWidgetLayoutType LayoutType);

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject"), Category = "Widget")
		static void VisibilityLayout(UObject* WorldContextObject, EWidgetLayoutType LayoutType, ESlateVisibility Visibility);

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject"), Category = "Widget")
		static void ExecuteWidgetSingle(UObject* WorldContextObject, FName WidgetName, FName FunctionName, FWidgetParam WidgetParam);

	UFUNCTION(BlueprintPure, Meta = (WorldContext = "WorldContextObject"), Category = "Widget")
		static URPGUserWidgetBase* GetWidgetWithLayoutType(UObject* WorldContextObject, EWidgetLayoutType LayoutType, FName WidgetName);


};
