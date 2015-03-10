// Score.h: interface for the CScore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCORE_H__9939D477_C570_11D4_A7CC_EA7F379C1C5F__INCLUDED_)
#define AFX_SCORE_H__9939D477_C570_11D4_A7CC_EA7F379C1C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyObject.h"

class CScore : public CMyObject  
{
public:
	bool Draw(CDC* pDC, bool bPause);
	CScore(CPoint ptPos, int nScore, DWORD nColor);
	virtual ~CScore();

private:
	COLORREF m_nColor;
	int m_nProcess;
	int m_nScore;
};

#endif // !defined(AFX_SCORE_H__9939D477_C570_11D4_A7CC_EA7F379C1C5F__INCLUDED_)
