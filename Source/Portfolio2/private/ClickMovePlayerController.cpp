// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMovePlayerController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

AClickMovePlayerController::AClickMovePlayerController() {
	bShowMouseCursor = true;
}

void AClickMovePlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	InputComponent->BindAction("RightClick", IE_Pressed, this, &AClickMovePlayerController::InputRightMouseButtonPressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &AClickMovePlayerController::InputRightMouseButtonReleased);
}

void AClickMovePlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);

	if (bClickLeftMouse) {
		MoveToMouseCursor();
	}
}


void AClickMovePlayerController::InputRightMouseButtonPressed() {
	bClickLeftMouse = true;
}


void AClickMovePlayerController::InputRightMouseButtonReleased() {
	bClickLeftMouse = false;
}

void AClickMovePlayerController::SetNewDestination(const FVector Destination) {
	APawn* const MyPawn = GetPawn();

	if (MyPawn) {
		float const Distance = FVector::Dist(Destination, MyPawn->GetActorLocation());
		if (Distance > 120.0f) {
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
		}
	}
}

void AClickMovePlayerController::MoveToMouseCursor() {
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit) {
		SetNewDestination(Hit.ImpactPoint);
	}
}