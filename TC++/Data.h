#include <fstream>
using namespace std;

//�������������ⲿ����
//���Ʋ�����ϢControl
extern int nodenum_c, elementnum_c, materialnum_c, loadnum_c, fixnum_c, elsetnum_c, nsetnum_c, sectionnum_c, initialnum_c, surfsetnum_c, surfnum_c,tablenum_c;

//������ϢMaterial
extern float *density_m, **diffusivity_m, *c_m, *rise_m, *m_m, **conduction_m;
extern char **name_m;

//�����ϢNode
extern float **xyz_n, *t_n;

//��Ԫ��ϢElement
extern int *material_e, **node_e, *class_e,*plan_e;
extern float *t_e;
extern int **surf_e;

//�߽�������ϢBoundary
extern int boundarynum_c,*num_b,**list_b,*table_b;
extern float *fix_b;
//extern int *node_b;
//extern float *fix_b;

//������Ϣ Loadcase
extern int incnum_c,inc_l, *deactive_l, maxelement_l;
extern float timeinc_l, totaltime_l; 
extern char name_l[500];

//���鶨����ϢSet
extern char **name_elset,**name_nset;
extern int *type_elset, **list_elset, *num_elset, *type_nset, **list_nset, *num_nset;

//���ϲ�����ϢSection
extern char **elset_section,**material_section;

//����Ϣ
extern char **name_surfset,**name_surf;
extern int *num_surfset, *type_surfset, **list_surfset, *num_surf, **elelist_surf, **facelist_surf;

//�����Ϣ
extern char **name_tb;
extern int *num_tb;
extern float **time_tb,**value_tb;
extern float **Table_step;

//Debug�ļ�
extern FILE *DEBUG;

//ˮ����Ϣ
extern int pipenum_c,*pts_p;
extern float ***xyz_p;

// iniArray.cpp
extern void Alloc2DArray_float(float*** arr,int k1,int k2);
extern void Alloc2DArray_int  (int*** arr,int k1,int k2);
extern void Alloc2DArray_char  (char*** arr,int k1,int k2);
extern void	Alloc3DArray_float(float**** arr,int k1,int k2,int k3);
extern void Alloc3DArray_int  (int**** arr,int k1,int k2,int k3);
extern void FREE2D_int(int** arr,int num);
extern void FREE2D_float(float** arr,int num);
extern void FREE2D_char(char** arr,int num);
extern void FREE3D_int(int*** arr,int num1,int num2);
extern void FREE3D_float(float*** arr,int num1,int num2);