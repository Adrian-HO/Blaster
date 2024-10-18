// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayText;

	/*UPROPERTY(meta = (BindWidget))
		class UTextBlock* DisplayName;*/

	void SetDisplayText(FString TextToDisplay);
	//void SetDisplayName(FString NameToDisplay);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);

	//UFUNCTION(BlueprintCallable)
	//	void ShowPlayerName(APawn* InPawn);

//private:
//	UPROPERTY(EditAnywhere, Category = "Overhead Widget Properties", meta = (AllowPrivateAccess = true, Units = "Seconds"))
//		float GetPlayerNameTimeout = 30.f;
//
//	UPROPERTY(EditAnywhere, Category = "Overhead Widget Properties", meta = (AllowPrivateAccess = true, Units = "Seconds"))
//		float GetPlayerNameInterval = 0.1f;
//	float TotalTime = -0.1f;

protected:
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	
};
