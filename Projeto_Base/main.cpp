#include <SOIL.h>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "posicao.h"
#include <time.h>


struct MovimentoCachorro{
    GLuint Dog_Texture[11];//vetor de texturas
};

struct MovimentoPato{
    GLuint Duck_Texture[36]; //vetor de textura dos patos
};

struct TamanhoText{
    float altura,largura;
};

struct IconePato{
    GLuint patinho[2];
    int cor = 0;

};

int NumTextCachorro = 0, NumTextPato = 3;

int contadorcheiradas=0,NumPatos=0,PatosMortos = 0,voa = 0,acao = 0,NumErros = 0,NumTiros = 0,MostraPato = 1, TempoMostra = 0;

int CorDoPato = rand()%3, timer =0, risada = 0,acertaParto = 0;
int CorDoIcone[11];
int GameOver = 0;
int Nivel = 1;
char nivelChar[10];

float VelocidadeHorizontal = rand()%1 + 1 , VelocidadeVertical = rand()%1 +1;

int Pausa = 1;
int Tela = 0; // DEFINE O QUE MOSTRAR NA TELA, 0=MENU, 1=JOGO, 2=PAUSA, 3=CREDITOS
int PiscaIcone = 0;
int Score = 0;
char scoreChar[10];
int clique = 0;
int conversor = 0;
int fundo_pos_tiro;
int acertou = 0; // indicador se o pato foi acertado

int i,j,aux;

float ConstanteH = 1, ConstanteV = 1;
struct ponto PosicaoMouse;
struct ponto Tiro;
struct ponto TexturaDogwalk;
struct ponto TexturaDuckPos;
struct ponto IconeDuck[11];
struct ponto BotaoStart;
struct ponto Botao_Creditos;
struct MovimentoCachorro CachorroAnda;
struct TamanhoText TextCachorroA;
struct TamanhoText TexturaPatoTam;
struct TamanhoText StartButtom;
struct TamanhoText creditosBotao;
struct MovimentoPato Patomove;

struct IconePato Icone[11];

GLint andaCachorro = 0, cheiracachorro = 0;

GLuint Fundo, Menu, Press_Start , Tiro1 , Tiro2, Tiro3, Flyaway, Game_Over, Pause, Perfect, BotaoCreditos, Creditos;
GLuint IndicadorAzul6, IndicadorAzul7,IndicadorAzul8,IndicadorAzul9,IndicadorAzul10;   // id de textura

void cachorro_anda(int idx);
void pato_voa_azul(int idx);
void pato_voa_preto(int idx);
void pato_voa_vermelho(int idx);
void atualiza(int idx);
void pato_morre_azul(void);
void pato_morre_preto(void);
void pato_morre_vermelho(void);
void mostra_pato(void);
void pato_escapa_azul(void);
void pato_escapa_preto(void);
void pato_escapa_vermelho(void);
void cachorro_ri(void);
void analisaNivel(void);
void piscaTela(void);

void inicializa(){ // INICIA OS DADOS DE ALGUMAS VARIAVEIS
    glClearColor(0.3,0.734,1.0,0);

    IconeDuck[1].z = 1;
    IconeDuck[2].z = 1;
    IconeDuck[3].z = 1;
    IconeDuck[4].z = 1;
    IconeDuck[5].z = 1;
    IconeDuck[6].z = 1;
    IconeDuck[7].z = 1;
    IconeDuck[8].z = 1;
    IconeDuck[9].z = 1;
    IconeDuck[10].z = 1;

    CorDoIcone[1] = 0;
    CorDoIcone[2] = 0;
    CorDoIcone[3] = 0;
    CorDoIcone[4] = 0;
    CorDoIcone[5] = 0;
    CorDoIcone[6] = 0;
    CorDoIcone[7] = 0;
    CorDoIcone[8] = 0;
    CorDoIcone[9] = 0;
    CorDoIcone[10] = 0;


    BotaoStart.x = 55;
    BotaoStart.y = 20;
    BotaoStart.z = 1;
    StartButtom.altura = 25;
    StartButtom.largura = 90;

    Botao_Creditos.x = 160;
    Botao_Creditos.y = 10;
    Botao_Creditos.z = 1;
    creditosBotao.altura = 20;
    creditosBotao.largura = 30;

    TextCachorroA.altura = 32,5;
    TextCachorroA.largura = 45;
    TexturaDogwalk.x = 0;
    TexturaDogwalk.y = 37.5;
    TexturaDogwalk.z = 1;

    TexturaDuckPos.x = rand()% 165;
    TexturaDuckPos.y = 50;
    TexturaDuckPos.z = -1;
    TexturaPatoTam.altura = 21;
    TexturaPatoTam.largura = 32;
}

