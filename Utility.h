#pragma once
#ifndef INO_UTILITY_INCLUDED
#define INO_UTILITY_INCLUDED

#include "InoCore.h"
#include <std/TypeTraits.h>

#include <math.h>
#include <inttypes.h>

namespace ino {

	// * ----- Math -------------------------------------------------------------------------------------------------------------------

	constexpr inline unsigned long long Power(uint8_t Base, uint8_t Exp)
	{
		return (Exp == 0 ? 1 : Power(Base, Exp - 1) * Base);
	}

	// * ----- Fold-expression helpers ------------------------------------------------------------------------------------------------

	template <bool Arg = false>
	constexpr bool FoldLogicalOr_Helper() {
		return Arg;
	}

	template <bool First, bool... Others>
	constexpr typename std::enable_if<sizeof...(Others), bool>::type FoldLogicalOr_Helper() {
		return First || FoldLogicalOr_Helper<Others...>();
	}

	template <bool Arg = true>
	constexpr bool FoldLogicalAnd_Helper() {
		return Arg;
	}

	template <bool First, bool... Others>
	constexpr typename std::enable_if<sizeof...(Others), bool>::type FoldLogicalAnd_Helper() {
		return First && FoldLogicalAnd_Helper<Others...>();
	}

	template <bool... Args>
	struct FoldLogicalOr : std::integral_constant<bool, FoldLogicalOr_Helper<Args...>()> {};

	template <bool... Args>
	struct FoldLogicalAnd : std::integral_constant<bool, FoldLogicalAnd_Helper<Args...>()> {};

	// * ----- Signed- and unsigned tests ---------------------------------------------------------------------------------------------

	template <typename T, typename std::enable_if<std::is_integral<T>::value == true, int>::type = 0>
	struct IsSigned : std::integral_constant<bool, (T)-1 < 0> {};

	template <typename T, typename std::enable_if<std::is_integral<T>::value == true, int>::type = 0>
	struct IsUnsigned : std::integral_constant<bool, !((T)-1 < 0)> {};

#define INO_IS_UNSIGNED_CHAR ((char)-1 > 0)
#define INO_IS_SIGNED_CHAR ((char)-1 < 0)

	// * ----- ElementType typetrait --------------------------------------------------------------------------------------------------

	template <typename T>
	struct ElementType_Helper { using type = void; }; // T is not an array

	template <typename T, size_t N>
	struct ElementType_Helper<T[N]> { using type = T; };

	// Just needed when std::array is in use
	//template <typename T, size_t N>
	//struct ElementType_Helper<std::array<T, N>> { using type = T; };

	template <typename T>
	struct ElementType_Helper<T&> : ElementType_Helper<T> {};

	template <typename T>
	struct ElementType_Helper<T&&> : ElementType_Helper<T> {};

	template <typename T>
	struct ElementType { using type = typename ElementType_Helper<T>::type; };

	// * ----- ReduceType typetrait ---------------------------------------------------------------------------------------------------
	
	// (const) (volatile) T (&(&))						-> T
	// (const) (volatile) T * (const) (volatile) (&(&))	-> T*	
	template <typename T, typename Enable = void>
	struct ReduceType /*{ using type = T; }*/;

	template <typename T>
	struct ReduceType<T, typename std::enable_if<!std::is_pointer<T>::value && !std::is_pointer<typename std::remove_reference<T>::type>::value>::type>
	{
		using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
	};

	template <typename T>
	struct ReduceType<T, typename std::enable_if<std::is_pointer<T>::value>::type>
	{
		using type = typename std::add_pointer<typename std::remove_cv<typename std::remove_pointer<T>::type>::type>::type;
	};

	template <typename T>
	struct ReduceType<T, typename std::enable_if<std::is_reference<T>::value && std::is_pointer<typename std::remove_reference<T>::type>::value>::type>
	{
		using type = typename ReduceType<typename std::remove_reference<T>::type>::type;
	};

	// * ----- ReduceTypeExeptConst typetrait -----------------------------------------------------------------------------------------
	
	// (volatile) T (&(&))								-> T
	// const (volatile) T (&(&))						-> const T
	// (volatile) T * (const) (volatile) (&(&))			-> T*	
	// const (volatile) T * (const) (volatile) (&(&))	-> const T*
	template <typename T, typename Enable = void>
	struct ReduceTypeExeptConst /*{ using type = T; }*/;

	template <typename T>
	struct ReduceTypeExeptConst<T, typename std::enable_if<!std::is_pointer<T>::value && !std::is_pointer<typename std::remove_reference<T>::type>::value>::type>
	{
		using type = typename std::remove_volatile<typename std::remove_reference<T>::type>::type;
	};

