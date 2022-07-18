#pragma once

#include "basic_math_array.h"




//动态数组的实现2,使用variant作为节点类型，用variant的当前类型来作为是否为空位的标志，不再依赖
//typetrait 提供 类型的无效值，方便很多
//存储结构为顺序存储的静态链表，插入，删除，修改，查找效率均为 O(1),不过在内存扩容的时候涉及到数据的拷贝，效率较低，
//建议初始化的时候就提供足够的大小。
template<typename Ty, template<typename> class Alloc = std::allocator >
class SunnyTcsDynamicVariantArray {
public:

	typedef SunnyTcsDynamicVariantArray<Ty, Alloc>									Self;
	typedef std::size_t																size_type; //长度类型
	typedef size_type																difference_type;
	typedef Ty																		value_type; //值类型
	typedef std::variant<std::pair<size_type, size_type>, value_type>				ValueTypeNode; //节点类型
	typedef Alloc<ValueTypeNode>													AllocType;

	static constexpr size_type defaultSize = 100;
	static constexpr size_type ValueTypeNodeSize = sizeof(ValueTypeNode);


	//迭代器定义
	class NormalIterator
	{
	public:
		friend class Self;

		typedef std::forward_iterator_tag iterator_category;
		typedef value_type value_type;
		typedef difference_type difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;

		//copy ctor
		NormalIterator(NormalIterator const&) = default;
		//assign
		NormalIterator& operator=(NormalIterator const&) = default;
		//dector
		virtual ~NormalIterator() {}

		//operator== 
		bool operator==(NormalIterator const& var)const {
			return std::addressof(var.m_arr) == std::addressof(m_arr) && m_index == var.m_index;
		}

		//operator!=
		bool operator!=(NormalIterator const& var)const {
			return !this->operator==(var);
		}

		NormalIterator& operator++() {
			m_index = m_arr.nextVaildPos(m_index);
			return *this;
		}

		NormalIterator operator++(int) {
			NormalIterator tmp = *this;
			m_index = m_arr.nextVaildPos(m_index);
			return tmp;
		}

		value_type& operator*() {
			return m_arr[m_index];
		}

		value_type const& operator*()const {
			return m_arr[m_index];
		}

		value_type* operator->() {
			return &(m_arr[m_index]);
		}

		value_type const* operator->() const {
			return &(m_arr[m_index]);
		}

		operator bool() {
			return -1 != m_index;
		}

	private:
		NormalIterator(Self& arr, size_type index) :m_arr(arr), m_index(index) {}

		Self& m_arr;
		size_type m_index;
	};

	typedef NormalIterator			iterator;
	typedef NormalIterator const	const_iterator;

public:
	//ctor
	explicit SunnyTcsDynamicVariantArray(size_type defSize = defaultSize)
		:m_data(nullptr), m_size(0), m_nextEmpty(0), m_lastEmpty(0), m_alloc()
	{
		assert(defSize >= 0); //初始容量不可小于0
		this->allocMem(defSize);
	}

	//copy ctor
	SunnyTcsDynamicVariantArray(SunnyTcsDynamicVariantArray const& var)
		:m_data(nullptr), m_size(0), m_nextEmpty(0), m_lastEmpty(0), m_alloc()
	{
		this->operator=(var);
	}

	//move ctor
	SunnyTcsDynamicVariantArray(SunnyTcsDynamicVariantArray&& var) noexcept
		:m_data(nullptr), m_size(0), m_nextEmpty(0), m_lastEmpty(0), m_alloc()
	{
		this->operator=(std::move(var));
	}

	//dector
	virtual ~SunnyTcsDynamicVariantArray() {
		this->destroy();
	}

	//assign
	SunnyTcsDynamicVariantArray& operator=(SunnyTcsDynamicVariantArray const& var) {
		this->destroy();
		this->allocMem(var.m_size);
		m_nextEmpty = var.m_nextEmpty;
		m_lastEmpty = var.m_lastEmpty;
		std::copy(var.m_data, var.m_data + var.m_size, m_data);
		return *this;
	}

	SunnyTcsDynamicVariantArray& operator=(SunnyTcsDynamicVariantArray&& var)noexcept {
		std::swap(m_size, var.m_size);
		std::swap(m_nextEmpty, var.m_nextEmpty);
		std::swap(m_lastEmpty, var.m_lastEmpty);
		std::swap(m_data, var.m_data);
		return *this;
	}

	//operator
	value_type& operator[](size_type pos) {
		assert(pos >= 0 && pos < m_size);
		assert(1 == m_data[pos].index());
		return std::get<1>(m_data[pos]);
	}

	value_type const& operator[](size_type pos)const {
		assert(pos >= 0 && pos < m_size);
		assert(1 == m_data[pos].index());
		return std::get<1>(m_data[pos]);
	}

	bool operator==(SunnyTcsDynamicVariantArray const& var)const {
		SunnyTcsDynamicVariantArray const& maxOne = m_size > var.m_size ? *this : var;
		SunnyTcsDynamicVariantArray const& minOne = m_size > var.m_size ? var : *this;
		std::equal_to<Ty> equlFuncObj;
		for (size_type i = 0; i < maxOne.m_size; ++i) {
			if (minOne.isPosVaild(i) ^ maxOne.isPosVaild(i))return false;
			if (minOne.isPosVaild(i) && maxOne.isPosVaild(i) && !equlFuncObj(minOne[i], maxOne[i]))return false;
		}
		return true;
	}

	bool operator!=(SunnyTcsDynamicVariantArray const& var)const {
		return !this->operator==(var);
	}

	//api
	size_type size()const { return m_size; }

