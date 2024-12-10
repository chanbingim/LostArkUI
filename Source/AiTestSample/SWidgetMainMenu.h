// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
/**
 * 
 */
class AITESTSAMPLE_API SWidgetMainMenu : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWidgetMainMenu) {}
	//SLATE_ARGUMENT(TWeakObjectPtr<Class> AMenuHUD>, OwnningHUD)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AMenuHUD> OwnningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };

};
