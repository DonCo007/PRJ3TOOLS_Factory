
// ListeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fabrica.h"
#include "FabricaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CEdit x;
  
	CDialogEx::DoDataExchange(pDX);
  // DDX_CBString(pDX, IDC_DIRECTOR, m_strDir);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CProdusDlg dialog 


// CAboutDlg dialog used for App About

class CProdusDlg : public CDialogEx
{
public:
  CProdusDlg(Produs & produs);

  // Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_PRODUS };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
  DECLARE_MESSAGE_MAP()
  virtual BOOL OnInitDialog();

public:
  CString m_Nume;
  CString m_Zi;
  CString m_Luna;
  CString m_An;
  CString m_Pret;
  Produs & m_Produs;
  afx_msg void OnBnClickedButtonOk();
};

CProdusDlg::CProdusDlg(Produs & produs) 
  : CDialogEx(IDD_DIALOG_PRODUS)
  , m_Produs(produs)
{
  m_Nume = m_Produs.m_Nume.c_str();
  m_Zi.Format(L"%d", m_Produs.m_Zi);
  m_Luna.Format(L"%d", m_Produs.m_Luna);
  m_An.Format(L"%d", m_Produs.m_An);
  m_Pret.Format(L"%lf", m_Produs.m_Pret);
}

void CProdusDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
}

BOOL CProdusDlg::OnInitDialog()
{

  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_NUME);
    edit->SetWindowTextW(m_Nume);
  }
  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_ZI);
    edit->SetWindowTextW(m_Zi);
  }
  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_LUNA);
    edit->SetWindowTextW(m_Luna);
  }
  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_AN);
    edit->SetWindowTextW(m_An);
  }
  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_PRET);
    edit->SetWindowTextW(m_Pret);
  }

  return 0;
}

void CProdusDlg::OnBnClickedButtonOk()
{
  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_NUME);
    edit->GetWindowTextW(m_Nume);
  }
  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_ZI);
    edit->GetWindowTextW(m_Zi);
  }
  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_LUNA);
    edit->GetWindowTextW(m_Luna);
  }
  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_AN);
    edit->GetWindowTextW(m_An);
  }
  {
    CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_PRET);
    edit->GetWindowTextW(m_Pret);
  }

  if (m_Nume.Trim().IsEmpty() ||
    m_Zi.Trim().IsEmpty() ||
    m_Luna.Trim().IsEmpty() ||
    m_An.Trim().IsEmpty() ||
    m_Pret.Trim().IsEmpty())
  {
    ::MessageBox(*this, L"Toate campurile trebuie completate", L"Eroare", MB_ICONERROR | MB_OK);
    return;
  }

  wstring nume;
  int zi{}, luna{}, an{};
  double pret{};
  try
  {
    nume = m_Nume.GetString();
    zi = stoi(m_Zi.GetString());
    luna = stoi(m_Luna.GetString());
    an = stoi(m_An.GetString());
    pret = stod(m_Pret.GetString());
  }
  catch (const std::exception&)
  {
    ::MessageBox(*this, L"Date nevalide", L"Eroare", MB_ICONERROR | MB_OK);
    return;
  }

  m_Produs = Produs{ nume, zi, luna, an, pret };

  EndDialog(IDOK);
}

BEGIN_MESSAGE_MAP(CProdusDlg, CDialogEx)
  ON_BN_CLICKED(IDC_BTN_OK, &CProdusDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()

// CListeDlg dialog

CFabricaDlg::CFabricaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFabricaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_DIR_SELECTAT, m_lcProduse);
}

