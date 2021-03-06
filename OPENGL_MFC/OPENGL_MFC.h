
// OPENGL_MFC.h: OPENGL_MFC 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "afxwin.h"


// COPENGLMFCApp:
// 有关此类的实现，请参阅 OPENGL_MFC.cpp
//


class COPENGLMFCApp : public CWinApp
{
public:
	COPENGLMFCApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	afx_msg void OnCreateCube();
	DECLARE_MESSAGE_MAP()
};

extern COPENGLMFCApp theApp;


class CCreate : public CDialogEx
{

	friend class COPENGLMFCView;
//	COPENGLMFCView cov;

public:

	static float ccx;
	static float ccy;
	static float ccz;
	CCreate();


	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

														// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void On32773();
	//afx_msg void OnCreateCube();
	//CButton x;

	float xc;
	float yc;
	float zc;
//	afx_msg void OnBnClickedOk();
	CEdit edit1;
	CEdit edit2;
	CEdit edit3;
	afx_msg void OnBnClickedOk();
};
