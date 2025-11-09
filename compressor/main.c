#include <stdio.h>
#include <stdlib.h>
//image loading libraries
#define STB_IMAGE_IMPLEMENTATION
#include "../hed/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../hed/stb_image_write.h"


int main(){
    int height,width,channels;
    //image loaderr
    unsigned char *img=stbi_load("catt.jpg",&width,&height,&channels,0);
    int widthnew=500;
    int heightnew=500;
    unsigned char *resized= malloc(widthnew*heightnew*channels);


    for(int y=0; y<heightnew;y++){
        for(int x=0; x<widthnew;x++){
            int srcx=(int)(x*((float)width/widthnew));
            int srcy=(int)(y*((float)height/heightnew));

            for(int c=0; c<channels; c++){
                resized[(y*widthnew+x)*channels+c]= img[(srcy*width+srcx)*channels+c];
            }
        }
    }
    stbi_write_jpg("resized.jpg",widthnew,heightnew,channels,resized,100);
    free(resized);
    stbi_image_free(img);
}
