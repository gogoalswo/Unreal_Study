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
		// 액터가 다른 클라이언트에 Replicate(복제) 됨
		SetReplicates(true);

		// 액터의 움직임이 다른 클라이언트에 Replicate(복제) 됨
		SetReplicateMovement(true);

		StartLocation = GetActorLocation();
		EndLocation = GetTransform().TransformPosition(TargetLocation); // 월드 Position으로 변환

		LerpStartLocation = StartLocation;
		LerpEndLocation = EndLocation;

		Distance = FVector::Distance(StartLocation, EndLocation);
	}
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	if (HasAuthority())
	{
		ElapsedTime += DeltaSeconds;
		float EndTime = Distance / Speed;

		float Alpha = FMath::Clamp(ElapsedTime / EndTime, 0.0f, 1.0f);
		FVector Location = FMath::Lerp(LerpStartLocation, LerpEndLocation, Alpha);
		SetActorLocation(Location);

		if (Alpha >= 1.0f)
		{
			ElapsedTime = 0.0f;

			FVector LerpStartLocationTemp = LerpStartLocation;
			LerpStartLocation = LerpEndLocation;
			LerpEndLocation = LerpStartLocationTemp;

			/*if (FMath::IsNearlyZero(FVector::Distance(StartLocation, GetActorLocation()), 1.0f))
			{
				LerpStartLocation = StartLocation;
				LerpEndLocation = EndLocation;
			}
			else
			{
				LerpStartLocation = EndLocation;
				LerpEndLocation = StartLocation;
			}*/
		}
		
		/*if (!FMath::IsNearlyZero(FVector::Distance(ActorLocation, EndLocation), 1.0f))
		{
			FVector Dir = (EndLocation - ActorLocation).GetSafeNormal();
			FVector Location = ActorLocation + Dir * Speed * DeltaSeconds;
			SetActorLocation(Location);
		}
		else
		{
			if (FMath::IsNearlyZero(FVector::Distance(ActorLocation, StartLocation), 1.0f))
			{
				EndLocation = GetTransform().TransformPosition(TargetLocation);
			}
			else
			{
				EndLocation = StartLocation;
			}
		}*/
	}
}