// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureTheFlagTeamsGameMode.h"
#include "Blaster/Weapon/Flag.h"
#include "Blaster/CaptureTheFlag/FlagZone.h"
#include "Blaster/GameState/BlasterGameState.h"


void ACaptureTheFlagTeamsGameMode::PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	ABlasterGameMode::PlayerEliminated(ElimmedCharacter, VictimController, AttackerController);

}

void ACaptureTheFlagTeamsGameMode::FlagCaptured(AFlag* Flag, AFlagZone* Zone)
{
	bool bValidCapture = Flag->GetTeam() != Zone->Team;
	ABlasterGameState* BGameState = Cast<ABlasterGameState>(GameState);
	if (BGameState)
	{
		if (Zone->Team == ETeam::ET_BlueTeam)
		{
			BGameState->BlueTeamScores();
		}
		if (Zone->Team == ETeam::ET_RedTeam)
		{
			BGameState->RedTeamScores();
		}
	}
}
