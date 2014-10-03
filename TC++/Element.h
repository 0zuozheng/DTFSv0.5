#include "Data.h"

//������Ԫ�����������������det,sf,dsf,dxyzsfΪ��Ԫ�������	
extern int ijk[3];
extern float nodexyz_e[3][8], **det, ***sf, ****dsf, ****dxyzsf;
extern float w2x2x2[8],w3x3x3[27],w4x4x4[64],w5x5x5[125];
extern float i2x2x2_[8][3],i3x3x3_[27][3],i4x4x4_[64][3],i5x5x5_[125][3];

//������Ԫ��������
void GetNodeXYZ(int nodenum, int en);
void GetSfDsf(float x, float y, float z, float* sf_, float** dsf_);
void GetDetDxyzsf(float* det_, float** dsf_, float** dxyzsf_);
void ElementAnalysis();

//21.LibraryNormal.cpp
extern void ShapeFunc_normal(int);

//25.ElementParameter.cpp
extern void IntegratePlan();

//�����κ���log
extern FILE *log_N;