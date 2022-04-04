
// helloView.cpp: ChelloView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "hello.h"
#endif

#include "helloDoc.h"
#include "helloView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





// ChelloView

IMPLEMENT_DYNCREATE(ChelloView, CView)

BEGIN_MESSAGE_MAP(ChelloView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &ChelloView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PRINT_HELLO, &ChelloView::OnPrintHello)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &ChelloView::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_ADD, &ChelloView::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &ChelloView::OnPixelTwoImageAdd)
	ON_COMMAND(ID_REGION_SHARPENING, &ChelloView::OnRegionSharpening)
	ON_COMMAND(ID_REGION_MEANING, &ChelloView::OnRegionMeaning)
END_MESSAGE_MAP()

// ChelloView 생성/소멸

ChelloView::ChelloView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

ChelloView::~ChelloView()
{
}

BOOL ChelloView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// ChelloView 그리기

void ChelloView::OnDraw(CDC* pDC)
{
	ChelloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//if (!pDoc)
		//return;

		/*for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x],
				pDoc->inputImg[y][x],
				pDoc->inputImg[y][x]));
		}
	}*/
	if (!pDoc)
	{
		return;
	}
	
	if (pDoc->inputImg == NULL)
	{
		return;
	}

	drawImage(pDC, pDoc->inputImg, 0, 0, pDoc->imageHeight, pDoc->depth);

	if (viewMode == THREE_IMAGES)
	{
		drawImage(pDC, pDoc->inputImg2, 300, 0, pDoc->imageHeight, pDoc->depth);
		drawImage(pDC, pDoc->resultImg, 600, 0, pDoc->imageHeight, pDoc->depth);
	}
	else
	{
		drawImage(pDC, pDoc->resultImg, 300, 0, pDoc->imageHeight, pDoc->depth);
	}
	
	/*if (pDoc->depth == 1)
	{
		for (int y = 0; y < pDoc->imageHeight; y++)
		{
			for (int x = 0; x < pDoc->imageWidth; x++)
			{
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x],
					pDoc->inputImg[y][x],
					pDoc->inputImg[y][x]));
			}
		}

		if (viewMode == THREE_IMAGES)
		{

			for (int y = 0; y < pDoc->imageHeight; y++)
			{
				for (int x = 0; pDoc->imageWidth; x++)
				{
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x],
							pDoc->inputImg2[y][x]));
				}
			}

			for (int y = 0; y < pDoc->imageHeight; y++)
			{
				for (int x = 0; x < pDoc->imageWidth; x++)
				{
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y, 
						RGB(pDoc->resultImg[y][x],
						pDoc->resultImg[y][x],
						pDoc->resultImg[y][x]));
				}
			}

		}
		else
		{
			for (int y = 0; y < pDoc->imageHeight; y++)
			{
				for (int x = 0; x < pDoc->imageWidth; x++)
				{
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, 
						RGB(pDoc->resultImg[y][x],
						pDoc->resultImg[y][x],
						pDoc->resultImg[y][x]));
				}
			}
		}
	}
	else if (pDoc->depth == 3)
	{
		for (int y = 0; y < pDoc->imageHeight; y++)
		{
			for (int x = 0; x < pDoc->imageWidth; x++)
			{
				pDC->SetPixel(x + pDoc->imageWidth + 30, y, 
					RGB(pDoc->resultImg[y][3*x],
					pDoc->resultImg[y][3*x+1],
					pDoc->resultImg[y][3*x+2]));
			}
		}

		if (viewMode == THREE_IMAGES)
		{

			for (int y = 0; y < pDoc->imageHeight; y++)
			{
				for (int x = 0; pDoc->imageWidth; x++)
				{
					pDC->SetPixel(x + pDoc->imageWidth + 30, y,
						RGB(pDoc->inputImg2[y][3*x],
							pDoc->inputImg2[y][3*x+1],
							pDoc->inputImg2[y][3*x+2]));
				}
			}

			for (int y = 0; y < pDoc->imageHeight; y++)
			{
				for (int x = 0; x < pDoc->imageWidth; x++)
				{
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y, 
						RGB(pDoc->resultImg[y][3*x],
						pDoc->resultImg[y][3*x+1],
						pDoc->resultImg[y][3*x+2]));
				}
			}

		}
		else
		{
			for (int y = 0; y < pDoc->imageHeight; y++)
			{
				for (int x = 0; x < pDoc->imageWidth; x++)
				{
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, 
						RGB(pDoc->resultImg[y][3*x],
						pDoc->resultImg[y][3*x+1],
						pDoc->resultImg[y][3*x+2]));
				}
			}
		}
	}*/




	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//pDC->TextOut(100, 100, "첫번째 영상처리 프로그램 예제 입니다 ");
}


// ChelloView 인쇄


void ChelloView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL ChelloView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void ChelloView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void ChelloView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void ChelloView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void ChelloView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// ChelloView 진단

#ifdef _DEBUG
void ChelloView::AssertValid() const
{
	CView::AssertValid();
}

void ChelloView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

ChelloDoc* ChelloView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ChelloDoc)));
	return (ChelloDoc*)m_pDocument;
}
#endif //_DEBUG


// ChelloView 메시지 처리기


void ChelloView::OnPrintHello()
{
	AfxMessageBox("안녕하세요 여러분!!!");
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void ChelloView::OnPixelHistoEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ChelloDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelHistoEq();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void ChelloView::OnPixelAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ChelloDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);//pDoc 변수의 오류검증

	if (pDoc->inputImg == NULL) return; //입력 영상이 있는지 검사
	
	pDoc->PixelAdd();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
	
}


void ChelloView::OnPixelTwoImageAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ChelloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelTwoImageAdd();

	viewMode = THREE_IMAGES;

	Invalidate(FALSE);
}

void ChelloView::drawImage(CDC* pDC, unsigned char** image, int offsetX, int offsetY, int imageSize, int depth) const
{
	//ChelloDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);

	bool blsRGB = (depth == 3) ? true : false;
	if (blsRGB)
	{
		for (int y = 0; y < imageSize; y++)
		{
			for (int x = 0; x < imageSize * 3; x++)
			{
				pDC->SetPixel(x + offsetX, y + offsetY,
					RGB(image[y][3 * x],
						image[y][3 * x + 1],
						image[y][3 * x + 2]));
			}
		}
	}
	else
	{
		for (int y = 0; y < imageSize; y++)
		{
			for (int x = 0; x < imageSize; x++)
			{
				pDC->SetPixel(x + offsetX, y + offsetY,
					RGB(image[y][x],
						image[y][x],
						image[y][x]));
			}
		}
	}
}


void ChelloView::OnRegionSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ChelloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->RegionSharpening();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void ChelloView::OnRegionMeaning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ChelloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->RegionMeaning();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}
