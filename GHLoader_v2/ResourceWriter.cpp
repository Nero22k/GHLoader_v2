#include "ResourceWriter.h"

CResourceWriter::CResourceWriter(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
}


CResourceWriter::~CResourceWriter()
{
}

size_t CResourceWriter::Write(tstring szFilename, DWORD dwID, DWORD dwType)
{
	hRsrc = FindResource(hInstance, MAKEINTRESOURCE(dwID), MAKEINTRESOURCE(dwType));
	if (!hRsrc)
		return 0;

	hGlobal = LoadResource(hInstance, hRsrc);
	if (!hGlobal)
		return 0;

	size = SizeofResource(hInstance, hRsrc);
	pResource = LockResource(hGlobal);
	hFile = CreateFile(szFilename.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile)
	{
		DWORD outSize = 0;
		WriteFile(hFile, pResource, size, &outSize, nullptr);
		CloseHandle(hFile);
		return outSize;
	}
	return 0;
}
