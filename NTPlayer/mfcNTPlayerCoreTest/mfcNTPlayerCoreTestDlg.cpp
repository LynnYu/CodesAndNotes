
// mfcNTPlayerCoreTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfcNTPlayerCoreTest.h"
#include "mfcNTPlayerCoreTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_ID_GET_CURRENT_PLAY_POS   1

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CmfcNTPlayerCoreTestDlg dialog




CmfcNTPlayerCoreTestDlg::CmfcNTPlayerCoreTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmfcNTPlayerCoreTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcNTPlayerCoreTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcNTPlayerCoreTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_SIZE()
    ON_WM_SIZING()
	//}}AFX_MSG_MAP
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BTN_OPEN, &CmfcNTPlayerCoreTestDlg::OnBnClickedBtnOpen)
    ON_BN_CLICKED(IDC_BTN_PLAY, &CmfcNTPlayerCoreTestDlg::OnBnClickedBtnPlay)
    ON_BN_CLICKED(IDC_BTN_PAUSE, &CmfcNTPlayerCoreTestDlg::OnBnClickedBtnPause)
    ON_BN_CLICKED(IDC_BTN_STOP, &CmfcNTPlayerCoreTestDlg::OnBnClickedBtnStop)
    ON_BN_CLICKED(IDC_BTN_CLOSE, &CmfcNTPlayerCoreTestDlg::OnBnClickedBtnClose)
    ON_WM_TIMER()
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CmfcNTPlayerCoreTestDlg)
    //EASYSIZE(IDC_VIDEO_DISPLAY, ES_BORDER, ES_BORDER, ES_BORDER, IDC_BTN_PAUSE, ES_HCENTER)
    EASYSIZE(IDC_BTN_PAUSE, ES_BORDER, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_HCENTER)
    EASYSIZE(IDC_BTN_PLAY, IDC_BTN_PAUSE, ES_KEEPSIZE, IDC_BTN_PAUSE, ES_BORDER, 0)
    EASYSIZE(IDC_BTN_OPEN, IDC_BTN_PLAY, ES_KEEPSIZE, IDC_BTN_PLAY, ES_BORDER, 0)
    EASYSIZE(IDC_BTN_STOP, IDC_BTN_PAUSE, ES_KEEPSIZE, IDC_BTN_PAUSE, ES_BORDER, 0)
    EASYSIZE(IDC_BTN_CLOSE, IDC_BTN_STOP, ES_KEEPSIZE, IDC_BTN_STOP, ES_BORDER, 0)
END_EASYSIZE_MAP()



// CmfcNTPlayerCoreTestDlg message handlers

BOOL CmfcNTPlayerCoreTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    INIT_EASYSIZE;

    CRect rect(0, 0, 600, 450);
    MoveWindow(rect);


    ntplayer_init(OnNtPlayerNotify, this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmfcNTPlayerCoreTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmfcNTPlayerCoreTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmfcNTPlayerCoreTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmfcNTPlayerCoreTestDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    UPDATE_EASYSIZE;

    RECT rcControl, rcDisplay;
    GetClientRect(&rcDisplay);
    GetDlgItem(IDC_BTN_OPEN)->GetClientRect(&rcControl);
    GetDlgItem(IDC_BTN_OPEN)->MapWindowPoints(this, &rcControl);

    rcDisplay.bottom = rcControl.top - 2;
    GetDlgItem(IDC_VIDEO_DISPLAY)->MoveWindow(&rcDisplay);

    ntplayer_update_video_display(&rcDisplay, false);
}

void CmfcNTPlayerCoreTestDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
    CDialog::OnSizing(fwSide, pRect);
    EASYSIZE_MINSIZE(600, 450, fwSide, pRect);
}
void CmfcNTPlayerCoreTestDlg::OnDestroy()
{
    CDialog::OnDestroy();

    // TODO: Add your message handler code here

    KillTimer(TIMER_ID_GET_CURRENT_PLAY_POS);

    ntplayer_uninit();
}

void CmfcNTPlayerCoreTestDlg::OnBnClickedBtnOpen()
{
    // TODO: Add your control notification handler code here
    RECT rcDisplay;
    GetDlgItem(IDC_VIDEO_DISPLAY)->GetClientRect(&rcDisplay);
    ntplayer_set_video_display(GetDlgItem(IDC_VIDEO_DISPLAY)->GetSafeHwnd(), &rcDisplay, false);

    CFileDialog dlg(TRUE);
    if (IDOK == dlg.DoModal())
    {
        CString strFileName = dlg.GetPathName();
        ntplayer_open(wcs2mbs(CP_UTF8, strFileName).c_str());
    }
}

std::string	wcs2mbs(int nCodePage, const wchar_t* wcs)
{
    if (!wcs)
        return std::string("");

    char* pText;
    int cbMultiByte = WideCharToMultiByte(nCodePage,
        0,
        wcs,
        -1,
        NULL,
        0,
        NULL,
        NULL);
    pText=new char[cbMultiByte+1];
    memset(pText, 0, (cbMultiByte+1)*sizeof(char));
    WideCharToMultiByte(nCodePage,
        0,
        wcs,
        -1,
        pText,
        cbMultiByte,
        NULL,
        NULL);

    std::string strText(pText);
    delete[] pText;
    return strText;
}

void CmfcNTPlayerCoreTestDlg::OnBnClickedBtnPlay()
{
    // TODO: Add your control notification handler code here
    ntplayer_play();
}

void CmfcNTPlayerCoreTestDlg::OnBnClickedBtnPause()
{
    // TODO: Add your control notification handler code here
    ntplayer_pause();
}

void CmfcNTPlayerCoreTestDlg::OnBnClickedBtnStop()
{
    // TODO: Add your control notification handler code here
    ntplayer_stop();
}

void CmfcNTPlayerCoreTestDlg::OnBnClickedBtnClose()
{
    // TODO: Add your control notification handler code here
    KillTimer(TIMER_ID_GET_CURRENT_PLAY_POS);
    ntplayer_close();
}


void CmfcNTPlayerCoreTestDlg::OnNtPlayerNotify(void* pUser, int msg, void* pParam)
{
    CmfcNTPlayerCoreTestDlg* pThis = (CmfcNTPlayerCoreTestDlg*)pUser;
    switch (msg)
    {
    case kPlayerNotifyOpenSucceeded:
        pThis->OnOpenSucceeded();
        break;
    case kPlayerNotifyOpenFailed:
        pThis->OnOpenFailed();
        break;
    }
}

void CmfcNTPlayerCoreTestDlg::OnOpenSucceeded()
{
    SetTimer(TIMER_ID_GET_CURRENT_PLAY_POS, 1000, NULL);
    ntplayer_play();
}

void CmfcNTPlayerCoreTestDlg::OnOpenFailed()
{
    MessageBox(_T("Open File Failed"));
}
void CmfcNTPlayerCoreTestDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    switch (nIDEvent)
    {
    case TIMER_ID_GET_CURRENT_PLAY_POS:
        {
            long cur_play_pos = 0;
            ntplayer_get_current_play_pos(&cur_play_pos);
        }
        break;
    }

    CDialog::OnTimer(nIDEvent);
}
