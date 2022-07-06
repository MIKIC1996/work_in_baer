#pragma once
#include "core_defs.h"


typedef int32_t SubCraftIdImpl;
typedef int32_t LocationIdImpl;

//�ӹ����ʵ��
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


//�ӹ��������ߵ�ʵ��
class SunnyTcsSubCraftLinkLineImpl {
public:

};


//����ѡ�õ�ʵ��
typedef SunnyTcsSubCraftImpl			SunnyTcsSubCraft;
typedef SunnyTcsSubCraftLinkLineImpl	SunnyTcsSubCraftLinkLine;

