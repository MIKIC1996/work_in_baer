#pragma once
#include "pch.h"

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

	enum SonNodePosition {
		Left = 1,
		Right = 2,
	};

	
	//���������˳��洢ʱ����ʵ���ǰ��ղ���洢�ģ����Բ�����������
	class tree_level_iterator :public std::iterator<std::bidirectional_iterator_tag, Elem> {
	public:
		friend class seq_stored_binary_tree<Elem>;

		
		Elem& operator*() {
			return _tree_ref._data_array[_h]._data;
		}

		
		Elem* operator->() {
			return &_tree_ref._data_array[_h]._data;
		}

		
		//ǰ��++
		tree_level_iterator& operator++() {
			while (_h < seq_stored_binary_tree<Elem>::array_size - 1  && !_tree_ref._data_array[++_h]._isUsed ); //���Ľڵ� _h = array_size -1 
			return *this; 
		}


		//����++
		tree_level_iterator operator++(int) {
			tree_level_iterator tmp = *this;
			this->operator++();
			return tmp;
		}


		//ǰ��--
		tree_level_iterator& operator--() {
			while (_h > 0 && !_tree_ref._data_array[--_h]._isUsed);
			if (_h == 0) //�±�0 �ڵ㲻������
				_h = seq_stored_binary_tree<Elem>::array_size - 1; //�Ǿ�ָ��end
			return *this;
		}


		//����--
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
			//������������Χ�ڣ���ָ��ڵ�������
			return _h > 0  && _h < array_size-1 && _tree_ref._data_array[_h]._isUsed;
		}

	private:
		tree_level_iterator(seq_stored_binary_tree<Elem>& t, seq_stored_binary_tree<Elem>::Handel h)
			:_tree_ref(t), _h(h)
		{}

		seq_stored_binary_tree<Elem> & _tree_ref;
		Handel _h;
	};


	
	//���ӿں���
	virtual void init() {
		memset(_data_array , 0, sizeof(Node)* array_size);
		assert(this->begin() == this->end());
	}

	//�������ø�����Ϊ���е�insert������Ӹ����ô˺�������
	virtual void resetRoot(Elem const& e) {
		_data_array[1]._data = e;
		_data_array[1]._isUsed = true;
	}

	virtual void destory() {

	}

	//�������Ľ��� ���л��뷴���л�
	//ǰ�� ���л�
	virtual std::vector<Elem> forward_list() {
		std::vector<Elem> vec;
		this->forward_for_each(this->root(), [&vec](Elem& e) { vec.push_back(e); });
		return vec;
	}

	//���� ���л�
	virtual std::vector<Elem> mid_list() {
		std::vector<Elem> vec;
		this->mid_for_each(this->root(), [&vec](Elem& e) { vec.push_back(e); });
		return vec;
	}

	//���� ���л�
	virtual std::vector<Elem> back_list() {
		std::vector<Elem> vec;
		this->back_for_each(this->root(), [&vec](Elem& e) { vec.push_back(e); });
		return vec;
	}

	//���� ���л�
	virtual std::vector<Elem> level_list() {
		std::vector<Elem> vec;
		auto iter = this->begin();
		for (; iter != this->end(); ++iter) {
			vec.push_back(*iter);
		}
		return vec;
	}

	enum list_method {
		Forward = 1,
		Mid = 2,
		Back = 3,
		Level = 4
	};


	//���������ǰ��� �����л�
	virtual void anti_list_by_mid_forward(std::vector<Elem> mid, std::vector<Elem> forward,iterator node ) {
		
		//��������ǰ�� �����Ƿ���ȣ��Լ���ǰ�Ľڵ��Ƿ���Բ�������
		assert(mid.size() == forward.size() );

		auto forward_iter = forward.begin();
		if (forward_iter == forward.end()) { //û�����ݿɹ����� mid.size() == 0
			return;
		}
	
		//Ѱ�Ҹ��ڵ�Ԫ���������е�λ��
		auto iter = std::find( mid.begin(), mid.end(), *forward_iter );
		if (iter == mid.end()) {
			assert(false);//�Ƿ�����
		}

		//����ǰ�ڵ㸳ֵ
		_data_array[node._h]._data = *iter;
		_data_array[node._h]._isUsed = true;
		
		//����������ڵ�
		iterator left(*this, 2 * node._h);
		iterator right(*this, 2 * node._h + 1);

		//������������������ �����б��з���
		std::vector<Elem> left_son_tree_mid;
		std::vector<Elem> right_son_tree_mid;
		std::copy(mid.begin(), iter, std::inserter( left_son_tree_mid,left_son_tree_mid.begin()));
		assert(std::distance(mid.begin(), iter) == left_son_tree_mid.size());
		std::copy(++iter, mid.end(), std::inserter(right_son_tree_mid, right_son_tree_mid.begin()));
		assert(std::distance(iter , mid.end()) == right_son_tree_mid.size());
		
		

		//������������������ ǰ���б��з���
		std::vector<Elem> left_son_tree_forward;
		std::vector<Elem> right_son_tree_forward;
		std::advance(forward_iter, left_son_tree_mid.size() + 1);
		std::copy(forward.begin()+1, forward_iter,
			std::inserter(left_son_tree_forward, left_son_tree_forward.begin()));
		std::copy(forward_iter, forward.end(),
			std::inserter(right_son_tree_forward, right_son_tree_forward.begin()));
		assert(left_son_tree_forward.size() == left_son_tree_mid.size());
		assert(right_son_tree_forward.size() == right_son_tree_mid.size());

		//�ݹ����
		anti_list_by_mid_forward(left_son_tree_mid, left_son_tree_forward ,left);
		anti_list_by_mid_forward(right_son_tree_mid, right_son_tree_forward , right);

	}

	//��ȫ���������л�


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
			++iter;
		}
		return s;
	}

	virtual int depth() //���������
	{
		auto iter = this->end();
		if ((--iter) != this->end()) {
			Handel h = iter._h;
			h = std::log2( h );
			h += 1;
			return h;
		}
		return 0;//����
	}


	virtual int degree(iterator iter)//ĳ���ڵ�Ķ�
	{
		Handel h = iter._h;
		Handel leftSon = 2 * (h);
		Handel rightSon = 2 * (h) + 1 ;
		int deg = 0; //�ֱ�鿴�������ӽڵ��Ƿ������ʹ��
		if (leftSon < array_size-1  && _data_array[leftSon]._isUsed ) { 
			++deg;
		}
		if (rightSon < array_size - 1  && _data_array[rightSon]._isUsed ) {
			++deg;
		}
		return deg;
	}


	//�ڵ����
	virtual iterator root() { //��ȡ���ڵ�
		return this->begin();
	}


	virtual iterator leftChild(iterator iter) { //����
		assert(iter);//������������Ч�� 
		Handel r = 2 * (iter._h) ; //�������ӽڵ��±�
		return  (r < array_size - 1 && _data_array[r]._isUsed) ? iterator(*this, r) : this->end();
	}


	virtual iterator rightChild(iterator iter) { //�Һ��� ������ӿڶԶ������ȽϷ���
		assert(iter);
		Handel r = 2 * (iter._h) + 1;
		return  (r < array_size - 1 && _data_array[r]._isUsed) ? iterator(*this, r) : this->end();
	}


	virtual iterator rightBrother(iterator iter) {
		assert(iter);
		//��ǰ�ڵ�����ڵ㣬�ҽڵ��±��ڷ�Χ֮�ڣ��ҽڵ�������
		return ( iter._h % 2 == 0 && iter._h + 1< array_size-1  && _data_array[iter._h + 1]._isUsed )
			? iterator(*this, iter._h + 1) : this->end();
	}


	virtual iterator parent(iterator iter)  //��ĸ�ڵ�
	{
		assert(iter);
		if (iter._h == 1)return this->end(); //���ڵ�û�и�ĸ
		return (iter._h ) % 2 == 0 ? /*��ڵ�*/ iterator(*this , (iter._h) / 2 ) : /*�ҽڵ�*/ iterator(*this , (iter._h - 1) / 2 );
	}


	virtual Elem& value(iterator iter ) {
		assert(iter);
		return *iter;
	}

	


	//��������,Ҳ���õݹ�ķ�ʽ,����ʹ��ǰ��ݹ�ȽϺ��ʣ���Ϊһ�㶼���Լ��ȸ�ֵ�ˣ��ڸ��ӽڵ㸳ֵ
	//��Ϊ����������ϸ�����ṩ�Ķ�����Ч�ĵ�������������Ҫ������Ч����������ָ��Ҫ���뵽������������ĸ��ӽڵ㡣
	virtual void insertSonTree(iterator tar_node, SonNodePosition pos, seq_stored_binary_tree<Elem>& tree, iterator tree_root_node) {
		if (!tree_root_node) return; //Ҫ��������Դ�ڵ�Ϊ����
		assert(tar_node);//��鿽��Ŀ���ַ�ڵ�ĸ��ڵ��Ƿ���Ч
		Handel h = tar_node._h;
		h = (pos == Left) ? 2 * h : 2 * h + 1; //��λ��Ŀ��ڵ�
		assert(h > 0 && h < array_size - 1 && !_data_array[h]._isUsed ); //���Ŀ��ڵ�λ���Ƿ������Ϊ��
		_data_array[h]._data = *tree_root_node;
		_data_array[h]._isUsed = true;
		insertSonTree(iterator(*this, h), Left, tree, tree.leftChild(tree_root_node));
		insertSonTree(iterator(*this, h), Right, tree, tree.rightChild(tree_root_node));
	}



	//����ɾ����������ú���ݹ�ȽϺ��ʣ���ɾ�ӽڵ㣬��ɾ�Լ�
	virtual void deleteSonTree(iterator iter) {
		if (!iter)return; //���ڵ�����Ѿ����
		deleteSonTree(this->leftChild(iter));
		deleteSonTree(this->rightChild(iter));
		deleteSonNode(iter);
	}

	

	//�ڵ�����ɾ��
	virtual void insertSonNode(iterator tar_node, SonNodePosition pos, Elem const& e) //����һ�� ����tree ���ڵ�� tar_son_index
	{
		assert(tar_node);
		Handel h = tar_node._h;
		h =  (pos == Left) ? 2 * h : 2 * h + 1;
		assert(h > 0 && h < array_size - 1);
		_data_array[h]._data = e;
		_data_array[h]._isUsed = true;

	}																									
			

	virtual void deleteSonNode(iterator tar_node)  //ɾ���ڵ�
	{
		assert(tar_node && 0 == this->degree(tar_node)); //ֻ��ɾ��Ҷ�ӽڵ�
		Handel h = tar_node._h;
		memset(&_data_array[h], 0, sizeof(Node));
	}

	//STL��׼
	iterator begin() {
		iterator iter(*this,1); //����һ��ָ����ĵ�����
		return !iter ? end() : iter;
	}

	iterator end() {
		return iterator(*this, array_size-1); // 1023
	}


	bool operator==(seq_stored_binary_tree<Elem> const& tree) {
		return  0 == memcmp(_data_array, tree. _data_array, array_size);
	}


	//����
	//ǰ�����
	template< typename _functor>
	void forward_for_each(iterator iter , _functor func) {
		if(!iter)return; //��Ч�ĵ�����
		func(*iter);
		forward_for_each(this->leftChild(iter),func);
		forward_for_each(this->rightChild(iter),func);
	}

	//��Ա�����汾
	template<typename _Class>
	void forward_for_each(iterator iter, void (_Class::*func)(Elem&) ,_Class* obj ) {
		if (!iter)return; //��Ч�ĵ�����
		obj->func(*iter);
		forward_for_each(this->leftChild(iter), func,obj);
		forward_for_each(this->rightChild(iter), func,obj);
	}


	//�������
	template< typename _functor>
	void mid_for_each(iterator iter, _functor func) {
		if (!iter)return; //��Ч�ĵ�����
		mid_for_each(this->leftChild(iter),func);
		func(*iter);
		mid_for_each(this->rightChild(iter),func);
	}

	//�������
	template< typename _functor>
	void back_for_each(iterator iter, _functor func) {
		if (!iter)return;
		back_for_each(this->leftChild(iter), func);
		back_for_each(this->rightChild(iter), func);
		func(*iter);
	}

private:
	Node _data_array[array_size]; //��ǰ��һ���������һ�����洢���ݣ������һ����Ϊ��END,�洢�±귶Χ�� 1 �� 1022��

};

