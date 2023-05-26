#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modulo_estruturas.h"
#include "modulo_imagens_ppm.h"

int main(int argc, char *argv[]) {

  char nome[30];
  char saidaArgv4[30]; //nome da nova imagem
  char saidaArgv5[30];

  int qtdParamentro = 0;
  qtdParamentro = argc;

  int valorRotacao;

  strcpy(nome, argv[1]);

  imagem IMAGE;
  FILE *imagem;

  lerImagem(&IMAGE, imagem, nome);

  if (qtdParamentro == 4) {
    strcpy(saidaArgv4, argv[3]);
    //-------------------------------------------------------
    if (strcmp(argv[2], "cinza") == 0) {
      // ./main rainha.ppm cinza cinzaRainha.ppm
      escalaCinza(&IMAGE);
      salvarImagem(&IMAGE, imagem, saidaArgv4);
    } // end if cinza
      //-------------------------------------------------------
    else if (strcmp(argv[2], "inverte") == 0) {
      negativo(&IMAGE);
      salvarImagem(&IMAGE, imagem, saidaArgv4);
    } // end if else inverte

    else if (strcmp(argv[2], "filtro") == 0) {
      espelhar(&IMAGE);
      salvarImagem(&IMAGE, imagem, saidaArgv4);
    } // end if else filtro
    else
      printf("Erro 1");
    //---------------------------------------------------

  } // end if qtdParamento 4
  //=========================================================
  else if (qtdParamentro == 5) {
    strcpy(saidaArgv5, argv[4]);

    if (strcmp(argv[2], "red") == 0) {
      int valorRed = atoi(argv[3]);
      reduzir(&IMAGE, valorRed);
      salvarImagem(&IMAGE, imagem,saidaArgv5);

    }
    //-------------------------------------------------------
    else if (strcmp(argv[2], "amp") == 0) {
      int aumento = atoi(argv[3]);
      ampliarImagem(&IMAGE,aumento);
      salvarImagem(&IMAGE, imagem,saidaArgv5);

    } // end if red
      //-------------------------------------------------------
    else if (strcmp(argv[2], "rot") == 0) {
      valorRotacao = atoi(argv[3]);

      if (valorRotacao == 90) {
        rotacionar(&IMAGE);
        rotacionar(&IMAGE);
        rotacionar(&IMAGE);
        salvarImagem(&IMAGE, imagem,saidaArgv5);

      } // end if 90
      //.........................................
      else if (valorRotacao == 180) {
        rotacionar(&IMAGE);
        rotacionar(&IMAGE);
        salvarImagem(&IMAGE, imagem,saidaArgv5);

      } // end if 180
      //.........................................
      else if (valorRotacao == 270) {
        rotacionar(&IMAGE);
        salvarImagem(&IMAGE, imagem,saidaArgv5);

      } else
        printf("Erro no rot");
      // } // end else
    } // end if rot

    // //=========================================================
    else if (strcmp(argv[2], "remove") == 0) {

      if (strcmp(argv[3], "r") == 0) {
        removerCorVermelha(&IMAGE);
          salvarImagemCores(&IMAGE, imagem,saidaArgv5);
      } // end if remove r
      //---------------------------------------------------
      else if (strcmp(argv[3], "g") == 0) {
        removerCorVerde(&IMAGE);
        salvarImagemCores(&IMAGE, imagem,saidaArgv5);

      } // end if remove g
      //--------------------------------------------------

      else if (strcmp(argv[3], "b") == 0) {
        removerCorAzul(&IMAGE);
        salvarImagemCores(&IMAGE, imagem,saidaArgv5);
        
      } // end if remove b
      //--------------------------------------------------
      else if (strcmp(argv[3], "rg") == 0) {
        removerCorVermelhoVerde(&IMAGE);
        salvarImagemCores(&IMAGE, imagem,saidaArgv5);
      } // end if remove rg
      //--------------------------------------------------
      else if (strcmp(argv[3], "rb") == 0) {
        removerCorVermelhoAzul(&IMAGE);
        salvarImagemCores(&IMAGE, imagem,saidaArgv5);        
      } // end if remove rg
      //--------------------------------------------------
      else if (strcmp(argv[3], "gb") == 0) {
        removerCorVerdeAzul(&IMAGE);
        salvarImagemCores(&IMAGE, imagem,saidaArgv5);        
      } // end if remove gb
      //--------------------------------------------------
      else
        printf("erro");

    } // end else if remove
    //-------------------------------------------------------
  } // end if argc == 5

  else
    printf("Erro");

  return 0;
}