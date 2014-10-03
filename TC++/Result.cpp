#include "Result.h"

int rst_flag=0,rst_nodenum=0,*rst_nodes;
FILE *rst_file_node;

void Read_Result(){	//��ȡresult.dat�ļ�������������Ľ����
	FILE *fp;
	if (fp=fopen("Result.dat","r")){
		rst_flag=1;			//rst_flag����������ʶ
		rst_file_node=fopen("rst_nodes.dat","w");
		fscanf(fp,"%d\n",&rst_nodenum);
		rst_nodes=new int[rst_nodenum];

		for(int i=0;i<rst_nodenum;i++){
			fscanf(fp,"%d",&rst_nodes[i]);	rst_nodes[i]--;
			fprintf(rst_file_node,"Node:%7d X=%6.3f Y=%6.3f Z=%6.3f\n",rst_nodes[i]+1,xyz_n[rst_nodes[i]][0],xyz_n[rst_nodes[i]][1],xyz_n[rst_nodes[i]][2]);
		}fprintf(rst_file_node,"\nTemperature Result:\n");
		for(int i=0;i<rst_nodenum;i++)	fprintf(rst_file_node,"%10d",rst_nodes[i]+1);
		fprintf(rst_file_node,"\n");
		fclose(fp);
	}
}

void Rst_wrt_node(int maxnodenum,float *t_n){
	for(int i=0;i<rst_nodenum;i++){
		for(int j=0;j<maxnodenum;j++){
			if(j==rst_nodes[i]){
				fprintf(rst_file_node,"%10.3f",t_n[j]);
			}
		}
	}fprintf(rst_file_node,"\n");
}