#pragma once
#include "GHLMainWindow.h"
#include "ProcManager.h"
#include "ResourceWriter.h"
class GHLoader
{
public:
	GHLoader(HINSTANCE hInstance);
	~GHLoader();

	bool IsDlgMessage(MSG * pMsg);
	void LoadCheat();

private:
	GHLFormInfo GHLGetForm();
	void WriteInj();
	void WriteDll();
public:
private:
	std::vector<CXWindow*> vWindows;
	HINSTANCE hInstance;
	GHLMainWindow * pWnd;
	GHLFormInfo formInfo;
	
	ProcManager pm;
	std::thread thLoad;
	tstring szTarget;
	CProcess cpProcess;
};

