#pragma once

#include "basic_math_array_variant.h"
#include "basic_math_matrix.h"




//��̬���󣬻��ڶ�άVariant��̬����ʵ�֣�����ʵ�ֲ����ٶȽϿ죬���ڴ������龳�����ݲ���Ҳ�Ͽ죬�ʺ�
template<typename Ty>
class SunnyTcsDynamicVariantMatrix
{
public:
	typedef SunnyTcsDynamicVariantMatrix<Ty>								Self;
	typedef SunnyTcsDynamicVariantArray<SunnyTcsDynamicVariantArray<Ty>>	Base_type;
	typedef Ty																value_type;
	typedef typename Base_type::size_type									size_type;
	typedef typename Base_type::difference_type								difference_type;
	typedef SunnyTcsDynamicVariantArray<Ty>									RowType;
	typedef std::pair<size_type, size_type>									CoorType;

	static constexpr size_type defaultRows = 100;
	static constexpr size_type defaultColumns = 100;


	//�������������
	class RowIterator {
	public:
		friend class Self;
		typedef std::forward_iterator_tag iterator_category;
		typedef value_type value_type;
		typedef difference_type difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;

		RowIterator(RowIterator const&) = default;
		RowIterator& operator=(RowIterator const&) = default;
		virtual ~RowIterator() {}

		bool operator==(RowIterator const& var)const {
			return std::addressof(m_matrix) == std::addressof(var.m_matrix) &&
				m_rowIndex == var.m_rowIndex && m_columnIndex == var.m_columnIndex;
		}

		bool operator!=(RowIterator const& var)const {
			return !this->operator==(var);
		}

		RowIterator& operator++() {
			auto coor = m_matrix.nextVaildPosByRowSeq(m_rowIndex, m_columnIndex);
			m_rowIndex = coor.first;
			m_columnIndex = coor.second;
			return *this;
		}

		RowIterator operator++(int) {
			RowIterator tmp = *this;
			this->operator++();
			return tmp;
		}

		value_type& operator*() {
			return m_matrix[m_rowIndex][m_columnIndex];
		}

		value_type const& operator*()const {
			return m_matrix[m_rowIndex][m_columnIndex];
		}

		value_type* operator->() {
			return &m_matrix[m_rowIndex][m_columnIndex];
		}

		value_type const* operator->()const {
			return &m_matrix[m_rowIndex][m_columnIndex];
		}

	private:
		//ctor
		RowIterator(Self& ma, size_type row, size_type column)
			:m_matrix(ma), m_rowIndex(row), m_columnIndex(column) {}

	private:
		Self& m_matrix;
		size_type m_rowIndex;
		size_type m_columnIndex;
	};

	typedef RowIterator iterator;
	typedef RowIterator const const_iterator;

	//ctor
	SunnyTcsDynamicVariantMatrix(size_type rows = defaultRows, size_type columns = defaultColumns)
		:m_base(rows), m_rows(rows), m_columns(columns)  //ʹ��������ʼ��
	{}

	//copy ctor
	SunnyTcsDynamicVariantMatrix(SunnyTcsDynamicVariantMatrix const& var)
		:m_base(var.m_base), m_rows(var.m_rows), m_columns(var.m_columns)
	{}

	//move ctor
	SunnyTcsDynamicVariantMatrix(SunnyTcsDynamicVariantMatrix&& var)noexcept
		:m_base(0), m_rows(0), m_columns(0)
	{
		this->operator=(std::move(var));
	}

	//dector
	virtual ~SunnyTcsDynamicVariantMatrix() {}

	//assign
	SunnyTcsDynamicVariantMatrix& operator=(SunnyTcsDynamicVariantMatrix const& var) {
		m_base = var.m_base;
		m_rows = var.m_rows;
		m_columns = var.m_columns;
		return *this;
	}

	SunnyTcsDynamicVariantMatrix& operator=(SunnyTcsDynamicVariantMatrix&& var) noexcept {
		m_base = std::move(var.m_base);
		std::swap(m_rows, var.m_rows);
		std::swap(m_columns, var.m_columns);
		return *this;
	}

	//operator
	bool operator==(SunnyTcsDynamicVariantMatrix const& var)const {
		bool ret = true;
		ret &= (m_rows == var.m_rows && m_columns == var.m_columns);
		if (!ret)return ret;
		for (size_type i = 0; i < m_rows; ++i) {
			if (m_base.isPosVaild(i) && !var.m_base.isPosVaild(i) && m_base[i].vaildSize() != 0)return false;
			if (var.m_base.isPosVaild(i) && !m_base.isPosVaild(i) && var.m_base[i].vaildSize() != 0)return false;
			if (m_base.isPosVaild(i) && var.m_base.isPosVaild(i) && (m_base[i] != var.m_base[i]))return false;
		}
		return true;
	}

	bool operator!=(SunnyTcsDynamicVariantMatrix const& var)const {
		return !this->operator==(var);
	}

