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

clock_t start, endtime ,start1, endtime1,start2, endtime2,start3, endtime3,start4, endtime4;
double cpu_time_used;

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
    //start1 = clock();
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
    /*endtime1 = clock();
    cpu_time_used = ((double) (endtime1 - start1)) / CLOCKS_PER_SEC;          //for calculate time spend
      printf("no_critial_Time = %f\n", cpu_time_used);*/
    return true;
}

int eval(Board s,int my_color){
    //start2 = clock();
    int result = 0;
    int cout_me = 0,cout_you = 0;

    /*for(int i = 0; i<5 ; i++){
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
    result = (cout_you>=cout_me)? cout_you-cout_me : cout_me-cout_you; */

      //cornor
    if(s.get_cell_color(0,0) == my_color){
        if(no_critial(s,0,0,my_color)){
            result+=3;
        }
    }
    if(s.get_cell_color(0,5) == my_color){
        if(no_critial(s,0,5,my_color)){
            result+=3;
        }
    }
    if(s.get_cell_color(4,0) == my_color){
        if(no_critial(s,4,0,my_color)){
            result+=3;
        }
    }
    if(s.get_cell_color(4,5) == my_color){
        if(no_critial(s,4,5,my_color)){
            result+=3;
        }
    }   //  edge
    for(int i = 1 ; i<5 ; i++){
        if(s.get_cell_color(0,i)==my_color){
            if(no_critial(s,0,i,my_color)){
                result+=2;
            }
        }
        if(s.get_cell_color(4,i)==my_color){
            if(no_critial(s,4,i,my_color)){
                result+=2;
            }
        }
    }
    for(int i = 1 ; i<4 ; i++){
        if(s.get_cell_color(i,0)==my_color){
            if(no_critial(s,i,0,my_color)){
                result+=2;
            }
        }
        if(s.get_cell_color(i,5)==my_color){
            if(no_critial(s,i,5,my_color)){
                result+=2;
            }
        }
    }
    for(int i = 0; i<5 ; i++){
        for(int j = 0 ; j<6 ; j++){
            if(s.get_cell_color(i,j) == my_color){  
                cout_me++;
                if(s.get_orbs_num(i,j) == s.get_capacity(i,j)-1){
                    if(no_critial(s,i,j,my_color))result+=2;                                            //if the cell is ours and is critial cell with no enemy critial cell nearby -> +2 
                    else result+=4;                                                                     //if the cell is ours and is critial cell with enemy critial cell nearby -> -4 
                }else{
                    if(!no_critial(s,i,j,my_color)) result-=1;
                    else result+=1;                                           
                }  
            }else if(s.get_cell_color(i,j) == 'w'){
                continue;
            }else{
                result-=1; 
                cout_you++;
            }
        }
    }
    if(cout_you == 0 && cout_me >0){
        return 2000;
    }else if(cout_me == 0 && cout_you >0){
        return -2000;
    } 

    /*endtime2 = clock();
    cpu_time_used = ((double) (endtime2 - start2)) / 1000.0;          //for calculate time spend
      printf("eval_Time = %.10f\n", cpu_time_used);*/

    return result;
}
//negascout
int negamax(Board s, Player me, Player you,int my_color, int you_color, int alpha, int beta, int depth){
    if(terminal_teat(s,my_color)){
        return utility(s,my_color);
    }
    if(depth == 0){
        return eval(s,my_color);
    }
    int b = beta;
    int result = -10000;
    for(int i = 0; i<5 ; i++){
        for(int j = 0 ; j<6 ; j++){
            if(s.get_cell_color(i,j) == my_color || s.get_cell_color(i,j) == 'w'){
                Board next_s = s;
                next_s.place_orb(i,j,&me);
                int result_next = -negamax(next_s, you, me, you_color, my_color, -1 * b, -1 * alpha, depth-1);
                if(alpha< result_next && result_next < beta)
                    result_next = -negamax(next_s, you, me, you_color, my_color, -1 * beta, -1 * alpha, depth-1);
                if (depth == DEPTH && result < result_next){
                    ans_i = i; ans_j = j;
                }
                result = max(result,result_next);
                if (result >= beta)
                    return result;
                alpha = max(alpha, result);
                b = alpha + 1;
            }
        }
    }

    return result;
}

void algorithm_A(Board board, Player player, int index[]){
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

    index[0] = ans_i;                                                                           //output
    index[1] = ans_j;
    //cout<<"i,j ="<< ans_i<<" "<< ans_j<<" "<< my_board.get_cell_color(ans_i,ans_j) <<endl;    //for debug



    endtime = clock();
    cpu_time_used = ((double) (endtime - start)) / CLOCKS_PER_SEC;          //for calculate time spend
      //printf("Time = %f\n", cpu_time_used);
    

    if( cpu_time_used>=1){
        printf("%f\n", cpu_time_used);
        board.print_current_board(index[0], index[1],0);            //to find out which case spent more than 1 sec 
    }
}


