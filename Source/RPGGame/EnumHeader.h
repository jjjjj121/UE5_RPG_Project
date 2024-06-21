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
	MELEEWEAPONS,	//���� ����
	RANGEWEAPONS,	//���Ÿ� ����
	SHIELDS,		//����
	CLOTHES,		//��� ��
	MATERIAL,		//���
	CONSUMABLE,		//�Һ�
	SPECIAL,		//Ư��
	ETC,			//��Ÿ ���
};

/*Equip Slot*/
UENUM(BlueprintType)
enum class EEquipCategoryType : uint8
{
	MAINWEAPON,		//�� ���� ����
	SUBWEAPON,		//���� ���� ����
	ARROW,			//ȭ��

	HEAD,			//�Ӹ�
	TOP,			//����
	PANTS,			//����
	GLOVES,			//�尩
	SHOES,			//�Ź�

	SUBITEMS1,		//���� ������1
	SUBITEMS2,		//���� ������2

	NONE,
	
};

/*Equipment Type*/
UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	WEAPON,			//����
	SHIELD,			//����
	ARROW,			//ȭ��

	HEAD,			//�Ӹ�
	TOP,			//����
	PANTS,			//����
	GLOVES,			//�尩
	SHOES,			//�Ź�

	SUBITEMS,		//���� ������

	MAX
};


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Hand			UMETA(DisplayName = "Hand"),			//Non
	GreatSword		UMETA(DisplayName = "GreatSword"),		//���
	Sword			UMETA(DisplayName = "Sword"),			//�Ѽ� ��
	Bow				UMETA(DisplayName = "Bow"),				//Ȱ
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	Head			UMETA(DisplayName = "Head"),			//����
	armor			UMETA(DisplayName = "armor"),			//���� ��
	leg				UMETA(DisplayName = "leg"),				//�ٸ� ��
	shoes			UMETA(DisplayName = "shoes"),			//��ȭ
	Gloves			UMETA(DisplayName = "Gloves"),			//�尩
};

UENUM(BlueprintType)
enum class EAccessaryType : uint8
{
	ring			UMETA(DisplayName = "Head"),			//����
	necklace		UMETA(DisplayName = "armor"),			//�����
};


UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	Common			UMETA(DisplayName = "Common"),			//�Ϲ� ���
	Magic			UMETA(DisplayName = "Magic"),			//���� ���
	Rare			UMETA(DisplayName = "Rare"),			//���� ���
	Unique			UMETA(DisplayName = "Unique"),			//����ũ ���
	Legendary		UMETA(DisplayName = "Legendary"),		//�������� ���
	None			UMETA(DisplayName = "None"),			
};



//Monster
//���� �з�
UENUM(BlueprintType)
enum class EMonsterRace : uint8
{
	Cannibals			UMETA(DisplayName = "Cannibals"),		//������
	Cultists			UMETA(DisplayName = "Cultists"),		//���ŵ�
	Drowned				UMETA(DisplayName = "Drowned"),			//�ͻ�ü
	Fallen				UMETA(DisplayName = "Fallen"),			//Ÿ������
	Ghoul				UMETA(DisplayName = "Ghoul"),			//�Ǳ�
	Goatmen				UMETA(DisplayName = "Goatmen"),			//�����ΰ�
	Nangari				UMETA(DisplayName = "Nangari"),			//������
	Skeletons			UMETA(DisplayName = "Skeletons"),		//�ذ�
	Spiders				UMETA(DisplayName = "Spiders"),			//�Ź�
	Vampires			UMETA(DisplayName = "Vampires"),		//�����̾�
	Werewolves			UMETA(DisplayName = "Werewolves"),		//�����ΰ�
	Wild_Life			UMETA(DisplayName = "Wild Life"),		//�߻�����
};

UENUM(BlueprintType)
enum class ECannibals : uint8
{
	Cannibals_melee		UMETA(DisplayName = "Cannibals_melee"),		//����
	Cannibals_range		UMETA(DisplayName = "Cannibals_range"),		//���Ÿ�

};


class RPGGAME_API EnumHeader
{
public:
	EnumHeader();
	~EnumHeader();
};


