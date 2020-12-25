#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

bool checkrange1(int i, int j){
    if(i<0 || i> 4 || j<0 || j>5){
        return false;
    }
    return true;
}

void algorithm_B(Board board, Player player, int index[]){
    /*srand(time(NULL)*time(NULL));
    int row, col;
    int color = player.get_color();
    
    while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }

    index[0] = row;
    index[1] = col;*/
    int row, col;
    int my_color = player.get_color();
   
    int mat1[5][6];     //my chess
    int mat2[5][6];

    for(int i = 0; i<5 ; i++){
        for(int j = 0; j<6 ; j++){
            if(board.get_cell_color(i,j)== my_color){
                mat1[i][j] = board.get_orbs_num(i,j);
                mat2[i][j] = -1;
            }else if(board.get_cell_color(i,j)== 'w'){
                mat1[i][j] = 0;
                mat2[i][j] = 0;
            }else{
                mat1[i][j] = -1;
                mat2[i][j] = board.get_orbs_num(i,j);
            }
        }
    }

    bool no_limit = true;
    int l1=-1,l2=-1;

    for(int i = 0; i<5 ; i++){
        for(int j = 0; j<6 ; j++){
            if(mat2[i][j] == board.get_capacity(i,j)-1){
                no_limit = false;
                l1 = i; l2 = j;
            }
        }
    }    
    //cout<< no_limit<<endl;
    if(no_limit == true){
                   //4 angle
        if((mat2[0][0]==0 || mat2[0][0]==-1 )&& !(mat1[0][0] == 2) ){
            index[0] = 0;
            index[1] = 0;
        }
        else if((mat2[0][5]==0 || mat2[0][5]==-1 )&& !(mat1[0][5] == 2) ){
            index[0] = 0;
            index[1] = 5;
        }
        else if((mat2[4][0]==0 || mat2[4][0]==-1 )&& !(mat1[4][0] == 2) ){
            index[0] = 4;
            index[1] = 0;
        }
        else if((mat2[4][5]==0 || mat2[4][5]==-1 )&& !(mat1[4][5] == 2) ){
            index[0] = 4;
            index[1] = 5;
        }
        else{  
                     //4 side + 2 center
            if((mat2[2][2]==0 || mat2[2][2]==-1 )&& !(mat1[2][2] == 7)){
                index[0] = 2;
                index[1] = 2;
            }else if((mat2[2][3]==0 || mat2[2][3]==-1 )&& !(mat1[2][3] == 7)){
                index[0] = 2;
                index[1] = 3;
            }

            for(int i = 1 ; i<5 ; i++){
                if((mat2[0][i]==0 || mat2[0][i]==-1 )&& !(mat1[0][i] == 4) ){
                    if(i%2 == 0 && mat1[0][i] == 3){
                        continue;
                    }
                    index[0] = 0;
                    index[1] = i;
                    break;
                }else if((mat2[4][i]==0 || mat2[4][i]==-1) && !(mat1[4][i] == 4)){
                    if(i%2 == 0 && mat1[0][i] == 3){
                        continue;
                    }
                    index[0] = 4;
                    index[1] = i;
                    break;
                }
            }
            for(int i = 1 ; i<4 ; i++){
                if((mat2[i][0]==0 || mat2[i][0]==-1 )&& !(mat1[i][0] == 4) ){
                    if(i%2 == 0 && mat1[0][i] == 3){
                        continue;
                    }
                    index[0] = i;
                    index[1] = 0;
                    break;
                }else if((mat2[i][5]==0 || mat2[i][5]==-1 )&& !(mat1[i][5] == 4)){
                    if(i%2 == 0 && mat1[0][i] == 3){
                        continue;
                    }
                    index[0] = i;
                    index[1] = 5;
                    break;
                }
            }  
        }
    }else{
        int ans[5][6];
        for(int i = 0; i<5 ; i++){
            for(int j = 0; j<6 ; j++){
                if(mat1[i][j] == -1){
                    ans[i][j] = -1;
                }else{
                    ans[i][j] = 0;
                }
            }
        }

        while(1){
            row = rand() % 5;
            col = rand() % 6;
            if((board.get_cell_color(row, col) == my_color || board.get_cell_color(row, col) == 'w')&&(mat2[row][col] == 0||mat2[row][col] == -1)
                &&ans[row][col] != -1) break;
        }
        index[0] = row;
        index[1] = col;


        for(int i = 0; i<5 ; i++){
            for(int j = 0; j<6 ; j++){
                if(mat2[i][j] == board.get_capacity(i,j)-1){
                    int ul1 = (checkrange1(i-1,j-1))? mat1[i-1][j-1]+8-board.get_capacity(i-1,j-1) : 10;
                    int u1 = (checkrange1(i-1,j))? mat1[i-1][j]+8-board.get_capacity(i-1,j) : 10;
                    int ur1 = (checkrange1(i-1,j+1))? mat1[i-1][j+1]+8-board.get_capacity(i-1,j+1) : 10;
                    int l1 = (checkrange1(i,j-1))? mat1[i][j-1]+8-board.get_capacity(i,j-1) : 10;
                    int r1 = (checkrange1(i,j+1))? mat1[i][j+1]+8-board.get_capacity(i,j+1) : 10;
                    int dl1 = (checkrange1(i+1,j-1))? mat1[i+1][j-1]+8-board.get_capacity(i+1,j-1) : 10;
                    int d1 = (checkrange1(i+1,j))? mat1[i+1][j]+8-board.get_capacity(i+1,j) : 10;
                    int dr1 = (checkrange1(i+1,j+1))? mat1[i+1][j+1]+8-board.get_capacity(i+1,j+1) : 10;

                    int ul2 = (checkrange1(i-1,j-1))? mat2[i-1][j-1]+8-board.get_capacity(i-1,j-1) : 10;
                    int u2 = (checkrange1(i-1,j))? mat2[i-1][j]+8-board.get_capacity(i-1,j) : 10;
                    int ur2 = (checkrange1(i-1,j+1))? mat2[i-1][j+1]+8-board.get_capacity(i-1,j+1) : 10;
                    int l2 = (checkrange1(i,j-1))? mat2[i][j-1]+8-board.get_capacity(i,j-1) : 10;
                    int r2 = (checkrange1(i,j+1))? mat2[i][j+1]+8-board.get_capacity(i,j-1) : 10;
                    int dl2 = (checkrange1(i+1,j-1))? mat2[i+1][j-1]+8-board.get_capacity(i+1,j-1) : 10;
                    int d2 = (checkrange1(i+1,j))? mat2[i+1][j]+8-board.get_capacity(i+1,j) : 10;
                    int dr2 = (checkrange1(i+1,j+1))? mat2[i+1][j+1]+8-board.get_capacity(i+1,j+1) : 10;

                    if(ul1 == 6){
                        int c11 = (checkrange1(i-1,j-2))? mat1[i-1][j-2]+8-board.get_capacity(i-1,j-2) : 10;
                        int c12 = (checkrange1(i-2,j-2))? mat1[i-2][j-2]+8-board.get_capacity(i-2,j-2) : 10;
                        int c13 = (checkrange1(i-2,j-1))? mat1[i-2][j-1]+8-board.get_capacity(i-2,j-1) : 10;

                        int c21 = (checkrange1(i-1,j-2))? mat2[i-1][j-2]+8-board.get_capacity(i-1,j-2) : 10;
                        int c22 = (checkrange1(i-2,j-2))? mat2[i-2][j-2]+8-board.get_capacity(i-2,j-2) : 10;
                        int c23 = (checkrange1(i-2,j-1))? mat2[i-2][j-1]+8-board.get_capacity(i-2,j-1) : 10;
                        
                        if(c21 == 7){
                            if(c12 == 7){
                                index[0] = i-2;
                                index[1] = j-2;
                            }else if(c13 == 7){
                                index[0] = i-2;
                                index[1] = j-1;
                            }
                        }else if(c22 == 7){
                            if(c11 == 7){
                                index[0] = i-1;
                                index[1] = j-2;
                            }else if(c13 == 7){
                                index[0] = i-2;
                                index[1] = j-1;
                            }
                        }else if(c23 == 7){
                            if(c12 == 7){
                                index[0] = i-2;
                                index[1] = j-2;
                            }else if(c11 == 7){
                                index[0] = i-1;
                                index[1] = j-2;
                            }
                        }else{
                            if(c11 == 6 && c12 <= 6 && c13 <=6 ){
                                index[0] = i-1;
                                index[1] = j-2;
                            }else if(c12 == 6 && c11 <= 6 && c13 <=6 ){
                                index[0] = i-2;
                                index[1] = j-2;
                            }else if(c13 == 6 && c12 <= 6 && c11 <=6 ){
                                index[0] = i-2;
                                index[1] = j-1;
                            }else{
                                if(c11 == 5 && c12 <= 5 && c13 <=5 ){
                                    index[0] = i-1;
                                    index[1] = j-2;
                                }else if(c12 == 5 && c11 <= 5 && c13 <=5 ){
                                    index[0] = i-2;
                                    index[1] = j-2;
                                }else if(c13 == 5 && c12 <= 5 && c11 <=5 ){
                                    index[0] = i-2;
                                    index[1] = j-1;
                                }
                            }
                        }

                    }else if(u1 == 6){
                        int c11 = (checkrange1(i-2,j-1))? mat1[i-2][j-1]+8-board.get_capacity(i-2,j-1) : 10;
                        int c12 = (checkrange1(i-2,j))? mat1[i-2][j]+8-board.get_capacity(i-2,j) : 10;
                        int c13 = (checkrange1(i-2,j+1))? mat1[i-2][j+1]+8-board.get_capacity(i-2,j+1) : 10;

                        int c21 = (checkrange1(i-2,j-1))? mat2[i-2][j-1]+8-board.get_capacity(i-2,j-1) : 10;
                        int c22 = (checkrange1(i-2,j))? mat2[i-2][j]+8-board.get_capacity(i-2,j) : 10;
                        int c23 = (checkrange1(i-2,j+1))? mat2[i-2][j+1]+8-board.get_capacity(i-2,j+1) : 10;
                        
                        if(c21 == 7){
                            if(c12 == 7){
                                index[0] = i-2;
                                index[1] = j;
                            }else if(c13 == 7){
                                index[0] = i-2;
                                index[1] = j+1;
                            }
                        }else if(c22 == 7){
                            if(c11 == 7){
                                index[0] = i-2;
                                index[1] = j-1;
                            }else if(c13 == 7){
                                index[0] = i-2;
                                index[1] = j+1;
                            }
                        }else if(c23 == 7){
                            if(c12 == 7){
                                index[0] = i-2;
                                index[1] = j;
                            }else if(c11 == 7){
                                index[0] = i-2;
                                index[1] = j-1;
                            }
                        }else{
                            if(c11 == 6 && c12 <= 6 && c13 <=6 ){
                                index[0] = i-2;
                                index[1] = j-1;
                            }else if(c12 == 6 && c11 <= 6 && c13 <=6 ){
                                index[0] = i-2;
                                index[1] = j;
                            }else if(c13 == 6 && c12 <= 6 && c11 <=6 ){
                                index[0] = i-2;
                                index[1] = j+1;
                            }else{
                                if(c11 == 5 && c12 <= 5 && c13 <=5 ){
                                    index[0] = i-2;
                                    index[1] = j-1;
                                }else if(c12 == 5 && c11 <= 5 && c13 <=5 ){
                                    index[0] = i-2;
                                    index[1] = j;
                                }else if(c13 == 5 && c12 <= 5 && c11 <=5 ){
                                    index[0] = i-2;
                                    index[1] = j+1;
                                }
                            }
                        }
                    }else if(ur1 == 6){
                        int c11 = (checkrange1(i-2,j+1))? mat1[i-2][j+1]+8-board.get_capacity(i-2,j+1) : 10;
                        int c12 = (checkrange1(i-2,j+2))? mat1[i-2][j+2]+8-board.get_capacity(i-2,j+2) : 10;
                        int c13 = (checkrange1(i-1,j+2))? mat1[i-1][j+2]+8-board.get_capacity(i-1,j+2) : 10;

                        int c21 = (checkrange1(i-2,j+1))? mat2[i-2][j+1]+8-board.get_capacity(i-2,j+1) : 10;
                        int c22 = (checkrange1(i-2,j+2))? mat2[i-2][j+2]+8-board.get_capacity(i-2,j+2) : 10;
                        int c23 = (checkrange1(i-1,j+2))? mat2[i-1][j+2]+8-board.get_capacity(i-1,j+2) : 10;
                        
                        if(c21 == 7){
                            if(c12 == 7){
                                index[0] = i-2;
                                index[1] = j+2;
                            }else if(c13 == 7){
                                index[0] = i-1;
                                index[1] = j+2;
                            }
                        }else if(c22 == 7){
                            if(c11 == 7){
                                index[0] = i-2;
                                index[1] = j+1;
                            }else if(c13 == 7){
                                index[0] = i-1;
                                index[1] = j+2;
                            }
                        }else if(c23 == 7){
                            if(c12 == 7){
                                index[0] = i-2;
                                index[1] = j+2;
                            }else if(c11 == 7){
                                index[0] = i-2;
                                index[1] = j+1;
                            }
                        }else{
                            if(c11 == 6 && c12 <= 6 && c13 <=6 ){
                                index[0] = i-2;
                                index[1] = j+1;
                            }else if(c12 == 6 && c11 <= 6 && c13 <=6 ){
                                index[0] = i-2;
                                index[1] = j+2;
                            }else if(c13 == 6 && c12 <= 6 && c11 <=6 ){
                                index[0] = i-1;
                                index[1] = j+2;
                            }else{
                                if(c11 == 5 && c12 <= 5 && c13 <=5 ){
                                    index[0] = i-2;
                                    index[1] = j+1;
                                }else if(c12 == 5 && c11 <= 5 && c13 <=5 ){
                                    index[0] = i-2;
                                    index[1] = j+2;
                                }else if(c13 == 5 && c12 <= 5 && c11 <=5 ){
                                    index[0] = i-1;
                                    index[1] = j+2;
                                }
                            }
                        }
                    }else if(l1 == 6){
                        int c11 = (checkrange1(i-1,j-2))? mat1[i-1][j-2]+8-board.get_capacity(i-1,j-2) : 10;
                        int c12 = (checkrange1(i,j-2))? mat1[i][j-2]+8-board.get_capacity(i,j-2) : 10;
                        int c13 = (checkrange1(i+1,j-2))? mat1[i+1][j-2]+8-board.get_capacity(i+1,j-2) : 10;

                        int c21 = (checkrange1(i-1,j-2))? mat2[i-1][j-2]+8-board.get_capacity(i-1,j-2) : 10;
                        int c22 = (checkrange1(i,j-2))? mat2[i][j-2]+8-board.get_capacity(i,j-2) : 10;
                        int c23 = (checkrange1(i+1,j-2))? mat2[i+1][j-2]+8-board.get_capacity(i+1,j-2) : 10;
                        
                        if(c21 == 7){
                            if(c12 == 7){
                                index[0] = i;
                                index[1] = j-2;
                            }else if(c13 == 7){
                                index[0] = i+1;
                                index[1] = j-2;
                            }
                        }else if(c22 == 7){
                            if(c11 == 7){
                                index[0] = i-1;
                                index[1] = j-2;
                            }else if(c13 == 7){
                                index[0] = i+1;
                                index[1] = j-2;
                            }
                        }else if(c23 == 7){
                            if(c12 == 7){
                                index[0] = i;
                                index[1] = j-2;
                            }else if(c11 == 7){
                                index[0] = i-1;
                                index[1] = j-2;
                            }
                        }else{
                            if(c11 == 6 && c12 <= 6 && c13 <=6 ){
                                index[0] = i-1;
                                index[1] = j-2;
                            }else if(c12 == 6 && c11 <= 6 && c13 <=6 ){
                                index[0] = i;
                                index[1] = j-2;
                            }else if(c13 == 6 && c12 <= 6 && c11 <=6 ){
                                index[0] = i+1;
                                index[1] = j-2;
                            }else{
                                if(c11 == 5 && c12 <= 5 && c13 <=5 ){
                                    index[0] = i-1;
                                    index[1] = j-2;
                                }else if(c12 == 5 && c11 <= 5 && c13 <=5 ){
                                    index[0] = i;
                                    index[1] = j-2;
                                }else if(c13 == 5 && c12 <= 5 && c11 <=5 ){
                                    index[0] = i+1;
                                    index[1] = j-2;
                                }
                            }
                        }
                    }else if(r1 == 6){
                        int c11 = (checkrange1(i-1,j+2))? mat1[i-1][j+2]+8-board.get_capacity(i-1,j+2) : 10;
                        int c12 = (checkrange1(i,j+2))? mat1[i][j+2]+8-board.get_capacity(i,j+2) : 10;
                        int c13 = (checkrange1(i+1,j+2))? mat1[i+1][j+2]+8-board.get_capacity(i+1,j+2) : 10;

                        int c21 = (checkrange1(i-1,j+2))? mat2[i-1][j+2]+8-board.get_capacity(i-1,j+2) : 10;
                        int c22 = (checkrange1(i,j+2))? mat2[i][j+2]+8-board.get_capacity(i,j+2) : 10;
                        int c23 = (checkrange1(i+1,j+2))? mat2[i+1][j+2]+8-board.get_capacity(i+1,j+2) : 10;
                        
                        if(c21 == 7){
                            if(c12 == 7){
                                index[0] = i;
                                index[1] = j+2;
                            }else if(c13 == 7){
                                index[0] = i+1;
                                index[1] = j+2;
                            }
                        }else if(c22 == 7){
                            if(c11 == 7){
                                index[0] = i-1;
                                index[1] = j+2;
                            }else if(c13 == 7){
                                index[0] = i+1;
                                index[1] = j+2;
                            }
                        }else if(c23 == 7){
                            if(c12 == 7){
                                index[0] = i;
                                index[1] = j+2;
                            }else if(c11 == 7){
                                index[0] = i-1;
                                index[1] = j+2;
                            }
                        }else{
                            if(c11 == 6 && c12 <= 6 && c13 <=6 ){
                                index[0] = i-1;
                                index[1] = j+2;
                            }else if(c12 == 6 && c11 <= 6 && c13 <=6 ){
                                index[0] = i;
                                index[1] = j+2;
                            }else if(c13 == 6 && c12 <= 6 && c11 <=6 ){
                                index[0] = i+1;
                                index[1] = j+2;
                            }else{
                                if(c11 == 5 && c12 <= 5 && c13 <=5 ){
                                    index[0] = i-1;
                                    index[1] = j+2;
                                }else if(c12 == 5 && c11 <= 5 && c13 <=5 ){
                                    index[0] = i;
                                    index[1] = j+2;
                                }else if(c13 == 5 && c12 <= 5 && c11 <=5 ){
                                    index[0] = i+1;
                                    index[1] = j+2;
                                }
                            }
                        }
                    }else if(dl1 == 6){
                        int c11 = (checkrange1(i+1,j-2))? mat1[i+1][j-2]+8-board.get_capacity(i+1,j-2) : 10;
                        int c12 = (checkrange1(i+2,j-2))? mat1[i+2][j-2]+8-board.get_capacity(i+2,j-2) : 10;
                        int c13 = (checkrange1(i+2,j-1))? mat1[i+2][j-1]+8-board.get_capacity(i+2,j-1) : 10;

                        int c21 = (checkrange1(i+1,j-2))? mat2[i+1][j-2]+8-board.get_capacity(i+1,j-2) : 10;
                        int c22 = (checkrange1(i+2,j-2))? mat2[i+2][j-2]+8-board.get_capacity(i+2,j-2) : 10;
                        int c23 = (checkrange1(i+2,j-1))? mat2[i+2][j-1]+8-board.get_capacity(i+2,j-1) : 10;
                        
                        if(c21 == 7){
                            if(c12 == 7){
                                index[0] = i+2;
                                index[1] = j-2;
                            }else if(c13 == 7){
                                index[0] = i+2;
                                index[1] = j-1;
                            }
                        }else if(c22 == 7){
                            if(c11 == 7){
                                index[0] = i+1;
                                index[1] = j-2;
                            }else if(c13 == 7){
                                index[0] = i+2;
                                index[1] = j-1;
                            }
                        }else if(c23 == 7){
                            if(c12 == 7){
                                index[0] = i+2;
                                index[1] = j-2;
                            }else if(c11 == 7){
                                index[0] = i+1;
                                index[1] = j-2;
                            }
                        }else{
                            if(c11 == 6 && c12 <= 6 && c13 <=6 ){
                                index[0] = i+1;
                                index[1] = j-2;
                            }else if(c12 == 6 && c11 <= 6 && c13 <=6 ){
                                index[0] = i+2;
                                index[1] = j-2;
                            }else if(c13 == 6 && c12 <= 6 && c11 <=6 ){
                                index[0] = i+2;
                                index[1] = j-1;
                            }else{
                                if(c11 == 5 && c12 <= 5 && c13 <=5 ){
                                    index[0] = i+1;
                                    index[1] = j-2;
                                }else if(c12 == 5 && c11 <= 5 && c13 <=5 ){
                                    index[0] = i+2;
                                    index[1] = j-2;
                                }else if(c13 == 5 && c12 <= 5 && c11 <=5 ){
                                    index[0] = i+2;
                                    index[1] = j-1;
                                }
                            }
                        }

                    }else if(d1 == 6){
                        int c11 = (checkrange1(i+2,j-1))? mat1[i+2][j-1]+8-board.get_capacity(i+2,j-1) : 10;
                        int c12 = (checkrange1(i+2,j))? mat1[i+2][j]+8-board.get_capacity(i+2,j) : 10;
                        int c13 = (checkrange1(i+2,j+1))? mat1[i+2][j+1]+8-board.get_capacity(i+2,j+1) : 10;

                        int c21 = (checkrange1(i+2,j-1))? mat2[i+2][j-1]+8-board.get_capacity(i+2,j-1) : 10;
                        int c22 = (checkrange1(i+2,j))? mat2[i+2][j]+8-board.get_capacity(i+2,j) : 10;
                        int c23 = (checkrange1(i+2,j+1))? mat2[i+2][j+1]+8-board.get_capacity(i+2,j+1) : 10;
                        
                        if(c21 == 7){
                            if(c12 == 7){
                                index[0] = i+2;
                                index[1] = j;
                            }else if(c13 == 7){
                                index[0] = i+2;
                                index[1] = j+1;
                            }
                        }else if(c22 == 7){
                            if(c11 == 7){
                                index[0] = i+2;
                                index[1] = j-1;
                            }else if(c13 == 7){
                                index[0] = i+2;
                                index[1] = j+1;
                            }
                        }else if(c23 == 7){
                            if(c12 == 7){
                                index[0] = i+2;
                                index[1] = j;
                            }else if(c11 == 7){
                                index[0] = i+2;
                                index[1] = j-1;
                            }
                        }else{
                            if(c11 == 6 && c12 <= 6 && c13 <=6 ){
                                index[0] = i+2;
                                index[1] = j-1;
                            }else if(c12 == 6 && c11 <= 6 && c13 <=6 ){
                                index[0] = i+2;
                                index[1] = j;
                            }else if(c13 == 6 && c12 <= 6 && c11 <=6 ){
                                index[0] = i+2;
                                index[1] = j+1;
                            }else{
                                if(c11 == 5 && c12 <= 5 && c13 <=5 ){
                                    index[0] = i+2;
                                    index[1] = j-1;
                                }else if(c12 == 5 && c11 <= 5 && c13 <=5 ){
                                    index[0] = i+2;
                                    index[1] = j;
                                }else if(c13 == 5 && c12 <= 5 && c11 <=5 ){
                                    index[0] = i+2;
                                    index[1] = j+1;
                                }
                            }
                        }
                    }else if(dr1 == 6){
                        int c11 = (checkrange1(i+2,j+1))? mat1[i+2][j+1]+8-board.get_capacity(i+2,j+1) : 10;
                        int c12 = (checkrange1(i+2,j+2))? mat1[i+2][j+2]+8-board.get_capacity(i+2,j+2) : 10;
                        int c13 = (checkrange1(i+1,j+2))? mat1[i+1][j+2]+8-board.get_capacity(i+1,j+2) : 10;

                        int c21 = (checkrange1(i+2,j+1))? mat2[i+2][j+1]+8-board.get_capacity(i+2,j+1) : 10;
                        int c22 = (checkrange1(i+2,j+2))? mat2[i+2][j+2]+8-board.get_capacity(i+2,j+2) : 10;
                        int c23 = (checkrange1(i+1,j+2))? mat2[i+1][j+2]+8-board.get_capacity(i+1,j+2) : 10;
                        
                        if(c21 == 7){
                            if(c12 == 7){
                                index[0] = i+2;
                                index[1] = j+2;
                            }else if(c13 == 7){
                                index[0] = i+1;
                                index[1] = j+2;
                            }
                        }else if(c22 == 7){
                            if(c11 == 7){
                                index[0] = i+2;
                                index[1] = j+1;
                            }else if(c13 == 7){
                                index[0] = i+1;
                                index[1] = j+2;
                            }
                        }else if(c23 == 7){
                            if(c12 == 7){
                                index[0] = i+2;
                                index[1] = j+2;
                            }else if(c11 == 7){
                                index[0] = i+2;
                                index[1] = j+1;
                            }
                        }else{
                            if(c11 == 6 && c12 <= 6 && c13 <=6 ){
                                index[0] = i+2;
                                index[1] = j+1;
                            }else if(c12 == 6 && c11 <= 6 && c13 <=6 ){
                                index[0] = i+2;
                                index[1] = j+2;
                            }else if(c13 == 6 && c12 <= 6 && c11 <=6 ){
                                index[0] = i+1;
                                index[1] = j+2;
                            }else{
                                if(c11 == 5 && c12 <= 5 && c13 <=5 ){
                                    index[0] = i+2;
                                    index[1] = j+1;
                                }else if(c12 == 5 && c11 <= 5 && c13 <=5 ){
                                    index[0] = i+2;
                                    index[1] = j+2;
                                }else if(c13 == 5 && c12 <= 5 && c11 <=5 ){
                                    index[0] = i+1;
                                    index[1] = j+2;
                                }
                            }
                        }
                    }


                    if(ul1 == 7){
                        index[0] = i-1;
                        index[1] = j-1;
                    }else if(u1 == 7){
                        index[0] = i-1;
                        index[1] = j;
                    }else if(ur1 == 7){
                        index[0] = i-1;
                        index[1] = j+1;
                    }else if(l1 == 7){
                        index[0] = i;
                        index[1] = j-1;
                    }else if(r1 == 7){
                        index[0] = i;
                        index[1] = j+1;
                    }else if(dl1 == 7){
                        index[0] = i+1;
                        index[1] = j-1;
                    }else if(d1 == 7){
                        index[0] = i+1;
                        index[1] = j;
                    }else if(dr1 == 7){
                        index[0] = i+1;
                        index[1] = j+1;
                    }
                    

                }
            }
        } 
    }
}