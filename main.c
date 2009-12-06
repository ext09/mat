#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_gfxPrimitives_font.h"
#include "SDL/SDL_image.h"
#include <string.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

SDL_Event event;

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Rectangle to hold the offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

/*void drawgraph(int i, int j, int *pr, SDL_Surface* scr )
{
    lineColor(scr, pr[i][j], pr[i+1][j], pr[i][j+1], pr[i+1][j+1], 0x0000FFFF);
    lineColor(scr, pr[i][j], pr[i+1][j]+1, pr[i][j+1], pr[i+1][j+1]+1, 0x0000FFFF);
    pixelColor(scr, pr[i][j], pr[i+1][j], 0x00FFFFFF);
    pixelColor(scr, pr[i][j+1], pr[i+1][j+1], 0x00FFFFFF);
}*/

void Drawgraf(int p, int t, int *bb, SDL_Surface* screen  )
{
    int k;
    for (k=1; k<=p-1; k++)
    {
        lineColor(screen, bb[t*3+k], bb[(t+1)*3+k], bb[t*3+(k+1)], bb[(t+1)*3+(k+1)], 0x0000FFFF);
        lineColor(screen, bb[t*3+k], bb[(t+1)*3+k]+1, bb[t*3+(k+1)], bb[(t+1)*3+(k+1)]+1, 0x0000FFFF);
        //pixelColor(screen, bb[t][k], bb[t+1][k], 0x00FFFFFF);
        //pixelColor(screen, bb[t][k+1], bb[t+1][k+1], 0x00FFFFFF);
        SDL_Flip(screen);
    }
}

void CheckMouseHover(int i, int j, int k, int l, SDL_Surface* button,SDL_Surface* button1,SDL_Surface* screen)

{
    int mouse_x, mouse_y;

    if ( event.type == SDL_MOUSEMOTION )
    {
        //Get the mouse offsets
        mouse_x = event.motion.x;
        mouse_y = event.motion.y;

        if ( ((mouse_x <i) && (mouse_x >j) ) &&( (mouse_y > k) && (mouse_y < l)) )
        {
            apply_surface(j , k, button, screen );
            SDL_Flip(screen);

        }
        else
        {
            apply_surface(j , k, button1, screen );
            SDL_Flip(screen);
        }


    }
}


int main(int argc, char *argv[])

