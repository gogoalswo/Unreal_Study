#pragma once

#include <CoreMinimal.h>
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"


UCLASS()
class PUZZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	float Speed = 50.0f;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetLocation;

private:
	FVector StartLocation;
	FVector EndLocation;
	FVector LerpStartLocation;
	FVector LerpEndLocation;
	float ElapsedTime = 0.0f;
	float Distance = 0.0f;
};