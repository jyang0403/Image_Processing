// Jiashu Yang jyang166
// Katelyn Surrao ksurrao1
// Ai Omae aomae1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ppm_io.h"

/**
 * \file img_processing.c
 * \brief processes the ppm image in a variety of ways
 *
 * \details This source file implements all image processing functions for the midterm project.
 */

int grayscale(char input[], char output[]) {
    FILE* input_file = fopen(input, "r");
    if (input_file == NULL || ferror(input_file)) {
        fprintf(stderr, "Input file I/O error\n");
        return 2;
    }
    Image* image = ReadPPM(input_file);
    if (image == NULL) {
        fprintf(stderr, "The Input file cannot be read as a PPM file\n");
        return 4;
    }
    for (int i = 0; i < image->rows * image->cols; i++) {
        // converting to greyscale
        double sum = image->data[i].r * 0.3 + image->data[i].g * 0.59 + image->data[i].b * 0.11;
        unsigned char res = sum;
        Pixel grey = {res, res, res};
        image->data[i] = grey;
    }
    FILE* output_file = fopen(output, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Output file I/O error\n");
        return 3;
    }
    WritePPM(output_file, image);
    if (ferror(output_file)) {
        fprintf(stderr, "Image could not be written to output\n");
        return 3;
    }
    fclose(input_file);
    fclose(output_file);
    free(image->data);
    free(image);
    return 0;
}

int binarize(char fileReadName[], char fileWriteName[], int threshold) {
    //testing whether the threshold value is within bounds
    if (threshold < 0 || threshold > 255) {
      fprintf(stderr, "Invalid arguments for the specified operation\n");  
      return 7;
    }
    unsigned char binaryVal;
    //opening file
    FILE* file = fopen(fileReadName, "r");
    if (file == NULL || ferror(file)) {
      fprintf(stderr, "Input file I/O error\n");
      return 2;
    }
    Image* image = ReadPPM(file);
    if (image == NULL) {
      fprintf(stderr, "The Input file cannot be read as a PPM file\n");
      return 4;
    }
    for (int i = 0; i < image->rows * image->cols; i++) {
        //checking greyscale value
        double greyScale = image->data[i].r * 0.3 + image->data[i].g * 0.59 + image->data[i].b *0.11;
        if (greyScale < threshold) {
            binaryVal = 0;
        }
        else {
            binaryVal = 255;
        }
        Pixel binary = {binaryVal, binaryVal, binaryVal};
        image->data[i] = binary;
    }
    FILE* write = fopen(fileWriteName, "w");
    if (write == NULL || ferror(write)) {
      fprintf(stderr, "Output file I/O error\n");
      return 3;
    }
    WritePPM(write, image);
    if (ferror(write)) {
        fprintf(stderr, "Image could not be written to output\n");
        return 3;
    }
    fclose(file);
    fclose(write);
    free(image->data);
    free(image);
    return 0;
}

int crop(char input_file[], char output_file[], int x1, int y1, int x2, int y2) {
    FILE* file = fopen(input_file, "r");
    if (file == NULL || ferror(file)) {
        return 2;
    }
    Image* origImg = ReadPPM(file);
    if (origImg == NULL) {
        return 4;
    }
    Point upperL = {x1, y1};
    Point lowerR  = {x2, y2};

    //check if coordinates are within bounds of 2D array of pixels
    if (upperL.x < 0 || upperL.y < 0 || lowerR.x < 0 || lowerR.y < 0 ||
        upperL.x >= origImg->cols || lowerR.x > origImg->cols || upperL.y >= origImg->rows || lowerR.y > origImg->rows) {
        fprintf(stderr, "Invalid arguments for the specified operation 1\n");
        return 7;
        }
    //check if upperL preceeds lowerR
    if (x1 >= x2 - 1|| y1 >= y2 - 1) {
        fprintf(stderr, "Invalid arguments for the specified operation 2\n");
        return 7;
    }

    Image* newImg = malloc(sizeof(Image));
    newImg->rows = (lowerR.y - upperL.y);
    newImg->cols = (lowerR.x - upperL.x); 
    newImg->data = malloc(sizeof(Pixel) * newImg->rows * newImg->cols);

    int index = 0; //of new array
    for (int i = upperL.y; i < lowerR.y; i++) {
        for (int j = upperL.x; j < lowerR.x; j++) {
            newImg->data[index]= origImg->data[i * origImg->cols + j];
            index++;
        }
    }

    FILE* write = fopen(output_file, "w");
    if (write == NULL) {
        fprintf(stderr, "Output file I/O error\n");
        return 3;
    }
    WritePPM(write, newImg);
    if (ferror(write)) {
        fprintf(stderr, "Image could not be written to output\n");
        return 3;
    }
    fclose(file);
    fclose(write);
    free(origImg->data);
    free(origImg);
    free(newImg->data);
    free(newImg);
    return 0;
}

