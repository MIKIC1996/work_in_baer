#pragma once

#include "pch.h"


template<typename Elem>
class list_stored_binary_tree
{
public:
	//遍历策略
	enum Traverse_stategy {
		Forward =1,
		Mid =2,
		Back = 3,
		Level =4
	};

	//子节点指针域标识符号
	enum Link_type
	{
		Link = 1, //树枝 ，只有指针存在且确实指向子节点的情况采用这个类型
		Thread =2  //线索，其他情况都用这个，这样我们判断的时候，要确定某个节点有没有子节点的时候，只要判断
		// 是不是LINK就行了，不用管指针是否为空，因为指针判断并不准确
	};

	enum SonNodePosition {
		Left = 1,
		Right = 2,
	};

	struct Node { //节点数据结构
		//ctor
		Node() :_left_link_type(Thread), _right_link_type(Thread), _left_son(nullptr), _right_son(nullptr), _data() {}

		Link_type _left_link_type;
		Node* _left_son;
		Elem _data;
		Link_type _right_link_type;
		Node* _right_son;
	};

	// 迭代器
	class Normal_iterator;
	typedef Normal_iterator iterator;
	class Const_Normal_iterator;
	typedef Const_Normal_iterator const_iterator;


	//迭代器定义
	//这里只标记forward_tag,虽然我也实现了--操作符，但是在前序排列下是不能使用的，所以要避免标准库使用--操作符
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

		//前置++
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

		//前置++
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
		//使用序列化和反序列化比较简单

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
		

	//树的接口
	virtual void init() {
		_head = new Node(); //初始化创建头节点
		_stategy = Forward;
	}


	virtual void destory() {
		this->clear();
		delete _head;
	}


	//序列化,按照输入要求的序列
	std::vector<Elem> serialize(Traverse_stategy s) {
		std::vector<Elem> ret;
		return ret;
	}


	//反序列化 ,使用前序和中序
	virtual void deserialize_forward(std::vector<Elem> mid_vec , std::vector<Elem> oth_vec) {
		this->clear();
		_deserialize_forward(mid_vec, oth_vec, *this);
	}
	
private:

	void _deserialize_forward(std::vector<Elem> mid_vec, std::vector<Elem> oth_vec, list_stored_binary_tree<Elem>& tree) {
		
		//检查中序和前序 长度是否相等，以及当前的节点是否可以插入数据
		assert(mid_vec.size() == oth_vec.size());
		auto forward_iter = oth_vec.begin();
		if (forward_iter == oth_vec.end()) { //没有数据可供分析 mid.size() == 0
			return;
		}

		//寻找根节点元素再中序中的位置
		auto iter = std::find(mid_vec.begin(), mid_vec.end(), *forward_iter);
		if (iter == mid_vec.end()) {
			assert(false);//非法输入
		}

		//将当前节点赋值
		tree.setRoot(*iter);

		//将左子树和右子树从 中序列表中分离
		std::vector<Elem> left_son_tree_mid;
		std::vector<Elem> right_son_tree_mid;
		std::copy(mid_vec.begin(), iter, std::inserter(left_son_tree_mid, left_son_tree_mid.begin()));
		assert(std::distance(mid_vec.begin(), iter) == left_son_tree_mid.size());
		std::copy(++iter, mid_vec.end(), std::inserter(right_son_tree_mid, right_son_tree_mid.begin()));
		assert(std::distance(iter, mid_vec.end()) == right_son_tree_mid.size());

		

		//将左子树和右子树从 前序列表中分离
		std::vector<Elem> left_son_tree_forward;
		std::vector<Elem> right_son_tree_forward;
		std::advance(forward_iter, left_son_tree_mid.size() + 1);
		std::copy(oth_vec.begin() + 1, forward_iter,
			std::inserter(left_son_tree_forward, left_son_tree_forward.begin()));
		std::copy(forward_iter, oth_vec.end(),
			std::inserter(right_son_tree_forward, right_son_tree_forward.begin()));
		assert(left_son_tree_forward.size() == left_son_tree_mid.size());
		assert(right_son_tree_forward.size() == right_son_tree_mid.size());

		//递归调用
		list_stored_binary_tree<Elem> left_tree;
		list_stored_binary_tree<Elem> right_tree;
		_deserialize_forward(left_son_tree_mid, left_son_tree_forward, left_tree);
		_deserialize_forward(right_son_tree_mid, right_son_tree_forward, right_tree);
		return;
	}



public:
	//清除所有数据
	virtual void clear() {
		auto iter = this->begin();
		iterator tmp = iter;
		while ( iter != this->end()) {
			tmp = iter++;
			delete iter._ptr;
		}
	}

	

	//大小
	virtual bool isEmpty() {
		return true;
	}

	virtual std::size_t size() {
		return std::distance(this->begin(), this->end());
	}

	virtual int depth() //整棵树深度
	{
		return 0;
	}


	virtual int degree(iterator iter) //某个节点的度
	{

		return 0;
	}

	//节点操作
	virtual iterator root() //获取根节点句柄
	{
		return this->begin();
	}

	virtual iterator leftChild(iterator iter)  //最左边（第一个孩子）
	{
		return  Link == iter._ptr->_left_link_type ? iterator(*this, iter._ptr->_left_son) : this->end();
	}
	
	virtual iterator rightChild(iterator iter) //右子节点
	{
		return  Link == iter._ptr->_right_link_type ? iterator(*this, iter._ptr->_right_son) : this->end();
	}


	virtual iterator rightBrother(iterator iter)  //右边的兄弟（弟弟）
	{
		auto ret = this->parent(iter); //先找父母，需要遍历一遍才能找到
		if (ret != this->end() && (ret._ptr->_left_link_type == Link && ret._ptr->_left_son == iter._ptr)) //如果父母存在，并且当前节点是左节点
		{
			return iter._ptr->_right_link_type == Link ? iterator(*this, iter._ptr->_right_son) : this->end();
		}
		return this->end();
	}

