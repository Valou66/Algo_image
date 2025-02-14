#include "../include/ex1.h"

struct pgm* pgm_alloc(int hauteur,int largeur,int max_val){
    struct pgm *res=(struct pgm*)malloc(sizeof(struct pgm));
    res->height=hauteur;
    res->width=largeur;
    res->max_value=max_val;

    res->pixels=(unsigned char**)malloc(hauteur*sizeof(unsigned char*));
    for(int i=0;i<res->height;i++){
        res->pixels[i]=(unsigned char*)malloc(largeur*sizeof(unsigned char));
    }

    for(int i=0;i<res->height;i++){
        for(int j=0;j<res->width;j++){
            res->pixels[i][j]=res->max_value;
        }
    }
    return res;
}//q2

void pgm_free(struct pgm *img){
    for(int i=0;i<img->height;i++){
        free(img->pixels[i]);
    }
    free(img->pixels);
    free(img);
    img=NULL;
}//q3

struct pgm* pgm_read_asc(char *fname){
    struct pgm *res;
    FILE *fichier = fopen(fname,"r");

    if(fichier!=NULL){
        char var;
        fscanf(fichier,"%c",&var);
        fscanf(fichier,"%c",&var);
        fscanf(fichier,"%c",&var);
        do{
            fscanf(fichier,"%c",&var);
        }while(var !='\n');

        int h,l,m,e;
        fscanf(fichier,"%d",&h);
        fscanf(fichier,"%d",&l);
        fscanf(fichier,"%d",&m);
        res = pgm_alloc(h,l,m); 
        for(int i=0;i<res->height;i++){
            for(int j=0;j<res->width;j++){
                fscanf(fichier,"%d",&e);

                res->pixels[i][j]=e; 
            }
        }
        fclose(fichier);
    }
    return res;
}//q4

int pgm_write_asc(char *fname,struct pgm *w){
    int succes=0;
    FILE *fichier = fopen(fname,"w");

    if(fichier!=NULL){
        fprintf(fichier,"%s","P2\n");
        fprintf(fichier,"%s","# Write in C by the best programmers\n");
        fprintf(fichier,"%d",w->height);
        fprintf(fichier,"%c",' ');
        fprintf(fichier,"%d",w->width);
        fprintf(fichier,"%c",'\n');
        fprintf(fichier,"%d",w->max_value);
        fprintf(fichier,"%c",'\n');
        
        
        for(int i=0;i<w->height;i++){
            for(int j=0;j<w->width;j++){
                fprintf(fichier,"%d",w->pixels[i][j]);
                fprintf(fichier,"%c",'\n');
            }
            
        }

        fclose(fichier);
    }
    else{
        succes=1;
    }

    return succes;
}//q5

struct pgm * pgm_read_bin(char *fname){
    struct pgm *res=NULL;
    FILE *fichier=fopen(fname,"rb");
    unsigned char t;
    int sl=0;
    if(fichier){

        int h,l,m;

        do{
            fread(&t,sizeof(unsigned char),1,fichier);

            if(t=='\n'){
                fread(&t,sizeof(unsigned char),1,fichier);
                if(t!='#'){
                    sl=1;
                }
            }
        }while(!sl);
        fseek(fichier,-1,SEEK_CUR);
        fscanf(fichier,"%d",&h);
        fscanf(fichier,"%d",&l);
        fscanf(fichier,"%d",&m);
        fread(&t,sizeof(unsigned char),1,fichier);
        res=pgm_alloc(h,l,m);
        for(short i=0;i<res->height;i++){
            for(short j=0;j<res->width;j++){
                fread(&t,sizeof(unsigned char),1,fichier);
                res->pixels[i][j]=t;
            }
        }
        fclose(fichier);
    }
    return res;
}//q6

int pgm_write_bin(char *fname,struct pgm *w){
    int succes=0;

    FILE *fichier=fopen(fname,"wb");

    if(fichier!=NULL){
        fprintf(fichier,"%s","P5\n");
        fprintf(fichier,"%s","# Write in C by the best programmers\n");
        fprintf(fichier,"%d",w->height);
        fprintf(fichier,"%c",' ');
        fprintf(fichier,"%d",w->width);
        fprintf(fichier,"%c",'\n');
        fprintf(fichier,"%d",w->max_value);
        fprintf(fichier,"%c",'\n');

        for(short i=0;i<w->height;i++)
            for(short j=0;j<w->width;j++)
                fwrite(&(w->pixels[i][j]),sizeof(unsigned char),1,fichier);
                
        fclose(fichier);
    }
    else{
        succes=1;
    }

    return succes;

}//q7

void pgm_negative(struct pgm *scr,struct pgm **dst){
    *dst=pgm_alloc(scr->height,scr->width,scr->max_value);
    for(short i=0;i<(*dst)->height;i++){
        for(short j=0;j<(*dst)->width;j++){
            (*dst)->pixels[i][j]=(*dst)->max_value-scr->pixels[i][j];
        }
    }
}

void pgm_extract(char *fname,struct pgm pgm_t,int dx,int dy,int width,int height){
    struct pgm *w=pgm_alloc(height,width,pgm_t.max_value);
    for(short i=0;i<w->height;i++){
        for(short j=0;j<w->width;j++){
            w->pixels[i][j]=pgm_t.pixels[dx+i][dy+j];
        }
    }
    pgm_write_bin(fname,w);
    pgm_free(w);
}