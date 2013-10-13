#define _POSIX_C_SOURCE 999
#include <features.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


typedef enum BLOCK_NONE{
	NONE=0
}BLOCK_NONE;

typedef enum BLOCK_TYPE{
	CENTER=1,EDGE,ANGLE
}BLOCK_TYPE;

typedef enum BLOCK_COLOR{
	BLUE=1,GREEN,RED,ORANGE,WHITE,YELLOW
}BLOCK_COLOR;

typedef enum BLOCK_DIRECTION{
	U=1,D,L,R,B,F,MAX_D
}BLOCK_DIRECTION;

typedef enum BLOCK_POSITION{
	MC=0,UC,UL,UR,UF,UB,ULF,ULB,URF,URB,ML,MR,MF,MB,MLF,MLB,MRF,MRB,DC,DL,DR,DF,DB,DLF,DLB,DRF,DRB
}BLOCK_POSITION;

typedef struct Block{
	BLOCK_TYPE type;
	BLOCK_COLOR color[3];
	BLOCK_DIRECTION color_direction[3];
}Block;

typedef struct Slot{
	BLOCK_POSITION position;
	Block* block;
}Slot;

char getActionChar(int keynum);
void chaos(Slot cube[3][3][3]);
void printCube(Slot cube[3][3][3]);
void rotate(char key,int ccw,Slot cube[3][3][3]);
void rotateBlock(char key,int ccw,Block* block);
char getDirectionChar(BLOCK_DIRECTION direction);
void getColorChar(char color_name[100],BLOCK_COLOR color);
void getFace(int color[3][3],int color_direction,Slot cube[3][3][3]);
void main(void){
	Slot cube[3][3][3]={
		{
			 {{ULB,NULL},{UL,NULL},{ULF,NULL}}
			,{{UB,NULL},{UC,NULL},{UF,NULL}}
			,{{URB,NULL},{UR,NULL},{URF,NULL}}
		}
		,{
			 {{MLB,NULL},{ML,NULL},{MLF,NULL}}
			,{{MB,NULL},{MC,NULL},{MF,NULL}}
			,{{MRB,NULL},{MR,NULL},{MRF,NULL}}
		}
		,{
			 {{DLB,NULL},{DL,NULL},{DLF,NULL}}
			,{{DB,NULL},{DC,NULL},{DF,NULL}}
			,{{DRB,NULL},{DR,NULL},{DRF,NULL}}
		}
	};

	Block b[3][3][3]={
		{
			{
				{
					ANGLE
					,{BLUE,RED,WHITE}
					,{U,L,B}
				}
				,{
					EDGE
					,{BLUE,RED,NONE}
					,{U,L,NONE}
				}
				,{
					ANGLE
					,{BLUE,RED,YELLOW}
					,{U,L,F}
				}
			}
			,{
				{
					EDGE
					,{BLUE,WHITE,NONE}
					,{U,B,NONE}
				}
				,{
					CENTER
					,{BLUE,NONE,NONE}
					,{U,NONE,NONE}
				}
				,{
					EDGE
					,{BLUE,YELLOW,NONE}
					,{U,F,NONE}
				}
			}
			,{
				{
					ANGLE
					,{BLUE,ORANGE,WHITE}
					,{U,R,B}
				}
				,{
					EDGE
					,{BLUE,ORANGE,NONE}
					,{U,R,NONE}
				}
				,{
					ANGLE
					,{BLUE,ORANGE,YELLOW}
					,{U,R,F}
				}
			}
		}
		,{
			{
				{
					EDGE
					,{RED,WHITE,NONE}
					,{L,B,NONE}
				}
				,{
					CENTER
					,{RED,NONE,NONE}
					,{L,NONE,NONE}
				}
				,{
					EDGE
					,{RED,YELLOW,NONE}
					,{L,F,NONE}
				}
			}
			,{
				{
					CENTER
					,{WHITE,NONE,NONE}
					,{B,NONE,NONE}
				}
				,{
					NONE
					,{NONE,NONE,NONE}
					,{NONE,NONE,NONE}
				}
				,{
					CENTER
					,{YELLOW,NONE,NONE}
					,{F,NONE,NONE}
				}
			}
			,{
				{
					EDGE
					,{ORANGE,WHITE,NONE}
					,{R,B,NONE}
				}
				,{
					CENTER
					,{ORANGE,NONE,NONE}
					,{R,NONE,NONE}
				}
				,{
					EDGE
					,{ORANGE,YELLOW,NONE}
					,{R,F,NONE}
				}
			}
		}
		,{

			{
				{
					ANGLE
					,{GREEN,RED,WHITE}
					,{D,L,B}
				}
				,{
					EDGE
					,{GREEN,RED,NONE}
					,{D,L,NONE}
				}
				,{
					ANGLE
					,{GREEN,RED,YELLOW}
					,{D,L,F}
				}
			}
			,{
				{
					EDGE
					,{GREEN,WHITE,NONE}
					,{D,B,NONE}
				}
				,{
					CENTER
					,{GREEN,NONE,NONE}
					,{D,NONE,NONE}
				}
				,{
					EDGE
					,{GREEN,YELLOW,NONE}
					,{D,F,NONE}
				}
			}
			,{
				{
					ANGLE
					,{GREEN,ORANGE,WHITE}
					,{D,R,B}
				}
				,{
					EDGE
					,{GREEN,ORANGE,NONE}
					,{D,R,NONE}
				}
				,{
					ANGLE
					,{GREEN,ORANGE,YELLOW}
					,{D,R,F}
				}
			}
		}
	};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				cube[i][j][k].block=&b[i][j][k];
			}
		}		
	}

	// printCube(cube);

	chaos(cube);

	printCube(cube);

	char* text="rubik's cube";
	printf("%s\n",text);

}
void chaos(Slot cube[3][3][3]){
	struct timeval tv;
	gettimeofday(&tv,0);
	srand(tv.tv_usec);
	int r;
	int key;
	int cww;
	for(int i=0;i<50;i++){
		r=rand();
		key=getActionChar(r%6);
		r=rand();
		cww=r%2;
		rotate(key,cww,cube);
		printf("key=%c:cww=%d\n",key,cww); 
	};
}
char getActionChar(int keynum){
	char ret='?';
	switch(keynum){
		case 0:
			ret='U';
			break;
		case 1:
			ret='D';
			break;
		case 2:
			ret='L';
			break;
		case 3:
			ret='R';
			break;
		case 4:
			ret='F';
			break;
		case 5:
			ret='B';
			break;
	}
	return ret;
}
void printCube(Slot cube[3][3][3]){
	int c=U;
	for(c=U;c<MAX_D;c++){
		int colors[3][3];
		printf("face[%C]\n",getDirectionChar(c));
		getFace(colors,c,cube);
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				char color_name[100]="aaaaa";
				getColorChar(color_name,colors[i][j]);
				printf("[%d][%d]=%s\n",i,j,color_name);
			}
		}
		printf("\n");
	}
}
void getColorChar(char color_name[100],BLOCK_COLOR color){
	strcpy(color_name,"Unknow");
	switch(color){
		case BLUE:
			strcpy(color_name,"Blue");
			break;
		case GREEN:
			strcpy(color_name,"Green");
			break;
		case RED:
			strcpy(color_name,"Red");
			break;
		case ORANGE:
			strcpy(color_name,"Orange");
			break;
		case WHITE:
			strcpy(color_name,"White");
			break;
		case YELLOW:
			strcpy(color_name,"Yellow");
			break;
	}
}
char getDirectionChar(BLOCK_DIRECTION direction){
	char ret='?';
	switch(direction){
		case U:
			ret='U';
			break;
		case D:
			ret='D';
			break;
		case L:
			ret='L';
			break;
		case R:
			ret='R';
			break;
		case F:
			ret='F';
			break;
		case B:
			ret='B';
			break;
	}
	return ret;
}

