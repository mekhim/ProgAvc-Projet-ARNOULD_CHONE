#include <SDL.h>
#include <math.h>
#include "fonction.h"
#define PI 3.14159265358979323846

int main()
{
	int i;
	int gameover = 0;
	SDL_Surface *screen , *temp , *temp2 , *temp3,*temp4,*temp5 , *temp6 , *temp7;
	SDL_Surface *TabImageCase[6];
	SDL_Surface *tab_image_ennemis[2];
	int d = 50;
	char key[SDLK_LAST] = {0};

	coor chemin[127];
	ini_chemin(chemin);

	enn ennemis[200];
	init_ennemis(ennemis);
	
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(816 ,816 , 0, 0);
	SDL_WM_SetCaption("Tower Defense", "Tower Defense");
	

	temp = SDL_LoadBMP("herbe.bmp");
	TabImageCase[0]=SDL_DisplayFormat(temp);
	temp2 = SDL_LoadBMP("montagne.bmp");
	TabImageCase[1]=SDL_DisplayFormat(temp2);
	temp3 = SDL_LoadBMP("chemin.bmp");
	TabImageCase[2]=SDL_DisplayFormat(temp3);
	temp4 = SDL_LoadBMP("eau.bmp");
	TabImageCase[3]=SDL_DisplayFormat(temp4);
	temp5 = SDL_LoadBMP("chemin.bmp");
	TabImageCase[4]=SDL_DisplayFormat(temp5);
	temp6 = SDL_LoadBMP("chemin.bmp");
	TabImageCase[5]=SDL_DisplayFormat(temp6);
	temp7 = SDL_LoadBMP("spriteSoldat1.bmp");
	tab_image_ennemis[0] = SDL_DisplayFormat(temp7);
	
	cm **carte = malloc(sizeof(struct case_map*) *17);

	for (i=0 ; i <17; i++)
		carte[i] = malloc(sizeof(struct case_map) * 17);

	lectureNiveau(carte);

	int possible_chemin = verifChemin(carte);
	defchemin(carte , emplacementDebut(carte)/17 , emplacementDebut(carte)%17 ,'e',chemin ,0);
	spawn_soldat(ennemis , chemin[0]);
	while (gameover != 1 && possible_chemin == 1)
		{
			evenement_clavier(key,&gameover);
			evenement_verifClavier(key,&d);
			afficheMap(TabImageCase ,carte , screen);
			affichage_ennemi(ennemis , tab_image_ennemis , screen);
			ennemis_moove(ennemis , chemin);
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Delay(d);
		}

	i = 0;

	///Libération mémoire///
	for (i=0 ; i < 17; i++)
		free(carte[i]);
	free(carte);
	for (i=0 ; i < 6; i++)
		SDL_FreeSurface(TabImageCase[i]);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(temp);
	SDL_FreeSurface(temp2);
	SDL_FreeSurface(temp3);
	SDL_FreeSurface(temp4);
	SDL_FreeSurface(temp5);
	SDL_FreeSurface(temp6);
	SDL_FreeSurface(temp7);
    SDL_Quit();
	return EXIT_SUCCESS;
}
	
