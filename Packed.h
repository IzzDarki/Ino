#pragma once
#ifndef INO_PACKED_INCLUDED
#define INO_PACKED_INCLUDED

#include "InoCore.h"
#include "Utility.h"
#include <std/TypeTraits.h>

namespace ino {

	template <typename T>
	struct Wrapper {
		const T& Val;
		constexpr Wrapper(const T& Val) : Val(Val) {}
	};

	template <typename VarT, typename... ParTs>
	struct Packed : Wrapper<ParTs>...
	{
		template <typename T>
		struct Contains : std::integral_constant<bool, FoldLogicalOr<std::is_same<T, ParTs>::value...>::value> {};
		
		VarT&& Var;

		constexpr Packed(VarT&& Var, const ParTs&... Pars) : Wrapper<ParTs>(Pars)..., Var(std::forward<VarT>(Var)) {}
		constexpr Packed(const Packed& Other) : Wrapper<ParTs>(Other.Wrapper<ParTs>::Val)..., Var(std::forward<VarT>(Other.Var)) {}
		constexpr Packed(Packed&& Other) : Wrapper<ParTs>(Other.Wrapper<ParTs>::Val)..., Var(std::forward<VarT>(Other.Var)) {}

		template <typename T>
		constexpr const T& Get() const {
			return Wrapper<T>::Val;
		}

	};

	template <typename VarT, typename... ParTs>
	constexpr inline Packed<VarT, ParTs...> Pack(VarT&& Var, const ParTs&... Pars) {
		return Packed<VarT, ParTs...>(std::forward<VarT>(Var), Pars...);
	}
}

#endif
