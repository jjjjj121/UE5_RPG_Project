// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */



//Item
UENUM(BlueprintType)
enum class EItemCategoryType : uint8
{
	MELEEWEAPONS,	//근접 무기
	RANGEWEAPONS,	//원거리 무기
	SHIELDS,		//방패
	MATERIAL,		//재료
	CONSUMABLE,		//소비
	SPECIAL,		//특별
	ETC,			//기타 등등
};

UENUM(BlueprintType)
enum class EEquipItemType : uint8
{
	Weapon			UMETA(DisplayName = "Weapon"),		//무기
	Armor			UMETA(DisplayName = "Armor"),		//방어구
	Accessary		UMETA(DisplayName = "Accessary"),	//장신구
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Hand			UMETA(DisplayName = "Hand"),			//Non
	GreatSword		UMETA(DisplayName = "GreatSword"),		//대검
	Sword			UMETA(DisplayName = "Sword"),			//한손 검
	Bow				UMETA(DisplayName = "Bow"),				//활
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	Head			UMETA(DisplayName = "Head"),			//투구
	armor			UMETA(DisplayName = "armor"),			//가슴 방어구
	leg				UMETA(DisplayName = "leg"),				//다리 방어구
	shoes			UMETA(DisplayName = "shoes"),			//장화
	Gloves			UMETA(DisplayName = "Gloves"),			//장갑
};

UENUM(BlueprintType)
enum class EAccessaryType : uint8
{
	ring			UMETA(DisplayName = "Head"),			//반지
	necklace		UMETA(DisplayName = "armor"),			//목걸이
};


UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	Common			UMETA(DisplayName = "Common"),			//일반 등급
	Magic			UMETA(DisplayName = "Magic"),			//매직 등급
	Rare			UMETA(DisplayName = "Rare"),			//레어 등급
	Legendary		UMETA(DisplayName = "Legendary"),		//레전더리 등급
	Unique			UMETA(DisplayName = "Unique"),			//유니크 등급
};



//Monster
//종족 분류
UENUM(BlueprintType)
enum class EMonsterRace : uint8
{
	Cannibals			UMETA(DisplayName = "Cannibals"),		//식인종
	Cultists			UMETA(DisplayName = "Cultists"),		//광신도
	Drowned				UMETA(DisplayName = "Drowned"),			//익사체
	Fallen				UMETA(DisplayName = "Fallen"),			//타락한자
	Ghoul				UMETA(DisplayName = "Ghoul"),			//악귀
	Goatmen				UMETA(DisplayName = "Goatmen"),			//염소인간
	Nangari				UMETA(DisplayName = "Nangari"),			//낭가리
	Skeletons			UMETA(DisplayName = "Skeletons"),		//해골
	Spiders				UMETA(DisplayName = "Spiders"),			//거미
	Vampires			UMETA(DisplayName = "Vampires"),		//뱀파이어
	Werewolves			UMETA(DisplayName = "Werewolves"),		//늑대인간
	Wild_Life			UMETA(DisplayName = "Wild Life"),		//야생동물
};

UENUM(BlueprintType)
enum class ECannibals : uint8
{
	Cannibals_melee		UMETA(DisplayName = "Cannibals_melee"),		//근접
	Cannibals_range		UMETA(DisplayName = "Cannibals_range"),		//원거리

};


class RPGGAME_API EnumHeader
{
public:
	EnumHeader();
	~EnumHeader();
};


