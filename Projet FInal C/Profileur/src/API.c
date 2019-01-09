/**
 * \file API.c
 * \brief Affiche un arbre en utilisant MLVLIB
 * \author PINTO Bruno
 *
 * Permet de parser des fichier.log
 *
 */


/*		### BIBLIOTHEQUE ###		*/
#include "../include/API.h"
#include "../include/Erreur.h"
/*		### STRUCT FONCTION PRIVEE###	*/
#define TAB_NOEUD_TAILLE_DEFAUT 16

typedef struct{
	const Noeud** tab;
	unsigned int nb_elem;
	unsigned int taille;
}Tab_noeud;

typedef struct{
	MLV_Image* frontend;
	MLV_Image* backend;
}Info_affichage;



#define OPTION_BAS_TAILLE_Y 120

/*		### DECLARATION FONCTION PRIVEE###	*/
static void init_fenetre();
static int init_info(Info_affichage* inf);
/**
 * 0: erreur d'allocation
 * 1: sinon
 */ 
static void libere_info(Info_affichage* inf);
static int init_tab_noeud(Tab_noeud* tab);
/**
 * 0: erreur d'allocation
 * 1: sinon
 */ 
static int ajout_tab_noeud(Tab_noeud* tab, const Noeud* n);
/**
 * 0: erreur d'allocation
 * 1: sinon
 */ 
static void libere_tab_noeud(Tab_noeud* tab);

static void parcours(const Arbre a, Info_affichage *inf, unsigned int x0 ,unsigned int y0,unsigned int xmax, unsigned int ymax, double temps_total);

static MLV_Color conv_id_couleur(const unsigned char id[3]);

static void affiche_nom(unsigned int x, unsigned int y, const char* nom);
static void affiche_info(const char* nom, double temps_seul, double temps_total);

static void affiche_bouton_bd();
/*		### DEFINITION FONCTION ###		*/

int init_tab_noeud(Tab_noeud* tab){
		
	tab->nb_elem = 0;
	tab->tab = malloc(sizeof(Noeud*) * TAB_NOEUD_TAILLE_DEFAUT);
	
	if(NULL == tab->tab){
		tab->taille = 0;
		return 0;
	}
		
	tab->taille = TAB_NOEUD_TAILLE_DEFAUT;	
	return 1;
}

void libere_tab_noeud(Tab_noeud* tab){
	free(tab->tab);
	tab->taille = tab->nb_elem = 0;
}

int ajout_tab_noeud(Tab_noeud* tab, const Noeud* n){
	const Noeud** tmp;
	
	if(tab->nb_elem == tab->taille){
		tmp = realloc(tab->tab, tab->taille * 2 * sizeof(Noeud*));
		if(NULL == tmp)
			return 0;
		tab->tab = tmp;
		tab->taille = (tab->taille) * 2;
	}
	tab->tab[tab->nb_elem] = n;
	(tab->nb_elem) += 1;
	
	return 1;
}

void init_fenetre(){
	MLV_create_full_screen_window_with_default_font( "PROFILER",
						"PROFILER",
						MLV_get_desktop_width(),
						MLV_get_desktop_height(),
						"../fichier/LOVES.ttf", 
						18);
}

int init_info(Info_affichage* inf){
	int x;
	int y;
	x =MLV_get_window_width();
	y = MLV_get_window_height() - OPTION_BAS_TAILLE_Y;
	
	inf->frontend = MLV_create_image(x, y);
	if(NULL == inf->frontend){
		return 0;
	}
	inf->backend = MLV_create_image(x, y);
	if(NULL == inf->backend){
		MLV_free_image(inf->frontend);
		return 0;
	}
	return 1;
}

void libere_info(Info_affichage* inf){
	MLV_free_image(inf->frontend);
	MLV_free_image(inf->backend);
}

void parcours(const Arbre a, Info_affichage *inf, unsigned int x0,unsigned int y0,unsigned int xmax,unsigned int ymax, double temps_total){
	Tab_noeud tab;
	Noeud* temp;
	int i;
	int ecart_x;
	int marge_x, marge_y;
	
	if(y0 > ymax || x0 > xmax)
		return;
	
	if(ymax - y0 < 10 || xmax - x0 < 10){
		MLV_draw_filled_rectangle_on_image(x0, y0, xmax - x0, ymax - y0, MLV_COLOR_WHITE, inf->frontend);
		MLV_draw_filled_rectangle_on_image(x0, y0, xmax - x0, ymax - y0, conv_id_couleur(a->id), inf->backend);
		return;
	}
	MLV_draw_filled_rectangle_on_image(x0, y0, xmax - x0, ymax - y0, conv_id_couleur(a->id), inf->backend);
	MLV_draw_filled_rectangle_on_image(x0, y0, xmax - x0, ymax - y0, MLV_COLOR_BLACK, inf->frontend);
	MLV_draw_filled_rectangle_on_image(x0+1, y0+1, xmax - x0 - 2, ymax - y0 - 2, MLV_rgba(0, 255 - 128 * (a->info.temps_total / temps_total), 255 - 128 * (a->info.temps_seul / temps_total), 255), inf->frontend);
	/*MLV_draw_text_on_image(x0, y0, "%s", MLV_COLOR_WHITE, inf->frontend, a->info.nom);*/
	
	init_tab_noeud(&tab);
	for(temp = a->fg; temp != NULL; temp = temp->frd){
		ajout_tab_noeud(&tab, temp);
	}
	
	ecart_x = (xmax - x0) * 0.8 / tab.nb_elem;
	marge_x = (xmax - x0) * 0.2 / tab.nb_elem;; 
	marge_y = (ymax - y0) * 0.2 / tab.nb_elem;; 

	for(i = 0; i < tab.nb_elem; i++){
		parcours((const Arbre)tab.tab[i], inf, x0 + ecart_x * i + marge_x,
						y0 + marge_y,
						x0 + ecart_x * (i + 1) + marge_x * 0.9,
						ymax - marge_y / 2, temps_total);
	}
	libere_tab_noeud(&tab);
	
}

