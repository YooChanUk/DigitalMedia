
// helloView.h: ChelloView 클래스의 인터페이스
//

#pragma once


class ChelloView : public CView
{
protected: // serialization에서만 만들어집니다.
	ChelloView() noexcept;
	DECLARE_DYNCREATE(ChelloView)

// 특성입니다.
public:
	ChelloDoc* GetDocument() const;
	int viewMode;

	#define TWO_IMAGES 2
	#define THREE_IMAGES 3

	void drawImage(CDC* pDC, unsigned char** image, int offsetX, int offsetY, int imageSize, int depth) const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~ChelloView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPrintHello();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionMeaning();
};

#ifndef _DEBUG  // helloView.cpp의 디버그 버전
inline ChelloDoc* ChelloView::GetDocument() const
   { return reinterpret_cast<ChelloDoc*>(m_pDocument); }
#endif

