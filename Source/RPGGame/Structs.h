#pragma once

#include "Engine/DataTable.h"
#include "EnumHeader.h"
#include "Public/MonsterData.h"
#include "Structs.generated.h"


USTRUCT(BlueprintType)
struct FRootArrayData {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AItem> RootItemclass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DropRate;
};


USTRUCT()
struct FEquipItemTable : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

public:
	//Monster ID Code
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
		UMonsterData* DataAsset;



	//+���Ϳ� ���� �ִϸ��̼�?
	//+ AI����
};