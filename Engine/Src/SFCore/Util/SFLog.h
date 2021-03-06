////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Log
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Service/SFLogService.h"
#include "Util/SFStrUtil.h"
#include "Container/SFArray.h"
#include "Container/SFSpinBufferMT.h"
#include "Util/SFStrFormat.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Component/SFLibraryComponent.h"





namespace SF {
namespace Log {


	class LogOutputHandler;



	/////////////////////////////////////////////////////////////////////////
	//
	//	Log module
	//


	class LogModule : public LibraryComponent, public LogService
	{
	public:
		static constexpr StringCrc64 TypeName = "LogModule";

		//Structure for Spin Buffer
		struct LogItem
		{
			LogChannel* Channel = nullptr;
			LogOutputType		OutputType{};
			LogOutputMask		OutputMask{}; // GlobalMask & LogChannelMask
			SystemTimeStampMS	TimeStamp{};
			size_t LogStringSize = 0;
			char	LogBuff[3 * 1024]{};

			LogItem()
			{
			}
		};

		typedef SpinBufferMT<LogItem, 128> LogSpinBuffer;

	private:

		FunctorThread m_Thread;

		// output handler array
		DynamicArray<LogOutputHandler*> m_OutputHandlers;

		LogSpinBuffer m_LogSpinBuffer;

		TimeStampMS m_LogTimeMS;

	protected:

		void Run(Thread* pThread);

	public:

		LogModule(const LogOutputMask& logOutputGlobalMask = LogOutputMask());
		~LogModule();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		virtual Result InitializeComponent() override;
		virtual void DeinitializeComponent() override;


		// output handler
		virtual void RegisterOutputHandler(LogOutputHandler* output) override;
		virtual void UnregisterOutputHandler(LogOutputHandler* output) override;

		// Reserve write buffer
		virtual void* ReserveWriteBuffer() override;
		virtual void ReleaseWriteBuffer(void* block, size_t messageSize) override;
		virtual size_t WriteTimeTag(void* pLogItem) override;

		// Flush log queue
		virtual void Flush() override;

	};




	/////////////////////////////////////////////////////////////////////////
	//
	//	Log output handler
	//

	class LogOutputHandler
	{
	private:

		LogOutputMask m_OutputMask;

	public:

		LogOutputHandler(const LogOutputMask& outputMask);
		virtual ~LogOutputHandler();

		const LogOutputMask& GetOutputMask() { return m_OutputMask; }
		void SetOutputMask(const LogOutputMask& value) { m_OutputMask = value; }

		virtual void PrintOutput(const LogModule::LogItem* logMessage) = 0;

		// flush output if it uses buffering
		virtual void Flush() {}
	};





} // namespace Log

} // namespace SF




//////////////////////////////////////////////////////////////////////////////////////
//
//  Declare trace module
//

#define SFLog(channel,outputType, ...) SFLog2(::SF::Log::channel, ::SF::LogOutputType::outputType, __VA_ARGS__)


#define SFLog2(channel,outputType, ...) \
		do{\
			auto* pLogService = *::SF::Service::LogModule;\
			if( (pLogService != nullptr) )\
			{\
				auto channelMask = channel.ChannelMask;\
				auto outputMask = ::SF::LogService::ToChannelMask(outputType);\
				if (pLogService->ShouldPrint(channelMask, outputMask))\
				{\
					auto block = (::SF::Log::LogModule::LogSpinBuffer::BLOCK*)pLogService->ReserveWriteBuffer(); \
					if (block == nullptr) break; \
					block->Data.Channel = &channel;\
					block->Data.OutputType = outputType;\
					block->Data.OutputMask = outputMask & channelMask; \
					auto messageSize = pLogService->WriteTimeTag(&block->Data); if(messageSize > 0) messageSize--; \
					auto remainBuffSize = static_cast<int>(sizeof(block->Data.LogBuff) - messageSize);\
					messageSize += SF::StrUtil::Format(block->Data.LogBuff + messageSize, remainBuffSize, __VA_ARGS__) - 1; \
					pLogService->ReleaseWriteBuffer(block, messageSize); \
				}\
			}\
		}while(0);\
		\


#ifdef DEBUG
#define SFLogDebug(channel,outputType, ...) SFLog(channel,Debug,__VA_ARGS__)
#else
#define SFLogDebug(channel,outputType, ...)
#endif



/////////////////////////////////////////////////
//
// Error Jump Macros.
//
/////////////////////////////////////////////////

// gradually deprecated
#define SFErrJmp(channel, errval) \
	do {\
		hr = errval;\
		SFLog(channel, Error, "{0}({1}): {2}", (const char*)__FILE__, __LINE__, hr ); \
		goto Proc_End;\
	} while(0);


//#ifdef DEBUG

#define SFCheckResult(trcMod, Op) \
	do {\
		hr = (Op);\
		if (!hr) { \
			SFLog(trcMod, Error, "{0}({1}): {2}", __FILE__, __LINE__, (Result)hr );    \
			return hr;\
		}\
	} while(0);

#define SFCheckMem(trcMod, Op) \
	do {\
		hr = (Op) != nullptr ? ResultCode::SUCCESS : ResultCode::OUT_OF_MEMORY;\
		if (!hr) { \
			SFLog(trcMod, Error, "{0}({1}): {2}", __FILE__, __LINE__, (Result)hr );    \
			return hr;\
		}\
	} while(0);


#define SFCheckPtr(trcMod, Op) \
	do {\
		hr = (Op) != nullptr ? ResultCode::SUCCESS : ResultCode::INVALID_POINTER;\
		if (!hr) { \
			SFLog(trcMod, Error, "{0}({1}): {2}", __FILE__, __LINE__, (Result)hr );    \
			return hr;\
		}\
	} while(0);

//#else // #ifdef DEBUG
//
//#define SFCheckResult(trcMod, Op) \
//	do {\
//		hr = (Op);\
//		if (!hr) { \
//			return hr;\
//		}\
//	} while(0);
//
//#define SFCheckMem(trcMod, Op) \
//	do {\
//		hr = (Op) != nullptr ? ResultCode::SUCCESS : ResultCode::OUT_OF_MEMORY;\
//		if (!hr) { \
//			return hr;\
//		}\
//	} while(0);
//
//
//#define SFCheckPtr(trcMod, Op) \
//	do {\
//		hr = (Op) != nullptr ? ResultCode::SUCCESS : ResultCode::INVALID_POINTER;\
//		if (!hr) { \
//			return hr;\
//		}\
//	} while(0);
//
//#endif // #ifdef DEBUG