{

    int quit = 0;
    FILE *data;
    FILE *out;
    char ch;
    int aa[10][15];
    int i,j,n, k, l, p, m;
    int t[10];
    int bb[3][10];
    char str[10], str1[10];
    char *token;

    if ((data = fopen("data.txt","r+"))==NULL)
    {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    if ((out = fopen("out.txt","w+"))==NULL)
    {
        printf("Ошибка при открытии файла.\n");
        exit(1);
    }

    for (m=0; m<=2; m++)
    {
        for (i=0; i<=10; i++)
            bb[m][i]=0;
    }

    i=0;
    j=0;
    n=1;
    i=0;
    k=0;

    do
    {
        ch = getc(data);
        if (ch=='\n')
        {
            t[j]=i;
            i=0;
            j++;
        }
        fscanf(data, "%s", str);
        //j++;
        token = strtok(str," ");
        //fputs(str1,out);
        //while (token !=NULL)
        i++;
        strcpy(str1,token);
        aa[j][i]=atoi(str1);
        fprintf(out,"%d%c",aa[j][i],' ');

    }
    while (ch != EOF);
    fprintf(out,"%d%c%d", i,' ', j);
    //for(l=0; l<=j; l++)
    //fprintf(out,"%d%c", t[l],' ');

    if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 )
    {

        fprintf(stderr, "Не могу инициализировать SDL: %s\n", SDL_GetError());

        exit(1);

    }

    atexit(SDL_Quit);


    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Surface *button1;
    SDL_Surface *button2;
    SDL_Surface *button11;
    SDL_Surface *button22;
    SDL_Surface *button3;
    SDL_Surface *button4;

    button1 = IMG_Load("button1.png");
    button11 = IMG_Load("button11.png");
    button2 = IMG_Load("button2.png");
    button22 = IMG_Load("button22.png");
    button3 = IMG_Load("button3.png");
    button4 = IMG_Load("button4.png");

    image = IMG_Load("pole.jpg");
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    if ( screen == NULL )  // Если установить разрешение не удалось
    {

        fprintf(stderr, "Невозможно установить разрешение 640x480: %s\n", SDL_GetError());

        exit(1);

    }

    apply_surface( 0, 0, image, screen );
    apply_surface( 0, 500, button1, screen );
    apply_surface( 350, 500, button2, screen );

    for(k=1; k<=i-2; k++)
    /*{
    lineColor(screen, aa[0][k], aa[1][k], aa[0][k+1], aa[1][k+1], 0x0000FFFF);
    lineColor(screen, aa[0][k], aa[1][k]+1, aa[0][k+1], aa[1][k+1]+1, 0x0000FFFF);
    pixelColor(screen, aa[0][k], aa[1][k], 0x00FFFFFF);
    pixelColor(screen, aa[0][k+1], aa[1][k+1], 0x00FFFFFF);
    }*/

    SDL_Flip(screen);

    while ( quit == 0 )
    {
        //If there's an event to handle


        if ( SDL_WaitEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
            {
                quit = 1;
            }
            //If a key was pressed
            CheckMouseHover(320, 0, 500, 580,button3, button1, screen);

            CheckMouseHover(670, 350, 500, 580,button4, button2, screen);

            int mouse_x, mouse_y;

            if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
                //If the left mouse button was pressed
                if ( event.button.button == SDL_BUTTON_LEFT )
                {
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;

                    if ( ((mouse_x <320) && (mouse_x >0) ) &&( (mouse_y > 500) && (mouse_y < 580)) )
                    {
                        apply_surface( 0, 0, image, screen );
                        apply_surface(0 , 500, button11, screen );
                        apply_surface( 350, 500, button2, screen );

                        if ((bb[0][1]==0)||(bb[1][1]==0))
                        {
                            for (i=1; i<=t[0]; i++)
                            {
                                for (k=0; k<=j; k++)
                                {
                                    if ((k%2)==0)
                                        bb[0][i]+=aa[k][i]/2;
                                    else
                                        bb[1][i]+=aa[k][i]/2;
                                }
                                fprintf(out,"%d%c", t[0],' ');

                            }
                        }
                        for (k=1; k<=t[0]-1; k++)
                        {
                            lineColor(screen, bb[0][k], bb[1][k], bb[0][k+1], bb[1][k+1], 0x0000FFFF);
                            lineColor(screen, bb[0][k], bb[1][k]+1, bb[0][k+1], bb[1][k+1]+1, 0x0000FFFF);
                            pixelColor(screen, bb[0][k], bb[1][k], 0x00FFFFFF);
                            pixelColor(screen, bb[0][k+1], bb[1][k+1], 0x00FFFFFF);
                            /*drawgraph(0,k,bb,screen);*/
                            fprintf(out,"%d%c%d", bb[0][k],' ', bb[1][k]);
                        }

                        //Drawgraf(t[0], 0, bb[3][10], screen );

                        SDL_Flip(screen);

                    }


                    else

                        if ( ((mouse_x <670) && (mouse_x >350) ) &&( (mouse_y > 500) && (mouse_y < 580)) )
                        {
                            apply_surface( 0, 0, image, screen );
                            apply_surface(0 , 500, button1, screen );
                            apply_surface(350 , 500, button22, screen );
                            SDL_Flip(screen);
                        }
                }
            }


        if ( event.type == SDL_KEYDOWN )
        {
            if ( event.key.keysym.sym == SDLK_ESCAPE  )
            {
                //Quit the program
                quit = 1;
            }
            //Set the proper message surface
            switch ( event.key.keysym.sym )
            {
            case SDLK_UP:
            {
                apply_surface( 0, 0, image, screen );
                apply_surface( 350, 500, button2, screen );
                apply_surface( 0, 500, button11, screen );
                /*bb[0][1]=(aa[0][1]+aa[2][1]+aa[4][1])/2;
                bb[0][2]=(aa[0][2]+aa[2][2]+aa[4][2])/2;
                bb[0][3]=(aa[0][3]+aa[2][3]+aa[4][3])/2;
                bb[0][4]=(aa[0][4]+aa[2][4]+aa[4][4])/2;
                bb[0][5]=(aa[0][5]+aa[2][5]+aa[4][5])/2;
                bb[1][1]=(aa[1][1]+aa[3][1]+aa[5][1])/2;
                bb[1][2]=(aa[1][2]+aa[3][2]+aa[5][2])/2;
                bb[1][3]=(aa[1][3]+aa[3][3]+aa[5][3])/2;
                bb[1][4]=(aa[1][4]+aa[3][4]+aa[5][4])/2;
                bb[1][5]=(aa[1][5]+aa[3][5]+aa[5][5])/2;
                if ((bb[0][1]==0)||(bb[1][1]==0))*/
                {
                    for (i=1; i<=t[0]; i++)
                    {
                        for (k=0; k<=j; k++)
                        {
                            if ((k%2)==0)
                                bb[0][i]+=aa[k][i]/2;
                            else
                                bb[1][i]+=aa[k][i]/2;
                        }

                    }
                }
                for (k=1; k<=t[0]-1; k++)
                {
                    lineColor(screen, bb[0][k], bb[1][k], bb[0][k+1], bb[1][k+1], 0x0000FFFF);
                    lineColor(screen, bb[0][k], bb[1][k]+1, bb[0][k+1], bb[1][k+1]+1, 0x0000FFFF);
                    pixelColor(screen, bb[0][k], bb[1][k], 0x00FFFFFF);
                    pixelColor(screen, bb[0][k+1], bb[1][k+1], 0x00FFFFFF);
                    /*drawgraph(0,k,bb,screen);*/
                    fprintf(out,"%d%c%d", bb[0][k],' ', bb[1][k]);
                }
                SDL_Flip(screen);
            }
            break;
            case SDLK_DOWN:
            {
                apply_surface( 0, 0, image, screen );
                apply_surface( 0, 500, button1, screen );
                apply_surface( 350, 500, button22, screen );
                SDL_Flip(screen);
            }
            break;
            case SDLK_SPACE:
            {
                apply_surface( 0, 0, image, screen );
                for (l=0, p=0;l<=j/2; l++)
                {
                    for (k=1; k<=t[p]-1; k++)
                    {
                        lineColor(screen, aa[p][k], aa[p+1][k], aa[p][k+1], aa[p+1][k+1], 0x0000FFFF);
                        lineColor(screen, aa[p][k], aa[p+1][k]+1, aa[p][k+1], aa[p+1][k+1]+1, 0x0000FFFF);
                        pixelColor(screen, aa[p][k], aa[p+1][k], 0x00FFFFFF);
                        pixelColor(screen, aa[p][k+1], aa[p+1][k+1], 0x00FFFFFF);
                        apply_surface( 350, 500, button2, screen );
                        apply_surface( 0, 500, button1, screen );
                        SDL_Flip(screen);
                    }
                    p=p+2;
                }
            }
            break;

            }
            //CheckMousedown(320, 0, 500, 580,button11, button1, screen, *bb, t[0], 0);
        }
     }
        //If the user has Xed out the window

    }
    fclose(data);
    fclose(out);
   // SDL_Flip(screen);
    SDL_Delay(1000);
    return 0;
}
