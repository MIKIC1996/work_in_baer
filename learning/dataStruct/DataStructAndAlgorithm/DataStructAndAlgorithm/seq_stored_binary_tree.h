#pragma once


template<typename Elem>
class seq_stored_binary_tree //������ȫ������ ˳��洢�� ������
{
public:
	class tree_level_iterator;
	friend class tree_level_iterator;
	typedef tree_level_iterator iterator;
	static constexpr int array_size = 1024;
	typedef int Handel;

	struct Node {
		Elem _data;
		bool _isUsed;//�Ƿ�Ϊ�սڵ�ı�־
	};



	//���������˳��洢ʱ����ʵ���ǰ��ղ���洢�ģ����Բ�����������
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
		

		
		//ǰ��++
		tree_level_iterator& operator++() {
			while (_h < seq_stored_binary_tree<Elem>::array_size - 1  && !_tree_ref[++_h]._isUsed ); //���Ľڵ� _h = array_size -1 
			return *this; 
		}

		//����++
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

	

	

	
	//���ӿں���
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

	//��С
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

	virtual int depth() //���������
	{
		return 0;
	}

	virtual int degree(Handel)//ĳ���ڵ�Ķ�
	{
		return 0;
	}


	//�ڵ����
	virtual Handel root() {
		assert(this->size() > 0);
		return 0;
	}

	virtual Handel leftChild(Handel h) {
		Handel r = 2 * (h + 1) - 1;
		return r;
	}

	virtual Handel rightBrother(Handel h) {
		assert( (h + 1) % 2 == 0 );//ֻ����ڵ�������ֵܣ�
		return h + 1;
	}

	virtual Handel parent(Handel h)  //��ĸ�ڵ�
	{
		return (h + 1) % 2 == 0 ? /*��ڵ�*/ (h + 1) / 2 - 1 : /*�ҽڵ�*/ ((h + 1) - 1) / 2 -1 ;
	}


	virtual Elem value(Handel h ) {
		assert(h >= 0 && h < array_size);
		return _data_array[h]._data;
	}

	//�ڵ�����ɾ��
	virtual void insertSonTree(Handel tar_node, int tar_son_index, seq_stored_binary_tree const& tree) //����һ�� ����tree ���ڵ�� tar_son_index
	{}																									
																											//λ�� 
	virtual void deleteSonTree(Handel tar_node, int tar_son_index)  //ɾ���ڵ�� ������Ϊ tar_son_index ������
	{}

	//---STL��׼--
	iterator begin() {
		iterator iter(*this,0);
		return !iter ? end() : iter;
	}

	iterator end() {
		return iterator(*this, array_size-1);
	}

private:
	Node _data_array[array_size]; //���һ�� _data_array[array_size -1] ��end������ָ��

};

