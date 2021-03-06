///////////////////////////////////////////////////////
// Mainfrm.h
//  Declaration of the CMainFrame class

#ifndef MAINFRM_H
#define MAINFRM_H


#include "SplitterPanes.h"

#ifndef BTNS_WHOLEDROPDOWN
  #define BTNS_WHOLEDROPDOWN  0x0080
#endif

class CMainFrame : public CFrame
{
public:
	CMainFrame();
	virtual ~CMainFrame();
	CMyListView* GetListView() const {return (CMyListView*)m_RightPane->GetView();}
	CMyTreeView* GetTreeView() const {return (CMyTreeView*)m_LeftPane.GetView();}
	BOOL GetShowHidden() {return m_bShowHidden;}

protected:
	virtual void OnInitialUpdate();
	virtual void OnClose();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnCreate();
	virtual LRESULT OnNotify(WPARAM wParam, LPARAM lParam);
	virtual void SetupToolBar();
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void DoPopupMenu();

private:
	CLeftPane m_LeftPane;
	CRightPane* m_RightPane;
	BOOL m_bShowHidden;
};

#endif  //MAINFRM_H

