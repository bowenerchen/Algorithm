/*
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*/

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 * }
 */
/**
  *  斜率公式：
  *     slope=(y1-y2)/(x1-x2) (其中x1 != x2)
  */
struct node{
    float slope;
    int count;
    struct node* next;
};

struct node** initial(int size){
    struct node** tab=(struct node**)malloc(sizeof(struct node*)*size);
    for(int i=0;i<size;i++)
        tab[i]=NULL;
return tab;
}

void insert(struct node** tab,int index,float slope){
    struct node* cur=tab[index];
    if(cur==NULL){
            struct node* newnode=(struct node*)malloc(sizeof(struct node));
            newnode->slope=slope;
            newnode->count=2;
            //printf("index=%d count=%d slope=%f\n",index,newnode->count,slope);
            newnode->next=NULL;
            tab[index]=newnode;
    }else{
        struct node* frd=cur;
        while(frd){
            if(frd->slope==slope){
                frd->count++;
                //printf("index=%d count=%d slope=%f\n",index,frd->count,slope);
                return;
            }
            cur=frd;
            frd=frd->next;
        }
        struct node* newnode=(struct node*)malloc(sizeof(struct node));
        newnode->slope=slope;
        newnode->count=2;
        newnode->next=NULL;
        cur->next=newnode;
    }
}

void destroy(struct node** tab,int size){
    struct node* del=NULL;
    for(int i=0;i<size;i++){
        while(tab[i]){
            del=tab[i];
            tab[i]=tab[i]->next;
            free(del);
        }
    }
    free(tab);
}

int find_max(struct node** tab,int size){
    int max=0;
    struct node* tmp=NULL;
    for(int i=0;i<size;i++){
        tmp=tab[i];
        while(tmp){
            if(tmp->count > max)
                max=tmp->count;
            tmp=tmp->next;
        }
    }
return max;
}

int maxPoints(struct Point* points, int pointsSize) {
    if(pointsSize<3)
        return pointsSize;
    struct node** tab=initial(pointsSize);
    float slope=0;
    float tmp_slope=0;
    for(int i=0;i<pointsSize;i++){
        for(int j=0;j<pointsSize;j++){
            if(i==j){
                continue;
            }else if(points[i].x==points[j].x && points[i].y==points[j].y){
                tmp_slope=9998;/*重合的点*/
                insert(tab,i,tmp_slope);
                struct node* tmp=tab[i];
                while(tmp){
                    if(tmp->slope!=9998)
                        tmp->count++;
                    tmp=tmp->next;
                }
                continue;
            }else if(points[i].x==points[j].x && points[i].y!=points[j].y){
                tmp_slope=9999;
                insert(tab,i,tmp_slope);
                continue;
            }else if(points[i].x!=points[j].x ){
                slope=(points[i].y-points[j].y)*(1.0)/(points[i].x-points[j].x);
                insert(tab,i,slope);
                continue;
            }
        }
    }
    
    int max=find_max(tab,pointsSize);
    
    destroy(tab,pointsSize);
    
return max;
}
