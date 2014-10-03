#include "Data.h"
extern void Warning(char*,char* tmp2="",char* tmp3="");
extern FILE* out;
extern int SearchSetName(char* setname,int type);
extern void AssignSurface(int,char*,int);
char KeywordData[500];
int Abaqus_face[7] = {0,5,4,3,0,2,1};

void TrimSpace(char* s){
	if (s==0)	return;
	char *p = s;
	int j = 0;
	for(int i=0;i<strlen(p);i++){
		if (p[i]!=10){		// ASCII:32-�ո�; 10-����
			if (p[i]!=32){
				s[j++] = p[i];
			}else{
				if (((p[i-1]>64)&&(p[i-1]<123))&&((p[i+1]>64)&&(p[i+1]<123)))
					s[j++] = p[i];
			}
		}
	}s[j]='\0';
}

void LineExtract(FILE *in,char (*cmd)[500],int* num){	
	char* token;	int i = 0;	char tmp[500];

	if(fgets(tmp,500,in)){
		token = strtok(tmp,",");
		if(token){
			TrimSpace(token);
			strcpy(cmd[0],token);
		}

		while (token){
			i++;
			token = strtok(NULL,",");
			if (token){
				TrimSpace(token);
				strcpy(cmd[i],token);
			}	
		}*num = i;
		if (*num==0)	cmd[0][0]=0;
	}
}

void KeywordElement(char (*cmd)[500],int num,int id){
	if (!strstr(cmd[0],"*Element"))	Warning("Keyword",cmd[0]," should not be included in the Element.inp");
	fprintf(out,cmd[0]);
	char type[500];		

	for (int i=1;i<num;i++){
		int output=1;// Default
		if (strstr(cmd[i],"type")){
			sscanf(cmd[i],"type=%s",&type);
			if (strcmp(type,"DCC3D8"))	// DCC3D8: 8-node Forced convection/diffusion elements
				Warning("Element type ",type," is not supported in this version.");
		}else{
			Warning(cmd[i]," is not a parameter in *Element");
			output = 0;
		}if(output)	fprintf(out,", %s",cmd[i]);
	}fprintf(out,"\n");	
}

