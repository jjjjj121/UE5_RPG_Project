// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/RPGWidgetFunctionLibrary.h"
#include "System/RPGGameInstance.h"

URPGUserWidgetBase* URPGWidgetFunctionLibrary::PushWidget(UObject* WorldContextObject, FName WidgetName, EWidgetLayoutType LayoutType, EWidgetAnchorType AnchorType)
{
    if (WorldContextObject == nullptr) {
        return nullptr;
    }


    return WIDGET_SUBSYSTEM(WorldContextObject)->PushWidget(WidgetName, LayoutType, AnchorType);
}

URPGUserWidgetBase* URPGWidgetFunctionLibrary::PopWidget(UObject* WorldContextObject, FName WidgetName, EWidgetLayoutType LayoutType)
{
    if (WorldContextObject == nullptr) {
        return nullptr;
    }

    return WIDGET_SUBSYSTEM(WorldContextObject)->PopWidget(WidgetName, LayoutType);
}

void URPGWidgetFunctionLibrary::VisibilityLayout(UObject* WorldContextObject, EWidgetLayoutType LayoutType, ESlateVisibility Visibility)
{
    if (WorldContextObject == nullptr) {
        return ;
    }

    WIDGET_SUBSYSTEM(WorldContextObject)->VisibilityLayout(LayoutType, Visibility);
}

void URPGWidgetFunctionLibrary::ExecuteWidgetSingle(UObject* WorldContextObject, FName WidgetName, FName FunctionName, FWidgetParam WidgetParam)
{
    if (WorldContextObject == nullptr) {
        return ;
    }

    return WIDGET_SUBSYSTEM(WorldContextObject)->ExecuteWidgetSingle(WidgetName, FunctionName, WidgetParam);
}

URPGUserWidgetBase* URPGWidgetFunctionLibrary::GetWidgetWithLayoutType(UObject* WorldContextObject, EWidgetLayoutType LayoutType, FName WidgetName)
{
    if (WorldContextObject == nullptr) {
        return nullptr;
    }

    return WIDGET_SUBSYSTEM(WorldContextObject)->GetWidgetWithLayoutType(LayoutType, WidgetName);
}
