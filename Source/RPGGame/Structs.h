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

	//Item 등급
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemGrade D_ItemGrade;

	//ItemType
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType D_ItemType;

	//Level 제한
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

	//공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Damage;

	//방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Defence;

	//힘
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_STRlimit;

	//민첩
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_DEXlimit;

	//지능
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

	//추가효과 (버프 또는 디버프 같은 것)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_ItemSkill;

	//양손 잡이인지
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

	//공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Damage;

	//방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Defence;

	//추가효과 (버프 또는 디버프 같은 것)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Skill;

	//제공 경험치
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float D_Experience;

	//Drop Item List
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FRootArrayData> RootArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMonsterData* DataAsset;



	//+몬스터에 따른 애니메이션?
	//+ AI설정
};