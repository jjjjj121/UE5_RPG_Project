// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGame/EnumHeader.h"
#include "RPGGame/Structs.h"
#include "ItemDefinition.generated.h"

class UItemInstance;

/*Item Type을 정의하는 클래스*/
/*DefaultToInstanced : 인스턴스화 / EditInlineNew : Editor Property 창에서 생성 가능 / Abstract : 추상 기본 클래스로 선언(레벨에 추가 방지)*/
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class UItemFragment : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnInstanceCreated(UItemInstance* _Instance) const { }
	virtual bool OnUseItem(UItemInstance* _Instance) const { UE_LOG(LogTemp, Log, TEXT("UItemFragment_OnUseItem")); return false; }
};


/*Item State, Property 등의 데이터를 정의하는 클래스*/
UCLASS(Blueprintable, Const, Abstract)
class RPGGAME_API UItemDefinition : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = ItemInfo)
	FItemData ItemData;

public:
	UPROPERTY(EditDefaultsOnly, Category = Fragment, Instanced)
		TArray<UItemFragment*> Fragments;

public:
	UItemDefinition();

	FORCEINLINE FItemData GetItemData() { return ItemData; }
	//void SetItemData(FItemData NewItemData);

	const UItemFragment* FindFragmentByClass(TSubclassOf<UItemFragment> _FragmentClass) const;
};
