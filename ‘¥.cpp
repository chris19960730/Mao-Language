#include"����.h"
#define NULL 0

void DeleteSpace(char*sentence)   //ɾ�������еĿո�
{
int length = strlen(sentence);
int move = 0, count = 0;
for (move = 0; move <= length; move++) {
if (sentence[move] == ' ') {
continue;
}
sentence[count] = sentence[move];
count++;
}
}
void main(int argc,char*argv[]){
void DeleteSpace(char*sentence);
FILE*fp;
char *p;				//pָ��ÿһ�ж����ë�ļ��ַ���
fp = fopen(argv[1], "r");
struct mylist *head = NULL, *p1, *p2;
p1 = p2 = (struct mylist*)malloc(sizeof(struct mylist));
p = (char*)calloc(1005, sizeof(char));
int n = 0;
while (fgets(p, 1000, fp)){
int i = 0;
while (p[i] == ' '){    // ����ǰ���ֵĿո�
i++;
}
if (p[i] == 'i'&&p[i + 1] == 'n'&&p[i + 2] == 't'&&p[i + 3] == ' '){  // �ж��Ƿ�Ϊint ��
DeleteSpace(p);
int k = 0;
for (int j = 3; p[j] != '\0'; j++){
if ((p[j] != ',') && (p[j] != ';')){
p1->name[k] = p[j];
k++;
}
else{
p1->name[k] = '\0';
p1->type = 0;
p1->int_value = 0;
p1->double_value = 0.0;
p1->len = strlen(p1->name);
n = n + 1;
if (n == 1)
head = p1;
else
p2->next = p1;
p2 = p1;
p1 = (struct mylist*)malloc(sizeof(struct mylist));
k = 0;
}
}p2->next = NULL;
}
else if (p[i] == 'd'&&p[i + 1] == 'o'&&p[i + 2] == 'u'&&p[i + 3] == 'b'&&p[i + 4] == 'l'&&p[i + 5] == 'e'&&p[i + 6] == ' '){ //�ж��Ƿ�Ϊdouble��
DeleteSpace(p);
int k = 0;
for (int j = 6; p[j] != '\0'; j++){
if (p[j] != ',' && p[j] != ';'){
p1->name[k] = p[j];
k++;
}
else{
p1->name[k] = '\0';
p1->type = 1;
p1->int_value = 0;
p1->double_value = 0.0;
p1->len = strlen(p1->name);
n = n + 1;
if (n == 1)
head = p1;
else
p2->next = p1;
p2 = p1;
p1 = (struct mylist*)malloc(sizeof(struct mylist));
k = 0;
}
}p2->next = NULL;
}
else if (p[i] == 'p'&&p[i + 1] == 'r'&&p[i + 2] == 'i'&&p[i + 3] == 'n'&&p[i + 4] == 't' && (p[i + 5] == ' ' || p[i + 5] == '(')){ //�ж��Ƿ�Ϊprint���
DeleteSpace(p);
Print(p, head);
}
else{
DeleteSpace(p);
if (p[0] == '\n')   //��������
continue;
else{
Analysis(p, head, 0, strlen(p));
}
}
}
}