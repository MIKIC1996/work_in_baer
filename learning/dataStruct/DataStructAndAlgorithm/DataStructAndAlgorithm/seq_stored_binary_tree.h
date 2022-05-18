#pragma once


template<typename Elem>
class seq_stored_binary_tree //基于完全二叉树 顺序存储的 二叉树
{
public:
	class tree_level_iterator;
	friend class tree_level_iterator;
	typedef tree_level_iterator iterator;
	static constexpr int array_size = 1024;
	typedef int Handel;

	struct Node {
		Elem _data;
		bool _isUsed;//是否为空节点的标志
	};



	//层序遍历，顺序存储时，其实就是按照层序存储的，所以层序迭代器最方便
	class tree_level_iterator :public std::iterator<std::bidirectional_iterator_tag, Elem> {
	public:
		tree_level_iterator(seq_stored_binary_tree<Elem> & t , seq_stored_binary_tree<Elem>::Handel h)
			:_tree_ref(t),_h(h)
		{}

		
		Elem& operator*() {
			return _tree_ref._data_array[_h]._data;
		}

		
		Elem* operator->() {
			return &_tree_ref._data_array[_h]._data;
		}
		

		
		//前置++
		tree_level_iterator& operator++() {
			while (_h < seq_stored_binary_tree<Elem>::array_size - 1  && !_tree_ref[++_h]._isUsed ); //最后的节点 _h = array_size -1 
			return *this; 
		}

		//后置++
		tree_level_iterator operator++(int) {
			tree_level_iterator tmp = *this;
			this->operator++();
			return tmp;
		}

		tree_level_iterator& operator--() {
			while (_h > 0 && !_tree_ref[--_h]._isUsed);
			return *this;
		}

		tree_level_iterator operator--(int) {
			tree_level_iterator tmp = *this;
			this->operator--();
			return tmp;
		}

		bool operator==(tree_level_iterator const & iter) {
			return &_tree_ref == &iter._tree_ref && _h == iter._h;
		}

		bool operator!=(tree_level_iterator const & iter) {
			return !this->operator==(iter);
		}

		operator bool() {
			return _tree_ref._data_array[_h]._isUsed;
		}

	private:
		seq_stored_binary_tree<Elem> & _tree_ref;
		Handel _h;
	};

	

	

	
	//树接口函数
	virtual void init() {
		memset(_data_array , 0, sizeof(Node)* array_size);
	}

	virtual void destory() {

	}

	virtual bool create(std::string def) {
		return false;
	}

	virtual void clear() {
		this->init();
	}

	//大小
	virtual bool isEmpty() {
		return this->begin() == this->end();
	}

	virtual std::size_t size() {
		auto iter = this->begin();
		std::size_t s=0;
		while (iter != this->end()) {
			++s;
		}
		return s;
	}

	virtual int depth() //整棵树深度
	{
		return 0;
	}

	virtual int degree(Handel)//某个节点的度
	{
		return 0;
	}


	//节点操作
	virtual Handel root() {
		assert(this->size() > 0);
		return 0;
	}

	virtual Handel leftChild(Handel h) {
		Handel r = 2 * (h + 1) - 1;
		return r;
	}

	virtual Handel rightBrother(Handel h) {
		assert( (h + 1) % 2 == 0 );//只有左节点才有右兄弟；
		return h + 1;
	}

	virtual Handel parent(Handel h)  //父母节点
	{
		return (h + 1) % 2 == 0 ? /*左节点*/ (h + 1) / 2 - 1 : /*右节点*/ ((h + 1) - 1) / 2 -1 ;
	}


	virtual Elem value(Handel h ) {
		assert(h >= 0 && h < array_size);
		return _data_array[h]._data;
	}

	//节点插入和删除
	virtual void insertSonTree(Handel tar_node, int tar_son_index, seq_stored_binary_tree const& tree) //插入一颗 子树tree 到节点的 tar_son_index
	{}																									
																											//位置 
	virtual void deleteSonTree(Handel tar_node, int tar_son_index)  //删除节点的 子索引为 tar_son_index 的子树
	{}

	//---STL标准--
	iterator begin() {
		iterator iter(*this,0);
		return !iter ? end() : iter;
	}

	iterator end() {
		return iterator(*this, array_size-1);
	}

private:
	Node _data_array[array_size]; //最后一个 _data_array[array_size -1] 做end迭代器指向

};

