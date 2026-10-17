#pragma once

#include <list>

#include "polysoup.h"

#include "../../shared/globalgamedefine.h"

class cModel
{
public:
	cModel();
	~cModel();

	void SetPosition(const WVector& pos);
	void SetRotate(float angle);
	void Apply_ChangeModelData();
	void OBBToAABB();

	int m_nState;
	sFurniture_List* m_pFurniture;
	WPolySoup::sModel* m_pModel;
	float m_fRotate;
	int m_nWallIndex;
};
