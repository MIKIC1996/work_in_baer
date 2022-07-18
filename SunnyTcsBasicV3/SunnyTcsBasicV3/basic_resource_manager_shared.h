#pragma once
#include "basic_resource_manager.h"




template<typename Ty,
	template<typename>class Trait = SunnyTcsTypeTraits,
	template<typename>class Policy = SunnyTcsResourceManagePolicy>
class SunnyTcsSharedPtrResourceManager {
public:
	typedef Ty													ResourceType;
	typedef Trait<ResourceType>									TraitType;
	typedef Policy<ResourceType>								PolicyType;
	typedef SunnyTcsSharedPtrResourceManager<Ty, Trait, Policy> Self;

	class FunctorRaII {
	public:
		explicit FunctorRaII(Self* parent) :m_parent(parent) {}
		FunctorRaII(FunctorRaII const&) = default;
		FunctorRaII& operator=(FunctorRaII const&) = default;
		~FunctorRaII() {}

		void operator()(ResourceType* ptr) {
			if (m_parent) {
				std::lock_guard<std::mutex> lk(m_parent->m_lock);
				ResourceType& currval = *ptr;
				std::equal_to<ResourceType> equalFuncion;
				auto iter = std::find_if(m_parent->m_used.begin(), m_parent->m_used.end(),
					[&currval, &equalFuncion](ResourceType const& val)->bool {return equalFuncion(currval, val); });
				assert(iter != m_parent->m_used.end());
				m_parent->m_used.erase(iter);
			}
			delete ptr;
		}
	private:
		Self* m_parent;
	};

	friend class FunctorRaII;

	//keeper
	class SunnyTcsSharedResourceKeeper {
	public:
		typedef  ResourceType ResourceType;
		friend class Self;

		//copy ctor
		SunnyTcsSharedResourceKeeper(SunnyTcsSharedResourceKeeper const& var)
			:m_res(var.m_res)
		{}

		SunnyTcsSharedResourceKeeper& operator=(SunnyTcsSharedPtrResourceManager const& var) {
			m_res = var.m_res;
		}

		//dector
		virtual ~SunnyTcsSharedResourceKeeper() {

		}

		//api
		ResourceType getValue()const {
			return *m_res;
		}

		inline void reset() {
			m_res.reset();
		}

		bool isNull()const {
			return !(bool)m_res;
		}

		operator bool()const {
			return (bool)m_res;
		}

	private:
		//ctor
		template<typename DectorFunctor>
		SunnyTcsSharedResourceKeeper(ResourceType const& var, DectorFunctor&& func)
			:m_res(nullptr)
		{
			m_res = std::make_shared<ResourceType>(var, std::forward<DectorFunctor>(func));
		}


		template<typename DectorFunctor>
		SunnyTcsSharedResourceKeeper(ResourceType* ptr, DectorFunctor&& func)
			:m_res(ptr, std::forward<DectorFunctor>(func))
		{}

	private:
		std::shared_ptr<ResourceType> m_res;
	};

	class SunnyTcsUniqueResourceKeeper {
	public:
		typedef  ResourceType ResourceType;
		friend class Self;

		//move ctor
		SunnyTcsUniqueResourceKeeper(SunnyTcsUniqueResourceKeeper&& var)
			:m_res(std::move(var.m_res))
		{}

		SunnyTcsUniqueResourceKeeper& operator=(SunnyTcsUniqueResourceKeeper&& var) {
			m_res = std::move(var.m_res);
			return *this;
		}

		//dector
		virtual ~SunnyTcsUniqueResourceKeeper() {}


		ResourceType getValue()const {
			return *m_res;
		}

		bool isNull()const {
			return !(bool)m_res;
		}

		operator bool()const {
			return (bool)m_res;
		}

	private:
		//ctor
		SunnyTcsUniqueResourceKeeper(ResourceType const& var, FunctorRaII const& func)
			:m_res(nullptr)
		{
			m_res = std::make_unique<ResourceType, FunctorRaII>(var, func);
		}



