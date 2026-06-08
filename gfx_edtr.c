#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25 
#define MAX_OBJ 50

typedef enum {
    LINE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
} ShapeType;

// to store object information
typedef struct{
    ShapeType type;
    int x1, y1, x2, y2;  // For line, rectangle, triangle
    int x, y, radius;     // For circle
    char symbol;
    int active;           // 1 if active, 0 if deleted
} Shape;

typedef struct{
    char picture[HEIGHT][WIDTH];
    Shape objects[MAX_OBJ];
    int objectCount;
}picture;

void initializePicture(picture *p);
int isWithinBounds(int x,int y);
void displayMenu();
void addShape(picture *p);
void deleteShape(picture *p);
void redrawPicture(picture *p);
void savePicture(picture *p);
void loadPicture(picture *p);
void displayPicture(picture *p);
void drawLine(picture *p,int x1,int x2,int y1,int y2,char sym);
void drawRectangle(picture *p,int x1,int x2,int y1,int y2,char sym);
void drawTriangle(picture *p,int x1, int x2, int x, int y1, int y2, int y, char sym);
void drawCircle(picture *p,int r,int x,int y,char sym);

int isWithinBounds(int x, int y){
    return (x>=0 && x<WIDTH && y>=0 && y<HEIGHT);
}

void addShape(picture *p) {
    if (p->objectCount >= MAX_OBJ) {
        printf("\nMaximum objects limit reached!\n");
        return;
    }
 
    int shapeChoice, x1, y1, x2, y2, x3, y3, r, x, y;
    char sym;
 
    Shape newShape;
    newShape.active=1;

    printf("\n========== ADD SHAPE ==========\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Triangle\n");
    printf("4. Circle\n");
    printf("Enter shape choice: ");
    scanf("%d", &shapeChoice);
 
    printf("Enter symbol to draw with (* or _): ");
    scanf(" %c", &sym);

    newShape.symbol=sym;

    switch (shapeChoice)
    {
    case 1: // Line
        printf("Enter starting points (x1 y1): ");
        scanf("%d %d",&x1,&y1);
        printf("Enter starting points (x2 y2): ");
        scanf("%d %d",&x2,&y2);
        if(isWithinBounds(x1,y1)&&isWithinBounds(x2,y2)){
            newShape.type=LINE;
            newShape.x1=x1;
            newShape.y1=y1;
            newShape.x2=x2;
            newShape.y2=y2;
            p->objects[p->objectCount]=newShape;
                p->objectCount++;
            drawLine(p,x1,x2,y1,y2,sym);
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
            newShape.type=RECTANGLE;
            newShape.x1=x1;
            newShape.y1=y1;
            newShape.x2=x2;
            newShape.y2=y2;
            p->objects[p->objectCount]=newShape;
                p->objectCount++;
            drawRectangle(p,x1,x2,y1,y2,sym);
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
            newShape.type=TRIANGLE;
            newShape.x1=x1;
            newShape.y1=y1;
            newShape.x2=x2;
            newShape.y2=y2;
            newShape.x=x;
            newShape.y=y;
            p->objects[p->objectCount]=newShape;
                p->objectCount++;
            drawTriangle(p,x1,x2,x,y1,y2,y,sym);
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
            newShape.type=CIRCLE;
            newShape.x=x;
            newShape.y=y;
            newShape.radius=r;
            p->objects[p->objectCount] = newShape;
                p->objectCount++;
            drawCircle(p,r,x,y,sym);
        }else{
            printf("Center coordinates out of bound!");
        }
        break;
    
    default:
        printf("Invalid choice! (1-4)");
        break;
    }

}

void initializePicture(picture *p) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            p->picture[i][j] = ' ';
        }
    }
    p->objectCount = 0;
    for (int i = 0; i < MAX_OBJ; i++) {
        p->objects[i].active = 0;
    }
}

