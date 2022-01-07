#include <bits/stdc++.h>
#include <windows.h>
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
int gx[17], gy[17];
int step, gr, g, id; clock_t t, cnt;
int per[4];

void cor(char &a, char b){if(a=='o')a=b;}

void initMap(){
	for(int i=0; i<4; ++i){
		int a; bool ok=1;
		while(ok){
			ok=0, a=rand()&3;
			for(int j=0; j<i; ++j)if(a==per[j])ok=1;
		}
		per[i]=a;
	}
	for(int i=0; i<16; ++i)r[i]=c[i]="ooooooooooooooooo";
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
vector<point> steps[4];

void makeMap(){
	system("cls");
	cout<<step<<" steps\nRobot #"<<gr<<" to X\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED);
	for(int i=0; i<65; ++i)cout<<(i&3?'_':'.'); cout<<endl;
	for(int i=0; i<16; ++i){
		for(int j=0; j<65; ++j){
			if(j&3){
				if((j&3)==2){
					int k=0;
					if(gx[g]==i&&gy[g]==j>>2){
						for(; k<4; ++k)if(robot[k]==point(i, j>>2)){
							if(k==id)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
							cout<<'Y';
							if(k==id)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED);
							break;
						}
						if(k==4)cout<<'X';
						k=5;
					}
					for(; k<4; ++k)if(robot[k]==point(i, j>>2)){
						if(k==id)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_GREEN);
						cout<<k;
						if(k==id)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED);
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}

void move(int id, int d){
	point p=d==0?point(1, 0):d==1?point(0, 1):d==2?point(-1, 0):point(0, -1);
	for(;;robot[id]+=p){
		for(int i=0; i<4; ++i)if(robot[id]+p==robot[i])return;
		if(d==0&&c[robot[id].y][robot[id].x+1]=='l')return;
		if(d==1&&r[robot[id].x][robot[id].y+1]=='l')return;
		if(d==2&&c[robot[id].y][robot[id].x]=='l')return;
		if(d==3&&r[robot[id].x][robot[id].y]=='l')return;
	}
}

bool key(int c){return GetKeyState((c+256)%256)<0;}

void init(){
	step=0, gr=id=rand()%4, g=rand()%17, cnt=0;
	for(int i=0; i<4; ++i)steps[i].clear(), steps[i].push_back(robot[i]);
	makeMap();
}

int main(){
	cout<<"Press WASD to move the robots.\n\
Press JKL; to change the robot you control to 0123, respectively.\n\
Press R to go back to the last step.\n\
The robot won't stop until it bumps into a wall or another robot.\n\
The mission is to move the given robot to the right place (which is ususally marked X).\n\
The place is marked Y if there's a robot on it.\n\
Press N to have a new mission.\n\
Have fun!\n", system("PAUSE"), system("cls"),
	cout<<"Copyright 2021 H.P.H. ";
	for(int i=0; i<3; ++i)Sleep(1000), cout<<". "; system("cls");
	robot[0]=point(0, 0), robot[1]=point(0, 15), robot[2]=point(15, 15), robot[3]=point(15, 0);
	srand(time(0)), initMap(), init();
	while(1){
		bool change=0;
		string s="SDWA";
		for(int i=0; i<4; ++i)if(key(s[i])){move(id, i), change=1; while(key(s[i]));}
		s="JKL ", s[3]=186;
		for(int i=0; i<4; ++i)if(i!=id&&key(s[i]))id=i, makeMap();
		if(change){for(int i=0; i<4; ++i)steps[i].push_back(robot[i]); ++step, makeMap();}
		if(step&&key('R')){for(int i=0; i<4; ++i)robot[i]=steps[i][step-1], steps[i].pop_back(); --step, makeMap();}
		if(key('N')){
			cout<<"Are you sure you want a new one? (Y/N)\n";
			while(key('N'));
			while(!key('N'))if(key('Y')){init(); break;}
			while(key('N'));
		}
		if(!cnt&&key('T'))t=clock(), cout<<"Start countdown!\n", cnt=1;
		if(cnt&&clock()-t>cnt*1000){
			cout<<"\b\b";
			if(cnt>50)cout<<' ';
			cout<<60-cnt++;
		}
		if(cnt==61)cout<<"\nTime's up!\n", cnt=0;
	}
}
