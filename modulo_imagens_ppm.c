#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modulo_estruturas.h"
#include "modulo_imagens_ppm.h"


//**************************************************************************
// IMAGEM - CRIAR MATRIZ
//**************************************************************************

void criarMatrizPixeis(pontImagem Imagem) {
  int i;
  Imagem->pix_imagem = (pixel **)malloc(Imagem->linhas * sizeof(pixel *));
  for (i = 0; i < Imagem->linhas; i++) {
    Imagem->pix_imagem[i] = (pixel *)malloc(Imagem->colunas * sizeof(pixel));
  } // end-for
}

//**************************************************************************
// IMAGEM - LEITURA
//**************************************************************************
void lerImagem(pontImagem Imagem, FILE *imagem, char *nomeArquivo) {
  int i, j;
  imagem = fopen(nomeArquivo, "rb");

  if (imagem == NULL) {
    printf("Houve um erro ao abrir a imagem\n");
    exit(1);
  }

  fscanf(imagem, "%s", Imagem->codigo);
  fscanf(imagem, "%i", &Imagem->colunas);
  fscanf(imagem, "%i", &Imagem->linhas);
  criarMatrizPixeis(Imagem);
  fscanf(imagem, "%i", &Imagem->maxval);

  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      fscanf(imagem, "%c", &Imagem->pix_imagem[i][j].red);
      fscanf(imagem, "%c", &Imagem->pix_imagem[i][j].green);
      fscanf(imagem, "%c", &Imagem->pix_imagem[i][j].blue);
    } // end-for
  }   // end-for

  fclose(imagem);
}

//**************************************************************************
// IMAGEM - SALVAR + CORES
//**************************************************************************

void salvarImagem(pontImagem Imagem, FILE *imagem, char *nomeArquivo) {
  int i, j;
  char nome_imagem[100];

  imagem = fopen(nomeArquivo, "wb");

  fprintf(imagem, "%s\n", Imagem->codigo); // p6
  fprintf(imagem, "%i ", Imagem->colunas); // 100
  fprintf(imagem, "%i\n", Imagem->linhas); // 100
  fprintf(imagem, "%i\n\n\n", Imagem->maxval);
  //fprintf(imagem, "%i\n", Imagem->maxval); // 255

  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      fprintf(imagem, "%c", Imagem->pix_imagem[i][j].red);
      fprintf(imagem, "%c", Imagem->pix_imagem[i][j].green);
      fprintf(imagem, "%c", Imagem->pix_imagem[i][j].blue);
    } // end-for
  }   // end-for
  fclose(imagem);
  free(Imagem->pix_imagem);
} 

void salvarImagemCores(pontImagem Imagem, FILE *imagem, char *nomeArquivo) {
  int i, j;
  char nome_imagem[100];

  imagem = fopen(nomeArquivo, "wb");

  fprintf(imagem, "%s\n", Imagem->codigo); // p6
  fprintf(imagem, "%i ", Imagem->colunas); // 100
  fprintf(imagem, "%i\n", Imagem->linhas); // 100
  fprintf(imagem, "%i\n\n\n\n", Imagem->maxval);
  //fprintf(imagem, "%i\n", Imagem->maxval); // 255

  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      fprintf(imagem, "%c", Imagem->pix_imagem[i][j].red);
      fprintf(imagem, "%c", Imagem->pix_imagem[i][j].green);
      fprintf(imagem, "%c", Imagem->pix_imagem[i][j].blue);
    } // end-for
  }   // end-for
  fclose(imagem);
  free(Imagem->pix_imagem);
} 


//**************************************************************************
//         IMAGEM - GIRAR 90° -
//**************************************************************************
void rotacionar(pontImagem Imagem) {
  int i, j, l;

  imagem ImagemLoc;
  ImagemLoc.linhas = Imagem->colunas;
  ImagemLoc.colunas = Imagem->linhas;
  criarMatrizPixeis(&ImagemLoc);

  for (j = Imagem->colunas - 1, l = 0; l < Imagem->linhas && j >= 0; j--, l++) {
    for (i = 0; i < Imagem->linhas; i++) {
      ImagemLoc.pix_imagem[l][i] = Imagem->pix_imagem[i][j];
    }
  }

  free(Imagem->pix_imagem);
  Imagem->pix_imagem = ImagemLoc.pix_imagem;
  Imagem->colunas = ImagemLoc.colunas;
  Imagem->linhas = ImagemLoc.linhas;
}

//**************************************************************************
// IMAGEM - AMPLIAR
//**************************************************************************

void ampliarImagem(pontImagem Imagem,int aumentar){
	int i, j, k, l;

	imagem ImagemLoc;
	ImagemLoc.linhas = Imagem->linhas * aumentar;
	ImagemLoc.colunas = Imagem->colunas * aumentar;
	criarMatrizPixeis(&ImagemLoc);

	for(i = 0, k = 0; i < Imagem->linhas && k < ImagemLoc.linhas; k ++){
		if(k % aumentar == 0 && k != 0){
			i++;
		}
		for(j = 0, l = 0; j < Imagem->colunas && l < ImagemLoc.colunas;  l++){
			if(l % aumentar == 0 && l != 0){
				j++;
			}
			ImagemLoc.pix_imagem[k][l] = Imagem->pix_imagem[i][j];
		}
	}
	free(Imagem->pix_imagem);
	Imagem->linhas = ImagemLoc.linhas;
	Imagem->colunas = ImagemLoc.colunas;
	Imagem->pix_imagem = ImagemLoc.pix_imagem;
}


//**************************************************************************
// IMAGEM - ESPELHAR HORIZONTAL - ->FILTRO GRUPO<-
//**************************************************************************

