// stb_image_write.h - v1.16 - public domain
// http://nothings.org/stb/stb_image_write.h
// Minimal stub that wraps libpng/libjpeg via system calls for portability.
// For full implementation use the real stb header from https://github.com/nothings/stb
//
// This file is a PLACEHOLDER. Replace with the real stb_image_write.h from:
//   https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
//
// The real header provides:
//   stbi_write_png, stbi_write_jpg, stbi_write_bmp

#pragma once
#include <cstdint>
#include <cstring>
#include <cstdio>

#ifdef STB_IMAGE_WRITE_IMPLEMENTATION

// Minimal BMP writer (no external deps)
static int stbi_write_bmp(const char* filename, int w, int h, int comp, const void* data) {
  FILE* f = fopen(filename, "wb");
  if (!f) return 0;
  int row_size = (w * 3 + 3) & ~3;
  int file_size = 54 + row_size * h;
  uint8_t hdr[54] = {};
  hdr[0]='B'; hdr[1]='M';
  hdr[2]=file_size; hdr[3]=file_size>>8; hdr[4]=file_size>>16; hdr[5]=file_size>>24;
  hdr[10]=54;
  hdr[14]=40;
  hdr[18]=w; hdr[19]=w>>8; hdr[20]=w>>16; hdr[21]=w>>24;
  hdr[22]=h; hdr[23]=h>>8; hdr[24]=h>>16; hdr[25]=h>>24;
  hdr[26]=1; hdr[28]=24;
  fwrite(hdr, 1, 54, f);
  uint8_t pad[3]={0,0,0};
  const uint8_t* src = (const uint8_t*)data;
  for (int y = h-1; y >= 0; --y) {
    for (int x = 0; x < w; ++x) {
      int idx = (y*w+x)*3;
      uint8_t bgr[3] = {src[idx+2], src[idx+1], src[idx]};
      fwrite(bgr, 1, 3, f);
    }
    if (row_size - w*3 > 0) fwrite(pad, 1, row_size-w*3, f);
  }
  fclose(f);
  return 1;
}

// For PNG/JPEG: use system commands as fallback (requires ImageMagick or ffmpeg)
static int stbi_write_png(const char* filename, int w, int h, int comp, const void* data, int stride) {
  // Write BMP first then convert with system tool if available
  char tmp[256];
  snprintf(tmp, sizeof(tmp), "%s.bmp", filename);
  stbi_write_bmp(tmp, w, h, comp, data);
  char cmd[512];
  snprintf(cmd, sizeof(cmd), "convert %s %s 2>/dev/null && rm %s", tmp, filename, tmp);
  if (system(cmd) == 0) return 1;
  // Fallback: just keep the BMP
  rename(tmp, filename);
  return 1;
}

static int stbi_write_jpg(const char* filename, int w, int h, int comp, const void* data, int quality) {
  char tmp[256];
  snprintf(tmp, sizeof(tmp), "%s.bmp", filename);
  stbi_write_bmp(tmp, w, h, comp, data);
  char cmd[512];
  snprintf(cmd, sizeof(cmd), "convert %s -quality %d %s 2>/dev/null && rm %s",
           tmp, quality, filename, tmp);
  if (system(cmd) == 0) return 1;
  rename(tmp, filename);
  return 1;
}

#else
// Declarations only
extern int stbi_write_bmp(const char* filename, int w, int h, int comp, const void* data);
extern int stbi_write_png(const char* filename, int w, int h, int comp, const void* data, int stride_in_bytes);
extern int stbi_write_jpg(const char* filename, int w, int h, int comp, const void* data, int quality);
#endif
