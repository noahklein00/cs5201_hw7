from PIL import Image
import numpy as np
import sys
import math

def rgb_to_bw(pixel: np.array) -> str:
    '''
    @brief Reduces the color range of a pixel to either black or white.
    If the average intensity is less than 200, the pixel is changed to black,
    otherwise, it is white.
    @param pixel: An array of size 3 containing RGB values
    @return A single-character string indicating the new color of the pixel
    '''
    if (sum(pixel)/3) < 200:
        return 'B'
    else:
        return 'W'

def image_to_array(image_path: str,
                   text_path: str = 'output.txt',
                   size_threshold: int = 5000) -> None:
    '''
    @brief Converts an image to a black-or-white ASCII representation,
    downscaling as necessary
    @param image_path: The filename of the input image
    @param text_path: The filename of the ASCII output
    @param size_threshold: The max allowed matrix size
    @return The ASCII array (to be used in further processing)
    '''
    with Image.open(image_path) as image:
        matrix_size = image.size[0] * image.size[1]
        if matrix_size > size_threshold:
                scale_factor = math.sqrt(int(size_threshold) / matrix_size)
                new_shape = (int(scale_factor * dim) for dim in image.size)
                image = image.resize(new_shape)
        im_arr = np.fromstring(image.tobytes(), dtype=np.uint8)
        im_arr = im_arr.reshape((image.size[1], image.size[0], 3))
    im_arr = np.apply_along_axis(rgb_to_bw, 2, im_arr)
    np.savetxt(text_path, im_arr, delimiter='', fmt='%c')

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print('Pass three arguments: input image path, output text path, and '
        'matrix size threshold')
        raise RuntimeError('Wrong # of arguments')
    image_to_array(sys.argv[1], sys.argv[2], int(sys.argv[3]))