void getFace(int color[3][3],int direction,Slot cube[3][3][3]){
	int i_s=0,j_s=0,k_s=0;
	int i_e=3,j_e=3,k_e=3;
	int i_lock=0,j_lock=0,k_lock=0;
	if(direction==U || direction==D){
		i_s=direction==U?0:2;
		i_e=i_s+1;
		i_lock=1;
	}else if(direction==L || direction==R){
		j_s=direction==L?0:2;
		j_e=j_s+1;
		j_lock=1;
	}else if(direction==B || direction==F){
		k_s=direction==B?0:2;
		k_e=k_s+1;
		k_lock=1;
	}

	for(int i=i_s;i<i_e;i++){
		for(int j=j_s;j<j_e;j++){
			for(int k=k_s;k<k_e;k++){
				for(int l=0;l<3;l++){
					if(cube[i][j][k].block->color_direction[l]==direction){
						int x,y;
						if(i_lock){
							x=j;y=k;
						}else if(j_lock){
							x=i;y=k;
						}else if(k_lock){
							x=i;y=j;
						}
						color[x][y]=cube[i][j][k].block->color[l];
						break;
					}
				}
			}
		}		
	}
}
void rotateBlock(char key,int ccw,Block* block){
	switch(key){
		case 'D':
		case 'd':
			key='U';
			ccw=!ccw;
			break;
		case 'R':
		case 'r':
			key='L';
			ccw=!ccw;
			break;
		case 'F':
		case 'f':
			key='B';
			ccw=!ccw;
			break;

	}	
	switch(key){
		case 'U':
		case 'u':
			if(!ccw){
				for(int i=0;i<3;i++){
					switch(block->color_direction[i]){
						case L:
							block->color_direction[i]=B;
							break;
						case R:
							block->color_direction[i]=F;
							break;
						case B:
							block->color_direction[i]=R;
							break;
						case F:
							block->color_direction[i]=L;
							break;
					}
				}
			}else{
				for(int i=0;i<3;i++){
					switch(block->color_direction[i]){
						case L:
							block->color_direction[i]=F;
							break;
						case R:
							block->color_direction[i]=B;
							break;
						case B:
							block->color_direction[i]=L;
							break;
						case F:
							block->color_direction[i]=R;
							break;
					}
				}
			}
			break;
		case 'L':
		case 'l':
			if(!ccw){
				for(int i=0;i<3;i++){
					switch(block->color_direction[i]){
						case U:
							block->color_direction[i]=F;
							break;
						case D:
							block->color_direction[i]=B;
							break;
						case B:
							block->color_direction[i]=U;
							break;
						case F:
							block->color_direction[i]=D;
							break;
					}
				}
			}else{
				for(int i=0;i<3;i++){
					switch(block->color_direction[i]){
						case U:
							block->color_direction[i]=B;
							break;
						case D:
							block->color_direction[i]=F;
							break;
						case B:
							block->color_direction[i]=D;
							break;
						case F:
							block->color_direction[i]=U;
							break;
					}
				}
			}
			break;
		case 'B':
		case 'b':
			if(!ccw){
				for(int i=0;i<3;i++){
					switch(block->color_direction[i]){
						case U:
							block->color_direction[i]=L;
							break;
						case D:
							block->color_direction[i]=R;
							break;
						case L:
							block->color_direction[i]=D;
							break;
						case R:
							block->color_direction[i]=U;
							break;
					}
				}
			}else{
				for(int i=0;i<3;i++){
					switch(block->color_direction[i]){
						case U:
							block->color_direction[i]=R;
							break;
						case D:
							block->color_direction[i]=L;
							break;
						case L:
							block->color_direction[i]=U;
							break;
						case R:
							block->color_direction[i]=D;
							break;
					}
				}
			}
			break;
	}
}
void rotate(char key,int ccw,Slot cube[3][3][3]){
	Block* tmp_B;
	int _ccw;
	Slot* rotate_slot[8];
	int fix;
	switch(key){
		case 'U':
		case 'u':
		case 'D':
		case 'd':
			fix=(key=='D'||key=='d')?2:0;
			_ccw=(key=='D'||key=='d')?!ccw:ccw;
			rotate_slot[0]=&cube[fix][0][0];
			rotate_slot[1]=&cube[fix][1][0];
			rotate_slot[2]=&cube[fix][2][0];
			rotate_slot[3]=&cube[fix][2][1];
			rotate_slot[4]=&cube[fix][2][2];
			rotate_slot[5]=&cube[fix][1][2];
			rotate_slot[6]=&cube[fix][0][2];
			rotate_slot[7]=&cube[fix][0][1];
			break;
		case 'L':
		case 'l':
		case 'R':
		case 'r':
			fix=(key=='R'||key=='r')?2:0;
			_ccw=(key=='R'||key=='r')?!ccw:ccw;
			rotate_slot[0]=&cube[0][fix][0];
			rotate_slot[1]=&cube[0][fix][1];
			rotate_slot[2]=&cube[0][fix][2];
			rotate_slot[3]=&cube[1][fix][2];
			rotate_slot[4]=&cube[2][fix][2];
			rotate_slot[5]=&cube[2][fix][1];
			rotate_slot[6]=&cube[2][fix][0];
			rotate_slot[7]=&cube[1][fix][0];
			break;
		case 'B':
		case 'b':
		case 'F':
		case 'f':
			fix=(key=='F'||key=='f')?2:0;
			_ccw=(key=='F'||key=='f')?!ccw:ccw;
			rotate_slot[0]=&cube[0][2][fix];
			rotate_slot[1]=&cube[0][1][fix];
			rotate_slot[2]=&cube[0][0][fix];
			rotate_slot[3]=&cube[1][0][fix];
			rotate_slot[4]=&cube[2][0][fix];
			rotate_slot[5]=&cube[2][1][fix];
			rotate_slot[6]=&cube[2][2][fix];
			rotate_slot[7]=&cube[1][2][fix];
			break;
	}

	if(_ccw){
		tmp_B=rotate_slot[0]->block;

		rotate_slot[0]->block=rotate_slot[2]->block;
		rotateBlock(key,ccw,rotate_slot[0]->block);

		rotate_slot[2]->block=rotate_slot[4]->block;
		rotateBlock(key,ccw,rotate_slot[2]->block);

		rotate_slot[4]->block=rotate_slot[6]->block;
		rotateBlock(key,ccw,rotate_slot[4]->block);

		rotate_slot[6]->block=tmp_B;
		rotateBlock(key,ccw,rotate_slot[6]->block);

		tmp_B=rotate_slot[1]->block;

		rotate_slot[1]->block=rotate_slot[3]->block;
		rotateBlock(key,ccw,rotate_slot[1]->block);

		rotate_slot[3]->block=rotate_slot[5]->block;
		rotateBlock(key,ccw,rotate_slot[3]->block);

		rotate_slot[5]->block=rotate_slot[7]->block;
		rotateBlock(key,ccw,rotate_slot[5]->block);

		rotate_slot[7]->block=tmp_B;
		rotateBlock(key,ccw,rotate_slot[7]->block);
	}else{
		tmp_B=rotate_slot[0]->block;

		rotate_slot[0]->block=rotate_slot[6]->block;
		rotateBlock(key,ccw,rotate_slot[0]->block);

		rotate_slot[6]->block=rotate_slot[4]->block;
		rotateBlock(key,ccw,rotate_slot[6]->block);

		rotate_slot[4]->block=rotate_slot[2]->block;
		rotateBlock(key,ccw,rotate_slot[4]->block);

		rotate_slot[2]->block=tmp_B;
		rotateBlock(key,ccw,rotate_slot[2]->block);

		tmp_B=rotate_slot[1]->block;

		rotate_slot[1]->block=rotate_slot[7]->block;
		rotateBlock(key,ccw,rotate_slot[1]->block);

		rotate_slot[7]->block=rotate_slot[5]->block;
		rotateBlock(key,ccw,rotate_slot[7]->block);

		rotate_slot[5]->block=rotate_slot[3]->block;
		rotateBlock(key,ccw,rotate_slot[5]->block);

		rotate_slot[3]->block=tmp_B;
		rotateBlock(key,ccw,rotate_slot[3]->block);

	}
}
