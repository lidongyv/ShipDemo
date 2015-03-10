// MyShip.cpp: implementation of the CMyShip class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShipDemo.h"
#include "MyShip.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageList CMyShip::m_Images;

CMyShip::CMyShip(CPoint ptPos)
{
	m_ptPos = ptPos;
}

CMyShip::~CMyShip()
{

}

bool CMyShip::Draw(CDC *pDC, bool bPause)
{
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return false;
}

BOOL CMyShip::LoadImage()
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_SHIP);

	if(!m_Images.Create(SHIP_WIDTH, SHIP_HEIGHT, ILC_COLOR24|ILC_MASK, 1, 0))
		return FALSE;

	m_Images.Add(&bmp, RGB(255, 0, 255));

	return TRUE;
}

void CMyShip::DeleteImage()
{
	m_Images.DeleteImageList();
}
