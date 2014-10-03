/* * * * * * * * * * * * * * * * * *
*
*		�������Ʋ���ֵ
*
* * * * * * * * * * * * * * * * * */
#include <string.h>
#include "Data.h"
extern FILE* log_check;
extern void Warning(char*,char* tmp2="",char* tmp3="");

int* list;	int len;	// ��̬����, ����

int SearchSetName(char* setname,int type){
	int id = 0;

	switch(type){
		case 1:		// ����� nset, e.g., Nset-1
			for (int i=0;i<nsetnum_c;i++)
				if (strcmp(setname,name_nset[i])==0)	id=i;
			break;
		case 2:		// ��Ԫ�� elset, e.g., Elset-1
			for (int i=0;i<elsetnum_c;i++)
				if (strcmp(setname,name_elset[i])==0)	id=i;
			break;
		case 3:		// �浥Ԫ�� surfset, e.g., Surf-1
			for (int i=0;i<surfsetnum_c;i++)
				if (strcmp(setname,name_surfset[i])==0)	id=i;
		case 4:		// �浥Ԫ�� surfset, e.g., Surf-1
			for (int i=0;i<surfnum_c;i++)
				if (strcmp(setname,name_surf[i])==0)	id=i;
		case 10:	// ������ material, e.g., MAT001
			for (int i=0;i<materialnum_c;i++)
				if (strcmp(setname,name_m[i])==0)		id=i;
			break;
		case 20:	// ����� table, e.g., AMP-1
			for (int i=0;i<tablenum_c;i++)
				if (strcmp(setname,name_tb[i])==0)		id=i;
			break;
	}
	return id;
}

void SearchSetList(int id,int type,char* cmd="Default"){	// type=1:nset;	type=2:elset
	free(list);
	if (strcmp(cmd,"Default")!=0)	id = SearchSetName(cmd,type);

// ����� nset
	if (type==1){
		if (type_nset[id]==1){ // ֱ������
			len  = num_nset[id];
			list = (int*)calloc(len,sizeof(int));
			for (int i=0;i<num_nset[id];i++){
				list[i] = list_nset[id][0] + i*list_nset[id][2];
			}
		}else if(type_nset[id]==2){ // ͨ����Ԫ
			len  = num_nset[id];
			list = (int*)calloc(len,sizeof(int));
			for (int j=0;j<num_nset[id];j++){
				list[j] = list_nset[id][j];
			}
		}else if (type_nset[id]==0){
			len  = num_nset[id];
			list = (int*)calloc(len,sizeof(int));
			for (int i=0;i<num_nset[id];i++){
				list[i] = list_nset[id][i];
			}
		}
	}
// ��Ԫ�� elset
	if (type==2){
		if (type_elset[id]==1){
			len  = num_elset[id];
			list = (int*)calloc(len,sizeof(int));
			for (int i=0;i<num_elset[id];i++){
				list[i] = list_elset[id][0] + i*list_elset[id][2];
			}
		}else if (type_elset[id]==0){
			len  = num_elset[id];
			list = (int*)calloc(len,sizeof(int));
			for (int i=0;i<num_elset[id];i++){
				list[i] = list_elset[id][i];
			}
		}
	}
// ��Ԫ����
	if (type==3){
		if (type_surfset[id]==0){
			len  = num_surfset[id];
			list = (int*)calloc(len,sizeof(int));
			for (int i=0;i<num_surfset[id];i++){
				list[i] = list_surfset[id][i];
			}
		}if (type_surfset[id]==1){
			len  = num_surfset[id];
			list = (int*)calloc(len,sizeof(int));
			for (int i=0;i<num_surfset[id];i++){
				list[i] = list_surfset[id][0] + i*list_surfset[id][2];
			}
		}
	}
}

void AssignInitial_T(char* nsetname, float iniT){
	int ele;	int id;

	id = SearchSetName(nsetname,1);	// ��ѯ���������
	if (type_nset[id]==2){			// �����ͨ����Ԫ��ֵ
		ele = num_nset[id];			// ��õ�Ԫ����
		SearchSetList(ele,2);		// ��õ�Ԫ�б�
		for (int i=0;i<len;i++)		// Ϊ��Ԫ����ֵ
			t_e[list[i]] = iniT;
	}else if(type_nset[id]==1){		// �����ֱ�Ӹ�ֵ
		SearchSetList(id,1);
		for (int i=0;i<len;i++)		// Ϊ��㸳��ֵ
			t_n[list[i]] = iniT;
	}else		
		Warning("The node set used in Initial Condition should be the elset format");

	
}

void AssignMaterial(int id,char* MaterialName){
	int MatID = SearchSetName(MaterialName,10);		//��ѯ�������
	int SetID = SearchSetName(elset_section[id],2);	//��ѯ��Ԫ���
	SearchSetList(SetID,2);

	for (int i=0;i<len;i++){
		material_e[list[i]] = MatID;
	}
}

void AssignSurface(int SurfId,char* SetName,int face){
	int SetID = SearchSetName(SetName,3);	//��ѯ��Ԫ���
	SearchSetList(SetID,3);

	int num_old = num_surf[SurfId];

	elelist_surf[SurfId]  = (int*)realloc(elelist_surf[SurfId],(num_old+len)*sizeof(int));
	facelist_surf[SurfId] = (int*)realloc(facelist_surf[SurfId],(num_old+len)*sizeof(int));

	for (int i=0;i<len;i++){
		elelist_surf[SurfId][num_old+i] = list[i];
		facelist_surf[SurfId][num_old+i] = face;
	}num_surf[SurfId] += len;
}