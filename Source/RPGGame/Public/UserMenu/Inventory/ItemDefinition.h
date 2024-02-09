// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGame/EnumHeader.h"
#include "RPGGame/Structs.h"
#include "ItemDefinition.generated.h"

class UItemInstance;

/*Item Type�� �����ϴ� Ŭ����*/
/*DefaultToInstanced : �ν��Ͻ�ȭ / EditInlineNew : Editor Property â���� ���� ���� / Abstract : �߻� �⺻ Ŭ������ ����(������ �߰� ����)*/
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class UItemFragment : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnInstanceCreated(UItemInstance* _Instance) const { }
	virtual bool OnUseItem(UItemInstance* _Instance) const { UE_LOG(LogTemp, Log, TEXT("UItemFragment_OnUseItem")); return false; }
};


/*Item State, Property ���� �����͸� �����ϴ� Ŭ����*/
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
