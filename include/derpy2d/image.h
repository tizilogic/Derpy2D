#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#define IMAGE_FILTER_NEAREST 0
#define IMAGE_FILTER_LINEAR 1
#define IMAGE_FILTER_BILINEAR 2

#include <circle/types.h>
#include "derpy2d/color.h"
#include <string>
#include <vector>


class Image {
public:
    Image(std::string path);
    float width(void);
    float height(void);
    Color get_px(float x, float y, int filter = IMAGE_FILTER_NEAREST);
    boolean is_loaded(void);
    void load(void);
    void unload(void);

private:
    inline void read_size(void);

    float w, h;
    std::string path;
    std::vector<u8> imgdata;
    boolean loaded = false;
};

#endif // _IMAGE_HPP_
