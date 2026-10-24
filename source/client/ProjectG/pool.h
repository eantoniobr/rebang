#pragma once

#include "wtextureview.h"
#include "wflag.h"

enum eMapType;

class CPool
{
public:
	CPool();
	virtual ~CPool();

	virtual void SetReflection(bool bEnable) = 0;
	virtual void Process(float dt) = 0;
	virtual void Prerender(WView* view) = 0;
	virtual void Render(WView* view) = 0;

	void SetArea(const Waabb& area, const char* option);

	static CPool* CreatePoolByMapType(eMapType type);

protected:
	int m_type;
	Waabb m_area;
	WFlags m_flag;

private:
	virtual void BuildMesh() = 0;
};

class CPoolCaustic : public CPool
{
public:
	CPoolCaustic();
	virtual ~CPoolCaustic();

	virtual void SetReflection(bool bEnable);
	virtual void Process(float dt);
	virtual void Render(WView* view);
	virtual void Prerender(WView* view);

private:
	virtual void BuildMesh();
	void AddLayer(float speedU, float speedV, float scale, unsigned char alpha);

	struct sLayer
	{
		float speedU;
		float speedV;
		WTVertex* vl[5];
		WTVertex vtx[4];
		int texHandle;

		sLayer() { texHandle = 0; }

		~sLayer();
	};

	Waabb m_causticArea;
	WVector m_corner[4];
	sLayer m_layer[3];
	int m_layerNum;
};

class CPoolReflective : public CPool
{
public:
	CPoolReflective();
	virtual ~CPoolReflective();

	virtual void SetReflection(bool bEnable);
	virtual void Process(float dt);
	virtual void Prerender(WView* view);
	virtual void Render(WView* view);

private:
	virtual void BuildMesh();
	void ExcludePoint();
	void MakeNorm();
	void Wave(float dt);
	void Droplet();

	struct sWaveVertex
	{
		WVector pos;
		WVector normal;
		float force;
		float speed;
		float tu;
		float tv;
		bool bWater;
	};

	int m_gridX;
	int m_gridZ;
	sWaveVertex** m_grid;
	unsigned long m_dropTime;
	WTVertex* m_vl[5];
	WTVertex m_vtx[4];
	WTextureView* m_pReflectView;
};
