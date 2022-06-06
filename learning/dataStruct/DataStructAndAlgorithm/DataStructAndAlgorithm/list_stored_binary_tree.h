#pragma once

#include "pch.h"


template<typename Elem>
class list_stored_binary_tree
{
public:
	//��������
	enum Traverse_stategy {
		Forward =1,
		Mid =2,
		Back = 3,
		Level =4
	};

	//�ӽڵ�ָ�����ʶ����
	enum Link_type
	{
		Link = 1, //��֦ ��ֻ��ָ�������ȷʵָ���ӽڵ����������������
		Thread =2  //�������������������������������жϵ�ʱ��Ҫȷ��ĳ���ڵ���û���ӽڵ��ʱ��ֻҪ�ж�
		// �ǲ���LINK�����ˣ����ù�ָ���Ƿ�Ϊ�գ���Ϊָ���жϲ���׼ȷ
	};

	enum SonNodePosition {
		Left = 1,
		Right = 2,
	};

	struct Node { //�ڵ����ݽṹ
		//ctor
		Node() :_left_link_type(Thread), _right_link_type(Thread), _left_son(nullptr), _right_son(nullptr), _data() {}

		Link_type _left_link_type;
		Node* _left_son;
		Elem _data;
		Link_type _right_link_type;
		Node* _right_son;
	};

	// ������
	class Normal_iterator;
	typedef Normal_iterator iterator;
	class Const_Normal_iterator;
	typedef Const_Normal_iterator const_iterator;


	//����������
	//����ֻ���forward_tag,��Ȼ��Ҳʵ����--��������������ǰ���������ǲ���ʹ�õģ�����Ҫ�����׼��ʹ��--������
	class Normal_iterator :public std::iterator<std::forward_iterator_tag,Elem> { 
	public:
		friend class list_stored_binary_tree<Elem>;

		Normal_iterator(list_stored_binary_tree<Elem>& tree ,Node* n): _tree(tree),_ptr(n) {}

		Normal_iterator(Normal_iterator const& ) = default;

		~Normal_iterator() {}

		Normal_iterator& operator=(Normal_iterator const& rhs) 
		{
			_ptr = rhs._ptr;
			return *this;
		}

		


		Elem& operator*() {
			return _ptr->_data;
		}

		Elem* operator->() {
			return _ptr->_data;
		}

		//ǰ��++
		Normal_iterator& operator++() {
			_tree.next(*this);
			return *this;
		}

		Normal_iterator& operator++(int) {
			Normal_iterator tmp(*this);
			this->operator++();
			return tmp;
		}

		Normal_iterator& operator--() {
			_tree.back(*this);
			return *this;
		}

		Normal_iterator& operator--(int) {
			Normal_iterator tmp(*this);
			this->operator--();
			return tmp;
		}

		bool operator==(iterator const& iter) {
			return _ptr == iter._ptr;
		}

		bool operator!=(iterator const& iter) {
			return !this->operator==(iter);
		}

	private:
		Node* _ptr;
		list_stored_binary_tree<Elem>& _tree;
	};

	class Const_Normal_iterator :public std::iterator<std::forward_iterator_tag, Elem> {
	public:
		friend class list_stored_binary_tree<Elem>;

		Const_Normal_iterator(list_stored_binary_tree<Elem>& tree, Node* n) : _tree(tree), _ptr(n) {}

		Elem const & operator*() {
			return _ptr->_data;
		}

		Elem const* operator->() {
			return _ptr->_data;
		}

		//ǰ��++
		Const_Normal_iterator& operator++() {
			_tree.next(*this);
			return *this;
		}

		Const_Normal_iterator& operator++(int) {
			Const_Normal_iterator tmp(*this);
			this->operator++();
			return tmp;
		}

		Const_Normal_iterator& operator--() {
			_tree.back(*this);
			return *this;
		}

		Const_Normal_iterator& operator--(int) {
			Const_Normal_iterator tmp(*this);
			this->operator--();
			return tmp;
		}

		bool operator==(Const_Normal_iterator const& iter) {
			return _ptr == iter._ptr;
		}

		bool operator!=(Const_Normal_iterator const& iter) {
			return !this->operator==(iter);
		}

	private:
		Node* _ptr;
		list_stored_binary_tree<Elem>& _tree;
	};

	//ctor
	list_stored_binary_tree() 
		: _head(nullptr),_root(nullptr),_lastOne(nullptr),_stategy(Forward)
	{
		this->init();
	}

