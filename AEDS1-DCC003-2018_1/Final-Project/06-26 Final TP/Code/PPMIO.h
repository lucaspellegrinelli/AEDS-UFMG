/*
  Autor: Lucas Pellegrinelli
  Data: 07/05/2018
*/

/*
	Nesse código teremos a definição de todos os métodos/funções responsáveis
	pela leitura e escrita de arquivos tipo PPM (ASCII, P3)
*/

/*
  Struct com função de armazenar as informações de uma imagem PPM
*/
struct Image{
	int width;
	int height;
	char **header;
	int **pixels; // Linha: Cada pixel.    Coluna: Cada valor RGB
};

/*
  Lê a imagem PPM (ASCII, P3) informada e a armazena em um struct Image

  Entrada:
  'path' -> Caminho para o arquivo da imagem

  Saída:
  'return' -> struct Image com os pixels, dimensões e headers da imagem
*/
struct Image read_image(char *path);

/*
  Salva uma imagem tipo struct Image como um arquivo de imagem PPM (ASCII, P3)

  Entrada:
   image -> stuct Image com as informações da imagem a ser salva
	 output_name -> Nome que a imagem terá ao ser salva
*/
void write_image(struct Image image, char *output_name);
