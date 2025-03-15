#include "../include/TD1.h"

double Q[8][8]={{16.0,11.0,10.0,16.0,24.0,40.0,51.0,61.0},
                {12.0,12.0,14.0,19.0,26.0,58.0,60.0,55.0},
                {14.0,13.0,16.0,24.0,40.0,57.0,69.0,56.0},
                {14.0,17.0,22.0,29.0,51.0,87.0,80.0,62.0},
                {18.0,22.0,37.0,56.0,68.0,109.0,103.0,77.0},
                {24.0,35.0,55.0,64.0,81.0,104.0,113.0,92.0},
                {49.0,64.0,78.0,87.0,103.0,121.0,120.0,101.0},
                {72.0,92.0,95.0,98.0,112.0,100.0,103.0,99.0}};

int zigzag_order[64][2] = {
                    {0, 0}, {0, 1}, {1, 0}, {2, 0}, {1, 1}, {0, 2}, {0, 3}, {1, 2},
                    {2, 1}, {3, 0}, {4, 0}, {3, 1}, {2, 2}, {1, 3}, {0, 4}, {0, 5},
                    {1, 4}, {2, 3}, {3, 2}, {4, 1}, {5, 0}, {6, 0}, {5, 1}, {4, 2},
                    {3, 3}, {2, 4}, {1, 5}, {0, 6}, {0, 7}, {1, 6}, {2, 5}, {3, 4},
                    {4, 3}, {5, 2}, {6, 1}, {7, 0}, {7, 1}, {6, 2}, {5, 3}, {4, 4},
                    {3, 5}, {2, 6}, {1, 7}, {2, 7}, {3, 6}, {4, 5}, {5, 4}, {6, 3},
                    {7, 2}, {7, 3}, {6, 4}, {5, 5}, {4, 6}, {3, 7}, {4, 7}, {5, 6},
                    {6, 5}, {7, 4}, {7, 5}, {6, 6}, {5, 7}, {6, 7}, {7, 6}, {7, 7}
                          };

yuv_t rgb_to_yuv(rgb_t in){
    yuv_t out;
    out.y=0.299*in.r+0.587*in.g+0.114*in.b;
    out.u=-0.147*in.r-0.289*in.g+ 0.436*in.b;
    out.v=0.615*in.r-0.515*in.g-0.100*in.b;
    return out;
}

rgb_t yuv_to_rgb(yuv_t in) {
    rgb_t out;
    out.r = (in.y + 1.140 * in.v);
    out.g = (in.y - 0.395 * in.u - 0.581 * in.v);
    out.b = (in.y + 2.032 * in.u);

    if(out.r >255){
        out.r=255;
    }
    if(out.r<0){
        out.r=0;
    }

    if(out.g >255){
        out.g=255;
    }
    if(out.g<0){
        out.g=0;
    }

    if(out.b >255){
        out.b=255;
    }
    if(out.b<0){
        out.b=0;
    }
    return out;
}

struct pgm* pgm_alloc(int hauteur,int largeur,int max_val){
    struct pgm *res=(struct pgm*)malloc(sizeof(struct pgm));
    res->height=hauteur;
    res->width=largeur;
    res->max_value=max_val;

    res->pixels=(unsigned char**)malloc(hauteur*sizeof(unsigned char*));
    for(short i=0;i<res->height;i++){
        res->pixels[i]=(unsigned char*)malloc(largeur*sizeof(unsigned char));
    }