	RowType& operator[](size_type pos) {
		assert(pos >= 0 && pos < m_rows);
		assert(m_base.isPosVaild(pos));
		return m_base[pos];
	}

	RowType const& operator[](size_type pos) const {
		assert(pos >= 0 && pos < m_rows);
		assert(m_base.isPosVaild(pos));
		return m_base[pos];
	}

	//api
	//����ߴ���ؽӿ�
	size_type rows()const { return m_rows; }

	size_type columns()const { return m_columns; }

	size_type size()const { return rows() * columns(); }

	void resetSize(size_type rows, size_type columns) {
		resetRows(rows);
		resetColumns(columns);
	}


	void resetRows(size_type rows) {
		if (m_rows == rows)return;
		m_base.resetSize(rows); //������չ
		if (rows < m_rows)//������С��ʱ��,�����г�ʼ��Ϊ��
			m_base.initRange(rows, m_base.size() - rows);
		m_rows = rows;
	}


	void resetColumns(size_type columns) {
		if (m_columns == columns)return;
		for (size_type i = 0; i < m_rows; ++i) {
			if (!m_base.isPosVaild(i))continue;
			SunnyTcsDynamicVariantArray<Ty>& row = m_base[i];
			row.resetSize(columns); //��������ʵ����������������
			if (columns < m_columns)
				row.initRange(columns, row.size() - columns); //��С������ʱ�򣬶����λ�ó�ʼ��Ϊ��
		}
		m_columns = columns;
	}


	//�����е�Ԫ����Ч����ؽӿ�
	//һ������Ч��Ԫ��
	size_type vaildSizeInRow(size_type row)const {
		return m_base.isPosVaild(row) ? m_base[row].vaildSize() : 0;
	}

	//һ������Ч��Ԫ��
	size_type vaildSizeInColumn(size_type column)const {
		if (column >= m_columns)return 0;
		size_type ret = 0;
		for (size_type i = 0; i < rows(); ++i) {
			ret += m_base.isPosVaild(i) ? (m_base[i].isPosVaild(column) ? 1 : 0) : 0;
		}
		return ret;
	}

	//�ܵ���ЧԪ�ظ���
	size_type vaildSize()const {
		size_type ret = 0;
		for (size_type i = 0; i < rows(); ++i) {
			ret += this->vaildSizeInRow(i);
		}
		return ret;
	}

	//ĳ��λ���е�Ԫ���Ƿ���Ч
	bool isPosVaild(size_type rowIndex, size_type columnIndex)const {
		if (rowIndex < 0 || rowIndex >= m_rows ||
			columnIndex < 0 || columnIndex >= m_columns)return false;
		return m_base.isPosVaild(rowIndex) && m_base[rowIndex].isPosVaild(columnIndex);
	}

	//һ���е�һ����ЧԪ�ص�����
	inline size_type firstVaildPosInRow(size_type row)const {
		return nextVaildPosInRow(row, -1);
	}

	//һ������һ����ЧԪ�ص�����
	size_type nextVaildPosInRow(size_type row, size_type cur)const {
		size_type ret = m_base.isPosVaild(row) ? m_base[row].nextVaildPos(cur) : -1;
		assert(ret == -1 || (ret >= 0 && ret < m_columns));
		return ret;
	}


	//һ���е�һ����ЧԪ�ص�����
	inline size_type firstVaildPosInColumn(size_type column)const {
		return nextVaildPosInColumn(column, -1);
	}


	//һ������һ����ЧԪ�ص�����
	size_type nextVaildPosInColumn(size_type column, size_type cur)const {
		if (cur + 1 >= m_rows || cur + 1 < 0)return -1;
		for (size_type i = cur + 1; i < m_rows; ++i) {
			if (!m_base.isPosVaild(i))continue;
			if (m_base[i].isPosVaild(column))return i;
		}
		return -1;
	}

	//���������а�����Ѱ�ҵ��ĵ�һ��Ԫ��
	inline CoorType firstVaildPosByRowSeq()const {
		return this->nextVaildPosByRowSeq(0, -1);
	}

	//������Ѱ����һ��Ԫ��
	CoorType nextVaildPosByRowSeq(size_type row, size_type clo)const {
		if (row < 0 || row  >= m_rows || clo + 1 < 0 || clo + 1 >= m_columns)
			return std::make_pair<size_type, size_type>(-1, -1);
		for (size_type i = row ; i < m_rows; ++i) {
			if (0 == this->vaildSizeInRow(i))continue;
			for (size_type j = clo + 1; j < m_columns; ++j) {
				if (this->isPosVaild(i, j))return std::make_pair<size_type, size_type>(i + 0, j + 0);
			}
			clo = 0;//�����0
		}
		return std::make_pair<size_type, size_type>(-1, -1);
	}

	//��������Ѱ�ҵ�һ��Ԫ��
	inline CoorType firstVaildPosByColumnSeq()const {
		return this->nextVaildPosByRowSeq(-1, 0);
	}

