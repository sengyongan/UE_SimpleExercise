// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/StaticMeshComponent.h"
//引入头文件
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"


// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//头组件
	RootComponent = OutCollision;
	PrimaryActorTick.bCanEverTick = true;
	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OUtCollision"));
	OutCollision->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	OutCollision->SetSimulatePhysics(true);//启用物理
	OutCollision->BodyInstance.bLockXRotation = true;//碰撞体X水平锁定
	OutCollision->BodyInstance.bLockYRotation = true;//碰撞体Y水平
	//向上推行器
	UPThurster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UPThurster"));
	UPThurster->SetupAttachment(RootComponent);
	//UPThurster->ThrustStrength = 1000.0f;//力无法飞起
	//UPThurster->ThrustStrength = OutCollision->GetMass()*-980.0f;//力
	UPThurster->ThrustStrength = 980.0f;//力
	UPThurster->SetAutoActivate(true);//自动开启
	UPThurster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorUpVector()));//方向为自身朝上的相反：朝下
	//向前推行器
	ForwardThurster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwardThurster"));
	ForwardThurster->SetupAttachment(RootComponent);
	ForwardThurster->ThrustStrength = 0.0f;//力
	ForwardThurster->SetAutoActivate(true);//自动开启
	ForwardThurster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorForwardVector()));//方向为自身朝前的相反：朝后


	//
	Mesh = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(OutCollision);
	 Paddle1 = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("Paddle4"));
	//子物体
	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));
	//
	Paddles.Add(Paddle1);
	Paddles.Add(Paddle2);
	Paddles.Add(Paddle3);
	Paddles.Add(Paddle4);
}


// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetInputAxisValue(TEXT("Lift")) == 0) {
		UPThurster->ThrustStrength = 980.0f;//抵消掉重力，立即为0
	}
	if (GetInputAxisValue(TEXT("Forward")) == 0) {
		ForwardThurster->ThrustStrength = 0.0f;//立即为0
		//复原
		if (Mesh->GetRelativeRotation().Pitch != 0.0f) {
			//-pitch是缓慢恢复，固定值是线性
			float pitch1 = Mesh->GetRelativeRotation().Pitch;
			Mesh->AddRelativeRotation(FRotator(-pitch1 * DeltaTime, 0.0f, 0.0f));//相反值复原
			//if (FMath::Abs(Mesh->GetRelativeRotation().Pitch <= KINDA_SMALL_NUMBER)) {
				//Mesh->SetRelativeRotation(FRotator(.0f, .0f, .0f));
			//}
		}
	}
	RotatePaddle(DeltaTime);
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//输入设置:：上下，前后，左右
	PlayerInputComponent->BindAxis(TEXT("Lift"), this, &ADrone::LIft);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ADrone::Forward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrone::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADrone::DoFire);//按下发生函数
}
void ADrone::LIft(float val) {
	UPThurster->ThrustStrength += val * LiftAcc * GetWorld()->DeltaTimeSeconds;//*每帧增加10000*当前帧时间
	UPThurster->ThrustStrength=FMath::Clamp(UPThurster->ThrustStrength, -LiftThrushMax, LiftThrushMax);//大小限制
}
void ADrone::Forward(float val) {
	ForwardThurster->ThrustStrength+=val*ForwardAcc* GetWorld()->DeltaTimeSeconds; 
	ForwardThurster->ThrustStrength = FMath::Clamp(ForwardThurster->ThrustStrength, -ForwardThrushMax, ForwardThrushMax);//大小限制
	//前倾
	float pitch = Mesh->GetRelativeRotation().Pitch;
	if (FMath::Abs(pitch) < 30.0f) {
		Mesh->AddRelativeRotation((FRotator(-100.0f * GetWorld()->DeltaTimeSeconds * val, 0.0f, 0.0f)));
	}

}
void ADrone::Turn(float val) {
	OutCollision->AddTorqueInDegrees(-this->GetActorUpVector() * val * TurnStrengh);
}

void ADrone::RotatePaddle(float time)
{
	for (auto paddle : Paddles) {
		paddle->AddRelativeRotation(FRotator(.0f,  time* PaddleRotationspeed,.0f));//局部旋转
	}
}
void ADrone::DoFire()
{
	FTransform fire= Mesh->GetSocketTransform(TEXT("FringSocket"));//获取插槽位置 
	GetWorld()->SpawnActor< AMissle > (Bullet, fire);//生成子弹（类，位置）
}
