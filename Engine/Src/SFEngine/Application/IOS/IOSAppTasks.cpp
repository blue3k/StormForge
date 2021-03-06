////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic IOS application
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"

#if SF_PLATFORM == SF_PLATFORM_IOS

#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "Application/IOS/IOSApp.h"
#include "Application/IOS/IOSAppTasks.h"
#include "Service/SFEngineService.h"
#include "SFEngine.h"
#include "Graphics/SFGraphicDeviceGLES.h"



namespace SF
{

	IOSAppTask::IOSAppTask(ApplicationBase* app)
		: m_pApp((IOSApp*)app)
	{

	}


	/////////////////////////////////////////////////////////////////
	//
	//	App EngineTask
	//



	IOSAppTask_InitWindow::IOSAppTask_InitWindow(ApplicationBase* app, NativeWindow pWindow)
		: IOSAppTask(app)
		, m_Window(pWindow)
	{
	}

	IOSAppTask_InitWindow::~IOSAppTask_InitWindow()
	{
		//if (m_Window != nullptr)
		//	ANativeWindow_release(m_Window);
	}

	void IOSAppTask_InitWindow::Run()
	{
		if (m_Window != nullptr)
		{
			Service::GraphicDevice->InitDisplay(m_Window);
			m_Window = nullptr;
		}
		Finished();
	}


	IOSAppTask_DestroyWindow::IOSAppTask_DestroyWindow(ApplicationBase* app)
		: IOSAppTask(app)
	{
	}

	void IOSAppTask_DestroyWindow::Run()
	{
		Service::GraphicDevice->DeinitDisplay();
		Finished();
	}


	IOSAppTask_WindowResized::IOSAppTask_WindowResized(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_WindowResized::Run()
	{
		Finished();
	}


	IOSAppTask_GainFocus::IOSAppTask_GainFocus(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_GainFocus::Run()
	{
		GetApp()->SetPaused(false);

		Finished();
	}


	IOSAppTask_LostFocus::IOSAppTask_LostFocus(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_LostFocus::Run()
	{
		GetApp()->SetPaused(true);

		Finished();
	}


	IOSAppTask_LowMemory::IOSAppTask_LowMemory(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_LowMemory::Run()
	{
		Finished();
	}


	IOSAppTask_AppStart::IOSAppTask_AppStart(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_AppStart::Run()
	{
		Finished();
	}


	IOSAppTask_AppStop::IOSAppTask_AppStop(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_AppStop::Run()
	{
		Finished();
	}


	IOSAppTask_Pause::IOSAppTask_Pause(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_Pause::Run()
	{
		GetApp()->SetPaused(true);
		Finished();
	}


	IOSAppTask_Resume::IOSAppTask_Resume(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_Resume::Run()
	{
		GetApp()->SetPaused(false);
		Finished();
	}


	IOSAppTask_ConfigChanged::IOSAppTask_ConfigChanged(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_ConfigChanged::Run()
	{
		Finished();
	}


	IOSAppTask_SaveState::IOSAppTask_SaveState(ApplicationBase* app)
		: IOSAppTask(app)
	{

	}

	void IOSAppTask_SaveState::Run()
	{
		// TODO::
		Finished();
	}




}
#else
void IOSAppTasks_Dummy() {}
#endif