void init() { // CARREGA TEXTURAS

    BotaoCreditos = SOIL_load_OGL_texture (
        "Botao_Creditos.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Creditos = SOIL_load_OGL_texture (
        "Creditos.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Perfect = SOIL_load_OGL_texture (
        "Perfect.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    IndicadorAzul10 = SOIL_load_OGL_texture (
        "Indicador_Azul_1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    IndicadorAzul9 = SOIL_load_OGL_texture (
        "Indicador_Azul_1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    IndicadorAzul8 = SOIL_load_OGL_texture (
        "Indicador_Azul_1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    IndicadorAzul7 = SOIL_load_OGL_texture (
        "Indicador_Azul_1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    IndicadorAzul6 = SOIL_load_OGL_texture (
        "Indicador_Azul_6.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Menu = SOIL_load_OGL_texture (
        "Menu.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Press_Start = SOIL_load_OGL_texture (
        "Start.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Pause = SOIL_load_OGL_texture (
        "Pause.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Game_Over = SOIL_load_OGL_texture (
        "GameOver.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Icone[0].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[0].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[1].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[1].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[2].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[2].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[3].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[3].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[4].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[4].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[5].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[5].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[6].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[6].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[7].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[7].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[8].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[8].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[9].patinho[0] = SOIL_load_OGL_texture (
        "Icone_Branco.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Icone[9].patinho[1] = SOIL_load_OGL_texture (
        "Icone_Vermelho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Flyaway = SOIL_load_OGL_texture (
        "FlyAway.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Tiro1 = SOIL_load_OGL_texture (
        "Tiro.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Tiro2 = SOIL_load_OGL_texture (
        "Tiro.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Tiro3 = SOIL_load_OGL_texture (
        "Tiro.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    Fundo = SOIL_load_OGL_texture (
        "Fundo.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

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
        "Dog_Find.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    CachorroAnda.Dog_Texture[6] = SOIL_load_OGL_texture (
        "Dog_Jump1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    CachorroAnda.Dog_Texture[7] = SOIL_load_OGL_texture (
        "Dog_Jump2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    CachorroAnda.Dog_Texture[8]= SOIL_load_OGL_texture (
        "Dead_Duck1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    CachorroAnda.Dog_Texture[9]= SOIL_load_OGL_texture (
        "Dog_Laugh1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    CachorroAnda.Dog_Texture[10]= SOIL_load_OGL_texture (
        "Dog_Laugh2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );


    Patomove.Duck_Texture[0]= SOIL_load_OGL_texture (
        "BlueDuck_Hor1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[1]= SOIL_load_OGL_texture (
        "BlueDuck_Hor2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[2]= SOIL_load_OGL_texture (
        "BlueDuck_Hor3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[3]= SOIL_load_OGL_texture (
        "BlueDuck_Diag1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[4]= SOIL_load_OGL_texture (
        "BlueDuck_Diag2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[5]= SOIL_load_OGL_texture (
        "BlueDuck_Diag3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[6]= SOIL_load_OGL_texture (
        "BlueDuck_Up1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[7]= SOIL_load_OGL_texture (
        "BlueDuck_Up2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[8]= SOIL_load_OGL_texture (
        "BlueDuck_Up3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[9]= SOIL_load_OGL_texture (
        "BlueDuck_Dies1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[10]= SOIL_load_OGL_texture (
        "BlueDuck_Dies2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[11]= SOIL_load_OGL_texture (
        "BlueDuck_Dies3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[12]= SOIL_load_OGL_texture (
        "BlackDuck_Hor1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[13]= SOIL_load_OGL_texture (
        "BlackDuck_Hor2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[14]= SOIL_load_OGL_texture (
        "BlackDuck_Hor3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[15]= SOIL_load_OGL_texture (
        "BlackDuck_Diag1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[16]= SOIL_load_OGL_texture (
        "BlackDuck_Diag2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[17]= SOIL_load_OGL_texture (
        "BlackDuck_Diag3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[18]= SOIL_load_OGL_texture (
        "BlackDuck_Up1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[19]= SOIL_load_OGL_texture (
        "BlackDuck_Up2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[20]= SOIL_load_OGL_texture (
        "BlackDuck_Up3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[21]= SOIL_load_OGL_texture (
        "BlackDuck_Dies1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[22]= SOIL_load_OGL_texture (
        "BlackDuck_Dies2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[23]= SOIL_load_OGL_texture (
        "BlackDuck_Dies3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[24]= SOIL_load_OGL_texture (
        "RedDuck_Hor1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[25]= SOIL_load_OGL_texture (
        "RedDuck_Hor2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[26]= SOIL_load_OGL_texture (
        "RedDuck_Hor3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[27]= SOIL_load_OGL_texture (
        "RedDuck_Diag1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[28]= SOIL_load_OGL_texture (
        "RedDuck_Diag2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[29]= SOIL_load_OGL_texture (
        "RedDuck_Diag3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[30]= SOIL_load_OGL_texture (
        "RedDuck_Up1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[31]= SOIL_load_OGL_texture (
        "RedDuck_Up2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[32]= SOIL_load_OGL_texture (
        "RedDuck_Up3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[33]= SOIL_load_OGL_texture (
        "RedDuck_Dies1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[34]= SOIL_load_OGL_texture (
        "RedDuck_Dies2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    Patomove.Duck_Texture[35]= SOIL_load_OGL_texture (
        "RedDuck_Dies3.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );


  if (Fundo == 0 ) {
    printf("Erro ao carregar textura: '%s'\n", SOIL_last_result());
  }

  if (Pause == 0){
        printf("Erro ao carregar textura: '%s'\n", SOIL_last_result());
  }
}

void escreveTexto(void * font, char *s, float x, float y, float z){
    int p;
    glRasterPos3f(x, y, z);
    for (p=0; p < strlen(s); p++)
       glutBitmapCharacter(font, s[p]);
    glColor3f(1,1,1);
}

void desenha(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER,0);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);

    if(Tela == 0){ //EXIBE A TELA DE MENU E OS BOT�ES
        glBindTexture(GL_TEXTURE_2D, Menu);
            glBegin(GL_QUADS);
                // Associamos um canto da textura para cada v�rtice
                glTexCoord2f(0, 0); glVertex3f(0,0, 0);
                glTexCoord2f(1, 0); glVertex3f( 200,0, 0);
                glTexCoord2f(1, 1); glVertex3f( 200, 200, 0);
                glTexCoord2f(0, 1); glVertex3f(0, 200, 0);
            glEnd();

        glBindTexture(GL_TEXTURE_2D, Press_Start);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(BotaoStart.x,BotaoStart.y, BotaoStart.z);
                glTexCoord2f(1, 0); glVertex3f(BotaoStart.x + StartButtom.largura,BotaoStart.y, BotaoStart.z);
                glTexCoord2f(1, 1); glVertex3f(BotaoStart.x + StartButtom.largura, BotaoStart.y + StartButtom.altura, BotaoStart.z);
                glTexCoord2f(0, 1); glVertex3f(BotaoStart.x, BotaoStart.y + StartButtom.altura, BotaoStart.z);
            glEnd();

        glBindTexture(GL_TEXTURE_2D, BotaoCreditos);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(Botao_Creditos.x,Botao_Creditos.y,Botao_Creditos.z);
                glTexCoord2f(1, 0); glVertex3f(Botao_Creditos.x + creditosBotao.largura , Botao_Creditos.y ,Botao_Creditos.z);
                glTexCoord2f(1, 1); glVertex3f(Botao_Creditos.x + creditosBotao.largura, Botao_Creditos.y + creditosBotao.altura, Botao_Creditos.z);
                glTexCoord2f(0, 1); glVertex3f(Botao_Creditos.x,Botao_Creditos.y + creditosBotao.altura , Botao_Creditos.z);
            glEnd();
    }

    if(Pausa == -1){
        glBindTexture(GL_TEXTURE_2D, Pause); //PLACA PAUSE
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(80,140, 1);
                glTexCoord2f(1, 0); glVertex3f( 120,140, 1);
                glTexCoord2f(1, 1); glVertex3f( 120, 165, 1);
                glTexCoord2f(0, 1); glVertex3f(80, 165, 1);
            glEnd();
    }


    if(Tela == 1 || Tela == 2){ // TELA DO JOGO - DESENHA TUDO O QUE ESTAR� PRESENTE NO GAMEPLAY
        glColor3f(1,1,1);

        glBindTexture(GL_TEXTURE_2D, IndicadorAzul6);
        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(70, 10, 1);
            glTexCoord2f(1, 0); glVertex3f(110, 10, 1);
            glTexCoord2f(1, 1); glVertex3f(110, 15, 1);
            glTexCoord2f(0, 1); glVertex3f(70, 15, 1);
        glEnd();

        if(Nivel >5){
            glBindTexture(GL_TEXTURE_2D, IndicadorAzul7);
            glBegin(GL_QUADS);

                glTexCoord2f(0, 0); glVertex3f(111, 10, 1);
                glTexCoord2f(1, 0); glVertex3f(117, 10, 1);
                glTexCoord2f(1, 1); glVertex3f(117, 15, 1);
                glTexCoord2f(0, 1); glVertex3f(111, 15, 1);
            glEnd();
        }
        if(Nivel >10){
            glBindTexture(GL_TEXTURE_2D, IndicadorAzul8);
            glBegin(GL_QUADS);

                glTexCoord2f(0, 0); glVertex3f(118, 10, 1);
                glTexCoord2f(1, 0); glVertex3f(124, 10, 1);
                glTexCoord2f(1, 1); glVertex3f(124, 15, 1);
                glTexCoord2f(0, 1); glVertex3f(118, 15, 1);
            glEnd();
        }
        if(Nivel >15){
            glBindTexture(GL_TEXTURE_2D, IndicadorAzul9);
            glBegin(GL_QUADS);

                glTexCoord2f(0, 0); glVertex3f(125, 10, 1);
                glTexCoord2f(1, 0); glVertex3f(131, 10, 1);
                glTexCoord2f(1, 1); glVertex3f(131, 15, 1);
                glTexCoord2f(0, 1); glVertex3f(125, 15, 1);
            glEnd();
        }
        if(Nivel >20){
            glBindTexture(GL_TEXTURE_2D, IndicadorAzul10);
            glBegin(GL_QUADS);

                glTexCoord2f(0, 0); glVertex3f(132, 10, 1);
                glTexCoord2f(1, 0); glVertex3f(138, 10, 1);
                glTexCoord2f(1, 1); glVertex3f(138, 15, 1);
                glTexCoord2f(0, 1); glVertex3f(132, 15, 1);
            glEnd();
        }
        if(PatosMortos == 10){
            glBindTexture(GL_TEXTURE_2D, Perfect); // PLACA PERFECT
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(80,140, 1);
                glTexCoord2f(1, 0); glVertex3f( 120,140, 1);
                glTexCoord2f(1, 1); glVertex3f( 120, 165, 1);
                glTexCoord2f(0, 1); glVertex3f(80, 165, 1);
            glEnd();

        }
        glColor3f(0.2,1,0.2);
        escreveTexto(GLUT_BITMAP_HELVETICA_18,nivelChar,32, 32, 0);

        glColor3f(0.9,0.9,0.9);
        escreveTexto(GLUT_BITMAP_HELVETICA_18,scoreChar,170, 20, 1);

        glBindTexture(GL_TEXTURE_2D, Icone[0].patinho[CorDoIcone[1]]);
        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(70, 17, IconeDuck[1].z);
            glTexCoord2f(1, 0); glVertex3f(75, 17, IconeDuck[1].z);
            glTexCoord2f(1, 1); glVertex3f(75, 23, IconeDuck[1].z);
            glTexCoord2f(0, 1); glVertex3f(70, 23, IconeDuck[1].z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, Icone[1].patinho[CorDoIcone[2]]);

        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(77, 17, IconeDuck[2].z);
            glTexCoord2f(1, 0); glVertex3f(82, 17, IconeDuck[2].z);
            glTexCoord2f(1, 1); glVertex3f(82, 23, IconeDuck[2].z);
            glTexCoord2f(0, 1); glVertex3f(77, 23, IconeDuck[2].z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, Icone[2].patinho[CorDoIcone[3]]);

        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(84, 17, IconeDuck[3].z);
            glTexCoord2f(1, 0); glVertex3f(89, 17, IconeDuck[3].z);
            glTexCoord2f(1, 1); glVertex3f(89, 23, IconeDuck[3].z);
            glTexCoord2f(0, 1); glVertex3f(84, 23, IconeDuck[3].z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, Icone[3].patinho[CorDoIcone[4]]);

        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(91, 17, IconeDuck[4].z);
            glTexCoord2f(1, 0); glVertex3f(96, 17, IconeDuck[4].z);
            glTexCoord2f(1, 1); glVertex3f(96, 23, IconeDuck[4].z);
            glTexCoord2f(0, 1); glVertex3f(91, 23, IconeDuck[4].z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, Icone[4].patinho[CorDoIcone[5]]);

        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(98, 17, IconeDuck[5].z);
            glTexCoord2f(1, 0); glVertex3f(103, 17, IconeDuck[5].z);
            glTexCoord2f(1, 1); glVertex3f(103, 23, IconeDuck[5].z);
            glTexCoord2f(0, 1); glVertex3f(98, 23, IconeDuck[5].z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, Icone[5].patinho[CorDoIcone[6]]);

        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(105, 17, IconeDuck[6].z);
            glTexCoord2f(1, 0); glVertex3f(110, 17, IconeDuck[6].z);
            glTexCoord2f(1, 1); glVertex3f(110, 23, IconeDuck[6].z);
            glTexCoord2f(0, 1); glVertex3f(105, 23, IconeDuck[6].z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, Icone[6].patinho[CorDoIcone[7]]);

        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(112, 17, IconeDuck[7].z);
            glTexCoord2f(1, 0); glVertex3f(117, 17, IconeDuck[7].z);
            glTexCoord2f(1, 1); glVertex3f(117, 23, IconeDuck[7].z);
            glTexCoord2f(0, 1); glVertex3f(112, 23, IconeDuck[7].z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, Icone[7].patinho[CorDoIcone[8]]);

        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(119, 17, IconeDuck[8].z);
            glTexCoord2f(1, 0); glVertex3f(124, 17, IconeDuck[8].z);
            glTexCoord2f(1, 1); glVertex3f(124, 23, IconeDuck[8].z);
            glTexCoord2f(0, 1); glVertex3f(119, 23, IconeDuck[8].z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, Icone[8].patinho[CorDoIcone[9]]);

        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(126, 17, IconeDuck[9].z);
            glTexCoord2f(1, 0); glVertex3f(131, 17, IconeDuck[9].z);
            glTexCoord2f(1, 1); glVertex3f(131, 23, IconeDuck[9].z);
            glTexCoord2f(0, 1); glVertex3f(126, 23, IconeDuck[9].z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, Icone[9].patinho[CorDoIcone[10]]);

        glBegin(GL_QUADS);

            glTexCoord2f(0, 0); glVertex3f(133, 17, IconeDuck[10].z);
            glTexCoord2f(1, 0); glVertex3f(138, 17, IconeDuck[10].z);
            glTexCoord2f(1, 1); glVertex3f(138, 23, IconeDuck[10].z);
            glTexCoord2f(0, 1); glVertex3f(133, 23, IconeDuck[10].z);
        glEnd();

        if(NumTiros<3){
            glBindTexture(GL_TEXTURE_2D, Tiro1);
            glBegin(GL_QUADS);

                glTexCoord2f(0, 0); glVertex3f(20, 17, 1);
                glTexCoord2f(1, 0); glVertex3f(23, 17, 1);
                glTexCoord2f(1, 1); glVertex3f(23, 23, 1);
                glTexCoord2f(0, 1); glVertex3f(20, 23, 1);
            glEnd();
        }
        if(NumTiros<2){
            glBindTexture(GL_TEXTURE_2D, Tiro2);
            glBegin(GL_QUADS);

                glTexCoord2f(0, 0); glVertex3f(26, 17, 1);
                glTexCoord2f(1, 0); glVertex3f(29, 17, 1);
                glTexCoord2f(1, 1); glVertex3f(29, 23, 1);
                glTexCoord2f(0, 1); glVertex3f(26, 23, 1);
            glEnd();
        }
        if(NumTiros<1){
            glBindTexture(GL_TEXTURE_2D, Tiro3);
            glBegin(GL_QUADS);

                glTexCoord2f(0, 0); glVertex3f(32, 17, 1);
                glTexCoord2f(1, 0); glVertex3f(35, 17, 1);
                glTexCoord2f(1, 1); glVertex3f(35, 23, 1);
                glTexCoord2f(0, 1); glVertex3f(32, 23, 1);
            glEnd();
        }

        if(GameOver == 1){
            glBindTexture(GL_TEXTURE_2D, Game_Over); // PLACA GAMEOVER
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(70,140, 0);
                glTexCoord2f(1, 0); glVertex3f( 130,140, 0);
                glTexCoord2f(1, 1); glVertex3f( 130, 165, 0);
                glTexCoord2f(0, 1); glVertex3f(70, 165, 0);
            glEnd();
        }

        if(acao == 3){
            glBindTexture(GL_TEXTURE_2D, Flyaway); // PLACA FLY AWAY
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(75,120, 0);
                glTexCoord2f(1, 0); glVertex3f( 130,120, 0);
                glTexCoord2f(1, 1); glVertex3f( 130, 135, 0);
                glTexCoord2f(0, 1); glVertex3f(75, 135, 0);
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D, Fundo);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(0,0, 0);
            glTexCoord2f(1, 0); glVertex3f( 200,0, 0);
            glTexCoord2f(1, 1); glVertex3f( 200, 200, 0);
            glTexCoord2f(0, 1); glVertex3f(0, 200, 0);
        glEnd();

        if(TexturaDogwalk.z < -0.1 ){
            if(ConstanteH>0){
                glBindTexture(GL_TEXTURE_2D, Patomove.Duck_Texture[NumTextPato]);

                    glBegin(GL_QUADS);
                        glTexCoord2f(0, 0); glVertex3f(TexturaDuckPos.x, TexturaDuckPos.y, TexturaDuckPos.z);
                        glTexCoord2f(1, 0); glVertex3f(TexturaDuckPos.x + TexturaPatoTam.largura,TexturaDuckPos.y, TexturaDuckPos.z);
                        glTexCoord2f(1, 1); glVertex3f(TexturaDuckPos.x + TexturaPatoTam.largura, TexturaDuckPos.y + TexturaPatoTam.altura, TexturaDuckPos.z);
                        glTexCoord2f(0, 1); glVertex3f(TexturaDuckPos.x,TexturaDuckPos.y + TexturaPatoTam.altura, TexturaDuckPos.z);
                    glEnd();
        }
            if(ConstanteH <0){
                glBindTexture(GL_TEXTURE_2D, Patomove.Duck_Texture[NumTextPato]);

                    glBegin(GL_QUADS);
                        glTexCoord2f(0, 0); glVertex3f(TexturaDuckPos.x + TexturaPatoTam.largura,TexturaDuckPos.y, TexturaDuckPos.z);
                        glTexCoord2f(1, 0); glVertex3f(TexturaDuckPos.x, TexturaDuckPos.y, TexturaDuckPos.z);
                        glTexCoord2f(1, 1); glVertex3f(TexturaDuckPos.x,TexturaDuckPos.y + TexturaPatoTam.altura, TexturaDuckPos.z);
                        glTexCoord2f(0, 1); glVertex3f(TexturaDuckPos.x + TexturaPatoTam.largura, TexturaDuckPos.y + TexturaPatoTam.altura, TexturaDuckPos.z);
                    glEnd();

            }
        }
        glColor3f(1,1,1);
        glBindTexture(GL_TEXTURE_2D, CachorroAnda.Dog_Texture[NumTextCachorro]);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(TexturaDogwalk.x, TexturaDogwalk.y, TexturaDogwalk.z);
            glTexCoord2f(1, 0); glVertex3f(TexturaDogwalk.x + TextCachorroA.largura,TexturaDogwalk.y, TexturaDogwalk.z);
            glTexCoord2f(1, 1); glVertex3f(TexturaDogwalk.x + TextCachorroA.largura, TexturaDogwalk.y +TextCachorroA.altura, TexturaDogwalk.z);
            glTexCoord2f(0, 1); glVertex3f(TexturaDogwalk.x, TexturaDogwalk.y +TextCachorroA.altura, TexturaDogwalk.z);
        glEnd();
    }

    if(Tela == 4){ // DESENHA TELA DOS CREDITOS

        glBindTexture(GL_TEXTURE_2D, Creditos);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(0,0, 0);
                glTexCoord2f(1, 0); glVertex3f( 200,0, 0);
                glTexCoord2f(1, 1); glVertex3f( 200, 200, 0);
                glTexCoord2f(0, 1); glVertex3f(0, 200, 0);
            glEnd();
    }

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);


    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

