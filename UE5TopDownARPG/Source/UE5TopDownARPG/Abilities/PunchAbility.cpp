// Fill out your copyright notice in the Description page of Project Settings.

#include "PunchAbility.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/DamageEvents.h"

bool UPunchAbility::Activate(FVector Location)
{
	if (Super::Activate(Location) == false)
	{
		return false;
	}

	UObject* Outer = GetOuter();
	AActor* Owner = Cast<AActor>(Outer);

	if (IsValid(Owner) == false)
	{
		return false;
	}

	USkeletalMeshComponent* Mesh = Owner->FindComponentByClass<USkeletalMeshComponent>();
	if (IsValid(Mesh) == false)
	{
		return false;
	}

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (IsValid(AnimInstance) == false)
	{
		return false;
	}

	AnimInstance->Montage_Play(PunchMontage);
	//AnimInstance->Montage_SetEndDelegate(FOnMontageEnded::CreateUObject(this, &UPunchAbility::OnPunchEnded));

	CollisionBox = NewObject<UBoxComponent>(this);
	CollisionBox->SetBoxExtent(FVector(15, 15, 15));
	CollisionBox->RegisterComponent();
	CollisionBox->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_r_socket"));
	CollisionBox->SetCollisionProfileName(TEXT("Ability"));
	CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &UPunchAbility::OnBeginOverlap);

	return true;
}

void UPunchAbility::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UObject* Outer = GetOuter();
	AActor* Owner = Cast<AActor>(Outer);

	if (IsValid(Other) && Other != Owner)
	{
		Other->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, Owner);
	}
	
	if (IsValid(CollisionBox))
	{
		CollisionBox->DestroyComponent();
	}
}