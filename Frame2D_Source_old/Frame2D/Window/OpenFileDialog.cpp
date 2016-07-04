#include "OpenFileDialog.h"
#include "WindowManager.h"

static OpenFileDialog* pInstance = 0;

OpenFileDialog* OpenFileDialog::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new OpenFileDialog();
	}

	return pInstance;
}

bool OpenFileDialog::Open()
{
	char absolutePath[256];
	char fileName[256];
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	//需要兼容UNICODE处理
	ofn.Flags = OFN_EXPLORER;
	ofn.hwndOwner = WindowManager::getInstance()->getHWND();
	ofn.lpstrFile = absolutePath;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFileTitle = fileName;
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.nMaxFile = 256;
	ofn.nMaxFileTitle = 256;

	char savePath[256];
	GetCurrentDirectory(256, savePath);
	if (GetOpenFileName(&ofn))
	{
		_absolutePath = absolutePath;
		_filename = fileName;
		SetCurrentDirectory(savePath);
		return true;
	}
	else
	{
		return false;
	}
}

string OpenFileDialog::GetAbsolutePath() const
{
	return _absolutePath;
}

string OpenFileDialog::GetFileName() const
{
	return _filename;
}

void OpenFileDialog::Release()
{
	delete this;
	pInstance = 0;
}
