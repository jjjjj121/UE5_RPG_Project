// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Library/WidgetEnumLibrary.h"
#include "RPGUserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API URPGUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	EWidgetLayoutType LayoutType;

	bool bOnlyUIControl = false;
	bool bUseCursor = false;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void InputBindEvents();
	virtual void InputUnbindEvents();

public:
	virtual void SetMousePosition();

public:
	UFUNCTION(BlueprintPure, Category = "Widget")
	EWidgetLayoutType GetLayoutType() const { return LayoutType; }

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetWidgetLayout(EWidgetLayoutType NewLayoutType) { LayoutType = NewLayoutType; }

#pragma region Input
protected:
	virtual void OnDefaultKeyUp() { UE_LOG(LogTemp, Warning, TEXT("OnDefaultKeyUp")); }
	virtual void OnDefaultKeyDown() { UE_LOG(LogTemp, Warning, TEXT("OnDefaultKeyDown")); }
	virtual void OnDefaultKeyLeft() { UE_LOG(LogTemp, Warning, TEXT("OnDefaultKeyLeft")); }
	virtual void OnDefaultKeyRight() { UE_LOG(LogTemp, Warning, TEXT("OnDefaultKeyRight")); }
	virtual void OnDefaultKeyOkay() { UE_LOG(LogTemp, Warning, TEXT("OnDefaultKeyOkay")); }
	virtual void OnDefaultKeyCancel() { UE_LOG(LogTemp, Warning, TEXT("OnDefaultKeyCancel")); }
	virtual void OnDefaultKeyTab() { UE_LOG(LogTemp, Warning, TEXT("OnDefaultKeyTab")); }

#pragma endregion
};