	//��������Ѱ����һ��Ԫ��
	CoorType nextVaildPosByColumnSeq(size_type row, size_type clo)const {
		if (row + 1 < 0 || row + 1 >= m_rows || clo  < 0 || clo  >= m_columns)
			return std::make_pair<size_type, size_type>(-1, -1);
		for (size_type j = clo ; j < m_columns; ++j) {
			if (0 == this->vaildSizeInColumn(j))continue;
			for (size_type i = row + 1; i < m_rows; ++i) {
				if (this->isPosVaild(i, j))return std::make_pair<size_type, size_type>(i + 0, j + 0);
			}
			row = 0;
		}
		return std::make_pair<size_type, size_type>(-1, -1);
	}


	//�����ݽ����޸ĵĽӿ�
	inline value_type& at(size_type row, size_type column) {
		return (*this)[row][column];
	}

	inline value_type const& at(size_type row, size_type column)const {
		return (*this)[row][column];
	}

	//����
	void insert(size_type rowIndex, size_type columnIndex, value_type const& var) {
		assert(rowIndex >= 0 && columnIndex >= 0);
		if (rowIndex >= m_rows)resetRows(rowIndex + 1);
		if (columnIndex >= m_columns)resetColumns(columnIndex + 1);
		if (!m_base.isPosVaild(rowIndex)) {
			m_base.insert(rowIndex, RowType(m_columns));
		}
		m_base[rowIndex].insert(columnIndex, var);
	}


	void remove(size_type rowIndex, size_type columnIndex) {
		if (rowIndex < 0 || rowIndex >= m_rows || columnIndex < 0 || columnIndex >= m_columns ||
			!m_base.isPosVaild(rowIndex) || !m_base[rowIndex].isPosVaild(columnIndex))return; //������Χ�Ļ�����Ч����ֱ�ӷ���
		m_base[rowIndex].remove(columnIndex);
	}

	void removeRow(size_type row) {
		if (row < 0 || row >= m_rows)return;
		m_base.remove(row);
	}


	void removeColumn(size_type column) {
		if (column < 0 || column >= m_columns)return;
		for (size_type i = 0; i < m_rows; ++i) {
			if (!m_base.isPosVaild(i))continue;
			m_base[i].remove(column);
		}
	}

	inline void swapRows(size_type row1, size_type row2) {
		m_base.swap(row1, row2);
	}

	void swapColumns(size_type column1, size_type column2) {
		for (size_type i = 0; i < m_rows; ++i) {
			if (!m_base.isPosVaild(i))continue;//��Ч��
			m_base[i].swap(column1, column2);
		}
	}

	//���ݱ�׼��
	iterator begin() {
		auto coor = this->firstVaildPosByRowSeq();
		return iterator(*this, coor.first, coor.second);
	}

	iterator end() {
		return iterator(*this, -1, -1);
	}

	const_iterator cbegin()const {
		auto coor = this->firsiVaildPosByRowSeq();
		return const_iterator(*this, coor.first, coor.second);
	}

	const_iterator cend()const {
		return const_iterator(*this, -1, -1);
	}

	//����Ϊѡ���Խӿ�
	//ͨ���ɵ��ö��� �޸�����Ϊ������value_type�ľ���
	template<typename Valty, typename Functor>
	SunnyTcsDynamicVariantMatrix<Valty> toOtherMatrix(Functor&& func)const {
		SunnyTcsDynamicVariantMatrix<Valty> ret(m_rows, m_columns);
		for (size_type i = 0; i < m_rows; ++i) {
			if (this->isRowVaild(i))ret.activeInVaildRow(i);
			for (size_type j = 0; j < m_columns; ++j) {
				if (this->isPosVaild(i, j)) {
					Valty ele(func((*this)[i][j]));
					ret.insert(i, j, ele);
				}
			}
		}
		return ret;
	}

	//����Ч����ؽӿ�
	//���Ƿ���Ч
	bool isRowVaild(size_type row)const {
		return m_base.isPosVaild(row);
	}

	size_type firstVaildRow()const {
		return m_base.firstVaildPos();
	}

	size_type nextVaildRow(size_type cur)const {
		return m_base.nextVaildPos(cur);
	}

	//��һ����Ч��
	inline size_type firstInVaildRow() {
		size_type ret = m_base.firstInVaildPos(); //����base�е�һ����λ�õ����������λ�ÿ��ܻ����m_rows
		if (ret >= m_rows)this->resetRows(ret + 1); //�Զ�������չ���������
		return ret;
	}

	//����һ����Ч��
	inline void activeInVaildRow(size_type row) {
		if (row >= m_rows)resetRows(row + 1); //���Ҫ�󼤻�����ڵ�ǰ�д�С֮�⣬�Ǿ͵���������
		if (!m_base.isPosVaild(row)) m_base.insert(row, RowType(m_columns));
	}

#ifdef STRICT_INTERFACE_CHECK
	TCS_MATRIX_INTERFACE_CHECK(Self)
#endif // STRICT_INTERFACE_CHECK



private:
	Base_type m_base;
	size_type m_rows;
	size_type m_columns;
};
