#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double MINR = -2.2, MAXR = 1.0, MINI = -1.2, MAXI = 1.2;

extern int mandel(int re, int im);

int doubleToFixed(double d)
{
    return (int)(d * (1 << 16));
}

int mapToReal(int X, int width, double minR, double maxR)
{
    double range = maxR-minR;
    double x0 = X*(range/width) + minR;
    int x = doubleToFixed(x0);
    return x;
}

int mapToImaginary( int Y, int height, double minI, double maxI)
{
    double range = maxI - minI;
	double y0 = Y*(range/height) + minI;
    int y = doubleToFixed(y0);
    return y;
}


int main(int argc, const char *argv[])
{
    if (argc !=3)
    {
        printf("Enter image width and output file name as parameters\n");
        return 0;
    }
    int width = atoi(argv[1]);
    int height = width*3 / 4;

    const int pixelSize = 3;
    FILE* fp;
    fp = fopen(argv[2], "wb");
    int xLen = (int)(((8 * pixelSize * width) + 31) / 32) * 4;
    int pixelsSize = xLen * height;
    int fileSize = 54 + pixelsSize;
    unsigned char widthBytes[4];
    unsigned char heightBytes[4];

    widthBytes[0] = (width >> 24) & 0xFF;
    widthBytes[1] = (width >> 16) & 0xFF;
    widthBytes[2] = (width >> 8) & 0xFF;
    widthBytes[3] = width & 0xFF;

    heightBytes[0] = (height >> 24) & 0xFF;
    heightBytes[1] = (height >> 16) & 0xFF;
    heightBytes[2] = (height >> 8) & 0xFF;
    heightBytes[3] = height & 0xFF;

    unsigned char bmpFileHeader[14] = {'B','M', fileSize, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpInfoHeader[40] = {40, 0, 0, 0, widthBytes[3], widthBytes[2], widthBytes[1],
                                       widthBytes[0], heightBytes[3], heightBytes[2], heightBytes[1], heightBytes[0], 1, 0, 24, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0};

    fwrite(&bmpFileHeader, 1, 14, fp);
    fwrite(&bmpInfoHeader, 1, 40, fp);
    unsigned char* pixels = malloc(pixelsSize);

    int iter, x, y, i=0;
    for (int Y=0; Y<height; Y++)
    {
        for (int X=0; X<width; X++)
        {
            x = mapToReal(X, width, MINR, MAXR);
            y = mapToImaginary(Y, height, MINI, MAXI);
            iter = mandel(x, y);

            u_int8_t r = (int)sinf(iter);
            u_int8_t g = iter;
            u_int8_t b = iter;
            pixels[i++] = r*r;
            pixels[i++] = g;
            pixels[i++] = b;
        }
    }
    fwrite(pixels, 1, pixelsSize, fp);
    fclose(fp);
    return 0;
}
