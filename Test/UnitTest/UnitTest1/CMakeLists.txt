﻿

include_directories(
	./
	../../../3rdParties/src/gtest/gtest/googletest/include
	../../../3rdParties/src/gtest/gtest/googlemock/include
	)


set(SF_UNIT_TEST_FILES
	UnitTest1PCH.h
	UnitTest1PCH.cpp
	UnitTest1.cpp
	UnitTest_ServerConfig.cpp
	UnitTest_Zookeeper.cpp
	Test/SFTestBase.h
	Test/SFTestBase.cpp
	Test/Algorithm/UnitTest_Algorithm.h
	Test/Algorithm/Matching/SFSphericalShellManager.cpp
	Test/Algorithm/Matching/SFSphericalShellManager.h
	Test/Algorithm/Matching/UnitTest_Algorithm_MatchingPreferance.cpp
	Test/Algorithm/Matching/UnitTest_Algorithm_MatchingQueue.cpp
	Test/Algorithm/Matching/UnitTest_Algorithm_MatchingRanking.cpp
	Test/Asset/UnitTest_Asset.cpp
	Test/Container/UnitTest_AVLTreeTest.h
	Test/Container/UnitTest_AVLTreeTest_DualMap.cpp
	Test/Container/UnitTest_AVLTreeTest_DualMapPerformance.cpp
	Test/Container/UnitTest_AVLTreeTest_SortedMap.cpp
	Test/Container/UnitTest_AVLTreeTest_SortedMapPerformance.cpp
	Test/Container/UnitTest_CircularBuffer.h
	Test/Container/UnitTest_CircularBuffer.cpp
	Test/Container/UnitTest_ConcurrentContainerTest.h
	Test/Container/UnitTest_ConcurrentContainerTest.cpp
	Test/Container/UnitTest_HashTable2Test.cpp
	Test/Container/UnitTest_HashTableTest.cpp
	Test/Container/UnitTest_HashTableTest.h
	Test/Container/UnitTest_QueueTest.cpp
	Test/FBX/UnitTest_FBX.h
	Test/FBX/UnitTest_FBX.cpp
	Test/LogServer/UnitTest_Kafka.h
	Test/LogServer/UnitTest_Kafka.cpp
	Test/Math/UnitTest_Math.h
	Test/Math/UnitTest_Math_Func.cpp
	Test/Math/3D/UnitTest_Math3D_Matrix.cpp
	Test/Math/3D/UnitTest_Math3D_Quaternion.cpp
	Test/Math/3D/UnitTest_Math3D_Vector.cpp
	Test/Memory/UnitTest_Memory.h
	Test/Memory/UnitTest_Memory_CircularHeap.cpp
	Test/Memory/UnitTest_Memory_Heap.cpp
	Test/Memory/UnitTest_Memory_StackHeap.cpp
	Test/Net/UnitTest_Net.h
	Test/Net/UnitTest_Net.cpp
	Test/Net/UnitTest_NetMessageWindow.cpp
	Test/String/UnitTest_String.h
	Test/String/UnitTest_String_BasicTest.cpp
	Test/Texture/UnitTest_TextureJpg.cpp
	Test/Texture/UnitTest_TexturePng.cpp
	Test/Texture/UnitTest_TextureTGA.cpp
	Test/Thread/SFThreadTest.h
	Test/Thread/SFThreadTest.cpp
	Test/Thread/SFSystemSynchronizeTest.h
	Test/Thread/SFSystemSynchronizeTest.cpp
	Test/TongScript/UnitTest_TongScript.h
	Test/TongScript/UnitTest_TongScript_Bytecode.cpp
	Test/TongScript/UnitTest_TongScript_Compile.cpp
	Test/TongScript/UnitTest_TongScript_FileFormat.cpp
	Test/Variable/UnitTest_Variable.h
	Test/Variable/UnitTest_Variable_Table.cpp
	Test/Variable/UnitTest_Variable_Boxing.cpp
	Test/Movement/UnitTest_Movement.h
	Test/Movement/UnitTest_Movement.cpp
  )


if(WIN32)
elseif(ANDROID_PLATFORM)
elseif(IOS)
elseif(UNIX)
endif()




add_executable(SFUnitTest ${SF_UNIT_TEST_FILES})


target_link_libraries(SFUnitTest ${ENGINE_LINK_LIBS} SFProtocol ${ENGINE_LINK_LIBS} ${PLATFORM_LIBS}  gtest)


install (TARGETS SFUnitTest
         ARCHIVE DESTINATION lib COMPONENT StormForge
         LIBRARY DESTINATION lib COMPONENT StormForge
         RUNTIME DESTINATION bin COMPONENT StormForge)
