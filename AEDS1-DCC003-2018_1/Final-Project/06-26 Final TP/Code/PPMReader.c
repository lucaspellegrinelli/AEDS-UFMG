#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "PPMReader.h"

Image read_image(char *path){
	Image output;

	FILE *image_file = fopen(path, 'r');

	// Todo
	int image_width = 100;
	int image_height = 100;


	int pixels[image_width * image_height][3];

	for (int i = 0; i < image_width * image_height; pixel++) {
		int number_of_rbg_comp_read = fscanf(image_file, "%d %d %d", &pixels[i][0], &pixels[i][1], &pixels[i][2]);
		if (number_of_rbg_comp_read < 3) break;
	}

	output.width = image_width;
	output.height = image_height;
	output.pixels = pixels;

	fclose(image_file);

	return output;
}

void write_image(struct Image image, char *output_name){

}