	virtual iterator parent(iterator iter) //父母节点
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


	virtual Elem& value(iterator iter) //根据句柄获取对应的值
	{	
		return *iter;
	}

	//节点插入和删除
	virtual void setRoot(Elem const& e) {
		if (!_root ) {
			//这棵树还是空的
			_root = new Node();
		}
		_root->_data = e;
		rearrange(_stategy);
	}


	virtual void insertSonNode(iterator parent_node, SonNodePosition pos, Elem const& e) 
	{
		Link_type& type		=	pos == Left ? parent_node._ptr->_left_link_type : parent_node._ptr->_right_link_type;
		Node*& tar			=	pos == Left ? parent_node._ptr->_left_son : parent_node._ptr->_right_son;
		assert( Link != type ); //不能对已经有数据的节点再进行插入
		tar = new Node();
		tar->_data = e;
		type = Link;
		rearrange(_stategy);
	}
																							   

	virtual void deleteSonNode(iterator parent_node, SonNodePosition pos)  
	{
		//删除节点，这个节点必须是叶子节点
		Node* & tar = pos == Left ? parent_node._ptr->_left_son :  parent_node._ptr->_right_son;
		Link_type& type = Left ? parent_node._ptr->_left_link_type : parent_node._ptr->_right_link_type;
		assert(Link == type && tar); //目标节点必须存在且为 子节点 而非 线索
		assert(Thread == tar->_left_link_type && Thread == tar->_right_link_type); //目标节点必须是叶子节点
		delete tar;
		tar = nullptr;
		type = Thread;
		rearrange(_stategy);
	}

	//子树的插入和删除
	virtual void insertSonTree(iterator parent_node, SonNodePosition pos, list_stored_binary_tree<Elem>& tree) {
		
	}


	virtual void deleteSonTree(iterator tar_node) {
	
	}


	//按照指定顺序重置线索二叉树
	void rearrange(Traverse_stategy s) {
		if (!_root)return;//空树
		_stategy = s;

		_lastOne = _head; //设置到头节点
		_lastOne->_right_link_type = Thread;
		_lastOne->_right_son = nullptr; //将头节点 下一个指向置空
		switch (s)
		{
		case Forward:
			_rearrange_forward(_root, Link); //参数2随意
			break;
		case Mid:
			_rearrange_mid(_root, Link);
			break;
		case Back:
			assert(false); //已经证明后序没有办法使用 递进(++)线索二叉树
			_rearrange_back(_root, Link);
			break;
		default:
			break;
		}
		//遍历完后，最后一个
		assert(Link != _lastOne->_right_link_type);
		_lastOne->_right_link_type = Thread;
		_lastOne->_right_son = _head; //做成循环链表
		if (_stategy == Mid) { //只有mid才可以设置前驱
			_head->_left_link_type = Thread;
			_head->_left_son = _lastOne;
		}
	}


		

	//标准库
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
			//前序遍历的时候，当前节点有左子节点，就选左子节点，否则就选右指针域所指向
			n = (Link == n->_left_link_type) ? n->_left_son : n->_right_son;
			break;
		case Mid:
			n = n->_right_son; //中序遍历的时候，不管是线索还是子节点，都是直接访问自己的右指针域，因为默认左指针域的指向数据已经访问完了
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
			//前序遍历的时候，当前节点有左子节点，就选左子节点，否则就选右指针域所指向
			assert(false);
			break;
		case Mid:
			if (Link == n->_left_link_type) { //左指针域是节点
				n = n->_left_son; //找到做子树根节点
				while (Link == n->_right_link_type) {
					n = n->_right_son;
				}
			}
			else { //左指针域是线索
				assert(n->_left_son);//一定存在
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
		if (Link != type )return; //这里是检测当前节点是否是 一个存在的子节点,或者是根节点也可以 ，线索和空指针的情况直接返回
		assert(cur);

		//前序遍历只能做后继
		if (Link != _lastOne->_right_link_type) { //上一个遍历节点没有右子节点
			_lastOne->_right_link_type = Thread;
			_lastOne->_right_son = cur;  //让上一个节点指向当前节点
		}
		_lastOne = cur; //记录下当前的遍历点


		_rearrange_forward(cur->_left_son, cur->_left_link_type);
		_rearrange_forward(cur->_right_son, cur->_right_link_type);
	}
		
			
		
	void _rearrange_mid(Node* cur, Link_type type) {
		if (Link != type )return; //这里是检测当前节点是否是 一个存在的子节点,或者是根节点也可以 ，线索和空指针的情况直接返回
		assert(cur);

		_rearrange_mid(cur->_left_son, cur->_left_link_type);
		if (Link != _lastOne->_right_link_type) { //上一个遍历节点没有右子节点
			_lastOne->_right_link_type = Thread;
			_lastOne->_right_son = cur;  //让上一个节点指向当前节点
		}
		if (Link != cur->_left_link_type) //左指针域没有记录,那我们记录前驱
		{
			cur->_left_link_type = Thread;
			cur->_left_son = _lastOne;
		}

		_lastOne = cur; //记录下当前的遍历点
		_rearrange_mid(cur->_right_son, cur->_right_link_type);
	}


	void _rearrange_back(Node* cur, Link_type type) {
		assert(false);//后序遍历无法使用线索
	}

private:
	//采用头节点设计,下标值为 -1
	Node* _head; //头节点，是用来在遍历的时候充当 this->end（）的节点
	Traverse_stategy _stategy;
	Node* _root; //树的根节点
	Node* _lastOne; //重排遍历的上一个

};

