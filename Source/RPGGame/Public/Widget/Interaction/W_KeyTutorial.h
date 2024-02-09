// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "Library/WidgetStructLibrary.h"
#include "W_KeyTutorial.generated.h"

class UTextBlock;
class UInteractionWidget;
/**
 * 
 */
UCLASS()
class RPGGAME_API UW_KeyTutorial : public URPGUserWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void SetTutorialText(FString Key, FString Description);

	void PlayShowAnim(bool IsForward);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TB_Key;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TB_Description;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ShowAnim;

public:
	TWeakObjectPtr<UInteractionWidget> ParentWidget;
};
