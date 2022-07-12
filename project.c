// Jiashu Yang jyang166
// Katelyn Surrao ksurrao1
// Ai Omae aomae1
/*****************************************************************************
 * Midterm Project - A program to run the image processing operations
 * Note: for naming convention, we try to follow Google C++ style guide:
 *       https://google.github.io/styleguide/cppguide.html
 * It is not compulsory, but you are highly encouraged to follow a convention.
 *
 * Summary: This file implements a program for image processing operations.
 *          Different operations take different input arguments. In general,
 *            ./project <input> <output> <operation name> [operation params]
 *          The program will return 0 and write an output file if successful.
 *          Otherwise, the below error codes should be returned:
 *            1: Wrong usage (i.e. mandatory arguments are not provided)
 *            2: Input file I/O error
 *            3: Output file I/O error
 *            4: The Input file cannot be read as a PPM file
 *            5: Unsupported image processing operations
 *            6: Incorrect number of arguments for the specified operation
 *            7: Invalid arguments for the specified operation
 *            8: Other errors 
 *****************************************************************************/
#include "ppm_io.h" // PPM I/O header
#include "img_processing.h"
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char **argv) {
  //too few arguments for any operation
  if (argc < 4) {
    fprintf(stderr, "Wrong usage (i.e. mandatory arguments are not provided)\n");
    return 1;
  }
  //checking arguments for each operation
  if (strcmp(argv[3], "grayscale") == 0) {
    if (argc != 4) {
      fprintf(stderr, "incorrect # of inputs for specified operation\n");
      return 6;
    }
    return grayscale(argv[1], argv[2]);
  }
  else if (strcmp(argv[3], "binarize") == 0) {
    if (argc != 5) {
      fprintf(stderr, "incorrect # of inputs for specified operation\n");
      return 6;
    }
    return binarize(argv[1], argv[2], atoi(argv[4]));
  }
  else if (strcmp(argv[3], "crop") == 0) {
    if (argc != 8) {
      fprintf(stderr, "incorrect # of inputs for specified operation\n");
      return 6;
    }
    return crop(argv[1],argv[2], atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
  }
  else if (strcmp(argv[3], "transpose") == 0) {
    if (argc != 4) {
      fprintf(stderr, "incorrect # of inputs for specified operation\n");
      return 6;
    }
    return transpose(argv[1], argv[2]);
  }
  else if (strcmp(argv[3], "gradient") == 0) {
    if (argc != 4) {
      fprintf(stderr, "incorrect # of inputs for specified operation\n");
      return 6;
    }
    return gradient(argv[1], argv[2]);
  }
  else if (strcmp(argv[3], "seam") == 0) {
    if (argc != 6) {
      fprintf(stderr, "incorrect # of inputs for specified operation\n");
      return 6;
    }
    FILE* file = fopen(argv[1], "r");
    Image* image = ReadPPM(file);
    double fact1 = atof(argv[4]);
    double fact2 = atof(argv[5]);
    if (fact1 < 0 || fact1 > 1 || fact2 < 0 || fact2 > 1) {
      printf("invalid arguments for specified operation\n");
    }
    fact1 = (int) (fact1 * image->cols);
    fact2 = (int) (fact2 * image->rows);
    //making sure the image dimension is not less than two
    if (fact1 < 2) {
        fact1 = 2;
    }
    if (fact2 < 2) {
        fact2 = 2;
    }
    // passing image from one function to another
    seam(image, fact1, argv[1], "vertical_seams.ppm");
    crop("vertical_seams.ppm", "vertical_crop.ppm", 0, 0, fact1, image->rows - 1);
    transpose("vertical_crop.ppm", "sideways_ready_for_horizontal_seam.ppm");
    FILE* newFile = fopen("sideways_ready_for_horizontal_seam.ppm", "r");
    Image* transposedImage = ReadPPM(newFile);
    seam(transposedImage, fact2, "sideways_ready_for_horizontal_seam.ppm", "horizontal_seams.ppm");
    crop("horizontal_seams.ppm", "horizontal_crop.ppm", 0, 0, fact2, fact1);
    transpose("horizontal_crop.ppm", argv[2]);
    fclose(file);
    //cleaning up
    free(image->data);
    free(image);
    remove("vertical_seams.ppm");
    remove("vertical_crop.ppm");
    remove("sideways_ready_for_horizontal_seam.ppm");
    remove("horizontal_seams.ppm");
    remove("horizontal_crop.ppm");
  }
  else {
    fprintf(stderr, "Not a valid image processing option\n");
    return 5;
  }
}
