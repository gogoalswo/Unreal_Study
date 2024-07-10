#include "MovingPlatform.h"
#include "Net/UnrealNetwork.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	if (HasAuthority())
	{
		FVector Location;
		Location = GetActorLocation();
		Location.X += Speed * DeltaSeconds;
		SetActorLocation(Location);
	}
}