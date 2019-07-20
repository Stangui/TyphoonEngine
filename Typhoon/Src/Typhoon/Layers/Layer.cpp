#include "TyphoonPCH.h"
#include "Layer.h"


namespace TyphoonEngine
{

	////---------------------------------------------////
	Layer::Layer(const std::string& name, bool bEnable) :
		 m_name(name)
		,m_bEnabled(bEnable)
	{
	}

	////---------------------------------------------////
	Layer::~Layer()
	{
	}

}