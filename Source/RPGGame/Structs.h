#pragma once

#include "Engine/DataTable.h"
#include "EnumHeader.h"
#include "Public/MonsterData.h"
#include "Animation/AnimInstance.h"

#include "Structs.generated.h"

USTRUCT(BlueprintType)
struct FRPGPlayerState : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		int32 Level = 1;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float MaxHP = 100;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float MaxMP;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float CurHP = 100;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float CurMP;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float Damage = 10;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float STR = 10;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float DEX = 10;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float INT = 10;
};
USTRUCT(BlueprintType)
struct FWidgetData : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName WidgetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> WidgetClass;
};

USTRUCT(BlueprintType)
struct FRootArrayData {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RootItemID;
		//TSubclassOf<class UItemDefinition> RootItemclass;

	/*���̽� ���� ������ ���ۼ�Ʈ Ȯ���� ���Ȯ�� �� ������*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DropRate;

	/*���� ������ ���� ���� - �� �� ����������*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 RollDice = 1;

	int32 ItemNum = 0;
};

USTRUCT(BlueprintType)
struct FMonsterAnim {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		int32 MaxCombo;

	UPROPERTY(EditAnywhere)
		UAnimMontage* Basic_Hit_Reaction_Montages;

	UPROPERTY(EditAnywhere)
		UAnimMontage* Charged_Hit_Reaction_Montages;

	UPROPERTY(EditAnywhere)
		UAnimMontage* Death_Reaction_Montages;
};

USTRUCT(BlueprintType)
struct FItemTable : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
	TSubclassOf<class UItemDefinition> ItemDef;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
	TSubclassOf<class UEquipmentDefinition> EquipDef;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
	class UPrimaryDataAsset* AnimationData;

public:
	FItemTable() {
		Init();
	}

	void Init() {
		ItemDef = nullptr;
		EquipDef = nullptr;
		AnimationData = nullptr;
	}
};



USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		UStaticMesh* ItemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		EItemGrade ItemGrade;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		EItemCategoryType Category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		FString Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemInfo)
		class UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		float BuyPrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		float SellPrice;

	//������ �״� �������? (�Ҹ�ǰ, ��� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		bool IsStack;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Fragment)
	//	TArray<TSubclassOf<class UItemFragment>> Fragments;

	/*Equip������ �߰��� �͵�*/

	/*EquipDefinition���� �ű���*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		EEquipCategoryType EquipCategory;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float STRlimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float DEXlimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float INTlimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float RepairPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		int32 ItemSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		bool IsDualWield;

	/*Consume Property*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Consume)
		float ModifierValue;


public:
	FItemData() {
		Init();
	}

	void Init() {
		ItemName = "No Name";
		ItemGrade = EItemGrade::Common;
		Category = EItemCategoryType::SPECIAL;
		Description = "No Description";
		ItemIcon = nullptr;

		BuyPrice = 0;
		SellPrice = 0;

		IsStack = true;

		EquipCategory = EEquipCategoryType::NONE;

		ItemMesh = nullptr;

		Damage = 0;
		Defence = 0;
		STRlimit = 0;
		DEXlimit = 0;
		INTlimit = 0;

		RepairPrice = 0;

		ItemSkill = 0;
		IsDualWield = 0;

	}
};

//Monster Table
USTRUCT()
struct FMonsterTable : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

public:
	//Monster ID Code
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString D_MonsterID;

	//MonsterName
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString D_MonsterName;

	//Monster Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 D_Level;

	//Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* MonsterMesh;

	//Anim Instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UAnimInstance> MonsterAnimInstance;

	//AI Controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AAIController> MonsterAIController;

	////Attack Behavior
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	TSubclassOf<UAttackBehavior> Attack_Behavior;

	//TEST PROPERTY (Attack_Behavior �ȿ� React �ִϸ��̼��� ���̺��� �������ְ� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMonsterAnim MonsterAnimation;

	//Icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* MonsterIcon;

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

	//�߰�ȿ�� (���� �Ǵ� ����� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Skill;

	//���� ����ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Experience;

	//Drop Item List
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FRootArrayData> RootArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxRootItemNum;


	//+���Ϳ� ���� �ִϸ��̼�?
	//+ AI����
};