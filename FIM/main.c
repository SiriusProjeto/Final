//DECLARA ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
//DECLARA C
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>


// CONSTANTES DO DISPLAY
const int LARGURA_TELA = 1280;
const int ALTURA_TELA = 720;

const int BOT_INICIO_X1 = 960;
const int BOT_INICIO_X2 = 1220;
const int BOT_INICIO_Y1 = 657;
const int BOT_INICIO_Y2 = 580;

const int BOT_PROX_X1 = 25;
const int BOT_PROX_X2 = 285;
const int BOT_PROX_Y1 = 102;
const int BOT_PROX_Y2 = 25;

const int JUP_BOX_X1 = 75;
const int JUP_BOX_X2 = 161;
const int JUP_BOX_Y1 = 253;
const int JUP_BOX_Y2 = 178;

//PARTES DO JOGO
#define P_APRESENTACAO 0
#define P_MENU 1
#define P_BOASVINDAS 2
#define P_TRANSICAO_NIVEL_1 3
#define P_NIVEL_1 4
#define P_TRANSICAO_NIVEL_2 5
#define P_NIVEL_2 6
#define P_TRANSICAO_NIVEL_3 7
#define P_NIVEL_3 8
#define P_EXPLICACOES 9
#define P_FINAL 10


//VARIAVEIS ALLEGRO
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

//ALLEGRO_FONT *titulo = NULL;
ALLEGRO_BITMAP *x = NULL;
ALLEGRO_COLOR cor_menu;
ALLEGRO_COLOR cor_titulo;

ALLEGRO_BITMAP *dicas[6] = {NULL, NULL, NULL, NULL, NULL, NULL};

ALLEGRO_BITMAP *estados[26] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

ALLEGRO_BITMAP *terra_concluida = NULL;
ALLEGRO_BITMAP *acre = NULL;
ALLEGRO_BITMAP *alagoas = NULL;
ALLEGRO_BITMAP *amapa = NULL;
ALLEGRO_BITMAP *amazonas = NULL;
ALLEGRO_BITMAP *bahia = NULL;
ALLEGRO_BITMAP *ceara = NULL;
ALLEGRO_BITMAP *espirito_santo = NULL;
ALLEGRO_BITMAP *goias = NULL;
ALLEGRO_BITMAP *maranhao = NULL;
ALLEGRO_BITMAP *mato_grosso = NULL;
ALLEGRO_BITMAP *mato_grosso_do_sul = NULL;
ALLEGRO_BITMAP *minas_gerais = NULL;
ALLEGRO_BITMAP *para = NULL;
ALLEGRO_BITMAP *paraiba = NULL;
ALLEGRO_BITMAP *parana = NULL;
ALLEGRO_BITMAP *pernambuco = NULL;
ALLEGRO_BITMAP *piaui = NULL;
ALLEGRO_BITMAP *rio_de_janeiro = NULL;
ALLEGRO_BITMAP *rio_grande_do_norte = NULL;
ALLEGRO_BITMAP *rio_grande_do_sul = NULL;
ALLEGRO_BITMAP *rondonia = NULL;
ALLEGRO_BITMAP *roraima = NULL;
ALLEGRO_BITMAP *santa_catarina = NULL;
ALLEGRO_BITMAP *sao_paulo = NULL;
ALLEGRO_BITMAP *sergipe = NULL;
ALLEGRO_BITMAP *tocantins = NULL;

ALLEGRO_BITMAP *agradecimento = NULL;

ALLEGRO_BITMAP *qual_nome_estado = NULL;

ALLEGRO_BITMAP *apresentacao_img[10] = {NULL, NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL};

ALLEGRO_BITMAP *correta = NULL;

//VARIAVEIS DE CONTROLE
int controle = 0;
int estado = 0;
int n_alternativa = 1;
int passa_pin = 0;
int dica_i = 0;

int inicializar(){
	printf(">>> Iniciando o jogo...\n");
	int sucesso = 0;

	printf(">>> Iniciando Funcoes\n");
	if(!al_init()){
		fprintf(stderr, "al_init\n");
	}else if(!(janela = al_create_display(LARGURA_TELA,ALTURA_TELA))){
		fprintf(stderr, "al_create_display\n");
	}else if(!al_init_primitives_addon()){
		fprintf(stderr, "al_init_primitives_addon\n");
	}else if (!al_init_font_addon()) {
		fprintf(stderr, "inicializa_font\n");
	}
	/*else if(!(titulo = al_load_font("res/font/comic.ttf", 48, 0))){
		fprintf(stderr, "erro na fonte do titulo\n");

	}*/

	else if(!al_install_keyboard()){
		fprintf(stderr, "al_install_keyboard\n");
	}else if(!al_install_joystick()){
		fprintf(stderr, "al_install_joystick\n");
	}else if(!al_install_mouse()){
		fprintf(stderr, "al_install_mouse\n");
	}else if (!(fila_eventos = al_create_event_queue())) {
		fprintf(stderr, "al_create_event_queue\n");
	}else if(!al_install_mouse()){
		fprintf(stderr, "al_install_mouse\n");
	}else if(!al_init_image_addon()){
		fprintf(stderr, "al_init_image_addon\n");
	}else {
		sucesso = 1;

        al_set_window_title(janela, "*SELBY SPACE*");// DEFINE NOME DA JANELA
        al_register_event_source(fila_eventos, al_get_display_event_source(janela)); /*Registra os eventos que ocorrem dentro da janela*/
        al_register_event_source(fila_eventos, al_get_keyboard_event_source()); /*Registra os eventos do teclado*/

        printf(">>> Funcoes Iniciadas\n");
    }
}