void KeywordSet(char (*cmd)[500],int num,int* ElsetId,int* NsetId){
	char tmp[500];

	if (strstr(cmd[0],"*Elset")){
		*ElsetId = *ElsetId + 1;	fprintf(out,"%s",cmd[0]);
		for (int i=1;i<num;i++){
			int output = 1;
			if (strstr(cmd[i],"elset")){			//���� elset
				sscanf(cmd[i],"elset=%s",&tmp);
				sprintf(name_elset[*ElsetId],"%s",tmp);
			}else if(strstr(cmd[i],"generate")){	//����	generate
				type_elset[*ElsetId]=1;
			}else{
				Warning(cmd[i]," is not a parameter in *Elset");
				output = 0;
			}if(output)	fprintf(out,", %s",cmd[i]);
		}strcpy(KeywordData,"*Elset");
	}else if (strstr(cmd[0],"*Nset")){
		*NsetId = *NsetId + 1;		fprintf(out,"%s",cmd[0]);
		for (int i=1;i<num;i++){
			int output = 1;	
			if (strstr(cmd[i],"nset")){				//���� nset
				sscanf(cmd[i],"nset=%s",&tmp);
				sprintf(name_nset[*NsetId],"%s",tmp);
			}else if(strstr(cmd[i],"generate")){	//���� generate
				type_nset[*NsetId]=1;
			}else if(strstr(cmd[i],"elset")){		//���� elset
				sscanf(cmd[i],"elset=%s",&tmp);
				type_nset[*NsetId] = 2;
				num_nset[*NsetId] = SearchSetName(tmp,2);
			}else{
				Warning(cmd[i]," is not a parameter in *Nset");
				output = 0;
			}if(output)	fprintf(out,", %s",cmd[i]);
		}strcpy(KeywordData,"*Nset");
	
	}else{	// ���ݶ�
		if (strstr(KeywordData,"*Elset")){
			if(type_elset[*ElsetId]==1){		// ֱ�����ɵ�Ԫ��ʽ
				list_elset[*ElsetId] = (int*)calloc(3,sizeof(int));
				for(int i=0;i<3;i++)	sscanf(cmd[i],"%d",&list_elset[*ElsetId][i]);
				list_elset[*ElsetId][0]--;	list_elset[*ElsetId][1]--;	// �����������ı�
				num_elset[*ElsetId] = (list_elset[*ElsetId][1]-list_elset[*ElsetId][0])/list_elset[*ElsetId][2] + 1;//���γ���				
				fprintf(out,"%s, %s, %s",cmd[0],cmd[1],cmd[2]);
			}else if(type_elset[*ElsetId]==0){	// ֱ�Ӹ�����Ԫ�б�				
				num_elset[*ElsetId] += num;
				list_elset[*ElsetId]  = (int*)realloc(list_elset[*ElsetId],num_elset[*ElsetId]*sizeof(int));
				for(int i=0;i<num;i++){ int k;
					int startid = num_elset[*ElsetId]-num;
					sscanf(cmd[i],"%d",&k);	fprintf(out,"%d",k);
					k--;	list_elset[*ElsetId][startid+i] = k;					
					if(i!=num-1)	fprintf(out,", ");
				}
			}

		}else if(strstr(KeywordData,"*Nset")){
			if (type_nset[*NsetId]==1){		// ֱ�����ɽ��
				list_nset[*NsetId]=(int*)calloc(3,sizeof(int));
				for(int i=0;i<3;i++)	sscanf(cmd[i],"%d",&list_nset[*NsetId][i]);
				list_nset[*NsetId][0]--;	list_nset[*NsetId][1]--;	// �����������ı�
				num_nset[*NsetId] = (list_nset[*NsetId][1]-list_nset[*NsetId][0])/list_nset[*NsetId][2] + 1;	//���γ���
				fprintf(out,"%s, %s, %s",cmd[0],cmd[1],cmd[2]);
			}else if(type_nset[*NsetId]==2){	// ͨ����Ԫ, elset=...
				fprintf(out,",");
			}else if(type_nset[*NsetId]==0){	// ֱ�Ӹ����б�
				num_nset[*NsetId] += num;
				list_nset[*NsetId]  = (int*)realloc(list_nset[*NsetId],num_nset[*NsetId]*sizeof(int));
				for(int i=0;i<num;i++){	int k;
					int startid = num_nset[*NsetId]-num;
					sscanf(cmd[i],"%d",&k);	fprintf(out,"%d",k);
					k--;	list_nset[*NsetId][startid+i] = k;
					if(i!=num-1)	fprintf(out,", ");
				}
			}
		}
	}fprintf(out,"\n");	
}

void KeywordInitial(char (*cmd)[500],int num,int id){
	char tmp[500];
	if (!strstr(cmd[0],"*Initial Conditions"))	Warning("Keyword",cmd[0]," should not be included in initial condition");
	fprintf(out,cmd[0]);

	for (int i=1;i<num;i++){
		int output=1;
		if (strstr(cmd[i],"type")){				//���� nset
			sscanf(cmd[i],"type=%s",&tmp);
			if (strcmp(tmp,"TEMPERATURE"))	Warning("Inital condition type ",tmp," is not supported in this version.");
		}else{
			Warning(cmd[i]," is not a parameter in *Initial Condition");
			output = 0;
		}if(output)	fprintf(out,", %s",cmd[i]);
	}fprintf(out,"\n");
}

