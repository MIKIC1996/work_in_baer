#pragma once

#include "basic_math_array.h"


/*矩阵标准接口
* 内嵌类型
	value_type;
	size_type;
	difference_type;
	RowType;
	CoorType;
*函数接口
	*行数	 
	size_type rows()const 
	*列数
	size_type columns()const
	*总数 = 行×列
	size_type size()const 
	*重置行列数
	void resetSize(size_type rows, size_type columns) 
	*重置行数
	void resetRows(size_type rows) 
	*重置列数
	void resetColumns(size_type columns) 

	*矩阵中的元素有效性相关接口
	*一行中的有效元素个数
	size_type vaildSizeInRow(size_type row)const
	*一列中有效的元素
	size_type vaildSizeInColumn(size_type column)const 
	*总的有效元素个数
	size_type vaildSize()const 
	*某个位置中的元素是否有效
	bool isPosVaild(size_type rowIndex, size_type columnIndex)const 
	*一行中第一个有效元素的索引
	inline size_type firstVaildPosInRow(size_type row)const 
	*一行中下一个有效元素的索引
	size_type nextVaildPosInRow(size_type row, size_type cur)const 
	*一列中第一个有效元素的索引
	inline size_type firstVaildPosInColumn(size_type column)const 
	*一列中下一个有效元素的索引
	size_type nextVaildPosInColumn(size_type column, size_type cur)const 
	*整个矩阵中按行序寻找到的第一个元素
	inline CoorType firstVaildPosByRowSeq()const 
	*按行序寻找下一个元素
	CoorType nextVaildPosByRowSeq(size_type row ,size_type clo)const 
	*按照列序寻找第一个元素
	CoorType firsiVaildPosByColumnSeq()const 
	*按照列序寻找下一个元素
	CoorType nextVaildPosByColumnSeq(size_type row, size_type clo)const

	*对数据进行修改的接口
	*获取元素
	value_type& at(size_type row ,size_type column)
	*获取元素const
	value_type const& at(size_type row ,size_type column)const
	*插入到相应位置，或位置超过当前大小，则自动扩大矩阵大小
	void insert(size_type rowIndex, size_type columnIndex, value_type const& var) 
	*从某个位置删除元素，若本就不存在元素，则直接返回
	void remove(size_type rowIndex, size_type columnIndex) 
	*重置某一行所有元素为无效
	void removeRow(size_type row) 
	*重置某一列所有元素为无效
	void removeColumn(size_type column)
	*交换两行
	void swapRows(size_type row1, size_type row2) 
	*交换两列
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

