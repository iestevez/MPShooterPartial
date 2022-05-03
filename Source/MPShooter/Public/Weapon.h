// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class MPSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* MeshComponent;
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* MuzzleHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
		float AimInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
		float DropInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
		FRotator DropRotation;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Aiming|State")
		FVector AimLocation;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Aiming|State")
		bool bAimLocationIsValid;

public:

	void UpdateAimLocation(const FVector& InWorldAimLocation, const FVector& InViewAimLocation);

public:
	// Sets default values for this actor's properties
	AWeapon(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
