////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TongScript
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFStrUtil.h"
#include "Service/SFScriptService.h"
#include "Script/Tong/SFTongScriptEnvironment.h"
#include "Script/Tong/SFTongScriptVariable.h"
#include "Script/Tong/SFTongScriptFunction.h"
#include "Script/Tong/SFTongScriptBytecode.h"
#include "Script/Tong/SFTongScriptContext.h"
#include "Script/Tong/SFTongScriptBytecodeOpCode.h"



namespace SF
{
	namespace Tong
	{

		ScriptContext::ScriptContext(ScriptEnvironment& env)
			: SF::ScriptContext(env)
			, m_VariableStack(env.GetHeap())
			, m_VairableTable(env.GetHeap())
			, m_ControlStack(env.GetHeap())
		{
		}

		ScriptContext::~ScriptContext()
		{
		}

		// Get variable
		// This function searches local context first and environment next
		Variable* ScriptContext::GetVariable(const PathString& path)
		{
			if (path.size() == 0)
				return nullptr;
			else if (path.size() == 1)
				return m_VairableTable.GetVariable(FixedString(path[0]));
			else
				return GetEnvironment().GetVariable(path);
		}

		// Call function, push current execution PCInfo and set up new one with function name
		// Function parameters should be set up beforehand
		Result ScriptContext::PrepareFunctionCall(const ScriptFunction& function)
		{
			m_ControlStack.push_back(m_BytecodeContext);
			
			m_BytecodeContext.ByteCodeData = &function.GetBytecode();
			// We don't use the first byte
			m_BytecodeContext.CurrentPosition = 1;

			return ResultCode::SUCCESS;
		}

		// Execute context
		Result ScriptContext::Execute()
		{
			Result result;

			if (m_BytecodeContext.CurrentPosition == 0)
				return ResultCode::INVALID_STATE;


			auto pByteCode = m_BytecodeContext.ByteCodeData;
			if (pByteCode == nullptr)
				return ResultCode::INVALID_POINTER;


			while (m_BytecodeContext.CurrentPosition < static_cast<int>(pByteCode->size()))
			{
				auto opCode = (*pByteCode)[m_BytecodeContext.CurrentPosition];
				if (opCode < 0 || opCode > (int)SrciptBytecodeOpCode::Max)
					return ResultCode::INVALID_BYTE_SEQUENCE;

				result = Impl::ScriptBytecode_OpCodeTable[opCode]->Execute(*this);
				if (!result || result == ResultCode::SUCCESS_YIELD)
					return result;
			}

			return result;
		}


	}

} // namespace SF


