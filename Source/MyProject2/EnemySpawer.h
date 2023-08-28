// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject2/Enemy.h"

#include "EnemySpawer.generated.h"

UCLASS()
class MYPROJECT2_API AEnemySpawer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	//
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent * SpawnArea;
	
		//Éú³É
	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemy>EnemyType;

	UFUNCTION()
		void SpawerEnemy( );
	//¼ä¸ô
	UPROPERTY(EditAnywhere)
		float spawnSpeed = 1.0f;

protected:
	AEnemySpawer();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	FTimerHandle SpawnHandle;
};
