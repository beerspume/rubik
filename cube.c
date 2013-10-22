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

void getPositionChar(char position_name[5],BLOCK_POSITION position);
void findEdgeBlock(Slot* ret[4],BLOCK_COLOR color,Slot cube[3][3][3]);
BLOCK_COLOR getDirectionColor(BLOCK_DIRECTION direction,Slot cube[3][3][3]);
void restore(Slot cube[3][3][3]);
char getActionChar(int keynum);
void chaos(Slot cube[3][3][3]);
void printCube(Slot cube[3][3][3]);
void rotate(char key,int ccw,Slot cube[3][3][3]);
void rotateBlock(char key,int ccw,Block* block);
char getDirectionChar(BLOCK_DIRECTION direction);
void getColorChar(char color_name[10],BLOCK_COLOR color);
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


	printf("----------↓↓↓ initialized cube ↓↓↓----------\n");
	// printCube(cube);//init cube status

	chaos(cube);//chaos cube
	printf("----------↓↓↓ chaotic cube ↓↓↓----------\n");
	printCube(cube);//print chaotic cube

	restore(cube);//restore cube
	printf("----------↓↓↓ restored cube ↓↓↓----------\n");
	// printCube(cube);//print restored cube

	printf("----------☆☆☆ rubik's cube ☆☆☆----------\n");

}
void restore(Slot cube[3][3][3]){
	BLOCK_COLOR c1=getDirectionColor(U,cube);
	Slot* edges[4];
	findEdgeBlock(edges,c1,cube);
	char position_name[5];
	for(int i=0;i<4;i++){
		getPositionChar(position_name,edges[i]->position);
		printf("%s\n",position_name);
	}

	char color_name[10];
	getColorChar(color_name,c1);
	printf("%s\n",color_name);
}


void findEdgeBlock(Slot* ret[4],BLOCK_COLOR color,Slot cube[3][3][3]){
	int count=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				if(cube[i][j][k].block->type==EDGE){
					for(int l=0;l<3;l++){
						if(cube[i][j][k].block->color[l]==color){
							ret[count]=&cube[i][j][k];
							count++;
							break;
						}
					}
				}
			}
		}
	}
}
BLOCK_COLOR getDirectionColor(BLOCK_DIRECTION direction,Slot cube[3][3][3]){
	BLOCK_COLOR ret=NONE;
	switch(direction){
		case U:
			ret=cube[0][1][1].block->color[0];
			break;
		case D:
			ret=cube[2][1][1].block->color[0];
			break;
		case L:
			ret=cube[1][0][1].block->color[0];
			break;
		case R:
			ret=cube[1][2][1].block->color[0];
			break;
		case B:
			ret=cube[1][1][0].block->color[0];
			break;
		case F:
			ret=cube[1][1][2].block->color[0];
			break;
	}
	return ret;
}
void chaos(Slot cube[3][3][3]){
	struct timeval tv;
	gettimeofday(&tv,0);
	srand(tv.tv_usec);
	int r;
	int key;
	int cww;
	int lastkey=-1;
	for(int i=0;i<50;i++){
		r=rand();
		key=getActionChar(r%6);
		r=rand();
		cww=r%2;
		if(lastkey==key){
			i--;
			continue;
		}
		rotate(key,cww,cube);
		lastkey=key;
		// printf("key=%c:cww=%d\n",key,cww); 
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
				char color_name[10];
				getColorChar(color_name,colors[i][j]);
				printf("Slot[%d][%d]=%s\n",i,j,color_name);
			}
		}
		printf("\n");
	}
}
void getPositionChar(char position_name[5],BLOCK_POSITION position){
	strcpy(position_name,"Unknow");
	switch(position){
		case MC:
			strcpy(position_name,"MC");
			break;
		case UC:
			strcpy(position_name,"UC");
			break;
		case UL:
			strcpy(position_name,"UL");
			break;
		case UR:
			strcpy(position_name,"UR");
			break;
		case UF:
			strcpy(position_name,"UF");
			break;
		case UB:
			strcpy(position_name,"UB");
			break;
		case ULF:
			strcpy(position_name,"ULF");
			break;
		case ULB:
			strcpy(position_name,"ULB");
			break;
		case URF:
			strcpy(position_name,"URF");
			break;
		case URB:
			strcpy(position_name,"URB");
			break;
		case ML:
			strcpy(position_name,"ML");
			break;
		case MR:
			strcpy(position_name,"MR");
			break;
		case MF:
			strcpy(position_name,"MF");
			break;
		case MB:
			strcpy(position_name,"MB");
			break;
		case MLF:
			strcpy(position_name,"MLF");
			break;
		case MLB:
			strcpy(position_name,"MLB");
			break;
		case MRF:
			strcpy(position_name,"MRF");
			break;
		case MRB:
			strcpy(position_name,"MRB");
			break;
		case DC:
			strcpy(position_name,"DC");
			break;
		case DL:
			strcpy(position_name,"DL");
			break;
		case DR:
			strcpy(position_name,"DR");
			break;
		case DF:
			strcpy(position_name,"DF");
			break;
		case DB:
			strcpy(position_name,"DB");
			break;
		case DLF:
			strcpy(position_name,"DLF");
			break;
		case DLB:
			strcpy(position_name,"DLB");
			break;
		case DRF:
			strcpy(position_name,"DRF");
			break;
		case DRB:
			strcpy(position_name,"DRB");
			break;
	}

}
void getColorChar(char color_name[10],BLOCK_COLOR color){
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
