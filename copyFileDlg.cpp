
// copyFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "copyFile.h"
#include "copyFileDlg.h"
#include "afxdialogex.h"


#include <direct.h>
#include <string>
#include <direct.h>
#include <fstream>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcopyFileDlg 对话框



CcopyFileDlg::CcopyFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COPYFILE_DIALOG, pParent)
	, m_dest(_T(""))
	, m_source(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcopyFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEST, m_dest);
	DDX_Text(pDX, IDC_EDIT_SOURCE, m_source);
	DDX_Control(pDX, IDC_LIST_SHOW, m_show);
}

BEGIN_MESSAGE_MAP(CcopyFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SOURCE, &CcopyFileDlg::OnBnClickedButtonSource)
	ON_BN_CLICKED(IDC_BUTTON_DEST, &CcopyFileDlg::OnBnClickedButtonDest)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &CcopyFileDlg::OnBnClickedButtonCopy)
END_MESSAGE_MAP()


// CcopyFileDlg 消息处理程序

BOOL CcopyFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	UpdateData();
	char buff[256];
	_getcwd(buff, 255);
	m_source=buff;
	m_dest = "D:\\AutoMachine";
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcopyFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcopyFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcopyFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcopyFileDlg::OnBnClickedButtonSource()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR servPath[MAX_PATH];
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = servPath;
	bi.lpszTitle = _T("选择需要目的文件路径");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	if ((pidl = SHBrowseForFolder(&bi)) != NULL)
	{
		if (SUCCEEDED(SHGetPathFromIDList(pidl, servPath))) //得到文件夹的全路径，不要的话，只得本文件夹名  
		{
			UpdateData();
			m_source = servPath;
			UpdateData(false);
			//SetDlgItemText(IDC_EDIT_SOURCE, servPath);
		}
	}
}


void CcopyFileDlg::OnBnClickedButtonDest()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR servPath[MAX_PATH];
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = servPath;
	bi.lpszTitle = _T("选择需要复制的文件路径");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	if ((pidl = SHBrowseForFolder(&bi)) != NULL)
	{
		if (SUCCEEDED(SHGetPathFromIDList(pidl, servPath))) //得到文件夹的全路径，不要的话，只得本文件夹名  
		{
			UpdateData();
			m_dest = servPath;
			UpdateData(false);
			//SetDlgItemText(IDC_EDIT_SOURCE, servPath);
		}
	}
}


int CcopyFileDlg::copyDir(char * source, char * dest)
{
	char sourcePath[128];
	char tempSourcePath[128];
	char tempDestPath[128];
	struct _finddata_t  finddata;
	if (_access(source, 0) == -1)
	{
		//printf("can't find the source dir");
		CString t(source);
		MessageBox(t);
		return -1;
	}
	if (_access(dest, 0) == -1) //判断目标文件夹是否存在，不存在就创建
	{
		//create dest dir
		if (_mkdir(dest) == -1)
		{
			//printf("can't open and create Dir:%s\n", dest);
			CString t(dest);
			MessageBox(t);
			return -2;
		}
	}
	strcpy_s(sourcePath, source);
	strcat_s(sourcePath, "//*.*");
	long handle = _findfirst(sourcePath, &finddata);
	if (handle == -1)
	{
		//printf("error");
		MessageBox("error");
		return -1;
	}
	do
	{
		if (finddata.attrib == _A_SUBDIR)  //是文件夹,递归调用复制文件夹
		{
			if (strcmp(finddata.name, ".") == 0 || strcmp(finddata.name, "..") == 0 || strcmp(finddata.name, "HWIO") == 0)
			{
				//printf("skip %s\n", finddata.name);
				continue;
			}
			if (strcmp(finddata.name, "Config") == 0) //Config
			{
				if (MessageBox("是否需要复制Config文件夹", NULL, MB_YESNO) == IDNO)
				{
					continue;
				}
			}
			strcpy_s(tempSourcePath, source);
			strcat_s(tempSourcePath, "\\");
			strcat_s(tempSourcePath, finddata.name);

			strcpy_s(tempDestPath, dest);
			strcat_s(tempDestPath, "\\");
			strcat_s(tempDestPath, finddata.name);
			copyDir(tempSourcePath, tempDestPath);
		}
		else //文件直接复制
		{
			strcpy_s(tempSourcePath, source);
			strcat_s(tempSourcePath, "\\");
			strcat_s(tempSourcePath, finddata.name);

			strcpy_s(tempDestPath, dest);
			strcat_s(tempDestPath, "\\");
			strcat_s(tempDestPath, finddata.name);
			CopyFile((LPCSTR)tempSourcePath, (LPCSTR)tempDestPath, false);
			CString s1 = tempSourcePath;
			CString s2 = tempDestPath;
			m_show.AddString(s1 + _T("--->>>") + s2);
			//UpdateData();		
			UpdateData();
		//	Sleep(2);
		}
	} while (!_findnext(handle, &finddata));
	_findclose(handle);
	return 0;
}


void CcopyFileDlg::OnBnClickedButtonCopy()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(FALSE);
	m_show.ResetContent();
	UpdateData();
	char *t1 = m_source.GetBuffer(0);
	char *t2 = m_dest.GetBuffer(m_dest.GetLength());
	if (copyDir(m_source.GetBuffer(0), t2) == 0)
	{
		MessageBox("复制成功！！");
	}
	else
		MessageBox("failed");
	GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(TRUE);
}
