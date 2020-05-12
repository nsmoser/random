#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void print_board(int *coord_start);							//board printing function definition
void get_input(int *board,int *player);						//handles user input
int victory(int *board);									//checks victory conditions
void win(int victory);										//announces winner or draw

int main(){
	srand(time(0));											//seeds random player selection
	int coord[9];											//create board variable and pointer						
	int *board=&coord[0];									
	int player=0;											//create player variable and pointer
	int *player_ptr=&player;
	for(int i=0;i<9;i++){									//fill board with "empty" spaces
		coord[i]=0;
	}
	print_board(board);										//displays preliminary board
	while(!victory(board)){									//while there is no winner
		get_input(board,player_ptr);						//get the user input
		print_board(board);									//reprint board
	}
	win(victory(board));									//announces winner or draw
	return 0;
}

void win(int victory){										//announces winner or draw
	if(victory==1){printf("\nPlayer 1 wins!\n");}			//if statements based on value
	else if(victory==2){printf("\nPlayer 2 wins!\n");}		//handed off by victory function
	else if(victory==3){printf("\nDraw!\n");}
	else{printf("\nUh oh, something went wrong\n");}		//this shouldnt happen
}

int victory(int *board){									//victory conditions
	int i=0,draw_count=0;
	while(i<9){												//row check
		if((*(board+i)==1)&&(*(board+i+1)==1)&&(*(board+i+2)==1)){
			return 1;
		}
		else if((*(board+i)==2)&&(*(board+i+1)==2)&&(*(board+i+2)==2)){
			return 2;
		}
		i+=3;
	}
	i=0;
	while(i<3){												//column check
		if((*(board+i)==1)&&(*(board+3+i)==1)&&(*(board+6+i)==1)){
			return 1;
		}
		else if((*(board+i)==2)&&(*(board+3+i)==2)&&(*(board+6+i)==2)){
			return 2;
		}
		i++;
	}
	if((*(board)==1)&&(*(board+4)==1)&&(*(board+8)==1)){	//diagonal check
		return 1;
	}
	if((*(board+2)==1)&&(*(board+4)==1)&&(*(board+6)==1)){
		return 1;
	}
	if((*(board)==2)&&(*(board+4)==2)&&(*(board+8)==2)){
		return 2;
	}
	if((*(board+2)==2)&&(*(board+4)==2)&&(*(board+6)==2)){
		return 2;
	}
	for(i=0;i<9;i++){										//draw check
		if(*(board+i)==0){draw_count++;}
	}
	if(draw_count==0){return 3;}
	return 0;
}

void get_input(int *board, int *player){
	int row=0, position=0; char column;
	if(*player==0){											//picks a player if none are
		*player=(rand()%2)+1;								//assigned this turn
	}
	if(*player==1){
		printf("Player 1: Pick a column and a row\nexample: (A2 or B3)\n");
		scanf(" %c%d",&column,&row);						//determines position based on input
		if(row==1){position=column-65;}						//position value is column ascii 
		else if(row==2){position=column-62;}				//minus row value
		else if(row==3){position=column-59;}				//ensures correct row value
		else{position=69;}									//error value, picked "arbitrarily"
		if(column==65||column==66||column==67){}			//ensures correct column input
		else{position=69;}									//error value, picked bc its funny
		if(*(board+position)==0){}							//check if position is occupied
		else{position=69;printf("That position is already taken\n");}
		if(position==69){printf("Incorrect move. Lose 1 turn");}
		else{
			*(board+position)=1;							//changes board position to 
		}													//player 1 value
		*player=2;											//switches to other player
	}
	else if(*player==2){									//reuses player 1 code
		printf("Player 2: Pick a column and a row\nexample: (A2 or B3)\n");
		scanf(" %c%d",&column,&row);						
    	if(row==1){position=column-65;}
		else if(row==2){position=column-62;}
		else if(row==3){position=column-59;}
		else{position=69;}
		if(column==65||column==66||column==67){}
		else{position=69;}
		if(*(board+position)==0){}
		else{position=69;printf("That position is already taken\n");}
		if(position==69){printf("Incorrect move. Lose 1 turn");}
		else{
			*(board+position)=2;
		}
		*player=1;
	}
}

void print_board(int *coord_start){
	char board[9];											//creates an array of characters
	for(int i=0;i<9;i++){									//makes array depending on values
		if(*(coord_start+i)==0){							//given by the board array, which
			board[i]='-';									//tells if a spot is empty or 
		}													//occupied by a current player
		else if(*(coord_start+i)==1){
			board[i]='O';
		}
		else if(*(coord_start+i)==2){
			board[i]='X';
		}
	}
	printf("\n\n\n\t A | B | C \n\n\t");
	
	for (int i=0;i<9;i++){									//prints board to console
		if((i+1)%3==0){										//has special output for ends of
			if(i!=8){										//rows and end character (column c)
				printf(" %c    %d\n\t---+---+---  ---\n\t",board[i],i/2);
			}
			else{
				printf(" %c    3",board[i]);
			}
		}
		else{												//instructions if not an end
			printf(" %c |",board[i]);						//character (column a and b)
		}
	}
	printf("\n\n\n");
}