void redimensiona(int w, int h){
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, 200, 0, 200, -10, 10);
   glMatrixMode(GL_MODELVIEW);
}

void restart(void){
    ConstanteH = 1;
    ConstanteV = 1; //AUMENTA VELOCIDADE ACADA NIVEL
    NumPatos = 0;
    NumErros = 0;         //REINICIA ALGUNS DADOS
    PatosMortos = 0;
    voa = 0;
    acao = 0;
    andaCachorro = 0;
    cheiracachorro = 0;
    contadorcheiradas = 0;
    PiscaIcone = 0;
    Nivel=1;
    Score = 0;
    GameOver = 0;


    CorDoIcone[1] = 0; CorDoIcone[6] = 0;
    CorDoIcone[2] = 0; CorDoIcone[7] = 0;
    CorDoIcone[3] = 0; CorDoIcone[8] = 0;
    CorDoIcone[4] = 0; CorDoIcone[9] = 0;
    CorDoIcone[5] = 0; CorDoIcone[10] = 0;

    IconeDuck[1].z = 1; IconeDuck[6].z = 1;
    IconeDuck[2].z = 1; IconeDuck[7].z = 1;
    IconeDuck[3].z = 1; IconeDuck[8].z = 1;
    IconeDuck[4].z = 1; IconeDuck[9].z = 1;
    IconeDuck[5].z = 1; IconeDuck[10].z = 1;


    TexturaDogwalk.x = 0;
    TexturaDogwalk.y = 37.5;
    TexturaDogwalk.z = 1;

    TexturaDuckPos.x = rand()% 165;
    TexturaDuckPos.y = 50;
    TexturaDuckPos.z = -1;
}

