#ifndef MODULO_ESTRUTURAS_H
#define MODULO_ESTRUTURAS_H

//**************************************************************************
// Struct que define os elementos r, g e b de cada pixel
//**************************************************************************
typedef struct {
  int red;
  int green;
  int blue;
} pixel;

//**************************************************************************
// Struct de imagem para a matriz de pixel
//**************************************************************************
typedef struct {
  pixel **pix_imagem;
  char codigo[3];
  int maxval, colunas, linhas;
} imagem, *pontImagem;

#endif
