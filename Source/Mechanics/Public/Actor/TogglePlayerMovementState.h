// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TogglePlayerMovementState.generated.h"

class UBoxComponent;
class UInputMappingContext;

UCLASS()
class MECHANICS_API ATogglePlayerMovementState : public AActor
{
	GENERATED_BODY()
	
public:
	ATogglePlayerMovementState();

	 // Overlap function
    UFUNCTION()
    void OnBoxOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    void AddInputMapping(ACharacter* Character);
    void RemoveInputMapping(ACharacter* Character);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_OperationsOnOverlap(bool bIsInterior);

	 // Box Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBoxComponent> BoxComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    bool bShouldFly = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* MappingContext;


protected:
	virtual void BeginPlay() override;
};