void teclado(unsigned char key, int x, int y){
   switch (key) {
      case 27:
         exit(0);

      case 112:
        Pausa = Pausa * -1;
        glutPostRedisplay();

          if(Tela==1){
            Tela=2;
          }
          else{
            Tela=1;
            glutTimerFunc(33,atualiza,0);
          }
          break;

      case 114:
          restart();
          break;
   }
}

void movimento_do_mouse(int x, int y){
    PosicaoMouse.x = x /4;
    PosicaoMouse.y = (y * -1/4) + 200 ;
}

void atualiza(int idx){


    if(Tela == 1){ // tela do jogo rodando

            //converte o nivel e score para char para imprimir na tela
        itoa(Nivel,nivelChar,10);
        itoa(Score,scoreChar,10);
            // Pede ao GLUT para redesenhar a tela, assim que poss�vel
        glutPostRedisplay ();

        if(NumPatos <=10){ //  se o nivel nao acabou ainda (10 patos)
            if(TexturaDogwalk.z > -2){ // se a textura do cachorro esta na frente do fundo
                cachorro_anda(0); // roda anima��o do cachorro andando
            }
            if(TexturaDogwalk.z <= -2){ // se a textura do cachorro estiver atras do fundo
                if (voa == 0){ //se o pato come�ou a voar agora
                    NumPatos++; // numero de patos + 1
                }
                voa ++; // timer entre o cachorro entrar no mato e o pato voar
            }
            if(acao == 0 && voa > 10){ // se a a��o for 0 (pato voando e o timer voa for 10)
                if(CorDoPato == 0){
                    pato_voa_azul(0);
                }
                if(CorDoPato == 1){
                    pato_voa_preto(0);
                }
                if(CorDoPato == 2){
                    pato_voa_vermelho(0);
                }

                timer++;
                if(timer % 30 == 0){ // FAZ ICONES DOS PATOS PISCAREM ENQUANTO VOAM
                    if(NumPatos == 1)
                        IconeDuck[1].z = IconeDuck[1].z * -1;
                    if(NumPatos == 2)
                        IconeDuck[2].z = IconeDuck[2].z * -1;
                    if(NumPatos == 3)
                        IconeDuck[3].z = IconeDuck[3].z * -1;
                    if(NumPatos == 4)
                        IconeDuck[4].z = IconeDuck[4].z * -1;
                    if(NumPatos == 5)
                        IconeDuck[5].z = IconeDuck[5].z * -1;
                    if(NumPatos == 6)
                        IconeDuck[6].z = IconeDuck[6].z * -1;
                    if(NumPatos == 7)
                        IconeDuck[7].z = IconeDuck[7].z * -1;
                    if(NumPatos == 8)
                        IconeDuck[8].z = IconeDuck[8].z * -1;
                    if(NumPatos == 9)
                        IconeDuck[9].z = IconeDuck[9].z * -1;
                    if(NumPatos == 10)
                        IconeDuck[10].z = IconeDuck[10].z * -1;

                }
            }

            if(acao == 1){ // se acao for 1 (pato morre)
                if(CorDoPato == 0){
                    pato_morre_azul();
                }
                if(CorDoPato == 1){
                    pato_morre_preto();
                }
                if(CorDoPato == 2){
                    pato_morre_vermelho();
                }
            }
            if(acao == 2){ // acao 2 (mostra pato)
                mostra_pato();
            }
            if(timer == 350 || NumErros >= 6){ // pato fugindo
                acao = 3; // tela fly away
                timer =0; // reseta
            }
            if(acao == 3){
                if(CorDoPato == 0){
                    pato_escapa_azul();
                }
                if(CorDoPato == 1){
                    pato_escapa_preto();
                }
                if(CorDoPato == 2){
                    pato_escapa_vermelho();
                }
            }
            if(acao == 4){
                cachorro_ri();
            }

        }

        if(NumPatos == 11){
            analisaNivel();
        }
                    // Se registra novamente, para que fique sempre sendo chamada (60 FPS)

        conversor++;
        glutTimerFunc(15, atualiza, 0);
    }

}

void pato_voa_azul(int idx){

    glClearColor(0.3,0.734,1.0,0); //  volta cor do fundo para o azul

    fundo_pos_tiro = 0;
    TexturaDuckPos.x += VelocidadeHorizontal * ConstanteH;
    TexturaDuckPos.y += VelocidadeVertical * ConstanteV;

    if(conversor == 2){
        NumTextPato++;
    }
    if(conversor > 2){
        conversor = 0;
    }

    if(TexturaDuckPos.x + TexturaPatoTam.largura  > 200 || TexturaDuckPos.x < 0){ // Impacto com a parede lateral
        TexturaDuckPos.x -= VelocidadeHorizontal * ConstanteH;

        ConstanteH = ConstanteH * -1; // muda direcao do movimento


        VelocidadeHorizontal = rand()%2;
        VelocidadeVertical = rand()%1+1;



    }
    if(TexturaDuckPos.y + TexturaPatoTam.altura  > 200 || TexturaDuckPos.y < 40){ // Impacto com a parede de cima e de baixo
        TexturaDuckPos.y -= VelocidadeVertical * ConstanteV;
        ConstanteV = ConstanteV * -1;
        VelocidadeVertical = rand()%1+1;
        VelocidadeHorizontal = rand()%2;


    }

    if(VelocidadeHorizontal >= VelocidadeVertical ){
        if(NumTextPato >2){
            NumTextPato = 0;
        }
    }

    if(VelocidadeHorizontal < VelocidadeVertical && VelocidadeHorizontal != 0){

        if(NumTextPato >5 ){
            NumTextPato = 3;
        }
    }

    if(VelocidadeHorizontal == 0){

        if(ConstanteV > 0){
            if(NumTextPato >8){
                NumTextPato = 6;
            }
        }
        else{
            if(NumTextPato >5 ){
                NumTextPato = 3;
            }
        }
    }
    glutPostRedisplay();
}

void pato_voa_preto(int idx){
    glClearColor(0.3,0.734,1.0,0);

    fundo_pos_tiro = 0;
    TexturaDuckPos.x += VelocidadeHorizontal * ConstanteH ;
    TexturaDuckPos.y += VelocidadeVertical * ConstanteV ;

    if(conversor == 2){
        NumTextPato++;
    }
    if(conversor > 2){
        conversor = 0;
    }

    if(TexturaDuckPos.x + TexturaPatoTam.largura  > 200 || TexturaDuckPos.x < 0){ // Impacto com a parede lateral
        TexturaDuckPos.x -= VelocidadeHorizontal * ConstanteH;

        ConstanteH = ConstanteH * -1;


        VelocidadeHorizontal = rand()%2;
        VelocidadeVertical = rand()%1 + 1;
    }
    if(TexturaDuckPos.y + TexturaPatoTam.altura  > 200 || TexturaDuckPos.y < 40){ // Impacto com a parede de cima e de baixo
        TexturaDuckPos.y -= VelocidadeVertical * ConstanteV;
        ConstanteV = ConstanteV * -1;
        VelocidadeVertical = rand()%1+1;
        VelocidadeHorizontal = rand()%2;

    }
    if(VelocidadeHorizontal >= VelocidadeVertical ){
        if(NumTextPato >14 || NumTextPato <12){
            NumTextPato = 12;
        }
    }

    if(VelocidadeHorizontal < VelocidadeVertical && VelocidadeHorizontal != 0){

        if(NumTextPato >17 ||  NumTextPato< 15 ){
            NumTextPato = 15;
        }
    }

    if(VelocidadeHorizontal == 0){

        if(ConstanteV > 0){
            if(NumTextPato >=21 || NumTextPato < 18){
                NumTextPato = 18;
            }
        }
        else{
            if(NumTextPato >17 || NumTextPato <15 ){
                NumTextPato = 15;
            }
        }
    }
    glutPostRedisplay();
}

