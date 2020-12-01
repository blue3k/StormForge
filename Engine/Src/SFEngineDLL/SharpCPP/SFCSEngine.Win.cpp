////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine interface
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Application/Win/WindowsApp.h"
#include "Application/Win/WindowsAppTasks.h"

#include "Service/SFLogService.h"
#include "Task/SFAsyncTaskManager.h"
#include "Util/SFLog.h"
#include "Util/SFLogComponent.h"
#include "Object/SFObjectManager.h"
#include "Util/SFTimeUtil.h"
#include "String/SFStrUtil.h"
#include "EngineObject/SFEngineObjectManager.h"
#include "EngineObject/SFEngineTaskManager.h"
#include "Net/SFNetSystem.h"
#include "Net/SFConnectionManager.h"
#include "Resource/SFResourceManager.h"
#include "Graphics/SFGraphicDeviceGLES.h"
#include "Net/SFNetConst.h"
#include "Service/SFServices.h"
#include "Service/SFEngineService.h"
#include "SFEngine.h"



//////////////////////////////////////////////////////////////////////////////////////
//
//	Engine interface
//

SFDLL_EXPORT SF::Engine* SFEngine_NativeStartEngineEmpty()
{
	SF::LogOutputMask logOutputMask;

	SF::EngineInitParam initParam;
#ifdef _DEBUG
	initParam.EnableMemoryLeakDetection = false;
	SF::Log::Net.ChannelMask.Info = 1;
	SF::Log::Net.ChannelMask.Warning = 1;
	SF::Log::Net.ChannelMask.Error = 1;
	SF::Log::Net.ChannelMask.Assert = 1;
	SF::Log::Net.ChannelMask.Debug1 = 1;
	logOutputMask.Custom1 = 1;
	logOutputMask.Custom2 = 1;
	logOutputMask.Custom3 = 1;
	logOutputMask.Custom4 = 1;
	logOutputMask.Custom5 = 1;
	logOutputMask.Custom6 = 1;
	logOutputMask.Custom7 = 1;
	logOutputMask.Custom8 = 1;
	logOutputMask.Custom9 = 1;
	logOutputMask.Custom10 = 1;
	logOutputMask.Debug1 = 1;
	logOutputMask.Debug2 = 0;
	logOutputMask.Debug3 = 0;
#else

	logChannelParameter.MainChannelMasks[(int)SF::LogMainChannels::Net] = { 0, };
	logChannelParameter.SubChannelMask.Custom1 = 0;
	logChannelParameter.SubChannelMask.Custom2 = 0;
	logChannelParameter.SubChannelMask.Custom3 = 0;
	logChannelParameter.SubChannelMask.Custom4 = 0;
	logChannelParameter.SubChannelMask.Custom5 = 0;
	logChannelParameter.SubChannelMask.Custom6 = 0;
	logChannelParameter.SubChannelMask.Custom7 = 0;
	logChannelParameter.SubChannelMask.Custom8 = 0;
	logChannelParameter.SubChannelMask.Custom9 = 0;
	logChannelParameter.SubChannelMask.Custom10 = 0;
	logChannelParameter.SubChannelMask.Debug = 0;
	logChannelParameter.SubChannelMask.Debug1 = 0;
	logChannelParameter.SubChannelMask.Debug2 = 0;
	logChannelParameter.SubChannelMask.Debug3 = 0;
#endif
	initParam.EnableMemoryLeakDetection = false;

	static char InstanceName[128];
	srand(clock());
	SF::StrUtil::Format(InstanceName, "StormForge");
	initParam.GlobalLogOutputMask = logOutputMask;
	initParam.LogOutputConsole = { 0, };
	initParam.LogOutputDebugger = { 0, };
	initParam.LogFilePrefix = InstanceName;
	initParam.LogOutputFile = SF::LogOutputMask(-1); // print all
	// For stress test
	initParam.AsyncTaskThreadCount = 6;
	initParam.NetworkThreadCount = 4;

	auto pEngine = SF::Engine::Start(initParam);
	return pEngine;
}

SFDLL_EXPORT SF::Engine* SFEngine_NativeStartEngine(void* context)
{
	SF::EngineInitParam initParam;
#ifdef _DEBUG
	initParam.EnableMemoryLeakDetection = true;
#else
	initParam.EnableMemoryLeakDetection = false;
#endif

	initParam.LogOutputConsole = false;
	initParam.GraphicSystem = "Vulkan";
	auto pEngine = SF::Engine::Start(initParam);
	return pEngine;
}

SFDLL_EXPORT void SFEngine_NativeStopEngine()
{
	SF::Engine::Stop();
}

SFDLL_EXPORT void SFEngine_NativeFocused(bool focused)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::WindowsApp>();
	if (focused)
		pApp->SendCommand<SF::WindowsAppTask_GainFocus>();
	else
		pApp->SendCommand<SF::WindowsAppTask_LostFocus>();
}


SFDLL_EXPORT void SFEngine_NativeWindowCreated(intptr_t nativeHandle)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::WindowsApp>();
	pApp->SendCommand<SF::WindowsAppTask_InitWindow>((NativeWindow)nativeHandle);
}


SFDLL_EXPORT void SFEngine_NativeWindowClosed(intptr_t nativeHandle)
{
	auto pApp = SF::Engine::GetEngineComponent<SF::WindowsApp>();
	pApp->SendCommand<SF::WindowsAppTask_DestroyWindow>();
}


SFDLL_EXPORT void SFEngine_NativeWindowResized()
{
	auto pApp = SF::Engine::GetEngineComponent<SF::WindowsApp>();
	pApp->SendCommand<SF::WindowsAppTask_WindowResized>();
}

#endif
