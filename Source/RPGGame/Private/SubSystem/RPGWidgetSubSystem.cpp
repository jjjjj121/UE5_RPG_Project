// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/RPGWidgetSubSystem.h"
#include "System/RPGGameInstance.h"
#include "Widget/LayoutWidget.h"
#include "Blueprint/UserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

URPGWidgetSubSystem::URPGWidgetSubSystem()
{
	UE_LOG(LogTemp, Warning, TEXT("[RPGWidgetSubSystem] URPGWidgetSubSystem() "));
}

void URPGWidgetSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("[RPGWidgetSubSystem] Initialize() "));

	/*다음 틱에 실행 - 이렇게 해야 위젯이 생성됨 생성 주기와 관련된 듯?*/
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &URPGWidgetSubSystem::CreateWidgetLayout);
}

void URPGWidgetSubSystem::Deinitialize()
{
	Super::Deinitialize();

	DestroyWidgetLayout();

	UE_LOG(LogTemp, Warning, TEXT("[RPGWidgetSubSystem] Deinitialize() "));
}

URPGUserWidgetBase* URPGWidgetSubSystem::SpawnRPGWidget(FName WidgetName)
{
	TSubclassOf<URPGUserWidgetBase> WidgetClass = DATATABLE_MANAGER(GetWorld())->GetWidgetClassWithName(WidgetName);
	if (ensureMsgf(WidgetClass, TEXT("[RPGWidgetSubSystem::SpawnRPGWidget] Not Widget Class")) == false) {
		return nullptr;
	}

	return CreateWidget<URPGUserWidgetBase>(GetGameInstance(), WidgetClass);
}

URPGUserWidgetBase* URPGWidgetSubSystem::PushWidget(FName WidgetName, EWidgetLayoutType LayoutType)
{
	
	if (bCreatedWidgetLayout == false) {
		/*Layout 생성 전에 Push될 경우*/
		PushWidgets.Add(FPushWidgetQueue(WidgetName, LayoutType));

		return nullptr;
	}

	TSubclassOf<URPGUserWidgetBase> AddWidgetClass = DATATABLE_MANAGER(GetWorld())->GetWidgetClassWithName(WidgetName);
	if (ensureMsgf(AddWidgetClass, TEXT("[RPGWidgetSubSystem::PushWidget] Not Widget Class")) == false) {
		return nullptr;
	}

	URPGUserWidgetBase* NewWidget = SpawnRPGWidget(WidgetName);
	if (ensureMsgf(AddWidgetClass, TEXT("[RPGWidgetSubSystem::PushWidget] Not Spawn Widget")) == false) {
		return nullptr;
	}

	ULayoutWidget* LayoutWidget = *WidgetLayout.Find(LayoutType);
	if (ensureMsgf(LayoutWidget, TEXT("[RPGWidgetSubSystem::PushWidget] Not Exist Layout")) == false) {
		return nullptr;
	}

	LayoutWidget->GetPanel()->AddChildToCanvas(NewWidget);
	NewWidget->SetWidgetLayout(LayoutType);

	if (UCanvasPanelSlot* CPSlot = Cast<UCanvasPanelSlot>(NewWidget->Slot))
	{
		//CPSlot->SetAnchors(FAnchors(0.5f, 0.5f));
		//switch (AnchorType)
		//{
		//case EWidgetAnchorType::None:
		//{
		//	break;
		//}
		//case EWidgetAnchorType::Center:
		//{
		//	CPSlot->SetAnchors(FAnchors(0.5f, 0.5f));
		//	break;
		//}
		//case EWidgetAnchorType::Fill:
		//{
		//	CPSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		//	CPSlot->SetOffsets(FMargin(0.f));
		//	break;
		//}
		//}
	}

	return NewWidget;
}

URPGUserWidgetBase* URPGWidgetSubSystem::PopWidget(FName WidgetName, EWidgetLayoutType LayoutType)
{
	if (bCreatedWidgetLayout == false) {
		PushWidgets.Remove(FPushWidgetQueue(WidgetName, LayoutType));
		
		return nullptr;
	}

	URPGUserWidgetBase* Cast_FindWidget = GetWidgetWithLayoutType(LayoutType, WidgetName);
	if (ensureMsgf(Cast_FindWidget, TEXT("[URPGWidgetSubSystem::PopWidget] Not Created Widget")) == false)
		return nullptr;

	Cast_FindWidget->RemoveFromParent();

	return Cast_FindWidget;
}

