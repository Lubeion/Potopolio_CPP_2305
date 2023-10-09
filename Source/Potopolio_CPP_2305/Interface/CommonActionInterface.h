// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommonActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommonActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POTOPOLIO_CPP_2305_API ICommonActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginActionA()	 PURE_VIRTUAL(ICommonActionInterface::BeginActionA, return;)
	virtual void EndActionA()	 PURE_VIRTUAL(ICommonActionInterface::EndActionA, return;)
	virtual void BeginActionB()	 PURE_VIRTUAL(ICommonActionInterface::BeginActionB, return;)
	virtual void EndActionB()	 PURE_VIRTUAL(ICommonActionInterface::EndActionB, return;)
	virtual void BeginAction1()	 PURE_VIRTUAL(ICommonActionInterface::BeginActionC, return;)
	virtual void EndAction1()	 PURE_VIRTUAL(ICommonActionInterface::EndActionC, return;)
	virtual void BeginAction2()	 PURE_VIRTUAL(ICommonActionInterface::BeginActionD, return;)
	virtual void EndAction2()	 PURE_VIRTUAL(ICommonActionInterface::EndActionD, return;)
	virtual void BeginAction3()	 PURE_VIRTUAL(ICommonActionInterface::BeginActionE, return;)
	virtual void EndAction3()	 PURE_VIRTUAL(ICommonActionInterface::EndActionE, return;)
	virtual void BeginAction4()	 PURE_VIRTUAL(ICommonActionInterface::BeginActionF, return;)
	virtual void EndAction4()	 PURE_VIRTUAL(ICommonActionInterface::EndActionF, return;)

};
