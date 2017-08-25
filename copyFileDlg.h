
// copyFileDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CcopyFileDlg �Ի���
class CcopyFileDlg : public CDialogEx
{
// ����
public:
	CcopyFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COPYFILE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
