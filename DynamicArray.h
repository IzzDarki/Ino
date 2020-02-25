#pragma once
#ifndef INO_DYNAMICARRAY_INCLUDED
#define INO_DYNAMICARRAY_INCLUDED

#include "InoCore.h"
#include "std/TypeTraits.h"

namespace ino {

	template <typename T>
	class DynamicArray
	{
	private:
		T* Elements = nullptr;
		int TotalElements = 0;
	
	public:
		using ElementType = T;

		static_assert(std::is_const<T>::value == false, "Containers of const elements are forbidden");

		DynamicArray() = default;

		DynamicArray(const DynamicArray& Other) : TotalElements(Other.TotalElements)
		{
			Elements = new T[TotalElements];
			for (int C = 0; C < TotalElements; C++)
				Elements[C] = Other.Elements[C];
		}

		DynamicArray& operator=(const DynamicArray& Other)
		{
			TotalElements = Other.TotalElements;
			Elements = new T[TotalElements];
			for (int C = 0; C < TotalElements; C++)
				Elements[C] = Other.Elements[C];
			return *this;
		}

		//TODO invalidate after move and destruct, evtl. Debug and Release
		DynamicArray(DynamicArray&& Other) : Elements(Other.Elements), TotalElements(Other.TotalElements)
		{}

		DynamicArray& operator=(DynamicArray&& Other)
		{
			Elements = Other.Elements;
			TotalElements = Other.TotalElements;
			return *this;
		}

		~DynamicArray() { Erase(0, TotalElements); }

		inline T& operator[](int Index) { return Elements[Index]; }

		inline int GetLength() const { return TotalElements; }

		inline T* begin() { return &Elements[0]; }
		inline T* end() { return &Elements[TotalElements]; }
		inline const T* cbegin() const { return &Elements[0]; }
		inline const T* cend() const { return &Elements[TotalElements]; }

		//TODO Reserve function

		void PushBack(const T& NewElement)
		{
			const auto OldElements = Elements;
			Elements = new T[++TotalElements];
			for (int C = 0; C < TotalElements - 1; C++)
				Elements[C] = std::move(OldElements[C]);
			Elements[TotalElements - 1] = NewElement;
			delete[] OldElements;
		}
		
		void Erase(int Index, int Length = 1)
		{
			const auto OldElements = Elements;
			Elements = new T[TotalElements -= Length];
			int C = 0;
			for (; C < Index; C++)
				Elements[C] = std::move(OldElements[C]);
			for (; C < TotalElements; C++)
				Elements[C] = std::move(OldElements[C + Length]);
			delete[] OldElements;
		}
	};

}

#endif