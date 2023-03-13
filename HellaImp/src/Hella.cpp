#pragma once
#include"hlpch.h"
#include "Hella.h"

/*
	@author:Haruluya.
	@function:core functions of hella.
*/

void Hella::InitCore() {

	Hella::Log::Init();

	HELLA_CORE_INFO("{}",
		Util::LetStrConsoleCenter("HELLA CORE INIT", '-')
		);
}

void Hella::ShutdownCore()
{
	HELLA_CORE_INFO("{}",
		Util::LetStrConsoleCenter("HELLA CORE SHUNTDOWN", '-')
	);
	Hella::Log::Shutdown();

}



