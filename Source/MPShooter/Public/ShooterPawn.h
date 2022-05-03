// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterPawn.generated.h"

UCLASS()
class MPSHOOTER_API AShooterPawn : public ACharacter
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
		class UMaterialInstanceDynamic* MeshMID;
	UPROPERTY(ReplicatedUsing = OnRep_Color, Transient, BlueprintReadOnly, Category = "Player")
		FLinearColor Color;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* WeaponHandle;

	UPROPERTY(ReplicatedUsing = OnRep_Weapon, Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		class AWeapon* Weapon;




public:
	// Sets default values for this character's properties
	AShooterPawn(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float AimTraceDistance;

	virtual void Tick(float DeltaTime) override;


public:
	virtual void PostInitializeComponents() override;
	void AuthSetColor(const FLinearColor& InColor);

private:
	UFUNCTION() void OnFire();
	UFUNCTION() void OnMoveForward(float Axis);
	UFUNCTION() void OnMoveRight(float Axis);
	UFUNCTION() void OnMoveUp(float Axis);
	UFUNCTION() void OnLookRight(float Axis);
	UFUNCTION() void OnLookUp(float Axis);

private:
	UFUNCTION()
		void OnRep_Color();

private:
	UFUNCTION()
		void OnRep_Weapon();
};
