#ifndef _OPEN_FILE_DIALOG_H_H_
#define _OPEN_FILE_DIALOG_H_H_

#include "Win32.h"

class OpenFileDialog
{
public:
	static OpenFileDialog* getInstance();

	/*
	函数功能:打开一个"打开对话框"
	返回值:如果打开文件成功,返回真,否则返回假
	说明:打开成功后可以通过其他函数获取文件路径和文件名
	*/
	bool Open();

	// 获得文件的绝对路径
	string GetAbsolutePath() const;

	// 获得文件名
	string GetFileName() const;

	// 释放内存,delete自身
	void Release();

private:
	OpenFileDialog()
	: _absolutePath("")
	, _filename("")
	{}

	OpenFileDialog(OpenFileDialog&);
	OpenFileDialog& operator=(OpenFileDialog&);

private:
	string _absolutePath;
	string _filename;

};

#endif