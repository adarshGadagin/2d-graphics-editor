#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25 

typedef struct{
    char canvas[HEIGHT][WIDTH];
}size;

int isWithinBounds(int x,int y);
void drawLine(size *c,int x1,int x2,int y1,int y2,char sym);
void drawRectangle(size *c,int x1,int x2,int y1,int y2,char sym);
void drawTriangle(size *c,int x1, int x2, int x, int y1, int y2, int y, char sym);
void drawCircle(size *c,int r,int x,int y,char sym);
void drawObject();

// typedef struct{
//     int x1, x2, y1, y2;
//     int x, y, r;
// }input;

int isWithinBounds(int x, int y){
    return (x>=0 && x<WIDTH && y>=0 && y<HEIGHT);
}

void drawObject(){
    int x1, x2, y1, y2;
    int x, y, r;
    char sym;
    int shape;
    size c;

    printf("==============Shapes==============\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Triangle\n");
    printf("4. Circle\n");
    printf("Enter your choice: ");
    scanf("%d",&shape);

    printf("Enter symbol to draw (* or _): ");
    scanf(" %c",&sym);

    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            c.canvas[i][j]=' ';
        }
    }

    switch (shape)
    {
    case 1: // Line
        printf("Enter starting points (x1 y1): ");
        scanf("%d %d",&x1,&y1);
        printf("Enter starting points (x2 y2): ");
        scanf("%d %d",&x2,&y2);
        if(isWithinBounds(x1,y1)&&isWithinBounds(x2,y2)){
            drawLine(&c,x1,x2,y1,y2,sym);
        }else{
            printf("Coordinates out of bound!(0-%d, 0-%d)",WIDTH-1,HEIGHT-1);
        }
        break;

    case 2: // Rectangle
        printf("Enter top left corner (x1 y1): ");
        scanf("%d %d",&x1,&y1);
        printf("Enter bottom right corner (x2 y2): ");
        scanf("%d %d",&x2,&y2);
        if(isWithinBounds(x1,y1)&&isWithinBounds(x2,y2)){
            drawRectangle(&c,x1,x2,y1,y2,sym);
        }else{
            printf("Coordinates out of bound!(0-%d, 0-%d)",WIDTH-1,HEIGHT-1);
        }
        break;

    case 3: //Triangle
        printf("Enter first vertex (x1 y1): ");
        scanf("%d %d",&x1,&y1);
        printf("Enter second vertex (x2 y2): ");
        scanf("%d %d",&x2,&y2);
        printf("Enter third vertex (x3 y3): ");
        scanf("%d %d",&x,&y);
        if(isWithinBounds(x1,y1) && isWithinBounds(x2,y2) && isWithinBounds(x,y)){
            drawTriangle(&c,x1,x2,x,y1,y2,y,sym);
        }else{
            printf("one or more vertices out of bound!");
        }
        break;

    case 4: //Circle
        printf("Enter coordinates of center of circle: ");
        scanf("%d %d",&x, &y);
        printf("Enter radius of circle: ");
        scanf("%d",&r);
        if(isWithinBounds(x,y)){
            drawCircle(&c,r,x,y,sym);
        }else{
            printf("Center coordinates out of bound!");
        }
        break;
    
    default:
    printf("Invalid choice! (1-4)");
        break;
    }

    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            printf("%c",c.canvas[i][j]);
        }
        printf("\n");
    }
}

void drawLine(size *c,int x1,int x2,int y1,int y2,char sym){
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    float slope=(float)(y2-y1)/(x2-x1);
    if(x1==x2){
        int startY=(y1<y2)?y1:y2;
        int endY=(y1<y2)?y2:y1;
        for(int y=startY;y<endY;y++){
           c->canvas[y][x1]='*';
        }
    }else{
        if(dx>=dy){
            int startX=(x1<x2)?x1:x2;
            int endX=(x1<x2)?x2:x1;
            for(int x=startX;x<=endX;x++){
                int y=(int)round(y1+slope*(x-x1));
                c->canvas[y][x]=sym;
            }
        }else{
            int startY=(y1<y2)?y1:y2;
            int endY=(y1<y2)?y2:y1;
            float inverse_slope=(float)(x2-x1)/(y2-y1);
            for(int y=startY;y<=endY;y++){
                int x=(int)round(x1+inverse_slope*(y-y1));
                c->canvas[y][x]=sym;
            }
        }
    }
}

void drawRectangle(size *c,int x1,int x2,int y1,int y2,char sym){
    // top edge
    for(int x=x1;x<=x2;x++){
        c->canvas[y1][x]=sym;
    }
    // bottom edge
    for(int x=x1;x<=x2;x++){
        c->canvas[y2][x]=sym;
    }
    // left edge
    for(int y=y1;y<=y2;y++){
        c->canvas[y][x1]=sym;
    }
    // right edge
    for(int y=y1;y<=y2;y++){
        c->canvas[y][x2]=sym;
    }
}

void drawTriangle(size *c,int x1, int x2, int x, int y1, int y2, int y, char sym){
    drawLine(c,x1,x2,y1,y2,sym);
    drawLine(c,x2,x,y2,y,sym);
    drawLine(c,x,x1,y,y1,sym);
}

void drawCircle(size *c, int r, int x, int y, char sym){
    for(int j=y-r;j<=y+r;j++){
        for(int i=x-r;i<=x+r;i++){
            int dx=i-x;
            int dy=j-y;
            if(abs(dx*dx + dy*dy - r*r) <= r)
                c->canvas[j][i]=sym;
        }
    }
}

int main(){
    drawObject();
    return 0;
}