void pato_voa_vermelho(int idx){

    glClearColor(0.3,0.734,1.0,0);

    fundo_pos_tiro = 0;
    TexturaDuckPos.x += VelocidadeHorizontal * ConstanteH ;
    TexturaDuckPos.y += VelocidadeVertical * ConstanteV ;

    if(conversor == 2){
        NumTextPato++;
    }
    if(conversor > 2){
        conversor = 0;
    }

    if(TexturaDuckPos.x + TexturaPatoTam.largura  > 200 || TexturaDuckPos.x < 0){ // Impacto com a parede lateral
        TexturaDuckPos.x -= VelocidadeHorizontal * ConstanteH;

        ConstanteH = ConstanteH * -1;


        VelocidadeHorizontal = rand()%2;
        VelocidadeVertical = rand()%1 +1;

    }
    if(TexturaDuckPos.y + TexturaPatoTam.altura  > 200 || TexturaDuckPos.y < 40){ // Impacto com a parede de cima e de baixo
        TexturaDuckPos.y -= VelocidadeVertical * ConstanteV;
        ConstanteV = ConstanteV * -1;
        VelocidadeHorizontal = rand()%2;
        VelocidadeVertical = rand()%1 +1;
    }
    if(VelocidadeHorizontal >= VelocidadeVertical ){
        if(NumTextPato >26 || NumTextPato <24){
            NumTextPato = 24;
        }
    }

    if(VelocidadeHorizontal < VelocidadeVertical && VelocidadeHorizontal != 0){

        if(NumTextPato >29 || NumTextPato <27 ){
            NumTextPato = 27;
        }
    }

    if(VelocidadeHorizontal == 0){

        if(ConstanteV > 0){
            if(NumTextPato >32 || NumTextPato <30 ){
                NumTextPato = 30;
            }
        }
        else{
            if(NumTextPato >29 || NumTextPato <27 ){
            NumTextPato = 27;
            }
        }
    }
    glutPostRedisplay();
}

void pato_morre_azul(void){

    if(fundo_pos_tiro == 0){ // passaro voando tela azul
        glClearColor(0.3,0.734,1.0,0);
    }
    if (fundo_pos_tiro == 1){ // fundo rosa
        glClearColor(1,0.8,0.8,0);
    }

    acertaParto++; // 'timer' para as texturas
    if(acertaParto <3){
        NumTextPato = 9;
        glutPostRedisplay();
        Sleep(150);
    }

    else{
        TexturaDuckPos.y -=5/3;
        if(conversor == 2){
            NumTextPato++;
        }
        if(conversor > 2){
            conversor = 0;
        }
        if(NumTextPato >11)
            NumTextPato = 10;


        if(TexturaDuckPos.y <= 40){
            PatosMortos++;
            acertaParto = 0;
            acao = 2;
        }
    }
}

void pato_morre_preto(void){

    if(fundo_pos_tiro == 0){ // passaro voando tela azul
        glClearColor(0.3,0.734,1.0,0);
    }
    if (fundo_pos_tiro == 1){ // fundo rosa
        glClearColor(1,0.8,0.8,0);
    }

    acertaParto++;
    if(acertaParto <3){
        NumTextPato = 21;
        Sleep(150);
    }
    else{
        TexturaDuckPos.y -=5/4;
        if(conversor == 2){
        NumTextPato++;
        }
        if(conversor > 2){
            conversor = 0;
        }
        if(NumTextPato >23 || NumTextPato<20)
            NumTextPato = 22;


        if(TexturaDuckPos.y <= 40){
            PatosMortos++;
            acertaParto = 0;
            acao = 2;

        }
    }
}

void pato_morre_vermelho(void){

    if(fundo_pos_tiro == 0){ // passaro voando tela azul
        glClearColor(0.3,0.734,1.0,0);
    }
    if (fundo_pos_tiro == 1){ // fundo rosa
        glClearColor(1,0.8,0.8,0);
    }

    acertaParto++;
    if(acertaParto <3){
        NumTextPato = 33;
        Sleep(150);
    }
    else{
        TexturaDuckPos.y -= 5/4;
        if(conversor == 2){
        NumTextPato++;
        }
        if(conversor > 2){
            conversor = 0;
        }
        if(NumTextPato >35 || NumTextPato <33)
            NumTextPato = 34;


        if(TexturaDuckPos.y <= 40){
            PatosMortos++;
            acertaParto = 0;
            acao = 2;
        }
    }
}

void mostra_pato(void){
    glClearColor(0.3,0.734,1.0,0);
    glutPostRedisplay();
    NumTextCachorro = 8;
    if(TexturaDuckPos.x >= 25 && TexturaDuckPos.x <= 110){
        TexturaDogwalk.x = TexturaDuckPos.x;
    }
    if(TexturaDuckPos.x < 25){
        TexturaDogwalk.x = 25;
    }

    if(TexturaDuckPos.x > 110){
        TexturaDogwalk.x = 110;
    }

    TexturaDogwalk.z = -3;
    TexturaDogwalk.y += (3 * MostraPato) /2;
    if(TexturaDogwalk.y >= 65){
        Sleep(500);

        MostraPato = MostraPato * -1;
    }
    if(TexturaDogwalk.y <= 40 && MostraPato <0){

        int direcao_voo;
        direcao_voo = rand ()%1;

        if (direcao_voo == 0){
            ConstanteH = ConstanteH * 1;
        }
        else {
            ConstanteH = ConstanteH * -1;
        }
        MostraPato = MostraPato * -1;
        voa=0;
        acao=0;
        TexturaDuckPos.x = rand()%171;
        VelocidadeHorizontal = rand()%2;
        VelocidadeVertical = rand()%1 +1;
        CorDoPato = rand()%3;
        timer = 0;
        IconeDuck[NumPatos].z = 1;
        NumErros = 0;
        NumTiros = 0;
        acertou = 0;
    }
}

void pato_escapa_azul(void){

    glClearColor(1,0.8,0.8,0);
    glutPostRedisplay();
    fundo_pos_tiro = 1;
    if(NumErros >= 6){
        if(conversor == 2){
        NumTextPato++;
        }
        if(conversor > 2){
            conversor = 0;
        }
        VelocidadeVertical = 2;
        VelocidadeHorizontal = 0;
        TexturaDuckPos.y += VelocidadeVertical;
        if(NumTextPato >8){
            NumTextPato = 6;
        }

    }

    if(NumErros < 6){
        if(conversor == 2){
        NumTextPato++;
        }
        if(conversor > 2){
            conversor = 0;
        }
        TexturaDuckPos.x += VelocidadeHorizontal * ConstanteH;
        TexturaDuckPos.y += VelocidadeVertical * ConstanteV;
        if(TexturaDuckPos.y <=40){
            ConstanteV = ConstanteV * -1;
        }
        if(VelocidadeHorizontal >= VelocidadeVertical ){
            if(NumTextPato >2){
                NumTextPato = 0;
            }
        }

        if(VelocidadeHorizontal < VelocidadeVertical && VelocidadeHorizontal != 0){

            if(NumTextPato >6 ){
                NumTextPato = 3;
            }
        }

        if(VelocidadeHorizontal == 0){

            if(ConstanteV > 0){
                if(NumTextPato >8){
                    NumTextPato = 6;
                }
            }
            else{
                if(NumTextPato >5 ){
                    NumTextPato = 3;
                }
            }
        }

    }

    glutPostRedisplay();
    if(TexturaDuckPos.y >= 200 ||TexturaDuckPos.x >= 200 || TexturaDuckPos.x + TexturaPatoTam.largura <= 0){
        acao = 4;
        NumTextCachorro = 9;
     }
}

void pato_escapa_preto(void){
    glClearColor(1,0.8,0.8,0);
    glutPostRedisplay();
    fundo_pos_tiro = 1;
    if(NumErros >= 6){
        if(conversor == 2){
            NumTextPato++;
        }
        if(conversor > 2){
            conversor = 0;
        }
        VelocidadeVertical = 2;
        VelocidadeHorizontal = 0;
        TexturaDuckPos.y += VelocidadeVertical;
        if(NumTextPato >=21 || NumTextPato < 18){
            NumTextPato = 18;
        }

    }

    if(NumErros <6){
        if(conversor == 2){
            NumTextPato++;
        }
        if(conversor > 2){
            conversor = 0;
        }

        TexturaDuckPos.x += VelocidadeHorizontal * ConstanteH;
        TexturaDuckPos.y += VelocidadeVertical * ConstanteV;
        if(TexturaDuckPos.y <=40){
            ConstanteV = ConstanteV * -1;
        }
        if(VelocidadeHorizontal >= VelocidadeVertical ){
            if(NumTextPato >14 || NumTextPato <12){
                NumTextPato = 12;
            }
        }

        if(VelocidadeHorizontal < VelocidadeVertical && VelocidadeHorizontal != 0){

            if(NumTextPato >17 ||  NumTextPato< 15 ){
                NumTextPato = 15;
            }
        }

        if(VelocidadeHorizontal == 0){

            if(ConstanteV > 0){
                if(NumTextPato >=21 || NumTextPato < 18){
                    NumTextPato = 18;
                }
            }
            else{
                if(NumTextPato >17 || NumTextPato <15 ){
                    NumTextPato = 15;
                }
            }
        }

    }

    glutPostRedisplay();
    if(TexturaDuckPos.y >= 200 ||TexturaDuckPos.x >= 200 || TexturaDuckPos.x + TexturaPatoTam.largura <= 0){
        acao = 4;
        NumTextCachorro = 9;
     }
}

