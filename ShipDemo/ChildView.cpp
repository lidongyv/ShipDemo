// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "ShipDemo.h"
#include "ChildView.h"

#include "Explosion.h"
#include "MyObject.h"
#include "Score.h"
#include "MyShip.h"
#include "Submarine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SHIP_VERT_POS		20
#define SKY_COLOR			RGB(0, 255, 255)
#define SEA_COLOR			RGB(0, 128, 255)
/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
// load image list;
	CExplosion::LoadImage();
	CMyShip::LoadImage();
	CSubmarine::LoadImage();

// create my ship object, this is the 1st object in object list
	m_Objects.AddTail(new CMyShip(CPoint((GAME_WIDTH-SHIP_WIDTH)/2, SHIP_VERT_POS)));

	m_bGamePause = false;
}

CChildView::~CChildView()
{
// free memory

// delete all objects
	POSITION pos = m_Objects.GetHeadPosition();

	while(pos!=NULL)
	{
		delete m_Objects.GetNext(pos);
	}
	m_Objects.RemoveAll();

// clear image lists
	CExplosion::DeleteImage();
	CMyShip::DeleteImage();
	CSubmarine::DeleteImage();
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_GAMEPAUSE, OnGamepause)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

//	cs.dwExStyle |= WS_EX_CLIENTEDGE;  // I remove this line
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

// repaint window so easily
	dc.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_VirtualDC, 0, 0, SRCCOPY);

	// Do not call CWnd::OnPaint() for painting messages
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

// create virtual back buffer 
	CClientDC dc(this);
	m_VirtualBitmap.CreateCompatibleBitmap(&dc, GAME_WIDTH, GAME_HEIGHT);
	m_VirtualDC.CreateCompatibleDC(&dc);
	m_VirtualDC.SelectObject(&m_VirtualBitmap);

// create loop
	SetTimer(100, 30, NULL);
	return 0;
}

void CChildView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static int nCreator = random(50) + 20;
	CClientDC dc(this);

	if(m_bGamePause)
		return;
// create new sub
	if(nCreator==0)
	{
		m_Objects.AddTail(new CSubmarine(random(2)%2?true:false, random(GAME_HEIGHT-SHIP_VERT_POS-SHIP_HEIGHT*2-30)+SHIP_VERT_POS+SHIP_HEIGHT+30, random(4), random(4)+3));
		nCreator = random(50) + 10;
	}

// Draw sky and see
	m_VirtualDC.FillSolidRect(0, 0, GAME_WIDTH, SHIP_VERT_POS+SHIP_HEIGHT-5, SKY_COLOR);
	m_VirtualDC.FillSolidRect(0, SHIP_VERT_POS+SHIP_HEIGHT-5, GAME_WIDTH, GAME_HEIGHT, SEA_COLOR);

// Draw all objects on the virtual dc, Be careful using "POSITION"
	POSITION pos1, pos2;
	CObject* pLastObj;

	for(pos1=m_Objects.GetHeadPosition(); (pos2=pos1)!=NULL;)
   	{
		if(((CMyObject*)m_Objects.GetNext(pos1))->Draw(&m_VirtualDC, m_bGamePause))  // object terminated
		{
			pLastObj = m_Objects.GetAt(pos2);  // save for deletion
			m_Objects.RemoveAt(pos2);
			delete pLastObj;
		}
	}
// sample: calculate objects numbers
	m_VirtualDC.SetBkMode(TRANSPARENT);
	m_VirtualDC.SetTextColor(RGB(255, 0, 0));
	CString string;
	string.Format("Total objects: %d", m_Objects.GetCount());
	m_VirtualDC.TextOut(10, 10, string);

// sample: a simply message, cos we finally draw it, it'll above all objects
	m_VirtualDC.SetTextAlign(TA_CENTER);
	m_VirtualDC.TextOut(GAME_WIDTH/2, GAME_HEIGHT/2, "Click submarine to kill it");

// restore old text align
	m_VirtualDC.SetTextAlign(TA_LEFT);
// blt the virtual dc on client dc
	dc.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_VirtualDC, 0, 0, SRCCOPY);

	nCreator--;

//	CWnd ::OnTimer(nIDEvent);  // no use, safely remove it
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	POSITION pos1, pos2;
	CSubmarine* pSub;

// check all objects to find out enemy
	for(pos1=m_Objects.GetHeadPosition(); (pos2=pos1)!=NULL;)
   	{
		if(((CMyObject*)m_Objects.GetNext(pos1))->IsEnemy())  // object is a submarine
		{
			pSub = (CSubmarine*)m_Objects.GetAt(pos2);  // save for deletion
			if(pSub->GetRect().PtInRect(point))
			{
				// here we first create explosion object to make score always above that explosion
				m_Objects.AddTail(new CExplosion(pSub->GetPos()));
				m_Objects.AddTail(new CScore(pSub->GetPos(), pSub->GetType()+1, RGB(random(255), random(255), random(255))));
				m_Objects.RemoveAt(pos2);
				delete pSub;
			}
		}
	}
	
//	CWnd ::OnLButtonDown(nFlags, point);
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bGamePause)
		return;

	CMyShip* pShip = (CMyShip*)m_Objects.GetHead(); // remember that our ship is the first object in object list

	if(nChar==VK_LEFT)       // turn left
	{
		if(pShip->GetPos().x>0)
			pShip->SetPos(pShip->GetPos().x-5, pShip->GetPos().y);
		return;
	}
	else if(nChar==VK_RIGHT) // turn right
	{
		if(pShip->GetPos().x<GAME_WIDTH-SHIP_WIDTH)
			pShip->SetPos(pShip->GetPos().x+5, pShip->GetPos().y);
		return;
	}

//	CWnd ::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::OnDestroy() 
{
	CWnd ::OnDestroy();
	
	// TODO: Add your message handler code here
	KillTimer(100);
}

void CChildView::OnGamepause() 
{
	// TODO: Add your command handler code here
	m_bGamePause = !m_bGamePause;  // toggle pause status
	CString strTitle;
	strTitle.LoadString(AFX_IDS_APP_TITLE);
	AfxGetMainWnd()->SetWindowText(m_bGamePause ? strTitle+_T(" - ÔÝÍ£") : strTitle);
}
