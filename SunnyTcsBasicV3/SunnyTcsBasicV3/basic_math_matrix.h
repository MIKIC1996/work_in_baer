#pragma once

#include "basic_math_array.h"


/*�����׼�ӿ�
* ��Ƕ����
	value_type;
	size_type;
	difference_type;
	RowType;
	CoorType;
*�����ӿ�
	*����	 
	size_type rows()const 
	*����
	size_type columns()const
	*���� = �С���
	size_type size()const 
	*����������
	void resetSize(size_type rows, size_type columns) 
	*��������
	void resetRows(size_type rows) 
	*��������
	void resetColumns(size_type columns) 

	*�����е�Ԫ����Ч����ؽӿ�
	*һ���е���ЧԪ�ظ���
	size_type vaildSizeInRow(size_type row)const
	*һ������Ч��Ԫ��
	size_type vaildSizeInColumn(size_type column)const 
	*�ܵ���ЧԪ�ظ���
	size_type vaildSize()const 
	*ĳ��λ���е�Ԫ���Ƿ���Ч
	bool isPosVaild(size_type rowIndex, size_type columnIndex)const 
	*һ���е�һ����ЧԪ�ص�����
	inline size_type firstVaildPosInRow(size_type row)const 
	*һ������һ����ЧԪ�ص�����
	size_type nextVaildPosInRow(size_type row, size_type cur)const 
	*һ���е�һ����ЧԪ�ص�����
	inline size_type firstVaildPosInColumn(size_type column)const 
	*һ������һ����ЧԪ�ص�����
	size_type nextVaildPosInColumn(size_type column, size_type cur)const 
	*���������а�����Ѱ�ҵ��ĵ�һ��Ԫ��
	inline CoorType firstVaildPosByRowSeq()const 
	*������Ѱ����һ��Ԫ��
	CoorType nextVaildPosByRowSeq(size_type row ,size_type clo)const 
	*��������Ѱ�ҵ�һ��Ԫ��
	CoorType firsiVaildPosByColumnSeq()const 
	*��������Ѱ����һ��Ԫ��
	CoorType nextVaildPosByColumnSeq(size_type row, size_type clo)const

	*�����ݽ����޸ĵĽӿ�
	*��ȡԪ��
	value_type& at(size_type row ,size_type column)
	*��ȡԪ��const
	value_type const& at(size_type row ,size_type column)const
	*���뵽��Ӧλ�ã���λ�ó�����ǰ��С�����Զ���������С
	void insert(size_type rowIndex, size_type columnIndex, value_type const& var) 
	*��ĳ��λ��ɾ��Ԫ�أ������Ͳ�����Ԫ�أ���ֱ�ӷ���
	void remove(size_type rowIndex, size_type columnIndex) 
	*����ĳһ������Ԫ��Ϊ��Ч
	void removeRow(size_type row) 
	*����ĳһ������Ԫ��Ϊ��Ч
	void removeColumn(size_type column)
	*��������
	void swapRows(size_type row1, size_type row2) 
	*��������
	void swapColumns(size_type column1, size_type column2) 
*/


#define TCS_MATRIX_INTERFACE_CHECK(Type)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(Type,MAIT_1,size_type)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(Type,MAIT_2,size_type)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(Type,MAIT_3 , value_type)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(Type,MAIT_4 , RowType)\
TCS_STATIC_ASSERT_HAS_INSERTED_TYPE(Type,MAIT_5 , CoorType)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type, MAMF_1 ,size_type,rows )\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type, MAMF_2 ,size_type,columns )\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_3,size_type,size)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,MAMF_4,void ,resetSize, size_type ,size_type )\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,MAMF_5,void ,resetRows, size_type )\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,MAMF_6,void ,resetColumns, size_type )\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type, MAMF_7 ,size_type,vaildSizeInRow,size_type )\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type, MAMF_8 ,size_type,vaildSizeInColumn,size_type )\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_9,size_type,vaildSize)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_10,bool ,isPosVaild,size_type,size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_11,size_type,firstVaildPosInRow,size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_12,size_type,nextVaildPosInRow,size_type,size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_13,size_type,firstVaildPosInColumn,size_type )\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_14,size_type,nextVaildPosInColumn,size_type, size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_15,CoorType,firstVaildPosByRowSeq)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_16,CoorType,nextVaildPosByRowSeq,size_type,size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_17,CoorType,firstVaildPosByColumnSeq)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_18,CoorType,nextVaildPosByColumnSeq,size_type,size_type)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type,MAMF_19,value_type&,at,size_type,size_type)\
TCS_STATIC_ASSERT_HAS_CONST_MEMBER_FUNCTION(Type,MAMF_20,value_type const& ,at ,size_type, size_type)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type ,MAMF_20_5,void,insert,size_type,size_type ,value_type const&)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type, MAMF_21,void,remove,size_type,size_type)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type ,MAMF_22,void,removeRow,size_type)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type, MAMF_23,void ,removeColumn,size_type)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type ,MAMF_24,void ,swapRows,size_type,size_type)\
TCS_STATIC_ASSERT_HAS_MEMBER_FUNCTION(Type ,MAMF_25,void ,swapColumns ,size_type ,size_type)

