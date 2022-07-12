// Jiashu Yang jyang166
// Katelyn Surrao ksurrao1
// Ai Omae aomae1

#ifndef MIDTERM_IMG_PROCESSING_H_
#define MIDTERM_IMG_PROCESSING_H_
#include "ppm_io.h"
#include <stdio.h>

/**
 * \file img_processing.h
 * \brief contains all the image processing functions
 *
 * \details 
 */

/**
 * \brief The function to change a ppm image into greyscale
 * 
 * \details Takes input and ouput file names as parameters and changes said image into greyscale version of itself.
 *
 * \param[in] input   A file name to be read
 * \param[in] output  A file name for generated ppm to be written to
 *
 * \return  The return code of the function
 * \retval  0 if successfully implements the function
 * \retval  2 if error in input file I/O
 * \retval  3 if error in writing ppm to output, or error in output I/O
 * \retval  4 if error reading ppm file
 */
int grayscale(char input[], char output[]);

/**
 * \brief The function to binarize a ppm image.
 *
 * \details Takes input and output file names and an integer threshold as parameters and creates binarized version of said image.
 *
 * \param[in] fileReadName   A file name to be read
 * \param[in] fileWriteName  A file name for generated ppm to be written to
 * \param[in] threshold      A threshold value for assining the binary value to pixels
 *
 * \return  The return code of the function
 * \retval  0 if successfully implements the function
 * \retval  2 if error in input file I/O
 * \retval  3 if error in writing ppm to output, or error in output I/O
 * \retval  4 if error reading ppm file
 * \retval  7 if error if invalid input
 */
 int binarize(char fileReadName[], char fileWriteName[], int threshold);

/**
 * \brief The function to crop a ppm image.
 * 
 * \details Takes input and output file names and coordinates as parameters and creates a cropped version of the image.
 * 
 * \param[in] iput_file     A file name to be read
 * \param[in] output_file   A file name for generated ppm to be written to
 * \param[in] x1            The x coordinate of top left corner of the crop
 * \param[in] y1            The y coordinate of top left corner of the crop
 * \param[in] x2            The x coordinate of bottom right corner of the crop
 * \param[in] y2            The y coordinate of bottom right corner of the crop
 * 
 * \return  The return code of the function
 * \retval  0 if successfully implements the function
 * \retval  2 if error in input file I/O
 * \retval  3 if error in writing ppm to output, or error in output I/O
 * \retval  4 if error reading ppm file
 * \retval  7 if error if invalid input
 */
int crop(char input_file[], char output_file[], int x1, int y1, int x2, int y2);

/**
 * \brief The function to transpose a ppm image.
 *
 * \details Takes input and output file names as parameters and changes said image into transposed version of itself.
 *
 * \param[in] input   A file name to be read
 * \param[in] output  A file name for generated ppm to be written to
 *
 * \return  The return code of the function
 * \retval  0 if successfully implements the function
 * \retval  2 if error in input file I/O
 * \retval  3 if error in writing ppm to output, or error in output I/O
 * \retval  4 if error reading ppm file
 */
int transpose(char input[], char output[]);

 /**
 * \brief The function to apply gradient to a ppm image.
 *
 * \details Takes input and output file names as parameters, and applies the gradient to the image.
 * 
 * \param[in] input    A file name to be read
 * \param[in] output   A file name for generated ppm to be written to
 *
 * \return  The return code of the function
 * \retval  0 if successfully implements the function
 * \retval  2 if error in input file I/O
 * \retval  3 if error in writing ppm to output, or error in output I/O
 * \retval  4 if error reading ppm file
 */
int gradient(char input[], char output[]);

/**
 * \brief Finds the minimum of three input values.
 *
 * \details The helper function for seamCarve() that finds the minimum of three double values
 * 
 * \param[in] x   The first double to compare
 * \param[in] y   The second double to compare
 * \param[in] z   The third double to compare
 *
 * \return  The value of the minimum
 */
 int min(int x, int y, int z);

/**
 * \brief The helper function to repeatedly seam carve a ppm image.
 *
 * \details This function extracts vertical seams from an image based on the pixels' relative gradient magnitudes.
 *
 * \param[in] image  A pointer to an image to be seam carved
 * \param[in] fact   The rescaled width of the image
 *
 * \return  The return code of the function
 * \retval  0 if successfully implements the function
 */
int carveCols(Image* image, double fact);

/**
 * \brief The function that completes seam carving.
 *
 * \details This function takes in user input and accordingly seam carves a ppm image in both the vertical and horizontal directions by making calls to other helper functions.
 *
 * \param[in] image  A pointer to the image to be modified
 * \param[in] fact   A scale factor to apply to column size of original image
 * \param[in] input  File to read image from
 * \param[in] output  File to write image to
 *
 * \return  The return code of the function
 * \retval  0 if successfully implements the function
 * \retval  2 if error in input file I/O
 * \retval  3 if error in writing ppm to output, or error in output I/O
 * \retval  4 if error reading ppm file
 * \retval  7 if error if invalid input
 */
int seam(Image* image, double fact, char input[], char output[]);

#endif