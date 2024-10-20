// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

//void UOverheadWidget::SetDisplayName(FString NameToDisplay)
//{
//	if (DisplayName)
//	{
//		DisplayName->SetText(FText::FromString(NameToDisplay));
//	}
//}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;
	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority:
		Role = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		Role = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		Role = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		Role = FString("None");
		break;
	}
	FString RemoteRoleString = FString::Printf(TEXT("Local Role: %s"), *Role);
	SetDisplayText(RemoteRoleString);

}

//void UOverheadWidget::ShowPlayerName(APawn* InPawn)
//{
//	//show name
//
//	const APlayerState* PlayerState = InPawn->GetPlayerState();
//	if (!PlayerState || !*PlayerState->GetPlayerName() && TotalTime < GetPlayerNameTimeout)
//	{
//		FTimerHandle GetPlayerStateTimer;
//		FTimerDelegate TryAgainDelegate;
//		TryAgainDelegate.BindUFunction(this, FName("ShowPlayerName"), InPawn);
//		GetWorld()->GetTimerManager().SetTimer(GetPlayerStateTimer, TryAgainDelegate, GetPlayerNameInterval, false, 0.1f);
//		TotalTime += GetPlayerNameInterval;
//		return;
//	}
//	const FString PlayerName = InPawn->GetPlayerState()->GetPlayerName();
//	SetDisplayText(PlayerName);
//}

void UOverheadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	RemoveFromParent();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}