	void resetSize(size_type newSize) {
		this->allocMem(newSize);
	}

	size_type vaildSize()const {
		size_type ret = 0;
		for (size_type i = 0; i < m_size; ++i) {
			if (1 == m_data[i].index())++ret;
		}
		return ret;
	}

	bool isPosVaild(size_type pos)const {
		if (pos < 0 || pos >= m_size)return false;
		return 1 == m_data[pos].index();
	}

	inline size_type firstInVaildPos()const {
		return m_nextEmpty;
	}

	inline size_type firstVaildPos()const {
		return nextVaildPos(-1);
	}

	size_type nextVaildPos(size_type curPos)const {
		if (curPos + 1 == m_size)return -1;
		assert(curPos + 1 >= 0);
		for (size_type i = curPos + 1; i < m_size; ++i) {
			if (this->isPosVaild(i))return i;
		}
		return -1;
	}


	size_type push_front(value_type const& var) {
		if (m_nextEmpty == m_lastEmpty) allocMem(caculateSize(m_size));
		assert(m_data[m_nextEmpty].index() == 0);
		size_type next = std::get<0>(m_data[m_nextEmpty]).second;
		size_type cur = m_nextEmpty;
		m_data[m_nextEmpty] = var;
		m_nextEmpty = next;
		return cur;
	}


	size_type push_back(value_type const& var) {
		if (m_nextEmpty == m_lastEmpty) allocMem(caculateSize(m_size));
		assert(m_data[m_lastEmpty].index() == 0);
		size_type last = std::get<0>(m_data[m_lastEmpty]).first;
		size_type cur = m_lastEmpty;
		m_data[m_lastEmpty] = var;
		m_lastEmpty = last;
		return cur;
	}

	void remove(size_type pos) {
		if (pos < 0 || pos >= m_size || m_data[pos].index() == 0)return;
		m_data[pos] = std::make_pair<size_type, size_type>(0, 0 + m_nextEmpty);
		m_nextEmpty = pos;
	}

	void insert(size_type pos, value_type const& var) {
		if (pos < 0 || pos >= m_size)return;
		if (m_nextEmpty == pos) {
			this->push_front(var);
			return;
		}
		else if (m_lastEmpty == pos) {
			this->push_back(var);
			return;
		}
		else if (0 == m_data[pos].index()) {
			size_type last = std::get<0>(m_data[pos]).first;
			size_type next = std::get<0>(m_data[pos]).second;
			std::get<0>(m_data[last]).second = next;
			std::get<0>(m_data[next]).first = last;
		}
		m_data[pos] = var;
	}

	//初始化一定范围内的元素
	void initRange(size_type start, size_type n) {
		assert(start >= 0 && start + n <= m_size);
		for (int i = start; i < start + n; ++i) {
			this->remove(start);
		}
	}

	//以某个值初始化
	void initRange(size_type start, size_type n, Ty const& var) {
		assert(start >= 0 && start + n <= m_size);
		for (int i = start; i < start + n; ++i) {
			this->insert(i, var);
		}
	}

	void swap(size_type first, size_type second) {
		assert(first >= 0 && first < m_size&& second >= 0 && second < m_size);
		std::swap(m_data[first], m_data[second]);
	}

	//标准库兼容
	iterator begin() {
		return iterator(*this, this->firstVaildPos());
	}

	const_iterator cbegin()const {
		return const_iterator(*this, this->firstVaildPos());
	}

	iterator end() {
		return iterator(*this, -1);
	}

	const_iterator cend()const {
		return const_iterator(*this, -1);
	}

private:
	void allocMem(size_type newSize) {
		if (m_size >= newSize)return;
		ValueTypeNode* newMem = std::allocator_traits<AllocType>::allocate(m_alloc, newSize);
		if (m_data) {
			uninitialized_copy_n(m_data, m_size, newMem); //内存拷贝
			this->freeData();
		}
		else { //初次初始化
			m_nextEmpty = 0;
			m_lastEmpty = newSize - 1;
		}
		m_data = newMem;//指向新内存 
		ValueTypeNode* tmpPtr = m_data + m_size;
		for (size_type i = m_size; i < newSize; ++i) {
			std::allocator_traits<AllocType>::construct(this->m_alloc, tmpPtr, ValueTypeNode(std::make_pair<size_type, size_type>(i - 1, i + 1)));
			++tmpPtr;
		}
		std::get<0>(m_data[m_lastEmpty]).second = m_size;
		std::get<0>(m_data[m_size]).first = m_lastEmpty;
		m_lastEmpty = newSize - 1;
		m_size = newSize;//赋值新内存大小
	}

	//简单的容量算法
	inline size_type caculateSize(size_type cur) { return defaultSize / 2 >= cur ? defaultSize : 2 * cur; }


	void freeData() {
		if (!m_data)return;
		std::for_each(m_data, m_data + m_size, [this](ValueTypeNode& node)->void {
			std::allocator_traits<AllocType>::destroy(this->m_alloc, std::addressof(node));
			}); //析构对象
		std::allocator_traits<AllocType>::deallocate(m_alloc, m_data, m_size); //回收旧内存
		m_data = nullptr;
	}

	void destroy() {
		freeData();
		m_size = 0;
		m_nextEmpty = 0;
		m_lastEmpty = 0;
	}

#ifdef  STRICT_INTERFACE_CHECK
	TCS_ARRAY_INTERFACE_CHECK(Self)
#endif //  STRICT_INTERFACE_CHECK


private:
	AllocType m_alloc;
	size_type m_size;//当前内存长度
	size_type m_nextEmpty;//下一个空位置额索引
	size_type m_lastEmpty;
	ValueTypeNode* m_data;//数据内存区
};

