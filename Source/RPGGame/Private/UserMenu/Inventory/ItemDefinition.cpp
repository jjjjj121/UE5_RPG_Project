// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMenu/Inventory/ItemDefinition.h"

UItemDefinition::UItemDefinition()
{
	ItemData = FItemData();

}

//void UItemDefinition::SetItemData(FItemData NewItemData)
//{
//	ItemData = NewItemData;
//
//	Fragments.Empty();
//
//	for (TSubclassOf<UItemFragment> Fragment : ItemData.Fragments) {
//		//UItemFragment* NewFragment = NewObject<UItemFragment>(Fragment);
//		UItemFragment* NewFragment = Cast<UItemFragment>(Fragment->GetDefaultObject());
//		Fragments.Add(NewFragment);
//		UE_LOG(LogTemp, Warning, TEXT("[UItemDefinition] : Fragment Add"));
//	}
//
//}

const UItemFragment* UItemDefinition::FindFragmentByClass(TSubclassOf<UItemFragment> _FragmentClass) const
{
	if (_FragmentClass != nullptr)
	{
		for (UItemFragment* fragment : Fragments)
		{
			if (fragment && fragment->IsA(_FragmentClass))
			{
				return fragment;
			}
		}
	}

	return nullptr;
}
