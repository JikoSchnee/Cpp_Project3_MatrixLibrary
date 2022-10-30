# Cpp_Project3_MatrixLibrary

## Struct matrix

一个矩阵主要有三个基本信息需要存储，分别为行数、列数以及矩阵每个格子的对应值。另外根据矩阵的特点又分为方阵、对称矩阵、对角矩阵、单位矩阵等等。因此我构建的结构体分为两个部分，一个是基础信息部分，另一个是附加信息部分，基础信息即三个基本信息，实时更新；附加信息即矩阵的特点，可以选择在需要的时候再进行更新（更新详见：*Function for convenience - refreshMatrix()*）。

为使可存储的矩阵尽可能大，我选择了long来存储行数和列数。为方便读取，我选择了一维数组而不是二维数组。因为特征只有是或不是两个可能性，所以使用bool类型来存储。

```c
struct matrix{
    //basic info
    long row;
    long column;
    float * data;
    //addition info
    bool square;      //方阵
    bool diagnose;    //对角矩阵
    bool symmetric;   //对称矩阵
    bool identical;   //单位矩阵
    //...可以继续添加
};
```

## Function for users

### createMatrix()

```c
struct matrix * createMatrix(const long r,const long c,float * data);
```

#### 思路构建

创建一个矩阵。将数组第n行拼到第n-1行后面，形成一个一维数组，从这一数组的0位开始依次放入data，直到 *行数与列数乘积减一* 位。

#### 错误检查

如果传入的矩阵指针为空、矩阵r和c其中至少有一个小于等于0、data*指向为空则会输出对应错误提示，并返回一个NULL指针。

#### 代码实现

```c
struct matrix *createMatrix(const long r, const long c, float *data) {//一维数组导入
    if (data == NULL) {
        puts("Error in \"createMatrix\": Pointer is NULL.\n");
        return NULL;
    } else if (r * c == 0||data==NULL) {
        puts("Error in \"createMatrix\": Matrix is empty.\n");
        return NULL;
    }
    struct matrix *newMat = (struct matrix *) malloc(1);
    newMat->row = r;
    newMat->column = c;
    float *saveData;
    saveData = (float *) malloc(r * c * sizeof(float));
    for (int i = 0; i < r * c; ++i) {
        saveData[i] = data[i];
    }
    newMat->data = saveData;
    refreshType(newMat);
    return newMat;
}
```

#### 样例展示

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030170309864.png" alt="image-20221030170309864" style="zoom:50%;" />

> case0构建时传入了空的指针，因此创建矩阵时打印了`Error in "createMatrix": Pointer is NULL.`，case1、2为正确的传入方式，下面即为打印出来的矩阵1和矩阵2。

### deleteMatrix()

```c
void deleteMatrix(struct matrix ** mat);
```

#### 思路构建

传入矩阵指针的地址，先释放其data的内存，再释放这个指针所占用的内存，最后再将这个指针指向NULL。

#### 错误检查

如果传入的地址所指向的指针本身指向的就为NULL，那么除了输出错误提示什么也不会做。

#### 代码实现

```c
void deleteMatrix(struct matrix ** mat_loc){
    if(mat_loc == NULL){
        printf("Error in \"deleteMatrix\": this mat is NULL.\n");
        return;
    }
    free((*mat_loc)->data);
    free(*mat_loc);
    *mat_loc = NULL;
}
```

#### 样例展示

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030172552289.png" alt="image-20221030172552289" style="zoom:50%;" />

> case0是一个空的指针，所以delete操作会有错误提示；
>
> case1是一个合法的矩阵指针，删除后再打印会提示矩阵指针已经指向了NULL。

### copyMatrix()

```c
struct matrix * copyMatrix(const struct matrix * const mat);
```

#### 思路构建

将要拷贝的数组的所有数据都拷贝一份，然后重新create一个内存位置不同的矩阵。

#### 错误检查

检查这个将要被拷贝的矩阵是否合法，若不合法则错误提示，并返回一个空指针。

#### 代码实现

```c
struct matrix *copyMatrix(const struct matrix *const mat) {
    if (mat == NULL||mat->column<=0||mat->row<=0||mat->data==NULL) {
        printf("Error in \"copyMatrix\": input an invalid matrix.\n");
        printFalse(mat);
        return NULL;
    }
    float array[mat->row * mat->column];
    for (int i = 0; i < mat->row * mat->column; ++i) {
        array[i] = mat->data[i];
    }
    return createMatrix(mat->row, mat->column, array);
}
```

#### 样例展示

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030174938811.png" alt="image-20221030174938811" style="zoom: 50%;" />

> case0为空指针，复制时返回出错提示；case1为合法的矩阵指针，打印发现两个矩阵相同。

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030175224781.png" alt="image-20221030175224781" style="zoom:50%;" />

> 删掉被拷贝的矩阵后，拷贝的矩阵依然不变，说明二者没有共用内存。

### addMatrix()

```c
struct matrix * addMatrix(const struct matrix * const mat1,const struct matrix * const mat2);
```

