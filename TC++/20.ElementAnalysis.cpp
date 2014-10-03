/* * * * * * * * * * * * * * * * * *
*
*		��Ԫ�Ƶ�
*
* * * * * * * * * * * * * * * * * */

#include "ELEMENT.h"

float nodexyz_e[3][8], jacobi[3][3], divjacobi[3][3], **det, ***sf, ****dsf, ****dxyzsf;

void GetNodeXYZ(int nodenum,int en){ //en -> element_now;	���ӳ���ֻ���㵱ǰ��Ԫ��Node��Ϣ��ÿ�ε��ö�����һ��
	for(int i=0;i<nodenum;i++){
		int k=node_e[en][i];	//��ȡ����
		for(int j=0;j<3;j++)	nodexyz_e[j][i]=xyz_n[k][j];	//��ȡ������꣬����nodexyz_e
	}
}

void GetSfDsf(float x, float y, float z, float *sf_, float **dsf_){ //x,y,z -> coordinate; sf_ -> �κ���; dsf -> �κ�����ƫ����(�ֲ�����ϵ),�� (ƫN/ƫepsilon).
	int i,j;
	for(i=0;i<8;i++){
		sf_[i]=0;	for(j=0;j<3;j++)  dsf_[j][i]=0;	//��������
	}	// Serendipity����, �����޵�Ԫ���� P114
	sf_[0]=(1-x)*(1-y)*(1-z)/8;	 sf_[1]=(1+x)*(1-y)*(1-z)/8;    sf_[2]=(1+x)*(1+y)*(1-z)/8;	 sf_[3]=(1-x)*(1+y)*(1-z)/8;
	sf_[4]=(1-x)*(1-y)*(1+z)/8;	 sf_[5]=(1+x)*(1-y)*(1+z)/8;    sf_[6]=(1+x)*(1+y)*(1+z)/8;	 sf_[7]=(1-x)*(1+y)*(1+z)/8;

	dsf_[0][0]=-(1-y)*(1-z)/8;	 dsf_[0][1]=(1-y)*(1-z)/8;     dsf_[0][2]=(1+y)*(1-z)/8;	  dsf_[0][3]=-(1+y)*(1-z)/8;
	dsf_[0][4]=-(1-y)*(1+z)/8;	 dsf_[0][5]=(1-y)*(1+z)/8;     dsf_[0][6]=(1+y)*(1+z)/8;	  dsf_[0][7]=-(1+y)*(1+z)/8;

	dsf_[1][0]=-(1-x)*(1-z)/8;	 dsf_[1][1]=-(1+x)*(1-z)/8;    dsf_[1][2]=(1+x)*(1-z)/8;	  dsf_[1][3]=(1-x)*(1-z)/8;
	dsf_[1][4]=-(1-x)*(1+z)/8;	 dsf_[1][5]=-(1+x)*(1+z)/8;    dsf_[1][6]=(1+x)*(1+z)/8;	  dsf_[1][7]=(1-x)*(1+z)/8;

	dsf_[2][0]=-(1-x)*(1-y)/8;	 dsf_[2][1]=-(1+x)*(1-y)/8;	  dsf_[2][2]=-(1+x)*(1+y)/8;	  dsf_[2][3]=-(1-x)*(1+y)/8;
	dsf_[2][4]=(1-x)*(1-y)/8;	 dsf_[2][5]=(1+x)*(1-y)/8;	  dsf_[2][6]=(1+x)*(1+y)/8;	      dsf_[2][7]=(1-x)*(1+y)/8;
}	//�����ӳ����о��ھֲ�����ϵ������

void GetDetDxyzsf(float* det_, float **dsf_, float **dxyzsf_){ //det ->	Jacobi�������ʽ	dxyzsf -> �κ���ƫ��(��������ϵ)
	int i,j,k;	float tmp;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)  { jacobi[j][i]=0; divjacobi[j][i]=0; }//����Jacobi��
		for(j=0;j<8;j++)  dxyzsf_[i][j]=0;						//�����κ���ƫ����(��������ϵ)
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			tmp=0.0;
			for(k=0;k<8;k++)  tmp+=dsf_[i][k]*nodexyz_e[j][k];	// �����ÿ����Ԫ����ͬ��
			jacobi[i][j]=tmp;	//����Jacobi��
		}
	}
	for(i=0;i<3;i++){	//����������
		j=ijk[i];   k=ijk[j];
		divjacobi[i][i]=jacobi[j][j]*jacobi[k][k]-jacobi[k][j]*jacobi[j][k];
		divjacobi[i][j]=jacobi[k][j]*jacobi[i][k]-jacobi[i][j]*jacobi[k][k];
		divjacobi[j][i]=jacobi[j][k]*jacobi[k][i]-jacobi[j][i]*jacobi[k][k];
	}
	*det_=jacobi[0][0]*divjacobi[0][0]+jacobi[0][1]*divjacobi[1][0]+jacobi[0][2]*divjacobi[2][0];//��������ʽ
	for(i=0;i<3;i++){
		for(j=0;j<8;j++){
			tmp=0;
			for(k=0;k<3;k++)  tmp+=divjacobi[i][k]*dsf_[k][j];
			dxyzsf_[i][j]=tmp/(*det_);	// ����� = ������� / ����ʽ
		}
	}
}

void ElementAnalysis(){	// Called by Main.cpp
	det = (float **)calloc(elementnum_c,sizeof(float *));
	//w = (float **)calloc(elementnum_c,sizeof(float *));
	sf  = (float ***)calloc(elementnum_c,sizeof(float **));
	dsf  = (float ****)calloc(elementnum_c,sizeof(float ***));
	dxyzsf  = (float ****)calloc(elementnum_c,sizeof(float ***));
	
	IntegratePlan();	// �Ը��ֻ��ַ����ĳ���Ԥ�ȴ���, ����i2x2x2, w2x2x2֮���

	for(int i=0;i<elementnum_c;i++)	{
		ShapeFunc_normal(i);
	}
	fclose(log_N);
}