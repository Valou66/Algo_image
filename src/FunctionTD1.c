#include "../include/TD1.h"

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
}

struct ppm* ppm_alloc(int hauteur,int largeur,int max_val){
    struct ppm *res=(struct ppm*)malloc(sizeof(struct ppm));
    res->height=hauteur;
    res->width=largeur;
    res->max_value=max_val;

    res->pixels=(rgb_t **)malloc(hauteur*sizeof(rgb_t *));

    for(short i = 0;i<res->height;i++){
        res->pixels[i]=(rgb_t*)malloc(largeur*sizeof(rgb_t));
    }

    for(short i = 0;i<res->height;i++){
        for(short j = 0;j<res->width;j++){
            res->pixels[i][j].r=max_val;
            res->pixels[i][j].g=max_val;
            res->pixels[i][j].b=max_val;
        }
    }
    return res;
}

void pgm_free(struct pgm *img){
    for(int i=0;i<img->height;i++){
        free(img->pixels[i]);
    }
    free(img->pixels);
    free(img);
    img=NULL;
}

void ppm_free(struct ppm *img){
    for(short i = 0;i<img->height;i++){
        free(img->pixels[i]);
    }
    free(img->pixels);
    free(img);
    img=NULL;

}

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
        fscanf(fichier,"%d",&l);
        fscanf(fichier,"%d",&h);
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
}

struct ppm* ppm_read_asc(char *fname){
    struct ppm *res;
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
        fscanf(fichier,"%d",&l);
        fscanf(fichier,"%d",&h);
        fscanf(fichier,"%d",&m);
        res = ppm_alloc(h,l,m);
        for(short i = 0;i<res->height;i++){
            for(short j = 0;j<res->width;j++){
                fscanf(fichier,"%d",&e);
                res->pixels[i][j].r=e;
                fscanf(fichier,"%d",&e);
                res->pixels[i][j].g=e;
                fscanf(fichier,"%d",&e);
                res->pixels[i][j].b=e;
            }
        }
        fclose(fichier);
    }
    return res;
}

int pgm_write_asc(char *fname,struct pgm *w){
    int succes=0;
    FILE *fichier = fopen(fname,"w");

    if(fichier!=NULL){
        fprintf(fichier,"%s","P2\n");
        fprintf(fichier,"%s","# Write in C by the best programmers\n");
        fprintf(fichier,"%d",w->width);
        fprintf(fichier,"%c",' ');
        fprintf(fichier,"%d",w->height);
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
}

int ppm_write_asc(char *fname,struct ppm *w){
    int succes=0;
    FILE *fichier = fopen(fname,"w");

    if(fichier!=NULL){
        fprintf(fichier,"%s","P3\n");
        fprintf(fichier,"%s","# Write in C by the best programmers\n");
        fprintf(fichier,"%d",w->width);
        fprintf(fichier,"%c",' ');
        fprintf(fichier,"%d",w->height);
        fprintf(fichier,"%c",'\n');
        fprintf(fichier,"%d",w->max_value);
        fprintf(fichier,"%c",'\n');
        
        
        for(int i=0;i<w->height;i++){
            for(int j=0;j<w->width;j++){
                fprintf(fichier,"%d",w->pixels[i][j].r);
                fprintf(fichier,"%c",'\n');
                fprintf(fichier,"%d",w->pixels[i][j].g);
                fprintf(fichier,"%c",'\n');
                fprintf(fichier,"%d",w->pixels[i][j].b);
                fprintf(fichier,"%c",'\n');
            }
            
        }

        fclose(fichier);
    }
    else{
        succes=1;
    }

    return succes;
}

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
        fscanf(fichier,"%d",&l);
        fscanf(fichier,"%d",&h);
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
}

