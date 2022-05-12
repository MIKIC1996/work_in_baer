#pragma once
#include "pch.h"

template<typename Elem>
class Line_table
{
public:
	//表的初始化
	virtual void init() = 0;
	//是否为空
	virtual bool isEmpty() = 0;
	//当前长度
	virtual std::size_t size() = 0;
	//清空
	virtual void clear() = 0;
	//数据插入
	virtual void insert(int I, Elem data) = 0;
	//数据删除
	virtual void deleteElem(int i) = 0;
	//数据查询
	virtual Elem& getElem(int i) = 0;
	//数据定位
	virtual int locateElem(Elem data) = 0;
};