void KeywordSection(char (*cmd)[500],int num,int id){
	char tmp[500];
	if (!strstr(cmd[0],"*Solid Section"))	Warning("Keyword ",cmd[0]," should not be included in section definition");
	fprintf(out,cmd[0]);

	for (int i=1;i<num;i++){
		int output=1;
		if (strstr(cmd[i],"elset")){			//���� elset
			sscanf(cmd[i],"elset=%s",&tmp);
			sprintf(elset_section[id],"%s",tmp);
		}else if(strstr(cmd[i],"material")){	//���� material
			sscanf(cmd[i],"material=%s",&tmp);
			sprintf(material_section[id],"%s",tmp);
		}else{
			Warning(cmd[i]," is not a keyword in *Section");
			output = 0;
		}if(output)	fprintf(out,", %s",cmd[i]);
	}fprintf(out,"\n");
}

void KeywordMaterial(char (*cmd)[500],int num,int* id){
	char tmp[500];
	if (cmd[0][0]=='*'){	// *Keyword, ��������ؼ��֣��ոն�ȡ�����ݶ�
		if (strstr(cmd[0],"*Material")){	// *Material
			fprintf(out,"%s",cmd[0]);
			*id=*id+1;
			for(int i=1;i<num;i++){
				int output = 1;
				if (strstr(cmd[i],"name")){	// ���� name
					sscanf(cmd[i],"name=%s",&tmp);
					sprintf(name_m[*id],"%s",tmp);
				}else{
					Warning(cmd[i]," is not a parameter in *Material");
				}fprintf(out,", %s",cmd[i]);
			}
		}else{
			strcpy(KeywordData,cmd[0]);
			fprintf(out,"%s",cmd[0]);
		}fprintf(out,"\n");
	
	}else{	// �����������ݶΣ��ոն���ؼ���
		for(int i=0;i<num;i++){
			int output=1;	float f;	if(strlen(cmd[i]))	output = 1;
			sscanf(cmd[i],"%f",&f);
			if(strstr(KeywordData,"*Conductivity")){	// *Conductivity
				conduction_m[*id][0] = f;
			}else if(strstr(KeywordData,"*Density")){	// *Density
				density_m[*id] = f;
			}else if(strstr(KeywordData,"*Specific Heat")){	// *Specific Heat
				c_m[*id] = f;
			}else{
				output = 0;
			}
			if(output)	fprintf(out,"%.2f, ",f);
		}fprintf(out,"\n");
	}
}

