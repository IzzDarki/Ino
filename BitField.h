#pragma once
#ifndef INO_BITFIELD_INCLUDED
#define INO_BITFIELD_INCLUDED

#include "InoCore.h"
#include <std/TypeTraits.h>
#include <Utility.h>

namespace ino {

	template <size_t LastBit>
	struct MinimumType
	{
		using type = 
			typename std::conditional<LastBit == 0, void,
			typename std::conditional<LastBit <= 8, uint8_t,
			typename std::conditional<LastBit <= 16, uint16_t,
			typename std::conditional<LastBit <= 32, uint32_t,
			typename std::conditional<LastBit <= 64, uint64_t,
			void>::type>::type>::type>::type>::type;
	};

	template <size_t Index, size_t Bits = 1>
	class BitField
	{
	private:
		using Type = typename MinimumType<Index + Bits>::type;
		static constexpr Type Mask = (1ULL << Bits) - 1ULL;

		Type Val;

	public:
		template <class T>
		BitField& operator=(T Value)
		{
			Val = (Val & ~(Mask << Index)) | ((Value & Mask) << Index);
			return *this;
		}

		operator Type() const { return (Val >> Index) & Mask; }
		explicit operator bool() const { return Val & (Mask << Index); }

		inline BitField& operator--() { return *this -= 1; }
		inline BitField& operator++() { return *this += 1; }

		Type operator++(int) { Type Temp = *this; ++*this; return Temp; }
		Type operator--(int) { Type Temp = *this; --*this; return Temp; }

		static constexpr Type MaximalNumber = Power(2, Bits) - 1;
	
	};

	template <size_t Index>
	class BitField<Index, 1>
	{
	private:
		using Type = typename MinimumType<Index + 1>::type;
		static constexpr Type Mask = 1ULL;

		Type Val;

	public:
		BitField& operator=(bool Value)
		{
			Val = (Val & ~(Mask << Index)) | (Value << Index);
			return *this;
		}

		operator Type() const { return (Val >> Index) & Mask; }
		explicit operator bool() const { return Val & (Mask << Index); }

		static constexpr Type MaximalNumber = 1;

	};

}

#endif
