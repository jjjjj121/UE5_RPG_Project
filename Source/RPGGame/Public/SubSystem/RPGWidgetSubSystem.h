// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/WidgetEnumLibrary.h"
#include "Library/WidgetStructLibrary.h"
#include "RPGWidgetSubSystem.generated.h"

class ULayoutWidget;

/*Subsystem에 대한 참조가 삭제되고 더 이상 참조가 없는 경우 가비지 컬렉션이 되어 관리된다.
Game Instance Subsystem은 Game Instance와 유사한 수명을 가지기 때문에 게임 전반에 필요한 기능을 정의하는데 적합하다
Game Instance는 게임 전반을 관리하는 목적이기 때문에 부수적인 세부 기능은 Subsystem 에서 정의한다.*/

UCLASS()
class RPGGAME_API URPGWidgetSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/*Game Instance 생성 이후, Subsystem 인스턴스 생성*/
	URPGWidgetSubSystem();

protected:
	/*Game Instance 초기화 시 호출*/
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	/*Game Instance 종료 시 호출*/
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

	/*Widget Function 호출 함수*/
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
		/*Remove 함수 사용을 위해 == 를 재정의할 필요가 있음*/
		bool operator == (const FPushWidgetQueue& OtherPushWidgetQueue)
		{
			return LayoutType == OtherPushWidgetQueue.LayoutType &&
				WidgetName == OtherPushWidgetQueue.WidgetName;
		}

	};

	TArray<FPushWidgetQueue> PushWidgets;

#pragma endregion

};
