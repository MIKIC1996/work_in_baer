#pragma once
#include "pch.h"

template<typename Elem >
class stack_interface
{
public:
	virtual void init()=0;
	virtual void destory()=0;
	virtual void clear() = 0;
	virtual std::size_t size() = 0;
	virtual bool isEmpty() = 0;
	virtual Elem& top() = 0;
	virtual void push(const Elem& e) = 0;
	virtual void pop() = 0;

};