void pato_escapa_vermelho(void){
    glClearColor(1,0.8,0.8,0);
    glutPostRedisplay();
    fundo_pos_tiro = 1;
    if(NumErros >= 6){
        if(conversor == 2){
        NumTextPato++;
        }
        if(conversor > 2){
            conversor = 0;
        }
        VelocidadeVertical = 2;
        VelocidadeHorizontal = 0;
        TexturaDuckPos.y += VelocidadeVertical;
        if(NumTextPato >32 || NumTextPato <30 ){
            NumTextPato = 30;
        }

    }

    if(NumErros <6){
        if(conversor == 2){
        NumTextPato++;
        }
        if(conversor > 2){
            conversor = 0;
        }
        TexturaDuckPos.x += VelocidadeHorizontal * ConstanteH;
        TexturaDuckPos.y += VelocidadeVertical * ConstanteV;
        if(TexturaDuckPos.y <=40){
            ConstanteV = ConstanteV * -1;
        }
        if(VelocidadeHorizontal >= VelocidadeVertical ){
            if(NumTextPato >26 || NumTextPato <24){
                NumTextPato = 24;
            }
        }

        if(VelocidadeHorizontal < VelocidadeVertical && VelocidadeHorizontal != 0){

            if(NumTextPato >29 || NumTextPato <27 ){
                NumTextPato = 27;
            }
        }

        if(VelocidadeHorizontal == 0){

            if(ConstanteV > 0){
                if(NumTextPato >32 || NumTextPato <30 ){
                    NumTextPato = 30;
                }
            }
            else{
                if(NumTextPato >29 || NumTextPato <27 ){
                NumTextPato = 27;
                }
            }
        }

    }

    glutPostRedisplay();
    if(TexturaDuckPos.y >= 200 ||TexturaDuckPos.x >= 200 || TexturaDuckPos.x + TexturaPatoTam.largura <= 0){
        acao = 4;
        NumTextCachorro = 9;
     }
}

void cachorro_anda(int idx){
    NumTiros = 0;
    NumErros = 0;
    IconeDuck[1].z = 1; IconeDuck[6].z = 1;
    IconeDuck[2].z = 1; IconeDuck[7].z = 1;
    IconeDuck[3].z = 1; IconeDuck[8].z = 1;
    IconeDuck[4].z = 1; IconeDuck[9].z = 1;
    IconeDuck[5].z = 1; IconeDuck[10].z = 1;

    if(andaCachorro<6){
        if(conversor == 4){
            NumTextCachorro++;
        }
        if(conversor > 4){
            conversor = 0;
        }


        TexturaDogwalk.x += 0.5;


        if(NumTextCachorro >2){
            NumTextCachorro=0;
            andaCachorro++;
        }
    }

    if(andaCachorro >5 && andaCachorro <10){
        if(conversor == 4){
            NumTextCachorro++;
        }
        if(conversor > 4){
            conversor = 0;
        }
        if(NumTextCachorro>4){
            NumTextCachorro=3;
            cheiracachorro++;
            contadorcheiradas++;
            if(contadorcheiradas == 6){
                andaCachorro = 10;

            }
            if(cheiracachorro == 3){
                NumTextCachorro=0;
                andaCachorro = 0;
            }

        }
    }

    if (andaCachorro >= 10 && andaCachorro<13){
        NumTextCachorro=5;
        Sleep(100);
        andaCachorro++;
    }
    if(andaCachorro >=13 && andaCachorro < 17){

        if(conversor == 3){
            NumTextCachorro = 6;

            TexturaDogwalk.x +=1;
            TexturaDogwalk.y +=10;
            andaCachorro++;
        }
        if(conversor > 3){
            conversor = 0;
        }


    }

    if(andaCachorro > 16){
        if(conversor == 2){
           NumTextCachorro=7;
            TexturaDogwalk.x += 1;
            TexturaDogwalk.y -=5;
            TexturaDogwalk.z -=0.3;
        }
        if(conversor > 2){
            conversor = 0;
        }

    }

    glutPostRedisplay();

}

void cachorro_ri(void){
    glClearColor(0.3,0.734,1.0,0);
    risada++;
    TexturaDogwalk.z = -3;
    TexturaDogwalk.x = 75;
    if(risada < 60 && TexturaDogwalk.y <= 65){
        TexturaDogwalk.y +=1;
    }
    if(risada > 60 && risada <= 120){
        if(conversor == 3){
            NumTextCachorro++;
        }
        if(conversor > 3){
            conversor = 0;
        }

        NumErros = 0;
        if(NumTextCachorro > 10){
            NumTextCachorro = 9;

        }
    }
    if(risada >120){
        TexturaDogwalk.y -=1;
    }
    if(TexturaDogwalk.y <= 40 && risada > 120){
        int direcao_voo;
        direcao_voo = rand ()%1;

        if (direcao_voo == 0){
            ConstanteH = ConstanteH * 1;
        }
        else {
            ConstanteH = ConstanteH * -1;
        }

        voa=0;
        risada = 0;
        acao = 0;
        IconeDuck[NumPatos].z = 1;
        TexturaDuckPos.x = rand()%171;
        TexturaDuckPos.y = 40;
        VelocidadeHorizontal = rand()%2;
        VelocidadeVertical = rand()%1 +1;
        CorDoPato = rand()%3;
        timer = 0;
        NumErros = 0;
        NumTiros = 0;
        conversor = 0;


    }
}

void tiro (int botao, int estado, int x, int y){
    if(Tela == 0){

        if(botao == GLUT_LEFT_BUTTON){
            if(estado == GLUT_UP){
                Tiro.x = x/4;
                Tiro.y =(y * -1/4) + 200 ;


                if(Tiro.x >= BotaoStart.x && Tiro.x <= BotaoStart.x + StartButtom.largura){
                    if(Tiro.y > BotaoStart.y + 25 && Tiro.y <= BotaoStart.y + StartButtom.altura +15 ){
                        Tela = 1;
                        glutTimerFunc(90,atualiza,0);
                    }
                }
                if(Tiro.x >= Botao_Creditos.x && Tiro.x <= Botao_Creditos.x+creditosBotao.largura){
                    if(Tiro.y >= Botao_Creditos.y +26 && Tiro.y <= Botao_Creditos.y + creditosBotao.altura+26){
                        Tela = 4;
                        glutPostRedisplay();
                    }
                }
            }
        }
    }

    if(Tela == 1 && TexturaDogwalk.z <-2 && GameOver != 1){

        if(botao == GLUT_LEFT_BUTTON && NumErros < 6 ){

            if(estado == GLUT_UP && NumTiros <=3){
                piscaTela();
                Tiro.x = x/4;
                Tiro.y =(y * -1/4) + 200 ;
                NumTiros++;


            }

        }
        if(NumErros <6 && NumTiros <=3){


            // piscaTela();
            glutPostRedisplay();




            if(Tiro.x >= TexturaDuckPos.x  && Tiro.x <= TexturaDuckPos.x + TexturaPatoTam.largura  ){
                if(Tiro.y >= TexturaDuckPos.y  && Tiro.y <= TexturaDuckPos.y + TexturaPatoTam.altura ){

                    piscaTela();
                    glutPostRedisplay();

                    acertou = 1;

                    if(CorDoPato == 0){
                        NumTextPato = 9;
                        Score +=1000;
                        acao = 1;
                    }
                    if(CorDoPato == 1){
                        NumTextPato = 21;
                        Score +=500;
                        acao = 1;
                    }
                    if(CorDoPato == 2){
                        NumTextPato = 33;
                        Score +=1500;
                        acao = 1;
                    }

                    CorDoIcone[NumPatos] = 1;

                    if(fundo_pos_tiro == 0){ // passaro voando tela azul
                        glClearColor(0.3,0.734,1.0,0);
                    }
                    if (fundo_pos_tiro == 1){ // fundo rosa
                        glClearColor(1,0.8,0.8,0);
                    }

                }
                else{
                    if(NumTiros <= 3 && acertou == 0){
                        NumErros++;
                    }

                }
            }
            else{
                if(NumTiros <= 3 && acertou == 0){
                    NumErros++;

                }

            }
        }

    }
    if(Tela == 4){
        if(botao == GLUT_LEFT_BUTTON){
            if(estado == GLUT_UP){
                Tiro.x = x/4;
                Tiro.y =(y * -1/4) + 200 ;
                if(Tiro.x >=0&& Tiro.x <= 200){
                    if(Tiro.y >= 0&& Tiro.y <= 200 ){
                        clique++;
                        if(clique >1){
                            Tela = 0;
                            clique = 0;
                            glutPostRedisplay();
                        }
                    }
                }
            }
        }
    }

}