#### 思路构建

输入两个矩阵指针，两个指针的row和column相同，创建一个新数组，数组的长度为row * column，依次将对应的data存入这一数组，最后再使用这一数组create一个行数为row，列数为column的新矩阵，返回这个矩阵的指针。

#### 错误检查

检查矩阵指针是否指向NULL，是否存在column或row<=0，是否data指向NULL，如果有则输出相应错误提示，最后返回指向NULL的矩阵指针。

#### 代码实现

```c
struct matrix *addMatrix(const struct matrix *const mat1, const struct matrix *const mat2) {
    if (mat1 == NULL||mat1->column<=0||mat1->row<=0||mat1->data==NULL) {
        printf("Error in \"addMatrix\": input an invalid matrix(left).\n");
        printFalse(mat1);
        return NULL;
    }else if (mat2 == NULL||mat2->column<=0||mat2->row<=0||mat2->data==NULL) {
        printf("Error in \"copyMatrix\": input an invalid matrix(right).\n");
        printFalse(mat2);
        return NULL;
    }else if (mat1->column != mat2->column || mat1->row != mat2->row) {
        printf("Error in \"addMatrix\": matrix1 %d columns, matrix1 %d rows\n", mat1->column, mat1->row);
        printf("Error in \"addMatrix\": matrix2 %d columns, matrix2 %d rows\n", mat2->column, mat2->row);
        return NULL;
    }
    int c = mat1->column;
    int r = mat1->row;
    float array[c * r];
    for (int i = 0; i < c * r; ++i) {
        array[i] = mat1->data[i] + mat2->data[i];
    }
    return createMatrix(r, c, array);
}
```

#### 样例展示

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030202204312.png" alt="image-20221030202204312" style="zoom:50%;" />

> 第一个case是两个尺寸不同的矩阵相加，因此输出空指针。第二个case合法，输出了正确的矩阵。

### subMatrix()

```c
struct matrix * subMatrix(const struct matrix * const mat1, const struct matrix * const mat2);
```

#### 思路构建

输入两个矩阵指针，两个指针的row和column相同，创建一个新数组，数组的长度为row * column，依次将对应的data相减存入这一数组，最后再使用这一数组create一个行数为row，列数为column的新矩阵，返回这个矩阵的指针。

#### 错误检查

检查矩阵指针是否指向NULL，是否存在column或row<=0，是否data指向NULL，如果有则输出相应错误提示，最后返回指向NULL的矩阵指针。

#### 代码实现

```c
struct matrix *subMatrix(const struct matrix *const mat1, const struct matrix *const mat2) {
    if (mat1 == NULL||mat1->column<=0||mat1->row<=0||mat1->data==NULL) {
        printf("Error in \"subMatrix\": input an invalid matrix(left).\n");
        printFalse(mat1);
        return NULL;
    }else if (mat2 == NULL||mat2->column<=0||mat2->row<=0||mat2->data==NULL) {
        printf("Error in \"subMatrix\": input an invalid matrix(right).\n");
        printFalse(mat2);
        return NULL;
    }else if (mat1->column != mat2->column || mat1->row != mat2->row) {
        printf("Error in \"subMatrix\": matrix1 %d columns, matrix1 %d rows\n", mat1->column, mat1->row);
        printf("Error in \"subMatrix\": matrix2 %d columns, matrix2 %d rows\n", mat2->column, mat2->row);
        return NULL;
    }
    int c = mat1->column;
    int r = mat1->row;
    float array[c * r];
    for (int i = 0; i < c * r; ++i) {
        array[i] = mat1->data[i] - mat2->data[i];
    }
    return createMatrix(r, c, array);
}
```

#### 样例展示

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030203107847.png" alt="image-20221030203107847" style="zoom:50%;" />

> 第一个case是两个尺寸不同的矩阵相减，因此输出空指针。第二个case合法，输出了正确的矩阵。

### mulMatrix()

```c
struct matrix * mulMatrix(const struct matrix * const mat1,const struct matrix * const mat2);
```

#### 思路构建

mat1的每一行分别乘mat2的每一列，依次放入数组array中。

最终结果的矩阵行数与mat1相同，列数与mat2相同。最后create一个新的矩阵并返回其指针。

#### 错误检查

检查两个矩阵指针是否指向NULL，是否存在column或row<=0，是否data指向NULL，如果有则输出相应错误提示，且返回一个指向NULL的指针。

另外还需检查mat1的列数是否与mat2的行数相等，否则输出相应错误提示，且返回一个指向NULL的指针。

#### 代码实现

