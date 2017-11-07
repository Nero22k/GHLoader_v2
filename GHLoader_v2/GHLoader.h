#pragma once
#include "GHLMainWindow.h"

class GHLoader
{
public:
	GHLoader(HINSTANCE hInstance);
	~GHLoader();

	bool IsDlgMessage(MSG * pMsg);

private:
	int CreateMainWindow();

public:
	std::vector<CXWindow*> vWindows;
	GHLMainWindow * pWnd;
};

