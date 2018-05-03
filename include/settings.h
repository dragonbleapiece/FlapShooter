/*
 * settings.h
 * Déclaration des paramètres : variables globales et statiques
 *
 * Auteur : Nicolas CUSUMANO & Nicolas SENECAL
 * IMAC1 - S2 - Promotion 2020
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#define RGBA_EXTENSION (const char *[3]){"png","gif","bpm"} /* Les différentes extensions des images en RGBA */
#define RGBA_EXTENSION_SIZE (int) 3 /* Taille du tableau ci-dessus */

#define CERCLE_LIGNES 50 /* Nombre de polygones d'un cercle */

/* DEBUG */
#define SHOW_BOUNDING_BOX 1 /* Afficher les bounding box en violet sur les entités */
#define BOUNDING_BOX_COLOR 148,0,211,100 /* Couleur RGBA des bounding box */
#define UNTEXTURED_BOX_COLOR 255,0,255,255 /* Couleur RGBA des objets non texturé */

#endif
