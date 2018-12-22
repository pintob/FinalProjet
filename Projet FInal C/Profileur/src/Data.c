
/*		### BIBLIOTHEQUE ###		*/
#include "../include/Data.h"
/*		### DECLARATION FONCTION PRIVEE###	*/

/*		### DEFINITION FONCTION ###		*/

void affiche_data(const Data* data){
	assert(data != NULL);
	printf("%s :%lf/%lf\n", data->nom, data->temps_total, data->temps_seul);
}
