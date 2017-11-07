#include "GHLMainWindow.h"


GHLMainWindow::GHLMainWindow(HINSTANCE hInstance, GHLFormInfo fi)
	: CXMainWindow(hInstance, fi.szTitle, XMAINWNDCLS, fi.x, fi.y, fi.w, fi.h)
{
	g_pMainWindow = this;
	SetBgColor(fi.clCol);
	if (!Create())
	{
		//error ;P
		exit(-1);
	}

	xfSearch = CXFont(_T("Consolas"), 18);
	//xfSearch.SetWeight(FW_SEMIBOLD);

	xfGameName = CXFont(_T("Agency FB"), 48);
	xfGameName.SetItalic(TRUE);
}

GHLMainWindow::~GHLMainWindow()
{
}

int GHLMainWindow::CreateControls()
{
	CXLabel * pSearching =
		pControls->AddControl<CXLabel>(
			IDC_SEARCH,
			rcRect.left,
			rcRect.top + 10,
			uWidth,
			uHeight / 5,
			_T("Searching for..."),
			&xfSearch);

	CXLabel * pGameName =
		pControls->AddControl<CXLabel>(
			IDC_GAME,
			rcRect.left,
			rcRect.top + 40,
			uWidth,
			uHeight / 5,
			_T("Game Name"),
			&xfGameName);

	pGameName->SetDrawFlags(DT_NOCLIP | DT_CENTER);
	pSearching->SetDrawFlags(DT_NOCLIP | DT_CENTER);
	pSearching->SetTxtColor(RGB(200, 200, 200));
	return 0;
}
