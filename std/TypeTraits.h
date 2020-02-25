#pragma once
#ifndef INO_STD_TYPETRAITS_INCLUDED
#define INO_STD_TYPETRAITS_INCLUDED

#include <stddef.h>

//mostly copied from C++ standard implementations
namespace std {

		// STRUCT TEMPLATE integral_constant
	template<class _Ty,
		_Ty _Val>
		struct integral_constant
		{	// convenient template for integral constant types
		static constexpr _Ty value = _Val;

		using value_type = _Ty;
		using type = integral_constant;

		constexpr operator value_type() const noexcept
			{	// return stored value
			return (value);
			}

		constexpr value_type operator()() const noexcept
			{	// return stored value
			return (value);
			}
		};

	using true_type = integral_constant<bool, true>;
	using false_type = integral_constant<bool, false>;

		// STRUCT TEMPLATE enable_if
	template<bool _Test,
		class _Ty = void>
		struct enable_if
		{	// type is undefined for assumed !_Test
		};

	template<class _Ty>
		struct enable_if<true, _Ty>
		{	// type is _Ty for _Test
		using type = _Ty;
		};

		// STRUCT TEMPLATE conditional
	template<bool _Test,
		class _Ty1,
		class _Ty2>
		struct conditional
		{	// type is _Ty2 for assumed !_Test
		using type = _Ty2;
		};

	template<class _Ty1,
		class _Ty2>
		struct conditional<true, _Ty1, _Ty2>
		{	// type is _Ty1 for _Test
		using type = _Ty1;
		};

		// STRUCT TEMPLATE is_same
	template<class _Ty1,
		class _Ty2>
		struct is_same
			: false_type
		{	// determine whether _Ty1 and _Ty2 are the same type
		};

	template<class _Ty1>
		struct is_same<_Ty1, _Ty1>
			: true_type
		{	// determine whether _Ty1 and _Ty2 are the same type
		};

		// STRUCT TEMPLATE remove_const
	template<class _Ty>
		struct remove_const
		{	// remove top level const qualifier
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_const<const _Ty>
		{	// remove top level const qualifier
		using type = _Ty;
		};

		// STRUCT TEMPLATE remove_volatile
	template<class _Ty>
		struct remove_volatile
		{	// remove top level volatile qualifier
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_volatile<volatile _Ty>
		{	// remove top level volatile qualifier
		using type = _Ty;
		};

