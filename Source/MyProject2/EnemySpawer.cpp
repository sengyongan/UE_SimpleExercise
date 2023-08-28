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
	SpawnArea->SetBoxExtent(FVector(5000.0f, 5000.0f, 100.0f));//��ײ��

}
void AEnemySpawer::SpawerEnemy() {
	FVector Origin;
	FVector Extends;//��������
	GetActorBounds(false, Origin, Extends); //(boolֻ����ײ����룬��������)
	FVector Spawnpoint=UKismetMathLibrary::RandomPointInBoundingBox(Origin,Extends);//��Χ��չ��ײ�壨���ĵ㣩
	GetWorld()->SpawnActor<AEnemy>(EnemyType, Spawnpoint, FRotator::ZeroRotator);//����(�࣬λ�ã�Ĭ�Ϸ���)
}

// Called when the game starts or when spawned
void AEnemySpawer::BeginPlay()
{
	Super::BeginPlay();
	//�̶�ʱ������,����ȡ����ͣ�ȴ���ִ��Ƶ��
	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawer::SpawerEnemy, spawnSpeed, true);
}

// Called every frame
void AEnemySpawer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

