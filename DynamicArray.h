#pragma once
#ifndef INO_DYNAMICARRAY_INCLUDED
#define INO_DYNAMICARRAY_INCLUDED

#include "InoCore.h"
#include "Utility.h"
#include "std/TypeTraits.h"

namespace ino {

	template <typename T>
	class DynamicArray
	{
	public:
		using ElementType = T;
		static_assert(std::is_const<ElementType>::value == false, "Containers of const elements are forbidden");

	private:
		ElementType* Elements = nullptr;
		int TotalElements = 0;
		int Capacity = 0;

		inline void Helper_VariadicFill(const ElementType& NewElement) { Elements[TotalElements++] = NewElement; }

		template <typename... Args>
		void Helper_VariadicFill(const ElementType& First, const Args&... Others)
		{
			Helper_VariadicFill(First);
			Helper_VariadicFill(Others...);
		}

	protected:
		void Invalidate()
		{
			Elements = nullptr;
			TotalElements = 0;
			Capacity = 0;
		}
	
	public:
		DynamicArray() = default;

		template <typename... Args, typename std::enable_if<sizeof...(Args) && FoldLogicalAnd<std::is_same<ElementType, Args>::value...>::value, int>::type = 0>
		DynamicArray(const Args&... Arguments)
		{
			Reserve(sizeof...(Args));
			Helper_VariadicFill(Arguments...);
		}

		DynamicArray(const DynamicArray& Other) : TotalElements(Other.TotalElements), Capacity(Other.Capacity)
		{
			Elements = new ElementType[TotalElements];
			for (int C = 0; C < TotalElements; C++)
				Elements[C] = Other.Elements[C];
		}

		DynamicArray& operator=(const DynamicArray& Other)
		{
			TotalElements = Other.TotalElements;
			Capacity = Other.Capacity;
			Elements = new ElementType[TotalElements];
			for (int C = 0; C < TotalElements; C++)
				Elements[C] = Other.Elements[C];
			return *this;
		}

		inline DynamicArray(DynamicArray&& Other) : Elements(Other.Elements), TotalElements(Other.TotalElements), Capacity(Other.Capacity)
		{
			Other.Invalidate();
		}

		DynamicArray& operator=(DynamicArray&& Other)
		{
			Elements = Other.Elements;
			TotalElements = Other.TotalElements;
			Capacity = Other.Capacity;

			Other.Invalidate();

			return *this;
		}

		inline ~DynamicArray() { Erase(0, TotalElements); Invalidate();}

		inline ElementType& operator[](int Index) { return Elements[Index]; }

		inline int GetLength() const { return TotalElements; }
		inline int GetSize() const { return Capacity; }

		inline ElementType* begin() { return &Elements[0]; }
		inline ElementType* end() { return &Elements[TotalElements]; }
		inline const ElementType* cbegin() const { return &Elements[0]; }
		inline const ElementType* cend() const { return &Elements[TotalElements]; }

		void Reserve(int Capacity)
		{
			if (this->Capacity < Capacity)
			{
				const auto OldElements = Elements;
				this->Capacity = Capacity;

				Elements = new ElementType[Capacity];
				for (int C = 0; C < TotalElements; C++)
					Elements[C] = std::move(OldElements[C]);
				delete[] OldElements;
			}
		}

		void PushBack(const ElementType& NewElement)
		{
			if (++TotalElements > Capacity)
			{
				const auto OldElements = Elements;
				Elements = new ElementType[TotalElements];
				Capacity = TotalElements;
				for (int C = 0; C < TotalElements - 1; C++)
					Elements[C] = std::move(OldElements[C]);
				Elements[TotalElements - 1] = NewElement;
				delete[] OldElements;
			}
			else
				Elements[TotalElements - 1] = NewElement;
			
		}
		
		void Erase(int Index, int Length = 1)
		{
			const auto OldElements = Elements;
			Elements = new ElementType[TotalElements -= Length];
			Capacity = TotalElements;
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