// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    player_opens = GetWorld()->GetFirstPlayerController()->GetPawn();

}

void UOpenDoor::OpenDoor() {
    // Find the Owning Actor
    AActor* owner = GetOwner();
    FRotator new_rotation = FRotator(0.0f, open_angle, 0.0f);
    owner->SetActorRotation(new_rotation, ETeleportType::TeleportPhysics);
}

void UOpenDoor::CloseDoor() {
    AActor* owner = GetOwner();
    owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (pressure_plate->IsOverlappingActor(player_opens)) {
	    OpenDoor();
        last_door_open_time = GetWorld()->GetTimeSeconds();
    } else if (GetWorld()->GetTimeSeconds() - last_door_open_time > DoorCloseDelay) {
	    CloseDoor();
	}


}