    for(short i=0;i<res->height;i++){
        for(short j=0;j<res->width;j++){
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
    for(short i=0;i<img->height;i++){
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
        for(short i=0;i<res->height;i++){
            for(short j=0;j<res->width;j++){
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
        
        
        for(short i=0;i<w->height;i++){
            for(short j=0;j<w->width;j++){
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
        
        
        for(short i=0;i<w->height;i++){
            for(short j=0;j<w->width;j++){
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

void pgm_extract_blk(struct pgm *inpgm,double blk[8][8],int i,int j){
    for(short x = 0;x<8;x++){
        for(short y = 0;y<8;y++){
            blk[x][y]=inpgm->pixels[i+x][j+y];
        }
    }
}

void pgm_extrect_blk_reverse(struct pgm *inpgm,double blk[8][8],int i,int j){
    for(short x = 0;x<8;x++){
        for(short y = 0;y<8;y++){
            inpgm->pixels[i+x][j+y]=blk[x][y];
        }
    }
}

void ppm_extract_blk(struct ppm *inppm,double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],int i,int j){
    yuv_t e;
    for(short x = 0;x<8;x++){
        for(short y = 0;y<8;y++){
            e=rgb_to_yuv(inppm->pixels[i+x][j+y]);
            blk_y[x][y]=e.y;
            blk_u[x][y]=e.u;
            blk_v[x][y]=e.v;
        }
    }
}

void ppm_extract_blk_reverse(struct ppm *inppm,double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],int i,int j){
    rgb_t e_rgb;
    yuv_t e_yuv;
    for(short x = 0;x<8;x++){
        for(short y = 0;y<8;y++){
            e_yuv.y=blk_y[x][y];
            e_yuv.u=blk_u[x][y];
            e_yuv.v=blk_v[x][y];
            e_rgb=yuv_to_rgb(e_yuv);

            inppm->pixels[i+x][j+y].r=e_rgb.r;
            inppm->pixels[i+x][j+y].g=e_rgb.g;
            inppm->pixels[i+x][j+y].b=e_rgb.b;

        }
    }
}

void pgm_dct(double bloc[8][8]){
    double copie[8][8];
    short i,j,x,y;

    double c_i,c_j;

    double somme;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            copie[i][j]=bloc[i][j];
        }
    }

    for(i=0;i<8;i++){
        if(i==0)
            c_i=1.0/sqrtf(2);
        else
            c_i=1.0;

        for(j=0;j<8;j++){
            somme = 0.0;
            if(j==0)
                c_j=1.0/sqrtf(2);
            else
                c_j=1.0;
            
            for(x=0;x<8;x++){
                for(y=0;y<8;y++){
                    somme=somme+(copie[x][y]*cos((((2.0*x)+1.0)*i*M_PI)/16.0)*cos((((2.0*y)+1.0)*j*M_PI)/16.0));
                }
            }
            somme=somme*c_i*c_j*(2.0/8.0);
            bloc[i][j]=somme;
        }
    }
}

void ppm_dct(double bloc_y[8][8],double bloc_u[8][8],double bloc_v[8][8]){
    double copie_y[8][8];
    double copie_u[8][8];
    double copie_v[8][8];
    short i,j,x,y;

    double c_i,c_j;

    double somme_y;
    double somme_u;
    double somme_v;

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            copie_y[i][j]=bloc_y[i][j];
            copie_u[i][j]=bloc_u[i][j];
            copie_v[i][j]=bloc_v[i][j];
        }
    }

    for(i=0;i<8;i++){
        if(i==0)
            c_i=1.0/sqrtf(2);
        else
            c_i=1.0;

        for(j=0;j<8;j++){
            somme_y = 0.0;
            somme_u = 0.0;
            somme_v = 0.0;
            if(j==0)
                c_j=1.0/sqrtf(2);
            else
                c_j=1.0;
            
            for(x=0;x<8;x++){
                for(y=0;y<8;y++){
                    somme_y=somme_y+(copie_y[x][y]*cos((((2.0*x)+1.0)*i*M_PI)/16.0)*cos((((2.0*y)+1.0)*j*M_PI)/16.0));
                    somme_u=somme_u+(copie_u[x][y]*cos((((2.0*x)+1.0)*i*M_PI)/16.0)*cos((((2.0*y)+1.0)*j*M_PI)/16.0));
                    somme_v=somme_v+(copie_v[x][y]*cos((((2.0*x)+1.0)*i*M_PI)/16.0)*cos((((2.0*y)+1.0)*j*M_PI)/16.0));
                }
            }
            somme_y=somme_y*c_i*c_j*(2.0/8.0);
            somme_u=somme_u*c_i*c_j*(2.0/8.0);
            somme_v=somme_v*c_i*c_j*(2.0/8.0);
            bloc_y[i][j]=somme_y;
            bloc_u[i][j]=somme_u;
            bloc_v[i][j]=somme_v;
        }
    }
}

void pgm_idct(double bloc[8][8]){
    double copie[8][8];
    short x, y, i, j;
    double c_i, c_j, somme;

    // Sauvegarde du bloc transformé
    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            copie[x][y] = bloc[x][y];
        }
    }

    // Application de l'IDCT
    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            somme = 0.0;

            for (i = 0; i < 8; i++) {
                c_i = (i == 0) ? (1.0 / sqrt(2)) : 1.0;

                for (j = 0; j < 8; j++) {
                    c_j = (j == 0) ? (1.0 / sqrt(2)) : 1.0;

                    somme += c_i * c_j * copie[i][j] *
                             cos(((2.0 * x + 1.0) * i * M_PI) / 16.0) *
                             cos(((2.0 * y + 1.0) * j * M_PI) / 16.0);
                }
            }

            bloc[x][y] = somme * (2.0 / 8.0);
        }
    }
}