	//copy ctor
	list_stored_binary_tree(list_stored_binary_tree const& rhs)
		: _head(nullptr), _root(nullptr), _lastOne(nullptr), _stategy(Forward)
	{
		this->init();
		//ʹ�����л��ͷ����л��Ƚϼ�

	}

	//move ctor
	list_stored_binary_tree(list_stored_binary_tree&& rhs)
		: _head(nullptr), _root(nullptr), _lastOne(nullptr), _stategy(rhs._stategy)
	{
		_head = rhs._head;
		rhs._head = nullptr;
		_root = rhs._root;
		rhs._root = nullptr;
		this->rearrange(_stategy);

	}
	

	//dector
	~list_stored_binary_tree() {
		destory();
	}
		

	//���Ľӿ�
	virtual void init() {
		_head = new Node(); //��ʼ������ͷ�ڵ�
		_stategy = Forward;
	}


	virtual void destory() {
		this->clear();
		delete _head;
	}


	//���л�,��������Ҫ�������
	std::vector<Elem> serialize(Traverse_stategy s) {
		std::vector<Elem> ret;
		return ret;
	}


	//�����л� ,ʹ��ǰ�������
	virtual void deserialize_forward(std::vector<Elem> mid_vec , std::vector<Elem> oth_vec) {
		this->clear();
		_deserialize_forward(mid_vec, oth_vec, *this);
	}
	
private:

	void _deserialize_forward(std::vector<Elem> mid_vec, std::vector<Elem> oth_vec, list_stored_binary_tree<Elem>& tree) {
		
		//��������ǰ�� �����Ƿ���ȣ��Լ���ǰ�Ľڵ��Ƿ���Բ�������
		assert(mid_vec.size() == oth_vec.size());
		auto forward_iter = oth_vec.begin();
		if (forward_iter == oth_vec.end()) { //û�����ݿɹ����� mid.size() == 0
			return;
		}

		//Ѱ�Ҹ��ڵ�Ԫ���������е�λ��
		auto iter = std::find(mid_vec.begin(), mid_vec.end(), *forward_iter);
		if (iter == mid_vec.end()) {
			assert(false);//�Ƿ�����
		}

		//����ǰ�ڵ㸳ֵ
		tree.setRoot(*iter);

		//������������������ �����б��з���
		std::vector<Elem> left_son_tree_mid;
		std::vector<Elem> right_son_tree_mid;
		std::copy(mid_vec.begin(), iter, std::inserter(left_son_tree_mid, left_son_tree_mid.begin()));
		assert(std::distance(mid_vec.begin(), iter) == left_son_tree_mid.size());
		std::copy(++iter, mid_vec.end(), std::inserter(right_son_tree_mid, right_son_tree_mid.begin()));
		assert(std::distance(iter, mid_vec.end()) == right_son_tree_mid.size());

		

		//������������������ ǰ���б��з���
		std::vector<Elem> left_son_tree_forward;
		std::vector<Elem> right_son_tree_forward;
		std::advance(forward_iter, left_son_tree_mid.size() + 1);
		std::copy(oth_vec.begin() + 1, forward_iter,
			std::inserter(left_son_tree_forward, left_son_tree_forward.begin()));
		std::copy(forward_iter, oth_vec.end(),
			std::inserter(right_son_tree_forward, right_son_tree_forward.begin()));
		assert(left_son_tree_forward.size() == left_son_tree_mid.size());
		assert(right_son_tree_forward.size() == right_son_tree_mid.size());

		//�ݹ����
		list_stored_binary_tree<Elem> left_tree;
		list_stored_binary_tree<Elem> right_tree;
		_deserialize_forward(left_son_tree_mid, left_son_tree_forward, left_tree);
		_deserialize_forward(right_son_tree_mid, right_son_tree_forward, right_tree);
		return;
	}



public:
	//�����������
	virtual void clear() {
		auto iter = this->begin();
		iterator tmp = iter;
		while ( iter != this->end()) {
			tmp = iter++;
			delete iter._ptr;
		}
	}

	

	//��С
	virtual bool isEmpty() {
		return true;
	}

	virtual std::size_t size() {
		return std::distance(this->begin(), this->end());
	}

	virtual int depth() //���������
	{
		return 0;
	}


	virtual int degree(iterator iter) //ĳ���ڵ�Ķ�
	{

		return 0;
	}

