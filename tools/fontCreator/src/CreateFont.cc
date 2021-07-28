/*
 * createFont.cc
 *
 *  Created on: Jul 27, 2021
 *      Author: shawn
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <png.h>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned char*  bitmap;   /// ID handle of the glyph texture
    int          sizeX;       /// Size of glyph
    int          sizeY;       /// Size of glyph
    int          bearingX;    /// Offset from baseline to left/top of glyph
    int          bearingY;    /// Offset from baseline to left/top of glyph
    unsigned int advance;     /// Offset to advance to next glyph
    float        u1;          /// upper left uv coordinates
    float        v1;          /// upper left uv coordinates
    float        u2;          /// bottom right uv coordinates
    float        v2;          ///  bottom right uv coordinates
};

int main(int argc, char *argv[]) {

    std::string     filenameImage = "font.png";
    std::string     filenameData = "font.txt";
    int             imageWidth = 1024;
    int             imageHeight = 1024;

    // open a png file
    FILE* fileImage = fopen(filenameImage.c_str(), "wb");
    if (!fileImage) {
        return 1;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        return 1;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        return 1;
    }

    if (setjmp(png_jmpbuf(png))) {
        return 1;
    }

    png_init_io(png, fileImage);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(png, info, imageWidth, imageHeight, 8,
    PNG_COLOR_TYPE_GRAY,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    // set up freetype
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "fonts/LiberationSerif-Regular.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }

    // pixel offsets for each glyph
    int xOffset = 0;
    int yOffset = 0;
    int yCurrentMax = 0;

    // set font scale
    int scale = 128;
    FT_Set_Pixel_Sizes(face, 0, scale);

    // the raw image data with all the glyph
    png_bytepp imageData = new png_bytep[imageHeight];
    for(int i = 0; i < imageHeight; i++) {
        imageData[i] = new png_byte[imageWidth];
        for(int j =0; j <imageWidth; j++) {
            imageData[i][j] = 0;
        }
    }

    // open the data file
    std::ofstream fileData;
    fileData.open(filenameData.c_str());
    if (!fileData) {
        return 1;
    }

    // loop over all characters from ' ' to 127
    std::vector<Character> characters;
    for(unsigned char ch = 32; ch < 127; ch++) {

        // get the character data and bitmap
        if (FT_Load_Char(face, ch, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        Character data;
        data.bitmap     = face->glyph->bitmap.buffer;
        data.sizeX      = face->glyph->bitmap.width;
        data.sizeY      = face->glyph->bitmap.rows;
        data.bearingX   = face->glyph->bitmap_left;
        data.bearingY   = face->glyph->bitmap_top;

        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        // bitshift by 6 to get value in pixels (2^6 = 64)
        data.advance    = face->glyph->advance.x >> 6;
        data.u1         = (float) xOffset / imageWidth;
        data.v1         = (float) yOffset / imageHeight;
        data.u2         = (float) (xOffset + data.sizeX) / imageWidth;
        data.v2         = (float) (yOffset + data.sizeY) / imageHeight;

        fileData << (int) ch    << ",'" << ch                << "'," <<
                data.sizeX      << ","  << data.sizeX        << "," <<
                data.bearingX   << ","  << data.bearingY     << "," <<
                data.advance    << ","  <<
                data.u1         << ","  << data.v1           << "," <<
                data.u2         << ","  << data.v2           << "\n";

        // save the character
        characters.push_back(data);

        std::cout << "Character      : " << (int) ch << ": '" << ch << "'\n";
        std::cout << " data.sizeX    : " << data.sizeX << "\n";
        std::cout << " data.sizeY    : " << data.sizeY << "\n";
        std::cout << " data.bearingX : " << data.bearingX << "\n";
        std::cout << " data.bearingY : " << data.bearingY << "\n";
        std::cout << " data.advance  : " << data.advance << "\n";
        std::cout << " data.u1       : " << data.u1 << "\n";
        std::cout << " data.v1       : " << data.v1 << "\n";
        std::cout << " data.u2       : " << data.u2 << "\n";
        std::cout << " data.v2       : " << data.v2 << "\n";
        std::cout << "\n";

        // wrap to the next row if needed
        if (xOffset + data.sizeX >= imageWidth) {
            yOffset += yCurrentMax;
            yCurrentMax = 0;
            xOffset = 0;
        }

        // copy glyph to the final image
        int x = 0;
        int y = 0;
        for (int i = yOffset; i < yOffset + data.sizeY; i++) {
            for (int j = xOffset; j < xOffset + data.sizeX; j++) {
                imageData[i][j] = data.bitmap[x + data.sizeX * y];
                x++;
            }
            y++;
            x = 0;
        }

        yCurrentMax = data.sizeY > yCurrentMax ? data.sizeY : yCurrentMax;

        // adjust the offset for the next glyph
        xOffset += data.sizeX;
    }

    png_write_image(png, imageData);

    // clean up image
    for (int i = 0; i < imageHeight; i++) {
        delete imageData[i];
    }

    // clean up freetype
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // clean up png
    png_write_end(png, NULL);
    fclose(fileImage);
    png_destroy_write_struct(&png, &info);

}

