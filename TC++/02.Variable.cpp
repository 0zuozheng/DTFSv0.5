#include<stdlib.h>
// ����ȫ�ֱ���, �������ã�������Data.h
extern void FREE2D_int(int** arr,int num);
extern void FREE2D_float(float** arr,int num);
extern void FREE2D_char(char** arr,int num);
extern void FREE3D_int(int*** arr,int num1,int num2);
extern void FREE3D_float(float*** arr,int num1,int num2);
extern int *list;

int nodenum_c, elementnum_c, materialnum_c, loadnum_c, fixnum_c, elsetnum_c, nsetnum_c, sectionnum_c, initialnum_c, surfsetnum_c, surfnum_c;//���Ʋ�����ϢControl

float *density_m, **diffusivity_m, *c_m, *rise_m, *m_m, **conduction_m;//������ϢMaterial
char **name_m;

float **xyz_n, *t_n;//�����ϢNode

int *material_e, **node_e, *class_e, *plan_e;//��Ԫ��ϢElement
float *t_e;
int **surf_e;//��Ԫ����ϢElementFace
	
int boundarynum_c=0,*num_b,**list_b,*table_b;	//�߽����� Boundary
float *fix_b;
//int *node_b;
//float *fix_b;

int incnum_c,inc_l, *deactive_l, maxelement_l;//������Ϣ Loadcase
float timeinc_l, totaltime_l; 
char name_l[500];

int tablenum_c;

int pipenum_c,*pts_p;
float ***xyz_p;

char **name_elset, **name_nset;		// ����Ϣ Set
int *type_elset, **list_elset, *num_elset, *type_nset, **list_nset, *num_nset;

char **elset_section, **material_section;	// ���ϲ�����Ϣ Section

char **name_surfset,**name_surf;		// ����Ϣ
int *num_surfset, *type_surfset, **list_surfset, *num_surf, **elelist_surf, **facelist_surf;

char **name_tb;	// �����Ϣ
int *num_tb;
float **time_tb,**value_tb;

float **Table_step;//step

void Free_Read(){	// ����֮����Ҫɾ�����ı���
	FREE2D_char(name_m,materialnum_c);
	FREE2D_char(name_surfset,surfsetnum_c);
	free(num_surfset);
	free(type_surfset);
	FREE2D_int(list_surfset,surfsetnum_c);
}

void FreeVariables(){	// ������������Ҫɾ�����ı���

	FREE2D_float(xyz_n,nodenum_c);			free(t_n);
	free(material_e);   free(t_e);			FREE2D_int(node_e,elementnum_c);
	free(plan_e);		free(class_e);		FREE2D_int(surf_e,elementnum_c);
	free(deactive_l);
	
	// ������Ϣ
	FREE2D_float(diffusivity_m,materialnum_c);	free(density_m);	free(c_m);			
	FREE2D_float(conduction_m,materialnum_c);	free(rise_m);		free(m_m);			

	// ����Ϣ(��Ԫ�����)
	FREE2D_char(name_elset,elsetnum_c);		free(type_elset);	
	FREE2D_int(list_elset,elsetnum_c);		free(num_elset);
	FREE2D_char(name_nset,nsetnum_c);		free(type_nset);	
	FREE2D_int(list_nset,nsetnum_c);		free(num_nset);

	// Section��Ϣ
	FREE2D_char(elset_section,sectionnum_c);
	FREE2D_char(material_section,sectionnum_c);

	// ��Ԫ����Ϣ		
	FREE2D_char(name_surf,surfnum_c);		free(num_surf);
	FREE2D_int(elelist_surf,surfnum_c);		FREE2D_int(facelist_surf,surfnum_c);

	// �����Ϣ
	FREE2D_char(name_tb,tablenum_c);		free(num_tb);
	FREE2D_float(time_tb,tablenum_c);		FREE2D_float(value_tb,tablenum_c);

	// �߽���Ϣ
	free(num_b);	free(table_b);		free(fix_b);
	FREE2D_int(list_b,boundarynum_c);

	// step
	FREE2D_float(Table_step,tablenum_c);

	// free list
	free(list);
}