	//�ڵ����
	virtual iterator root() //��ȡ���ڵ���
	{
		return this->begin();
	}

	virtual iterator leftChild(iterator iter)  //����ߣ���һ�����ӣ�
	{
		return  Link == iter._ptr->_left_link_type ? iterator(*this, iter._ptr->_left_son) : this->end();
	}
	
	virtual iterator rightChild(iterator iter) //���ӽڵ�
	{
		return  Link == iter._ptr->_right_link_type ? iterator(*this, iter._ptr->_right_son) : this->end();
	}


	virtual iterator rightBrother(iterator iter)  //�ұߵ��ֵܣ��ܵܣ�
	{
		auto ret = this->parent(iter); //���Ҹ�ĸ����Ҫ����һ������ҵ�
		if (ret != this->end() && (ret._ptr->_left_link_type == Link && ret._ptr->_left_son == iter._ptr)) //�����ĸ���ڣ����ҵ�ǰ�ڵ�����ڵ�
		{
			return iter._ptr->_right_link_type == Link ? iterator(*this, iter._ptr->_right_son) : this->end();
		}
		return this->end();
	}

	virtual iterator parent(iterator iter) //��ĸ�ڵ�
	{
		auto ret = this->begin();
		while (ret != this->end()) {
			if ((ret._ptr->_left_link_type == Link && ret._ptr->_left_son == iter._ptr) || 
				(ret._ptr->_right_link_type == Link && ret._ptr->_right_son == iter._ptr)) 
			{
				return ret;
			}
			++ret;
		}
		return ret;
	}


	virtual Elem& value(iterator iter) //���ݾ����ȡ��Ӧ��ֵ
	{	
		return *iter;
	}

	//�ڵ�����ɾ��
	virtual void setRoot(Elem const& e) {
		if (!_root ) {
			//��������ǿյ�
			_root = new Node();
		}
		_root->_data = e;
		rearrange(_stategy);
	}


	virtual void insertSonNode(iterator parent_node, SonNodePosition pos, Elem const& e) 
	{
		Link_type& type		=	pos == Left ? parent_node._ptr->_left_link_type : parent_node._ptr->_right_link_type;
		Node*& tar			=	pos == Left ? parent_node._ptr->_left_son : parent_node._ptr->_right_son;
		assert( Link != type ); //���ܶ��Ѿ������ݵĽڵ��ٽ��в���
		tar = new Node();
		tar->_data = e;
		type = Link;
		rearrange(_stategy);
	}
																							   

	virtual void deleteSonNode(iterator parent_node, SonNodePosition pos)  
	{
		//ɾ���ڵ㣬����ڵ������Ҷ�ӽڵ�
		Node* & tar = pos == Left ? parent_node._ptr->_left_son :  parent_node._ptr->_right_son;
		Link_type& type = Left ? parent_node._ptr->_left_link_type : parent_node._ptr->_right_link_type;
		assert(Link == type && tar); //Ŀ��ڵ���������Ϊ �ӽڵ� ���� ����
		assert(Thread == tar->_left_link_type && Thread == tar->_right_link_type); //Ŀ��ڵ������Ҷ�ӽڵ�
		delete tar;
		tar = nullptr;
		type = Thread;
		rearrange(_stategy);
	}

	//�����Ĳ����ɾ��
	virtual void insertSonTree(iterator parent_node, SonNodePosition pos, list_stored_binary_tree<Elem>& tree) {
		
	}


	virtual void deleteSonTree(iterator tar_node) {
	
	}


	//����ָ��˳����������������
	void rearrange(Traverse_stategy s) {
		if (!_root)return;//����
		_stategy = s;

		_lastOne = _head; //���õ�ͷ�ڵ�
		_lastOne->_right_link_type = Thread;
		_lastOne->_right_son = nullptr; //��ͷ�ڵ� ��һ��ָ���ÿ�
		switch (s)
		{
		case Forward:
			_rearrange_forward(_root, Link); //����2����
			break;
		case Mid:
			_rearrange_mid(_root, Link);
			break;
		case Back:
			assert(false); //�Ѿ�֤������û�а취ʹ�� �ݽ�(++)����������
			_rearrange_back(_root, Link);
			break;
		default:
			break;
		}
		//����������һ��
		assert(Link != _lastOne->_right_link_type);
		_lastOne->_right_link_type = Thread;
		_lastOne->_right_son = _head; //����ѭ������
		if (_stategy == Mid) { //ֻ��mid�ſ�������ǰ��
			_head->_left_link_type = Thread;
			_head->_left_son = _lastOne;
		}
	}


		

