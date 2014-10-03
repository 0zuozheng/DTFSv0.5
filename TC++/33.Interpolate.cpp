/*		��ֵ��ʽ
***		
***		
*/
#include <stdio.h>
extern FILE* log_transform;

void QuadInterFunc(float *N,float *inter,float (*corner)[3],int k=0){	// ���ݽ���������ά�ռ�����
	for (int i=0;i<4;i++){
		N[i] = 0.25f*(1+inter[1]*corner[i][1])*(1+inter[2]*corner[i][2]);
	}
}

float Interpolate(float *coor_old,float *N,int k=4){
	fprintf(log_transform,"Ҫ��ֵ��: %f %f %f\n",coor_old[0],coor_old[1],coor_old[2]);
	float coor_new = 0;
	for (int i=0;i<k;i++){
		coor_new += coor_old[i] * N[i];
	}return coor_new;
}

void TriInterFunc(float *N,float *A,float *B,float *C,int k=0){// ���ݽ���������ά�ռ�����,Ĭ�ϲ�ֵԭ��O(0,0)
	float a = B[1]*C[2];	float b = -B[2]*C[1];
	float c = A[2]*C[1];	float d = -A[1]*C[2];
	float e = A[1]*B[2];	float f = -A[2]*B[1];
	float D = a+b+c+d+e+f;	
	
	// ��������Ĳ�ֵ����
	N[0] = (a+b)/D;
	N[1] = (c+d)/D;
	N[2] = (e+f)/D;

	// ��¼��ֵ��������
	for (int i=0;i<3;i++)	fprintf(log_transform,"��ֵ���� [%d] : %f\n",i,N[i]);
}

void CoorInterpolateByTri(float *coor_new,float *A,float *B,float *C,float *N){
	// N ��ֵ����; A B C ��������; coor_new ��ֵ����
	float* ABC[3];
	ABC[0] = A;		ABC[1] = B;		ABC[2] = C;
	
	for (int i=0;i<3;i++){
		coor_new[i] = 0.0;
		for (int j=0;j<3;j++){
			coor_new[i] += ABC[j][i] * N[j];
		}fprintf(log_transform,"������ [%d] = %f\n",i,coor_new[i]);
	}
}

void OriginPointInterpolateByTri(float* coor_new,float *A,float *B,float *C){
	float N[3];
	TriInterFunc(N,A,B,C);					// �õ�ԭ���Ӧ���������Ĳ�ֵ����	
	CoorInterpolateByTri(coor_new,A,B,C,N); // �����ֵ��ԭ�����������µ�����
}