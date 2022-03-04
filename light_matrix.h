#ifndef __LIGHT_MATRIX__
#define __LIGHT_MATRIX__

typedef struct{
	int row,col;
	float **element;
	unsigned char init;
}Mat;

Mat* MatCreate(Mat* mat, int row, int col);
void MatDelete(Mat* mat);
Mat* MatSetVal(Mat* mat, float* val);
void MatDump(const Mat* mat);


bool MatEqual(Mat* mat1,Mat* mat2);
Mat* MatTrans(Mat* src, Mat* dst);
void MatSwap(Mat *mat1,Mat *mat2);

#endif



