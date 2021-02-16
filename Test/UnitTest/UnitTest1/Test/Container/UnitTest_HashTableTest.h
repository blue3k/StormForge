////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 The Braves
// 
// Author : KyungKun Ko
//
// Description : Memroy test
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Container/SFHashTable.h"
#include "../SFTestBase.h"




class HashTableTest : public MyTestBase
{
protected:

	// Thread module test
	std::vector<SF::Thread*>	m_Threads;

	SF::SpinLock m_LockObject;

public:

	void StopAllThread()
	{
		for( auto itCur = m_Threads.begin(); itCur != m_Threads.end(); ++itCur)
		{
			SF::Thread *pThread = *itCur;
			if( pThread ) pThread->Stop( true );
			delete pThread;
		}
		m_Threads.clear();
	}

	// Remember that SetUp() is run immediately before a test starts.
	virtual void SetUp()
	{
		MyTestBase::SetUp();
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		MyTestBase::TearDown();

		StopAllThread();
	}
};




