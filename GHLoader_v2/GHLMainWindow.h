#pragma once
#include "XGui\XMainWindow.h"
#include "GHLInfoWindow.h"
#include "resource.h"

#define IDC_SEARCH	0x8000
#define IDC_GAME	0x8001
#define IDC_LABEL	0x8002
#define IDB_INFO	0x8003
#define IDC_BANNER	0x8010

#define IDINJ64	IDR_BINARY1
#define IDINJ32	IDR_BINARY2
#define IDCHEAT	IDR_BINARY3


struct GHLFormInfo
{
	tstring szTitle;
	tstring szProcess;
	tstring szAuthor;
	tstring szInfo;
	int x, y, w, h;
	COLORREF clCol;
};

class GHLMainWindow : public CXMainWindow
{
public:
	GHLMainWindow(HINSTANCE hInstance, GHLFormInfo fi);
	~GHLMainWindow();

	//we'll probably need to pass in some sort of struct
	//with some data to customize per build
	int CreateControls();
	CXControls* GetControls();
private:
	GHLInfoWindow * pInfoWnd;
	CXFont xfSearch;
	CXFont xfGameName;
};