MLV_Color conv_id_couleur(const unsigned char id[3]){
	return MLV_rgba(id[0], id[1], id[2], 255);
}

void affiche_nom(unsigned int x, unsigned int y, const char* nom){
	int x_texte, y_texte;
	MLV_get_size_of_text(nom, &x_texte, &y_texte);
	MLV_draw_text_box((x + x_texte < MLV_get_window_width())?x:x - x_texte, 
						(y < y_texte)?y + 16:y - y_texte, x_texte, y_texte, nom, 1, MLV_COLOR_BLUE, MLV_rgba(255,255,255,255), 
						MLV_rgba(255,255,255,64), MLV_TEXT_CENTER, MLV_HORIZONTAL_LEFT, MLV_VERTICAL_TOP );
	
}

void affiche_arbre(const Arbre a){
	Info_affichage inf;
	int clic_x, clic_y;
	int r, g, b;
	MLV_Mouse_button souris;
	MLV_Button_state clic_etat;
	MLV_Event event;
	unsigned char id[3];
	Noeud* name;
	init_fenetre();
	if(init_info(&inf) == 0){
		FATAL_ERROR("Erreur d'allocation\n");
	}
	name = (Noeud*) a;
	parcours(a, &inf, 0, 0,MLV_get_image_width(inf.frontend), MLV_get_image_height(inf.frontend), a->info.temps_total);
	MLV_change_frame_rate(60);
	MLV_draw_image(inf.frontend, 0, 0);
	affiche_bouton_bd();
	MLV_update_window();
	while(1){
		MLV_flush_event_queue();
		MLV_delay_according_to_frame_rate();
		event = MLV_get_event(NULL, NULL, NULL, NULL, NULL,
					&clic_x, &clic_y, &souris, &clic_etat);
		if(MLV_MOUSE_BUTTON == event || MLV_MOUSE_MOTION == event){
			if(clic_x >= 0 && clic_y >= 0 && clic_y < MLV_get_image_height(inf.backend)){
				MLV_get_pixel_on_image(inf.backend, clic_x, clic_y, &r, &g, &b, NULL);
				id[0] = r; id[1] = g; id[2] = b;
				name = cherche_noeud(a, id);		

				if(MLV_MOUSE_BUTTON == event && clic_etat == MLV_RELEASED){
					parcours(name, &inf, 0, 0,MLV_get_image_width(inf.frontend), MLV_get_image_height(inf.frontend), name->info.temps_total);
					MLV_draw_image(inf.frontend, 0, 0);
					MLV_update_window();
				}
				if(MLV_MOUSE_MOTION == event){
					MLV_clear_window(MLV_COLOR_BLACK);
					MLV_draw_image(inf.frontend, 0, 0);
					affiche_nom(clic_x, clic_y, name->info.nom);
					affiche_info(name->info.nom, name->info.temps_seul, name->info.temps_total);
					affiche_bouton_bd();
					MLV_update_window();
				}
			}
			else if(MLV_MOUSE_BUTTON == event && clic_etat == MLV_RELEASED){
				MLV_get_pixel(clic_x, clic_y, NULL, NULL, &b, NULL);
				switch (b%3){
					case 1:
						if(name->pere != NULL){
							name = name->pere;
							parcours(name, &inf, 0, 0,MLV_get_image_width(inf.frontend), MLV_get_image_height(inf.frontend), name->info.temps_total);
							MLV_clear_window(MLV_COLOR_BLACK);
							affiche_bouton_bd();
							MLV_draw_image(inf.frontend, 0, 0);
							MLV_update_window();
						}
						break;
					case 2:
						libere_info(&inf);
						MLV_free_window();
						return;
				}
			}
		}
	}
}

void affiche_bouton_bd(){
	int x, y, x_chaine, y_chaine;
	y = MLV_get_window_height();
	x = MLV_get_window_width();
	MLV_get_size_of_text("BACK", &x_chaine, &y_chaine);
	
	MLV_draw_text_box(x * 0.7, y - OPTION_BAS_TAILLE_Y, x*0.3, OPTION_BAS_TAILLE_Y/2, "BACK", 1, MLV_rgba(255,255,253,255), MLV_rgba(255,255,253,255), 
		MLV_rgba(0,0,1,255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);/* blue%3 == 1 -> back*/
	
	MLV_draw_text_box(x * 0.7, y - OPTION_BAS_TAILLE_Y/2, x*0.3, OPTION_BAS_TAILLE_Y/2, "EXIT", 1, MLV_rgba(255,255,254,255), MLV_rgba(255,255,254,255), 
		MLV_rgba(0,0,2,255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);/* blue%3 == 2 -> EXIT*/
	

}

void affiche_info(const char* nom, double temps_seul, double temps_total){
	char temp[4096];
	int x, y;
	y = MLV_get_window_height();
	x = MLV_get_window_width();
	sprintf(temp, "%s:\nTemps Seul:%lf\nTemps Total:%lf", nom, temps_seul, temps_total);
		MLV_draw_text_box(0, y - OPTION_BAS_TAILLE_Y, x*0.7, OPTION_BAS_TAILLE_Y, temp, 1, MLV_rgba(255,255,255,255), MLV_rgba(255,255,255,255), 
		MLV_rgba(0,0,0,255), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}
