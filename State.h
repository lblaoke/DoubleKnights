#ifndef STATE_H
#define STATE_H

#include<cmath>
#include<cstring>
#include<string>
#include<cstdlib>

#define SIZE 10 //棋盘大小

const int move_x[]={-2,-1,1,2,2,1,-1,-2};
const int move_y[]={1,2,2,1,-1,-2,-2,-1};

class State {
private:
	void error(int number=0) { //棋盘状态错误处理
		if(number==1) printf("Error 1: Overlapping!\n");
		else if(number==2) printf("Error 2: Out of bound!\n");
		else if(number==3) printf("Error 3: Used to go!\n");
		exit(0);
	}
public:
	bool flag=false,board[SIZE][SIZE];
	int x_a,y_a,x_b,y_b,depth=0;
	double cost_estimated=0.0;
	State* child[8]; //子状态列表

	State(State* f,int xa,int ya,int xb,int yb) { //创建状态
		//棋子位置合法性判断
		if(xa==xb && ya==yb) error(1);
		if(xa<0 || xa>=SIZE || ya<0 || ya>=SIZE || xb<0 || xb>=SIZE || yb<0 || yb>=SIZE) error(2);

		//状态参数设置
		memset(child,0x0,sizeof(child));
		x_a=xa;
		y_a=ya;
		x_b=xb;
		y_b=yb;

		if(f) {
			if(f->board[x_a][y_a] && f->board[x_b][y_b]) error(3);
			memcpy(board,f->board,sizeof(board));
			flag=!f->flag;
			depth=f->depth+1;
			cost_estimated=f->cost_estimated/4.0;
		} else memset(board,0x0,sizeof(board));

		board[x_a][y_a]=board[x_b][y_b]=true;

		//计算当前状态的代价
		int hA=0,hB=0;
		for(register int i=0;i<8;i++) { //A周围的可行走法数
			int x=x_a+move_x[i],y=y_a+move_y[i];
			if(x>=0 && x<SIZE && y>=0 && y<SIZE && !board[x][y]) hA++;
		}
		for(register int i=0;i<8;i++) { //B周围的可行走法数
			int x=x_b+move_x[i],y=y_b+move_y[i];
			if(x>=0 && x<SIZE && y>=0 && y<SIZE && !board[x][y]) hB++;
		}
		
		if(!hA && hB) cost_estimated=-100000000.0;
		else if(hA && !hB) cost_estimated=100000000.0;
		else if(!hA && !hB && flag) cost_estimated=100000000.0;
		else if(!hA && !hB && !flag) cost_estimated=-100000000.0;
		else cost_estimated+=(hA-hB)*sqrt((SIZE<<1)-abs(x_a-x_b)-abs(y_a-y_b));
	}
	bool is_leaf() {
		bool bA=true,bB=true;
		for(register int i=0;i<8;i++) {
			int x=x_a+move_x[i],y=y_a+move_y[i];
			if(x>=0 && x<SIZE && y>=0 && y<SIZE && !board[x][y]) {
				bA=false;
				break;
			}
		}
		for(register int i=0;i<8;i++) {
			int x=x_b+move_x[i],y=y_b+move_y[i];
			if(x>=0 && x<SIZE && y>=0 && y<SIZE && !board[x][y]) {
				bB=false;
				break;
			}
		}
		return (bA || bB);
	}
	void show() { //打印当前棋盘
		for(register int i=0;i<SIZE;i++) {
			for(register int j=0;j<SIZE;j++) {
				if(i==x_a && j==y_a) printf("A ");
				else if(i==x_b && j==y_b) printf("B ");
				else if(board[i][j]) printf("@ ");
				else printf("+ ");
			}
			printf("\n");
		}
		if(flag) printf("This is the outcome of A's move.\n");
		else printf("This is the outcome of B's move.\n");
	}
};

#endif