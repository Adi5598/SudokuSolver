#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printSoduko(vector<vector<int>>&);

bool fillSoduko(vector<vector<int>>& v){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(v[i][j] == -1){
				//cout << i << " " << j  << endl;
				vector<bool> possible(10,true);
				for(int k=0;k<9;k++){
					if(v[i][k] != -1){
						possible[v[i][k]] = false;
					}
				}
				for(int k=0;k<9;k++){
					if(v[k][j] != -1){
						possible[v[k][j]] = false;
					}
				}
				int row = i/3;
				int col = j/3;
				row *= 3;
				col *= 3;
				for(int k=0;k<3;k++){
					for(int w=0;w<3;w++){
						if(v[row+k][col+w] != -1){
							possible[v[row+k][col+w]] = false;
						}
					}
				}
				int c = count(possible.begin(),possible.end(),true);
				if(c == 1){
					return false;
				}
				for(int k=1;k<10;k++){
					if(possible[k]){
						v[i][j] = k;
						bool b = fillSoduko(v);
						//printSoduko(v);
						if(b){
							return b;
						}else{
							v[i][j] = -1;
						}
					}
				}
			}
		}
	} 
	return true;
}


void printSoduko(vector<vector<int>>& v){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(){
	vector<vector<int>> v(9,vector<int>(9,-1));
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cin >> v[i][j];
		}
	}
	fillSoduko(v);
	printSoduko(v);
	return 0;
}

























