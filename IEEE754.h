#pragma once
#ifndef INO_IEEE754_INCLUDED
#define INO_IEEE754_INCLUDED

#include "InoCore.h"
#include "BitField.h"

namespace ino {

	union IEEE754Single {
		float Float;
		BitField<0, 23> Mantisa;
		BitField<23, 8> Exponent;
		BitField<31, 1> Sign;
	};

	union IEEE754Double {
		BitField<0, 52> Mantisa;
		BitField<52, 11> Exponent;
		BitField<63, 1> Sign;
	};

	namespace IEEE754 {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"

		template <typename T, typename std::enable_if<std::is_floating_point<T>::value && sizeof(T) == 4, int>::type = 0>
		inline bool isninf(T Num)
		{
			const IEEE754Single& NumParts = reinterpret_cast<const IEEE754Single&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0xFF && NumParts.Sign == 1;
		}

		template <typename T, typename std::enable_if<std::is_floating_point<T>::value && sizeof(T) == 8, int>::type = 0>
		inline bool isninf(T Num)
		{
			const IEEE754Double& NumParts = reinterpret_cast<const IEEE754Double&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0x7FF && NumParts.Sign == 1;
		}

		template <typename T, typename std::enable_if<std::is_floating_point<T>::value && sizeof(T) == 4, int>::type = 0>
		inline bool isinf(T Num)
		{
			const IEEE754Single& NumParts = reinterpret_cast<const IEEE754Single&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0xFF && NumParts.Sign == 0;
		}

		template <typename T, typename std::enable_if<std::is_floating_point<T>::value && sizeof(T) == 8, int>::type = 0>
		inline bool isinf(T Num)
		{
			const IEEE754Double& NumParts = reinterpret_cast<const IEEE754Double&>(Num);
			return NumParts.Mantisa == 0 && NumParts.Exponent == 0x7FF && NumParts.Sign == 0;
		}

		template <typename T, typename std::enable_if<std::is_floating_point<T>::value && sizeof(T) == 4, int>::type = 0>
		inline bool isnan(T Num)
		{
			const IEEE754Single& NumParts = reinterpret_cast<const IEEE754Single&>(Num);
			return NumParts.Mantisa != 0 && NumParts.Exponent == 0xFF;
		}

		template <typename T, typename std::enable_if<std::is_floating_point<T>::value && sizeof(T) == 8, int>::type = 0>
		inline bool isnan(T Num)
		{
			const IEEE754Double& NumParts = reinterpret_cast<const IEEE754Double&>(Num);
			return NumParts.Mantisa != 0 && NumParts.Exponent == 0x7FF;
		}

#pragma GCC diagnostic pop

	}

}

#endif