```c
struct matrix *mulMatrix(const struct matrix *const mat1, const struct matrix *const mat2) {
    if (mat1 == NULL || mat1->column<=0||mat1->row<=0||mat1->data == NULL) {
        printf("Error in \"mulMatrix\": Input a invalid matrix(left)");
        printFalse(mat1);
        return NULL;
    } else if (mat2 == NULL || mat2->column<=0||mat2->row<=0||mat2->data == NULL) {
        printf("Error in \"mulMatrix\": Input a invalid matrix(right)");
        printFalse(mat2);
        return NULL;
    } else if (mat1->column != mat2->row) {
        printf("Error in \"mulMatrix\": mat1's column(%d) not equal mat2's row(%d).\n", mat1->column, mat2->row);
        return NULL;
    }
    long r = mat1->row;
    long c = mat2->column;
    float array[r * c];
    long indexResult = 0;
    for (int i = 0; i < mat1->row; ++i) {
        for (int j = 0; j < mat2->column; ++j) {
            array[indexResult] = 0;
            for (int k = 0; k < mat1->column; ++k) {
                array[indexResult] += mat1->data[i * mat1->column + k] * mat2->data[j + mat2->column * k];
            }
            indexResult++;
        }
    }
    struct matrix *newMatrix = createMatrix(r, c, array);
    return newMatrix;
}
```

#### 样例展示

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030212315177.png" alt="image-20221030212315177" style="zoom:50%;" />

### addScalar() and subScalar() and mulScalar()

```c
void addScalar(struct matrix * const mat, float scalar);
```

```c
void subScalar(struct matrix * const mat, float scalar);
```

```c
void mulScalar(struct matrix * const mat, float scalar);
```

#### 思路构建

传入矩阵指针以及要加(减/乘)的常数，直接在原矩阵的data上作修改。

#### 错误检查

检查矩阵指针是否指向NULL，是否存在column或row<=0，是否data指向NULL，如果有则输出相应错误提示，除此之外不做任何操作。

#### 代码实现

以加法为例

```c
void addScalar(struct matrix *const mat, float scalar) {
    if (mat == NULL || mat->column<=0||mat->row<=0 || mat->data==NULL) {
        printf("Error in \"addSac\": Invalid input.");
        printFalse(mat);
        return;
    }
    for (int i = 0; i < mat->column * mat->row; ++i) {
        mat->data[i] += scalar;
    }
}
```

#### 样例展示

以加法为例

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030204310708.png" alt="image-20221030204310708" style="zoom:50%;" />

### findMin() and findMax()

```c
float findMin(const struct matrix * const mat);
```

```c
float findMax(const struct matrix * const mat);
```

#### 思路构建

遍历矩阵的data，返回最小(大)的值。

#### 错误检查

检查矩阵指针是否指向NULL，是否存在column或row<=0，是否data指向NULL，如果有则输出相应错误提示，且返回0.0f。

#### 代码实现

以查找最小值为例

```c
float findMin(const struct matrix *const mat) {
    if (mat == NULL || mat->column<=0||mat->row<=0 || mat->data==NULL) {
        printf("Error in \"findMin\": Invalid input.");
        printFalse(mat);
        return 0.0f;
    }
    float min = mat->data[0];
    for (int i = 0; i < mat->row * mat->column; ++i) {
        if (mat->data[i] < min) {
            min = mat->data[i];
        }
    }
    return min;
}
```

#### 样例展示

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030210505062.png" alt="image-20221030210505062" style="zoom:50%;" />

> case1是一个非法的矩阵地址，因此有对应的错误提示，case2输出了矩阵中的最大值。

### transportMatrix()

```c
struct matrix * transportMatrix(const struct matrix * const mat);
```

#### 思路构建

将(n,m)处的值放到(m,n)的地方，把row和column交换，如此create一个新的矩阵，并返回其地址。

#### 错误检查

检查矩阵指针是否指向NULL，是否存在column或row<=0，是否data指向NULL，如果有则输出相应错误提示，且返回一个指向NULL的指针。

#### 代码实现

```c
struct matrix *transportMatrix(const struct matrix *const mat) {
    if (mat == NULL || mat->column<=0||mat->row<=0 || mat->data==NULL) {
        printf("Error in \"transportMatrix\": Invalid input.");
        printFalse(mat);
        return NULL;
    }
    long r = mat->column;
    long c = mat->row;
    long index = 0;
    float array[r * c];
    for (int i = 0; i < mat->column; ++i) {
        for (int j = 0; j < mat->row; ++j) {
            array[index++] = mat->data[i + j * mat->column];
        }
    }
    struct matrix *newMatrix = createMatrix(r, c, array);
    return newMatrix;
}
```

#### 样例展示

<img src="C:\Users\27449\Desktop\学习\typora图片\image-20221030211332607.png" alt="image-20221030211332607" style="zoom:50%;" />

## Function for convenience

### refreshType()

```c
void refreshType(struct matrix * const mat); 
```

用于更新矩阵的附加条件的状态。每次create一个新矩阵的时候都会启用。

- 如果后续有函数需要使用到附加条件的时候只要在开头refresh这个矩阵就能正常使用了。
- 如果后续需要添加新的附加条件，只要在头文件中添加新的bool类型，并在refreshType中添加正则即可。

### printMatrix()

```c
void printMatrix(const struct matrix * mat);
```

用于打印矩阵，根据矩阵的数据有效位数可以修改%f的参数使得数据能够向右对齐。
