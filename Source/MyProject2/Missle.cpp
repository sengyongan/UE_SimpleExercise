// Fill out your copyright notice in the Description page of Project Settings.


#include "Missle.h"
#include "Components/StaticMeshComponent.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include"Enemy.h"
#include "MyProject2GameModeBase.h"
#include "Kismet\GameplayStatics.h"
// Sets default values
AMissle::AMissle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetGenerateOverlapEvents(true);//启用穿插事件，不造成撞击
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMissle::OverlapHandler);//绑定事件到函数上，当触发事件调用函数
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 500.0f;//设置速度
	//InitiaLIfeSpan=8.0//设置速度可以放在AMissle中
}
void AMissle::OverlapHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(OtherActor->IsA<AEnemy>()){//如果碰撞为
		OtherActor->Destroy();//炸掉物体
		AMyProject2GameModeBase*gm= Cast<AMyProject2GameModeBase>(GetWorld()->GetAuthGameMode());//获取类//尝试转换
		if (gm != nullptr) {
			gm->points++;//gamemode中数值增加：穿透物体
		}
		this->Destroy();
	}

}
// Called when the game starts or when spawned
void AMissle::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySound2D(this, MissleSound, 0.5f);
	SetLifeSpan(8.0f);//自动销毁

}

// Called every frame
void AMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

