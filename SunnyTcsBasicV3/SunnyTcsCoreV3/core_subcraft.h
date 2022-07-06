#pragma once
#include "core_defs.h"


typedef int32_t SubCraftIdImpl;
typedef int32_t LocationIdImpl;

//子工序的实现
class SunnyTcsSubCraftImpl :public std::list<LocationIdImpl>
{
public:
	typedef SubCraftIdImpl									SubCraftId;
	typedef LocationIdImpl									LocationId;
	typedef SunnyTcsTypeTraits<SubCraftId>::TransferedType	SubCraftIdTransferedType;
	typedef SunnyTcsTypeTraits<LocationId>::TransferedType	LocationIdTransferedType;

	//ctor
	SunnyTcsSubCraftImpl():m_id(SunnyTcsTypeTraits<SubCraftId>::getDefaultValue()),m_runCondition(){}
	explicit SunnyTcsSubCraftImpl(SubCraftIdTransferedType idvar):m_id(idvar),m_runCondition(){}
	SunnyTcsSubCraftImpl(SunnyTcsSubCraftImpl const&) = default;
	//dector
	virtual ~SunnyTcsSubCraftImpl(){}

	SubCraftId getId()const { return m_id; }
	void setId(SubCraftIdTransferedType var) { m_id = var; }
	std::string getRunCondition()const { return m_runCondition; }
	void setRunCondition(std::string const& condition) { m_runCondition = condition; }

private:
	SubCraftId m_id;
	std::string m_runCondition;
};


//子工序连接线的实现
class SunnyTcsSubCraftLinkLineImpl {
public:

};


//决定选用的实现
typedef SunnyTcsSubCraftImpl			SunnyTcsSubCraft;
typedef SunnyTcsSubCraftLinkLineImpl	SunnyTcsSubCraftLinkLine;