void piscaTela(){
    glClearColor(0,0,0,0);
    glutPostRedisplay();

}

void analisaNivel(void){

    for(i=1;i<11;i++){    //JUNTA OS ICONES VELRMELHOS COM ICONES VERMELHOS E BRANCOS COM BRANCOS
        for(j=i+1;j<11;j++){
            if(CorDoIcone[i]<CorDoIcone[j]){
                aux = CorDoIcone[i];
                CorDoIcone[i] = CorDoIcone[j];
                CorDoIcone[j] = aux;
                glutPostRedisplay();
                Sleep(40);
                glutSwapBuffers();

            }
        }
    }

        if(PiscaIcone <= 300){
            PiscaIcone++;

            if(PiscaIcone % 30 == 0){
                IconeDuck[1].z = IconeDuck[1].z * -1;
                IconeDuck[2].z = IconeDuck[2].z * -1;
                IconeDuck[3].z = IconeDuck[3].z * -1;
                IconeDuck[4].z = IconeDuck[4].z * -1;
                IconeDuck[5].z = IconeDuck[5].z * -1;
                IconeDuck[6].z = IconeDuck[6].z * -1;
            }

        }

    if(Nivel <= 5){ // SE NIVEL MENOR QUE 5 TEM QUE ACERTAR 6 PATOS


        if(PatosMortos >= 6 && PiscaIcone >= 300){


            if(PatosMortos == 10){
                Score += 10000;
            }
            if(ConstanteH >0){
                ConstanteH += 0.10;
            }
            else{
                ConstanteH = (ConstanteH * -1) + 0.10;//AUMENTA VELOCIDADE ACADA NIVEL
            }
            if(ConstanteV >0){
                ConstanteV += 0.10;
            }
            else{
                ConstanteV = (ConstanteV * -1) + 0.10;
            }
            NumPatos = 0;
            NumErros = 0;         //REINICIA ALGUNS DADOS
            PatosMortos = 0;
            voa = 0;
            acao = 0;
            andaCachorro = 0;
            cheiracachorro = 0;
            contadorcheiradas = 0;
            PiscaIcone = 0;
            Nivel++;

            CorDoIcone[1] = 0; CorDoIcone[6] = 0;
            CorDoIcone[2] = 0; CorDoIcone[7] = 0;
            CorDoIcone[3] = 0; CorDoIcone[8] = 0;
            CorDoIcone[4] = 0; CorDoIcone[9] = 0;
            CorDoIcone[5] = 0; CorDoIcone[10] = 0;


            TexturaDogwalk.x = 0;
            TexturaDogwalk.y = 37.5;
            TexturaDogwalk.z = 1;

            TexturaDuckPos.x = rand()% 165;
            TexturaDuckPos.y = 50;
            TexturaDuckPos.z = -1;
        }

        if(PatosMortos<6 && PiscaIcone >=40){
            glClearColor(0.3,0.734,1.0,0);

            IconeDuck[1].z = 1; IconeDuck[6].z = 1;
            IconeDuck[2].z = 1; IconeDuck[7].z = 1;
            IconeDuck[3].z = 1; IconeDuck[8].z = 1;
            IconeDuck[4].z = 1; IconeDuck[9].z = 1;
            IconeDuck[5].z = 1; IconeDuck[10].z = 1;

            risada++;
            GameOver = 1;
            TexturaDogwalk.z = -3;
            TexturaDogwalk.x = 75;
            if(risada < 15 && TexturaDogwalk.y <= 65){
                TexturaDogwalk.y +=3;
            }
            if(risada > 15){
                if(conversor == 3){
                    NumTextCachorro++;
                }
                if(conversor > 3){
                    conversor = 0;
                }

                if(NumTextCachorro > 10){
                    NumTextCachorro = 9;

                }
            }
        }
    }

    if(Nivel > 5 && Nivel <= 10){   // SE NIVEL MENOR QUE 10 E MAIOR QUE 5 TEM QUE ACERTAR 7 PATOS

        if(conversor == 3){
                PiscaIcone++;
            }
            if(conversor > 3){
                conversor = 0;
            }
            if(PiscaIcone % 5 == 0){
                IconeDuck[1].z = IconeDuck[1].z * -1;
                IconeDuck[2].z = IconeDuck[2].z * -1;
                IconeDuck[3].z = IconeDuck[3].z * -1;
                IconeDuck[4].z = IconeDuck[4].z * -1;
                IconeDuck[5].z = IconeDuck[5].z * -1;
                IconeDuck[6].z = IconeDuck[6].z * -1;
            }



        if(PatosMortos >= 7 && PiscaIcone >= 40){

            if(PatosMortos == 10){
                Score += 10000;
            }
            if(ConstanteH >0){
                ConstanteH += 0.10;
            }
            else{
                ConstanteH = (ConstanteH * -1) + 0.10;//AUMENTA VELOCIDADE ACADA NIVEL
            }
            if(ConstanteV >0){
                ConstanteV += 0.10;
            }
            else{
                ConstanteV = (ConstanteV * -1) + 0.10;
            }
            NumPatos = 0;
            NumErros = 0;         //REINICIA ALGUNS DADOS
            PatosMortos = 0;
            voa = 0;
            acao = 0;
            andaCachorro = 0;
            cheiracachorro = 0;
            contadorcheiradas = 0;
            PiscaIcone = 0;
            Nivel++;


            CorDoIcone[1] = 0; CorDoIcone[6] = 0;
            CorDoIcone[2] = 0; CorDoIcone[7] = 0;
            CorDoIcone[3] = 0; CorDoIcone[8] = 0;
            CorDoIcone[4] = 0; CorDoIcone[9] = 0;
            CorDoIcone[5] = 0; CorDoIcone[10] = 0;

            TexturaDogwalk.x = 0;
            TexturaDogwalk.y = 37.5;
            TexturaDogwalk.z = 1;

            TexturaDuckPos.x = rand()% 165;
            TexturaDuckPos.y = 50;
            TexturaDuckPos.z = -1;
        }

        if(PatosMortos<7 && PiscaIcone >=40){
            glClearColor(0.3,0.734,1.0,0);

            IconeDuck[1].z = 1; IconeDuck[6].z = 1;
            IconeDuck[2].z = 1; IconeDuck[7].z = 1;
            IconeDuck[3].z = 1; IconeDuck[8].z = 1;
            IconeDuck[4].z = 1; IconeDuck[9].z = 1;
            IconeDuck[5].z = 1; IconeDuck[10].z = 1;

            risada++;
            GameOver = 1;
            TexturaDogwalk.z = -3;
            TexturaDogwalk.x = 75;
            if(risada < 15 && TexturaDogwalk.y <= 65){
                TexturaDogwalk.y +=3;
            }
            if(risada > 15){
                if(conversor == 3){
                    NumTextCachorro++;
                }
                if(conversor > 3){
                    conversor = 0;
                }
                if(NumTextCachorro > 10){
                    NumTextCachorro = 9;

                }
            }
        }
    }

    if(Nivel > 10 && Nivel <= 15){  // SE NIVEL MENOR QUE 15 E MAIOR QUE 10 TEM QUE ACERTAR 8 PATOS

        if(conversor == 3){
            PiscaIcone++;
        }
        if(conversor > 3){
            conversor = 0;
        }
        if(PiscaIcone % 5 == 0){
            IconeDuck[1].z = IconeDuck[1].z * -1;
            IconeDuck[2].z = IconeDuck[2].z * -1;
            IconeDuck[3].z = IconeDuck[3].z * -1;
            IconeDuck[4].z = IconeDuck[4].z * -1;
            IconeDuck[5].z = IconeDuck[5].z * -1;
            IconeDuck[6].z = IconeDuck[6].z * -1;
        }

        if(PatosMortos >= 8 && PiscaIcone >= 40){

            if(PatosMortos == 10){
                Score += 10000;
            }
            if(ConstanteH >0){
                ConstanteH += 0.10;
            }
            else{
                ConstanteH = (ConstanteH * -1) + 0.10;//AUMENTA VELOCIDADE ACADA NIVEL
            }
            if(ConstanteV >0){
                ConstanteV += 0.10;
            }
            else{
                ConstanteV = (ConstanteV * -1) + 0.10;
            }
            NumPatos = 0;
            NumErros = 0;         //REINICIA ALGUNS DADOS
            PatosMortos = 0;
            voa = 0;
            acao = 0;
            andaCachorro = 0;
            cheiracachorro = 0;
            contadorcheiradas = 0;
            PiscaIcone = 0;
            Nivel++;


            CorDoIcone[1] = 0; CorDoIcone[6] = 0;
            CorDoIcone[2] = 0; CorDoIcone[7] = 0;
            CorDoIcone[3] = 0; CorDoIcone[8] = 0;
            CorDoIcone[4] = 0; CorDoIcone[9] = 0;
            CorDoIcone[5] = 0; CorDoIcone[10] = 0;


            TexturaDogwalk.x = 0;
            TexturaDogwalk.y = 37.5;
            TexturaDogwalk.z = 1;

            TexturaDuckPos.x = rand()% 165;
            TexturaDuckPos.y = 50;
            TexturaDuckPos.z = -1;
        }

        if(PatosMortos<8 && PiscaIcone >=40){
            glClearColor(0.3,0.734,1.0,0);

            IconeDuck[1].z = 1; IconeDuck[6].z = 1;
            IconeDuck[2].z = 1; IconeDuck[7].z = 1;
            IconeDuck[3].z = 1; IconeDuck[8].z = 1;
            IconeDuck[4].z = 1; IconeDuck[9].z = 1;
            IconeDuck[5].z = 1; IconeDuck[10].z = 1;

            risada++;
            GameOver = 1;
            TexturaDogwalk.z = -3;
            TexturaDogwalk.x = 75;
            if(risada < 15 && TexturaDogwalk.y <= 65){
                TexturaDogwalk.y +=3;
            }
            if(risada > 15){
                if(conversor == 3){
                    NumTextCachorro++;
                }
                if(conversor > 3){
                    conversor = 0;
                }
                if(NumTextCachorro > 10){
                    NumTextCachorro = 9;

                }
            }
        }
    }

    if(Nivel > 15 && Nivel <= 20){  // SE NIVEL MENOR QUE 15 E MAIOR QUE 20 TEM QUE ACERTAR 9 PATOS

        if(conversor == 3){
            PiscaIcone++;
        }
        if(conversor > 3){
            conversor = 0;
        }
        if(PiscaIcone % 5 == 0){
            IconeDuck[1].z = IconeDuck[1].z * -1;
            IconeDuck[2].z = IconeDuck[2].z * -1;
            IconeDuck[3].z = IconeDuck[3].z * -1;
            IconeDuck[4].z = IconeDuck[4].z * -1;
            IconeDuck[5].z = IconeDuck[5].z * -1;
            IconeDuck[6].z = IconeDuck[6].z * -1;
        }

        if(PatosMortos >= 9 && PiscaIcone >= 40){

            if(PatosMortos == 10){
                Score += 10000;
            }
            if(ConstanteH >0){
                ConstanteH += 0.10;
            }
            else{
                ConstanteH = (ConstanteH * -1) + 0.10;//AUMENTA VELOCIDADE ACADA NIVEL
            }
            if(ConstanteV >0){
                ConstanteV += 0.10;
            }
            else{
                ConstanteV = (ConstanteV * -1) + 0.10;
            }
            NumPatos = 0;
            NumErros = 0;         //REINICIA ALGUNS DADOS
            PatosMortos = 0;
            voa = 0;
            acao = 0;
            andaCachorro = 0;
            cheiracachorro = 0;
            contadorcheiradas = 0;
            PiscaIcone = 0;
            Nivel++;


            CorDoIcone[1] = 0; CorDoIcone[6] = 0;
            CorDoIcone[2] = 0; CorDoIcone[7] = 0;
            CorDoIcone[3] = 0; CorDoIcone[8] = 0;
            CorDoIcone[4] = 0; CorDoIcone[9] = 0;
            CorDoIcone[5] = 0; CorDoIcone[10] = 0;


            TexturaDogwalk.x = 0;
            TexturaDogwalk.y = 37.5;
            TexturaDogwalk.z = 1;

            TexturaDuckPos.x = rand()% 165;
            TexturaDuckPos.y = 50;
            TexturaDuckPos.z = -1;
        }

        if(PatosMortos<9 && PiscaIcone >=40){
            glClearColor(0.3,0.734,1.0,0);

            IconeDuck[1].z = 1; IconeDuck[6].z = 1;
            IconeDuck[2].z = 1; IconeDuck[7].z = 1;
            IconeDuck[3].z = 1; IconeDuck[8].z = 1;
            IconeDuck[4].z = 1; IconeDuck[9].z = 1;
            IconeDuck[5].z = 1; IconeDuck[10].z = 1;

            risada++;
            GameOver = 1;
            TexturaDogwalk.z = -3;
            TexturaDogwalk.x = 75;
            if(risada < 15 && TexturaDogwalk.y <= 65){
                TexturaDogwalk.y +=3;

            }
            if(risada > 15){
                if(conversor == 3){
                    NumTextCachorro++;
                }
                if(conversor > 3){
                    conversor = 0;
                }
                if(NumTextCachorro > 10){
                    NumTextCachorro = 9;

                }
            }
        }
    }

    if(Nivel >20){  // SE NIVEL MAIOR QUE 20 TEM QUE ACERTAR 10 PATOS

        if(conversor == 3){
            PiscaIcone++;
        }
        if(conversor > 3){
            conversor = 0;
        }
        if(PiscaIcone % 5 == 0){
            IconeDuck[1].z = IconeDuck[1].z * -1;
            IconeDuck[2].z = IconeDuck[2].z * -1;
            IconeDuck[3].z = IconeDuck[3].z * -1;
            IconeDuck[4].z = IconeDuck[4].z * -1;
            IconeDuck[5].z = IconeDuck[5].z * -1;
            IconeDuck[6].z = IconeDuck[6].z * -1;
        }

        if(PatosMortos >= 10 && PiscaIcone >= 40){

            if(PatosMortos == 10){
                Score += 10000;
            }
            if(ConstanteH >0){
                ConstanteH += 0.10;
            }
            else{
                ConstanteH = (ConstanteH * -1) + 0.10;
            }
            if(ConstanteV >0){
                ConstanteV += 0.10;
            }
            else{
                ConstanteV = (ConstanteV * -1) + 0.10;
            }

            NumPatos = 0;
            NumErros = 0;         //REINICIA ALGUNS DADOS
            PatosMortos = 0;
            voa = 0;
            acao = 0;
            andaCachorro = 0;
            cheiracachorro = 0;
            contadorcheiradas = 0;
            PiscaIcone = 0;
            Nivel++;


            CorDoIcone[1] = 0; CorDoIcone[6] = 0;
            CorDoIcone[2] = 0; CorDoIcone[7] = 0;
            CorDoIcone[3] = 0; CorDoIcone[8] = 0;
            CorDoIcone[4] = 0; CorDoIcone[9] = 0;
            CorDoIcone[5] = 0; CorDoIcone[10] = 0;


            TexturaDogwalk.x = 0;
            TexturaDogwalk.y = 37.5;
            TexturaDogwalk.z = 1;

            TexturaDuckPos.x = rand()% 165;
            TexturaDuckPos.y = 50;
            TexturaDuckPos.z = -1;
        }

        if(PatosMortos<10 && PiscaIcone >=40){
            glClearColor(0.3,0.734,1.0,0);

            IconeDuck[1].z = 1; IconeDuck[6].z = 1;
            IconeDuck[2].z = 1; IconeDuck[7].z = 1;
            IconeDuck[3].z = 1; IconeDuck[8].z = 1;
            IconeDuck[4].z = 1; IconeDuck[9].z = 1;
            IconeDuck[5].z = 1; IconeDuck[10].z = 1;

            risada++;
            GameOver = 1;
            TexturaDogwalk.z = -3;
            TexturaDogwalk.x = 75;
            if(risada < 15 && TexturaDogwalk.y <= 65){
                TexturaDogwalk.y +=3;
            }
            if(risada > 15){
                if(conversor == 3){
                    NumTextCachorro++;
                }
                if(conversor > 3){
                    conversor = 0;
                }
                if(NumTextCachorro > 10){
                    NumTextCachorro = 9;

                }
            }
        }
    }

}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(800, 700);
   glutInitWindowPosition(350, 0);

   srand(time(NULL));

   glutCreateWindow("SUPER DUCK HUNT");
   inicializa();
   init();
   glutReshapeFunc(redimensiona);
   glutKeyboardFunc(teclado);
   glutDisplayFunc(desenha);
   glutPassiveMotionFunc(movimento_do_mouse);
   glutSetCursor(GLUT_CURSOR_CROSSHAIR);
   glutMouseFunc(tiro);
   glutTimerFunc(33,atualiza,0);


   glutMainLoop();
   return 0;
}
