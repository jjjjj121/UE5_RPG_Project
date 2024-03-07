#pragma once

#include "CoreMinimal.h"
#include "WidgetEnumLibrary.generated.h"

UENUM(BlueprintType)
enum class EButtonMenuType : uint8
{
	Equip,
	UnEquip,
	Use,
	ThrowAway,
	ETC,
};

UENUM(BlueprintType)
enum class EWidgetLayoutType : uint8
{
	None,
	Main, // Player HUD, Interaction 등 Overlay UI  - Main은 첫 스폰 후 계속 가지고 있는 위젯으로 Visibility를 조정하여 화면에 보이게 안보이게 설정
	Option, // 게임 종료, 도감, 장비창 등 Option UI - Option은 해당 위젯을 킬 때마다 스폰하고, 끌 때는 삭제하는 식의 위젯으로 push, pop으로 설정
	Popup, // 아이템 획득, NPC 대화, 옵션 선택 체크 등 Popup UI - Popup은 일시적으로 스폰 후 일 정 시간이 지나면 자동으로 삭제되는 식의 위젯
	Etc, //기타 등등
};

UENUM(BlueprintType)
enum class EWidgetAnchorType : uint8
{
	None,
	Center,
	Fill,
};

UENUM(BlueprintType)
enum class EUserMenuType : uint8
{
	None,
	Equipment,
	Inventory,
	Quest,
	Map,
};

namespace EWidgetNames {
	/*Main HUD*/
	static FName Layout = TEXT("Layout");
	static FName PlayerHUD = TEXT("PlayerHUD");
	static FName Interaction = TEXT("Interaction");
	static FName KeyTutorial = TEXT("KeyTutorial");

	/*Pop up*/
	static FName Menu = TEXT("Menu");
	static FName Inventory = TEXT("Inventory");




	/*Sub Widget*/
	static FName RButtonMenu = TEXT("RButtonMenu");
	static FName RButtonMenuSlot = TEXT("RButtonMenuSlot");
	static FName Quantity = TEXT("Quantity");
}

namespace EWidgetFunctionNames
{
	static FName Interaction = TEXT("ExecuteInteraction");
	static FName Interaction_PreesKey = TEXT("PressInteractKey");
	static FName Interaction_TriggerKey = TEXT("TriggerInteractKey");
	static FName Interaction_SelectRoot = TEXT("SelectRootList");

	static FName Menu_GetInventoryWidget = TEXT("GetInventoryWidget");

	static FName RButtonMenu_Show = TEXT("ShowButtonMenu");
	static FName RButtonMenu_Hide = TEXT("HideButtonMenu");

}


namespace EItemGradeColor
{
	static FLinearColor Common = FLinearColor(1.f, 1.f, 1.f, 1.f);
	static FLinearColor Magic = FLinearColor(0.f, 1.f, 0.f, 1.f);
	static FLinearColor Rare = FLinearColor(0.f, 0.f, 1.f, 1.f);
	static FLinearColor Unique = FLinearColor(0.4f, 0.f, 0.9f, 1.f);
	static FLinearColor Legendary = FLinearColor(0.9f, 0.4f, 0.f, 1.f);
	static FLinearColor None = FLinearColor(0.3f, 0.3f, 0.3f, 1.f);
}
