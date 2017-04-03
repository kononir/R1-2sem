//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>
#include <fstream.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
struct Graph {int size; char **names; int **spisok; int *sm} *graph1;
Graph* load_graph(char path)
{
	FILE *in = fopen(path, "r");
	if (!in) {
		printf("Error: Cannot open file '%s'.\n", path);
		exit(1);
	}

	Graph *graph = new Graph;

	// ��������� ���������� ������.
	//
	fscanf(in, "%d", &graph->size);

	// ��������� ����� ������.
	//
	graph->names = new char*[graph->size];
        for(int i=0;i<graph->size;i++) {
		char buf[60];
		fscanf(in, "%s", buf);
		graph->names[i] = strdup(buf); //strdup - �������, ������� ���������� ������ buf � ���� names, ��� ���� ������������� �������� ������������ ������
	}
	// ������� ������ ���������.
	//
        graph->spisok = new int*[graph->size];
        for(int i=0;i<graph->size;i++){
                graph->spisok[i] = new int[1];
                graph->spisok[i][0] = -1; // ��� ������� �������� ������ �������, ������ -1 (������� � ����� ������� �� ����������)
        }
	// ��������� ������ ���������.
	//
        int numberofel;
        for(i=0;i<graph->size;i++){
                fscanf(in, '%d', numberofel); //��������� ���-�� ������� ������ ������� ������
                if(numberofel>0){ //���� ��� ���-�� ������ 0
                        delete graph->spisok[i][1]; //�� ������� ������ ������
                        graph->spisok[i]=new[numberofel]; //� ��������� ����� � ����������� ���-��� ������
                        for(int j=0;j<numberofel;j++){
                                fscanf(in, '%d', graph->spisok[i][j]);
                        }
                }
                else continue;
        }
	return graph;
}
int run_testcase(int number, char path){
        int c;
        Graph *graph1;
        *graph1=load_graph(path);
        show_graph(graph1);
        for(int i=0;i<graph1->size;i++)
        if(graph1->spisok[i].[0]=-1){
                c=2;
                return c;
        }
        c=1;
        return c;
}
void show_graph(Graph *graph){
        cout<<"kolichestvo vershin"<<endl;
        for(int i=0;i<graph1->size;i++)
        cout<<graph1->names[i]<<" ";
        for
}
int main(int argc, char* argv[])
{
        run_testcase(1, "graph1.txt");

	run_testcase(2, "graph2.txt");
	run_testcase(3, "graph3.txt");
	run_testcase(4, "graph4.txt");
	run_testcase(5, "graph5.txt");
        return 0;
}
//---------------------------------------------------------------------------
 