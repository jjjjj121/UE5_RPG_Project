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
	Main, // Player HUD, Interaction �� Overlay UI  - Main�� ù ���� �� ��� ������ �ִ� �������� Visibility�� �����Ͽ� ȭ�鿡 ���̰� �Ⱥ��̰� ����
	Option, // ���� ����, ����, ���â �� Option UI - Option�� �ش� ������ ų ������ �����ϰ�, �� ���� �����ϴ� ���� �������� push, pop���� ����
	Popup, // ������ ȹ��, NPC ��ȭ, �ɼ� ���� üũ �� Popup UI - Popup�� �Ͻ������� ���� �� �� �� �ð��� ������ �ڵ����� �����Ǵ� ���� ����
	Etc, //��Ÿ ���
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
