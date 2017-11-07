#include "GHLoader.h"


//_Form form;

void ProcPickWrap(uintptr_t pVoid)
{
	GHLoader* pApp = (GHLoader*)pVoid;
}

GHLoader::GHLoader(HINSTANCE hInstance)
{
	GHLFormInfo formInfo; //we'll populate this from the resources later but for now...
	formInfo.clCol = RGB(25, 25, 25);
	formInfo.szTitle = L"LoaderStub";
	formInfo.x = 250;
	formInfo.y = 150;
	formInfo.h = 250;
	formInfo.w = 450;
	formInfo.h = 300;

	g_pMainWindow = pWnd = new GHLMainWindow(hInstance, formInfo);
	pWnd->CreateControls();
}


GHLoader::~GHLoader()
{
}

bool GHLoader::IsDlgMessage(MSG * pMsg)
{
	bool bIsDlgMsg = false;
	for (auto p : vWindows)
		bIsDlgMsg = bIsDlgMsg || IsDialogMessage(p->GetHandle(), pMsg);
	return bIsDlgMsg;
}

int GHLoader::CreateMainWindow()
{
	if (!g_pMainWindow->Create())
		return -1;
	return 0;
}
