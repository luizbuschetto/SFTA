This is the implementation in C/C++ (OpenCV) of Segmentation-Based Fractal Texture Analysis (SFTA) proposed by Costa, Humpire-Mamani and Traina (2012). This algorithm was implemented based on the original code in MATLAB and it was compiled using OpenCV 3.2.0, in a Ubuntu based distro.

Publication where the SFTA algorithm is described:

Costa, A. F., G. E. Humpire-Mamani, A. J. M. Traina. 2012. "An Efficient Algorithm for Fractal Analysis of Textures." In SIBGRAPI 2012 (XXV Conference on Graphics, Patterns and Images), 39-46, Ouro Preto, Brazil.

More info and the original code (in MATLAB) can be found in: 

https://github.com/alceufc/sfta 

Usage:
This algorithm takes two input parameters. The first one is the image to be processed and the second is the nt value. Its explanation can be found on the paper above.

Example:

./sfta /home/luiz/Desktop/test_image.jpg 8

The algorithm will extract the features from "test_image.jpg" with nt = 8, generating a vector with 48 features.