void ppm_idct(double bloc_y[8][8],double bloc_u[8][8],double bloc_v[8][8]){
    double copie_y[8][8];
    double copie_u[8][8];
    double copie_v[8][8];
    short x, y, i, j;
    double c_i, c_j, somme_y, somme_u, somme_v;

    // Sauvegarde du bloc transformé
    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            copie_y[x][y] = bloc_y[x][y];
            copie_u[x][y] = bloc_u[x][y];
            copie_v[x][y] = bloc_v[x][y];
        }
    }

    // Application de l'IDCT
    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            somme_y = 0.0;
            somme_u = 0.0;
            somme_v = 0.0;

            for (i = 0; i < 8; i++) {
                c_i = (i == 0) ? (1.0 / sqrt(2)) : 1.0;

                for (j = 0; j < 8; j++) {
                    c_j = (j == 0) ? (1.0 / sqrt(2)) : 1.0;

                    somme_y += c_i * c_j * copie_y[i][j] *
                             cos(((2.0 * x + 1.0) * i * M_PI) / 16.0) *
                             cos(((2.0 * y + 1.0) * j * M_PI) / 16.0);
                    
                    somme_u += c_i * c_j * copie_u[i][j] *
                             cos(((2.0 * x + 1.0) * i * M_PI) / 16.0) *
                             cos(((2.0 * y + 1.0) * j * M_PI) / 16.0);
                    
                    somme_v += c_i * c_j * copie_v[i][j] *
                             cos(((2.0 * x + 1.0) * i * M_PI) / 16.0) *
                             cos(((2.0 * y + 1.0) * j * M_PI) / 16.0);
                }
            }

            bloc_y[x][y] = somme_y * (2.0 / 8.0);
            bloc_u[x][y] = somme_u * (2.0 / 8.0);
            bloc_v[x][y] = somme_v * (2.0 / 8.0);
        }
    }
}

void pgm_quantify(double blk[8][8],double Q[8][8]){
    short i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            blk[i][j]=round(blk[i][j]/Q[i][j]);
        }
    }
}

void pgm_quantify_reverse(double blk[8][8],double Q[8][8]){
    short i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            blk[i][j]=blk[i][j]*Q[i][j];
        }
    }
}

void ppm_quantify(double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],double Q[8][8]){
    short i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            blk_y[i][j]=round(blk_y[i][j]/Q[i][j]);
            blk_u[i][j]=round(blk_u[i][j]/Q[i][j]);
            blk_v[i][j]=round(blk_v[i][j]/Q[i][j]);
        }
    }
}

void ppm_quantify_reverse(double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],double Q[8][8]){
    short i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            blk_y[i][j]=blk_y[i][j]*Q[i][j];
            blk_u[i][j]=blk_u[i][j]*Q[i][j];
            blk_v[i][j]=blk_v[i][j]*Q[i][j];
        }
    }
}

void pgm_zig_zag_extract(double blk[8][8],int zgzg[64]){
    short i;
    for(i=0;i<64;i++){
        zgzg[i]=blk[zigzag_order[i][0]][zigzag_order[i][1]];
    }
}

void pgm_zig_zag_reverse(double blk[8][8],int zgzg[64]){
    short i;
    for(i=0;i<64;i++){
        blk[zigzag_order[i][0]][zigzag_order[i][1]]=zgzg[i];
    }
}

void ppm_zig_zag_extract(double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],int zgzg_y[64],int zgzg_u[64],int zgzg_v[64]){
    short i;
    for(i=0;i<64;i++){
        zgzg_y[i]=blk_y[zigzag_order[i][0]][zigzag_order[i][1]];
        zgzg_u[i]=blk_u[zigzag_order[i][0]][zigzag_order[i][1]];
        zgzg_v[i]=blk_v[zigzag_order[i][0]][zigzag_order[i][1]];
    }
}

void ppm_zig_zag_reverse(double blk_y[8][8],double blk_u[8][8],double blk_v[8][8],int zgzg_y[64],int zgzg_u[64],int zgzg_v[64]){
    short i;
    for(i=0;i<64;i++){
        blk_y[zigzag_order[i][0]][zigzag_order[i][1]]=zgzg_y[i];
        blk_u[zigzag_order[i][0]][zigzag_order[i][1]]=zgzg_u[i];
        blk_v[zigzag_order[i][0]][zigzag_order[i][1]]=zgzg_v[i];
    }
}