void drawLine(picture *p,int x1,int x2,int y1,int y2,char sym){
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    float slope=(float)(y2-y1)/(x2-x1);
    if(x1==x2){
        int startY=(y1<y2)?y1:y2;
        int endY=(y1<y2)?y2:y1;
        for(int y=startY;y<endY;y++){
           p->picture[y][x1]='*';
        }
    }else{
        if(dx>=dy){
            int startX=(x1<x2)?x1:x2;
            int endX=(x1<x2)?x2:x1;
            for(int x=startX;x<=endX;x++){
                int y=(int)round(y1+slope*(x-x1));
                p->picture[y][x]=sym;
            }
        }else{
            int startY=(y1<y2)?y1:y2;
            int endY=(y1<y2)?y2:y1;
            float inverse_slope=(float)(x2-x1)/(y2-y1);
            for(int y=startY;y<=endY;y++){
                int x=(int)round(x1+inverse_slope*(y-y1));
                p->picture[y][x]=sym;
            }
        }
    }
}

void drawRectangle(picture *p,int x1,int x2,int y1,int y2,char sym){
    // top edge
    for(int x=x1;x<=x2;x++){
        p->picture[y1][x]=sym;
    }
    // bottom edge
    for(int x=x1;x<=x2;x++){
        p->picture[y2][x]=sym;
    }
    // left edge
    for(int y=y1;y<=y2;y++){
        p->picture[y][x1]=sym;
    }
    // right edge
    for(int y=y1;y<=y2;y++){
        p->picture[y][x2]=sym;
    }
}

void drawTriangle(picture *p,int x1, int x2, int x, int y1, int y2, int y, char sym){
    drawLine(p,x1,x2,y1,y2,sym);
    drawLine(p,x2,x,y2,y,sym);
    drawLine(p,x,x1,y,y1,sym);
}

void drawCircle(picture *p, int r, int x, int y, char sym){
    for(int j=y-r;j<=y+r;j++){
        for(int i=x-r;i<=x+r;i++){
            int dx=i-x;
            int dy=j-y;
            if(abs(dx*dx + dy*dy - r*r)<=r)
                if (isWithinBounds(i,j))
                    p->picture[j][i]=sym;
        }
    }
}

void deleteShape(picture *p) {
    if (p->objectCount==0) {
        printf("\nNo objects to delete!\n");
        return;
    }
 
    printf("\n========== DELETE SHAPE ==========\n");
    printf("Objects in picture:\n");
    
    int validCount=0;
    for (int i=0;i<p->objectCount;i++) {
        if (p->objects[i].active) {
            validCount++;
            printf("%d. ", validCount);
            switch (p->objects[i].type) {
                case LINE:
                    printf("Line from (%d,%d) to (%d,%d)\n", 
                           p->objects[i].x1, p->objects[i].y1, 
                           p->objects[i].x2, p->objects[i].y2);
                    break;
                case RECTANGLE:
                    printf("Rectangle from (%d,%d) to (%d,%d)\n", 
                           p->objects[i].x1, p->objects[i].y1, 
                           p->objects[i].x2, p->objects[i].y2);
                    break;
                case CIRCLE:
                    printf("Circle at (%d,%d) with radius %d\n", 
                           p->objects[i].x, p->objects[i].y, p->objects[i].radius);
                    break;
                case TRIANGLE:
                    printf("Triangle with vertices (%d,%d), (%d,%d), (%d,%d)\n", 
                           p->objects[i].x1, p->objects[i].y1, 
                           p->objects[i].x2, p->objects[i].y2,
                           p->objects[i].x, p->objects[i].y);
                    break;
            }
        }
    }
 
    printf("\nEnter object number to delete (0 to cancel): ");
    int choice;
    scanf("%d",&choice);
 
    if (choice==0) {
        printf("Deletion cancelled.\n");
        return;
    }
 
    int count=0;
    for (int i=0;i<p->objectCount;i++) {
        if (p->objects[i].active) {
            count++;
            if (count==choice) {
                p->objects[i].active=0;
                printf("Object deleted successfully!\n");
                redrawPicture(p);
                return;
            }
        }
    }
 
    printf("Invalid object number!\n");
}

void displayMenu(){
    printf("\n========== MENU ==========\n");
    printf("1. Add Shape\n");
    printf("2. Delete Shape\n");
    printf("3. Display Picture\n");
    printf("4. Save Picture\n");
    printf("5. Load Picture\n");
    printf("6. Clear Picture\n");
    printf("7. Exit\n");
    printf("=========================\n");
}

