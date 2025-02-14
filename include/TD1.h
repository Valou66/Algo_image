#ifndef TD1_H
#define TD1_H

#include <stdio.h>
#include <stdlib.h>

struct pgm{
    int height,width,max_value;
    unsigned char **pixels;
};//q1

struct pgm* pgm_alloc(int hauteur,int largeur,int max_val);//q2
/*
    return: un pointeur sur une structure pgm avec une hauteur , largeur , max_val
*/

void pgm_free(struct pgm *img);//q3
/*
    libere la mémoire allouer pour une structure pgm
*/

struct pgm* pgm_read_asc(char *fname);//q4
/*
    prend en parametre un un pointeur sur une chaine de caractere 
    sur le nom du fichier au format ASCII à lire (fname) et retournant 
    un pointeur sur une structure pgm contenant les informations 
    relatives à l’image contenue dans le fichier fname.
*/

int pgm_write_asc(char *fname,struct pgm *w);//q5
/*
    prend en paramètre un pointeur sur une chaine de
    caractères contenant le nom du fichier (fname) à écrire (au format ASCII) 
    ainsi qu’un pointeur sur une structure pgm. 
    La fonction retourne un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/

struct pgm * pgm_read_bin(char *fname);//q6
/*
    prend en paramètre un pointeur sur une chaine de
    caractères contenant le nom du fichier au format 
    BINAIRE à lire (fname) et retourne un pointeur
    sur une structure pgm contenant les informations 
    relatives à l’image contenue dans le fichier fname.
*/

int pgm_write_bin(char *fname,struct pgm *w);//q7
/*
    prend en paramètre un pointeur sur une chaine de caractères 
    contenant le nom du fichier (fname à écrire (au format BINAIRE) 
    ainsi qu’un pointeur sur une structure pgm. La fonction retourne 
    un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/

void pgm_negative(struct pgm *scr,struct pgm **dst);//q8
/*
    prend en paramètre un pointeur scr sur une structure 
    pgm contenant l’image source et un pointeur dst sur 
    une structure pgm contenant le négatif de l’image source.
*/

void pgm_extract(char *fname,struct pgm *pgm_t,int dx,int dy,int width,int height);
/*
    prend en paramètre un pointeur sur une chaine de caractères
    contenant le nom du fichier de sortie (fname), une structure pgm_t, les coordonnées dx et dy
    indiquant le point de départ de l’image à extraire et les dimensions de l’image à extraire width et
    height. La fonction écrira dans le fichier fname une “sous-image” extraite de l’image principale.
*/





#endif //TD1_H