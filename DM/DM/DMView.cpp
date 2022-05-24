
// DMView.cpp: CDMView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DM.h"
#endif

#include "DMDoc.h"
#include "DMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TWO_IMAGES 1
#define THREE_IMAGES 2
#define TWO_IMAGES_SCALED 4

// CDMView

IMPLEMENT_DYNCREATE(CDMView, CScrollView)

BEGIN_MESSAGE_MAP(CDMView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDMView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PIXEL_ADD, &CDMView::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CDMView::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CDMView::OnPixelTwoImageAdd)
	ON_COMMAND(ID_REGION_SHARPENING, &CDMView::OnRegionSharpening)
	ON_COMMAND(ID_REGION_SOBEL, &CDMView::OnRegionSobel)
	ON_COMMAND(ID_REGION_MEDIAN, &CDMView::OnRegionMedian)
	ON_COMMAND(ID_REGION_MEANING, &CDMView::OnRegionMeaning)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CDMView::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_REGION_EMBOSSING, &CDMView::OnRegionEmbossing)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CDMView::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CDMView::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CDMView::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CDMView::OnGeometryRotate)
	ON_COMMAND(ID_GEOMETRY_FLIP, &CDMView::OnGeometryFlip)
	ON_COMMAND(ID_EROSION, &CDMView::OnErosion)
	ON_COMMAND(ID_DILATION, &CDMView::OnDilation)
	ON_COMMAND(ID_SMR, &CDMView::OnSmr)
	ON_COMMAND(ID_OPENING, &CDMView::OnOpening)
	ON_COMMAND(ID_CLOSING, &CDMView::OnClosing)
	ON_COMMAND(ID_BIN_LABELING, &CDMView::OnBinLabeling)
END_MESSAGE_MAP()

// CDMView 생성/소멸

CDMView::CDMView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CDMView::~CDMView()
{
}

BOOL CDMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CDMView 그리기

void CDMView::OnDraw(CDC* pDC)
{
	CDMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc)
	{
		return;
	}
	// 입력 영상이 읽히지 않았으면 종료 
	if (pDoc->inputImg == NULL)
	{
		return;
	}

	// 입력 이미지 1
	drawImage(pDC, pDoc->inputImg, 0, 0, pDoc->imageHeight, pDoc->imageWidth, pDoc->depth);

	if (viewMode == THREE_IMAGES)
	{
		// 입력 이미지 2
		drawImage(pDC, pDoc->inputImg2, 400, 0, pDoc->imageHeight, pDoc->imageWidth, pDoc->depth);
		// 결과 이미지 
		drawImage(pDC, pDoc->resultImg, 700, 0, pDoc->imageHeight, pDoc->imageWidth, pDoc->depth);

	}
	else if (viewMode == TWO_IMAGES_SCALED)
	{
		drawImage(pDC, pDoc->gResultImg, 400, 0, pDoc->gImageHeight, pDoc->gImageWidth, pDoc->depth);
	}
	else if(viewMode == TWO_IMAGES)
	{
		// TWO_IMAGES인 경우의 결과 이미지
		drawImage(pDC, pDoc->resultImg, 400, 0, pDoc->imageHeight, pDoc->imageWidth, pDoc->depth);
	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CDMView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CDMView 인쇄


void CDMView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CDMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDMView 진단

#ifdef _DEBUG
void CDMView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDMView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDMDoc* CDMView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDMDoc)));
	return (CDMDoc*)m_pDocument;
}
#endif //_DEBUG


// CDMView 메시지 처리기


void CDMView::OnPixelAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->PixelAdd();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnPixelHistoEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->PixelHistoEq();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnPixelTwoImageAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->PixelTwoImageAdd();

	viewMode = THREE_IMAGES;

	Invalidate(FALSE);
}


void CDMView::drawImage(CDC* pDC, unsigned char** image, int offsetX, int offsetY, int height, int width, int depth) const
{
	// TODO: 여기에 구현 코드 추가.
	if (depth == 3)		// 컬러일 때
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				pDC->SetPixel(x + offsetX, y + offsetY,
					RGB(image[y][depth * x],
						image[y][(depth * x) + 1],
						image[y][(depth * x) + 2],
						)	// RGB 매크로의 닫는 부분
				);		// SetPixel 함수의 닫는 부분
			}
		}
	}
	else	// 흑백일 때 
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				pDC->SetPixel(x + offsetX, y + offsetY,
					RGB(image[y][x],
						image[y][x],
						image[y][x],
						)	// RGB 매크로의 닫는 부분
				);		// SetPixel 함수의 닫는 부분
			}
		}
	}
}


void CDMView::OnRegionSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->RegionSharpening();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnRegionSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->RegionSobel();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnRegionMedian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;

	pDoc->RegionMedian();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnRegionMeaning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->RegionMeaning();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnGeometryZoominPixelCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->GeometryZoominPixelCopy();

	viewMode = TWO_IMAGES_SCALED;

	Invalidate(FALSE);
}


void CDMView::OnRegionEmbossing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->RegionEmbossing();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnGeometryZoomoutSubsampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->GeometryZoomoutSubsampling();

	viewMode = TWO_IMAGES_SCALED;

	Invalidate(FALSE);
}


void CDMView::OnGeometryZoomoutAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->GeometryZoomoutAvg();

	viewMode = TWO_IMAGES_SCALED;

	Invalidate(FALSE);
}


void CDMView::OnGeometryZoominInterpolation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->GeometryZoominInterpolation();

	viewMode = TWO_IMAGES_SCALED;

	Invalidate(FALSE);
}


void CDMView::OnGeometryRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->GeometryRotate();

	viewMode = TWO_IMAGES_SCALED;

	Invalidate(FALSE);
}


void CDMView::OnGeometryFlip()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->GeometryFlip();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->Erosion();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnDilation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->Dilation();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnSmr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->Smr();

	viewMode = TWO_IMAGES_SCALED;

	Invalidate(FALSE);

}


void CDMView::OnOpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->Opening();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}


void CDMView::OnClosing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->Closing();

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}

void CDMView::OnBinLabeling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CDMDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)
		return;

	pDoc->grass_label(256,256);

	viewMode = TWO_IMAGES;

	Invalidate(FALSE);
}
