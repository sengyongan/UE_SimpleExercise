// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enemy.generated.h"

UCLASS()
class MYPROJECT2_API AEnemy : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AEnemy();
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * Mesh;
	UFUNCTION()
		void DestoryMandler(AActor* DestroyedActor);
	//特效
	UPROPERTY(EditAnywhere)
	class	UParticleSystem* ExplosionParticle;
	//声音
	UPROPERTY(EditAnywhere)
	class USoundBase* ExplosionSound;
	//速度
	UPROPERTY(EditAnywhere)
	float floatspeed=500.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
