////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Shared pointer
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Memory/SFMemory.h"
#include "Object/SFSharedObject.h"
#include "Thread/SFSynchronization.h"
#include "Object/SFSharedObjectManager.h"
#include "Object/SFSharedPointer.h"


namespace SF {

	///////////////////////////////////////////////////////////////////////////
	//
	//
	//

	SharedObject::SharedObject()
		: m_ReferenceCount(0)
		, m_WeakReferenceCount(1)
		, m_ManagerReferenceCount(0)
		, m_ReferenceManagerObject(nullptr)
	{
		// Shared Object has to be allocated with memory manager
		// - Not if you make static instance
		//GetSystemHeap().CheckMemoryHeader(this);
	}

	SharedObject::~SharedObject()
	{
		assert(m_ManagerReferenceCount == 0);
		assert(m_ReferenceManagerObject == nullptr);
	}

	CounterType SharedObject::AddReference() const
	{
		auto org = m_ReferenceCount.fetch_add(1, std::memory_order_acquire);
		if (org == 0)
		{
			// First shared reference should have one designated weak reference
			Assert(GetWeakReferenceCount() == 1);
		}
		return org;
	}

	CounterType SharedObject::ReleaseReference() const
	{
		//auto refManager = m_ReferenceManagerObject;
		auto org = m_ReferenceCount.fetch_sub(1, std::memory_order_release);
		auto decValue = org - 1;
		if (decValue <= 0)
		{
			const_cast<SharedObject*>(this)->Dispose();

			ReleaseWeakReference();
		}
		return org;
	}

	CounterType SharedObject::AddWeakReference() const
	{
		return m_WeakReferenceCount.fetch_add(1, std::memory_order_acquire);
	}

	CounterType SharedObject::ReleaseWeakReference() const
	{
		CounterType org = 0;
		if (m_ReferenceManagerObject != nullptr)
		{
			auto localRef = m_ReferenceManagerObject;
			Assert(localRef != nullptr);
			auto decValue = org = m_WeakReferenceCount.fetch_sub(1, std::memory_order_release);
			if (decValue <= 1)
			{
				localRef->FreeSharedReference(const_cast<SharedObject*>(this)
#ifdef REFERENCE_DEBUG_TRACKING
					, fileName, lineNumber
#endif
					);
			}
		}
		else
		{
			auto decValue = org = m_WeakReferenceCount.fetch_sub(1, std::memory_order_acquire);
			if (decValue <= 1)
			{
				AssertRel(decValue == 1);
				delete this;
			}
		}

		return org;
	}


	void SharedObject::GetSharedPointer(SharedPointer& shardPointer) const
	{
		ReferenceCounterType curReference;
		do
		{
			curReference = m_ReferenceCount.load(std::memory_order_consume);
			if (curReference <= 0)
			{
				shardPointer = SharedPointer();
				return;
			}
		} while (!m_ReferenceCount.compare_exchange_weak(curReference, curReference + 1, std::memory_order_relaxed, std::memory_order_relaxed));

		shardPointer.SetPointer(const_cast<SharedObject*>(this));
	}

	///////////////////////////////////////////////////////////////////////////
	//
	//
	//


}