void espelhar(pontImagem Imagem) {
  int i, j, l;

  imagem ImagemLoc;
  ImagemLoc.linhas = Imagem->linhas;
  ImagemLoc.colunas = Imagem->colunas;
  criarMatrizPixeis(&ImagemLoc);

  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0, l = Imagem->colunas - 1; j < Imagem->colunas && l >= 0;
         j++, l--) {
      ImagemLoc.pix_imagem[i][l] = Imagem->pix_imagem[i][j];
    }
  }
  free(Imagem->pix_imagem);
  Imagem->pix_imagem = ImagemLoc.pix_imagem;
}

//**************************************************************************
// IMAGEM - REDUZIR
//**************************************************************************

void reduzir(pontImagem Imagem, int reducao) {
  int i, j, k, l;

  imagem ImagemLoc;

  if (reducao == 1) {
    ImagemLoc.linhas = Imagem->linhas;
    ImagemLoc.colunas = Imagem->colunas;
    criarMatrizPixeis(&ImagemLoc);

  } else {
    ImagemLoc.linhas = Imagem->linhas / reducao;
    ImagemLoc.colunas = Imagem->colunas / reducao;
    criarMatrizPixeis(&ImagemLoc);
  }

  for (i = 0, k = 1; i < ImagemLoc.linhas && k < Imagem->linhas; i++, k += 2) {
    for (j = 0, l = 1; j < ImagemLoc.colunas && l < Imagem->colunas;j++, l += 2) {
      ImagemLoc.pix_imagem[i][j].red = (Imagem->pix_imagem[k - 1][l - 1].red + Imagem->pix_imagem[k - 1][l].red + Imagem->pix_imagem[k][l - 1].red + Imagem->pix_imagem[k][l].red) / 4;
      ImagemLoc.pix_imagem[i][j].green = (Imagem->pix_imagem[k - 1][l - 1].green + Imagem->pix_imagem[k - 1][l].green + Imagem->pix_imagem[k][l - 1].green + Imagem->pix_imagem[k][l].green) / 4;
      ImagemLoc.pix_imagem[i][j].blue = (Imagem->pix_imagem[k - 1][l - 1].blue + Imagem->pix_imagem[k - 1][l].blue + Imagem->pix_imagem[k][l - 1].blue + Imagem->pix_imagem[k][l].blue) /4;
    }
  }
  free(Imagem->pix_imagem);
  Imagem->linhas = ImagemLoc.linhas;
  Imagem->colunas = ImagemLoc.colunas;
  Imagem->pix_imagem = ImagemLoc.pix_imagem;
}

//**************************************************************************
// IMAGEM - NEGATIVO
//**************************************************************************

void negativo(pontImagem Imagem) {
  int i, j;
  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      Imagem->pix_imagem[i][j].red = 255 - Imagem->pix_imagem[i][j].red;
      Imagem->pix_imagem[i][j].green = 255 - Imagem->pix_imagem[i][j].green;
      Imagem->pix_imagem[i][j].blue = 255 - Imagem->pix_imagem[i][j].blue;
    } // end-for
  }   // end-for
}

//**************************************************************************
// IMAGEM - ESCALA CINZA
//**************************************************************************

void escalaCinza(pontImagem Imagem) {
  int i, j;
  int mediaCores;
  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      mediaCores =
          (Imagem->pix_imagem[i][j].red + Imagem->pix_imagem[i][j].green +
           Imagem->pix_imagem[i][j].blue) /
          3;
      Imagem->pix_imagem[i][j].red = mediaCores;
      Imagem->pix_imagem[i][j].green = mediaCores;
      Imagem->pix_imagem[i][j].blue = mediaCores;
    } // end-for
  }   // end-for

} // end-sub

//**************************************************************************
// IMAGEM - REMOVER VERMELHO
//**************************************************************************

void removerCorVermelha(pontImagem Imagem) {
  int i, j;
  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      Imagem->pix_imagem[i][j].red = 0;

    } // end-for
  }   // end-for
}

//**************************************************************************
// IMAGEM - REMOVER VERDE
//**************************************************************************
void removerCorVerde(pontImagem Imagem) {
  int i, j;
  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      Imagem->pix_imagem[i][j].green = 0;
    } // end-for
  }   // end-for
}

//**************************************************************************
// IMAGEM - REMOVER AZUL
//**************************************************************************

void removerCorAzul(pontImagem Imagem) {
  int i, j;
  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      Imagem->pix_imagem[i][j].blue = 0;
    } // end-for
  }   // end-for
}

//**************************************************************************
// IMAGEM - REMOVER VERMELHO/VERDE
//**************************************************************************

void removerCorVermelhoVerde(pontImagem Imagem) {
  int i, j;
  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      Imagem->pix_imagem[i][j].red = 0;
      Imagem->pix_imagem[i][j].green = 0;
    } // end-for
  }   // end-for
}

//**************************************************************************
// IMAGEM - REMOVER VERMELHO/AZUL
//**************************************************************************

void removerCorVermelhoAzul(pontImagem Imagem) {
  int i, j;
  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      Imagem->pix_imagem[i][j].red = 0;
      Imagem->pix_imagem[i][j].blue = 0;
    } // end-for
  }   // end-for
}

//**************************************************************************
// IMAGEM - REMOVER VERDE/AZUL
//**************************************************************************
void removerCorVerdeAzul(pontImagem Imagem) {
  int i, j;
  for (i = 0; i < Imagem->linhas; i++) {
    for (j = 0; j < Imagem->colunas; j++) {
      Imagem->pix_imagem[i][j].green = 0;
      Imagem->pix_imagem[i][j].blue = 0;
    } // end-for
  }   // end-for

} // end-sub........................................................

