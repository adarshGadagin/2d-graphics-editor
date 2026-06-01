    #include <stdio.h>
    #include <math.h>

    #define WIDTH 80
    #define HEIGHT 25 

    void drawLine(char symbol){
        int x1, x2, y1, y2;
        char canvas[HEIGHT][WIDTH];
        for(int i=0;i<HEIGHT;i++){
            for(int j=0;j<WIDTH;j++){
                canvas[i][j]=' ';
            }
        }
        printf("Enter starting points (x1 y1): ");
        scanf("%d %d",&x1,&y1);
        printf("Enter starting points (x2 y2): ");
        scanf("%d %d",&x2,&y2);

        int dx=abs(x2-x1);
        int dy=abs(y2-y1);

        float slope=(float)(y2-y1)/(x2-x1);
        float inverse_slope=(float)(x2-x1)/(y2-y1);

        if(x1<WIDTH && x2<WIDTH && y1<HEIGHT && y2<HEIGHT){
            if(x1==x2){
                for(int y=y1;y<y2;y++){
                    canvas[y][x1]='*';
                }
            }else{
                if(dx>=dy){
                    int startX=(x1<x2)?x1:x2;
                    int endX=(x1<x2)?x2:x1;
                    for(int x=startX;x<=endX;x++){
                        int y=(int)round(y1+slope*(x-x1));
                        canvas[y][x]=symbol;
                    }
                }else{
                    int startY=(y1<y2)?y1:y2;
                    int endY=(y1<y2)?y2:y1;
                    for(int y=startY;y<=endY;y++){
                        int x=(int)round(x1+inverse_slope*(y-y1));
                        canvas[y][x]=symbol;
                    }
                }
            }
        }else{
            printf("Coordinates out of bound!(0-%d, 0-%d)",WIDTH-1,HEIGHT-1);
        }
        for(int i=0;i<HEIGHT;i++){
            for(int j=0;j<WIDTH;j++){
                printf("%c",canvas[i][j]);
            }
            printf("\n");
        }
    }

    int main(){
        drawLine('*');
        return 0;
    }