#pragma once


#include "basic_defs.h"


//动态数组
template<typename Ty>
class SunnyTcsDynamicMathArray {
public:
	
	typedef std::size_t size_type;
	typedef Ty value_type;
	static constexpr size_type defaultSize = 100;
	static constexpr size_type valueTypeSize = sizeof(value_type);

	explicit SunnyTcsDynamicMathArray(size_type defSize = defaultSize)
		:m_size(0), m_data(nullptr)
	{
		assert(defSize >= 0);

	}

	inline size_type size(){}
	
	void resetSize(size_type nsize){}

	value_type& operator[](size_type step) { assert(step + 1 <= m_size); return m_data[step]; }

private:
	void allocMem(size_type nsize) {
		assert(nsize >= 0);
		if (nsize == m_size)return;
		else if (nsize > m_size) {
			void* newMem = m_data ? realloc(m_data, nsize * valueTypeSize) : malloc(nsize * valueTypeSize);
			!newMem ? throw std::bad_alloc() :
				newMem == m_data ? 1 : free(m_data), m_data = newMem ;
		}
		else {

		}
	}

private:
	size_type m_size;
	value_type* m_data;
};




//动态矩阵
template<typename Ty>
class SunnyTcsDynamicMathMatrix {
public:
	typedef std::size_t size_type;
	typedef Ty value_type;



private:



};