int transpose(char input[], char output[]) {
    FILE* input_file = fopen(input, "r");
    if (input_file == NULL || ferror(input_file)) {
        fprintf(stderr, "Input file I/O error\n");
        return 2;
    }
    Image* image = ReadPPM(input_file);
    if (image == NULL) {
        fprintf(stderr, "The Input file cannot be read as a PPM file\n");
        return 4;
    }
    Image* transposed_image = malloc(sizeof(Image));
    Pixel* empty = malloc(sizeof(Pixel) * image->rows * image-> cols);
    transposed_image->data = empty;
    transposed_image->cols = image->rows;
    transposed_image->rows = image->cols;
    int new_index = 0;
    for(int i = 0; i < image->cols; i++){
        for (int j = 0; j < image->rows; j++) {
            int orig_index = j * image->cols + i;
            transposed_image->data[new_index] = image->data[orig_index];
            new_index++;
        }
    }
    FILE* output_file = fopen(output, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Output file I/O error\n");
        return 3;
    }
    WritePPM(output_file, transposed_image);
    if (ferror(output_file)) {
        fprintf(stderr, "Image could not be written to output\n");
        return 3;
    }
    fclose(input_file);
    fclose(output_file);
    free(image->data);
    free(image);
    free(empty);
    free(transposed_image);
    return 0;
}

int gradient(char input[], char output[]) {
    FILE* input_file = fopen(input, "r");
    if (input_file == NULL || ferror(input_file)) {
        fprintf(stderr, "Input file I/O error\n");
        return 2;
    }
    Image* image = ReadPPM(input_file);
    if (image == NULL) {
        fprintf(stderr, "The Input file cannot be read as a PPM file\n");
        return 4;
    }
    Image* gradient_image = malloc(sizeof(Image));
    int cols = image->cols;
    int rows = image->rows;
    Pixel* empty = malloc(sizeof(Pixel) * image->rows * image->cols);
    gradient_image->data = empty;
    gradient_image->cols = cols;
    gradient_image->rows = rows;
    for (int i = 0; i < rows * cols; i++) {
        if (i < cols || i > (rows - 1) * cols - 1 || i % cols == 0 || i % cols == cols - 1) {
            Pixel gradient = {0, 0, 0};
            gradient_image->data[i] = gradient;
        }
        else {
            double x_right_rgb = image->data[i + 1].r * 0.3 + image->data[i + 1].g * 0.59 + image->data[i + 1].b * 0.11;
            double x_left_rgb = image->data[i - 1].r * 0.3 + image->data[i - 1].g * 0.59 + image->data[i - 1].b * 0.11;
            double x_gradient = (x_right_rgb - x_left_rgb) / 2;
            double y_up_rgb = image->data[i - cols].r * 0.3 + image->data[i - cols].g * 0.59 + image->data[i - cols].b * 0.11;
            double y_down_rgb = image->data[i + cols].r * 0.3 + image->data[i + cols].g * 0.59 + image->data[i + cols].b * 0.11;
            double y_gradient = (y_up_rgb - y_down_rgb) / 2;
            double magnitude = fabs(x_gradient) + fabs(y_gradient);
            Pixel gradient = {magnitude, magnitude, magnitude};                
            gradient_image->data[i] = gradient;
        }
    }
    FILE* output_file = fopen(output, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Output file I/O error\n");
        return 3;
    }
    WritePPM(output_file, gradient_image);
    if (ferror(output_file)) {
        fprintf(stderr, "Image could not be written to output\n");
        return 3;
    }
    fclose(input_file);
    fclose(output_file);
    free(image->data);
    free(image);
    free(gradient_image->data);
    free(gradient_image);
    return 0;
}

int min(int x, int y, int z) {
    int min;
    min = x;
    if (y < min) {
        min = y;
    }
    if (z < min) {
        min = z;
    }
    return min;
}

