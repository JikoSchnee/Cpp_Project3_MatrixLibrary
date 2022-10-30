#ifndef CPP_PRO3_MATRIX_CMATRIX_H
#define CPP_PRO3_MATRIX_CMATRIX_H
class cmatrix {

};
struct matrix{
    //basic info
    int row;
    int column;
    float * data;
    //addition info

    //constructor
    matrix(int r,int c){
        row = r;
        column = c;
    }
    matrix(int r,int c,float * da){
        row = r;
        column = c;
        data = da;
    }
};
void ptUD(int times,int UorD);
void printMatrix(matrix &mat);
matrix createMatrix(const int r,const int c,const float * data);//一维数组导入法


#endif //CPP_PRO3_MATRIX_CMATRIX_H
