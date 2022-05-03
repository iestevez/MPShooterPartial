// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Engine/CollisionProfile.h"

// Sets default values
AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(
		TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")
	);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(
		TEXT("Material'/Game/Materials/Weapon/M_Weapon.M_Weapon'")
	);


	bReplicates = true;
	bNetUseOwnerRelevancy = true;

	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));
	MeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MeshComponent"));

	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetStaticMesh(MeshFinder.Object);
	MeshComponent->SetMaterial(0, MaterialFinder.Object);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	MeshComponent->SetRelativeLocation(FVector(20.0f, 0.0f, 0.0f));
	MeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 45.0f));
	MeshComponent->SetRelativeScale3D(FVector(0.5f, 0.15f, 0.15f));

	AimInterpSpeed = 8.0f;
	DropInterpSpeed = 10.0f;
	DropRotation = FRotator(-30.0f, -80.0f, 0.0f);

	MuzzleHandle = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("MuzzleHandle"));
	MuzzleHandle->SetupAttachment(RootComponent);
	MuzzleHandle->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));


}
// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAimLocationIsValid) {

		const FVector AimDisplacement = AimLocation - GetActorLocation();
		const FVector AimDirection = AimDisplacement.GetSafeNormal();

		const FQuat TargetRotation = AimDirection.ToOrientationQuat();
		const FQuat NewRotation = FMath::QInterpTo(GetActorQuat(), TargetRotation, DeltaTime, AimInterpSpeed);
		SetActorRotation(NewRotation);
	}

	else
	{
		AActor* AttachParent = GetAttachParentActor();
		const FQuat TargetRotation = AttachParent ? AttachParent->GetActorTransform().TransformRotation(FQuat(DropRotation)) : FQuat(DropRotation);
		const FQuat NewRotation = FMath::QInterpTo(GetActorQuat(), TargetRotation, DeltaTime, DropInterpSpeed);
		SetActorRotation(NewRotation);
	}

}

void AWeapon::UpdateAimLocation(const FVector& InWorldAimLocation, const FVector& InViewAimLocation)
{
	AimLocation = InWorldAimLocation;
	bAimLocationIsValid = InViewAimLocation.X > MuzzleHandle->GetRelativeLocation().X;


}
