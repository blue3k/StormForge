////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Math library
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Math/SF3DMath.h"
#include "Stream/SFStream.h"


namespace SF {

	Result operator >> (IInputStream& input, Vector4& data)
	{
		return input.Read(&data, sizeof(data));
	}

	Result operator << (IOutputStream& output, const Vector4& data)
	{
		return output.Write(&data, sizeof(data));
	}


	Result _ToString(ToStringContext& context, const Vector4& value)
	{
		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "("))
			return ResultCode::FAIL;

		if (!_FToA(context, value.x))
			return ResultCode::FAIL;


		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ","))
			return ResultCode::FAIL;

		if (!_FToA(context, value.y))
			return ResultCode::FAIL;


		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ","))
			return ResultCode::FAIL;

		if (!_FToA(context, value.z))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, ")"))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}
}