		// STRUCT TEMPLATE remove_cv
	template<class _Ty>
		struct remove_cv
		{	// remove top level const and volatile qualifiers
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_cv<const _Ty>
		{	// remove top level const and volatile qualifiers
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_cv<volatile _Ty>
		{	// remove top level const and volatile qualifiers
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_cv<const volatile _Ty>
		{	// remove top level const and volatile qualifiers
		using type = _Ty;
		};

		// STRUCT TEMPLATE _Is_integral
	template<class _Ty>
		struct _Is_integral
			: false_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<bool>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<char>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<unsigned char>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<signed char>
			: true_type
		{	// determine whether _Ty is integral
		};

	#ifdef _NATIVE_WCHAR_T_DEFINED
	template<>
		struct _Is_integral<wchar_t>
			: true_type
		{	// determine whether _Ty is integral
		};
	#endif /* _NATIVE_WCHAR_T_DEFINED */

	template<>
		struct _Is_integral<char16_t>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<char32_t>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<unsigned short>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<short>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<unsigned int>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<int>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<unsigned long>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<long>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<unsigned long long>
			: true_type
		{	// determine whether _Ty is integral
		};

	template<>
		struct _Is_integral<long long>
			: true_type
		{	// determine whether _Ty is integral
		};

		// STRUCT TEMPLATE is_integral
	template<class _Ty>
		struct is_integral
			: _Is_integral<typename remove_cv<_Ty>::type>::type
		{	// determine whether _Ty is integral
		};

		// STRUCT TEMPLATE _Is_floating_point
	template<class _Ty>
		struct _Is_floating_point
			: false_type
		{	// determine whether _Ty is floating point
		};

	template<>
		struct _Is_floating_point<float>
			: true_type
		{	// determine whether _Ty is floating point
		};

	template<>
		struct _Is_floating_point<double>
			: true_type
		{	// determine whether _Ty is floating point
		};

	template<>
		struct _Is_floating_point<long double>
			: true_type
		{	// determine whether _Ty is floating point
		};

		// STRUCT TEMPLATE is_floating_point
	template<class _Ty>
		struct is_floating_point
			: _Is_floating_point<typename remove_cv<_Ty>::type>
		{	// determine whether _Ty is floating point
		};

		// STRUCT TEMPLATE is_arithmetic
	template<class _Ty>
		struct is_arithmetic
			: integral_constant<bool, is_integral<_Ty>::value
				|| is_floating_point<_Ty>::value>
		{	// determine whether _Ty is an arithmetic type
		};

		// STRUCT TEMPLATE remove_reference
	template<class _Ty>
		struct remove_reference
		{	// remove reference
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_reference<_Ty&>
		{	// remove reference
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_reference<_Ty&&>
		{	// remove rvalue reference
		using type = _Ty;
		};

// type_traits

		// STRUCT TEMPLATE integer_sequence
	template<class _Ty,
		_Ty... _Vals>
		struct integer_sequence
		{	// sequence of integer parameters
		static_assert(is_integral<_Ty>::value,
			"integer_sequence<T, I...> requires T to be an integral type.");

		using value_type = _Ty;

		static constexpr size_t size() noexcept
			{	// get length of parameter list
			return (sizeof...(_Vals));
			}
		};

		// STRUCT TEMPLATE conjunction
	template<bool _First_value,
		class _First,
		class... _Rest>
		struct _Conjunction
		{	// handle false trait or last trait
		using type = _First;
		};

	template<class _True,
		class _Next,
		class... _Rest>
		struct _Conjunction<true, _True, _Next, _Rest...>
		{	// the first trait is true, try the next one
		using type = typename _Conjunction<_Next::value, _Next, _Rest...>::type;
		};

	template<class... _Traits>
		struct conjunction
			: true_type
		{	// If _Traits is empty, true_type
		};

	template<class _First,
		class... _Rest>
		struct conjunction<_First, _Rest...>
			: _Conjunction<_First::value, _First, _Rest...>::type
		{	// Otherwise, if any of _Traits are false, the first false trait
			// Otherwise, the last trait in _Traits
		};

		// STRUCT TEMPLATE disjunction
	template<bool _First_value,
		class _First,
		class... _Rest>
		struct _Disjunction
		{	// handle true trait or last trait
		using type = _First;
		};

	template<class _False,
		class _Next,
		class... _Rest>
		struct _Disjunction<false, _False, _Next, _Rest...>
		{	// first trait is false, try the next trait
		using type = typename _Disjunction<_Next::value, _Next, _Rest...>::type;
		};

	template<class... _Traits>
		struct disjunction
			: false_type
		{	// If _Traits is empty, false_type
		};

	template<class _First,
		class... _Rest>
		struct disjunction<_First, _Rest...>
			: _Disjunction<_First::value, _First, _Rest...>::type
		{	// Otherwise, if any of _Traits are true, the first true trait
			// Otherwise, the last trait in _Traits
		};

		// STRUCT TEMPLATE negation
	template<class _Trait>
		struct negation
			: integral_constant<bool, !static_cast<bool>(_Trait::value)>
		{	// The negated result of _Trait
		};

		// STRUCT TEMPLATE is_void
	template<class _Ty>
		struct is_void
			: false_type
		{	// determine whether _Ty is void
		};

	template<>
		struct is_void<void>
			: true_type
		{	// determine whether _Ty is void
		};

	template<>
		struct is_void<const void>
			: true_type
		{	// determine whether _Ty is void
		};

	template<>
		struct is_void<volatile void>
			: true_type
		{	// determine whether _Ty is void
		};

	template<>
		struct is_void<const volatile void>
			: true_type
		{	// determine whether _Ty is void
		};

	template <typename... _Types>
		struct _void_t
		{   //always void
			using type = void;
		};

		// Type modifiers
		// STRUCT TEMPLATE add_const
	template<class _Ty>
		struct add_const
		{	// add top level const qualifier
		using type = const _Ty;
		};

		// STRUCT TEMPLATE add_volatile
	template<class _Ty>
		struct add_volatile
		{	// add top level volatile qualifier
		using type = volatile _Ty;
		};

		// STRUCT TEMPLATE add_cv
	template<class _Ty>
		struct add_cv
		{	// add top level const and volatile qualifiers
		using type = const volatile _Ty;
		};

		// STRUCT TEMPLATE _Add_reference
	template<class _Ty,
		class = void>
		struct _Add_reference
		{	// add reference
		using _Lvalue = _Ty;
		using _Rvalue = _Ty;
		};

	template<class _Ty>
		struct _Add_reference<_Ty, typename _void_t<_Ty&>::type>
		{	// add reference
		using _Lvalue = _Ty&;
		using _Rvalue = _Ty&&;
		};

		// STRUCT TEMPLATE add_lvalue_reference
	template<class _Ty>
		struct add_lvalue_reference
		{	// add lvalue reference
		using type = typename _Add_reference<_Ty>::_Lvalue;
		};

		// STRUCT TEMPLATE add_rvalue_reference
	template<class _Ty>
		struct add_rvalue_reference
		{	// add rvalue reference
		using type = typename _Add_reference<_Ty>::_Rvalue;
		};

		// FUNCTION TEMPLATE declval
	template<class _Ty>
		typename add_rvalue_reference<_Ty>::type declval() noexcept;

		// STRUCT TEMPLATE remove_extent
	template<class _Ty>
		struct remove_extent
		{	// remove array extent
		using type = _Ty;
		};

	template<class _Ty, size_t _Ix>
		struct remove_extent<_Ty[_Ix]>
		{	// remove array extent
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_extent<_Ty[]>
		{	// remove array extent
		using type = _Ty;
		};

		// STRUCT TEMPLATE remove_all_extents
	template<class _Ty>
		struct remove_all_extents
		{	// remove all array extents
		using type = _Ty;
		};

	template<class _Ty, size_t _Ix>
		struct remove_all_extents<_Ty[_Ix]>
		{	// remove all array extents
		using type = typename remove_all_extents<_Ty>::type;
		};

	template<class _Ty>
		struct remove_all_extents<_Ty[]>
		{	// remove all array extents
		using type = typename remove_all_extents<_Ty>::type;
		};

		// STRUCT TEMPLATE remove_pointer
	template<class _Ty>
		struct remove_pointer
		{	// remove pointer
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_pointer<_Ty *>
		{	/* remove pointer */
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_pointer<_Ty * const>
		{	/* remove pointer */
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_pointer<_Ty * volatile>
		{	/* remove pointer */
		using type = _Ty;
		};

	template<class _Ty>
		struct remove_pointer<_Ty * const volatile>
		{	/* remove pointer */
		using type = _Ty;
		};


		// STRUCT TEMPLATE add_pointer
	template<class _Ty,
		class = void>
		struct _Add_pointer
		{	// add pointer
		using type = _Ty;
		};

	template<class _Ty>
		struct _Add_pointer<_Ty, typename _void_t<typename remove_reference<_Ty>::type *>::type>
		{	// add pointer
		using type = typename remove_reference<_Ty>::type *;
		};

	template<class _Ty>
		struct add_pointer
		{	// add pointer
		using type = typename _Add_pointer<_Ty>::type;
		};

	template<class _Ty>
		using add_pointer_t = typename _Add_pointer<_Ty>::type;


		// TYPE PREDICATES
		// STRUCT TEMPLATE is_array
	template<class _Ty>
		struct is_array
			: false_type
		{	// determine whether _Ty is an array
		};

	template<class _Ty, size_t _Nx>
		struct is_array<_Ty[_Nx]>
			: true_type
		{	// determine whether _Ty is an array
		};

	template<class _Ty>
		struct is_array<_Ty[]>
			: true_type
		{	// determine whether _Ty is an array
		};

		// STRUCT TEMPLATE is_lvalue_reference
	template<class _Ty>
		struct is_lvalue_reference
			: false_type
		{	// determine whether _Ty is an lvalue reference
		};

	template<class _Ty>
		struct is_lvalue_reference<_Ty&>
			: true_type
		{	// determine whether _Ty is an lvalue reference
		};

		// STRUCT TEMPLATE is_rvalue_reference
	template<class _Ty>
		struct is_rvalue_reference
			: false_type
		{	// determine whether _Ty is an rvalue reference
		};

	template<class _Ty>
		struct is_rvalue_reference<_Ty&&>
			: true_type
		{	// determine whether _Ty is an rvalue reference
		};

		// STRUCT TEMPLATE is_reference
	template<class _Ty>
		struct is_reference
			: false_type
		{	// determine whether _Ty is a reference
		};

	template<class _Ty>
		struct is_reference<_Ty&>
			: true_type
		{	// determine whether _Ty is a reference
		};

	template<class _Ty>
		struct is_reference<_Ty&&>
			: true_type
		{	// determine whether _Ty is a reference
		};

		// STRUCT TEMPLATE is_pointer
	template<class _Ty>
		struct is_pointer
			: false_type
		{	// determine whether _Ty is a pointer
		};

	template<class _Ty>
		struct is_pointer<_Ty *>
			: true_type
		{	// determine whether _Ty is a pointer
		};

	template<class _Ty>
		struct is_pointer<_Ty * const>
			: true_type
		{	// determine whether _Ty is a pointer
		};

	template<class _Ty>
		struct is_pointer<_Ty * volatile>
			: true_type
		{	// determine whether _Ty is a pointer
		};

	template<class _Ty>
		struct is_pointer<_Ty * const volatile>
			: true_type
		{	// determine whether _Ty is a pointer
		};

		// STRUCT TEMPLATE is_null_pointer
	template<class _Ty>
		struct is_null_pointer
			: integral_constant<bool, is_same<typename remove_cv<_Ty>::type, nullptr_t>::value>
		{	// determine whether _Ty is nullptr_t
		};

		// STRUCT TEMPLATE is_fundamental
	template<class _Ty>
		struct is_fundamental
			: integral_constant<bool, is_arithmetic<_Ty>::value
			|| is_void<_Ty>::value
			|| is_null_pointer<_Ty>::value>
		{	// determine whether _Ty is a fundamental type
		};

		// STRUCT TEMPLATE is_compound
	template<class _Ty>
		struct is_compound
			: integral_constant<bool, !is_fundamental<_Ty>::value>
		{	// determine whether _Ty is a compound type
		};

		// STRUCT TEMPLATE is_const
	template<class _Ty>
		struct is_const
			: false_type
		{	// determine whether _Ty is const qualified
		};

	template<class _Ty>
		struct is_const<const _Ty>
			: true_type
		{	// determine whether _Ty is const qualified
		};

		// STRUCT TEMPLATE is_volatile
	template<class _Ty>
		struct is_volatile
			: false_type
		{	// determine whether _Ty is volatile qualified
		};

	template<class _Ty>
		struct is_volatile<volatile _Ty>
			: true_type
		{	// determine whether _Ty is volatile qualified
		};

		// STRUCT TEMPLATE _Is_implicitly_default_constructible
	template<class _Ty,
		class = void>
		struct _Is_implicitly_default_constructible
			: false_type
		{	// determine whether _Ty is implicitly default constructible
		};

	template<class _Ty>
		void _Implicitly_default_construct(const _Ty&);

	template<class _Ty>
		struct _Is_implicitly_default_constructible<_Ty, typename _void_t<decltype(_Implicitly_default_construct<_Ty>({}))>::type>
			: true_type
		{	// determine whether _Ty is implicitly default constructible
		};

		// STRUCT TEMPLATE rank
	template<class _Ty>
		struct rank
			: integral_constant<size_t, 0>
		{	// determine number of dimensions of array _Ty
		};

	template<class _Ty, size_t _Ix>
		struct rank<_Ty[_Ix]>
			: integral_constant<size_t, rank<_Ty>::value + 1>
		{	// determine number of dimensions of array _Ty
		};

	template<class _Ty>
		struct rank<_Ty[]>
			: integral_constant<size_t, rank<_Ty>::value + 1>
		{	// determine number of dimensions of array _Ty
		};

		// STRUCT TEMPLATE extent
	template<class _Ty, unsigned int _Nx>
		struct _Extent
			: integral_constant<size_t, 0>
		{	// determine extent of dimension _Nx of array _Ty
		};

	template<class _Ty, size_t _Ix>
		struct _Extent<_Ty[_Ix], 0>
			: integral_constant<size_t, _Ix>
		{	// determine extent of dimension _Nx of array _Ty
		};

	template<class _Ty, unsigned int _Nx, size_t _Ix>
		struct _Extent<_Ty[_Ix], _Nx>
			: _Extent<_Ty, _Nx - 1>
		{	// determine extent of dimension _Nx of array _Ty
		};

	template<class _Ty, unsigned int _Nx>
		struct _Extent<_Ty[], _Nx>
			: _Extent<_Ty, _Nx - 1>
		{	// determine extent of dimension _Nx of array _Ty
		};

	template<class _Ty, unsigned int _Nx = 0>
		struct extent
			: _Extent<_Ty, _Nx>
		{	// determine extent of dimension _Nx of array _Ty
		};

		//STRUCT TEMPLATE is_function !!NEVER USE THIS!!
	template <typename _Ty> struct is_function
			: false_type
		{   //always false (just to make usage of decay possible)
		};

		// STRUCT TEMPLATE decay
	template<class _Ty>
		struct decay
		{	// determines decayed version of _Ty
		using _Ty1 = typename remove_reference<_Ty>::type;

		using type = typename conditional<is_array<_Ty1>::value,
			typename add_pointer<typename remove_extent<_Ty1>::type>::type,
			typename conditional<is_function<_Ty1>::value,
				typename add_pointer<_Ty1>::type,
				typename remove_cv<_Ty1>::type>::type>::type;
				};

		// STRUCT TEMPLATE common_type
	template<class _Ty1,
		class _Ty2,
		class = void>
		struct _Decayed_cond_oper
		{
		};

	template<class _Ty1,
		class _Ty2>
		struct _Decayed_cond_oper<_Ty1, _Ty2, typename _void_t<decltype(false ? ::std::declval<_Ty1>() : ::std::declval<_Ty2>())>::type>
		{
		using type = typename decay<decltype(false ? ::std::declval<_Ty1>() : ::std::declval<_Ty2>())>::type;
		};

	template<class... _Ty>
		struct common_type;

	template<>
		struct common_type<>
		{
		};

	template<class _Ty1>
		struct common_type<_Ty1>
			: common_type<_Ty1, _Ty1>
		{
		};

	template<class _Ty1,
		class _Ty2,
		class _Decayed1 = typename decay<_Ty1>::type,
		class _Decayed2 = typename decay<_Ty2>::type>
		struct _Common_type2
			: common_type<_Decayed1, _Decayed2>
		{
		};

	template<class _Ty1,
		class _Ty2>
		struct _Common_type2<_Ty1, _Ty2, _Ty1, _Ty2>
			: _Decayed_cond_oper<_Ty1, _Ty2>
		{
		};

	template<class _Ty1,
		class _Ty2>
		struct common_type<_Ty1, _Ty2>
			: _Common_type2<_Ty1, _Ty2>
		{
		};

	template<class _Void,
		class _Ty1,
		class _Ty2,
		class... _Rest>
		struct _Common_type3
		{
		};

	template<class _Ty1,
		class _Ty2,
		class... _Rest>
		struct _Common_type3<typename _void_t<typename common_type<_Ty1, _Ty2>::type>::type, _Ty1, _Ty2, _Rest...>
			: common_type<typename common_type<_Ty1, _Ty2>::type, _Rest...>
		{
		};

	template<class _Ty1,
		class _Ty2,
		class... _Rest>
		struct common_type<_Ty1, _Ty2, _Rest...>
			: _Common_type3<void, _Ty1, _Ty2, _Rest...>
		{
		};

		// STRUCT TEMPLATE underlying_type
	template<typename _Ty>
    struct underlying_type
		{ // determine underlying type for enum
			using type = __underlying_type(_Ty);
		};

		// STRUCT TEMPLATE _Identity
	template<class _Ty>
		struct _Identity
		{	// the identity transformation trait
		using type = _Ty;
		};

		// FUNCTION TEMPLATE forward
	template<class _Ty>
		constexpr _Ty&& forward(typename remove_reference<_Ty>::type& _Arg) noexcept
		{	// forward an lvalue as either an lvalue or an rvalue
		return (static_cast<_Ty&&>(_Arg));
		}

	template<class _Ty>
		constexpr _Ty&& forward(typename remove_reference<_Ty>::type&& _Arg) noexcept
		{	// forward an rvalue as an rvalue
		static_assert(!is_lvalue_reference<_Ty>::value, "bad forward call");
		return (static_cast<_Ty&&>(_Arg));
		}

			// FUNCTION TEMPLATE move
	template<class _Ty>
		constexpr typename remove_reference<_Ty>::type&&
			move(_Ty&& _Arg) noexcept
		{	// forward _Arg as movable
		return (static_cast<typename remove_reference<_Ty>::type&&>(_Arg));
		}

}

#endif
