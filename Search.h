#ifndef SEARCH_H
#define SEARCH_H

#include<cmath>
#include<cstring>
#include<string>
#include<cstdlib>

using namespace std;

#define DEPTH 12

double search(State& S,int depth_limit,double alpha,double beta) { //生成子节点并计算代价
	if(S.depth>=depth_limit || S.is_leaf()) return S.cost_estimated;

	double ans;

	if(S.flag) {
		ans=100000000.0;
		for(register int i=0;i<8;i++) {
			if(!S.child[i]) {
				int x=S.x_b+move_x[i],y=S.y_b+move_y[i];
				if(x<0 || x>=SIZE || y<0 || y>=SIZE) continue;
				if(x==S.x_a && y==S.y_a) continue;
				if(S.board[x][y]) continue;
				S.child[i]=new State(&S,S.x_a,S.y_a,x,y);
			}
			State S1=*(S.child[i]);
			beta=ans=min(ans,search(S1,depth_limit,alpha,beta));
			if(alpha>=beta) break;
		}
	} else {
		ans=-100000000.0;
		for(register int i=0;i<8;i++) {
			if(!S.child[i]) {
				int x=S.x_a+move_x[i],y=S.y_a+move_y[i];
				if(x<0 || x>=SIZE || y<0 || y>=SIZE) continue;
				if(x==S.x_b && y==S.y_b) continue;
				if(S.board[x][y]) continue;
				S.child[i]=new State(&S,x,y,S.x_b,S.y_b);
			}
			State S1=*(S.child[i]);
			alpha=ans=max(ans,search(S1,depth_limit,alpha,beta));
			if(alpha>=beta) break;
		}
	}
	return ans;
}

#endif