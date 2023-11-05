// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/WidgetEnumLibrary.h"
#include "Library/WidgetStructLibrary.h"
#include "RPGWidgetSubSystem.generated.h"

class ULayoutWidget;

/*Subsystem�� ���� ������ �����ǰ� �� �̻� ������ ���� ��� ������ �÷����� �Ǿ� �����ȴ�.
Game Instance Subsystem�� Game Instance�� ������ ������ ������ ������ ���� ���ݿ� �ʿ��� ����� �����ϴµ� �����ϴ�
Game Instance�� ���� ������ �����ϴ� �����̱� ������ �μ����� ���� ����� Subsystem ���� �����Ѵ�.*/

UCLASS()
class RPGGAME_API URPGWidgetSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/*Game Instance ���� ����, Subsystem �ν��Ͻ� ����*/
	URPGWidgetSubSystem();

protected:
	/*Game Instance �ʱ�ȭ �� ȣ��*/
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	/*Game Instance ���� �� ȣ��*/
	virtual void Deinitialize() override;

public:
	UFUNCTION(BlueprintPure, Category = "Widget")
		URPGUserWidgetBase* SpawnRPGWidget(FName WidgetName);

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject"), Category = "Widget")
		URPGUserWidgetBase* PushWidget(FName WidgetName, EWidgetLayoutType LayoutType);

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject"), Category = "Widget")
		URPGUserWidgetBase* PopWidget(FName WidgetName, EWidgetLayoutType LayoutType);

	UFUNCTION(BlueprintPure, Category = "Widget")
		URPGUserWidgetBase* GetWidgetWithLayoutType(EWidgetLayoutType LayoutType, FName WidgetName);

	/*Widget Function ȣ�� �Լ�*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void ExecuteWidgetSingle(FName WidgetName, FName FunctionName, FWidgetParam WidgetParam);





	UFUNCTION(BlueprintCallable, Category = "Widget|Option")
		void VisibilityLayout(EWidgetLayoutType LayoutType, ESlateVisibility Visibility);

private:
	void CreateWidgetLayout();
	void DestroyWidgetLayout();

	bool ExecuteWidget(URPGUserWidgetBase* Widget, UFunction* Function, FWidgetParam WidgetParam);

private:
	TMap<EWidgetLayoutType, ULayoutWidget*> WidgetLayout;

	bool bCreatedWidgetLayout = false;


#pragma region Push Widget Queue
private:
	struct FPushWidgetQueue {
		FPushWidgetQueue(FName _WidgetName, EWidgetLayoutType _LayoutType) : WidgetName(_WidgetName), LayoutType(_LayoutType) {}

	public:
		FName WidgetName;
		EWidgetLayoutType LayoutType;

	public:
		/*Remove �Լ� ����� ���� == �� �������� �ʿ䰡 ����*/
		bool operator == (const FPushWidgetQueue& OtherPushWidgetQueue)
		{
			return LayoutType == OtherPushWidgetQueue.LayoutType &&
				WidgetName == OtherPushWidgetQueue.WidgetName;
		}

	};

	TArray<FPushWidgetQueue> PushWidgets;

#pragma endregion

};
