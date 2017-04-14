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

	// —читываем количество вершин.
	//
	fscanf(in, "%d", &graph->size);
        fgetc(in); //пропускаем 1 символ(переходим на первую строку непосредственно записи графа
	// ¬место имЄн вершин - числа.

	// —оздаем список смежности.
	//
        graph->spisok = new int*[graph->size+1];
        for(int i=1;i<graph->size+1;i++){
                graph->spisok[i] = new int[1];
                graph->spisok[i][0] = -1; // все массивы получают первый элемент, равный -1 (вершины с таким номером не существует)
        }
        graph->sm = new int[graph->size+1];
	// —читываем список смежности.
	//
        Number_of_vertexes(in, path);
        for(int i=1;i<graph->size+1;i++){
                if(graph->sm[i]>0){ //если это кол-во больше 0
                        for(int i=0; i<2; i++) fgetc(in); //пропускаем 2 символа
                        delete graph->spisok[i]; //то удал€ем строку списка
                        graph->spisok[i]=new int[graph->sm[i]]; //и добавл€ем новую с необходимым кол-вом вершин
                        for(int j=0;j<graph->sm[i];j++){
                                fscanf(in, "%i", &graph->spisok[i][j]);
                        }
                }
                else continue;
        }
        fclose(in);
	return graph;
}
void show_graph(Graph *graph){ //выводим граф, как список смежности
        int a;
        cout<<"\ngraph:\n"<<endl;
        for(int i=1;i<graph->size+1;i++){ //дл€ каждой вершины
                cout<<i<<"->";
                if(graph->sm[i]==0){
                        cout<<endl;
                        continue;
                }
                for(int j=0;j<graph->sm[i]-1;j++){ //выводим номера смежных ей вершин (до предпоследней включительно)
                        cout<<graph->spisok[i][j]<<" , ";
                }
                a=graph->spisok[i][graph->sm[i]-1];
                cout<<a<<endl; //выводим номер последней смежной данной вершине вершины
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
void Number_of_vertexes(FILE *in, const char *path)//считываем кол-во смежных данным вершинам вершин
{
        int numberofel;
        char a;
        for(int i=1;i<graph->size+1;i++){
        numberofel=0;
        for(int i=0; i<2; i++) fgetc(in); //пропускаем 2 символа
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
 