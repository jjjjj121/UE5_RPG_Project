// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGame/EnumHeader.h"
#include "ItemDefinition.generated.h"


/*Item Type을 정의하는 클래스*/
UCLASS()
class UItemFragment : public UObject
{
	GENERATED_BODY()

};


/*Item State, Property 등의 데이터를 정의하는 클래스*/
UCLASS(Blueprintable, Abstract)
class RPGGAME_API UItemDefinition : public UObject
{
	GENERATED_BODY()
	
public:
	//Item ID Code
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemID;

	//ItemName
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;

	//Item 등급
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemGrade ItemGrade;

	//Category
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemCategoryType Category;

	//Level 제한
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Levellimit;

	//Item 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;

	//Mesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* ItemMesh;

	//Icon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UTexture2D* ItemIcon;

	//공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	//방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Defence;

	//힘
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float STRlimit;

	//민첩
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DEXlimit;

	//지능
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float INTlimit;

	//Buy Price
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BuyPrice;

	//Sell Price
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SellPrice;

	//Repair Price
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RepairPrice;

	//추가효과 (버프 또는 디버프 같은 것)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ItemSkill;

	//양손 잡이인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsDualWield;

	//스택을 쌓는 경우인지? (소모품, 재료 등)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsStack;

	UPROPERTY(EditDefaultsOnly, Category = ItemInfo)
		TSubclassOf<class UAttackBehavior> D_AttackBehavior;

	UPROPERTY(EditDefaultsOnly, Category = Fragment, Instanced)
		TArray<UItemFragment*> Fragments;

public:
	UItemDefinition();


};