		SunnyTcsUniqueResourceKeeper(ResourceType* ptr, FunctorRaII const& func)
			:m_res(ptr, func)
		{

		}

	private:
		std::unique_ptr<ResourceType, FunctorRaII> m_res;
	};

	typedef SunnyTcsSharedResourceKeeper			SharedResource;
	typedef SunnyTcsUniqueResourceKeeper			UniqueResource;

	//ctor
	explicit SunnyTcsSharedPtrResourceManager(bool enableDefVal = true)
		:m_used(), m_lock()
	{
		if(!enableDefVal) //如果默认值不有效
			m_used.push_back(TraitType::getDefaultValue());
	}

	//copy ctor
	SunnyTcsSharedPtrResourceManager(SunnyTcsSharedPtrResourceManager const& var)
		:m_used(), m_lock()
	{
		std::lock_guard<std::mutex> lk(var.m_lock);
		m_used = var.m_used;
	}

	//dector
	virtual ~SunnyTcsSharedPtrResourceManager() {}

	//assign
	SunnyTcsSharedPtrResourceManager& operator=(SunnyTcsSharedPtrResourceManager const& var) = delete;

	//已使用的资源数量
	std::size_t usedCount()const { return m_used.count(); }

	//获取下一个资源
	SharedResource getNextSharedResource() {
		std::lock_guard<std::mutex> lk(m_lock);
		ResourceType&& currentVal = TraitType::getDefaultValue();
		std::equal_to<ResourceType> equalFunc;
		while (m_used.end() != std::find_if(m_used.begin(), m_used.end(),
			[&currentVal, &equalFunc](ResourceType const& val)->bool {return equalFunc(val, currentVal); })) {
			currentVal = PolicyType::getNextResource(currentVal);
		}
		m_used.push_back(currentVal);
		return SharedResource(new ResourceType(currentVal), FunctorRaII(this));
	}


	UniqueResource getNextUniqueResource() {
		std::lock_guard<std::mutex> lk(m_lock);
		ResourceType&& currentVal = TraitType::getDefaultValue();
		std::equal_to<ResourceType> equalFunc;
		while (m_used.end() != std::find_if(m_used.begin(), m_used.end(),
			[&currentVal, &equalFunc](ResourceType const& val)->bool {return equalFunc(val, currentVal); })) {
			currentVal = PolicyType::getNextResource(currentVal);
		}
		m_used.push_back(currentVal);
		return UniqueResource(new ResourceType(currentVal), FunctorRaII(this));
	}


	//获取指定的资源
	SharedResource getDesignatedSharedResource(ResourceType const& var) {
		std::lock_guard<std::mutex> lk(m_lock);
		if (std::find(m_used.begin(), m_used.end(), var) != m_used.end())
			return SharedResource(nullptr, FunctorRaII(nullptr));
		else {
			m_used.push_back(var);
			return  SharedResource(new ResourceType(var), FunctorRaII(this));
		}
	}

	UniqueResource getDesignatedUniqueResource(ResourceType const& var) {
		std::lock_guard<std::mutex> lk(m_lock);
		if (std::find(m_used.begin(), m_used.end(), var) != m_used.end())
			return UniqueResource(nullptr, FunctorRaII(nullptr));
		else {
			m_used.push_back(var);
			return  UniqueResource(new ResourceType(var), FunctorRaII(this));
		}
	}

	//获取一个无效的 shared资源
	inline SharedResource getInvaildSharedResource()const {
		return SharedResource(nullptr, FunctorRaII(nullptr));
	}

	inline UniqueResource getInvaildUniqueResource()const {
		return UniqueResource(nullptr, FunctorRaII(nullptr));
	}

	//获取一个无效的 unique资源


#ifdef  STRICT_INTERFACE_CHECK
	TCS_RESOURCE_MANAGER_INTERFACE_CHECK(Self)
#endif //  STRICT_INTERFACE_CHECK


private:
	std::vector<ResourceType> m_used;
	std::mutex m_lock;
};