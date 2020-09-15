#include "derpy2d/image.h"
#include <fstream>
#include <iterator>
#include <assert.h>
#include <stdio.h>
#include <string.h>


Image::Image(std::string path) : path(path) {
    w = 0.0f;
    h = 0.0f;
}

float Image::width(void) {
    read_size();
    return w;
}

float Image::height(void) {
    read_size();
    return h;
}

Color Image::get_px(float x, float y, int filter) {
    assert(loaded);
    assert(filter >= 0 && filter < 3);
    assert(x >= 0.0f && x <= w - 1.0f && y >= 0.0f && y <= h - 1.0f);

    #ifdef DERPY_DEBUG
    return Color(
        255.0f - (x / w * 255.0),
        0.0f,
        (y / h) * 255.0f,
        255.0f
    );
    #else

    unsigned ix, iy, width = (unsigned)w, height = (unsigned)h;
    float r, g, b, a;
    switch (filter)
    {
    case IMAGE_FILTER_NEAREST: {
        ix = (unsigned)(x + 0.5f);
        iy = (unsigned)(y + 0.5f);
        r = (float)imgdata[iy * width * 4 + ix * 4];
        g = (float)imgdata[iy * width * 4 + ix * 4 + 1];
        b = (float)imgdata[iy * width * 4 + ix * 4 + 2];
        a = (float)imgdata[iy * width * 4 + ix * 4 + 3];
        return Color(r, g, b, a);
    }

    case IMAGE_FILTER_LINEAR: {
        ix = (unsigned)x;
        iy = (unsigned)y;
        unsigned nx = ix + 1 < width ? ix + 1 : ix;
        unsigned ny = iy + 1 < height ? iy + 1 : iy;
        float dx = (x - (float)ix) / 2.0f;
        float dy = (y - (float)iy) / 2.0f;

        r = (float)imgdata[iy * width * 4 + ix * 4] * (0.5f - dx);
        g = (float)imgdata[iy * width * 4 + ix * 4 + 1] * (0.5f - dx);
        b = (float)imgdata[iy * width * 4 + ix * 4 + 2] * (0.5f - dx);
        a = (float)imgdata[iy * width * 4 + ix * 4 + 3] * (0.5f - dx);

        r += (float)imgdata[iy * width * 4 + ix * 4] * (0.5f - dy);
        g += (float)imgdata[iy * width * 4 + ix * 4 + 1] * (0.5f - dy);
        b += (float)imgdata[iy * width * 4 + ix * 4 + 2] * (0.5f - dy);
        a += (float)imgdata[iy * width * 4 + ix * 4 + 3] * (0.5f - dy);

        r += (float)imgdata[iy * width * 4 + nx * 4] * dx;
        g += (float)imgdata[iy * width * 4 + nx * 4 + 1] * dx;
        b += (float)imgdata[iy * width * 4 + nx * 4 + 2] * dx;
        a += (float)imgdata[iy * width * 4 + nx * 4 + 3] * dx;

        r += (float)imgdata[ny * width * 4 + ix * 4] * dy;
        g += (float)imgdata[ny * width * 4 + ix * 4 + 1] * dy;
        b += (float)imgdata[ny * width * 4 + ix * 4 + 2] * dy;
        a += (float)imgdata[ny * width * 4 + ix * 4 + 3] * dy;
        return Color(r, g, b, a);
    }

    case IMAGE_FILTER_BILINEAR: {
        assert(false);  // TODO: Implement
        break;
    }

    default: {
        assert(false);
        break;

    }
    }
    #endif // DERPY_DEBUG
}

boolean Image::is_loaded(void) {
    return loaded;
}

void Image::load(void) {
    if (loaded) {
        return;
    }
    read_size();
    const unsigned file_size = (unsigned)w * (unsigned)h * 4;
    imgdata.reserve(file_size);
    printf("Open file %s and read %d bytes of image data...", path.c_str(), file_size);
    FILE *fp = fopen(path.c_str(), "rb");
    assert(fp != nullptr);
    unsigned char buf[256];
    unsigned pos = 0;
    unsigned skip = 8;
    size_t len = fread(buf, 1, sizeof(buf), fp);
    while (len) {
        for (unsigned i = 0; i < len; ++i) {
            if (skip) {
                --skip;
                continue;
            }
            imgdata[pos] = (u8)buf[i];
            ++pos;
        }
        len = fread(buf, 1, sizeof(buf), fp);
    }
    printf("%d bytes\n", pos);
    assert(pos == file_size);
    fclose(fp);
    loaded = true;
}

void Image::unload(void) {
    if (!loaded) {
        return;
    }
    imgdata.clear();
    loaded = false;
}

void Image::read_size(void) {
    if (w != 0.0f) {
        return;
    }
    FILE *fp = fopen(path.c_str(), "rb");
    assert(fp != nullptr);
    unsigned char sz[8];
    assert(fread(sz, 1, sizeof(sz), fp) == 8);
    w = (float)(((unsigned)(sz[0])<<24) + ((unsigned)(sz[1])<<16) + ((unsigned)(sz[2])<<8) + (unsigned)sz[3]);
    h = (float)(((unsigned)(sz[4])<<24) + ((unsigned)(sz[5])<<16) + ((unsigned)(sz[6])<<8) + (unsigned)sz[7]);
    fclose(fp);
}
