#include "Transform.h"

float rotatinMatrix[9];
float translateMatrix[3];

void test_Rotate(){
	//float a[3]={0, 1, -1};	// ԭ����ϵ���������ܣ�
	//float b[3]={-1.16, 0.8, -0.12};	//������ϵ��������ĳ�ᣩ
	//float c[3]={0, 0, 0};	// ԭ����ϵ����㣨�ܵ㣩
	//float x[3]={0, 1, -1};	// ԭ����ϵ�������
	//float y[3]={0, 0, 0};

	//CalcRotate(a,b);

	//for (int i=0;i<3;i++){
	//	for(int j=0;j<3;j++)	printf("%f\t",rotatinMatrix[i*3+j]);
	//	printf("\n");
	//}

	//CalcTranslate(c);

	//for (int i=0;i<3;i++)	printf("%f\t",translateMatrix[i]);
	//printf("\n");
	//	
	//CalcCoordinate(x,y);
	//
	//for (int i=0;i<3;i++)	printf("%f\t",y[i]);
	//getchar();
}

void CalcRotate(float* a,float* b){
	float Rot_Axis[3],cos_Rot_Angle;

	// ��������������������Rodrigues��ת��ʽ������ת����
	CrossProduct(Rot_Axis,a,b);
	cos_Rot_Angle = DotProduct(a,b)/(Normal(a)*Normal(b));
	Rodrigues(cos_Rot_Angle, Rot_Axis);

	// ��¼��ת����
	fprintf(log_transform,"Rotate Matrix : \n");
	for (int i=0;i<3;i++){
		for(int j=0;j<3;j++)	fprintf(log_transform,"%f\t",rotatinMatrix[i*3+j]);
		fprintf(log_transform,"\n");
	}
}

void CalcTranslate(float* a){
	// ����ƽ�ƾ���
	for(int i=0;i<3;i++)	translateMatrix[i]=-a[i];
	
	// ��¼ƽ�ƾ���
	fprintf(log_transform,"\nTranslate Matrix : \n");
	for (int i=0;i<3;i++)	fprintf(log_transform,"%f\t",translateMatrix[i]);
	fprintf(log_transform,"\n");
}

void CalcCoordinate(float* a,float* n,float* rMat,float* tMat){
	fprintf(log_transform,"\nOld coordinate : \n");
	for (int i=0;i<3;i++){
		fprintf(log_transform,"%f\t",a[i]);
		for (int j=0;j<3;j++){
			n[i] += rMat[i*3+j]*a[j];
		}n[i] += tMat[i];
	}fprintf(log_transform,"\nNew coordinate : \n");
	for (int j=0;j<3;j++)	fprintf(log_transform,"%f\t",n[j]);
}

void Rodrigues(float cos_theta, float* k){
	float norm = Normal(k);
	extern float rotatinMatrix[9];
	float sin_theta = sin(acos(cos_theta));

	if (norm>0.0001){	// ��ת������ģ����
		k[0] = k[0] / norm;
		k[1] = k[1] / norm;
		k[2] = k[2] / norm;
	//��1��
		rotatinMatrix[0] = cos_theta + k[0] * k[0] * (1 - cos_theta);
		rotatinMatrix[1] = k[0] * k[1] * (1 - cos_theta) - k[2] * sin_theta;
		rotatinMatrix[2] = k[1] * sin_theta + k[0] * k[2] * (1 - cos_theta);
	//��2��
		rotatinMatrix[3] = k[2] * sin_theta + k[0] * k[1] * (1 - cos_theta);
		rotatinMatrix[4] = cos_theta + k[1] * k[1] * (1 - cos_theta);
		rotatinMatrix[5] = -k[0] * sin_theta + k[1] * k[2] * (1 - cos_theta);
	//��3��
		rotatinMatrix[6] = -k[1] * sin_theta + k[0] * k[2] * (1 - cos_theta);
		rotatinMatrix[7] = k[0] * sin_theta + k[1] * k[2] * (1 - cos_theta);
		rotatinMatrix[8] = cos_theta + k[2] * k[2] * (1 - cos_theta);
	
	}else{	// ����ԭʼ�����ص�������ת����Ϊ������
		rotatinMatrix[0] = 1;		rotatinMatrix[1] = 0;		rotatinMatrix[2] = 0;
		rotatinMatrix[3] = 0;		rotatinMatrix[4] = 1;		rotatinMatrix[5] = 0;
		rotatinMatrix[6] = 0;		rotatinMatrix[7] = 0;		rotatinMatrix[8] = 1;
	}
}