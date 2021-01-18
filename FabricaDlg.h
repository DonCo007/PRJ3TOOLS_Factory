
// ListeDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CListeDlg dialog
class CFabricaDlg : public CDialogEx
{
// Construction
public:
	CFabricaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
  vector<Produs> m_Produse;
public:
  CListCtrl m_lcProduse;
  void RefreshListControl();

  afx_msg void OnBnClickedButtonLoad();
  afx_msg void OnBnClickedButtonSave();
  afx_msg void OnBnClickedButtonSortName();
  afx_msg void OnBnClickedButtonSortDate();
  afx_msg void OnBnClickedButtonSortPrice();
  afx_msg void OnBnClickedButtonAdaugare();
  afx_msg void OnBnClickedButtonStergere();
  afx_msg void OnBnClickedButtonEdit();
};
