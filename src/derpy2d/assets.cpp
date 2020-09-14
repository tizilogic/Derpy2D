#include "derpy2d/assets.h"


Assets::Assets(void) {}

Image& Assets::image(std::string name) {
    assert(images.find(name) != images.end());
    Image& img = *images[name];
    img.load();
    return img;
}

void Assets::load_everything(void) {
    for (auto &it: images) {
        it.second->load();
    }
}

void Assets::scan(void) {
    printf("Starting asset scan...\n");

    DIR * const dir = opendir("assets");  /* TODO: Remove hardcoded dir */

    if (dir != nullptr) {
        while (true) {
            errno = 0;
            struct dirent const * const dp = readdir(dir);
            if (dp != nullptr && (strstr(dp->d_name, ".raw") != NULL
                                  || strstr(dp->d_name, ".RAW") != NULL)) {
                char img_path[255];
                sprintf(img_path, "assets/%s", dp->d_name);
                printf("Adding \"%s\" as \"%s\"\n", img_path, dp->d_name);
                images.emplace(
                    std::make_pair(dp->d_name, new Image(img_path)));
            }
            else {
                if (errno != 0 && errno != ENOENT) {
                    fprintf(stderr, "readdir failed with errno %d\n", errno);
                }
                break;
            }
        }

        if (closedir (dir) != 0) {
                perror("closedir() failed ");
        }
        printf("Completed asset scan\n");
    }
    else {
        perror("opendir (\"assets\") failed");
    }

    printf("Loaded assets are: ");
    for (auto &it: images) {
        printf("\"%s\"" , it.first.c_str());
    }
    printf("\n");
}
