// 12Dlg.h : header file
//

#if !defined(AFX_12DLG_H__8475459D_E40C_47B6_8ACC_63771D1E94F8__INCLUDED_)
#define AFX_12DLG_H__8475459D_E40C_47B6_8ACC_63771D1E94F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma comment (lib,"ws2_32.lib")  // ¾²Ì¬Á´½Ó¿â
#include <winsock.h>

typedef struct IPPORT
{
    UINT ip;
	UINT port;
}MYUDP;
/////////////////////////////////////////////////////////////////////////////
// CMy12Dlg dialog

class CMy12Dlg : public CDialog
{
// Construction
private:  
	SOCKET Socket;
public:
	CMy12Dlg(CWnd* pParent = NULL);	// standard constructor
    UINT IPStrToInt(CString IPStr);
    CString IPIntToStr(UINT IPInt);
    void OnOK();
    UINT UDPScan(MYUDP udp);
	void DoEvent(CString strPass);

// Dialog Data
	//{{AFX_DATA(CMy12Dlg)
	enum { IDD = IDD_MY12_DIALOG };
	UINT	m_port1;
	UINT	m_port2;
	CString	m_status;
	CString	m_ip1;
	CString	m_ip2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy12Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy12Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonScan();
	virtual void OnCancel();
	afx_msg void OnButtonAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12DLG_H__8475459D_E40C_47B6_8ACC_63771D1E94F8__INCLUDED_)
