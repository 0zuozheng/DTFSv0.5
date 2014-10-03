#include "ELEMENT.h"
#include "Data.h"
#include <cmath>
#include <iostream>
#include <iomanip>

//�����������
extern float *time_e, **Q0, ***H, ***P, **Q3;
extern int *elements_n, equationnum, *marked, *order;
extern bool *calculate_n; 
extern ofstream tecplot;
extern float *BetaValue;
extern int *SinkTable,*SurfLoadType;
extern int SurfLoadId;


//�����ļ�ָ��
extern FILE *log_element;

//�������㺯��
void Assembly();
void PreTreatment(int ln); 
void Tface(int ln, int en, int face, int boundarynum);
void Tstep(int ln,int ptn,int pn,float dt);
extern void StiffMatrix_HEX8(int);