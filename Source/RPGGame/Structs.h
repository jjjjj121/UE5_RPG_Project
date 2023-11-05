#pragma once

#include "Engine/DataTable.h"
#include "EnumHeader.h"
#include "Public/MonsterData.h"
#include "Animation/AnimInstance.h"
#include "Structs.generated.h"

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
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	TSubclassOf<class AItem> RootItemclass;

	/*다이스 돌릴 때마다 몇퍼센트 확률로 드랍확정 될 것인지*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DropRate;

	/*개별 아이템 수량 관련 - 몇 번 돌릴것인지*/
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



USTRUCT()
struct FItemData : public FTableRowBase {

	GENERATED_USTRUCT_BODY()

public:
	//Item ID Code
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString D_ItemID;

	//ItemName
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString D_ItemName;

	//Item 등급
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemGrade D_ItemGrade;

	//Category
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemCategoryType D_Category;

	//Level 제한
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 D_Levellimit;

	//class
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//	TSubclassOf<class AItem> ItemClass;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* MonsterMesh;

	//Anim Instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UAnimInstance> MonsterAnimInstance;

	//AI Controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AAIController> MonsterAIController;

	//Attack Behavior
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UAttackBehavior> Attack_Behavior;

	//TEST PROPERTY (Attack_Behavior 안에 React 애니메이션을 테이블에서 설정해주고 싶음)
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
		int32 MaxRootItemNum;
	

	//+몬스터에 따른 애니메이션?
	//+ AI설정
};