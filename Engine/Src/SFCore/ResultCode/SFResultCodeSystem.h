////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description :  System predefined error code, same value with HRESULT
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <stdint.h>



namespace SF
{
	namespace ResultCode
	{
		constexpr Result SUCCESS((int32_t)0x00000000L);
		constexpr Result SUCCESS_FALSE((int32_t)0x00000001L);
		constexpr Result SUCCESS_YIELD((int32_t)0x00000002L);
		constexpr Result INVALID_POINTER((int32_t)0xC0000002L);
		constexpr Result FAIL((int32_t)0xC0000003L);
		constexpr Result NOT_IMPLEMENTED((int32_t)0xC0000004L);
		constexpr Result OUT_OF_MEMORY((int32_t)0xC0000005L);
		constexpr Result UNEXPECTED((int32_t)0xC0000006L);
		constexpr Result INVALID_ARG((int32_t)0xC0000007L);

		constexpr Result NO_DATA_EXIST((int32_t)0xC0001008L);

	};
}

#include "SFResultCodeLibrary.h"




