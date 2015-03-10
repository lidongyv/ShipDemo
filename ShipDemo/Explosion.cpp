// Explosion.cpp: implementation of the CExplosion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShipDemo.h"
#include "Explosion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageList CExplosion::m_Images;

CExplosion::CExplosion(CPoint ptPos)
{
	m_ptPos = ptPos;
	m_nProcess = 0;
}

CExplosion::~CExplosion()
{

}

bool CExplosion::Draw(CDC *pDC, bool bPause)
{
	m_Images.Draw(pDC, m_nProcess, m_ptPos, ILD_TRANSPARENT);
	
	if(bPause)
		return false;

	return m_nProcess++ > 15 ? true : false;
}

BOOL CExplosion::LoadImage()
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_EXPLOSION);

	if(!m_Images.Create(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, ILC_COLOR24|ILC_MASK, 15, 0))
		return FALSE;

	m_Images.Add(&bmp, RGB(255, 0, 255));

	return TRUE;
}

void CExplosion::DeleteImage()
{
	m_Images.DeleteImageList();
}