void displayPicture(picture *p){
    printf("\n");
    printf("+");
    for (int i=0; i<WIDTH; i++) 
        printf("-");
    printf("+\n");
 
    for (int i=0; i<HEIGHT; i++){
        printf("|");
        for (int j=0; j<WIDTH; j++){
            printf("%c", p->picture[i][j]);
        }
        printf("|\n");
    }
 
    printf("+");
    for (int i=0; i<WIDTH; i++) 
        printf("-");
    printf("+\n");
 
    int activeCount = 0;
    for(int i=0;i<p->objectCount;i++){
        if(p->objects[i].active)
            activeCount++;
    }
    printf("\nTotal objects: %d\n", activeCount);

}

void savePicture(picture *p){
    FILE *fp = fopen("Picture.txt", "w");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
 
    fprintf(fp, "%d\n", p->objectCount);
    for(int i=0; i<p->objectCount; i++){
        if(p->objects[i].active){
            fprintf(fp, "%d %d %c %d %d %d %d %d %d %d\n",
                    p->objects[i].type,
                    p->objects[i].active,
                    p->objects[i].symbol,
                    p->objects[i].x1,
                    p->objects[i].y1,
                    p->objects[i].x2,
                    p->objects[i].y2,
                    p->objects[i].x,
                    p->objects[i].y,
                    p->objects[i].radius);
        }
    }
 
    fclose(fp);
    printf("Picture saved to 'Picture.txt'\n");
}

void loadPicture(picture *p){
    FILE *fp=fopen("picture.txt","r");
    if (fp==NULL){
        printf("No saved picture found!\n");
        return;
    }
 
    initializePicture(p);
    int objectCount;
    fscanf(fp,"%d\n",&objectCount);
 
    for(int i=0; i<objectCount && i<MAX_OBJ; i++){
        if(fscanf(fp, "%d %d %c %d %d %d %d %d %d %d\n",
               (int *)&p->objects[i].type,
               &p->objects[i].active,
               &p->objects[i].symbol,
               &p->objects[i].x1,
               &p->objects[i].y1,
               &p->objects[i].x2,
               &p->objects[i].y2,
               &p->objects[i].x,
               &p->objects[i].y,
               &p->objects[i].radius)==10)
            p->objectCount++;
        else{
            printf("Error reading object %d\n", i);
            break;
        }
    }
 
    fclose(fp);
    redrawPicture(p);
    printf("Picture loaded successfully!\n");
}

void redrawPicture(picture *p){
    for(int i=0; i<HEIGHT; i++) {
        for(int j=0; j<WIDTH; j++) {
            p->picture[i][j]=' ';
        }
    }
 
    for (int i=0;i<p->objectCount;i++){
        if(p->objects[i].active==0)
            continue;
 
        Shape *shape=&p->objects[i];
        switch (shape->type){
            case LINE:
                drawLine(p, shape->x1, shape->x2, shape->y1, shape->y2, shape->symbol);
                break;
            case RECTANGLE:
                drawRectangle(p, shape->x1, shape->x2, shape->y1, shape->y2, shape->symbol);
                break;
            case CIRCLE:
                drawCircle(p, shape->radius, shape->x, shape->y, shape->symbol);
                break;
            case TRIANGLE:
                drawTriangle(p, shape->x1, shape->x2, shape->x, shape->y1, 
                            shape->y2, shape->y, shape->symbol);
                break;
        }
    }
}

int main(){
    picture pic;
    int choice;
    int run=1;

    initializePicture(&pic);

    while (run) {
            displayMenu();
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
     
            switch (choice) {
                case 1:
                    addShape(&pic);
                    break;
                case 2:
                    deleteShape(&pic);
                    break;
                case 3:
                    displayPicture(&pic);
                    break;
                case 4:
                    savePicture(&pic);
                    break;
                case 5:
                    loadPicture(&pic);
                    break;
                case 6:
                    initializePicture(&pic);
                    break;
                case 7:
                    run = 0;
                    break;
                default:
                    printf("\nInvalid choice! Please try again.\n");
            }
        }

    return 0;
}