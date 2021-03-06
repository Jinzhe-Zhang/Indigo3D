
// OPENGL_MFC.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "OPENGL_MFC.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "OPENGL_MFCDoc.h"
#include "OPENGL_MFCView.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COPENGLMFCApp

BEGIN_MESSAGE_MAP(COPENGLMFCApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &COPENGLMFCApp::OnAppAbout)
	ON_COMMAND(ID_32774, &COPENGLMFCApp::OnCreateCube)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// COPENGLMFCApp 构造

COPENGLMFCApp::COPENGLMFCApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("OPENGLMFC.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 COPENGLMFCApp 对象

COPENGLMFCApp theApp;


// COPENGLMFCApp 初始化

BOOL COPENGLMFCApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_OPENGLMFCTYPE,
		RUNTIME_CLASS(COPENGLMFCDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(COPENGLMFCView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int COPENGLMFCApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// COPENGLMFCApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void On32773();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_KEYDOWN()
//ON_COMMAND(ID_32773, &CAboutDlg::On32773)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void COPENGLMFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// COPENGLMFCApp 消息处理程序





//void CAboutDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}


/*
void CAboutDlg::On32773()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg createcube;
	createcube.DoModal();

}
*/





//-------------------------------------------------------------



CCreate::CCreate() : CDialogEx(IDD_DIALOG1)
, xc(0)
, yc(0)
, zc(0)
{
}

void CCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, xc);
	DDX_Text(pDX, IDC_EDIT2, yc);
	DDX_Text(pDX, IDC_EDIT3, zc);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_EDIT3, edit3);
}

BEGIN_MESSAGE_MAP(CCreate, CDialogEx)
	//	ON_WM_KEYDOWN()
	//ON_COMMAND(ID_32773, &CCreate::On32773)
	//ON_COMMAND(ID_32774, &CCreate::OnCreateCube)

	ON_BN_CLICKED(IDOK, &CCreate::OnBnClickedOk)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
//void COPENGLMFCApp::OnCreateCube()
//{
//	CCreate createcube;
//	createcube.DoModal();
//}

void COPENGLMFCApp::OnCreateCube()
{
	// TODO: 在此添加命令处理程序代码
		CCreate createcube;
		createcube.DoModal();
}


float xxxx(float x11)
{
	return x11;
}
float yyyy(float y11)
{
	return y11;
}
float zzzz(float z11)
{
	return z11;
}


float CCreate::ccx = CCreate::ccx;
float CCreate::ccy = CCreate::ccx;
float CCreate::ccz = CCreate::ccx;







void CCreate::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	ccx = xc;
	ccy = yc;
	ccz = zc;
	CDialogEx::OnOK();
	int value1;//定义中间变量
			  //获取m_edit1变量对应Edit Control中的数值

	UpdateData(TRUE);
	value1 = xc;
	//将str的数值显示到m_edit2变量对应Edit Control中
	ccx = value1;
	//UpdateData(FALSE);

	int value2;//定义中间变量
			   //获取m_edit1变量对应Edit Control中的数值

	UpdateData(TRUE);
	value2 = yc;
	//将str的数值显示到m_edit2变量对应Edit Control中
	ccy = value2;
	//UpdateData(FALSE);

	int value3;//定义中间变量
			   //获取m_edit1变量对应Edit Control中的数值

	UpdateData(TRUE);
	value3 = zc;
	//将str的数值显示到m_edit2变量对应Edit Control中
	ccz = value3;
	//UpdateData(FALSE);
}
