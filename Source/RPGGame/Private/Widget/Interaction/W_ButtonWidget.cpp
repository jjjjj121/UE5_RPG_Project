// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Interaction/W_ButtonWidget.h"
#include "Components/ProgressBar.h"

void UW_ButtonWidget::SetGauge(float Value)
{
	PB_ButtonGauge->SetPercent(Value);
}
