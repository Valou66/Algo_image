#ifndef TD1_H
#define TD1_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419716939937510
#endif


struct pgm{
    int height,width,max_value;
    unsigned char **pixels;
};

struct rgb{
    short r,g,b;
};
typedef struct rgb rgb_t;

struct yuv{
    double y,u,v;
};
typedef struct yuv yuv_t;

struct ppm{
    int height,width,max_value;
    rgb_t **pixels;
};

yuv_t rgb_to_yuv(rgb_t in);

rgb_t yuv_to_rgb(yuv_t in);

struct pgm* pgm_alloc(int hauteur,int largeur,int max_val);
/*
    return: un pointeur sur une structure pgm avec une hauteur , largeur , max_val
*/

struct ppm* ppm_alloc(int hauteur,int largeur,int max_val);
/*
    return: un pointeur sur une structure ppm avec une hauteur , largeur , max_val
*/

void pgm_free(struct pgm *img);
/*
    libere la mémoire allouer pour une structure pgm
*/

void ppm_free(struct ppm *img);
/*
    libere la mémoire allouer pour une structure ppm
*/

struct pgm* pgm_read_asc(char *fname);
/*
    prend en parametre un un pointeur sur une chaine de caractere 
    sur le nom du fichier au format ASCII à lire (fname) et retournant 
    un pointeur sur une structure pgm contenant les informations 
    relatives à l’image contenue dans le fichier fname.
*/

struct ppm* ppm_read_asc(char *fname);
/*
    prend en parametre un un pointeur sur une chaine de caractere 
    sur le nom du fichier au format ASCII à lire (fname) et retournant 
    un pointeur sur une structure ppm contenant les informations 
    relatives à l’image contenue dans le fichier fname.
*/



int pgm_write_asc(char *fname,struct pgm *w);
/*
    prend en paramètre un pointeur sur une chaine de
    caractères contenant le nom du fichier (fname) à écrire (au format ASCII) 
    ainsi qu’un pointeur sur une structure pgm. 
    La fonction retourne un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/

int ppm_write_asc(char *fname,struct ppm *w);
/*
    prend en paramètre un pointeur sur une chaine de
    caractères contenant le nom du fichier (fname) à écrire (au format ASCII) 
    ainsi qu’un pointeur sur une structure ppm. 
    La fonction retourne un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/



struct pgm * pgm_read_bin(char *fname);
/*
    prend en paramètre un pointeur sur une chaine de
    caractères contenant le nom du fichier au format 
    BINAIRE à lire (fname) et retourne un pointeur
    sur une structure pgm contenant les informations 
    relatives à l’image contenue dans le fichier fname.
*/

struct ppm * ppm_read_bin(char *fname);
/*
    prend en paramètre un pointeur sur une chaine de
    caractères contenant le nom du fichier au format 
    BINAIRE à lire (fname) et retourne un pointeur
    sur une structure ppm contenant les informations 
    relatives à l’image contenue dans le fichier fname.
*/

int pgm_write_bin(char *fname,struct pgm *w);
/*
    prend en paramètre un pointeur sur une chaine de caractères 
    contenant le nom du fichier (fname à écrire (au format BINAIRE) 
    ainsi qu’un pointeur sur une structure pgm. La fonction retourne 
    un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/

int ppm_write_bin(char *fname,struct ppm *w);
/*
    prend en paramètre un pointeur sur une chaine de caractères 
    contenant le nom du fichier (fname à écrire (au format BINAIRE) 
    ainsi qu’un pointeur sur une structure ppm. La fonction retourne 
    un entier égale à 0 si tout s’est bien passé et à 1 sinon.
*/

void pgm_negative(struct pgm *scr,struct pgm **dst);
/*
    prend en paramètre un pointeur scr sur une structure 
    pgm contenant l’image source et un pointeur dst sur 
    une structure pgm contenant le négatif de l’image source.
*/

void ppm_negative(struct ppm *scr,struct ppm **dst);
/*
    prend en paramètre un pointeur scr sur une structure 
    ppm contenant l’image source et un pointeur dst sur 
    une structure ppm contenant le négatif de l’image source.
*/

void pgm_extract(char *fname,struct pgm *pgm_t,int dx,int dy,int width,int height);
/*
    prend en paramètre un pointeur sur une chaine de caractères
    contenant le nom du fichier de sortie (fname), une structure pgm_t, les coordonnées dx et dy
    indiquant le point de départ de l’image à extraire et les dimensions de l’image à extraire width et
    height. La fonction écrira dans le fichier fname une “sous-image” extraite de l’image principale.
*/

void ppm_extract(char *fname,struct ppm *pgm_t,int dx,int dy,int width,int height);
/*
    prend en paramètre un pointeur sur une chaine de caractères
    contenant le nom du fichier de sortie (fname), une structure ppm_t, les coordonnées dx et dy
    indiquant le point de départ de l’image à extraire et les dimensions de l’image à extraire width et
    height. La fonction écrira dans le fichier fname une “sous-image” extraite de l’image principale.
*/

short* pgm_get_histogram(struct pgm *in);
/*
    prend en paramètre un pointeur sur une structure
    pgm et etourne un pointeur sur un tableau de 
    max_value contenant l’histogramme des pixels
    de l’image.
*/