void pgm_rle(FILE *fd,int zgzg[64]){
    short i=0;
    short count=0;

    while(i<64){
        if(zgzg[i]!=0){
            if(count>=2){
                fprintf(fd,"@%d\n",count);
            }
            else if(count >0){
                fprintf(fd,"%d\n",0);
            }
            count=0;
            fprintf(fd,"%d\n",zgzg[i]);
        }
        else{
            count++;
        }

        i++;
    }
    if(count>=2)
        fprintf(fd,"@%d\n",count);
    else if(count >0)
        fprintf(fd,"%d\n",0);
}

void ppm_rle(FILE *fd,int zgzg_y[64],int zgzg_u[64],int zgzg_v[64]){
    short i;
    short count;

    i=0;
    count=0;
    while(i<64){
        if(zgzg_y[i]!=0){
            if(count>=2){
                fprintf(fd,"@%d\n",count);
            }
            else if(count >0){
                fprintf(fd,"%d\n",0);
            }
            count=0;
            fprintf(fd,"%d\n",zgzg_y[i]);
        }
        else{
            count++;
        }

        i++;
    }
    if(count>=2)
        fprintf(fd,"@%d\n",count);
    else if(count >0)
        fprintf(fd,"%d\n",0);

    i=0;
    count=0;
    while(i<64){
        if(zgzg_u[i]!=0){
            if(count>=2){
                fprintf(fd,"@%d\n",count);
            }
            else if(count >0){
                fprintf(fd,"%d\n",0);
            }
            count=0;
            fprintf(fd,"%d\n",zgzg_u[i]);
        }
        else{
            count++;
        }

        i++;
    }
    if(count>=2)
        fprintf(fd,"@%d\n",count);
    else if(count >0)
        fprintf(fd,"%d\n",0);

    i=0;
    count=0;
    while(i<64){
        if(zgzg_v[i]!=0){
            if(count>=2){
                fprintf(fd,"@%d\n",count);
            }
            else if(count >0){
                fprintf(fd,"%d\n",0);
            }
            count=0;
            fprintf(fd,"%d\n",zgzg_v[i]);
        }
        else{
            count++;
        }

        i++;
    }
    if(count>=2)
        fprintf(fd,"@%d\n",count);
    else if(count >0)
        fprintf(fd,"%d\n",0);
    
}

void rle_pgm(FILE *fd,int zgzg[64]){
    short i=0;
    char e;
    int elem;
    while(i<64){
        fscanf(fd,"%c",&e);
        if(e=='@'){
            fscanf(fd,"%d",&elem);
            for(int j=0;j<elem;j++){
                zgzg[i]=0;
                i++;
            }
        }
        else{
            fseek(fd,-1*sizeof(char),SEEK_CUR);
            fscanf(fd,"%d",&elem);
            zgzg[i]=elem;
            i++;
            fscanf(fd,"%c",&e);
        }
    }
}

void rle_ppm(FILE *fd,int zgzg_y[64],int zgzg_u[64],int zgzg_v[64]){
    short i=0;
    char e;
    int elem;

    i=0;
    while(i<64){
        fscanf(fd,"%c",&e);
        if(e=='@'){
            fscanf(fd,"%d",&elem);
            for(int j=0;j<elem;j++){
                zgzg_y[i]=0;
                i++;
            }
        }
        else{
            fseek(fd,-1*sizeof(char),SEEK_CUR);
            fscanf(fd,"%d",&elem);
            zgzg_y[i]=elem;
            i++;
            fscanf(fd,"%c",&e);
        }
    }

    i=0;
    while(i<64){
        fscanf(fd,"%c",&e);
        if(e=='@'){
            fscanf(fd,"%d",&elem);
            for(int j=0;j<elem;j++){
                zgzg_u[i]=0;
                i++;
            }
        }
        else{
            fseek(fd,-1*sizeof(char),SEEK_CUR);
            fscanf(fd,"%d",&elem);
            zgzg_u[i]=elem;
            i++;
            fscanf(fd,"%c",&e);
        }
    }

    i=0;
    while(i<64){
        fscanf(fd,"%c",&e);
        if(e=='@'){
            fscanf(fd,"%d",&elem);
            for(int j=0;j<elem;j++){
                zgzg_v[i]=0;
                i++;
            }
        }
        else{
            fseek(fd,-1*sizeof(char),SEEK_CUR);
            fscanf(fd,"%d",&elem);
            zgzg_v[i]=elem;
            i++;
            fscanf(fd,"%c",&e);
        }
    }
}