void troca_tela(ALLEGRO_BITMAP *img1, ALLEGRO_BITMAP *img2){
	al_destroy_bitmap(img1);
	al_flip_display();
	al_draw_bitmap(img2, 0, 0, 0);
	al_flip_display();
}

void destroy(){
	if(janela)	al_destroy_display(janela);
//	if(titulo) al_destroy_font(titulo);
//	if(titulo) al_destroy_font(titulo);
	if(fila_eventos) al_destroy_event_queue(fila_eventos);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_joystick();
	al_uninstall_audio();
	al_shutdown_image_addon();
	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_shutdown_primitives_addon();
}

void mover_bitmap_em_x(ALLEGRO_BITMAP *bitmap, int x, int max){
    if(x < max){
        while(x <= max){
            al_draw_bitmap(bitmap, x, 0, 0);
            al_flip_display();
            x = x + 5;
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
    else if(x > max){
        while(x >= max){
            al_draw_bitmap(bitmap, x, 0, 0);
            al_flip_display();
            x = x - 5;
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
}

void intercala_tela(ALLEGRO_BITMAP *img1, ALLEGRO_BITMAP *img2, float tempo_de_trocar, int temporizador){
    int mudanca = 1;
    while(temporizador != 0){
        if (temporizador > 0) temporizador--;
            if(mudanca == 1){
                al_draw_bitmap(img1, 0, 0, 0);
                al_flip_display();
                al_clear_to_color(al_map_rgb(0, 0, 0));
                mudanca = mudanca * -1;
                al_rest(tempo_de_trocar);
            }
            if(mudanca == -1){
                al_draw_bitmap(img2, 0, 0, 0);
                al_flip_display();
                al_clear_to_color(al_map_rgb(0, 0, 0));
                mudanca = mudanca * -1;
                al_rest(tempo_de_trocar);
        }
    }
}

void apresentacao(){
	printf(">>> Declara vetor da apresentacao");
	//VARIAVEL DA APRESENTAÇÂO

	printf(">>> Atribui valor ao vetor apresentação\n");
	apresentacao_img[0] = al_load_bitmap("res/img/01_APRESENTACAO/a1.bmp");
	apresentacao_img[1] = al_load_bitmap("res/img/01_APRESENTACAO/a2.bmp");
	apresentacao_img[2] = al_load_bitmap("res/img/01_APRESENTACAO/a3.bmp");
	apresentacao_img[3] = al_load_bitmap("res/img/01_APRESENTACAO/a4.bmp");
	apresentacao_img[4] = al_load_bitmap("res/img/01_APRESENTACAO/a5.bmp");
	apresentacao_img[5] = al_load_bitmap("res/img/01_APRESENTACAO/a6.bmp");
	apresentacao_img[6] = al_load_bitmap("res/img/01_APRESENTACAO/a7.bmp");
	apresentacao_img[7] = al_load_bitmap("res/img/01_APRESENTACAO/a8.bmp");
	apresentacao_img[8] = al_load_bitmap("res/img/01_APRESENTACAO/a9.bmp");
	apresentacao_img[9] = al_load_bitmap("res/img/01_APRESENTACAO/a10.bmp");
	printf(">>> Valores atribuidos\n");

	printf(">>> Inicializa apresentação\n");
	al_draw_bitmap(apresentacao_img[0], 0, 0, 0);
	al_rest(1.0);
	al_flip_display();
	troca_tela(apresentacao_img[0], apresentacao_img[1]);
	al_rest(2.5);
	troca_tela(apresentacao_img[1], apresentacao_img[2]);
	al_rest(0.1);
	troca_tela(apresentacao_img[2], apresentacao_img[3]);
	al_rest(0.1);
	troca_tela(apresentacao_img[3], apresentacao_img[4]);
	al_rest(0.1);
	troca_tela(apresentacao_img[4], apresentacao_img[5]);
	al_rest(0.1);
	troca_tela(apresentacao_img[5], apresentacao_img[6]);
	al_rest(0.1);
	troca_tela(apresentacao_img[6], apresentacao_img[7]);
	al_rest(0.1);
	troca_tela(apresentacao_img[7], apresentacao_img[8]);
	al_rest(0.1);
	troca_tela(apresentacao_img[8], apresentacao_img[9]);
	al_destroy_bitmap(apresentacao_img[9]);
	//al_flip_display();

	printf(">>> Finaliza apresentação\n");


	controle++;
}

void desenha_tela_inicio(){
	printf(">>> Inicia função desenha tela inicio\n");
	ALLEGRO_BITMAP *tela_inicio = NULL;
	ALLEGRO_BITMAP *botao_inicio = NULL;

	tela_inicio = al_load_bitmap("res/img/02_MENU/menu.bmp");

	botao_inicio = al_load_bitmap("res/img/02_MENU/botao_iniciar.png");
	printf("VAr declaradas");
    //if (!botao_inicio){
        //printf("Falha ao criar botão de saída");
        //return -1;
    //}

	printf("%d\n",botao_inicio);
	printf("desenhando bitmaps");
	al_draw_bitmap(tela_inicio, 0, 0, 0);
	al_draw_bitmap(botao_inicio, 960, 580, 0);
	al_flip_display();


	printf(">>> Tela de inicio desenhada\n");
}

int pega_clique_passa(int bot1a,int bot1b,int bot2a,int bot2b){
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	ALLEGRO_FONT *fonte = NULL;

	if (!al_install_mouse()){
		printf("Falha ao inicializar o teclado");
	}


	if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
		printf("Falha ao atribuir ponteiro do mouse");
		return -1;
	}

	fila_eventos = al_create_event_queue();
	if (!fila_eventos){
		printf("Falha ao criar fila de eventos");
		al_destroy_display(janela);
	}

	al_register_event_source(fila_eventos, al_get_mouse_event_source());

	int no_botao = 0;

	int sair = 0;
	int tecla = 0;

	while (!sair){
		while(!al_is_event_queue_empty(fila_eventos)){
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
				if (evento.mouse.x >= bot1a && evento.mouse.x <= bot1b && evento.mouse.y <= bot2a && evento.mouse.y >= bot2b){
					return 1;
				}
			} else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				sair = 1;
			}
		}
	}

	al_destroy_event_queue(fila_eventos);

}

void menu(){
	printf(">>> Inicio função menu\n");
	desenha_tela_inicio();
	al_flip_display();
	{
		if(pega_clique_passa(BOT_INICIO_X1,BOT_INICIO_X2,BOT_INICIO_Y1,BOT_INICIO_Y2) == 1){
			controle++;
		}
	}
}

void boas_vindas(){
	ALLEGRO_BITMAP *boasvindas[4] = {NULL,NULL,NULL};
	ALLEGRO_BITMAP *botaoproximo = NULL;

	boasvindas[0] = al_load_bitmap("res/img/03_BOASVINDAS/b1.bmp");
	boasvindas[1] = al_load_bitmap("res/img/03_BOASVINDAS/b2.bmp");
	boasvindas[2] = al_load_bitmap("res/img/03_BOASVINDAS/b3.bmp");
	boasvindas[3] = al_load_bitmap("res/img/03_BOASVINDAS/b4.bmp");

	botaoproximo = al_load_bitmap("res/img/03_BOASVINDAS/P0.png");


	al_draw_bitmap(boasvindas[0], 0, 0, 0);
	al_draw_bitmap(botaoproximo, 25, 25, 0);
	al_flip_display();

	if(pega_clique_passa(BOT_PROX_X1,BOT_PROX_X2,BOT_PROX_Y1,BOT_PROX_Y2) == 1){

		al_draw_bitmap(boasvindas[1], 0, 0, 0);
		al_draw_bitmap(botaoproximo, 25, 25, 0);
		al_flip_display();
		al_destroy_bitmap(boasvindas[0]);

		if(pega_clique_passa(BOT_PROX_X1,BOT_PROX_X2,BOT_PROX_Y1,BOT_PROX_Y2) == 1){
			al_draw_bitmap(boasvindas[2], 0, 0, 0);
			al_draw_bitmap(botaoproximo, 25, 25, 0);
			al_flip_display();
			al_destroy_bitmap(boasvindas[1]);

			if(pega_clique_passa(BOT_PROX_X1,BOT_PROX_X2,BOT_PROX_Y1,BOT_PROX_Y2) == 1){
				al_draw_bitmap(boasvindas[3], 0, 0, 0);
				al_draw_bitmap(botaoproximo, 25, 25, 0);
				al_flip_display();
				al_destroy_bitmap(boasvindas[2]);
			}
		}
	}

	if(pega_clique_passa(BOT_PROX_X1,BOT_PROX_X2,BOT_PROX_Y1,BOT_PROX_Y2) == 1){
		controle++;
		al_destroy_bitmap(botaoproximo);
		al_destroy_bitmap(boasvindas[3]);
	}
}

void transicao_nivel(){

	int t;

	printf(">>> Inicia função desenha trasição\n");
	ALLEGRO_BITMAP *inicia = NULL;
	ALLEGRO_BITMAP *botao = NULL;
	ALLEGRO_BITMAP *explica = NULL;
    ALLEGRO_BITMAP *jogar = NULL;


	inicia = al_load_bitmap("res/img/04_NV1/i.bmp");
	botao = al_load_bitmap("res/img/04_NV1/bot.png");
	explica = al_load_bitmap("res/img/04_NV1/explica.bmp");
    jogar = al_load_bitmap("res/img/04_NV1/JOGAR.png");


	printf("VAr declaradas");
    //if (!botao_inicio){
        //printf("Falha ao criar botão de saída");
        //return -1;
    //}

	printf("%d\n",inicia);
	printf("desenhando bitmaps");
	al_draw_bitmap(inicia, 0, 0, 0);
    al_draw_bitmap(botao, 860, 580, 0);
	al_flip_display();
	pega_clique_passa(BOT_INICIO_X1,BOT_INICIO_X2,BOT_INICIO_Y1,BOT_INICIO_Y2);

	al_destroy_bitmap(inicia);
    al_destroy_bitmap(botao);


	al_draw_bitmap(explica,0,0,0);
	al_flip_display();
	printf("\n\n\nEsperando para desenhar botão jogar\n");
	al_rest(3.0);
	printf("desenhando botao jogar\n");
	al_draw_bitmap(jogar, 25, 25, 0);
	al_flip_display();
	printf("Esperando clique\n");
	pega_clique_passa(BOT_PROX_X1,BOT_PROX_X2,BOT_PROX_Y1,BOT_PROX_Y2);

    al_destroy_bitmap(explica);
	al_destroy_bitmap(jogar);
	controle++;

}

void nivel1(){
    ALLEGRO_BITMAP *apresenta_mercurio = NULL;
    ALLEGRO_BITMAP *botao_inicio = NULL;
    ALLEGRO_BITMAP *palavra[2] = {NULL,NULL};

    ALLEGRO_BITMAP *alternativaP1[2] = {NULL, NULL};
    ALLEGRO_BITMAP *alternativaP2[2] = {NULL, NULL};

    ALLEGRO_BITMAP *acerto[2] = {NULL, NULL};
    ALLEGRO_BITMAP *erro[2] = {NULL, NULL};


	apresenta_mercurio = al_load_bitmap("res/img/04_NV1/TMERC.jpg");
	botao_inicio = al_load_bitmap("res/img/04_NV1/P0.png");


    palavra[0] = al_load_bitmap("res/img/04_NV1/pal1.bmp");
    alternativaP1[0] = al_load_bitmap("res/img/04_NV1/ox1.png");
    alternativaP1[1] = al_load_bitmap("res/img/04_NV1/ox2.png");
    acerto[0] = al_load_bitmap("res/img/04_NV1/acertoP1.png");
    erro[0] = al_load_bitmap("res/img/04_NV1/erroP1.png");

    palavra[1] = al_load_bitmap("res/img/04_NV1/pal2.bmp");
    alternativaP2[0] = al_load_bitmap("res/img/04_NV1/ferro_incNOK.png");
    alternativaP2[1] = al_load_bitmap("res/img/04_NV1/ferro_incOK.png");
    acerto[1] = al_load_bitmap("res/img/04_NV1/ferrofimOK.png");

	al_draw_bitmap(apresenta_mercurio, 0, 0, 0);

	al_flip_display();
	al_rest(2.0);
    al_draw_bitmap(botao_inicio, 860, 580, 0);
    al_flip_display();



    if(pega_clique_passa(BOT_INICIO_X1,BOT_INICIO_X2,BOT_INICIO_Y1,BOT_INICIO_Y2) == 1){
        al_destroy_bitmap(apresenta_mercurio);
        al_draw_bitmap(palavra[0], 0, 0, 0);
        al_draw_bitmap(alternativaP1[0], 17, 432, 0);
        al_draw_bitmap(alternativaP1[1], 638, 432, 0);
        al_flip_display();

        dicas[0] = al_load_bitmap("res/img/objetos_diversos/dica_1.png");
        al_draw_bitmap(dicas[0], 880, 250, 0);
        al_flip_display();

        if(pega_clique_passa(17,621,BOT_INICIO_Y1,BOT_INICIO_Y2) == 1){
        al_destroy_bitmap(alternativaP1[0]);
        al_draw_bitmap(acerto[0], 17, 432, 0);
        al_draw_bitmap(botao_inicio, 860, 580, 0);
        al_flip_display();

        }
    }
    if(pega_clique_passa(BOT_INICIO_X1,BOT_INICIO_X2,BOT_INICIO_Y1,BOT_INICIO_Y2) == 1){

        al_clear_to_color(al_map_rgb(0,0,0));
        al_destroy_bitmap(palavra[0]);
        al_draw_bitmap(palavra[1], 0, 0, 0);
        al_draw_bitmap(alternativaP2[0], 17, 432, 0);
        al_draw_bitmap(alternativaP2[1], 638, 432, 0);
        al_flip_display();
        dicas[1] = al_load_bitmap("res/img/objetos_diversos/dica_2.png");
        al_draw_bitmap(dicas[1], 810, 250, 0);
        al_flip_display();
        //al_rest(5.0);

        if(pega_clique_passa(BOT_INICIO_X1,BOT_INICIO_X2,BOT_INICIO_Y1,BOT_INICIO_Y2) == 1){
            al_destroy_bitmap(alternativaP1[1]);
            al_draw_bitmap(acerto[1], 698, 412, 0);
            //al_draw_bitmap(botao_inicio, 860, 580, 0);
            al_flip_display();
            al_rest(5.0);
        }
    }
    controle++;


}



void alternativas(){
    int x, y;
    switch(n_alternativa){

        case 1:
            x = 900;
            y = 300;
            al_draw_bitmap(sao_paulo, 750, 200, 0);
            al_draw_bitmap(acre, x, y, 0);
            al_draw_bitmap(espirito_santo, 700, 400, 0);
            al_flip_display();
            printf("Desenho os role");

            dicas[2] = al_load_bitmap("res/img/objetos_diversos/dica_3.png");
            al_draw_bitmap(dicas[2], 200, 500, 0);
            al_flip_display();

            if(pega_clique_passa(x, x + al_get_bitmap_width(acre), y + al_get_bitmap_height(acre), y)){
                printf("\n\nClique OK\n\n");
                al_clear_to_color(al_map_rgb(0, 0, 0));
                /*al_destroy_bitmap(sao_paulo);
                al_destroy_bitmap(acre);
                al_destroy_bitmap(espirito_santo);*/
                n_alternativa++;
                passa_pin++;


            }

        printf("Saiu do clique %d %d",n_alternativa, passa_pin);

        break;

        case 2:
            x = 800;
            y = 200;
            al_draw_bitmap(alagoas, x, y, 0);
            al_draw_bitmap(bahia, 800, 300, 0);
            al_draw_bitmap(tocantins, 730, 400, 0);
            dicas[3] = al_load_bitmap("res/img/objetos_diversos/dica_4.png");
            al_draw_bitmap(dicas[3], 200, 500, 0);
            al_flip_display();
            al_flip_display();

        if(pega_clique_passa(x, x + al_get_bitmap_width(alagoas), y + al_get_bitmap_height(alagoas), y)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            n_alternativa++;
            passa_pin++;
        }
        break;

        case 3:
            x = 800;
            y = 400;
            al_draw_bitmap(rio_de_janeiro, 700, 200, 0);
            al_draw_bitmap(mato_grosso, 650, 300, 0);
            al_draw_bitmap(amapa, x, y, 0);
            al_flip_display();

        if(pega_clique_passa(x, x + al_get_bitmap_width(amapa), y + al_get_bitmap_height(amapa), y)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            /*al_destroy_bitmap(rio_de_janeiro);
            al_destroy_bitmap(mato_grosso);
            al_destroy_bitmap(amapa);*/
            n_alternativa++;
            passa_pin++;

        }
        break;

        case 4:
            x = 850;
            y = 300;
            al_draw_bitmap(rio_grande_do_norte, 650, 200, 0);
            al_draw_bitmap(amazonas, x, y, 0);
            al_draw_bitmap(rio_grande_do_sul, 650, 400, 0);
            al_flip_display();

        if(pega_clique_passa(x, x + al_get_bitmap_width(amazonas), y + al_get_bitmap_height(amazonas), y)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            /*al_destroy_bitmap(rio_grande_do_norte);
            al_destroy_bitmap(amazonas);
            al_destroy_bitmap(rio_grande_do_sul);*/
            n_alternativa++;
            passa_pin++;

        }
        break;

    }


}

void desenha_estado(){
    while (passa_pin<4){
        al_draw_bitmap(estados[passa_pin], 0, 0, 0);
        al_draw_bitmap(qual_nome_estado, 650, 100, 0);
        al_flip_display();
        alternativas(passa_pin);
    }
    al_draw_bitmap(terra_concluida, 0, 0, 0);
    al_flip_display();
    al_rest(3.0);

    al_destroy_bitmap(estados[0]);
    al_destroy_bitmap(estados[1]);
    al_destroy_bitmap(estados[2]);
    al_destroy_bitmap(estados[3]);
    al_destroy_bitmap(estados[4]);
    al_destroy_bitmap(estados[5]);
    al_destroy_bitmap(estados[6]);
    al_destroy_bitmap(estados[7]);
    al_destroy_bitmap(estados[8]);
    al_destroy_bitmap(estados[9]);
    al_destroy_bitmap(estados[10]);
    al_destroy_bitmap(estados[11]);
    al_destroy_bitmap(estados[12]);
    al_destroy_bitmap(estados[13]);
    al_destroy_bitmap(estados[14]);
    al_destroy_bitmap(estados[15]);
    al_destroy_bitmap(estados[16]);
    al_destroy_bitmap(estados[17]);
    al_destroy_bitmap(estados[18]);
    al_destroy_bitmap(estados[19]);
    al_destroy_bitmap(estados[20]);
    al_destroy_bitmap(estados[21]);
    al_destroy_bitmap(estados[22]);
    al_destroy_bitmap(estados[23]);
    al_destroy_bitmap(estados[24]);
    al_destroy_bitmap(estados[25]);

    al_destroy_bitmap(acre);
    al_destroy_bitmap(alagoas);
    al_destroy_bitmap(amapa);
    al_destroy_bitmap(amazonas);
    al_destroy_bitmap(bahia);
    al_destroy_bitmap(ceara);
    /*al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);
    al_destroy_bitmap(acre);*/
}

void transicao_nivel_2(){
    ALLEGRO_BITMAP *explica = NULL;
    ALLEGRO_BITMAP *jogar = NULL;

    explica = al_load_bitmap("res/img/transicoes_de_tela/transicaoTerra.jpg");
    jogar = al_load_bitmap("res/img/04_NV1/JOGAR.png");
    al_draw_bitmap(explica, 0,0,0);

    al_flip_display();
	printf("\n\n\nEsperando para desenhar botão jogar\n");
	al_rest(3.0);
	printf("desenhando botao jogar\n");
	al_draw_bitmap(jogar, 25, 25, 0);
	al_flip_display();
	printf("Esperando clique\n");
	pega_clique_passa(BOT_PROX_X1,BOT_PROX_X2,BOT_PROX_Y1,BOT_PROX_Y2);

    al_destroy_bitmap(explica);
	al_destroy_bitmap(jogar);

	controle++;

}


void fase_terra(){
    estados[0] = al_load_bitmap("res/img/fase_Terra/estados/posicao_acre.jpg");
    estados[1] = al_load_bitmap("res/img/fase_Terra/estados/posicao_alagoas.jpg");
    estados[2] = al_load_bitmap("res/img/fase_Terra/estados/posicao_amapa.jpg");
    estados[3] = al_load_bitmap("res/img/fase_Terra/estados/posicao_amazonas.jpg");
    estados[4] = al_load_bitmap("res/img/fase_Terra/estados/posicao_bahia.jpg");
    estados[5] = al_load_bitmap("res/img/fase_Terra/estados/posicao_ceara.jpg");
    estados[6] = al_load_bitmap("res/img/fase_Terra/estados/posicao_espirito_santo.jpg");
    estados[7] = al_load_bitmap("res/img/fase_Terra/estados/posicao_goias.jpg");
    estados[8] = al_load_bitmap("res/img/fase_Terra/estados/posicao_maranhao.jpg");
    estados[9] = al_load_bitmap("res/img/fase_Terra/estados/posicao_mato_grosso.jpg");
    estados[10] = al_load_bitmap("res/img/fase_Terra/estados/posicao_mato_grosso_do_sul.jpg");
    estados[11] = al_load_bitmap("res/img/fase_Terra/estados/posicao_minas_gerais.jpg");
    estados[12] = al_load_bitmap("res/img/fase_Terra/estados/posicao_para.jpg");
    estados[13] = al_load_bitmap("res/img/fase_Terra/estados/posicao_paraiba.jpg");
    estados[14] = al_load_bitmap("res/img/fase_Terra/estados/posicao_parana.jpg");
    estados[15] = al_load_bitmap("res/img/fase_Terra/estados/posicao_pernambuco.jpg");
    estados[16] = al_load_bitmap("res/img/fase_Terra/estados/posicao_piaui.jpg");
    estados[17] = al_load_bitmap("res/img/fase_Terra/estados/posicao_rio_de_janeiro.jpg");
    estados[18] = al_load_bitmap("res/img/fase_Terra/estados/posicao_rio_grande_do_norte.jpg");
    estados[19] = al_load_bitmap("res/img/fase_Terra/estados/posicao_rio_grande_do_sul.jpg");
    estados[20] = al_load_bitmap("res/img/fase_Terra/estados/posicao_rondonia.jpg");
    estados[21] = al_load_bitmap("res/img/fase_Terra/estados/posicao_roraima.jpg");
    estados[22] = al_load_bitmap("res/img/fase_Terra/estados/posicao_santa_catarina.jpg");
    estados[23] = al_load_bitmap("res/img/fase_Terra/estados/posicao_sao_paulo.jpg");
    estados[24] = al_load_bitmap("res/img/fase_Terra/estados/posicao_sergipe.jpg");
    estados[25] = al_load_bitmap("res/img/fase_Terra/estados/posicao_tocantins.jpg");

    terra_concluida = al_load_bitmap("res/img/fase_Terra/estados/posicao_todos.jpg");

    acre = al_load_bitmap("res/img/fase_Terra/estados/acre.png");
    alagoas = al_load_bitmap("res/img/fase_Terra/estados/alagoas.png");
    amapa = al_load_bitmap("res/img/fase_Terra/estados/amapa.png");
    amazonas = al_load_bitmap("res/img/fase_Terra/estados/amazonas.png");
    bahia = al_load_bitmap("res/img/fase_Terra/estados/bahia.png");
    ceara = al_load_bitmap("res/img/fase_Terra/estados/ceara.png");
    espirito_santo = al_load_bitmap("res/img/fase_Terra/estados/espirito_santo.png");
    goias = al_load_bitmap("res/img/fase_Terra/estados/goias.png");
    maranhao = al_load_bitmap("res/img/fase_Terra/estados/maranhao.png");
    mato_grosso = al_load_bitmap("res/img/fase_Terra/estados/mato_grosso.png");
    mato_grosso_do_sul = al_load_bitmap("res/img/fase_Terra/estados/mato_grosso_do_sul.png");
    minas_gerais = al_load_bitmap("res/img/fase_Terra/estados/minas_gerais.png");
    para = al_load_bitmap("res/img/fase_Terra/estados/para.png");
    paraiba = al_load_bitmap("res/img/fase_Terra/estados/paraiba.png");
    parana = al_load_bitmap("res/img/fase_Terra/estados/parana.png");
    pernambuco = al_load_bitmap("res/img/fase_Terra/estados/pernambuco.png");
    piaui = al_load_bitmap("res/img/fase_Terra/estados/piaui.png");
    rio_de_janeiro = al_load_bitmap("res/img/fase_Terra/estados/rio_de_janeiro.png");
    rio_grande_do_norte = al_load_bitmap("res/img/fase_Terra/estados/rio_grande_do_norte.png");
    rio_grande_do_sul = al_load_bitmap("res/img/fase_Terra/estados/rio_grande_do_sul.png");
    roraima = al_load_bitmap("res/img/fase_Terra/estados/roraima.png");
    santa_catarina = al_load_bitmap("res/img/fase_Terra/estados/santa_catarina.png");
    sao_paulo = al_load_bitmap("res/img/fase_Terra/estados/sao_paulo.png");
    sergipe = al_load_bitmap("res/img/fase_Terra/estados/sergipe.png");
    tocantins = al_load_bitmap("res/img/fase_Terra/estados/tocantins.png");

    qual_nome_estado = al_load_bitmap("res/img/fase_Terra/estados/qual_nome_estado.png");

    desenha_estado(estado);

    controle++;
}

void transicao_nivel_3(){
    ALLEGRO_BITMAP *explica = NULL;
    ALLEGRO_BITMAP *jogar = NULL;

    explica = al_load_bitmap("res/img/transicoes_de_tela/TransicaoJupiter.jpg");
    jogar = al_load_bitmap("res/img/04_NV1/JOGAR.png");
    al_draw_bitmap(explica, 0,0,0);

    al_flip_display();
	printf("\n\n\nEsperando para desenhar botão jogar\n");
	al_rest(3.0);
	printf("desenhando botao jogar\n");
	al_draw_bitmap(jogar, 25, 25, 0);
	al_flip_display();
	printf("Esperando clique\n");
	pega_clique_passa(BOT_PROX_X1,BOT_PROX_X2,BOT_PROX_Y1,BOT_PROX_Y2);

    al_destroy_bitmap(explica);
	al_destroy_bitmap(jogar);

	controle++;

}

void fase_jupiter(){
    ALLEGRO_BITMAP *apresenta_mercurio = NULL;
    ALLEGRO_BITMAP *botao_inicio = NULL;
    ALLEGRO_BITMAP *pergunta[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
    int i=0;

    correta = al_load_bitmap("res/img/objetos_diversos/correta.png");

    pergunta[0] = al_load_bitmap("res/img/fase_Jupiter/faseJupiter.jpg");
    pergunta[1] = al_load_bitmap("res/img/fase_Jupiter/faseJupiter2.jpg");
    pergunta[2] = al_load_bitmap("res/img/fase_Jupiter/faseJupiter3.jpg");
    pergunta[3] = al_load_bitmap("res/img/fase_Jupiter/faseJupiter4.jpg");
    pergunta[4] = al_load_bitmap("res/img/fase_Jupiter/faseJupiter5.jpg");
    pergunta[5] = al_load_bitmap("res/img/fase_Jupiter/faseJupiter6.jpg");

    al_draw_bitmap(pergunta[0], 0, 0, 0);
    al_flip_display();

    while(i<6){
    if(i==0){

        if(pega_clique_passa(JUP_BOX_X1, JUP_BOX_X2, JUP_BOX_Y1+285, JUP_BOX_Y2+285)){
            al_draw_bitmap(correta, LARGURA_TELA/2 - 100, ALTURA_TELA/2 - 10, 0);
            al_flip_display();
            al_rest(3.0);
            i++;
            al_draw_bitmap(pergunta[i], 0, 0, 0);
            al_flip_display();
            al_destroy_bitmap(pergunta[i-1]);
            }
        }

    if(i==1){

        if(pega_clique_passa(JUP_BOX_X1, JUP_BOX_X2, JUP_BOX_Y1+285, JUP_BOX_Y2+285)){
            al_draw_bitmap(correta, LARGURA_TELA/2 - 100, ALTURA_TELA/2 - 10, 0);
            al_flip_display();
            al_rest(3.0);
            i++;
            al_draw_bitmap(pergunta[i], 0, 0, 0);
            al_flip_display();
            al_destroy_bitmap(pergunta[i-1]);
            }
        }

    if(i==2){

        if(pega_clique_passa(JUP_BOX_X1+650, JUP_BOX_X2+650, JUP_BOX_Y1, JUP_BOX_Y2)){
            al_draw_bitmap(correta, LARGURA_TELA/2 - 100, ALTURA_TELA/2 - 10, 0);
            al_flip_display();
            al_rest(3.0);
            i++;
            al_draw_bitmap(pergunta[i], 0, 0, 0);
            al_flip_display();
            al_destroy_bitmap(pergunta[i-1]);
            }
        }

    if(i==3){

        if(pega_clique_passa(JUP_BOX_X1+650, JUP_BOX_X2+650, JUP_BOX_Y1+285, JUP_BOX_Y2+285)){
            al_draw_bitmap(correta, LARGURA_TELA/2 - 100, ALTURA_TELA/2 - 10, 0);
            al_flip_display();
            al_rest(3.0);
            i++;
            al_draw_bitmap(pergunta[i], 0, 0, 0);
            al_flip_display();
            al_destroy_bitmap(pergunta[i-1]);
            }
        }

    if(i==4){

        if(pega_clique_passa(JUP_BOX_X1+650, JUP_BOX_X2+650, JUP_BOX_Y1+285, JUP_BOX_Y2+285)){
            al_draw_bitmap(correta, LARGURA_TELA/2 - 100, ALTURA_TELA/2 - 10, 0);
            al_flip_display();
            al_rest(3.0);
            i++;
            al_draw_bitmap(pergunta[i], 0, 0, 0);
            al_flip_display();
            al_destroy_bitmap(pergunta[i-1]);
            }
        }

    if(i==5){

        if(pega_clique_passa(JUP_BOX_X1, JUP_BOX_X2, JUP_BOX_Y1, JUP_BOX_Y2)){
            al_draw_bitmap(correta, LARGURA_TELA/2 - 100, ALTURA_TELA/2 - 10, 0);
            al_flip_display();
            al_rest(3.0);
            i++;

            }
        }
    }
al_destroy_bitmap(pergunta[i-1]);
controle++;

}

/*void coloca_dica(ALLEGRO_BITMAP *dica[10], int x, int y){
    if(dica_i >=6){
        al_draw_bitmap(dica[dica_i], x, y, 0);
        al_flip_display();
        al_destroy_bitmap(dica[dica_i-1]);
    }
}*/

void explica_planetas(){

    ALLEGRO_BITMAP *explica_planeta[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    ALLEGRO_BITMAP *avaliacao_planeta[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    agradecimento = al_load_bitmap("res/img/objetos_diversos/selby_agradece.jpg");
    al_draw_bitmap(agradecimento, 0,0,0);
    al_flip_display();
    al_rest(6.0);

    explica_planeta[0] = al_load_bitmap("res/img/transicoes_de_tela/transicaoMercurio.jpg");
    explica_planeta[1] = al_load_bitmap("res/img/transicoes_de_tela/transicaoVenus.png");
    explica_planeta[2] = al_load_bitmap("res/img/transicoes_de_tela/transicaoTerra.jpg");
    explica_planeta[3] = al_load_bitmap("res/img/transicoes_de_tela/transicaoMarte.jpg");
    explica_planeta[4] = al_load_bitmap("res/img/transicoes_de_tela/TransicaoJupiter.jpg");
    explica_planeta[5] = al_load_bitmap("res/img/transicoes_de_tela/transicaoSaturno.jpg");
    explica_planeta[6] = al_load_bitmap("res/img/transicoes_de_tela/transicaoUrano.jpg");
    explica_planeta[7] = al_load_bitmap("res/img/transicoes_de_tela/transicaoNetuno.jpg");

    avaliacao_planeta[0] = al_load_bitmap("res/img/transicoes_de_tela/avaliacao_mercurio.jpg");
    avaliacao_planeta[1] = al_load_bitmap("res/img/transicoes_de_tela/avaliacao_venus.jpg");
    avaliacao_planeta[2] = al_load_bitmap("res/img/transicoes_de_tela/avaliacao_terra.jpg");
    avaliacao_planeta[3] = al_load_bitmap("res/img/transicoes_de_tela/avaliacao_marte.jpg");
    avaliacao_planeta[4] = al_load_bitmap("res/img/transicoes_de_tela/avaliacao_jupiter.jpg");
    avaliacao_planeta[5] = al_load_bitmap("res/img/transicoes_de_tela/avaliacao_saturno.jpg");
    avaliacao_planeta[6] = al_load_bitmap("res/img/transicoes_de_tela/avaliacao_urano.jpg");
    avaliacao_planeta[7] = al_load_bitmap("res/img/transicoes_de_tela/avaliacao_netuno.jpg");

	al_draw_bitmap(explica_planeta[0], 0, 0, 0);
	al_flip_display();
	al_rest(1.0);
	mover_bitmap_em_x(avaliacao_planeta[0], 0, -2560);
	al_destroy_bitmap(avaliacao_planeta[0]);

    al_draw_bitmap(explica_planeta[1], 0, 0, 0);
	al_flip_display();
	al_rest(1.0);
	mover_bitmap_em_x(avaliacao_planeta[1], 0, -2560);
	al_destroy_bitmap(avaliacao_planeta[1]);

    al_draw_bitmap(explica_planeta[2], 0, 0, 0);
	al_flip_display();
	al_rest(1.0);
	mover_bitmap_em_x(avaliacao_planeta[2], 0, -2560);
	al_destroy_bitmap(avaliacao_planeta[2]);

    al_draw_bitmap(explica_planeta[3], 0, 0, 0);
	al_flip_display();
	al_rest(1.0);
	mover_bitmap_em_x(avaliacao_planeta[3], 0, -2560);
	al_destroy_bitmap(avaliacao_planeta[3]);

    al_draw_bitmap(explica_planeta[4], 0, 0, 0);
	al_flip_display();
	al_rest(1.0);
	mover_bitmap_em_x(avaliacao_planeta[4], 0, -2560);
	al_destroy_bitmap(avaliacao_planeta[4]);

    al_draw_bitmap(explica_planeta[5], 0, 0, 0);
	al_flip_display();
	al_rest(1.0);
	mover_bitmap_em_x(avaliacao_planeta[5], 0, -2560);
	al_destroy_bitmap(avaliacao_planeta[5]);

    al_draw_bitmap(explica_planeta[6], 0, 0, 0);
	al_flip_display();
	al_rest(1.0);
	mover_bitmap_em_x(avaliacao_planeta[6], 0, -2560);
	al_destroy_bitmap(avaliacao_planeta[6]);

    al_draw_bitmap(explica_planeta[7], 0, 0, 0);
	al_flip_display();
	al_rest(1.0);
	mover_bitmap_em_x(avaliacao_planeta[7], 0, -2560);
	al_destroy_bitmap(avaliacao_planeta[7]);

	controle++;

}

int main(){
	if(!inicializar()){
		return -1;
	}
 al_install_audio();
        al_init_acodec_addon();
        al_reserve_samples(1);

        ALLEGRO_AUDIO_STREAM *som = NULL;
        som = al_load_audio_stream("back.wav", 4, 1024);
        al_attach_audio_stream_to_mixer(som, al_get_default_mixer());
        al_set_audio_stream_playmode(som, ALLEGRO_PLAYMODE_LOOP);




	while(controle != P_FINAL){
		if(controle == P_APRESENTACAO){
            printf("controle atual: %d\n", controle);
			apresentacao();

		} else if(controle == P_MENU){
            printf("controle atual: %d\n", controle);
			menu();

		} else if(controle == P_BOASVINDAS){
            printf("controle atual: %d\n", controle);
			boas_vindas();

		} else if(controle == P_TRANSICAO_NIVEL_1){
            printf("controle atual: %d\n", controle);
			transicao_nivel();

		}else if(controle == P_NIVEL_1){
            printf("controle atual: %d\n", controle);
            nivel1();

        } else if(controle == P_TRANSICAO_NIVEL_2){
            printf("controle atual: %d\n", controle);
            transicao_nivel_2();

		}else if(controle == P_NIVEL_2){
            printf("controle atual: %d\n", controle);
            fase_terra();

        } else if(controle == P_TRANSICAO_NIVEL_3){
            printf("controle atual: %d\n", controle);
            transicao_nivel_3();

		}else if(controle == P_NIVEL_3){
            printf("controle atual: %d\n", controle);
            fase_jupiter();

        } else if(controle == P_EXPLICACOES){
            printf("controle atual: %d\n", controle);
            explica_planetas();

			break;
		}
	}
	destroy();
	printf("\n-------------------------\nA EXECUÇAO DO JOGO TERMINOU\n-------------------------");
	return 0;
}

