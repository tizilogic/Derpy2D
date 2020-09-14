#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

#include "derpy2d/image.h"
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <assert.h>

class Assets {
public:
    Assets(void);
    Image& image(std::string name);
    void load_everything(void);
    void scan(void);

private:
    std::unordered_map<std::string, std::unique_ptr<Image>> images;
};


#endif // _ASSETS_HPP_
