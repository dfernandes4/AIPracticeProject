// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent.Get());

	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SwordMesh->SetupAttachment(Scene.Get());
	
}


