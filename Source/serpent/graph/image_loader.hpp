#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include "frame.hpp"
#include "sprite.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void LoadImage(const char* path, Frame *frame)
{
    int w;
    int h;
    int comp;
    int channels = 4;
    unsigned char* image = stbi_load(path, &w, &h, &comp, STBI_rgb_alpha);
    if(image == nullptr) throw(std::string("Failed to load image"));


    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            uint colour = 0;
            for(int c = 0; c < channels; c++)
            {
                colour<<=8;
                colour += image[(x + y*w)*channels + c];
                
            }
            frame->pset(x, y, colour);
        }
    }
}


void LoadImageFlipY(const char* path, Frame *frame)
{
    int w;
    int h;
    int comp;
    int channels = 4;
    unsigned char* image = stbi_load(path, &w, &h, &comp, STBI_rgb_alpha);
    if(image == nullptr) throw(std::string("Failed to load image"));


    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            uint colour = 0;
            for(int c = 0; c < channels; c++)
            {
                colour<<=8;
                colour += image[(x + y*w)*channels + c];
                
            }
            frame->pset(x, h-y-1, colour);
        }
    }
}


void LoadSprite(Sprite* sprite, const char* path, int width, int height, int n)
{
    int w;
    int h;
    int comp;
    int channels = 4;
    unsigned char* image = stbi_load(path, &w, &h, &comp, STBI_rgb_alpha);
    if(image == nullptr) throw(std::string("Failed to load image"));
    Frame frame(width, height);

    for(int i = 0; i < n; i++)
    {
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                uint colour = 0;
                for(int c = 0; c < channels; c++)
                {
                    colour <<= 8;
                    colour += image[(x + (y + i * height) * w ) * channels + c];
                }
                frame.pset(x, y, colour);
            }
        }
        sprite->load(&frame);
    }
}


void LoadSpriteFlipY(Sprite* sprite, const char* path, int width, int height, int n)
{
    int w;
    int h;
    int comp;
    int channels = 4;
    unsigned char* image = stbi_load(path, &w, &h, &comp, STBI_rgb_alpha);
    if(image == nullptr) throw(std::string("Failed to load image"));
    Frame frame(width, height);

    for(int i = 0; i < n; i++)
    {
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                uint colour = 0;
                for(int c = 0; c < channels; c++)
                {
                    colour <<= 8;
                    colour += image[(x + (y + i * height) * w ) * channels + c];
                }
                frame.pset(x, height-y-1, colour);
            }
        }
        sprite->load(&frame);
    }
}