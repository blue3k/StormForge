////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Memory allocation library
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Memory/SFIMemoryManager.h"
#include "Container/SFDoubleLinkedListBase.h"


// Enable memory allocation trace
#define ENABLE_MEMORY_TRACE true



namespace SF {

	class IHeap;
	class IHeap;
	class MemoryPool;

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Memory block descriptor
	//

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	// Check CRT heap memory status
	inline void CheckCtrMemory()
	{
		//Assert( _CrtCheckMemory( ) );
	}

#else
	inline void CheckCtrMemory()
	{
		//Assert(_CrtCheckMemory());
	}
#endif




#pragma pack(push)
#pragma pack(1)
	struct MemBlockHdr
	{
		static constexpr uint16_t MEM_MAGIC = 0x187e;
		static constexpr uint16_t MEM_MAGIC_FREE = 0xCDCD;

		uint16_t Magic			= MEM_MAGIC_FREE;
		uint16_t DataOffset		= 0;				// Data offset from the header
		uint32_t Size			= 0;				// Allocated memory size. We don't support bigger than 4GB allocation
		IHeap* pHeap			= nullptr;


#if ENABLE_MEMORY_TRACE
		DoubleLinkedListNode ListNode;
		CallStackTrace StackTrace;
		ThreadID LatestThreadID;
#endif

		void Init(IHeap* heap, uint32_t size, uint32_t dataOffset);

		void* GetDataPtr() { return (uint8_t*)this + DataOffset; }
	};
#pragma pack(pop)

	
} // namespace SF


void* operator new(size_t size, SF::IHeap& heap);
void operator delete(void* pBuff, SF::IHeap& heap) noexcept;

void* operator new[] (size_t size, SF::IHeap& heap);
void operator delete[](void* pBuff, SF::IHeap& heap) noexcept;


