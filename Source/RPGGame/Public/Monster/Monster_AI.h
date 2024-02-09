// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGGame/Structs.h"
#include "RPGGame/Public/Interface/InteractionInterface.h"
#include "Monster_AI.generated.h"

struct FRootArrayData;

UCLASS()
class RPGGAME_API AMonster_AI : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster_AI();

public:
	//Monster ID Code
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MonsterID;

	//MonsterName
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MonsterName;

	//Monster Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Level;

	//Mesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* MonsterMesh;

	//Icon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UTexture2D* MonsterIcon;

	//MAXHP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MAXHP;

	//MAXMP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MAXMP;

	//공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	//방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Defence;

	//추가효과 (버프 또는 디버프 같은 것)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Skill;

	//제공 경험치
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Experience;

	//Drop Item List
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FRootArrayData> RootArray;

	//Anim Instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMonsterAnimInstance* MonsterAnimInstance;

	//AI Controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMonsterAIController* AI_Controller;

private:

	float CurHP;
	float CurMP;

	bool IsDead = false;

	TArray<UItemInstance*> RootItems;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when Overlap Actor
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	void SetUnit(class UDataTable* MonsterTable, FName MonsterName_);
	void SetMontage_Lamda();
	void DropItem();
	int32 CalculateDirectionIndex(float Direction);
	void HitReaction(int32 SectionIndex, bool IsCharged);

	/*Animation*/
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
		bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
		int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
		bool IsComboInputOn;

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
		void OnReactMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/*Start Combo -> Set Property*/
	void AttackStartComboState();
	/*End Combo -> Init Property*/
	void AttackEndComboState();

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
		bool CanNextCombo;
public:
	void Attack();
	void InitAttack();
	bool GetIsAttacking();

	bool bRunningHit = false;
protected:
	//Apply Damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SetRootItems();
	void SetRagdollPhysics();

	/*Interaction Interface*/
public:
	virtual bool IsAvailableInteraction_Implementation() const override;
	virtual bool ExecuteInteraction_Implementation(AActor* InteractionTarget, UItemInstance* NewItemInstance) override;
	virtual void StopInteration_Implementation(AActor* InteractionTarget) override;
	virtual void SetTouchActor_Implementation(AActor* NewTouchActor) override;
	virtual TArray<UItemInstance*> GetRootItemList_Implementation() override;
	virtual FName GetInteractionActorName_Implementation() override;
	virtual FVector GetInteractionWidgetLocation_Implementation() override;

};
