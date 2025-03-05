
// MFCSOLUTION1Dlg.h: 헤더 파일
//

#include <vector>
#pragma once


// CMFCSOLUTION1Dlg 대화 상자
class CMFCSOLUTION1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCSOLUTION1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSOLUTION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	std::vector<CPoint> m_points;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void  LBtnClicked(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

};
