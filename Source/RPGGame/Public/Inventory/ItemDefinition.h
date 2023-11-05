// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGame/EnumHeader.h"
#include "ItemDefinition.generated.h"


/*Item Type�� �����ϴ� Ŭ����*/
UCLASS()
class UItemFragment : public UObject
{
	GENERATED_BODY()

};


/*Item State, Property ���� �����͸� �����ϴ� Ŭ����*/
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

	//Item ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemGrade ItemGrade;

	//Category
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemCategoryType Category;

	//Level ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Levellimit;

	//Item ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;

	//Mesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* ItemMesh;

	//Icon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UTexture2D* ItemIcon;

	//���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Defence;

	//��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float STRlimit;

	//��ø
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DEXlimit;

	//����
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

	//�߰�ȿ�� (���� �Ǵ� ����� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ItemSkill;

	//��� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsDualWield;

	//������ �״� �������? (�Ҹ�ǰ, ��� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsStack;

	UPROPERTY(EditDefaultsOnly, Category = ItemInfo)
		TSubclassOf<class UAttackBehavior> D_AttackBehavior;

	UPROPERTY(EditDefaultsOnly, Category = Fragment, Instanced)
		TArray<UItemFragment*> Fragments;

public:
	UItemDefinition();


};
