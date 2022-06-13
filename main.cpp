#include <bits/stdc++.h>
#define sz 9
using namespace std;
int arr[sz][sz] = {0};
int n;
vector<int> row;
vector<int> col;
vector<int> block;
vector<vector<int> > ava_nums;
vector<int> avability_check(int, int);
int block_index(int,int);
int get_empty_num(int,int);
void print_matrix();

vector<int> avability_check(int row, int col){
	vector<int> ok;
	bool rowline[sz+1] = {false};
	bool colline[sz+1] = {false};
	bool blockline[sz+1] = {false};
	bool num[sz+1] = {false};
	//row
	for (int i=0;i<n*3;i++){
		if (arr[i][col]!=0){
		if (rowline[(arr[i][col])]==true){
			return ok;
		}
		else {
			num[arr[i][col]] = true;
			rowline[arr[i][col]] = true;
		}
		}
	}
	//col
	for (int i=0;i<n*3;i++){
		if(arr[row][i]!=0){
		if (colline[arr[row][i]]==true){
			return ok;
		}
		else {
			num[arr[row][i]] = true;
			colline[arr[row][i]] = true;
		}
		}
	}
	//block
	int area = block_index(row,col);
//	cout << area << endl;
	for(int i=(area/3)*3;i<=(area/3)*3+2;i++){
		for (int j=(area%3)*3;j<=(area%3)*3+2;j++){
			if(arr[i][j]!=0){
				if (blockline[arr[i][j]]==true){
					return ok;
				}
			else {
					num[arr[i][j]] = true;
					blockline[arr[i][j]] = true;
			}
			}
		}
	}
	for (int i=1;i<=sz;i++){
		if (num[i]==false){
			ok.push_back(i);
		}
	}
	return ok;
} 

int get_empty_num(vector<int> &row, vector<int> &col){
	row.clear();
	col.clear();
	int num = 0;
	for(int i=0;i<3*n;i++){
		for(int j=0;j<3*n;j++){
			if (arr[i][j]==0){
				row.push_back(i);
				col.push_back(j);
				num++;
			}
		}
	}
	return num;
}

int block_index(int row,int col){
	row = row / 3;
	col = col / 3;
	int num = row*3 + col;
	return num;
}

void DFS(int current,int blank,vector<int> &row,vector<int> &col){
	if (current == blank){
		print_matrix();
		return; 
	}
	int r = row[current];
	int c = col[current];
	vector<int> candidates = avability_check(r,c);
	if (candidates.empty()) return;
	for(int i=0;i<candidates.size();i++){
		int value = candidates[i];
		arr[r][c] = value;
		DFS(current+1,blank,row,col);
		arr[r][c] = 0;
	}
}

void print_matrix(){
	for(int i=0;i<3*n;i++){
		for(int j=0;j<3*n;j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

int main(){
	cin >> n;
	
	for(int i=0;i<3*n;i++){
		for(int j=0;j<3*n;j++){
			cin >> arr[i][j];
		}
	}
	
	int blank = get_empty_num(row,col);
	DFS(0,blank,row,col);
//	for (int i=0;i<blank;i++){
//		vector<int> fl = avability_check(row[i],col[i]);
//		if (!fl.empty()){
//			cout << row[i] << " " << col[i] << " ";
//			cout << "(";
//			for(int j=0;j<fl.size();j++){
//				cout << fl[j] << " ";
//			}
//			cout << ")" << endl;
//		}
//		else {
//			cout << "NO SOLUTION" << endl;
//			break;
//		}
//	}
}
