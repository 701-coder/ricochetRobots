#include <bits/stdc++.h>
using namespace std;

const string R[4][8]={
	{
		"loooloooo",
		"loooooooo",
		"loooooloo",
		"loooooooo",
		"loolooooo",
		"loooooolo",
		"llooooooo",
		"loooooolo"
	},
	{
		"loooolooo",
		"loolooooo",
		"loooooooo",
		"llooooooo",
		"loooooloo",
		"loooooooo",
		"loooooloo",
		"loooloolo"
	},
	{
		"loooloooo",
		"loooooloo",
		"llooooooo",
		"loooooooo",
		"loooooloo",
		"loooooooo",
		"loolooooo",
		"loooooolo"
	},
	{
		"loloooooo",
		"loooloooo",
		"loloooooo",
		"loooooolo",
		"loooooooo",
		"loooooooo",
		"loolooooo",
		"loooooolo"
	}
}, C[4][8]={
	{
		"loooolooo",
		"loooooloo",
		"loooloooo",
		"loooooooo",
		"loooooooo",
		"loolooooo",
		"loooooooo",
		"looooollo"
	},
	{
		"loooolooo",
		"loooloooo",
		"loloooooo",
		"loooooool",
		"loooooooo",
		"loooooloo",
		"loooloooo",
		"loooooolo"
	},
	{
		"loooloooo",
		"loolooooo",
		"loooooloo",
		"loooooooo",
		"loooooooo",
		"loloooooo",
		"loooloooo",
		"loooooolo"
	},
	{
		"loooooloo",
		"loloooooo",
		"loooooooo",
		"loooooolo",
		"llooooooo",
		"loooooooo",
		"loooloooo",
		"loooooolo"
	}
};

const string Gx[4]={"cefg", "bdegh", "bceg", "bcdg"},
			 Gy[4]={"fchb", "cbgfd", "fbgc", "ebgd"};

string r[16], c[16];
int gx[17], gy[17]; // the 17 position of the goal
int step, gr, g;
int per[4]; // the random permutation of the board

void changeColor(char c){
	string s="\033[1;", t="RGYBPC";
	if(c=='W')s+="0m";
	for(int i=0; i<t.size(); ++i)if(c==t[i])s+='3', s+=(char)(49+i), s+='m';
	cout<<s;
}

void initMap(){
	for(int i=0; i<4; ++i)per[i]=i;
	random_shuffle(per, per+4);
	for(int i=0; i<16; ++i)r[i]=c[i]="ooooooooooooooooo";
	auto cor=[](char &a, char b){if(a=='o')a=b;};
	for(int i=0; i<8; ++i)for(int j=0; j<9; ++j)
		cor(r[i][j], R[per[0]][i][j]), cor(c[i][j], C[per[0]][i][j]),
		cor(c[i][16-j], R[per[1]][i][j]), cor(r[15-i][j], C[per[1]][i][j]),
		cor(r[15-i][16-j], R[per[2]][i][j]), cor(c[15-i][16-j], C[per[2]][i][j]),
		cor(c[15-i][j], R[per[3]][i][j]), cor(r[i][16-j], C[per[3]][i][j]);
	int k=0;
	for(int i=0; i<Gx[per[0]].size(); ++i, ++k)gx[k]=Gx[per[0]][i]-'a', gy[k]=Gy[per[0]][i]-'a';
	for(int i=0; i<Gx[per[1]].size(); ++i, ++k)gx[k]=-Gy[per[1]][i]+'p', gy[k]=Gx[per[1]][i]-'a';
	for(int i=0; i<Gx[per[2]].size(); ++i, ++k)gx[k]=-Gx[per[2]][i]+'p', gy[k]=-Gy[per[2]][i]+'p';
	for(int i=0; i<Gx[per[3]].size(); ++i, ++k)gx[k]=Gy[per[3]][i]-'a', gy[k]=-Gx[per[3]][i]+'p'; 
}

struct point{
	int x, y;
	point(){}
	point(int _x, int _y):x(_x), y(_y){}
	point operator+(const point rhs){return point(x+rhs.x, y+rhs.y);}
	void operator+=(const point rhs){x+=rhs.x, y+=rhs.y;}
	bool operator==(const point rhs){return x==rhs.x&&y==rhs.y;}
}robot[4];

const point direction[4]={point(1, 0), point(0, 1), point(-1, 0), point(0, -1)};

