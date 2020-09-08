////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 StormForge
// 
// Author : KyungKun Ko
//
// Description : String basic test
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Thread/SFSystemSynchronization.h"
#include "Thread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "String/SFToString.h"
#include "UnitTest_String.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


//


TEST_F(StringTest, CharBasic)
{
	String A("A");
	String B("B");
	String C;


	EXPECT_EQ(C.IsNullOrEmpty(), true);

	EXPECT_EQ(A.IsEqual("A"), true);
	EXPECT_EQ(A.size(), 1);
	EXPECT_EQ(A.GetLength(), 1);
	EXPECT_EQ(A.length(), 1);
	EXPECT_EQ(A.IsNullOrEmpty(), false);

	EXPECT_EQ(B.IsEqual("B"), true);

	C = A + B;
	EXPECT_EQ(C.IsEqual("AB"), true);
	EXPECT_EQ(C.length(), 2);

	String D = A;
	D.Append("B");
	D.Append(B);
	EXPECT_EQ(D.IsEqual("ABB"), true);
	EXPECT_EQ(D.length(), 3);
}
