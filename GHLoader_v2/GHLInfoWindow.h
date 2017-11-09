#pragma once
#include "XGui\XDialog.h"
#include "XGui\XControls.h"
#define INFOWND_W 300
#define INFOWND_H 300

#define IDC_INFOEDIT 0x8000

class GHLInfoWindow : public CXDialog
{
public:
	GHLInfoWindow(CXWindow * pOwner);
	~GHLInfoWindow();
	virtual void Show();
private:
	void CreateControls();

private:
	
};

