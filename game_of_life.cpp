#include <bits/stdc++.h>
using namespace std;

vector<int> get_cells_status(const vector<vector<int>>& grid){
    vector<int> cells;
    int alive=0;
    int dead=0;
    for(vector<int> row:grid){
        for(int cell : row){
            if(cell){
                alive++;
            }else{
                dead++;
            }
        }
    }
    cells.push_back(alive);
    cells.push_back(dead);
    return cells;
}
void display(const vector<vector<int>>& grid){
    system("CLS");
    for(vector<int> Row:grid){
        for(int cell:Row){
            char c = (cell)? '#':'.';
            cout<<c;
        }
        cout<<'\n';
    }
}

int n_neigbors(const vector<vector<int>>& grid, int w, int h,int cell_w,int cell_h){

    int count=0;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if(i==0&&j==0) continue;
            int nrow=cell_h+i;
            int ncol=cell_w+j;
            if(nrow>=h||ncol>=w||nrow<0||ncol<0) continue;
            if(grid[nrow][ncol]==1) count++;
        }
    }
    
    return count;
}

vector<vector<int>> update(const vector<vector<int>>& grid,int w,int h){
    vector<vector<int>> newgrid = grid;
    int cur_row=0;
    int cur_col=0;
    for(vector<int> row:grid){
        for(int cell:row){
            int neigbors = n_neigbors(grid,w,h,cur_col,cur_row);
            if(cell){
                if(neigbors<2||neigbors>3){
                    newgrid[cur_row][cur_col]=0;
                }else{
                    newgrid[cur_row][cur_col]=1;
                }
            }else{
                if(neigbors == 3){
                    newgrid[cur_row][cur_col]=1;
                }
            }
            cur_col++;
        }
        cur_row++;
        cur_col=0;
    }
    return newgrid;
}

int main(){
    int h=20;
    int w=40;
    vector<vector<int>> grid(h,vector<int>(w,0));
    cout<<"How many alive cells are there (pseudo generated locations) [be relative to number of total cells (800) ] >";
    int n;cin>>n;
    system("cls");
    cout<<"enter fps (recommended : 10) >";
    int fps;cin>>fps;
    system("cls");
    if(n>(w*h)){
        cout<<"more alive cells than total cells !";
        return 1;
    }
    srand(time(0));
    while(n--){
        grid[rand() % h][rand() % w]=1;
    }
    long long counter = 0;
    display(grid);
    vector<vector<int>> newgrid = update(grid,w,h);
    std::this_thread::sleep_until(std::chrono::system_clock::now()+std::chrono::milliseconds(1000/fps));
    system("CLS");
    while(true){
        display(newgrid);
        cout<<"Alive cells : "<<get_cells_status(newgrid)[0]<<"  |  "<<"Dead cells : "<<get_cells_status(newgrid)[1];
        cout<<'\n';
        cout<<"Generation : "<<counter;
        newgrid = update(newgrid,w,h);
        std::this_thread::sleep_until(std::chrono::system_clock::now()+std::chrono::milliseconds(1000/fps));
        counter++;
    }
    return 0;

}
