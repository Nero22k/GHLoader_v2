#pragma once
#include "XGui\XMainWindow.h"

#define IDC_SEARCH 0x8000
#define IDC_GAME 0x8001

struct GHLFormInfo
{
	tstring szTitle;
	int x, y, w, h;
	COLORREF clCol;
};

class GHLMainWindow : public CXMainWindow
{
public:
	GHLMainWindow(HINSTANCE hInstance, GHLFormInfo fi);
	~GHLMainWindow();

	//we'll probably need to pass in some sort of struct
	//with some data to customize per game
	//
	int CreateControls();

private:
	CXFont xfSearch;
	CXFont xfGameName;
};

