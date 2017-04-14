//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <fstream.h>
#include <iostream.h>
#pragma hdrstop
struct Graph {int size; int **spisok; char **names; int *sm;} *graph1, *graph;
void Delete_graphs(void);
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

	// Считываем количество вершин.
	//
	fscanf(in, "%d", &graph->size);

        // Считываем имена вершин.
	//
	graph->names = new char*[graph->size];
	for(int i=1;i<graph->size+1;i++){
		char buf[2];
		fscanf(in, "%s", buf);
		graph->names[i] = strdup(buf);
                cout<<graph->names[i];
	}

	// Создаем список смежности и массив кол-в смежных вершин.
	//
        graph->spisok = new int*[graph->size+1];
        graph->sm = new int[graph->size+1];

	// Считываем список смежности.
	//
        Number_of_vertexes(in, path);
        for(int i=1;i<graph->size+1;i++){
                for(int i=0; i<2; i++) fgetc(in); //пропускаем 2 символа
                if(graph->sm[i]>0){ //если это кол-во больше 0
                        graph->spisok[i]=new int[graph->sm[i]]; //и добавляем новую с необходимым кол-вом вершин
                        for(int j=0;j<graph->sm[i];j++){
                                fscanf(in, "%i", &graph->spisok[i][j]);
                                cout<<graph->spisok[i][j];
                        }
                }
                else{
                        graph->spisok[i] = new int[1];// все массивы, у которых кол-во смежных вершин равно нулю, получают первый элемент, равный -1 (вершины с таким номером не существует)
                        graph->spisok[i][0] = -1;
                        continue;
                }
        }
        fclose(in);
	return graph;
}
void show_graph(Graph *graph){ //выводим граф, как список смежности
        int a, b;
        cout<<"\ngraph:\n"<<endl;
        for(int i=1;i<graph->size+1;i++){ //для каждой вершины
                cout<<graph->names[i][0]<<"->";
                if(graph->sm[i]==0){
                        cout<<endl;
                        continue;
                }
                for(int j=0;j<graph->sm[i]-1;j++){ //выводим номера смежных ей вершин (до предпоследней включительно)
                        b=graph->spisok[i][j];
                        cout<<graph->names[b][0]<<" , ";
                }
                a=graph->spisok[i][graph->sm[i]-1];
                cout<<graph->names[a][0]<<endl; //выводим номер последней смежной данной вершине вершины
        }
}
void run_testcase(int number, const char *path){
        int c, num=0;
        Graph *graph1;
        graph1=load_graph(path);
        show_graph(graph1);
        if(graph1->size==0){
                cout<<"Nevernie dannie!"<<endl;
                Delete_graphs();
                return;
        }
        for(int i=1;i<graph1->size+1;i++){
                if(graph1->spisok[i][0]==-1){
                        cout<<"\nOtvet:"<<endl<<"Ne svyzniy graf!"<<endl;
                        Delete_graphs();
                        return;
                }
                else num++;
        }
        if(num==graph1->size){
                cout<<"Otvet:"<<endl<<"Svyzniy graf!"<<endl;
                Delete_graphs();
                return;
        }
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
        int numberofel, size;
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
        size=sizeof(int)+((graph->size)*(sizeof(char))*2)+2; //+1 - т.к.
        fseek(in, size, 0);
}
void Delete_graphs()
{
        delete graph1;
        for(int i=1;i<graph->size+1;i++){
                delete graph->names[i];
                delete graph->spisok[i];
        }
        delete graph->names;
        delete graph->spisok;
        delete graph->sm;
        delete graph;
}
//---------------------------------------------------------------------------
 