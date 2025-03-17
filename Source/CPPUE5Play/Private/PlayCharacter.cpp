// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayCharacter::APlayCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
    MovementComponent->bOrientRotationToMovement = true;
    MovementComponent->RotationRate = FRotator(0.f, 400.f, 0.f);


    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 600.f;
    SpringArmComp->bUsePawnControlRotation = true;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp);
    CameraComp->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayCharacter::BeginPlay()
{
    Super::BeginPlay();

    //Add Input Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
            UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            //addedMappingContext = true;
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

//Called every frame
void APlayCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);


    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        //Look
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayCharacter::Look);

        //Moving
        EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayCharacter::Move);

        //Fire
        EnhancedInputComponent->BindAction(PrimaryFireAction, ETriggerEvent::Triggered, this, &APlayCharacter::PrimaryFire);

        
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayCharacter::Jump);
        
        
    }
}



void APlayCharacter::PrimaryFire(const FInputActionValue& Value)
{
    // Check if the action is currently active (true/false)
    bool bIsPrimaryActionPressed = Value.Get<bool>();

    
    if (bIsPrimaryActionPressed)
    {
        
        FVector SocketLocation = GetMesh()->GetSocketLocation("Muzzle_01");
        FTransform SpawnTM = FTransform(GetControlRotation(), SocketLocation);
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
        GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
    }
    
}

void APlayCharacter::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    // Add yaw and pitch input to controller
    // This is taking the X and Y axes values from the X/Y Plane of the mousepad
    // and mapping them to the
    //   -Pitch(rotation about the side to side (left to right or strafe) axis, which is the Y axis in unreal)
    //   -Yaw(rotation about the vertical axis, which is the Z axis in unreal)
    //   -Roll(rotation about the forward/backward axis, which is the X axis in unreal) is ignored
    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}


void APlayCharacter::Move(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    // find out which way is forward
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // get forward vector
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

    // get right vector 
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // add movement 
    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);
}
