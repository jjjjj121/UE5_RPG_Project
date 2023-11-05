#pragma once

#include "CoreMinimal.h"
#include "WidgetEnumLibrary.generated.h"

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



namespace EWidgetNames {
	static FName Inventory = TEXT("Inventory");
	static FName Layout = TEXT("Layout");
	static FName PlayerHUD = TEXT("PlayerHUD");
}