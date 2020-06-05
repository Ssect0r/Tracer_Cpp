// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingOrb.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tracer_cppCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
ARotatingOrb::ARotatingOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Dimensions = FVector(300, 0, 0);
	AxisVector = FVector(0, 0, 1);
	Multiplier = 300.f;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//MeshComp->
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComp->SetSphereRadius(200);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_MAX, ECR_Overlap);
	SphereComp->SetVisibility(true);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARotatingOrb::OnOverlap);
	SphereComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARotatingOrb::BeginPlay()
{
	Super::BeginPlay();
	//Host = GetOwner();

}

// Called every frame
void ARotatingOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Host)
	{
		Location = Host->GetActorLocation();
		AngleAxis += DeltaTime * Multiplier;

		if (AngleAxis >= 360.0f)
		{
			AngleAxis = 0;
		}

		FVector RotateValue = Dimensions.RotateAngleAxis(AngleAxis, AxisVector);

		Location.X += RotateValue.X;
		Location.Y += RotateValue.Y;
		Location.Z += RotateValue.Z;

		FRotator NewRotation = FRotator(0, AngleAxis, 0);
		FQuat QuatRotation = FQuat(NewRotation);

		SetActorLocationAndRotation(Location, NewRotation, false, 0, ETeleportType::None);
	}
}

void ARotatingOrb::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TSubclassOf<UDamageType> P;
	ATracer_cppCharacter* player = Cast<ATracer_cppCharacter>(OtherActor);
	{
		if (player)
		{
			UGameplayStatics::ApplyDamage(player, 10, GetInstigatorController() , this, P);
		}
	}
}

void ARotatingOrb::SetHost(AActor* ThisHost)
{
	Host = ThisHost;
}

