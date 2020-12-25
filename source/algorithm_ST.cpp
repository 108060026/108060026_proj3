#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"
#include <time.h>

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/
int ans_i = 0,ans_j = 0;
int DEPTH = 4;

bool checkrange(int i, int j){
    if(i<0 || i> 4 || j<0 || j>5){
        return false;
    }
    return true;
}

bool terminal_teat(Board s, int my_color){
    bool result = true;
    //bool is_me = true,is_you = true;
    int cout_me = 0,cout_you = 0;
    for(int i = 0; i<5 ; i++){
        for(int j = 0 ; j<6 ; j++){
            if(s.get_cell_color(i,j) == 'w'){
                continue;
            }else if(s.get_cell_color(i,j) == my_color){
                //is_you = false;
                cout_me++;
            }else{
                //is_me = false;
                cout_you++;
            }
        }
    }
    if(cout_you == 0 && cout_me == 0){
        result = false;
    }else if(cout_you > 0 && cout_me > 0){
        result = false;
    }

    return result;
}

int utility(Board s,int my_color){
    int result = 0;
    int cout_me = 0,cout_you = 0;

    for(int i = 0; i<5 ; i++){
        for(int j = 0 ; j<6 ; j++){
            if(s.get_cell_color(i,j) == 'w'){
                continue;
            }else if(s.get_cell_color(i,j) == my_color){
                cout_me++;
            }else{
                cout_you++;
            }
        }
    }
    result = (cout_you>=cout_me)? cout_you-cout_me : cout_me-cout_you; 
    if(cout_you == 0 && cout_me >0){
        return 1000;
    }else if(cout_me == 0 && cout_you >0){
        return -1000;
    }

    return result;
}

int max(int result1,int result2){
    if(result1<=result2){
        return  result2;
    }else{
        return  result1;
    }
}

bool no_critial(Board s,int i,int j,int my_color){
    int ul = (checkrange(i-1,j-1))? s.get_orbs_num(i-1,j-1) +8-s.get_capacity(i-1,j-1) : 10;
    int u = (checkrange(i-1,j))? s.get_orbs_num(i-1,j-1)+8-s.get_capacity(i-1,j) : 10;
    int ur = (checkrange(i-1,j+1))? s.get_orbs_num(i-1,j-1)+8-s.get_capacity(i-1,j+1) : 10;
    int l = (checkrange(i,j-1))? s.get_orbs_num(i-1,j-1)+8-s.get_capacity(i,j-1) : 10;
    int r = (checkrange(i,j+1))? s.get_orbs_num(i-1,j-1)+8-s.get_capacity(i,j+1) : 10;
    int dl = (checkrange(i+1,j-1))? s.get_orbs_num(i-1,j-1)+8-s.get_capacity(i+1,j-1) : 10;
    int d = (checkrange(i+1,j))? s.get_orbs_num(i-1,j-1)+8-s.get_capacity(i+1,j) : 10;
    int dr = (checkrange(i+1,j+1))? s.get_orbs_num(i-1,j-1)+8-s.get_capacity(i+1,j+1) : 10;

    ul = (s.get_cell_color(i-1,j-1)!= my_color)? ul : 10;
    u = (s.get_cell_color(i-1,j)!= my_color)? u : 10;
    ur = (s.get_cell_color(i-1,j+1)!= my_color)? ur : 10;
    l = (s.get_cell_color(i,j-1)!= my_color)? l : 10;
    r = (s.get_cell_color(i,j+1)!= my_color)? r : 10;
    dl = (s.get_cell_color(i+1,j-1)!= my_color)? dl : 10;
    d = (s.get_cell_color(i+1,j)!= my_color)? d : 10;
    dr = (s.get_cell_color(i+1,j+1)!= my_color)? dr : 10;

    if((ul == 7 && ul != 10)||(u == 7 && u != 10)||(ur == 7 && ur != 10)||(l == 7 && l != 10)
        ||(d == 7 && d != 10)||(dr == 7 && dr != 10)||(dl == 7 && dl != 10)||(r == 7 && r != 10)){
        return false;
    }
    return true;
}

