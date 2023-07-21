// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGGame/Structs.h"
#include "Monster.generated.h"

UCLASS()
class RPGGAME_API AMonster : public AActor
{
	GENERATED_BODY()
	
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
		USkeletalMesh* ItemMesh;

	//Icon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UTexture2D* ItemIcon;

	//MAXHP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MAXHP;

	//MAXMP
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MAXMP;

	//���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Defence;

	//�߰�ȿ�� (���� �Ǵ� ����� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Skill;

	//���� ����ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Experience;

	//Drop Item List
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FRootArrayData> RootArray;

public:	
	// Sets default values for this actor's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetUnit(UDataTable* MonsterTable, FName MonsterName_);
	void DropItem();

};
