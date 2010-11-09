// This software is in the public domain.
// There are no restrictions on any sort of usage of this software.

#include <monapi.h>
#include <monapi/messages.h>
#define USE_JPEG 1
#ifdef USE_JPEG
#include <jpegls.h>
#endif
#include "image.h"

#define BYTE2INT(array, index) (*(int*)&array[index])

using namespace MonAPI;

static HList<guiserver_bitmap*> bitmaps;

guiserver_bitmap* CreateBitmap(int width, int height, unsigned int background)
{
	uint32_t handle = MemoryMap::create(sizeof(guiserver_bitmap) + width * height * 4);
	if (handle == 0) return NULL;
	
	guiserver_bitmap* ret = (guiserver_bitmap*)MemoryMap::map(handle, false);
	if (ret == NULL) return NULL;
	
	ret->Handle = handle;
	ret->Width  = width;
	ret->Height = height;
	bitmaps.add(ret);
	
	FillColor(ret, (unsigned int)background);
	
	return ret;
}

guiserver_bitmap* GetBitmapPointer(uint32_t handle)
{
	int size = bitmaps.size();
	for (int i = 0; i < size; i++)
	{
		if (bitmaps[i]->Handle == handle) return bitmaps[i];
	}
	return NULL;
}

bool DisposeBitmap(uint32_t handle)
{
	int size = bitmaps.size();
	for (int i = 0; i < size; i++)
	{
		if (bitmaps[i]->Handle == handle)
		{
			bitmaps.removeAt(i);
			MemoryMap::unmap(handle);
			return true;
		}
	}
	return false;
}

guiserver_bitmap* ReadBitmap(SharedMemory& shm)
{
	if (shm.size() < 6) return NULL;
	
	if (shm.data()[0] != 'B' || shm.data()[1] != 'M') return NULL;
	if (shm.size() != (uint32_t)BYTE2INT(shm.data(), 2)) return NULL;
	if (BYTE2INT(shm.data(), 6) != 0) return NULL;
	if (BYTE2INT(shm.data(), 14) != 40) return NULL;
	if (shm.data()[28] + (shm.data()[29] << 8) != 24) return NULL; // 24bpp only
	if (BYTE2INT(shm.data(), 30) != 0) return NULL;
	
	int bfOffBits = BYTE2INT(shm.data(), 10);
	int w = BYTE2INT(shm.data(), 18);
	int h = BYTE2INT(shm.data(), 22);

	uint32_t handle = MemoryMap::create(sizeof(guiserver_bitmap) + w * h * 4);
	if (handle == 0) return NULL;
	
	guiserver_bitmap* ret = (guiserver_bitmap*)MemoryMap::map(handle);
	if (ret == NULL) return NULL;
	
	ret->Handle = handle;
	ret->Width  = w;
	ret->Height = h;
	int p1 = 0;
	int lineSize = (w * 3 + 3) >> 2 << 2;
	for (int y = 0; y < h; y++)
	{
		int p2 = bfOffBits + (h - y - 1) * lineSize;
		for (int x = 0; x < w; x++)
		{
			uint8_t* ptr = (uint8_t*)&ret->Data[p1++];
			ptr[0] = shm.data()[p2++];
			ptr[1] = shm.data()[p2++];
			ptr[2] = shm.data()[p2++];
			ptr[3] = 0xff;
		}
	}
	return ret;
}

#ifdef USE_JPEG
guiserver_bitmap* ReadJPEG(SharedMemory& shm)
{
	CJPEGLS jpeg;
	if (jpeg.Open(shm.data(), shm.size()) != 0) return NULL;
	
	int w, h;
	jpeg.GetInfo(&w, &h);

	uint32_t handle = MemoryMap::create(sizeof(guiserver_bitmap) + w * h * 4);
	if (handle == 0) return NULL;
	
	guiserver_bitmap* ret = (guiserver_bitmap*)MemoryMap::map(handle);
	if (ret == NULL) return NULL;
	
	ret->Handle = handle;
	ret->Width  = w;
	ret->Height = h;
	jpeg.Decode((uint8_t*)ret->Data);
	for (int i = w * h - 1; i >= 0; i--)
	{
		uint8_t* ptr1 = (uint8_t*)&ret->Data[i], * ptr2 = &((uint8_t*)ret->Data)[i * 3];
		ptr1[0] = ptr2[2];
		ptr1[1] = ptr2[1];
		ptr1[2] = ptr2[0];
		ptr1[3] = 0xff;
	}
	return ret;
}
#endif