struct ppm * ppm_read_bin(char *fname){
    struct ppm *res=NULL;
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
        fscanf(fichier,"%d",&l);
        fscanf(fichier,"%d",&h);
        fscanf(fichier,"%d",&m);
        fread(&t,sizeof(unsigned char),1,fichier);
        res=ppm_alloc(h,l,m);
        for(short i=0;i<res->height;i++){
            for(short j=0;j<res->width;j++){
                fread(&t,sizeof(unsigned char),1,fichier);
                res->pixels[i][j].r=t;
                fread(&t,sizeof(unsigned char),1,fichier);
                res->pixels[i][j].g=t;
                fread(&t,sizeof(unsigned char),1,fichier);
                res->pixels[i][j].b=t;
            }
        }
        fclose(fichier);
    }
    return res;
}
int pgm_write_bin(char *fname,struct pgm *w){
    int succes=0;

    FILE *fichier=fopen(fname,"wb");

    if(fichier!=NULL){
        fprintf(fichier,"%s","P5\n");
        fprintf(fichier,"%s","# Write in C by the best programmers\n");
        fprintf(fichier,"%d",w->width);
        fprintf(fichier,"%c",' ');
        fprintf(fichier,"%d",w->height);
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

}

int ppm_write_bin(char *fname,struct ppm *w){
    int succes=0;

    FILE *fichier=fopen(fname,"wb");

    if(fichier!=NULL){
        fprintf(fichier,"%s","P6\n");
        fprintf(fichier,"%s","# Write in C by the best programmers\n");
        fprintf(fichier,"%d",w->width);
        fprintf(fichier,"%c",' ');
        fprintf(fichier,"%d",w->height);
        fprintf(fichier,"%c",'\n');
        fprintf(fichier,"%d",w->max_value);
        fprintf(fichier,"%c",'\n');

        for(short i=0;i<w->height;i++){
            for(short j=0;j<w->width;j++){
                fwrite(&(w->pixels[i][j].r),sizeof(unsigned char),1,fichier);
                fwrite(&(w->pixels[i][j].g),sizeof(unsigned char),1,fichier);
                fwrite(&(w->pixels[i][j].b),sizeof(unsigned char),1,fichier);
            }
        }
                
        fclose(fichier);
    }
    else{
        succes=1;
    }

    return succes;
}

void pgm_negative(struct pgm *scr,struct pgm **dst){
    *dst=pgm_alloc(scr->height,scr->width,scr->max_value);
    for(short i=0;i<(*dst)->height;i++){
        for(short j=0;j<(*dst)->width;j++){
            (*dst)->pixels[i][j]=(*dst)->max_value-scr->pixels[i][j];
        }
    }
}

void ppm_negative(struct ppm *scr,struct ppm **dst){
    *dst=ppm_alloc(scr->height,scr->width,scr->max_value);
    for(short i=0;i<(*dst)->height;i++){
        for(short j=0;j<(*dst)->width;j++){
            (*dst)->pixels[i][j].r=(*dst)->max_value-scr->pixels[i][j].r;
            (*dst)->pixels[i][j].g=(*dst)->max_value-scr->pixels[i][j].b;
            (*dst)->pixels[i][j].b=(*dst)->max_value-scr->pixels[i][j].g;
        }
    }
}

void pgm_extract(char *fname,struct pgm *pgm_t,int dx,int dy,int width,int height){
    struct pgm *w=pgm_alloc(height,width,pgm_t->max_value);
    
    for(short i = 0;i<w->height;i++){
        for(short j = 0;j<w->width;j++){
            w->pixels[i][j]=pgm_t->pixels[dx+i][dy+j];
        }
    }

    pgm_write_asc(fname,w);
    pgm_free(w);
}

void ppm_extract(char *fname,struct ppm *pgm_t,int dx,int dy,int width,int height){
    struct ppm *w=ppm_alloc(height,width,pgm_t->max_value);
    
    for(short i = 0;i<w->height;i++){
        for(short j = 0;j<w->width;j++){
            w->pixels[i][j].r=pgm_t->pixels[dx+i][dy+j].r;
            w->pixels[i][j].g=pgm_t->pixels[dx+i][dy+j].g;
            w->pixels[i][j].b=pgm_t->pixels[dx+i][dy+j].b;
        }
    }

    ppm_write_asc(fname,w);
    ppm_free(w);
}

short* pgm_get_histogram(struct pgm *in){
    short *histogram=(short *)malloc(in->max_value*sizeof(short)); 
    for(short i = 0;i<in->max_value;i++){
        histogram[i]=0;
    }

    for(short i = 0;i<in->height;i++){
        for(short j = 0;j<in->width;j++){
            histogram[in->pixels[i][j]]++;
        }
    }

    return histogram;


}

short** ppm_get_histogram(struct ppm *in){
    short **histogram=(short **)malloc(3*sizeof(short*));
    histogram[0]=(short*)malloc(in->max_value*sizeof(short));
    histogram[1]=(short*)malloc(in->max_value*sizeof(short)); 
    histogram[2]=(short*)malloc(in->max_value*sizeof(short));
    
    for(short i = 0;i<in->max_value;i++){
        histogram[0][i]=0;
        histogram[1][i]=0;
        histogram[2][i]=0;
    }

    for(short i = 0;i<in->height;i++){
        for(short j = 0;j<in->width;j++){
            histogram[0][in->pixels[i][j].r]++;
            histogram[1][in->pixels[i][j].g]++;
            histogram[2][in->pixels[i][j].b]++;
        }
    }

    return histogram;
}

void pgm_write_histogram(struct pgm *in,char *fname){
    pgm_write_bin(fname,in);
    FILE *fichier=fopen("../obj/histogram_pgm.txt","w");

    if(fichier!=NULL){
        short *hist_res=pgm_get_histogram(in);
        for(short i = 0;i<in->max_value;i++){
            fprintf(fichier,"%d : %d \n",i,hist_res[i]);
        }
        free(hist_res);
        fclose(fichier);
    }
}

void ppm_write_histogram(struct ppm *in,char *fname){
    ppm_write_bin(fname,in);
    FILE *fichier=fopen("../obj/histogram_ppm.txt","w");

    if(fichier!=NULL){
        short **hist_res=ppm_get_histogram(in);
        for(short i = 0;i<in->max_value;i++){
            fprintf(fichier,"%d : (%d,%d,%d) \n",i,hist_res[0][i],hist_res[1][i],hist_res[2][i]);
        }
        free(hist_res[0]);
        free(hist_res[1]);
        free(hist_res[2]);
        free(hist_res);
        fclose(fichier);
    }
}

void ppm_to_pgm(struct ppm *in,struct pgm **out){
    *out=pgm_alloc(in->height,in->width,in->max_value);
    short moy;

    for(short i = 0;i<(*out)->height;i++){
        for(short j = 0;j<(*out)->width;j++){
            moy=0;
            moy=moy+in->pixels[i][j].r;
            moy=moy+in->pixels[i][j].g;
            moy=moy+in->pixels[i][j].b;
            moy=moy/3;
            (*out)->pixels[i][j]=moy;
        }
    }
}
