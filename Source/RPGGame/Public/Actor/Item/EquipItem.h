// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/Item.h"
#include "EquipItem.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AEquipItem : public AItem
{
	GENERATED_BODY()


public:
	AEquipItem();
	
public:

	//Item ID Code
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString D_ItemID;

	//ItemName
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString D_ItemName;

	//Item ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemGrade D_ItemGrade;

	//ItemType
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType D_ItemType;

	//Level ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 D_Levellimit;

	//class
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class AItem> ItemClass;

	//Mesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* ItemMesh;

	//Icon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UTexture2D* ItemIcon;

	//MAXHP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_MAXHP;

	//MAXMP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_MAXMP;

	//���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Damage;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Defence;

	//��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_STRlimit;

	//��ø
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_DEXlimit;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_INTlimit;

	//Buy Price
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_BuyPrice;

	//Sell Price
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_SellPrice;

	//Repair Price
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_RepairPrice;

	//�߰�ȿ�� (���� �Ǵ� ����� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_ItemSkill;

	//��� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool D_IsDualWield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UAttackBehavior> D_AttackBehavior;

public:
	virtual void BeginPlay() override;
	
private:
	void InitProperty(FName RowName);
};