guiserver_bitmap* ReadImage(const CString& file, bool prompt /*= false*/)
{
	CString fn = file.toUpper();
	scoped_ptr<SharedMemory> shm(monapi_file_read_all(fn));
	guiserver_bitmap* ret = NULL;
	if (shm.get() == NULL) return ret;
	
	if (fn.endsWith(".BMP"))
	{
		if (prompt) printf("%s: Decoding %s....", GUI_SERVER_NAME, (const char*)fn);
		ret = ReadBitmap(*shm);
		if (prompt) printf(ret != NULL ? "OK\n" : "ERROR\n");
	}
#ifdef USE_JPEG
	else if (fn.endsWith(".JPG"))
	{
		if (prompt) printf("%s: Decoding %s....", GUI_SERVER_NAME, (const char*)fn);
		ret = ReadJPEG(*shm);
		if (prompt) printf(ret != NULL ? "OK\n" : "ERROR\n");
	}
#endif
#ifdef USE_BZIP2
	else if (fn.endsWith(".BM2"))
	{
		if (prompt) printf("%s: Decompressing %s....", GUI_SERVER_NAME, (const char*)fn);
		monapi_cmemoryinfo* mi2 = monapi_call_file_decompress_bz2(mi);
		if (prompt) printf(mi2 != NULL ? "OK\n" : "ERROR\n");
		
		if (mi2 != NULL)
		{
			if (prompt) printf("%s: Decoding %s....", GUI_SERVER_NAME, (const char*)fn);
			ret = ReadBitmap(mi2);
			if (prompt) printf(ret != NULL ? "OK\n" : "ERROR\n");
			monapi_cmemoryinfo_dispose(mi2);
			monapi_cmemoryinfo_delete(mi2);
		}
	}
#endif
	else if (fn.endsWith(".BM5"))
	{
		if (prompt) printf("%s: Decompressing %s....", GUI_SERVER_NAME, (const char*)fn);
		scoped_ptr<SharedMemory> shm2(monapi_call_file_decompress_st5(*(shm.get())));
		if (prompt) printf(shm2.get() != NULL ? "OK\n" : "ERROR\n");
		
		if (shm2.get() != NULL)
		{
			if (prompt) printf("%s: Decoding %s....", GUI_SERVER_NAME, (const char*)fn);
			ret = ReadBitmap(*shm2);
			if (prompt) printf(ret != NULL ? "OK\n" : "ERROR\n");
            shm2->unmap();
		}
	}
    shm->unmap();
	return ret;
}

guiserver_bitmap* ResizeBitmap(guiserver_bitmap* bmp, int width, int height)
{
	guiserver_bitmap* ret = CreateBitmap(width, height, 0);
	unsigned char* ptr = (unsigned char*)ret->Data;
	for (int y = 0; y < height; y++)
	{
		double y1 = ((double)(y    )) * ((double)bmp->Height) / ((double)height);
		double y2 = ((double)(y + 1)) * ((double)bmp->Height) / ((double)height);
		for (int x = 0; x < width; x++)
		{
			double x1 = ((double)(x    )) * ((double)bmp->Width) / ((double)width);
			double x2 = ((double)(x + 1)) * ((double)bmp->Width) / ((double)width);
			double size = (x2 - x1) * (y2 - y1);
			double r = 0.0, g = 0.0, b = 0.0;
			for (double y3 = y1, y4; y3 < y2; y3 = y4)
			{
				y4 = (double)(int)(y3 + 1);
				if (y4 > y2) y4 = y2;
				for (double x3 = x1, x4; x3 < x2; x3 = x4)
				{
					x4 = (double)(int)(x3 + 1);
					if (x4 > x2) x4 = x2;
					double size2 = (x4 - x3) * (y4 - y3);
					unsigned char* ptr2 = (unsigned char*)&bmp->Data[((int)x3) + ((int)y3) * bmp->Width];
					b += ((double)ptr2[0]) * size2;
					g += ((double)ptr2[1]) * size2;
					r += ((double)ptr2[2]) * size2;
				}
			}
			ptr[0] = (int)(b / size);
			ptr[1] = (int)(g / size);
			ptr[2] = (int)(r / size);
			ptr[3] = 255;
			ptr += 4;
		}
	}
	return ret;
}

