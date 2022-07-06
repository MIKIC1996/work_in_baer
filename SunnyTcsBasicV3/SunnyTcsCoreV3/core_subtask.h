#pragma once

#include "core_craft.h"
#include "core_action.h"

//всхннЯ
class SunnyTcsSubTaskImpl :public std::vector<SunnyTcsAction>
{
public:
	typedef typename SunnyTcsSubCraft::SubCraftId					SubTaskId;
	typedef typename SunnyTcsTypeTraits<SubTaskId>::TransferedType	SubTaskIdTransferedType;

	//ctor
	SunnyTcsSubTaskImpl():m_id(SunnyTcsTypeTraits<SubTaskId>::getDefaultValue()){}
	explicit SunnyTcsSubTaskImpl(SubTaskIdTransferedType idvar):m_id(idvar){}
	SunnyTcsSubTaskImpl(SunnyTcsSubTaskImpl const& var) = default;
	//dector
	virtual ~SunnyTcsSubTaskImpl(){}

	inline SubTaskId getId()const { return m_id; }
	inline void setId(SubTaskIdTransferedType var) { m_id = var; }
private:
	SubTaskId m_id;

};


typedef SunnyTcsSubCraftImpl SunnyTcsSubTask;