BEGIN_MESSAGE_MAP(CFabricaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_LBN_SELCHANGE(IDC_SUBDIRECTOARE, &CListeDlg::OnSelchangeSubdirectoare)
  ON_BN_CLICKED(IDC_BUTTON_LOAD, &CFabricaDlg::OnBnClickedButtonLoad)
  ON_BN_CLICKED(IDC_BUTTON_SAVE, &CFabricaDlg::OnBnClickedButtonSave)
  ON_BN_CLICKED(IDC_BUTTON_SORT_NAME, &CFabricaDlg::OnBnClickedButtonSortName)
  ON_BN_CLICKED(IDC_BUTTON_SORT_DATE, &CFabricaDlg::OnBnClickedButtonSortDate)
  ON_BN_CLICKED(IDC_BUTTON_SORT_PRICE, &CFabricaDlg::OnBnClickedButtonSortPrice)
  ON_BN_CLICKED(IDC_BUTTON_ADAUGARE, &CFabricaDlg::OnBnClickedButtonAdaugare)
  ON_BN_CLICKED(IDC_BUTTON_STERGERE, &CFabricaDlg::OnBnClickedButtonStergere)
  ON_BN_CLICKED(IDC_BUTTON_EDIT, &CFabricaDlg::OnBnClickedButtonEdit)
END_MESSAGE_MAP()


// CListeDlg message handlers

BOOL CFabricaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000); 
  
  m_lcProduse.SetExtendedStyle(m_lcProduse.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

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

	m_lcProduse.InsertColumn(0, L"Nume", LVCFMT_LEFT, 70);
	m_lcProduse.InsertColumn(1, L"Data", LVCFMT_RIGHT, 50);
	m_lcProduse.InsertColumn(2, L"Pret", LVCFMT_RIGHT, 60);

  RefreshListControl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFabricaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFabricaDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFabricaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFabricaDlg::RefreshListControl()
{
	m_lcProduse.DeleteAllItems();

  for (const auto & produs : m_Produse) {
		int nItem;
		CString str;
		CString strFind;

		nItem = m_lcProduse.InsertItem(m_lcProduse.GetItemCount(), str);

		str.Format(L"%s", produs.m_Nume.c_str());
		m_lcProduse.SetItemText(nItem, 0, str);

		str.Format(L"%ld/%ld/%ld", produs.m_Zi, produs.m_Luna, produs.m_An);
		m_lcProduse.SetItemText(nItem, 1, str);

		str.Format(L"%lf", produs.m_Pret);
		m_lcProduse.SetItemText(nItem, 2, str);
	}
}

void CFabricaDlg::OnBnClickedButtonLoad()
{
  wifstream in("fabrica.txt");

  vector<Produs> produse;

  wstring nume, zi, luna, an, pret;
  while (in >> nume >> zi >> luna >> an >> pret) {
    produse.push_back(Produs{ nume, stoi(zi), stoi(luna), stoi(an), stod(pret) });
  }

  m_Produse = produse;
  RefreshListControl();
}

void CFabricaDlg::OnBnClickedButtonSave()
{
  wofstream out("fabrica.txt");

  for (const auto & produs : m_Produse) {
    out << produs.m_Nume << " "
      << produs.m_Zi << " "
      << produs.m_Luna << " "
      << produs.m_An << " "
      << produs.m_Pret << "\n";
  }
}


void CFabricaDlg::OnBnClickedButtonSortName()
{
  sort(m_Produse.begin(), m_Produse.end(), 
    [](const Produs & first, const Produs & second) {
      return first.m_Nume < second.m_Nume;
    });
  RefreshListControl();
}


void CFabricaDlg::OnBnClickedButtonSortDate()
{
  sort(m_Produse.begin(), m_Produse.end(),
    [](const Produs & first, const Produs & second) {
      return std::tie(first.m_An, first.m_Luna, first.m_Zi) < std::tie(second.m_An, second.m_Luna, second.m_Zi);
    });
  RefreshListControl();
}


void CFabricaDlg::OnBnClickedButtonSortPrice()
{
  sort(m_Produse.begin(), m_Produse.end(),
    [](const Produs & first, const Produs & second) {
      return first.m_Pret < second.m_Pret;
    });
  RefreshListControl();
}


void CFabricaDlg::OnBnClickedButtonAdaugare()
{
  Produs prod{ L"", 0, 0, 0, 0};
  CProdusDlg prodDlg(prod);
  if (prodDlg.DoModal() == IDOK)
  {
    m_Produse.push_back(prod);
    RefreshListControl();
  }
}


void CFabricaDlg::OnBnClickedButtonStergere()
{
  POSITION selected = m_lcProduse.GetFirstSelectedItemPosition();
  if (!selected) 
    return;

  size_t index = ((size_t)selected) - 1;
  m_Produse.erase(std::next(m_Produse.begin(), index));
  RefreshListControl();
}

void CFabricaDlg::OnBnClickedButtonEdit()
{
  POSITION selected = m_lcProduse.GetFirstSelectedItemPosition();
  if (!selected)
    return;

  size_t index = ((size_t)selected) - 1;
 
  CProdusDlg prodDlg(m_Produse[index]);
  prodDlg.DoModal();
  
  RefreshListControl();
}
