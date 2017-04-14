//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <fstream.h>
#include <iostream.h>
#pragma hdrstop
struct Graph {int size; int **spisok; int *sm;} *graph1, *graph;
void Number_of_vertexes(FILE*, const char*);
//---------------------------------------------------------------------------

#pragma argsused
Graph *load_graph(const char *path)
{
	FILE *in = fopen(path, "r");
	if (!in) {
		printf("Error: Cannot open file '%s'.\n", path);
		exit(1);
	}

        graph = new Graph;

	// ��������� ���������� ������.
	//
	fscanf(in, "%d", &graph->size);
        fgetc(in); //���������� 1 ������(��������� �� ������ ������ ��������������� ������ �����
	// ������ ��� ������ - �����.

	// ������� ������ ���������.
	//
        graph->spisok = new int*[graph->size+1];
        for(int i=1;i<graph->size+1;i++){
                graph->spisok[i] = new int[1];
                graph->spisok[i][0] = -1; // ��� ������� �������� ������ �������, ������ -1 (������� � ����� ������� �� ����������)
        }
        graph->sm = new int[graph->size+1];
	// ��������� ������ ���������.
	//
        Number_of_vertexes(in, path);
        for(int i=1;i<graph->size+1;i++){
                if(graph->sm[i]>0){ //���� ��� ���-�� ������ 0
                        for(int i=0; i<2; i++) fgetc(in); //���������� 2 �������
                        delete graph->spisok[i]; //�� ������� ������ ������
                        graph->spisok[i]=new int[graph->sm[i]]; //� ��������� ����� � ����������� ���-��� ������
                        for(int j=0;j<graph->sm[i];j++){
                                fscanf(in, "%i", &graph->spisok[i][j]);
                        }
                }
                else continue;
        }
        fclose(in);
	return graph;
}
void show_graph(Graph *graph){ //������� ����, ��� ������ ���������
        int a;
        cout<<"\ngraph:\n"<<endl;
        for(int i=1;i<graph->size+1;i++){ //��� ������ �������
                cout<<i<<"->";
                if(graph->sm[i]==0){
                        cout<<endl;
                        continue;
                }
                for(int j=0;j<graph->sm[i]-1;j++){ //������� ������ ������� �� ������ (�� ������������� ������������)
                        cout<<graph->spisok[i][j]<<" , ";
                }
                a=graph->spisok[i][graph->sm[i]-1];
                cout<<a<<endl; //������� ����� ��������� ������� ������ ������� �������
        }
}
void run_testcase(int number, const char *path){
        int c, num=0;
        Graph *graph1;
        graph1=load_graph(path);
        show_graph(graph1);
        for(int i=1;i<graph1->size+1;i++){
                if(graph1->spisok[i][0]==-1){
                        cout<<"Otvet:"<<endl<<"Ne svyzniy graf!"<<endl;
                        return;
                }
                else num++;
        }
        if(num==graph1->size){
                cout<<"Otvet:"<<endl<<"Svyzniy graf!"<<endl;
                return;
        }
        cout<<"Nevernie dannie!"<<endl;
}
int main(int argc, char* argv[])
{
        run_testcase(1, "graph1.txt");
	run_testcase(2, "graph2.txt");
	run_testcase(3, "graph3.txt");
	run_testcase(4, "graph4.txt");
	run_testcase(5, "graph5.txt");
        getch();
        return 0;
}
void Number_of_vertexes(FILE *in, const char *path)//��������� ���-�� ������� ������ �������� ������
{
        int numberofel;
        char a;
        for(int i=1;i<graph->size+1;i++){
        numberofel=0;
        for(int i=0; i<2; i++) fgetc(in); //���������� 2 �������
        M:
                a=fgetc(in);
                if(a==' ') goto M;
                if(a!='\n'){
                        numberofel++;
                        goto M;
                }
                graph->sm[i]=numberofel;
        }
        fclose(in);
        in=fopen(path, "r");
        fseek(in, sizeof(int), 0);
}
//---------------------------------------------------------------------------
 