#pragma once


#include "basic_defs.h"

template<typename Ty>
class SunnyTcsStack {
public:
	typedef std::vector<Ty> Container;
	typedef std::size_t size_type;
	typedef Ty	value_type;

	SunnyTcsStack():m_vars(){}

	SunnyTcsStack(SunnyTcsStack const&) = default;

	virtual ~SunnyTcsStack(){}

	SunnyTcsStack& operator=(SunnyTcsStack const&) = default;

	inline bool operator==(SunnyTcsStack const& var)const {
		return m_vars == var.m_vars;
	}

	inline bool operator!=(SunnyTcsStack const& var)const {
		return !this->operator==(var);
	}

	inline bool empty()const {
		return m_vars.empty();
	}

	inline size_type size()const {
		return m_vars.size();
	}

	inline void clear() {
		return m_vars.clear();
	}

	inline Ty& top() {
		return m_vars.at(m_vars.size() - 1);
	}

	inline Ty const& top() const{
		return m_vars.at(m_vars.size() - 1);
	}

	inline void push(Ty const& var) {
		return m_vars.push_back(var);
	}

	inline void pop() {
		return m_vars.pop_back();
	}

private:
	Container m_vars;
};