void makeMap(){
	cout<<step<<" steps\nRobot #"<<gr<<" to X\n";
	changeColor('W');
	for(int i=0; i<65; ++i)cout<<(i&3?'_':'.'); cout<<endl;
	for(int i=0; i<16; ++i){
		for(int j=0; j<65; ++j){
			if(j&3){
				if((j&3)==2){
					int k=0;
					if(gx[g]==i&&gy[g]==j>>2){
						for(; k<4; ++k)if(robot[k]==point(i, j>>2)){
							if(k==gr)changeColor('Y');
							cout<<'Y';
							if(k==gr)changeColor('W');
							break;
						}
						if(k==4)cout<<'X';
						k=5;
					}
					for(; k<4; ++k)if(robot[k]==point(i, j>>2)){
						if(k==gr)changeColor('G');
						else changeColor('R');
						cout<<k;
						changeColor('W');
						break;
					}
					if(k==4)cout<<' ';
				}
				else cout<<' ';
			}
			else cout<<(r[i][j>>2]=='l'?'|':' ');
		}
		cout<<endl;
		for(int j=0; j<65; ++j)cout<<(j&3?c[j>>2][i+1]=='l'?'_':' ':r[i][j>>2]=='l'?'|':'.');
		cout<<endl;
	}
	changeColor('W');
}

void init(){
	step=0, gr=rand()%4, g=rand()%17;
	makeMap();
}

const uint kN=1<<23;
uint H[kN], from[kN], goal, gbot; // the goal and the robot to the goal
point nxt[16][16][4];
bool vis[kN];
int dis[kN];

int h(uint x){
	uint y=x;
	do x=((x<<2u)+x+1u)&kN-1u; while(H[x]&&H[x]!=y);
	H[x]=y;
	return x;
}

point nxtPos(point q, int d){
	point p=direction[d];
	for(;;q+=p){
		if(d==0&&c[q.y][q.x+1]=='l')break;
		if(d==1&&r[q.x][q.y+1]=='l')break;
		if(d==2&&c[q.y][q.x]=='l')break;
		if(d==3&&r[q.x][q.y]=='l')break;
	}
	return q;
}

point getPos(uint x, uint r){
	uint pos=x>>(r<<3u)&255u;
	return point(pos>>4u, pos&15u);
}

void addRobot(uint &x, point p, uint r){
	x&=(uint)(-1)^(255u<<(r<<3u));
	x|=(uint)(p.x<<4|p.y)<<(r<<3u);
}

uint bfsInit(){
	for(int i=0; i<kN; ++i)H[i]=vis[i]=dis[i]=0;
	goal=(gx[g]<<4)+gy[g], gbot=gr<<3;
	for(int i=0; i<16; ++i)for(int j=0; j<16; ++j)for(int k=0; k<4; ++k)nxt[i][j][k]=nxtPos(point(i, j), k);
	uint x=0;
	for(int i=0; i<4; ++i)addRobot(x, robot[i], i);
	return x;
}

uint Nxt(uint x, uint y){
	uint r=y>>2, d=y&3;
	point p=getPos(x, r), q=nxt[p.x][p.y][d];
	for(int i=0; i<4; ++i)if(i!=r){
		point pr=getPos(x, i);
		if(pr.x==p.x&&d&1){
			if(p.y<pr.y&&pr.y<=q.y)q=pr+point(0, -1);
			else if(q.y<=pr.y&&pr.y<p.y)q=pr+point(0, 1);
		}
		else if(pr.y==p.y&&!(d&1)){
			if(p.x<pr.x&&pr.x<=q.x)q=pr+point(-1, 0);
			else if(q.x<=pr.x&&pr.x<p.x)q=pr+point(1, 0);
		}
	}
	addRobot(x, q, r);
	return x;
}

uint bfs(uint x){
	queue<uint> b;
	b.push(x), dis[h(x)]=from[h(x)]=0, vis[h(x)]=1;
	while(!b.empty()){
		x=b.front(), b.pop();
		for(int i=0; i<16; ++i){
			uint y=Nxt(x, i);
			int z=h(y);
			if(!vis[z]){
				vis[z]=1, dis[z]=dis[h(x)]+1, from[z]=x;
				if((y>>gbot&255u)==goal)return y;
				b.push(y);
			}
		}
	}
	return 0;
}

void print(uint x){
	for(int i=0; i<4; ++i)robot[i]=getPos(x, i);
	makeMap();
}

void waitRes(){
	string s;
	cout<<"Press enter to continue...", getline(cin, s);
}

int main(){
	cout<<"The robot won't stop until it bumps into a wall or another robot.\n\
The mission is to move the given robot to the right place (which is ususally marked X).\n\
The place is marked Y if there's a robot on it.\n\
Press N to have a new mission.\n\
Have fun!\n";
	robot[0]=point(0, 0), robot[1]=point(0, 15), robot[2]=point(15, 15), robot[3]=point(15, 0);
	srand(time(0)), initMap();
	while(1){
		init();
		uint x=bfs(bfsInit());
		cout<<dis[h(x)]<<" steps in total!\n";
		waitRes();
		vector<uint> route;
		route.push_back(x);
		while(from[h(x)])route.push_back(x=from[h(x)]);
		reverse(route.begin(), route.end());
		for(uint i:route)print(i), sleep(1), ++step;
	}
}
