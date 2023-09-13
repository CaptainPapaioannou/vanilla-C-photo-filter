# vanilla-C-photo-filter
Vanilla C programm to apply photo filters to an image in BMP format


## Overview ##
Program that applies filters to BMPs. You can think of filtering an image as taking the pixels of some original image, and modifying each pixel in such a way that a particular effect is apparent in the resulting image.
Current available filters are:
  - **Greyscale**: Converts the image to black and white. If all red, green, and blue values of an rgb pixel are set to 0x00 the pixel is black, and if all 3 values are set to 0xff the pixel is white. To turn an image to black and white, you just have to make sure that you turn all red,green, and blue of an rgb pixel to the same value. The result will be varying shades of gray along the black-white spectrum, with higher values meaning lighter shades (closer to white) and lower values meaning darker shades (closer to black). To decide what will be the value for each pixel in orer to retain the balance in the picture we get that average of all the 3 color hexadecimal values for each pixel
    
  - **Reflection**: The resulting image is what you would get by placing the original image in front of a mirror. So any pixels on the left side of the image should end up on the right, and vice versa
  - **Blur**: The "box blur" technique is used to create image softening or blurring effects. It involves averaging the color values of neighboring pixels within a 3x3 box centered around each pixel in the image. This process is applied even to pixels along the image's edges and corners
  - **Edges**: In image processing AI, edge detection is vital for finding object boundaries. The Sobel operator, applied in both horizontal and vertical directions, calculates new pixel values by emphasizing color differences in a 3x3 pixel grid. The final edge value is computed as the square root of the sum of squared Gx and Gy values, rounded to the nearest integer (capped at 255). For edge pixels, assume a 1-pixel black border, treating out-of-bounds access as solid black (0 values).

## Usage ##
1. Comple the program as per the bellow bash command:
   ```
   make filter
   ```
2. Run the program depending on the bmp file name and the filter you want to apply. Change the bellow INFILE and OUTFILE to the names of the files depending on your occasion
   -For grayscale:
   ```
   $ ./filter -g INFILE.bmp OUTFILE.bmp
   ```
  - For reflection:
    ```
    $ ./filter -r INFILE.bmp OUTFILE.bmp
    ```
  - For blur:
    ```
    $ ./filter -b INFILE.bmp OUTFILE.bmp
    ```
  - For edges:
    ```
    $ ./filter -e INFILE.bmp OUTFILE.bmp
    ```

## Aknowledgements ##
This program is a solution to a CS50 problem set

