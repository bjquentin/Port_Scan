// 12Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "12.h"
#include "12Dlg.h"
#pragma comment (lib,"ws2_32.lib")  // 静态链接库
#include <winsock.h>
#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
typedef union MultiByteStruct
{//IP地址联合体
	UINT uInt;
	UCHAR ucByte[4];
}UNIONIP,*PUNIONIP;



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


UINT CMy12Dlg::IPStrToInt(CString IPStr)
{
	UNIONIP IP;
	int i,j=0;
	IPStr.TrimLeft(" ");
	IPStr.TrimRight(" ");
	for (i=0;i<IPStr.GetLength();i++)
	{
		if (IPStr.GetAt(i) <'0' || IPStr.GetAt(i)>'9')
			if (IPStr.GetAt(i) == '.')
				j++;
			else
				return 0;		
	}
	if (j!=3)
		return 0;
	i=0;
	IPStr+=".";
	CString temp;
	for (int m=0;m<4;m++)
	{		
		temp="";
		while (IPStr.GetAt(i) != '.')
		{
			temp+=IPStr.GetAt(i);
			i++;
		}
		i++;
		if (temp=="" || atoi(temp) > 0xFF)
			return 0;
		else
			IP.ucByte[3-m]=atoi(temp);
	}
	return IP.uInt;
}
CString CMy12Dlg::IPIntToStr(UINT IPInt)
{
	UNIONIP IP;
	CString IPStr;
	
	IP.uInt=IPInt;
	IPStr.Format("%d.%d.%d.%d",IP.ucByte[3],IP.ucByte[2],IP.ucByte[1],IP.ucByte[0]);
	return IPStr;
}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy12Dlg dialog

CMy12Dlg::CMy12Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy12Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy12Dlg)
	m_port1 = 0;
	m_port2 = 0;
	m_status = _T("");
	m_ip1 = _T("");
	m_ip2 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy12Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy12Dlg)
	DDX_Text(pDX, IDC_EDIT1_PORT1, m_port1);
	DDX_Text(pDX, IDC_EDIT2_PORT2, m_port2);
	DDX_Text(pDX, IDC_EDIT3_PORSUT, m_status);
	DDX_Text(pDX, IDC_EDIT_IPSTART, m_ip1);
	DDX_Text(pDX, IDC_EDIT6_IPEND, m_ip2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy12Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy12Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SCAN, OnButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy12Dlg message handlers

BOOL CMy12Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    //改变编辑框默认显示
    CString str = "0.0.0.0";//默认显示内容
    GetDlgItem(IDC_EDIT_IPSTART)->SetWindowText(str);
    GetDlgItem(IDC_EDIT_IPEND)->SetWindowText(str);
	str="1";
    GetDlgItem(IDC_EDIT_PORT1)->SetWindowText(str);//改变ID为IDC_EDIT3的编辑框
    GetDlgItem(IDC_EDIT_PORT2)->SetWindowText(str);//改变ID为IDC_EDIT3的编辑框
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);

	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy12Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy12Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy12Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CMy12Dlg::OnOK()
{
    if(GetDlgItem(IDOK)==GetFocus())
    {
        CDialog::OnOK();    
    }
    //handle enter key
}


void CMy12Dlg::OnButtonScan() 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);                         //MFC窗口函数，用来刷新数据   
 
	UNIONIP uIPBegin,uIPEnd;
	uIPBegin.uInt=IPStrToInt(m_ip1);
	uIPEnd.uInt=IPStrToInt(m_ip2);
	CString strIP,strTemp;

	if (uIPBegin.uInt>uIPEnd.uInt)
	{
		MessageBox("IP地址不对，结束IP应该大于或等于开始IP","操作提示",MB_OK|MB_ICONERROR);
		return;
	}
	if (m_port1>m_port2)  
	{  
		MessageBox("请确保起始Port不大于终止port");  
		WSACleanup();  
		return;  
	} 

    clock_t startTime,endTime;
    startTime = clock();

    for (UINT ip=uIPBegin.uInt;ip<=uIPEnd.uInt;ip++)
	{
		strIP=IPIntToStr(ip);                //转换成字符
		m_status+="\r\n";
		m_status+=strIP;
        m_status+=":\r\n";
        for(UINT port=m_port1;port<=m_port2;port++)
		{
			strTemp.Format("正在扫描主机:%s[%d]",strIP,port);
			DoEvent(strTemp);
			
		   MYUDP Udp;
		   Udp.ip=ip;
		   Udp.port=port;
	       UDPScan(Udp);                     //端口扫描函数
		}
		m_status+="\r\n===================================================================\r\n";
	}	
	endTime = clock(); 
    double dfPassTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	strTemp.Format("扫描结束！共耗时 %f s",dfPassTime);
			DoEvent(strTemp);
   /* CString Time;
    Time.Format("%f",dfPassTime); 
	m_status+="\r\n扫描时间："; 
    m_status+=Time;
    m_status+="s\r\n"; */
	UpdateData(FALSE);
}


