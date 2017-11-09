#pragma once
#include <stdafx.h>

class CResourceWriter
{
public:
	CResourceWriter(HINSTANCE hInstance);
	~CResourceWriter();
	size_t Write(tstring szFilename, DWORD dwID, DWORD dwType);
private:
	HINSTANCE hInstance;
	HRSRC hRsrc = NULL;
	HGLOBAL hGlobal = NULL;
	size_t size = 0;
	void* pResource = nullptr;
	HANDLE hFile = NULL;
};

