//#include	"Data.h"
//#include	"Transform.h"
//extern FILE* log_transform;
//
//int node_face[6][4] = { {1,2,6,5},
//						{0,4,7,3},
//						{2,3,7,6},
//						{0,1,5,4},
//						{0,3,2,1},
//						{4,5,6,7}};
//
//void SinglePipeCrossFace(){
//
//	int k1,k2,k3;
//	float Xaxis[3] = {1, 0, 0};	// ������ϵ��������X�ᣩ
//	float B[4][3] = {0};		// �洢ABCD��������ϵ�µ�����
//	float coor_new[3];			// �����ԭ����ϵ������	
//	float pipe[3],XofO;			// �洢���߷���
//	float N[3];					// �洢��ֵ����
//	
//	float norm = NomalizeVector(pipe,L1,L2);		// �����������
//	fprintf(log_transform,"Norm = %f\n",norm);
//
//	CalcRotate(pipe,Xaxis);	// ��ת����ϵ��ʹˮ����������ϵ�µ�X��ƽ��
//	
//	CalcTranslate(L1);		// ƽ������ϵ��ʹˮ��λ��ԭ�㣬��ˮ�ܱ�ΪX��
//	
//	for (int i=0;i<4;i++){	// ����Aƽ�ƺ���ĵ����꣬��¼�뵽B
//		CalcCoordinate(A[i],B[i],rotatinMatrix,translateMatrix);
//	}
//	int N1 = JudgePointInQuad(B[0],B[1],B[2],B[3]);	// �жϵ��Ƿ����ı�����
//	
//	if (N1 >  0){
//		float  N3 = JudgePointInTri(A[0],A[1],A[2]);
//		if (N3>0)	k1 = 0, k2 = 1, k3 = 2;	
//		else		k1 = 2, k2 = 3, k3 = 0;	
//		
//		TriInterFunc(N,A[k1],A[k2],A[k3]);
//		float XofABC[3] = {B[k1][0],B[k2][0],B[k3][0]};
//		XofO = Interpolate(XofABC, N, 3);
//		if ((XofO<=norm)&&(XofO>=0)){
//			fprintf(log_transform,"����� x=%f �ڹ����ڲ�\n",XofO);
//			CoorInterpolateByTri(coor_new,A[k1],A[k2],A[k3],N);
//		}else	fprintf(log_transform,"����� x=%f �ڹ����ⲿ\n",XofO);
//	}
//
//	if (N1 == 0){
//		// ToDoToDoToDoToDoToDoToDoToDoToDo
//		//    �ڱ��ϵ��д���һ����̴���
//		// ToDoToDoToDoToDoToDoToDoToDoToDo
//		fprintf(log_transform,"�����ı��α���");
//	}
//	if (N1 <  0) fprintf(log_transform,"�����ı�����");
//}
//
//void PipeCrossFace(int PipeId,int EleId,int FaceId){
//	
//	
//	
//	for (int i=0;i<pipenum_c;i++){
//		for (int j=0;j<pts_p[i]-1;j++){
//			SinglePipeCrossFace(xyz_p[i][j],xyz_p[i][j+1]);
//		}
//	}
//}
//
//void GeometryAnalysis(){
//	for (int k=0;k<pipenum_c;k++){
//		for (int i=0;i<elementnum_c;i++){
//			for (int j=0;j<6;j++){
//				PipeCrossFace(k,i,j);
//			}
//		}
//	}
//}
//
