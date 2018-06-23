/*
  Autor: Lucas Pellegrinelli
  Data: 07/05/2018
*/

/*
	Nesse código teremos a definição de todos os métodos/funções responsáveis
	pela leitura e escrita de arquivos tipo PPM (ASCII, P3)
*/

struct Image{
	int width;
	int height;
	char **header;
	int **pixels; // Linha: Cada pixel.    Coluna: Cada valor RGB
};

struct Image read_image(char *path);

void write_image(struct Image image, char *output_name);
