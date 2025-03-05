
// MFCTESTDlg.h: 헤더 파일
//
#include<iostream>
#include<vector>
#pragma once

// CMFCTESTDlg 대화 상자
class CMFCTESTDlg : public CDialogEx
{
// 생성입니다.
private:
	CImage m_image;
	int nCcount = 0;
	bool bisblack = false;
	bool bLDown;
public:
	CMFCTESTDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);
	void updateDisplay();
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	int RADIUS;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void RESET();
	void drawLargeCircle(unsigned char* fm, const std::vector<std::pair<int, int>>& points, int nGray, double thick);
	bool IsInRange(int i, int j, int minX, int minY, int maxX, int maxY);
	bool IsBlack(int x, int y);
	std::pair<int, int>* FindnearP(int x, int y);
	afx_msg void OnBnClickedBtnReset();
	int THICK;
	afx_msg void OnBnClickedBtnRandom();
};


