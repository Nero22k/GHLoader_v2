#pragma once
#include "stdafx.h"

//little resource manager
//should update resources in a binary
//should be able to read resource from a binary or process handle

class CResource
{
public:
	CResource(int resID, int resType, std::vector<byte> vResource);
	BOOL Update(HANDLE hUpdate);
	int GetID();
	int GetType();

private:
	HANDLE hUpdate;
	int resID;
	int resType;
	std::vector<byte> vResource;
};

class CResourceManager
{
	HANDLE hUpdate;
	std::vector<CResource*> vResources;

public:
	CResourceManager();
	CResourceManager(std::vector<CResource*> vResources);
	~CResourceManager();

	// Update resources in a binary
	HANDLE BeginUpdate(tstring szFilePath);
	void AddResource(CResource * res);
	BOOL UpdateResources();
};

