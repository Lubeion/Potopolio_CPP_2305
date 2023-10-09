#pragma once

UENUM(BlueprintType)
enum class EElements : uint8
{
	None,
	Fire,
	Ice,
	Eletric,
	Max
};

UENUM(BlueprintType)
enum class ESimpleState : uint8
{
	Idle,
	Battle,
	Dead
};

UENUM(BlueprintType)
enum class EBattleState : uint8
{
	Idle,
	Attack,
	Dash,
	Hit,
	Break,
	Dead
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	Sword,
	Bow
};

UENUM(BlueprintType)
enum class EBowState : uint8
{
	Idle,
	Draw,
	Pull,
	Fire,
	Dead
};