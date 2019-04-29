#include <windows.h>
#include <objidl.h>
#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

void CreateImage(int nImageWidth, int nImageHeight)
{
	BYTE* pImageData = new BYTE[nImageWidth * 4 * nImageHeight];

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	// gdiplus
	Bitmap bmp(nImageWidth, nImageHeight, 4 * nImageWidth, PixelFormat32bppARGB, pImageData);
	Gdiplus::Graphics *g = Gdiplus::Graphics::FromImage(&bmp);
	g->Clear(Color(255, 255, 255, 255));

	// draw 
	// ...

	CLSID pngClsid;
	GetEncoderClsid(L"mochi.jpg", &pngClsid);
	bmp.Save(L"test_mochi.png", &pngClsid);

	delete[] pImageData;
	delete g;

}

/*
int main()
{
	CreateImage(10, 10);
	return 0;
}
*/
