#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree{
    int x;
    struct tree* left;
    struct tree* right;
};
struct tree* addTree(struct tree* p, int elem){
    if(p==NULL){
        struct tree* d=malloc(sizeof(struct tree));
        d->x=elem;
        d->left=NULL;
        d->right=NULL;
        p=d;
    }
    else{
            if (elem>=p->x) p->right = addTree(p->right,elem);
            else  if (elem<p->x) p->left = addTree(p->left,elem);
    }
    return p;
}
void deleteTree(struct tree* p){
    if(p!=NULL){
            deleteTree(p->left);
            deleteTree(p->right);
            free(p);
  }
}
void newFile(char* name, int n){
    FILE* f;
    int c,i,k=0;
    char* s=malloc((strlen(name)+5)*sizeof(char));
    strcpy(s,name);
    strcat(s,".bin");
    f=fopen(s,"w");
    for(i=0;i<n;i++){
        while (scanf("%d", &k) == 1 && k) {
            fwrite(&k,sizeof(int),1,f);
        }
        fwrite(&k,sizeof(int),1,f);//записываем ноль
    }
    fclose(f);
    free(s);
}
void bin_to_txt(char* name){
    char* s=malloc((strlen(name)+5)*sizeof(char));
    char* s2=malloc((strlen(name)+6)*sizeof(char));
    strcpy(s,name);
    strcat(s,".bin");
    strcpy(s2,name);
    strcat(s2,"T.txt");
    FILE* f;
    FILE* f2;
    int c;
    if((f=fopen(s,"r"))==NULL)printf("empty/error");
    else{
            f2=fopen(s2, "w");
            while (fread(&c,sizeof(int),1,f) == 1){
                if(c!=0) {
                    fprintf(f2,"%d ",c);
                    printf("%d ", c);
                } else {
                    fprintf(f2,"%c",'\n');
                    printf("\n");
                }
            }
            fclose(f);
            fclose(f2);
    }
    free(s);
    free(s2);
}
void copy(struct tree *t, FILE* f){
    int c;
    if (t!=NULL){
            copy(t->right,f);
            c=t->x;
            fwrite(&c,sizeof(int),1,f);
            copy(t->left,f);
    }
}
void sort(char* name){
    FILE* f;
    struct tree* t = NULL;
    int c,begin,end;
    char* s=malloc((strlen(name)+5)*sizeof(char));
    strcpy(s,name);
    strcat(s,".bin");
    if((f=fopen(s,"r+"))==NULL)printf("empty/error");
    else{
        while (!feof(f)){
            begin = ftell(f);
            c = 1;
            while (fread(&c,sizeof(int),1,f)==1 && c!= 0){
                t = addTree(t,c);
            }
            if (c == 0) {
                fseek(f,begin,SEEK_SET);
                copy(t,f);
                fseek(f,sizeof(int),SEEK_CUR);
            }
            deleteTree(t);
            t = NULL;

        }
    }
    fclose(f);
    free(s);
}
int main(int argc, char **argv)
{
    int n;
    if(argc<2){
        printf("Error");
        return 0;
    }

    printf("enter n\n");
    scanf("%d",&n);
    newFile(argv[1],n);
    bin_to_txt(argv[1]);
    sort(argv[1]);
    bin_to_txt(argv[1]);
    return 0;
}
