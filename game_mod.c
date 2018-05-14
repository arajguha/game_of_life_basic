#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

//function to get count of live neighbours
int nbr_count(int** a, int ro, int col){
	int count = 0;
	if(a[ro][col-1] == 1) count++;
	if(a[ro][col+1] == 1) count++;
	if(a[ro-1][col] == 1) count++;
	if(a[ro+1][col] == 1) count++;
	if(a[ro-1][col-1] == 1) count++;
	if(a[ro+1][col-1] == 1) count++;
	if(a[ro+1][col+1] == 1) count++;
	if(a[ro-1][col+1] == 1) count++;
	
	return count;
}

//randomly population utility function
void random_init(int** arr, int ros, int cols){
	
	int i, rand_ro, rand_col, num;
	i = 0;
	
	while(i < (ros/2)*(cols/2)){
		rand_ro = rand()%ros;
		rand_col = rand()%cols;
		num = rand()%2;
		arr[rand_ro][rand_col] = num;
		i++;
	}
}

//initialises all cells to 0
//if flag is set to 1 --> randomly populate
//else populate with only 0's
void init(int** arr, int ros, int cols, int flag){
	int i, j;
	for(i=0; i<ros; i++){
		for(j=0; j<cols; j++){
			arr[i][j] = 0;
		}
	}
	if(flag)
		random_init(arr, ros, cols);
}



//creates a dynamically allocated 2d array
//and returns pointer to it ( implicitly calls function 'init' )
int** create(int ros, int cols, int flag){
	int i, j;
	int** arr = (int**)malloc(ros * sizeof(int*));
	for(i=0; i<ros; i++){
		arr[i] = (int*)malloc(cols * sizeof(int));
	}
	init(arr, ros, cols, flag);
	return arr;
}

//utility function to print the 2d matrix ( m * n )
//1 is printed as "#" ... 0 as " "
//for display the boundary rows and columns are excluded
//they are also excluded from participation in the simualtion

void print(int** board, int ros, int cols){
	int i, j;
	printf("\n\n");
	for(i = 1; i < ros ; i++){
		printf("\t\t");
		for(j = 1; j < cols; j++){
			if(board[i][j]) 
				printf("#");
			else 
				printf(" ");
		}
		printf("\n");
	}
}

int is_dead(int** a, int ro, int col){
	if(a[ro][col] == 0) return 1;
	else return 0;
}

//apply main rule to a cell of current_gen

void apply_rule(int** current_gen, int** next_gen, int ro, int col){
	int count = nbr_count(current_gen, ro, col);
	
	if(count <=1 || count >= 4)			//death due to overcrowding or underpopulation
		next_gen[ro][col] = 0;
	
	else if(count == 3)		//if dead then make alive in next_gen
		next_gen[ro][col] = 1;
		
	else if(count == 2){			//2 neighbours --> state will remain same in next_gen
		next_gen[ro][col] = current_gen[ro][col];
	}
}

//iterate over the entire current_gen and
//apply the rules to each cell
//and update the next_gen accordingly
//to obtain the next_gen

void iterate(int** current_gen, int** next_gen, int ros, int cols){
	int i, j;
	for(i=1; i<ros-1; i++){
		for(j=1; j<cols-1; j++){
			apply_rule(current_gen, next_gen, i, j);
		}
	}
}


//Driver function
void main(int argc, char* argv[]){
	srand(time(NULL));
	
	if(argc != 3){
		printf("\n[+]Usage : [FILE_NAME] [ROWS] [COLS]\n");
		exit(1);
	}
	int ros = atoi(argv[1]);
	int cols = atoi(argv[2]);
	int p_factor = 0.5;
	
	int** current_gen = create(ros, cols, 1);	//current gen
	int** next_gen = create(ros, cols, 0);	//next_gen
	
	
	//setups
	int mid_ro = floor(ros * p_factor);
	int mid_col = floor(cols * p_factor);
	
	//setup for blinker
	/*current_gen[mid_ro][mid_col] = 1;
	current_gen[mid_ro][mid_col-1] = 1;
	current_gen[mid_ro][mid_col+1] = 1;
	*/
	
	
	//setup for glider
	/*
	current_gen[mid_ro][mid_col] = 1;
	current_gen[mid_ro][mid_col-1] = 1;
	current_gen[mid_ro][mid_col+1] = 1;
	current_gen[mid_ro-2][mid_col] = 1;
	current_gen[mid_ro-1][mid_col+1] = 1;
	*/
	
	//display intial structure
	print(current_gen, ros, cols);
		
	int val;	//just to stall temporarily
	scanf("%d", &val);
	
	int** tmp;	//temporary pointer to hold grid
	
	while(1){
		system("cls"); //clears screen
		iterate(current_gen, next_gen, ros, cols);	//iterating over the board and applying rule
		
		//display 
		print(next_gen, ros, cols);
		
		//updates done
		tmp = current_gen;
		current_gen = next_gen;
		next_gen = create(ros, cols, 0);
		free(tmp);	//deallocate the tmp
		
		//sleep(1);	//sleeps for one second
	}
}