void CMy12Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	   if (MessageBox("确实要退出吗?", "退出系统", MB_OKCANCEL | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDOK)
    {
        CDialog::OnCancel();
    }
}

void CMy12Dlg::OnButtonAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
    dlgAbout.DoModal();
}




UINT CMy12Dlg::UDPScan(MYUDP udp)
{
	CString strIP,str;
	strIP=IPIntToStr(udp.ip);

	WSADATA WSAData;  
	if(WSAStartup(MAKEWORD(2,2),&WSAData)!=0)  
	{   
		MessageBox("初始化Winsock接口失败!");  
		return -1; 
	}  
	Socket=socket(AF_INET,SOCK_DGRAM,0);         //创建连接套接字  

	if(Socket==INVALID_SOCKET)  
	{   
		MessageBox("创建Socket失败!");   
		WSACleanup();                           //释放套接字绑定 
		return -1;  
	} 
	
	int nIotrl;  
	unsigned long flag=1;     
	nIotrl=ioctlsocket(Socket,FIONBIO,&flag);  
	if(nIotrl==SOCKET_ERROR) 
	{   
		MessageBox("设置socket模式失败！");  
		closesocket(Socket);                   //关闭Socket套接口
		WSACleanup();     
		return -1;  
	}  
	

	int i=0;  
    int IpAddress=inet_addr(strIP); 

	if(IpAddress==INADDR_NONE) 
  {   
	  hostent* pHostent=gethostbyname(str);   
	  if(pHostent)    
		  IpAddress=(*(in_addr*)pHostent->h_addr).s_addr;  
  }   

	struct sockaddr_in desthost;                         //定义套接字地址  
	memset(&desthost,0,sizeof(desthost));   
	desthost.sin_family=AF_INET;     
	desthost.sin_addr.s_addr=IpAddress; 
	desthost.sin_port=htons(udp.port); 
	char *SendBuf; 
	SendBuf=new char[2]; 
	memset(SendBuf,0,2); 
	int nSend=sendto(Socket,SendBuf,1,0,( struct sockaddr*)&desthost,sizeof(desthost)); 
	if(nSend==SOCKET_ERROR)
	{ 
		MessageBox("UDP包发送失败！"); 
		closesocket(Socket); 
		WSACleanup(); 
		return -1; 
	} 
		
	Sleep(10); 
	sockaddr_in SourceHost; 
	int SourceSize; 
	SourceSize=sizeof(SourceHost); 
	memset(&SourceHost,0,SourceSize); 
	char *RecvBuf; 
	RecvBuf=new char[2]; 
	memset(RecvBuf,0,2);  
	int nRecv; 
	nRecv=recvfrom(Socket,RecvBuf,1,0,(struct sockaddr*)&SourceHost,&SourceSize);  
		
	if(nRecv==SOCKET_ERROR)  
	{   
		int ErrorCode=GetLastError();  
		if(ErrorCode==10054)  
		{  
			str.Format("%d",udp.port); 
			m_status+="UDP Port"; 
			m_status+=str; 
			m_status+=": Close\r\n";  
		}    
		if(ErrorCode==10035)   
		{ 
			str.Format("%d",udp.port); 
			m_status+="UDP Port";  
			m_status+=str;  
			m_status+=": open\r\n";   
		}
	} 
	else   
	{  
		m_status+="UDP Port"; 
		m_status+=udp.port;  
		m_status+=": open\r\n";   
	} 

	    UpdateData(false);  
     	closesocket(Socket);  
	    WSACleanup();                                 //释放套接字绑定  
     return 0; 

}

void CMy12Dlg::DoEvent(CString strPass)
{
	MSG msg;
	CWnd *pEdit=this->GetDlgItem(IDC_EDIT_COMMENT);
	pEdit->SetWindowText(strPass);
	pEdit->UpdateWindow();
	
	if(PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
