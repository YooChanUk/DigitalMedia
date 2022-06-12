
// DMDoc.h: CDMDoc 클래스의 인터페이스
//


#pragma once


class CDMDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CDMDoc() noexcept;
	DECLARE_DYNCREATE(CDMDoc)

// 특성입니다.
public:
	unsigned char** inputImg;
	unsigned char** inputImg2;
	unsigned char** resultImg;
	int imageHeight;
	int imageWidth;
	int depth;

	int gImageWidth;
	int gImageHeight;
	unsigned char** gResultImg;

	int tgImageWidth;
	int tgImageHeight;
	unsigned char** tgResultImg;

	//unsigned char** m_InImg;
	//unsigned char** m_OutImg;
	unsigned char** morphedImg[10];

	//워핑
	typedef struct
	{
		int Px;
		int Py;
		int Qx;
		int Qy;
	} control_line;

#include <math.h> 


// 작업입니다.
public:
	


// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CDMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void PixelAdd();
	void PixelHistoEq();
	void PixelTwoImageAdd();
	void LoadTwoImages();
	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
	void RegionSharpening();
	void Convolve(unsigned char** inputImg, unsigned char** resultImg, int cols, int rows, float mask[][3], int bias, int depth);
	void RegionSobel();
	void RegionMedian();
	void RegionMeaning();
	void GeometryZoominPixelCopy();
	void RegionEmbossing();
	void GeometryZoomoutSubsampling();
	void GeometryZoomoutAvg();
	void GeometryZoominInterpolation();
	void GeometryRotate();
	void GeometryFlip();
	void Erosion();
	void Dilation();
	int Smr();
	void Opening();
	void CopyResultToInput();
	void Closing();
	void grass_label(int height, int width);
	void grass(short* coloring, int height, int width, int i, int j, int curColor);
	int push(short* stackx, short* stacky, int arr_size, short vx, short vy, int* top);
	int pop(short* stackx, short* stacky, short *vx, short *vy, int* top);
	void m_BlobColoring(int height, int width);
	void m_BorderFollow(int height, int width);
	void GeometryWarping();
	void GeometryMorphing();
};
