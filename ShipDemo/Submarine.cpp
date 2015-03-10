// Submarine.cpp: implementation of the CSubmarine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShipDemo.h"
#include "Submarine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageList CSubmarine::m_Images;

CSubmarine::CSubmarine(bool bDir, int nVert, int nType, int nSpeed)
{
	m_bDirect = bDir;
	m_ptPos.x = m_bDirect ? GAME_WIDTH : -SUBMARINE_WIDTH;
	m_ptPos.y = nVert;
	m_nType = nType;
	m_nSpeed = nSpeed;
	m_bEnemy = true;
}

CSubmarine::~CSubmarine()
{

}

bool CSubmarine::Draw(CDC *pDC, bool bPause)
{
	m_Images.Draw(pDC, m_nType*2+(m_bDirect?0:1), m_ptPos, ILD_TRANSPARENT);
	if(bPause)
		return false;

	if(m_bDirect)
	{
		m_ptPos.x -= m_nSpeed;
		if(m_ptPos.x<-SUBMARINE_WIDTH)
			return true;		
	}
	else
	{
		m_ptPos.x += m_nSpeed;
		if(m_ptPos.x>GAME_WIDTH)
			return true;
	}
	
	return false;
}

BOOL CSubmarine::LoadImage()
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_SUBMARINE);

	if(!m_Images.Create(SUBMARINE_WIDTH, SUBMARINE_HEIGHT, ILC_COLOR24|ILC_MASK, 8, 0))
		return FALSE;

	m_Images.Add(&bmp, RGB(255, 0, 255));

	return TRUE;
}

void CSubmarine::DeleteImage()
{
	m_Images.DeleteImageList();
}