int seam(Image* image, double fact, char input[], char output[]) {
    int d = image->cols - fact; //total num of seams to remove
    int col_count = image->cols; //the number of columns in the current image
    //per iteration, remove a single vertical seam with the least gradient energy
    //input image is overwritten every iteration
    Image* temp = malloc(sizeof(Image));
    temp->data = malloc(sizeof(Pixel) * image->rows * image->cols);
    temp->cols = image->cols;
    temp->rows = image->rows;
    for (int i = 1; i <= d; i++) {
        //open generated file
        if (i == 1) {
            gradient(input, "first_seam.ppm");
            input = NULL;
        }
        else {
            gradient(output, "first_seam.ppm");
        }

        FILE* new_file = fopen("first_seam.ppm", "r");
        if (new_file == NULL || ferror(new_file)) {
            return 2;
        }
        //reread new gradient image after each iteration
        Image* gradient_image = ReadPPM(new_file);
        if (gradient_image == NULL) {
            return 4;
        }
        //each iteration checks a seam with beginning point at cth column of row 0
        int seam_path[image->rows * image->cols]; //each "column" of this fake 2D array will hold indices of a singular seam path
                                                  //notice: image, gradient_image, and seam_path have arrays of same dimensions
        int sum_gradients[col_count]; //each cell of this array contains the gradient energy of each seam
        //col_count decrements after each iteration
        for (int c = 0; c < col_count; c++) {    //r and c for structurally storing index data in seam_path array
            seam_path[c] = c; // start of seam path
            int next_seam_index;
            int gradient_energy = 0;
            int seam_c = c; //for tracking current column index of this seam path
            for (int r = 1; r < image->rows - 1; r++) {
                //special cases
                //skip checking min gradient
                if (r == image->rows - 2) { //when reaching lower boundary
                    next_seam_index = r * image->cols + seam_c;
                }
                else if (seam_c == 0) { // left boudnary
                    next_seam_index = r * image->cols + 1;
                    seam_c += 1;
                }
                else if (seam_c == col_count - 1) { //right boundary
                    next_seam_index = r * image->cols + seam_c - 1;
                    seam_c -= 1;
                }
                else {
                    //find the neighboring min gradient in this row
                    double right_mag = gradient_image->data[r * image->cols + seam_c + 1].b;
                    double left_mag = gradient_image->data[r * image->cols + seam_c - 1].b;
                    // setting second to last and second columns to high numbers so the boundaries aren't counted
                    if (seam_c == 1) {
                        left_mag = 1000000;
                    }
                    else if (seam_c == col_count - 2) {
                        right_mag = 1000000;
                    }
                    double current_mag = gradient_image->data[r * image->cols + seam_c].b;
                    double least_mag = min(right_mag, left_mag, current_mag);
                    // shift seam path left, right, or down depending on minimum
                    if (least_mag == right_mag) {
                        next_seam_index = r * image->cols + seam_c + 1;
                        seam_c += 1;
                    }
                    else if (least_mag == left_mag) {
                        next_seam_index = r * image->cols + seam_c - 1;
                        seam_c -= 1;
                    }
                    else if (least_mag == current_mag) {
                        next_seam_index = r * image->cols + seam_c;
                    }
                }
                 //allocate index of gradient_image as part of seam path
                seam_path[r * image->cols + c] = next_seam_index;
                gradient_energy += gradient_image->data[next_seam_index].b;
            }
             //allocate gradient energy to an array
            sum_gradients[c] = gradient_energy;
        }
         //find the min path in gradient energy array
        int min = sum_gradients[0];
        int min_index = 0;
        for (int i = 0; i < col_count; i++) {
            if (sum_gradients[i] < min) {
                min = sum_gradients[i];
                min_index = i;
            }
        }
        int seam_counter = 0; //for iterating through seam_path down the column
        int seam_col_counter = 1;
        for (int i = 0; i < image->cols * image->rows; i++) { //i is index of image
            if (i == seam_path[min_index + (image->cols * seam_counter)]) { // if i contains an index to be removed
                seam_counter++;
                for (int j = i; j < seam_col_counter * image->cols; j++) { //shift pixels to the right of seam left so the image can be cropped later
                    temp->data[j] = image->data[j+1];
                }
                i = seam_col_counter * image->cols - 1; //skip to next row
                seam_col_counter++;
            }
            else { // if not part of seam or after seam, just copy directly
                temp->data[i] = image->data[i];
            }
        }
        col_count--; //decrement column number
        image = temp;
        FILE* file = fopen(output, "w"); //modify image of input file
        WritePPM(file, image);
        fclose(file);
        fclose(new_file);
        free(gradient_image->data);
	    free(gradient_image);
        remove("first_seam.ppm");
    }
    return 0;
}
