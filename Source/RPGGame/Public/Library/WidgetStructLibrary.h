#pragma once
#include "CoreMinimal.h"
#include "WidgetStructLibrary.generated.h"

USTRUCT(BlueprintType)
struct FWidgetParam
{
	GENERATED_USTRUCT_BODY()

		FWidgetParam()
	{
		Init();
	}

	void Init()
	{
		ActorParam = nullptr;
		ObjectParam = nullptr;
		WidgetParam = nullptr;
		NameParam = NAME_None;
		StringParam = TEXT("");
		DescriptionParam = TEXT("");
		VectorParam = FVector::ZeroVector;
		FloatParam = 0.f;
		BoolParam = false;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* ActorParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UObject* ObjectParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* WidgetParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName NameParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString StringParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString DescriptionParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector VectorParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D Vector2DParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FloatParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool BoolParam;
};
