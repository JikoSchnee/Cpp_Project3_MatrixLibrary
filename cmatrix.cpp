
#include <string>
#include <iostream>
#include "cmatrix.h"

using namespace std;

void ptUD(int times,int UorD){
    string l = "╔";
    string r = "╗";
    string m = "═";
    if (UorD<0){
        l = "╚";
        r = "╝";
    }
    cout<<l;
    for (int i = 0; i < times; ++i) {
        cout<<m;
    }
    cout<<r<<endl;
}
void printMatrix(matrix &mat){
    ptUD(mat.column,1);
    int index = 0;
    for (int i = 0; i < mat.row; ++i) {
        cout<<"║";
        for (int j = 0; j < mat.column; ++j) {
            cout<<mat.data[index++];
        }
        cout<<"║";
    }
    ptUD(mat.column,-1);
}
matrix createMatrix(const int r,const int c,const float * data){//一维数组导入
    float saveData[r*c];
    for (int i = 0; i < r*c; ++i) {

    }
}