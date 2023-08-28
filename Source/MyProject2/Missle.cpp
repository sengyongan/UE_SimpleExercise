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
	Mesh->SetGenerateOverlapEvents(true);//���ô����¼��������ײ��
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMissle::OverlapHandler);//���¼��������ϣ��������¼����ú���
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 500.0f;//�����ٶ�
	//InitiaLIfeSpan=8.0//�����ٶȿ��Է���AMissle��
}
void AMissle::OverlapHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(OtherActor->IsA<AEnemy>()){//�����ײΪ
		OtherActor->Destroy();//ը������
		AMyProject2GameModeBase*gm= Cast<AMyProject2GameModeBase>(GetWorld()->GetAuthGameMode());//��ȡ��//����ת��
		if (gm != nullptr) {
			gm->points++;//gamemode����ֵ���ӣ���͸����
		}
		this->Destroy();
	}

}
// Called when the game starts or when spawned
void AMissle::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySound2D(this, MissleSound, 0.5f);
	SetLifeSpan(8.0f);//�Զ�����

}

// Called every frame
void AMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

