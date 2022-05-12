#pragma once
#include "pch.h"

template<typename Elem>
class Line_table
{
public:
	//��ĳ�ʼ��
	virtual void init() = 0;
	//�Ƿ�Ϊ��
	virtual bool isEmpty() = 0;
	//��ǰ����
	virtual std::size_t size() = 0;
	//���
	virtual void clear() = 0;
	//���ݲ���
	virtual void insert(int I, Elem data) = 0;
	//����ɾ��
	virtual void deleteElem(int i) = 0;
	//���ݲ�ѯ
	virtual Elem& getElem(int i) = 0;
	//���ݶ�λ
	virtual int locateElem(Elem data) = 0;
};