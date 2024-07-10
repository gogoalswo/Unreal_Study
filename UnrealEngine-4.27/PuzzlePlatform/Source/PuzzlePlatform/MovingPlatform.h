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
	float Speed = 20.0f;
};