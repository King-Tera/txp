// txp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Pixel {
    unsigned char r, g, b, a;
    bool operator==(const Pixel& other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
};
struct compPixel {
    Pixel pixel;
    int pixelcount;
};

std::vector<Pixel> loadPixels(int& outWidth, int& outHeight) {
    int channels;
    unsigned char* data = stbi_load("testimg.png", &outWidth, &outHeight, &channels, 4);

    if (data == nullptr) return {};

    int pixelCount = outWidth * outHeight;
    std::vector<Pixel> pixels(pixelCount);

    for (int i = 0; i < pixelCount; i++) {
        pixels[i] = {
            data[i * 4],        // R
            data[i * 4 + 1],    // G
            data[i * 4 + 2],    // B
            data[i * 4 + 3]     // A
        };
    }

    stbi_image_free(data);
    return pixels;
}
std::vector<compPixel> compressPixels(std::vector<Pixel>& imgpixel) {
    int count = 0;
    int c;
    compPixel comppix;
    std::vector<compPixel> comppixel;
    //std::cout << "img size:" << imgpixel.size() << std::endl;
    for (int i = 0;i < imgpixel.size(); i++) {
        for (int b = i; b+1<(int)imgpixel.size() && imgpixel[b] == imgpixel[b + 1]; b++) {
            count++;
            c = b;
        
        }

        comppix.pixel = (imgpixel[c]);
        comppix.pixelcount = count;
        comppixel.push_back(comppix);
        i += count;
        count = 0;

    }
    return comppixel;
}
std::vector<Pixel> decompressPixels(std::vector<compPixel>& comppixel){
    std::vector<Pixel> imgpixel;
    for (int i = 0; i < comppixel.size(); i++) {
        for (int b = 0;b <= comppixel[i].pixelcount; b++) {
            imgpixel.push_back(comppixel[i].pixel);
        }

    }
    return imgpixel;

}
int main() {
    int width, height;
    std::vector<Pixel> pixels = loadPixels(width, height);
    std::vector<compPixel> comppixel = compressPixels(pixels);
    std::vector<Pixel> decomppixel = decompressPixels(comppixel);
    std::cout << "og image size: "<< pixels.size() << "\n";
    std::cout << "comppressed image size: " <<comppixel.size() << "\n";
    std::cout << "decomppressed image size: " << decomppixel.size() << "\n";

    /* for (int i = 0; i < (int)pixels.size(); i++) {
        Pixel& p = pixels[i];
        std::cout << "Pixel " << i << ": "
            << "R=" << (int)p.r << " "
            << "G=" << (int)p.g << " "
            << "B=" << (int)p.b << " "
            << "A=" << (int)p.a << "\n";
    }
    */

}