int eval(Board s,int my_color){
    int result = 0;
    int cout_me = 0,cout_you = 0;

    for(int i = 0; i<5 ; i++){
        for(int j = 0 ; j<6 ; j++){
            if(s.get_cell_color(i,j) == 'w'){
                continue;
            }else if(s.get_cell_color(i,j) == my_color){
                cout_me++;
            }else{
                cout_you++;
            }
        }
    }
    result = (cout_you>=cout_me)? cout_you-cout_me : cout_me-cout_you; 
    if(cout_you == 0 && cout_me >0){
        return 1000;
    }else if(cout_me == 0 && cout_you >0){
        return -1000;
    }   //cornor
    if(s.get_cell_color(0,0) == my_color && no_critial(s,0,0,my_color)){
        result+=3;
    }
    if(s.get_cell_color(0,5) == my_color && no_critial(s,0,0,my_color)){
        result+=3;
    }
    if(s.get_cell_color(4,0) == my_color && no_critial(s,0,0,my_color)){
        result+=3;
    }
    if(s.get_cell_color(4,5) == my_color && no_critial(s,0,0,my_color)){
        result+=3;
    }   //  edge
    for(int i = 1 ; i<5 ; i++){
        if(s.get_cell_color(0,i)==my_color&&no_critial(s,0,i,my_color)){
            result += 2;
        }
        if(s.get_cell_color(4,i)==my_color&&no_critial(s,4,i,my_color)){
            result += 2;
        }
    }
    for(int i = 1 ; i<4 ; i++){
        if(s.get_cell_color(0,i)==my_color&&no_critial(s,0,i,my_color)){
            result += 2;
        }
        if(s.get_cell_color(4,i)==my_color&&no_critial(s,4,i,my_color)){
            result += 2;
        }
    }
    for(int i = 0; i<5 ; i++){
        for(int j = 0 ; j<6 ; j++){
            if(s.get_cell_color(i,j) == my_color && s.get_orbs_num(i,j) == s.get_capacity(i,j)-1
                && no_critial(s,i,j,my_color)){
                result+=2;
            }
            if(s.get_cell_color(i,j) == my_color && s.get_orbs_num(i,j) == s.get_capacity(i,j)-1
                && !no_critial(s,i,j,my_color)){
                result-=2;
            }
            if(s.get_cell_color(i,j) == my_color && !no_critial(s,i,j,my_color)){
                result-=1;
            }
        }
    }

    return result;
}

int negamax(Board s, Player me, Player you,int my_color, int you_color, int alpha, int beta, int depth){
    if(terminal_teat(s,my_color)){
        return utility(s,my_color);
    }
    if(depth == 0){
        return eval(s,my_color);
    }
    int result = -10000;
    for(int i = 0; i<5 ; i++){
        for(int j = 0 ; j<6 ; j++){
            if(s.get_cell_color(i,j) == my_color || s.get_cell_color(i,j) == 'w'){
                Board next_s = s;
                next_s.place_orb(i,j,&me);
                int result_next = max(result,-negamax(next_s, you, me, you_color, my_color, -1 * beta, -1 * alpha, depth-1));
                if (depth == DEPTH && result != result_next){
                    ans_i = i; ans_j = j;
                }
                result = result_next;
                if (result >= beta)
                    return result;
                alpha = max(alpha, result);
            }
        }
    }

    return result;
}