short** ppm_get_histogram(struct ppm *in);
/*
    prend en paramètre un pointeur sur une structure
    ppm et qui retournera un pointeur sur un tableu à 
    deux dimensions (3,=maxvalue=) contenant les
    histogrammes des trois composantes RGB des pixels de l’image.
*/

void pgm_write_histogram(struct pgm *in,char *fname);
/*
    prend en paramètre un pointeur sur une structure
    pgm, un pointeur sur une chaine de caractère fname. 
    et créer le fichier fname et l’histogramme 
    de l’image sous la forme de deux colonnes (la première colonne 
    contiendra les valeurs de 0 à max_value, la seconde les données 
    de l’histogramme correspondant).
*/

void ppm_write_histogram(struct ppm *in,char *fname);
/*
    prend en paramètre un pointeur sur une structure
    ppm, un pointeur sur une chaine de caractère fname. 
    La fonction devra créer le fichier fname et
    l’histogramme de l’image sous la forme de quatre colonnes 
    (la première colonne contiendra les valeurs de 0 à max_value, 
    les trois colonnes suivantes les données de l’histogramme des trois
    composantes correspondant).
*/

void ppm_to_pgm(struct ppm *in,struct pgm **out);
/*
    prendra en paramètre un pointeur sur une structure 
    ppm et un pointeur sur une structure pgm. La fonction 
    convertira l’image ppm en image pgm.
*/

void pgm_extract_blk(struct pgm *inpgm,double blk[8][8],int i,int j);
/*
    pgm_extract_blk(pgm_t *inpgm, double blk[8][8], int i, int j) 
    qui extrait le bloc 8 × 8 formé de la composante Y de l’image ppm 
    pointée par image dont le coin supérieur gauche se trouve aux 
    coordonnées (i,j). Ce bloc sera sauvegardé dans le tableau de double
    bloc passé en paramètre.
*/

void pgm_extrect_blk_reverse(struct pgm *inpgm,double blk[8][8],int i,int j);

void ppm_extract_blk(struct ppm *inppm,double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],int i,int j);

void ppm_extract_blk_reverse(struct ppm *inppm,double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],int i,int j);

void pgm_dct(double bloc[8][8]);
/*
   qui applique la transformée en cosinue discrète bi-dimensionnelle 
   à un tableau bloc de taille 8 × 8. 
*/

void pgm_idct(double bloc[8][8]);

void ppm_dct(double bloc_y[8][8],double bloc_u[8][8],double bloc_v[8][8]);

void ppm_idct(double bloc_y[8][8],double bloc_u[8][8],double bloc_v[8][8]);

void pgm_quantify(double blk[8][8],double Q[8][8]);
/*
    void pgm_quantify(double blk[8][8], double Q[8][8]) quantifie
    le bloc blk passé en paramètre avec la matrice de quantification Q passée en paramètre.
*/

void pgm_quantify_reverse(double blk[8][8],double Q[8][8]);

void ppm_quantify(double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],double Q[8][8]);

void ppm_quantify_reverse(double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],double Q[8][8]);

void pgm_zig_zag_extract(double blk[8][8],int zgzg[64]);
/*
    void pgm_zigzag_extract(double blk[8][8], int zgzg[64]) extrait les 64 nombres contenus 
    dans le bloc blk de taille 8 × 8 dans l’ordre donné par la figure 1. Les
    valeurs de blk seront arrondies à l’entier le plus proche avant d’être stockées dans le tableau zgzg
    passé en paramètre.
*/

void pgm_zig_zag_reverse(double blk[8][8],int zgzg[64]);

void ppm_zig_zag_extract(double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],int zgzg_y[64],int zgzg_u[64],int zgzg_v[64]);

void ppm_zig_zag_reverse(double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],int zgzg_y[64],int zgzg_u[64],int zgzg_v[64]);

void pgm_rle(FILE *fd,int zgzg[64]);
/*
    écrit les entiers contenus dans le tableau zgzg dans le fichier pointé par fd. 
    On supposera que le flux donné par fd aura été ouvert préalablement. 
    Chaque entier sera écrit sur une ligne différente et une séquence de n 0 sera
    codée par @$n$ dès que n >= 2.
*/

void ppm_rle(FILE *fd,int zgzg_y[64],int zgzg_u[64],int zgzg_v[64]);


void rle_pgm(FILE *fd,int zgzg[64]);

void rle_ppm(FILE *fd,int zgzg_y[64],int zgzg_u[64],int zgzg_v[64]);

void pgm_to_jpeg(struct pgm *in_pgm,char *fname);
/*
    compresse l’image pgm pointée par in_pgm en utilisant l’algorithme de compression JPEG 
    et qui stocke le résultat dans un fichier dont le nom est donné par fname. Le fichier
    compressé respectera le format suivant :

    JPEG
    width height
    x0
    x1
    x2
    ...
    ...
*/



void ppm_to_jpeg(struct ppm *in_pgm,char *fname);

void jpeg_to_pgm(char *fname);
void jpeg_to_ppm(char *fname);

int fsize(char *fname);
/*
    renvoit la taille en octets du fichier nommé par la chaine de caratère fname. 
    On supposera que chaque caractère du fichier fname est codé sur 1 octet. 
*/

#endif //TD1_H