void pgm_to_jpeg(struct pgm *in_pgm,char *fname){
    FILE *fichier=fopen(fname,"w");
    double res_blk[8][8];
    int res_zgzg[64];

    if(fichier!=NULL){
        fprintf(fichier,"JPEG\n");
        fprintf(fichier,"%d %d\n",in_pgm->width,in_pgm->height);
        for(short i = 0;i+8<=in_pgm->height;i=i+8){
            for(short j = 0;j+8<=in_pgm->width;j=j+8){
                pgm_extract_blk(in_pgm,res_blk,i,j);
                pgm_dct(res_blk);
                pgm_quantify(res_blk,Q);
                pgm_zig_zag_extract(res_blk,res_zgzg);
                pgm_rle(fichier,res_zgzg);
            }
        }


        fclose(fichier);
    }
}

void jpeg_to_pgm(char *fname){
    FILE *fichier=fopen(fname,"r");
    double res_blk[8][8];
    int res_zgzg[64];
    char e;
    for(int i=0;i<5;i++){
        fscanf(fichier,"%c",&e);
    }
    int w,h;
    fscanf(fichier,"%d %d",&w,&h);

    struct pgm *write=NULL;

    write=pgm_alloc(h,w,255);


    if(fichier!=NULL){
        for(short i = 0;i+8<=write->height;i=i+8){
            for(short j = 0;j+8<=write->width;j=j+8){
                rle_pgm(fichier,res_zgzg);
                pgm_zig_zag_reverse(res_blk,res_zgzg);
                pgm_quantify_reverse(res_blk,Q);
                pgm_idct(res_blk);
                pgm_extrect_blk_reverse(write,res_blk,i,j);
            }
        }
        fclose(fichier);
    }

    pgm_write_asc("./obj/test_reserse_jpeg.pgm",write);

    pgm_free(write);
    
}

void ppm_to_jpeg(struct ppm *in_ppm,char *fname){
    FILE *fichier=fopen(fname,"w");
    double res_blk_y[8][8];
    double res_blk_u[8][8];
    double res_blk_v[8][8];
    int res_zgzg_y[64];
    int res_zgzg_u[64];
    int res_zgzg_v[64];

    if(fichier!=NULL){
        fprintf(fichier,"JPEG\n");
        fprintf(fichier,"%d %d\n",in_ppm->width,in_ppm->height);
        for(short i = 0;i+8<=in_ppm->height;i=i+8){
            for(short j = 0;j+8<=in_ppm->width;j=j+8){
                ppm_extract_blk(in_ppm,res_blk_y,res_blk_u,res_blk_v,i,j);
                ppm_dct(res_blk_y,res_blk_u,res_blk_v);
                ppm_quantify(res_blk_y,res_blk_u,res_blk_v,Q);
                ppm_zig_zag_extract(res_blk_y,res_blk_u,res_blk_v,res_zgzg_y,res_zgzg_u,res_zgzg_v);
                ppm_rle(fichier,res_zgzg_y,res_zgzg_u,res_zgzg_v);
            }
        }


        fclose(fichier);
    }
}

void jpeg_to_ppm(char *fname){
    FILE *fichier=fopen(fname,"r");
    double res_blk_y[8][8];
    double res_blk_u[8][8];
    double res_blk_v[8][8];
    int res_zgzg_y[64];
    int res_zgzg_u[64];
    int res_zgzg_v[64];
    char e;
    for(int i=0;i<5;i++){
        fscanf(fichier,"%c",&e);
    }
    int w,h;
    fscanf(fichier,"%d %d",&w,&h);

    struct ppm *write=NULL;

    write=ppm_alloc(h,w,255);

    printf("%d %d \n",write->height,write->width);


    if(fichier!=NULL){
        for(short i = 0;i+8<=write->height;i=i+8){
            for(short j = 0;j+8<=write->width;j=j+8){
                rle_ppm(fichier,res_zgzg_y,res_zgzg_u,res_zgzg_v);
                ppm_zig_zag_reverse(res_blk_y,res_blk_u,res_blk_v,res_zgzg_y,res_zgzg_u,res_zgzg_v);
                ppm_quantify_reverse(res_blk_y,res_blk_u,res_blk_v,Q);
                ppm_idct(res_blk_y,res_blk_u,res_blk_v);
                ppm_extract_blk_reverse(write,res_blk_y,res_blk_u,res_blk_v,i,j);
            }
        }
        fclose(fichier);
    }

    ppm_write_asc("./obj/test_reserse_jpeg.ppm",write);

    ppm_free(write);
}

int fsize(char *fname){
    FILE *fichier=fopen(fname,"rb");
    int size=0;
    if(fichier!=NULL){
        char e;
        int ret;

        do{
            ret=fread(&e,sizeof(char),1,fichier);
            size=size+ret;
        }while(ret>0);
        fclose(fichier);
    }
    return size;
}
