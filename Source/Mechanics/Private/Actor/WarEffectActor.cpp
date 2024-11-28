// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/WarEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/WarAttributeSet.h"
#include "Components/SphereComponent.h"

AWarEffectActor::AWarEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AWarEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a gameplay effect. 
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UWarAttributeSet* WarAttributeSet = Cast<UWarAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UWarAttributeSet::StaticClass()));
		
		UWarAttributeSet* MutableWarAttributeSet = const_cast<UWarAttributeSet*>(WarAttributeSet);
		MutableWarAttributeSet->SetHealth(WarAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AWarEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AWarEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AWarEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AWarEffectActor::EndOverlap);
}

