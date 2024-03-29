#include "stdafx.h"
#include "c2_allocator.h"


namespace jmq_std {


	template<int inst>
	void(*__malloc_alloc_template<inst>::__malloc_alloc_oom_hander)() = nullptr;

	template<int inst>
	void* __malloc_alloc_template<inst>::oom_malloc(size_t n) {
		void(*my_malloc_hander)();
		void * result;

		for (;;) { //不断的重新配置
			my_malloc_hander = __malloc_alloc_oom_hander;
			if (nullptr = my_malloc_hander) {
				__THROW_BAD_ALLOC_JMQ;
			}
			(*my_malloc_hander)(); //调用处理例程，企图释放内存
			result = malloc(n);
			if (result)return result;
		}

	}

	template<int inst>
	void* __malloc_alloc_template<inst>::oom_realloc(void* p, size_t n) {
		void(*my_malloc_hander)();
		void * result;

		for (;;) { //不断的重新配置
			my_malloc_hander = __malloc_alloc_oom_hander;
			if (nullptr = my_malloc_hander) {
				__THROW_BAD_ALLOC_JMQ;
			}
			(*my_malloc_hander)(); //调用处理例程，企图释放内存
			result = realloc(p, n);
			if (result)return result;
		}
	}


	template<int inst>
	char* __default_alloc_template<inst>::start_free = nullptr;

	template<int inst>
	char* __default_alloc_template<inst>::end_free = nullptr;

	template<int inst>
	size_t __default_alloc_template<inst>::heap_size = 0;

	template<int inst>
	obj* volatile  __default_alloc_template<inst>::free_list[__NFREELISTS] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


	template<int inst>
	void* __default_alloc_template<inst>::allocate(size_t n) {
		obj* volatile * my_free_list;
		obj* result;

		if (n > (size_t)(__MAX_BYTES)) {
			return malloc_alloc::allocate(n);
		}

		my_free_list = free_list + freeList_index(n);
		result = *my_free_list;
		if (nullptr == result) {
			//没有可用的free list ,重新填充free_list
			void* r = refill(round_up(n));
			return r;
		}
		*my_free_list = result->free_list_link;
		return result;
	}

	template<int inst>
	void __default_alloc_template<inst> ::deallocate(void* p, size_t n)
	{
		Q_ASSERT(p);
		obj* q = (obj*)p;
		obj* volatile *my_free_list;

		//寻找合适的
		if (n > (size_t)__MAX_BYTES) {
			malloc_alloc::deallocate(p, n);
			return;
		}
		//回收区块
		my_free_list = free_list + freeList_index(n);
		q->free_list_link = *my_free_list;
		*my_free_list = q;
	}


	template<int inst>
	void* __default_alloc_template<inst>::refill(size_t n) {
		int nobjs = 20;
		char* chunk = chunk_alloc(n, nobjs);
		obj* volatile * my_free_list = nullptr;
		obj* result = nullptr;
		obj* current_obj = nullptr, *next_obj = nullptr;
		int i = 0;

		if (1 == nobjs) { //只获得了一个，直接返回给客端，不填充free_list
			return (obj*)chunk;
		}

		my_free_list = free_list + freeList_index(n);
		result = (obj*)(chunk);
		*my_free_list = next_obj = (obj*)(chunk + n);
		for (i = 1;; i++) {
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);
			if (nobjs - 1 == i) {
				current_obj->free_list_link = nullptr; //对尾最后一个obj的free_list_link总是设为0
				break;
			}
			else {
				current_obj->free_list_link = next_obj;
			}
		}
		return result;
	}



	template<int inst>
	char* __default_alloc_template<inst>::chunk_alloc(size_t size, int& nobjs)
	{
		char* result = nullptr;
		size_t total_bytes = size * nobjs;
		size_t bytes_left = end_free - start_free;
		if (bytes_left > total_bytes) {
			//内存足够
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else if (bytes_left > size) {
			//足够供应一个以上 ，nobjs个以下
			nobjs = bytes_left / size;
			total_bytes = nobjs * size;
			result = start_free;
			//同上
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else {
			//一个都不够
			//先处理残余空间，编入free_list
			if (bytes_left > 0) {
				obj * volatile * my_free_list = free_list + freeList_index(bytes_left);
				((obj*)start_free)->free_list_link = *my_free_list;
				*my_free_list = (obj*)start_free;
			}

			//扩充内存池
			size_t bytes_to_get = 2 * total_bytes + round_up(heap_size >> 4);
			start_free = (char*)malloc(bytes_to_get);

			obj* volatile * my_free_list = nullptr;
			obj* p = nullptr;

			if (nullptr == start_free) {//malloc失败，那么从自己的自由链表中看看有没有合适的
				int i = 0;

				for (i = size; i < __MAX_BYTES; i += __ALIGN) {
					my_free_list = free_list + freeList_index(i);
					p = *my_free_list;
					if (nullptr != p) {
						*my_free_list = p->free_list_link; //把p取出
						start_free = (char*)p;
						end_free = start_free += i;
						return  chunk_alloc(size, nobjs);
					}
				}

			}
			end_free = 0;//山穷水尽
			start_free = (char*)(malloc_alloc::allocate(bytes_to_get));//要么成功，要么异常
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return (chunk_alloc(size, nobjs));
		}
	}




}