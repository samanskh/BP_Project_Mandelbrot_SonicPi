#ifndef __MANDELBROTSET_H__
#define __MANDELBROTSET_H__

#include "defs.h"
#include <math.h>

int get_burning_ship_iter(double x, double y)
{
    const int max_iter = 500; 
    double zx = 0.0;
    double zy = 0.0;

    for (int iter = 0; iter < max_iter; ++iter)
    {
        double zx_squared = zx * zx;
        double zy_squared = zy * zy;

        if (zx_squared + zy_squared >= 10.0)
            return iter;

        double xtemp = zx_squared - zy_squared + x;
        zy = fabs(2 * zx * zy) + y;
        zx = xtemp;
    }

    return max_iter;  
}


// void hsv_to_rgb(int iter, int max_iter, COLORINDEX *p)
// {
//     // Adjusting hue, saturation, and value parameters for a lighter and smoother color scheme
//     int hue = (int)((double)iter / (double)max_iter * 180.0);
//     int saturation = 50;  // Lower saturation for a lighter look
//     int value = 150;  // Adjust value to control overall brightness

//     // Simple HSV to RGB conversion
//     int c = (saturation * value) / 255;
//     int x = c * (1 - abs((hue / 60) % 2 - 1));
//     int m = value - c;

//     int r, g, b;

//     if (hue < 60)
//     {
//         r = c;
//         g = x;
//         b = 0;
//     }
//     else if (hue < 120)
//     {
//         r = x;
//         g = c;
//         b = 0;
//     }
//     else if (hue < 180)
//     {
//         r = 0;
//         g = c;
//         b = x;
//     }
//     else if (hue < 240)
//     {
//         r = 0;
//         g = x;
//         b = c;
//     }
//     else if (hue < 300)
//     {
//         r = x;
//         g = 0;
//         b = c;
//     }
//     else
//     {
//         r = c;
//         g = 0;
//         b = x;
//     }

//     p->r = (r + m) * 255;
//     p->g = (g + m) * 255;
//     p->b = (b + m) * 255;
//     p->junk = 0;
// }





void UpdateImageData(ImageState *state)
{
    for (int x = 0; x < state->width; x++)
        for (int y = 0; y < state->height; y++)
        {
            
            double nx = state->minx + (x * (state->maxx - state->minx) / state->width);
            double ny = -(state->miny + (y * (state->maxy - state->miny) / state->height));

            
             double rx = nx * cos(state->angle) + ny * sin(state->angle);
            double ry = -nx * sin(state->angle) + ny * cos(state->angle);

            
            int iter = get_burning_ship_iter(rx, ry);

            
            // hsv_to_rgb(iter, 40, &(state->bmFileData.bmHeader.colorIdx[iter]));

            
            state->bmFileData.bmData[y * state->width + x] = iter;
        }
    for(int i =0;i<255;i++){
    state->bmFileData.bmHeader.colorIdx[i].b=(unsigned char)185.0*(double) i /20.0;
    state->bmFileData.bmHeader.colorIdx[i].g=(unsigned char)180.0*(double) i /30.0;
    state->bmFileData.bmHeader.colorIdx[i].r=(unsigned char)0.0*(double) i /8.0;
    }
    WriteBitmapFile(state->image_count++, &state->bmFileData);
}



void ChangeCenter(ImageState *state, double newcx, double newcy, int steps)
{
    double cx_step = (double)(newcx - state->cx) / steps;
    double cy_step = (double)(newcy - state->cy) / steps;

    for (int i = 0; i < steps; i++)
    {
        state->cx += cx_step;
        state->cy += cy_step;
        state->maxx += cx_step;
        state->maxy += cy_step;
        state->minx += cx_step;
        state->miny += cy_step;
        UpdateImageData(state);
    }
}

void ChangeZoom(ImageState* state, double zoom, int steps)
{
    double zoom_step = (1 - 1 / zoom) / steps;
    for (int i = 0; i < steps; i++)
    {
        double x = (state->maxx - state->minx) * zoom_step;
        double y = (state->maxy - state->miny) * zoom_step;
        state->maxx -= x;
        state->maxy -= y;
        state->minx += x;
        state->miny += y;
        UpdateImageData(state);    
    }
}

void ChangeRotation(ImageState *state, double angle, int steps)
{
    double angle_step = angle / steps;

    for (int i = 0; i < steps; i++)
    {
        state->angle += angle_step;

        UpdateImageData(state);
    }
}

void Hold(ImageState *state, int steps)
{
    for (int i = 0; i < steps; i++)
    {
        
        WriteBitmapFile(state->image_count++, &state->bmFileData);
    }
}

#endif
