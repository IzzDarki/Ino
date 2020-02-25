#pragma once
#ifndef INO_IEEE754_INCLUDED
#define INO_IEEE754_INCLUDED

#include "BitField.h"

namespace ino {

	union IEEE754Single {
		BitField<0, 23> Mantisa;
		BitField<23, 8> Exponent;
		BitField<31, 1> Sign;
	};

	union IEEE754Double {;
		BitField<0, 52> Mantisa;
		BitField<52, 11> Exponent;
		BitField<63, 1> Sign;
	};

	namespace IEEE754 {

		inline bool isninf(float Num)
		{
			IEEE754Single& NumParts = reinterpret_cast<IEEE754Single&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0xFF && NumParts.Sign == 1;
		}
		inline bool isninf(double Num)
		{
			IEEE754Double& NumParts = reinterpret_cast<IEEE754Double&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0x7FF && NumParts.Sign == 1;
		}
		inline bool isninf(long double Num)
		{
			IEEE754Double& NumParts = reinterpret_cast<IEEE754Double&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0x7FF && NumParts.Sign == 1;
		}

		inline bool isinf(float Num)
		{
			IEEE754Single& NumParts = reinterpret_cast<IEEE754Single&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0xFF && NumParts.Sign == 0;
		}
		inline bool isinf(double Num)
		{
			IEEE754Double& NumParts = reinterpret_cast<IEEE754Double&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0x7FF && NumParts.Sign == 0;
		}
		inline bool isinf(long double Num)
		{
			IEEE754Double& NumParts = reinterpret_cast<IEEE754Double&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0x7FF && NumParts.Sign == 0;
		}

		inline bool isnan(float Num)
		{
			IEEE754Single& NumParts = reinterpret_cast<IEEE754Single&>(Num);
			return NumParts.Mantisa != 0 && NumParts.Exponent == 0xFF;
		}
		inline bool isnan(double Num)
		{
			IEEE754Double& NumParts = reinterpret_cast<IEEE754Double&>(Num);
			return NumParts.Mantisa != 0 && NumParts.Exponent == 0x7FF;
		}
		inline bool isnan(long double Num)
		{
			IEEE754Double& NumParts = reinterpret_cast<IEEE754Double&>(Num);
			return NumParts.Mantisa != 0 && NumParts.Exponent == 0x7FF;
		}

	}

}

#endif
