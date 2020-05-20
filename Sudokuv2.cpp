#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printSoduko(vector<vector<int>>&);


vector<pair<pair<int,int>,vector<int>>> get_possible_outcomes(vector<vector<int>>& v){
	vector<pair<pair<int,int>,vector<int>>> possible_outcomes;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(v[i][j] == -1){
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
				int c = count(possible.begin()+1,possible.end(),true);
				if(c == 0){
					throw "No more possibilities : BACKTRACK";
				}else if(c == 1){
					for(int k=1;k<10;k++){
						if(possible[k]){
							v[i][j] = k;
						}
					}
					continue;
				}
				vector<int> possibilities;
				for(int k=1;k<10;k++){
					if(possible[k]){
						possibilities.push_back(k);
					}
				}
				possible_outcomes.push_back(make_pair(make_pair(i,j),possibilities));
			}
		}
	} 
	return possible_outcomes;
}

bool sortbyNumPossibilities(const pair<pair<int,int>,vector<int>>& a,const pair<pair<int,int>,vector<int>>& b){
		return a.second.size() < b.second.size();
}

bool fillSoduko(vector<vector<int>>& v){
	vector<pair<pair<int,int>,vector<int>>> possible_outcomes;
	try{
		possible_outcomes = get_possible_outcomes(v);
	}catch(const char* err){
		return false;
	}
	sort(possible_outcomes.begin(),possible_outcomes.end(),sortbyNumPossibilities);
	/*unordered_map<pair<int,int>,vector<int>> possibilities_map;
	for(auto &square : possible_outcomes){
		possibilities_map[square.first] = square.second;
	}*/
	for(auto &square : possible_outcomes){
		int i = square.first.first,j = square.first.second;
		for(int& possible_num : square.second){
			v[i][j] = possible_num;
			printSoduko(v);
			bool did_succeed = fillSoduko(v);
			if(did_succeed){
				return true;
			}else{
				v[i][j] = -1;
			}
		}
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(v[i][j] == -1){
				return false;
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
