#include "Transform.h"

int JudgePointInQuad(float* A,float* B,float* C,float* D){	// OΪԭ�㣬���ٸ���;ABCD��ʱ������
	float N1 = 1;	float* ABCD[4];
	ABCD[0] = A;	ABCD[1] = B;	ABCD[2] = C;	ABCD[3] = D;

	for (int i=0;i<4;i++){
		N1 *= PlaneCrossProduct(ABCD[i],ABCD[(i+1)%4],0);	// k = 0, ����ͶӰ��X��
		printf("Product[%d] = %f\n",i,N1);
		if (N1==0){
			if((ABCD[i][1]==ABCD[(i+1)%4][1])&&(ABCD[i][2]==ABCD[(i+1)%4][2])){
				N1=1;				
			}else{
				N1 = JudgePointInLine(ABCD[i],ABCD[(i+1)%4]);	
				break;
			}
		}
	}
	printf("N1=%f",N1);

	if (N1>0){		fprintf(log_transform,"\n�����ı�����\n");	return  1;	}
	else if (N1==0){fprintf(log_transform,"\n�����ı�����\n");	return  0;	}
	else{			fprintf(log_transform,"\n�����ı�����\n");	return -1;	}
}

float JudgePointInLine(float* A,float* B){	// Ĭ��A[0]=B[0]=0.0
	float N2;

	N2 = A[1]*B[1] + A[2]*B[2];	//	N2<0, �������߶���; N2=0, ������ڶ˵���; N2>0, ��������߶���
	return (-N2-abs(N2));		//  N2<=0, ����0; N2>0, ���ظ���
}

float JudgePointInTri(float* A,float* B,float* C){	// OΪԭ�㣬���ٸ���;ABCD��ʱ������
	float N3 = 1;

	N3 = (C[2]-A[2])/(C[1]-A[1])-(B[2]-A[2])/(B[1]-A[1]);
	N3 *= (C[2]-A[2])/(C[1]-A[1])-A[2]/A[1];

	if (N3>0)	fprintf(log_transform,"\n����������ABC��\n");
	else		fprintf(log_transform,"\n����������ABC��\n");

	return N3;
}