URPGUserWidgetBase* URPGWidgetSubSystem::GetWidgetWithLayoutType(EWidgetLayoutType LayoutType, FName WidgetName)
{
	TSubclassOf<URPGUserWidgetBase> WidgetClass = DATATABLE_MANAGER(GetWorld())->GetWidgetClassWithName(WidgetName);
	if (ensureMsgf(WidgetClass, TEXT("[URPGWidgetSubSystem::GetWidgetWithLayoutType] Not Widget Name")) == false) {
		return nullptr;
	}

	ULayoutWidget* LayoutWidget = *WidgetLayout.Find(LayoutType);
	if (ensureMsgf(LayoutWidget, TEXT("[URPGWidgetSubSystem::GetWidgetWithLayoutType] Not Exist Layout")) == false) {
		return nullptr;
	}

	TArray<UWidget*> ChildrenWidget = LayoutWidget->GetPanel()->GetAllChildren();
	UWidget** FindWidget = ChildrenWidget.FindByPredicate([WidgetClass](UWidget* ChildWidget) {
		return ChildWidget->GetClass() == WidgetClass;
		});

	if (ensureMsgf(FindWidget, TEXT("[URPGWidgetSubSystem::GetWidgetWithLayoutType] Not Found Widget")) == false) {
		return nullptr;
	}

	return *FindWidget ? Cast<URPGUserWidgetBase>(*FindWidget) : nullptr;
}

void URPGWidgetSubSystem::ExecuteWidgetSingle(FName WidgetName, FName FunctionName, FWidgetParam WidgetParam)
{
	TSubclassOf<URPGUserWidgetBase> WidgetClass = DATATABLE_MANAGER(GetWorld())->GetWidgetClassWithName(WidgetName);
	ensureMsgf(WidgetClass, TEXT("[URPGWidgetSubSystem::ExecuteWidgetSingle] Not Widget Name"));

	for (auto Layout : WidgetLayout)
	{
		ULayoutWidget* LayoutWidget = Layout.Value;

		for (UWidget* ChildWidget : LayoutWidget->GetPanel()->GetAllChildren())
		{
			if (URPGUserWidgetBase* WidgetChild = Cast<URPGUserWidgetBase>(ChildWidget))
			{
				if (WidgetChild->GetClass()->IsChildOf(WidgetClass))
				{
					if (ExecuteWidget(WidgetChild, WidgetChild->FindFunction(FunctionName), WidgetParam))
					{
						return;
					}
				}
			}
		}
	}
}

void URPGWidgetSubSystem::VisibilityLayout(EWidgetLayoutType LayoutType, ESlateVisibility Visibility)
{
	ULayoutWidget* LayoutWidget = *WidgetLayout.Find(LayoutType);
	if (ensureMsgf(LayoutWidget, TEXT("[URPGWidgetSubSystem::VisibilityLayout] Not Exist Layout")) == false) {
		return;
	}

	LayoutWidget->SetVisibility(Visibility);
}

void URPGWidgetSubSystem::CreateWidgetLayout()
{	
	for (int32 Typeindex = static_cast<int32>(EWidgetLayoutType::None) + 1; Typeindex < static_cast<int32>(EWidgetLayoutType::Etc); ++Typeindex) {

		const EWidgetLayoutType LayoutType = static_cast<EWidgetLayoutType>(Typeindex);
		ULayoutWidget * NewWidget = Cast<ULayoutWidget>(SpawnRPGWidget(EWidgetNames::Layout));
		NewWidget->AddToViewport();

		WidgetLayout.FindOrAdd(LayoutType, NewWidget);
	}

	bCreatedWidgetLayout = true;

	/*Layout 생성 전 Push된 Widget을 Layout Widget 생성 후 Push*/
	for (const FPushWidgetQueue Queue : PushWidgets) {
		PushWidget(Queue.WidgetName, Queue.LayoutType);
	}

	PushWidgets.Empty();
}

void URPGWidgetSubSystem::DestroyWidgetLayout()
{
	for (int32 TypeIndex = static_cast<int32>(EWidgetLayoutType::None) + 1; TypeIndex < static_cast<int32>(EWidgetLayoutType::Etc); TypeIndex++)
	{
		const EWidgetLayoutType LayoutType = static_cast<EWidgetLayoutType>(TypeIndex);
		if (ULayoutWidget* LayoutWidget = *WidgetLayout.Find(LayoutType))
		{
			LayoutWidget->RemoveFromParent();
		}
	}

	WidgetLayout.Empty();
}

bool URPGWidgetSubSystem::ExecuteWidget(URPGUserWidgetBase* Widget, UFunction* Function, FWidgetParam WidgetParam)
{
	if (ensureMsgf(Widget, TEXT("[URPGWidgetSubSystem::ExecuteWidget] Not Widget")) == false)
		return false;

	if (ensureMsgf(Function, TEXT("[URPGWidgetSubSystem::ExecuteWidget] Not Function")) == false)
		return false;

	/*함수 실행*/
	Widget->ProcessEvent(Function, &WidgetParam);

	return true;
}