	template <typename T>
	struct ReduceTypeExeptConst<T, typename std::enable_if<std::is_pointer<T>::value>::type>
	{
		using type = typename std::add_pointer<typename std::remove_volatile<typename std::remove_pointer<T>::type>::type>::type;
	};

	template <typename T>
	struct ReduceTypeExeptConst<T, typename std::enable_if<std::is_reference<T>::value && std::is_pointer<typename std::remove_reference<T>::type>::value>::type>
	{
		using type = typename ReduceTypeExeptConst<typename std::remove_reference<T>::type>::type;
	};

	// * ----- ReduceTypeExeptVolatile typetrait -----------------------------------------------------------------------------------------
	
	// (const) T (&(&))									-> T
	// (const) volatile T (&(&))						-> volatile T
	// (const) T * (const) (volatile) (&(&))			-> T*	
	// (const) volatile T * (const) (volatile) (&(&))	-> volatile T*

	template <typename T, typename Enable = void>
	struct ReduceTypeExeptVolatile /*{ using type = T; }*/;

	template <typename T>
	struct ReduceTypeExeptVolatile<T, typename std::enable_if<!std::is_pointer<T>::value && !std::is_pointer<typename std::remove_reference<T>::type>::value>::type>
	{
		using type = typename std::remove_const<typename std::remove_reference<T>::type>::type;
	};

	template <typename T>
	struct ReduceTypeExeptVolatile<T, typename std::enable_if<std::is_pointer<T>::value>::type>
	{
		using type = typename std::add_pointer<typename std::remove_const<typename std::remove_pointer<T>::type>::type>::type;
	};

	template <typename T>
	struct ReduceTypeExeptVolatile<T, typename std::enable_if<std::is_reference<T>::value && std::is_pointer<typename std::remove_reference<T>::type>::value>::type>
	{
		using type = typename ReduceTypeExeptVolatile<typename std::remove_reference<T>::type>::type;
	};

	// * ----- IsElementType typetrait  -----------------------------------------------------------------------------------------------

	template <typename T1, typename T2>
	struct IsElementType : std::integral_constant<bool, std::is_array<typename std::remove_reference<T2>::type>::value && std::is_same<T1, typename ReduceType<typename ElementType<T2>::type>::type>::value> {};

	// * ----- IsElementTypeConsiderConst typetrait  ----------------------------------------------------------------------------------

	template <typename T1, typename T2>
	struct IsElementTypeConsiderConst : std::integral_constant<bool, std::is_array<typename std::remove_reference<T2>::type>::value && std::is_same<T1, typename ReduceTypeExeptConst<typename ElementType<T2>::type>::type>::value> {};

	// * ----- IsElementTypeConsiderVolatile typetrait  ----------------------------------------------------------------------------------

	template <typename T1, typename T2>
	struct IsElementTypeConsiderVolatile : std::integral_constant<bool, std::is_array<typename std::remove_reference<T2>::type>::value && std::is_same<T1, typename ReduceTypeExeptVolatile<typename ElementType<T2>::type>::type>::value> {};
	
	// * ----- Templated operator%  ---------------------------------------------------------------------------------------------------

	template <typename T1, typename T2, typename std::enable_if<std::is_integral<T1>::value && std::is_integral<T2>::value, int>::type = 0>
	constexpr static inline T2 ModOperator(T1 Lhs, T2 Rhs) { return Lhs % Rhs; }
	
	template <typename T1, typename T2, typename std::enable_if<std::is_floating_point<T1>::value || std::is_floating_point<T2>::value, int>::type = 0>
	static inline double ModOperator(T1 Lhs, T2 Rhs) { return fmod(Lhs, Rhs); }

	// * ----- Templated modf ---------------------------------------------------------------------------------------------

	template <typename T, typename std::enable_if<std::is_same<float, T>::value, int>::type = 0>
	static inline float ModFunction(T Float, T& Integer)
	{
		return modff(Float, &Integer);
	}

	template <typename T, typename std::enable_if<std::is_same<double, T>::value, int>::type = 0>
	static inline double ModFunction(T Double, T& Integer)
	{
		return modf(Double, &Integer);
	}

	template <typename T, typename std::enable_if<std::is_same<long double, T>::value, int>::type = 0>
	static inline double ModFunction(T LongDouble, T& Integer)
	{
		// sometimes there's a modfl
		double IntegerDouble;
		double RetVal = modf(static_cast<double>(LongDouble), &IntegerDouble);
		Integer = IntegerDouble;
		return RetVal;
	}

}

#endif
