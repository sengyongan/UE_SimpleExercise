// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//"E:\11111\ue4\UE_4.24\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun - project = E : / 11111 / ue4_project_vs_code / MyProject2 / MyProject2.uproject - noP4 - clientconfig = DebugGame - serverconfig = DebugGame - nocompile - nocompileeditor - installed - ue4exe = E : \11111\ue4\UE_4.24\Engine\Binaries\Win64\UE4Editor - Cmd.exe - utf8output - platform = Win64 - targetplatform = Win64 - ini:Game:[/ Script / UnrealEd.ProjectPackagingSettings] : BlueprintNativizationMethod = Disabled - build - skipcook - compressed

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyProject2\Missle.h"
#include "Drone.generated.h"



UCLASS()
class MYPROJECT2_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent * Mesh;
	//
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent * OutCollision;
	//声明
	UPROPERTY(VisibleAnywhere)
	class UPhysicsThrusterComponent * UPThurster;
	UPROPERTY(VisibleAnywhere)
	class UPhysicsThrusterComponent * ForwardThurster;
	//可编辑,读写,标签
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="mycategory")
	FString myname;
	//属性
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * Paddle1;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * Paddle2;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * Paddle3;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * Paddle4;
	//速度和限制速度
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Init")
		float LiftAcc = 10000.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Init")
		float LiftThrushMax = 10000.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Init")
		float ForwardAcc = 500.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Init")
		float ForwardThrushMax = 10000.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Init")
		float TurnStrengh = 500000.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Init")
		float PaddleRotationspeed = 500.0f;
	//导弹
	UPROPERTY(EditAnywhere)
		TSubclassOf<AMissle> Bullet;//声明其他脚本，创建类
	UFUNCTION()
		void DoFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//声明函数
	UFUNCTION()
		void LIft(float val);

	UFUNCTION()
		void Forward(float val);

	UFUNCTION()
		void Turn(float val);
	//数组
	TArray< UStaticMeshComponent*>Paddles;
	void RotatePaddle(float time);



};