	//��׼��
	iterator begin() {
		return _head->_right_son ? iterator(*this,_head->_right_son) : this->end();
	}


	iterator end() {
		return iterator(*this,_head);
	}

	const_iterator c_begin()const {
	
	}

	const_iterator c_end()const {
	
	}

private:
	template<typename _Iter>
	void next(_Iter& iter) {
		Node*& n = iter._ptr;
		switch (_stategy)
		{
		case Forward:
			//ǰ�������ʱ�򣬵�ǰ�ڵ������ӽڵ㣬��ѡ���ӽڵ㣬�����ѡ��ָ������ָ��
			n = (Link == n->_left_link_type) ? n->_left_son : n->_right_son;
			break;
		case Mid:
			n = n->_right_son; //���������ʱ�򣬲��������������ӽڵ㣬����ֱ�ӷ����Լ�����ָ������ΪĬ����ָ�����ָ�������Ѿ���������
			break;
		case Back:
			assert(false);
			break;
		default:
			break;
		}
	}

	template<typename _Iter>
	void back(_Iter& iter) {
		Node*& n = iter._ptr;
		switch (_stategy)
		{
		case Forward:
			//ǰ�������ʱ�򣬵�ǰ�ڵ������ӽڵ㣬��ѡ���ӽڵ㣬�����ѡ��ָ������ָ��
			assert(false);
			break;
		case Mid:
			if (Link == n->_left_link_type) { //��ָ�����ǽڵ�
				n = n->_left_son; //�ҵ����������ڵ�
				while (Link == n->_right_link_type) {
					n = n->_right_son;
				}
			}
			else { //��ָ����������
				assert(n->_left_son);//һ������
				n = n->_left_son;
			}
			break;

		case Back:
			assert(false);
			break;
		default:
			break;
		}
	}

private:
	
	void _rearrange_forward(Node* cur,Link_type type) {
		if (Link != type )return; //�����Ǽ�⵱ǰ�ڵ��Ƿ��� һ�����ڵ��ӽڵ�,�����Ǹ��ڵ�Ҳ���� �������Ϳ�ָ������ֱ�ӷ���
		assert(cur);

		//ǰ�����ֻ�������
		if (Link != _lastOne->_right_link_type) { //��һ�������ڵ�û�����ӽڵ�
			_lastOne->_right_link_type = Thread;
			_lastOne->_right_son = cur;  //����һ���ڵ�ָ��ǰ�ڵ�
		}
		_lastOne = cur; //��¼�µ�ǰ�ı�����


		_rearrange_forward(cur->_left_son, cur->_left_link_type);
		_rearrange_forward(cur->_right_son, cur->_right_link_type);
	}
		
			
		
	void _rearrange_mid(Node* cur, Link_type type) {
		if (Link != type )return; //�����Ǽ�⵱ǰ�ڵ��Ƿ��� һ�����ڵ��ӽڵ�,�����Ǹ��ڵ�Ҳ���� �������Ϳ�ָ������ֱ�ӷ���
		assert(cur);

		_rearrange_mid(cur->_left_son, cur->_left_link_type);
		if (Link != _lastOne->_right_link_type) { //��һ�������ڵ�û�����ӽڵ�
			_lastOne->_right_link_type = Thread;
			_lastOne->_right_son = cur;  //����һ���ڵ�ָ��ǰ�ڵ�
		}
		if (Link != cur->_left_link_type) //��ָ����û�м�¼,�����Ǽ�¼ǰ��
		{
			cur->_left_link_type = Thread;
			cur->_left_son = _lastOne;
		}

		_lastOne = cur; //��¼�µ�ǰ�ı�����
		_rearrange_mid(cur->_right_son, cur->_right_link_type);
	}


	void _rearrange_back(Node* cur, Link_type type) {
		assert(false);//��������޷�ʹ������
	}

private:
	//����ͷ�ڵ����,�±�ֵΪ -1
	Node* _head; //ͷ�ڵ㣬�������ڱ�����ʱ��䵱 this->end�����Ľڵ�
	Traverse_stategy _stategy;
	Node* _root; //���ĸ��ڵ�
	Node* _lastOne; //���ű�������һ��

};

