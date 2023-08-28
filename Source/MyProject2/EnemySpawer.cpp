// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawer.h"
#include "Components/BoxComponent.h"
#include"GameFramework/Actor.h"
#include"TimerManager.h"
#include"Kismet/KismetMathLibrary.h"
// Sets default values
AEnemySpawer::AEnemySpawer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = SpawnArea;
	PrimaryActorTick.bCanEverTick = true;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("OUtCollision"));
	SpawnArea->SetBoxExtent(FVector(5000.0f, 5000.0f, 100.0f));//碰撞体

}
void AEnemySpawer::SpawerEnemy() {
	FVector Origin;
	FVector Extends;//引用类型
	GetActorBounds(false, Origin, Extends); //(bool只有碰撞体参与，引用类型)
	FVector Spawnpoint=UKismetMathLibrary::RandomPointInBoundingBox(Origin,Extends);//范围扩展碰撞体（中心点）
	GetWorld()->SpawnActor<AEnemy>(EnemyType, Spawnpoint, FRotator::ZeroRotator);//生成(类，位置，默认方向)
}

// Called when the game starts or when spawned
void AEnemySpawer::BeginPlay()
{
	Super::BeginPlay();
	//固定时间生成,可以取消暂停等待，执行频率
	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawer::SpawerEnemy, spawnSpeed, true);
}

// Called every frame
void AEnemySpawer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

