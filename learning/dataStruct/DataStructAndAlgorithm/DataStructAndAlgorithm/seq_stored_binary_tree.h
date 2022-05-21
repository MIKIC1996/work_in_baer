#pragma once
#include "pch.h"

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

	enum SonNodePosition {
		Left = 1,
		Right = 2,
	};

	
	//层序遍历，顺序存储时，其实就是按照层序存储的，所以层序迭代器最方便
	class tree_level_iterator :public std::iterator<std::bidirectional_iterator_tag, Elem> {
	public:
		friend class seq_stored_binary_tree<Elem>;

		
		Elem& operator*() {
			return _tree_ref._data_array[_h]._data;
		}

		
		Elem* operator->() {
			return &_tree_ref._data_array[_h]._data;
		}

		
		//前置++
		tree_level_iterator& operator++() {
			while (_h < seq_stored_binary_tree<Elem>::array_size - 1  && !_tree_ref._data_array[++_h]._isUsed ); //最后的节点 _h = array_size -1 
			return *this; 
		}


		//后置++
		tree_level_iterator operator++(int) {
			tree_level_iterator tmp = *this;
			this->operator++();
			return tmp;
		}


		//前置--
		tree_level_iterator& operator--() {
			while (_h > 0 && !_tree_ref._data_array[--_h]._isUsed);
			if (_h == 0) //下标0 节点不存数据
				_h = seq_stored_binary_tree<Elem>::array_size - 1; //那就指会end
			return *this;
		}


		//后置--
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
			//索引在正常范围内，且指向节点有数据
			return _h > 0  && _h < array_size-1 && _tree_ref._data_array[_h]._isUsed;
		}

	private:
		tree_level_iterator(seq_stored_binary_tree<Elem>& t, seq_stored_binary_tree<Elem>::Handel h)
			:_tree_ref(t), _h(h)
		{}

		seq_stored_binary_tree<Elem> & _tree_ref;
		Handel _h;
	};


	
	//树接口函数
	virtual void init() {
		memset(_data_array , 0, sizeof(Node)* array_size);
		assert(this->begin() == this->end());
	}

	//重新设置根，因为现有的insert不能添加根，用此函数代替
	virtual void resetRoot(Elem const& e) {
		_data_array[1]._data = e;
		_data_array[1]._isUsed = true;
	}

	virtual void destory() {

	}

	//二叉树的建立 序列化与反序列化
	//前序 序列化
	virtual std::vector<Elem> forward_list() {
		std::vector<Elem> vec;
		this->forward_for_each(this->root(), [&vec](Elem& e) { vec.push_back(e); });
		return vec;
	}

	//中序 序列化
	virtual std::vector<Elem> mid_list() {
		std::vector<Elem> vec;
		this->mid_for_each(this->root(), [&vec](Elem& e) { vec.push_back(e); });
		return vec;
	}

	//后序 序列化
	virtual std::vector<Elem> back_list() {
		std::vector<Elem> vec;
		this->back_for_each(this->root(), [&vec](Elem& e) { vec.push_back(e); });
		return vec;
	}

	//层序 序列化
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


	//基于中序和前序的 反序列化
	virtual void anti_list_by_mid_forward(std::vector<Elem> mid, std::vector<Elem> forward,iterator node ) {
		
		//检查中序和前序 长度是否相等，以及当前的节点是否可以插入数据
		assert(mid.size() == forward.size() );

		auto forward_iter = forward.begin();
		if (forward_iter == forward.end()) { //没有数据可供分析 mid.size() == 0
			return;
		}
	
		//寻找根节点元素再中序中的位置
		auto iter = std::find( mid.begin(), mid.end(), *forward_iter );
		if (iter == mid.end()) {
			assert(false);//非法输入
		}

		//将当前节点赋值
		_data_array[node._h]._data = *iter;
		_data_array[node._h]._isUsed = true;
		
		//接下来的左节点
		iterator left(*this, 2 * node._h);
		iterator right(*this, 2 * node._h + 1);

		//将左子树和右子树从 中序列表中分离
		std::vector<Elem> left_son_tree_mid;
		std::vector<Elem> right_son_tree_mid;
		std::copy(mid.begin(), iter, std::inserter( left_son_tree_mid,left_son_tree_mid.begin()));
		assert(std::distance(mid.begin(), iter) == left_son_tree_mid.size());
		std::copy(++iter, mid.end(), std::inserter(right_son_tree_mid, right_son_tree_mid.begin()));
		assert(std::distance(iter , mid.end()) == right_son_tree_mid.size());
		
		

		//将左子树和右子树从 前序列表中分离
		std::vector<Elem> left_son_tree_forward;
		std::vector<Elem> right_son_tree_forward;
		std::advance(forward_iter, left_son_tree_mid.size() + 1);
		std::copy(forward.begin()+1, forward_iter,
			std::inserter(left_son_tree_forward, left_son_tree_forward.begin()));
		std::copy(forward_iter, forward.end(),
			std::inserter(right_son_tree_forward, right_son_tree_forward.begin()));
		assert(left_son_tree_forward.size() == left_son_tree_mid.size());
		assert(right_son_tree_forward.size() == right_son_tree_mid.size());

		//递归调用
		anti_list_by_mid_forward(left_son_tree_mid, left_son_tree_forward ,left);
		anti_list_by_mid_forward(right_son_tree_mid, right_son_tree_forward , right);

	}

	//完全二叉树序列化


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
			++iter;
		}
		return s;
	}

	virtual int depth() //整棵树深度
	{
		auto iter = this->end();
		if ((--iter) != this->end()) {
			Handel h = iter._h;
			h = std::log2( h );
			h += 1;
			return h;
		}
		return 0;//空树
	}


	virtual int degree(iterator iter)//某个节点的度
	{
		Handel h = iter._h;
		Handel leftSon = 2 * (h);
		Handel rightSon = 2 * (h) + 1 ;
		int deg = 0; //分别查看其左右子节点是否存在且使用
		if (leftSon < array_size-1  && _data_array[leftSon]._isUsed ) { 
			++deg;
		}
		if (rightSon < array_size - 1  && _data_array[rightSon]._isUsed ) {
			++deg;
		}
		return deg;
	}


	//节点操作
	virtual iterator root() { //获取根节点
		return this->begin();
	}


	virtual iterator leftChild(iterator iter) { //左孩子
		assert(iter);//检查迭代器的有效性 
		Handel r = 2 * (iter._h) ; //计算左子节点下标
		return  (r < array_size - 1 && _data_array[r]._isUsed) ? iterator(*this, r) : this->end();
	}


	virtual iterator rightChild(iterator iter) { //右孩子 ，这个接口对二叉树比较方便
		assert(iter);
		Handel r = 2 * (iter._h) + 1;
		return  (r < array_size - 1 && _data_array[r]._isUsed) ? iterator(*this, r) : this->end();
	}


	virtual iterator rightBrother(iterator iter) {
		assert(iter);
		//当前节点是左节点，右节点下标在范围之内，右节点有数据
		return ( iter._h % 2 == 0 && iter._h + 1< array_size-1  && _data_array[iter._h + 1]._isUsed )
			? iterator(*this, iter._h + 1) : this->end();
	}


	virtual iterator parent(iterator iter)  //父母节点
	{
		assert(iter);
		if (iter._h == 1)return this->end(); //根节点没有父母
		return (iter._h ) % 2 == 0 ? /*左节点*/ iterator(*this , (iter._h) / 2 ) : /*右节点*/ iterator(*this , (iter._h - 1) / 2 );
	}


	virtual Elem& value(iterator iter ) {
		assert(iter);
		return *iter;
	}

	


	//子树插入,也采用递归的方式,这里使用前序递归比较合适，因为一般都是自己先赋值了，在给子节点赋值
	//因为我们在设计上给外界提供的都是有效的迭代器，这里需要给出有效迭代器，在指定要插入到这个迭代器的哪个子节点。
	virtual void insertSonTree(iterator tar_node, SonNodePosition pos, seq_stored_binary_tree<Elem>& tree, iterator tree_root_node) {
		if (!tree_root_node) return; //要拷贝的资源节点为空了
		assert(tar_node);//检查拷贝目标地址节点的父节点是否有效
		Handel h = tar_node._h;
		h = (pos == Left) ? 2 * h : 2 * h + 1; //定位到目标节点
		assert(h > 0 && h < array_size - 1 && !_data_array[h]._isUsed ); //检查目标节点位置是否合理，且为空
		_data_array[h]._data = *tree_root_node;
		_data_array[h]._isUsed = true;
		insertSonTree(iterator(*this, h), Left, tree, tree.leftChild(tree_root_node));
		insertSonTree(iterator(*this, h), Right, tree, tree.rightChild(tree_root_node));
	}



	//子树删除，这里采用后序递归比较合适，先删子节点，再删自己
	virtual void deleteSonTree(iterator iter) {
		if (!iter)return; //本节点如果已经清空
		deleteSonTree(this->leftChild(iter));
		deleteSonTree(this->rightChild(iter));
		deleteSonNode(iter);
	}

	

	//节点插入和删除
	virtual void insertSonNode(iterator tar_node, SonNodePosition pos, Elem const& e) //插入一颗 子树tree 到节点的 tar_son_index
	{
		assert(tar_node);
		Handel h = tar_node._h;
		h =  (pos == Left) ? 2 * h : 2 * h + 1;
		assert(h > 0 && h < array_size - 1);
		_data_array[h]._data = e;
		_data_array[h]._isUsed = true;

	}																									
			

	virtual void deleteSonNode(iterator tar_node)  //删除节点
	{
		assert(tar_node && 0 == this->degree(tar_node)); //只能删除叶子节点
		Handel h = tar_node._h;
		memset(&_data_array[h], 0, sizeof(Node));
	}

	//STL标准
	iterator begin() {
		iterator iter(*this,1); //创建一个指向根的迭代器
		return !iter ? end() : iter;
	}

	iterator end() {
		return iterator(*this, array_size-1); // 1023
	}


	bool operator==(seq_stored_binary_tree<Elem> const& tree) {
		return  0 == memcmp(_data_array, tree. _data_array, array_size);
	}


	//遍历
	//前序遍历
	template< typename _functor>
	void forward_for_each(iterator iter , _functor func) {
		if(!iter)return; //无效的迭代器
		func(*iter);
		forward_for_each(this->leftChild(iter),func);
		forward_for_each(this->rightChild(iter),func);
	}

	//成员函数版本
	template<typename _Class>
	void forward_for_each(iterator iter, void (_Class::*func)(Elem&) ,_Class* obj ) {
		if (!iter)return; //无效的迭代器
		obj->func(*iter);
		forward_for_each(this->leftChild(iter), func,obj);
		forward_for_each(this->rightChild(iter), func,obj);
	}


	//中序遍历
	template< typename _functor>
	void mid_for_each(iterator iter, _functor func) {
		if (!iter)return; //无效的迭代器
		mid_for_each(this->leftChild(iter),func);
		func(*iter);
		mid_for_each(this->rightChild(iter),func);
	}

	//后序遍历
	template< typename _functor>
	void back_for_each(iterator iter, _functor func) {
		if (!iter)return;
		back_for_each(this->leftChild(iter), func);
		back_for_each(this->rightChild(iter), func);
		func(*iter);
	}

private:
	Node _data_array[array_size]; //最前面一个和最后面一个不存储数据，最后面一个认为是END,存储下标范围【 1 ， 1022】

};

