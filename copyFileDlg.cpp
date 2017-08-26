
// copyFileDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CcopyFileDlg �Ի���



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


// CcopyFileDlg ��Ϣ�������

BOOL CcopyFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	UpdateData();
	char buff[256];
	_getcwd(buff, 255);
	m_source=buff;
	m_dest = "D:\\AutoMachine";
	UpdateData(false);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CcopyFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CcopyFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcopyFileDlg::OnBnClickedButtonSource()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR servPath[MAX_PATH];
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = servPath;
	bi.lpszTitle = _T("ѡ����ҪĿ���ļ�·��");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	if ((pidl = SHBrowseForFolder(&bi)) != NULL)
	{
		if (SUCCEEDED(SHGetPathFromIDList(pidl, servPath))) //�õ��ļ��е�ȫ·������Ҫ�Ļ���ֻ�ñ��ļ�����  
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR servPath[MAX_PATH];
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = servPath;
	bi.lpszTitle = _T("ѡ����Ҫ���Ƶ��ļ�·��");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	if ((pidl = SHBrowseForFolder(&bi)) != NULL)
	{
		if (SUCCEEDED(SHGetPathFromIDList(pidl, servPath))) //�õ��ļ��е�ȫ·������Ҫ�Ļ���ֻ�ñ��ļ�����  
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
	if (_access(dest, 0) == -1) //�ж�Ŀ���ļ����Ƿ���ڣ������ھʹ���
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
		if (finddata.attrib == _A_SUBDIR)  //���ļ���,�ݹ���ø����ļ���
		{
			if (strcmp(finddata.name, ".") == 0 || strcmp(finddata.name, "..") == 0 || strcmp(finddata.name, "HWIO") == 0)
			{
				//printf("skip %s\n", finddata.name);
				continue;
			}
			if (strcmp(finddata.name, "Config") == 0) //Config
			{
				if (MessageBox("�Ƿ���Ҫ����Config�ļ���", NULL, MB_YESNO) == IDNO)
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
		else //�ļ�ֱ�Ӹ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(FALSE);
	m_show.ResetContent();
	UpdateData();
	char *t1 = m_source.GetBuffer(0);
	char *t2 = m_dest.GetBuffer(m_dest.GetLength());
	if (copyDir(m_source.GetBuffer(0), t2) == 0)
	{
		MessageBox("���Ƴɹ�����");
	}
	else
		MessageBox("failed");
	GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(TRUE);
}
