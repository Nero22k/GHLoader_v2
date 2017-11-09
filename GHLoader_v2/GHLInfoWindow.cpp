#include "GHLInfoWindow.h"

GHLInfoWindow::GHLInfoWindow(CXWindow * pOwner)
	: CXDialog(pOwner, 1, pOwner->GetPos().x + pOwner->GetWidth(), pOwner->GetPos().y, INFOWND_W, INFOWND_H, _T("Info..."))
{
}

GHLInfoWindow::~GHLInfoWindow()
{
}

void GHLInfoWindow::Show()
{
	if (!bShown)
	{
		if (!hWnd)
		{
			Create();
			CreateControls();
		}
		RECT & rcWindow = pOwnerWindow->GetWndRect();
		SetPos(rcWindow.right - ((rcWindow.right  - rcWindow.left) / 2) - (uWidth / 2), rcWindow.top);
		CXDialog::Show();
	}
}

void GHLInfoWindow::CreateControls()
{
	CXEdit * pEdit = 
		xControls->AddControl<CXEdit>(
			IDC_INFOEDIT, 
			5, 
			5, 
			rcRect.right - 10, 
			rcRect.bottom - 10, 
			L"This is going to be additional info\r\nthat muhfuckas can provide about\r\ntheir bullshit hack.");

	pEdit->SetStyle(WS_XEDITML);
}
