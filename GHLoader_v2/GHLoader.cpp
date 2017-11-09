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
	//this function is called from another thread.
	//modifies a few labels and shit, nothing crazy. no need to worry about race conditions right now
	cpProcess = pm.FindProcess(szTarget);
	
	CXLabel * pLabel = pWnd->GetControls()->GetControl<CXLabel>(IDC_SEARCH);
	pLabel->SetText(L"Found process, injecting...");
	pLabel->SetTxtColor(RGB(255, 50, 50));

	pLabel = pWnd->GetControls()->GetControl<CXLabel>(IDC_GAME);
	pLabel->SetTxtColor(RGB(0, 150, 255));

	//write injector binary to disk
	WriteInj();

	//write dll to disk
	WriteDll();
	
	//execute injector
	//there's no real way to get feedback (that i know of) from the injector like this
	//since we're just writing his executable to disk
	//we're stuck to just simply relying on broihons messageboxes :(
	//while sacrificing feedback, we retain the ability of adding an easy to implement update function.
	Inject(); 

	// say good bye
	pLabel = pWnd->GetControls()->GetControl<CXLabel>(IDC_SEARCH);
	pLabel->SetText(L"Hack Loaded!");
	pLabel->SetTxtColor(RGB(50, 230, 50));
	
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(3s);
	
	pLabel->SetText(L"Closing loader... Have fun!");
	pLabel->SetTxtColor(RGB(200, 200, 200));

	std::this_thread::sleep_for(5s);
	ExitProcess(0);
}

GHLFormInfo GHLoader::GHLGetForm()
{
	//we need to load the following for the form.
	// form title
	// game name
	// hack author name
	// additional info that'll be loaded into a text box in another form.
	CResourceReader cr(hInstance);
	ResourceDataVec & vData = cr.ReadIntoVector(IDR_BINARY3, BINARY);
	if (!vData.empty())
		vData.clear();

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
	CResourceWriter rw(hInstance);
	//todo: random file name
	rw.Write(_T("fileName.dll"), IDCHEAT, BINARY);
}

void GHLoader::Inject()
{
	//get proc id and parse it to a string
	DWORD pid = cpProcess.GetPID();
	tstring szPid(22, 0);
	_itot_s(pid, &szPid[0], 22, 10);
	
	tstring szParam = _T("/p ");
	szParam.append(szPid.c_str()); 
	szParam.append(_T(" /f \"fileName.dll\" /m 0 /o 0"));
	ShellExecute(NULL, NULL, _T("inj.exe"), szParam.c_str(), NULL, SW_HIDE);
}