void KeywordSurface(char (*cmd)[500],int num,int* SetId,int* SurfId){
	char tmp[500];
	if (cmd[0][0]=='*'){	// *Keyword, ��������ؼ���
		if (strstr(cmd[0],"*Elset")){	// *Material
			fprintf(out,"%s",cmd[0]);
			*SetId = *SetId+1;
			type_surfset[*SetId] = 0;
			for(int i=1;i<num;i++){
				int output = 1;
				if (strstr(cmd[i],"elset")){	// ���� name
					sscanf(cmd[i],"elset=%s",&tmp);
					sprintf(name_surfset[*SetId],"%s",tmp);
				}else if(strstr(cmd[i],"generate")){	// ���� name
					type_surfset[*SetId] = 1;
				}else{
					output = 0;
					Warning(cmd[i]," is not a parameter in *Elset");
				}if(output)	fprintf(out,", %s",cmd[i]);
			}
		}else if(strstr(cmd[0],"*Surface")){
			fprintf(out,"%s",cmd[0]);
			*SurfId = *SurfId+1;
			for(int i=1;i<num;i++){
				int output = 1;
				if (strstr(cmd[i],"type")){	// ���� name
					sscanf(cmd[i],"type=%s",&tmp);
					if (strcmp(tmp,"ELEMENT"))	Warning("type = ",tmp," is not supported in this version");
				}else if (strstr(cmd[i],"name")){	// ���� name
					sscanf(cmd[i],"name=%s",&tmp);
					sprintf(name_surf[*SurfId],"%s",tmp);
				}else{
					output = 0;
					Warning(cmd[i]," is not a parameter in *Surface");
				}if(output)	fprintf(out,", %s",cmd[i]);
			}
		}else{
			Warning("Keyword ",cmd[0]," should not be included in Surface.inp");
		}strcpy(KeywordData,cmd[0]);	fprintf(out,"\n");
	
	}else{	// �����������ݶ�
		if(strstr(KeywordData,"*Elset")){	// *Elset
			int ele;
			if(type_surfset[*SetId]==0){	// ֱ�Ӹ�ֵ��ʽ
				list_surfset[*SetId] = (int*)calloc(1,sizeof(int));
				num_surfset[*SetId] = 0;
				for(int i=0;i<num;i++){
					num_surfset[*SetId] ++;
					list_surfset[*SetId] = (int*)realloc(list_surfset[*SetId],num_surfset[*SetId]*sizeof(int));
					sscanf(cmd[i],"%d",&ele);	ele--;
					list_surfset[*SetId][num_surfset[*SetId]-1] = ele;
					fprintf(out," %d,",ele+1);
				}
			}else if(type_surfset[*SetId]==1){	// generate��ʽ
				list_surfset[*SetId] = (int*)calloc(3,sizeof(int));
				sscanf(cmd[0],"%d",&ele);	ele--;	list_surfset[*SetId][0] = ele;
				sscanf(cmd[1],"%d",&ele);	ele--;	list_surfset[*SetId][1] = ele;
				sscanf(cmd[2],"%d",&ele);	ele;	list_surfset[*SetId][2] = ele;
				num_surfset[*SetId] = (list_surfset[*SetId][1]-list_surfset[*SetId][0])/list_surfset[*SetId][2]+1;
				
				fprintf(out,"%s, %s, %s",cmd[0],cmd[1],cmd[2]);

			}	// �����������type
		}if(strstr(KeywordData,"*Surface")){	// *Surface
			char set[500];	int face;
			sscanf(cmd[0],"%s",&set);
			sscanf(cmd[1],"S%d",&face);
			fprintf(out,"%s, S%d",set,face);

			face = Abaqus_face[face];	// Abaqus --> ���� (�涨��)
			AssignSurface(*SurfId,set,face);			
		}			
		fprintf(out,"\n");
	}
}

void KeywordTable(char (*cmd)[500],int num,int* id){
	char tmp[500];
	if (cmd[0][0]=='*'){	// *Keyword, ��������ؼ��֣��ոն�ȡ�����ݶ�
		if (strstr(cmd[0],"*Amplitude")){	// *Material
			fprintf(out,"%s",cmd[0]);
			*id=*id+1;	num_tb[*id] = 0;
			for(int i=1;i<num;i++){
				int output = 1;
				if (strstr(cmd[i],"name")){	// ���� name
					sscanf(cmd[i],"name=%s",&tmp);
					sprintf(name_tb[*id],"%s",tmp);
				}else if (strstr(cmd[i],"time")){	// ���� name
					if (strcmp(cmd[i],"time=TOTAL TIME"))	Warning("Only 'time=TOTAL TIME' can be used in this version.");
				}else{
					Warning(cmd[i]," is not a parameter in *Amplitude");
				}fprintf(out,", %s",cmd[i]);
			}
		}else{
			Warning("Keyword ",cmd[0]," should not be included in table definition");
		}fprintf(out,"\n");

	}else{	// �����������ݶΣ��ոն���ؼ���
		num_tb[*id] += num/2;
		time_tb[*id]  = (float*)realloc(time_tb[*id],num_tb[*id]*sizeof(float));
		value_tb[*id] = (float*)realloc(value_tb[*id],num_tb[*id]*sizeof(float));
		for(int i=0;i<num/2;i++){
			float time,value;
			int startid = num_tb[*id]-num/2;
			sscanf(cmd[2*i],"%f",&time);		time_tb[*id][startid+i] = time;
			sscanf(cmd[2*i+1],"%f",&value);		value_tb[*id][startid+i] = value;			
			fprintf(out," %.2f, %.2f, ",time,value);			
		}fprintf(out,"\n");
	}
}