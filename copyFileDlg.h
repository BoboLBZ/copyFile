
// copyFileDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CcopyFileDlg 对话框
class CcopyFileDlg : public CDialogEx
{
// 构造
public:
	CcopyFileDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COPYFILE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSource();
	afx_msg void OnBnClickedButtonDest();
	CString m_dest;
	CString m_source;
	int copyDir(char * source, char * dest);
	afx_msg void OnBnClickedButtonCopy();
	CListBox m_show;
};
