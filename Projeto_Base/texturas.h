#ifndef TEXTURAS_H_INCLUDED
#define TEXTURAS_H_INCLUDED

void init() {

    Fundo = SOIL_load_OGL_texture (
    "Fundo.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );
/*
    Arvore = SOIL_load_OGL_texture (
    "Fundo_Arvore.gif",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );
*/
    CachorroAnda.Dog_Texture[0] = SOIL_load_OGL_texture (
    "Dog_Walk1.png",
    SOIL_LOAD_RGBA,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );

    CachorroAnda.Dog_Texture[1] = SOIL_load_OGL_texture (
    "Dog_Walk2.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );

    CachorroAnda.Dog_Texture[2] = SOIL_load_OGL_texture (
    "Dog_Walk3.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );

    CachorroAnda.Dog_Texture[3] = SOIL_load_OGL_texture (
    "Dog_Sniff1.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );

    CachorroAnda.Dog_Texture[4] = SOIL_load_OGL_texture (
    "Dog_Sniff2.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );

    CachorroAnda.Dog_Texture[5] = SOIL_load_OGL_texture (
    "Dog_Jump1.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );

    CachorroAnda.Dog_Texture[6] = SOIL_load_OGL_texture (
    "Dog_Jump2.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
    );


  if (Fundo == 0 ) {
    printf("Erro ao carregar textura: '%s'\n", SOIL_last_result());
  }
  /*if (Arvore == 0 ) {
    printf("Erro ao carregar textura: '%s'\n", SOIL_last_result());
  }

*/
  if (CachorroAnda.Dog_Texture[4] == 0){
        printf("Erro ao carregar textura: '%s'\n", SOIL_last_result());
  }
}


#endif // TEXTURAS_H_INCLUDED
