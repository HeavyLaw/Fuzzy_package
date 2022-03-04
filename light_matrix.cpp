#include "light_matrix.h"
#include <stdio.h>
#include <stdlib.h>


#define MAT_LEGAL_CHECKING
#define MAT_INIT_FLAG 0x5C


/***************************************************/
/*               Public Function                   */
/***************************************************/

Mat* MatCreate(Mat* mat,int row,int col)
{
	int i;

#ifdef MAT_LEGAL_CHECKING
	if(mat->init == MAT_INIT_FLAG){
		if(mat->row == row && mat->col == col)
			return mat;
		else
			MatDelete(mat);
	}
#endif

	mat->element = (float**)malloc(row * sizeof(float*));
	for(i = 0;i<row;i++){
		mat->element[i] = (float*)malloc(col * sizeof(float));
	}

	if(mat->element == NULL){
		return NULL;
	}
	mat->row = row;
	mat->col = col;
	mat->init = MAT_INIT_FLAG;
	
	return mat;
}

void MatDelete(Mat* mat)
{
	int i;

#ifdef MAT_LEGAL_CHECKING
	if(mat->init == MAT_INIT_FLAG){
		return ;
	}
#endif
	
	for(i = 0;i < mat->row; i++)
		free(mat->element[i]);
	free(mat->element);

	mat->init = 0;
}

Mat* MatSetVal(Mat* mat,float* val)
{
	int row,col;

	for(row = 0;row < mat->row; row++){
		for(col = 0;col < mat->col; col++){
			mat->element[row][col] = val[col + row * mat->col];
		}
	}

	return mat;
}

void MatDump(const Mat* mat)
{
	int row,col;
#ifdef MAT_LEGAL_CHECKING
	if(mat == NULL){
			return ;
	}
#endif

	printf("Mat %dx%d:\n",mat->row,mat->col);
	for(row = 0;row < mat->row; row++){
		for(col = 0;col < mat->col; col++){
			printf("%.2f\t",mat->element[row][col]);
		}
		printf("\n");
	}
}

Mat* MatTrans(Mat* src, Mat* dst)
{
    int row, col;

#ifdef MAT_LEGAL_CHECKING
    if( src->row != dst->col || src->col != dst->row ){
        printf("err check, unmatch matrix for MatTranspose!\n");
        MatDump(src);
        MatDump(dst);
        return NULL;
    }
#endif

    for(row = 0 ; row < dst->row ; row++){
        for(col = 0 ; col < dst->col ; col++){
            dst->element[row][col] = src->element[col][row];
        }
    }

    return dst;
}

bool MatEqual(Mat* mat1,Mat* mat2){
	int row,col;
	bool flag;

#ifdef MAT_LEGAL_CHECKING
	if(mat1->row != mat2->row || mat1->col != mat2->col){
		printf("err check,unmatch matrix for MatEqual!\n");
		MatDump(mat1);
		MatDump(mat2);
		return 0;
	}
#endif

	for(row = 0;row < mat1->row;row++){
		for(col = 0;col < mat1->col;col++){
			if(mat1->element[row][col] == mat2->element[row][col])
				flag = 1;
			else
			{
				flag = 0;
				goto here;
			}
		}
	}
	here:
	return flag;
}

void MatSwap(Mat *mat1,Mat *mat2){
	int row,col;
	Mat mat3;

#ifdef MAT_LEGAL_CHECKING
	if(mat1->row != mat2->row || mat1->col != mat2->col){
		printf("err check,unmatch matrix for MatSwap!\n");
		MatDump(mat1);
		MatDump(mat2);
	}
#endif

	MatCreate(&mat3,mat1->row,mat1->col);
	for(row = 0;row < mat1->row;row++){
		for(col = 0;col <mat1->col;col++){
			mat3.element[row][col] = mat1->element[row][col];
			mat1->element[row][col] = mat2->element[row][col];
			mat2->element[row][col] = mat3.element[row][col];
		}
	} 
}