void FillColor(guiserver_bitmap* bmp, unsigned int color)
{
	int len = bmp->Width * bmp->Height;
	for (int i = 0; i < len; i++)
	{
		bmp->Data[i] = color;
	}
}

void DrawImage(guiserver_bitmap* dst, guiserver_bitmap* src, int x /*= 0*/, int y /*= 0*/, int sx /*= 0*/, int sy /*= 0*/, int sw /*= -1*/, int sh /*= -1*/, unsigned int transparencyKey /*= 0*/, int opacity /*= 255*/)
{
	if (opacity == 0) return;
	
	int dw = dst->Width, dh = dst->Height;
	if (sw < 0) sw = src->Width;
	if (sh < 0) sh = src->Height;
	int x1 = x, y1 = y, x2 = x + sw, y2 = y + sh;
	if (x1 < 0) x1 = 0;
	if (y1 < 0) y1 = 0;
	if (x2 > dw) x2 = dw;
	if (y2 > dh) y2 = dh;
	x1 += sx - x;
	y1 += sy - y;
	x2 += sx - x;
	y2 += sy - y;
	if (x1 < 0) x1 = 0;
	if (y1 < 0) y1 = 0;
	if (x2 > src->Width ) x2 = src->Width;
	if (y2 > src->Height) y2 = src->Height;
	x1 -= sx;
	y1 -= sy;
	x2 -= sx;
	y2 -= sy;
	for (int yy = y1; yy < y2; yy++)
	{
		unsigned int* pDst = &dst->Data[( x + x1) + ( y + yy) * dw];
		unsigned int* pSrc = &src->Data[(sx + x1) + (sy + yy) * src->Width];
		for (int xx = x1; xx < x2; xx++, pDst++, pSrc++)
		{
			if (((*pSrc) & 0xff000000) == 0 || *pSrc == transparencyKey) continue;
			
			if (opacity == 255)
			{
				*pDst = *pSrc;
			}
			else
			{
				uint8_t* p1 = (uint8_t*)pDst, * p2 = (uint8_t*)pSrc;
				p1[0] = (uint8_t)((((int)p1[0]) * (255 - opacity) + ((int)p2[0]) * opacity) / 255);
				p1[1] = (uint8_t)((((int)p1[1]) * (255 - opacity) + ((int)p2[1]) * opacity) / 255);
				p1[2] = (uint8_t)((((int)p1[2]) * (255 - opacity) + ((int)p2[2]) * opacity) / 255);
				p1[3] = 0xff;
			}
		}
	}
}

bool ImageHandler(MessageInfo* msg)
{
	switch (msg->header)
	{
		// �C���[�W�f�R�[�h�v��
		case MSG_GUISERVER_DECODEIMAGE:
		{
			// �t�@�C����
			guiserver_bitmap* bmp = ReadImage(msg->str);
			if (bmp != NULL)
			{
				Message::reply(msg, bmp->Handle);
			}
			else
			{
				Message::reply(msg);
			}
			break;
		}
		// �C���[�W�����v��
		case MSG_GUISERVER_CREATEBITMAP:
		{
			// ���A�����A�w�i�F
			guiserver_bitmap* bmp = CreateBitmap(msg->arg1, msg->arg2, msg->arg3);
			if (bmp != NULL)
			{
				Message::reply(msg, bmp->Handle);
			}
			else
			{
				Message::reply(msg);
			}
			break;
		}
		// �C���[�W�j���v��
		case MSG_GUISERVER_DISPOSEBITMAP:
			DisposeBitmap(msg->arg1);
			Message::reply(msg);
			break;
		default:
			return false;
	}
	return true;
}
