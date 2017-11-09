#include "GHLoader.h"

void LoaderCallback(GHLoader* ghLoader)
{
	ghLoader->LoadCheat();
}

GHLoader::GHLoader(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
	// create main window object and load form info from resource.
	pWnd = new GHLMainWindow(hInstance, GHLGetForm());
	pWnd->CreateControls();

	//should probably start looking for the process we're interested in
	//we'll also need to load this info from resource file.
	//along with the dll we'll be injecting.
	szTarget = L"hl2.exe";
	thLoad = std::thread(LoaderCallback, this);
	thLoad.detach();
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

void GHLoader::LoadCheat()
{
	cpProcess = pm.FindProcess(szTarget);
	
	CXLabel * pLabel = pWnd->GetControls()->GetControl<CXLabel>(IDC_SEARCH);
	pLabel->SetText(L"Found process, injecting...");
	pLabel->SetTxtColor(RGB(255, 50, 50));

	pLabel = pWnd->GetControls()->GetControl<CXLabel>(IDC_GAME);
	pLabel->SetTxtColor(RGB(0, 150, 255));
	WriteInj();
	//write dll
	CResourceWriter rw(hInstance);
	rw.Write(_T("fileName.dll"), IDCHEAT, BINARY);
	//execute injector

	DWORD pid = cpProcess.GetPID();
	tstring szPid(22, 0);
#ifdef _UNICODE
	_itow_s(pid, &szPid[0], 22, 10);
#else
	_itoa_s(pid, &szPid[0], 22, 10);
#endif 
	szPid.resize(szPid.length());
	tstring szParam = _T("/p ");
	szParam.append(szPid.c_str());
	szParam.append(_T(" /f \"fileName.dll\" /m 0 /o 0"));
	ShellExecute(NULL, NULL, _T("inj.exe"), szParam.c_str(), NULL, SW_HIDE);

	pLabel = pWnd->GetControls()->GetControl<CXLabel>(IDC_SEARCH);
	pLabel->SetText(L"Hack Loaded!");
	pLabel->SetTxtColor(RGB(50, 230, 50));
}

GHLFormInfo GHLoader::GHLGetForm()
{
	//we need to load the following for the form.
	// form title
	// game name
	// hack author name
	// additional info that'll be loaded into a text box in another form.

	GHLFormInfo formInfo; //we'll populate this from the resources later but for now...
	formInfo.clCol = RGB(25, 25, 25);
	formInfo.szTitle = L"LoaderStub";
	formInfo.x = 250;
	formInfo.y = 150;
	formInfo.h = 250;
	formInfo.w = 400;
	formInfo.h = 300;
	return formInfo;
}

void GHLoader::WriteInj()
{
	CResourceWriter rw(hInstance);
#define _inj _T("inj.exe")
#ifdef _WIN64
	rw.Write(_inj, IDINJ64, BINARY);
#else
	rw.Write(_inj, IDINJ32, BINARY);
#endif // !win32
}

void GHLoader::WriteDll()
{
}
