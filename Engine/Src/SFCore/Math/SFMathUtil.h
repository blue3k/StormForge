////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Math utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"


namespace SF
{

	// Math utilities
	namespace Math
	{
		template<class Type>
		SF_FORCEINLINE Type Clamp(Type mi, Type ma, Type value)
		{
			if (value < mi) value = mi;
			if (value > ma) value = ma;
			return value;
		}

		// get absolute value
		template<class Type>
		SF_FORCEINLINE Type Abs(Type value) { return value < 0 ? -value : value; }

		template<>
		SF_FORCEINLINE unsigned int Abs(unsigned int x)
		{
			return x;
		}

		template<class ValueType>
		constexpr ValueType Min(ValueType val1, ValueType val2)
		{
			return (((val1) < (val2)) ? (val1) : (val2));
		}

		template<class ValueType>
		constexpr ValueType Max(ValueType val1, ValueType val2)
		{
			return (((val1) > (val2)) ? (val1) : (val2));
		}

		// Find least significant bit index
		inline int FindLSBIndex(uint32_t value)
		{
			if (value == 0)
				return -1;

			uint32_t TestMaxBits = sizeof(decltype(value)) * 8;
			auto TestMask = static_cast<decltype(value)>(-1);
			uint32_t bitIndex = 0;

			for (int iLoop = 0; iLoop < 5; iLoop++)
			{
				TestMaxBits >>= 1;
				TestMask >>= TestMaxBits;
				if ((TestMask & value) == 0)
				{
					value >>= TestMaxBits;
					bitIndex += TestMaxBits;
				}
			}

			return bitIndex;
		}


		SF_FORCEINLINE float DistanceCmToM(float cm)
		{
			return cm / 100.f;
		}


		SF_FORCEINLINE float SlerpDegree(float a, float b, float t)
		{
			a = Math::Clamp(0.f, 360.f, a);
			b = Math::Clamp(0.f, 360.f, b);

			if (Math::Abs(a - b) < 180)
			{
				return a + (b - a) * t;
			}
			else
			{
				if (a > b)
				{
					b += 360;
				}
				else
				{
					a += 360;
				}
				return Math::Clamp(0.f, 360.f, a + (b - a) * t);
			}
		}
	}



} //namespace SF



