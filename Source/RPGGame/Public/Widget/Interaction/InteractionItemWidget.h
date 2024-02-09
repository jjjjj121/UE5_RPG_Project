// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "InteractionItemWidget.generated.h"

class UW_KeyTutorial;
class UInteractionWidget;

/**
 * 
 */
UCLASS()
class RPGGAME_API UInteractionItemWidget : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public:
	void SetInteractionItem(const FVector& Location, const FName& ActorName);

	UFUNCTION()
	void OnVisibility(ESlateVisibility InVisibility);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_InteractActorName;

public:
	TWeakObjectPtr<UW_KeyTutorial> KeyTutorial;

	TWeakObjectPtr<UInteractionWidget> ParentWidget;
};
