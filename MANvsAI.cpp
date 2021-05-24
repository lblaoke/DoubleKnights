#include<ctime>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<iostream>
#include"State.h"
#include"Search.h"

using namespace std;

int main() {
	srand(time(0));
	int xa=rand()%SIZE,ya=rand()%SIZE,xb=rand()%SIZE,yb=rand()%SIZE;
	while(xa==xb && ya==yb) {
		xa=rand()%SIZE;
		ya=rand()%SIZE;
		xb=rand()%SIZE;
		yb=rand()%SIZE;
	}
	State S0(NULL,xa,ya,xb,yb); //初始状态
	S0.show();
	State* c=&S0; //当前状态
	while(true) {
		int d;
		scanf("%d",&d);
		int x=c->x_a+move_x[d],y=c->y_a+move_y[d];

		if(!c->child[d]) c->child[d]=new State(c,x,y,c->x_b,c->y_b);
		c=c->child[d]; //根据玩家的选择更新当前状态
		c->show();
		if(c->is_leaf()) break;

		int depth=c->depth; //记录当前状态树深度

		State* choice=NULL;
		double min_cost=100000000.0;
		for(register int i=0;i<8;i++) {
			x=c->x_b+move_x[i];
			y=c->y_b+move_y[i];
			if(x<0 || x>=SIZE || y<0 || y>=SIZE) continue;
			if(x==c->x_a && y==c->y_a) continue;
			if(c->board[x][y]) continue;
			if(!c->child[i]) c->child[i]=new State(c,c->x_a,c->y_a,x,y);
			double current_cost=search(*(c->child[i]),depth+DEPTH,-100000000.0,100000000.0);
			if(current_cost<min_cost) {
				choice=c->child[i];
				min_cost=current_cost;
			}
		}
		if(!choice) for(register int i=0;i<8;i++) if(c->child[i]) {
			choice=c->child[i];
			break;
		}
		c=choice;
		c->show();
		if(c->is_leaf()) break;
	}
	return 0;
}