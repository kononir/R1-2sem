//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
struct Graph {int size; int **spisok; int *sm;} *graph1;
Graph *load_graph(const char *path)
{
	FILE *in = fopen(path, "r");
	if (!in) {
		printf("Error: Cannot open file '%s'.\n", path);
		exit(1);
	}

	Graph *graph = new Graph;

	// Считываем количество вершин.
	//
	fscanf(in, "%d", &graph->size);

	// Вместо имён вершин - числа.

	// Создаем список смежности.
	//
        graph->spisok = new int*[graph->size];
        for(int i=0;i<graph->size;i++){
                graph->spisok[i] = new int[1];
                graph->spisok[i][0] = -1; // все массивы получают первый элемент, равный -1 (вершины с таким номером не существует)
        }
        graph->sm = new int[graph->size];
	// Считываем список смежности.
	//
        int numberofel;
        for(int i=0;i<graph->size;i++){
                fscanf(in, "%d", &numberofel); //считываем кол-во смежных данной вершине вершин
                graph->sm[i]=numberofel;
                if(numberofel>0){ //если это кол-во больше 0
                        delete graph->spisok[i]; //то удаляем строку списка
                        graph->spisok[i]=new int[numberofel]; //и добавляем новую с необходимым кол-вом вершин
                        for(int j=0;j<numberofel;j++){
                                fscanf(in, "%d", &graph->spisok[i][j]);
                        }
                }
                else continue;
        }
	return graph;
}
void show_graph(Graph *graph){ //выводим граф, как список смежности
        cout<<"\ngraph:\n"<<endl;
        for(int i=0;i<graph->size;i++){ //для каждой вершины
                cout<<i+1<<"->";
                for(int j=0;j<graph->sm[i]-1;j++){ //выводим номера смежных ей вершин (до предпоследней включительно)
                        cout<<graph->spisok[i][j]+1<<" , ";
                }
                cout<<graph->spisok[i][graph->sm[i]-1]+1<<"\n\n"; //выводим номер последней смежной данной вершине вершины
        }
}
void run_testcase(int number, const char *path){
        int c;
        Graph *graph1;
        graph1=load_graph(path);
        show_graph(graph1);
        for(int i=0;i<graph1->size;i++){
                if(graph1->spisok[i][0]==-1){
                        cout<<"Otvet:"<<endl<<"Ne svyzniy graf!"<<endl;
                        return;
                }
        }
        cout<<"Otvet:"<<endl<<"Svyzniy graf!"<<endl;
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
//---------------------------------------------------------------------------
 