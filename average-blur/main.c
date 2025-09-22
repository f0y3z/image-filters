#include <stdio.h>
#include <stdlib.h>


//image loading libraries
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(){
    int height,width,channels;

    //image loaderr
    unsigned char *img=stbi_load("catt.jpg",&width,&height,&channels,0);
    unsigned char *blurred=malloc(height*width*channels);

    int mask=11;
    for (int y =mask/2; y <height-mask/2; y++){
        for (int x = mask/2; x < width-mask/2; x++){
            for (int c=0; c < channels;c++){
                int sum=0;
                for (int i = x-mask/2; i < x+mask/2; i++){
                    for (int j = y-mask/2; j< y+mask/2;j++){
                        int idx = (j*width+i)*channels+c;//calculates index on 1D array 
                        sum += img[idx];
                    }
                }
                blurred[(y*width+x)*channels+c]=sum/(mask*mask);
            }
        }
    }
    for (int y = 0; y <height; y++) {
        for (int x = 0; x < width;x++) {
            if (y < mask/2 || y >= height - mask/2 || x < mask/2 || x >= width - mask/2) {
                for (int c = 0; c < channels; c++) {
                    int idx = (y*width+x)*channels+c;
                    blurred[idx] = img[idx];
                }
            }
        }
    }
    stbi_write_png("blurred.jpg",width,height,channels,blurred,width*channels);
    free(blurred);
    stbi_image_free(img);
    return 0;
}

