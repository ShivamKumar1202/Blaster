// Fill out your copyright notice in the Description page of Project Settings.


#include "FlagZone.h"
#include "Blaster/BlasterTypes/Team.h"
#include "Blaster/GameMode/CaptureTheFlagTeamsGameMode.h"
#include "Blaster/Weapon/Flag.h"
#include "Components/SphereComponent.h"

AFlagZone::AFlagZone()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ZoneSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ZoneSphere"));
	SetRootComponent(ZoneSphere);
}


void AFlagZone::BeginPlay()
{
	Super::BeginPlay();

	ZoneSphere->OnComponentBeginOverlap.AddDynamic(this, &AFlagZone::OnSphereOverlap);
}


void AFlagZone::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFlag* OverlappingFlag = Cast<AFlag>(OtherActor);

	if (OverlappingFlag && OverlappingFlag->GetTeam() != Team)
	{
		ACaptureTheFlagTeamsGameMode* CTFGameMode = GetWorld()->GetAuthGameMode<ACaptureTheFlagTeamsGameMode>();
		
		if (CTFGameMode)
		{
			CTFGameMode->FlagCaptured(OverlappingFlag,this);
		}
		OverlappingFlag->ResetFlag();
	}

}