void algorithm_A(Board board, Player player, int index[]){
    
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    //////your algorithm design///////////
    int row, col;
    int my_color = player.get_color();
    char enemy_color = 'b';
    Board my_board = board;
    if(player.get_color() == 'b'){
        enemy_color = 'r';
    }
    Player enemy(enemy_color);

    negamax(my_board, player, enemy, my_color, enemy_color,-10000,10000,DEPTH);
    index[0] = ans_i;
    index[1] = ans_j;
    //cout<<"i,j ="<< ans_i<<" "<< ans_j<<" "<< my_board.get_cell_color(ans_i,ans_j) <<endl;


/*   
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
    cout<< no_limit<<endl;
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
                    int ul1 = (checkrange(i-1,j-1))? mat1[i-1][j-1]+8-board.get_capacity(i-1,j-1) : 10;
                    int u1 = (checkrange(i-1,j))? mat1[i-1][j]+8-board.get_capacity(i-1,j) : 10;
                    int ur1 = (checkrange(i-1,j+1))? mat1[i-1][j+1]+8-board.get_capacity(i-1,j+1) : 10;
                    int l1 = (checkrange(i,j-1))? mat1[i][j-1]+8-board.get_capacity(i,j-1) : 10;
                    int r1 = (checkrange(i,j+1))? mat1[i][j+1]+8-board.get_capacity(i,j+1) : 10;
                    int dl1 = (checkrange(i+1,j-1))? mat1[i+1][j-1]+8-board.get_capacity(i+1,j-1) : 10;
                    int d1 = (checkrange(i+1,j))? mat1[i+1][j]+8-board.get_capacity(i+1,j) : 10;
                    int dr1 = (checkrange(i+1,j+1))? mat1[i+1][j+1]+8-board.get_capacity(i+1,j+1) : 10;

                    int ul2 = (checkrange(i-1,j-1))? mat2[i-1][j-1]+8-board.get_capacity(i-1,j-1) : 10;
                    int u2 = (checkrange(i-1,j))? mat2[i-1][j]+8-board.get_capacity(i-1,j) : 10;
                    int ur2 = (checkrange(i-1,j+1))? mat2[i-1][j+1]+8-board.get_capacity(i-1,j+1) : 10;
                    int l2 = (checkrange(i,j-1))? mat2[i][j-1]+8-board.get_capacity(i,j-1) : 10;
                    int r2 = (checkrange(i,j+1))? mat2[i][j+1]+8-board.get_capacity(i,j-1) : 10;
                    int dl2 = (checkrange(i+1,j-1))? mat2[i+1][j-1]+8-board.get_capacity(i+1,j-1) : 10;
                    int d2 = (checkrange(i+1,j))? mat2[i+1][j]+8-board.get_capacity(i+1,j) : 10;
                    int dr2 = (checkrange(i+1,j+1))? mat2[i+1][j+1]+8-board.get_capacity(i+1,j+1) : 10;

                    if(ul1 == 6){
                        int c11 = (checkrange(i-1,j-2))? mat1[i-1][j-2]+8-board.get_capacity(i-1,j-2) : 10;
                        int c12 = (checkrange(i-2,j-2))? mat1[i-2][j-2]+8-board.get_capacity(i-2,j-2) : 10;
                        int c13 = (checkrange(i-2,j-1))? mat1[i-2][j-1]+8-board.get_capacity(i-2,j-1) : 10;

                        int c21 = (checkrange(i-1,j-2))? mat2[i-1][j-2]+8-board.get_capacity(i-1,j-2) : 10;
                        int c22 = (checkrange(i-2,j-2))? mat2[i-2][j-2]+8-board.get_capacity(i-2,j-2) : 10;
                        int c23 = (checkrange(i-2,j-1))? mat2[i-2][j-1]+8-board.get_capacity(i-2,j-1) : 10;
                        
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
                        int c11 = (checkrange(i-2,j-1))? mat1[i-2][j-1]+8-board.get_capacity(i-2,j-1) : 10;
                        int c12 = (checkrange(i-2,j))? mat1[i-2][j]+8-board.get_capacity(i-2,j) : 10;
                        int c13 = (checkrange(i-2,j+1))? mat1[i-2][j+1]+8-board.get_capacity(i-2,j+1) : 10;

                        int c21 = (checkrange(i-2,j-1))? mat2[i-2][j-1]+8-board.get_capacity(i-2,j-1) : 10;
                        int c22 = (checkrange(i-2,j))? mat2[i-2][j]+8-board.get_capacity(i-2,j) : 10;
                        int c23 = (checkrange(i-2,j+1))? mat2[i-2][j+1]+8-board.get_capacity(i-2,j+1) : 10;
                        
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
                        int c11 = (checkrange(i-2,j+1))? mat1[i-2][j+1]+8-board.get_capacity(i-2,j+1) : 10;
                        int c12 = (checkrange(i-2,j+2))? mat1[i-2][j+2]+8-board.get_capacity(i-2,j+2) : 10;
                        int c13 = (checkrange(i-1,j+2))? mat1[i-1][j+2]+8-board.get_capacity(i-1,j+2) : 10;

                        int c21 = (checkrange(i-2,j+1))? mat2[i-2][j+1]+8-board.get_capacity(i-2,j+1) : 10;
                        int c22 = (checkrange(i-2,j+2))? mat2[i-2][j+2]+8-board.get_capacity(i-2,j+2) : 10;
                        int c23 = (checkrange(i-1,j+2))? mat2[i-1][j+2]+8-board.get_capacity(i-1,j+2) : 10;
                        
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
                        int c11 = (checkrange(i-1,j-2))? mat1[i-1][j-2]+8-board.get_capacity(i-1,j-2) : 10;
                        int c12 = (checkrange(i,j-2))? mat1[i][j-2]+8-board.get_capacity(i,j-2) : 10;
                        int c13 = (checkrange(i+1,j-2))? mat1[i+1][j-2]+8-board.get_capacity(i+1,j-2) : 10;

                        int c21 = (checkrange(i-1,j-2))? mat2[i-1][j-2]+8-board.get_capacity(i-1,j-2) : 10;
                        int c22 = (checkrange(i,j-2))? mat2[i][j-2]+8-board.get_capacity(i,j-2) : 10;
                        int c23 = (checkrange(i+1,j-2))? mat2[i+1][j-2]+8-board.get_capacity(i+1,j-2) : 10;
                        
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
                        int c11 = (checkrange(i-1,j+2))? mat1[i-1][j+2]+8-board.get_capacity(i-1,j+2) : 10;
                        int c12 = (checkrange(i,j+2))? mat1[i][j+2]+8-board.get_capacity(i,j+2) : 10;
                        int c13 = (checkrange(i+1,j+2))? mat1[i+1][j+2]+8-board.get_capacity(i+1,j+2) : 10;

                        int c21 = (checkrange(i-1,j+2))? mat2[i-1][j+2]+8-board.get_capacity(i-1,j+2) : 10;
                        int c22 = (checkrange(i,j+2))? mat2[i][j+2]+8-board.get_capacity(i,j+2) : 10;
                        int c23 = (checkrange(i+1,j+2))? mat2[i+1][j+2]+8-board.get_capacity(i+1,j+2) : 10;
                        
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
                        int c11 = (checkrange(i+1,j-2))? mat1[i+1][j-2]+8-board.get_capacity(i+1,j-2) : 10;
                        int c12 = (checkrange(i+2,j-2))? mat1[i+2][j-2]+8-board.get_capacity(i+2,j-2) : 10;
                        int c13 = (checkrange(i+2,j-1))? mat1[i+2][j-1]+8-board.get_capacity(i+2,j-1) : 10;

                        int c21 = (checkrange(i+1,j-2))? mat2[i+1][j-2]+8-board.get_capacity(i+1,j-2) : 10;
                        int c22 = (checkrange(i+2,j-2))? mat2[i+2][j-2]+8-board.get_capacity(i+2,j-2) : 10;
                        int c23 = (checkrange(i+2,j-1))? mat2[i+2][j-1]+8-board.get_capacity(i+2,j-1) : 10;
                        
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
                        int c11 = (checkrange(i+2,j-1))? mat1[i+2][j-1]+8-board.get_capacity(i+2,j-1) : 10;
                        int c12 = (checkrange(i+2,j))? mat1[i+2][j]+8-board.get_capacity(i+2,j) : 10;
                        int c13 = (checkrange(i+2,j+1))? mat1[i+2][j+1]+8-board.get_capacity(i+2,j+1) : 10;

                        int c21 = (checkrange(i+2,j-1))? mat2[i+2][j-1]+8-board.get_capacity(i+2,j-1) : 10;
                        int c22 = (checkrange(i+2,j))? mat2[i+2][j]+8-board.get_capacity(i+2,j) : 10;
                        int c23 = (checkrange(i+2,j+1))? mat2[i+2][j+1]+8-board.get_capacity(i+2,j+1) : 10;
                        
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
                        int c11 = (checkrange(i+2,j+1))? mat1[i+2][j+1]+8-board.get_capacity(i+2,j+1) : 10;
                        int c12 = (checkrange(i+2,j+2))? mat1[i+2][j+2]+8-board.get_capacity(i+2,j+2) : 10;
                        int c13 = (checkrange(i+1,j+2))? mat1[i+1][j+2]+8-board.get_capacity(i+1,j+2) : 10;

                        int c21 = (checkrange(i+2,j+1))? mat2[i+2][j+1]+8-board.get_capacity(i+2,j+1) : 10;
                        int c22 = (checkrange(i+2,j+2))? mat2[i+2][j+2]+8-board.get_capacity(i+2,j+2) : 10;
                        int c23 = (checkrange(i+1,j+2))? mat2[i+1][j+2]+8-board.get_capacity(i+1,j+2) : 10;
                        
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
  */
   

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      //printf("Time = %f\n", cpu_time_used);
    

    if( cpu_time_used>=1){
        printf("%f\n", cpu_time_used);
        board.print_current_board(index[0], index[1],0);
    }
}


