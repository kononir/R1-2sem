//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <fstream.h>
#include <iostream.h>
#pragma hdrstop
struct Graph {int size; int **spisok; int *sm; int *connection;} *graph1, *graph;
void Delete_graphs(void);
void Check(int);
void Answer(void);
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
        fgetc(in);
        // Считываем имена вершин.
	//

	// Создаем список смежности и массив кол-в смежных вершин.
	//
        graph->spisok = new int*[graph->size+1];
        graph->sm = new int[graph->size+1];

	// Считываем список смежности.
	//
        Number_of_vertexes(in, path);
        for(int i=1;i<graph->size+1;i++){
                if(graph->sm[i]>0){ //если это кол-во больше 0
                        graph->spisok[i]=new int[graph->sm[i]]; //и добавляем новую с необходимым кол-вом вершин
                        for(int j=0;j<graph->sm[i];j++){
                                fscanf(in, "%i", &graph->spisok[i][j]);
                        }
                        fseek(in, sizeof(int), 1); //пропускаем номер вершины, являющимся номером текущей вершины
                }
                else{
                        graph->spisok[i] = new int[1];// все массивы, у которых кол-во смежных вершин равно нулю, получают первый элемент, равный -1 (вершины с таким номером не существует)
                        graph->spisok[i][0] = -1;
                        fseek(in, sizeof(char), 1); //пропускаем номер вершины, являющимся номером текущей вершины
                        continue;
                }
        }
        fclose(in);
	return graph;
}
void show_graph(Graph *graph){ //выводим граф, как список смежности
        int a, b;
        cout<<"\ngraph:\n"<<endl;
        if(graph->size==1 && graph->sm[1]==0){
                cout<<1<<endl;
                return;
        }
        for(int i=1;i<graph->size+1;i++){ //для каждой вершины
                cout<<i<<"->";
                if(graph->sm[i]==0){
                        cout<<endl;
                        continue;
                }
                for(int j=0;j<graph->sm[i]-1;j++){ //выводим номера смежных ей вершин (до предпоследней включительно)
                        b=graph->spisok[i][j];
                        cout<<b<<" , ";
                }
                a=graph->spisok[i][graph->sm[i]-1];
                cout<<a<<endl; //выводим номер последней смежной данной вершине вершины
        }
}
void run_testcase(int number, const char *path){
        int c;
        Graph *graph1;
        graph1=load_graph(path);
        show_graph(graph1);
        Answer();
        Delete_graphs();
}
int main(int argc, char* argv[])
{
        run_testcase(1, "graph1.txt");
	run_testcase(2, "graph2.txt");
	run_testcase(3, "graph3.txt");
	run_testcase(4, "graph4.txt");
	run_testcase(5, "graph5.txt");
        cout<<"\nPress any key...";
        getch();
        return 0;
}
void Number_of_vertexes(FILE *in, const char *path)//считываем кол-во смежных данным вершинам вершин
{
        int numberofel, size, mnoz;
        char a;
        for(int i=1;i<graph->size+1;i++){
        numberofel=0;
        int b=0;
        if(i>=1 && i<=9) mnoz=1;
        if(i>=10 && i<=99) mnoz=2;
        if(i>=100 && i<=999) mnoz=3;
        fseek(in, mnoz*sizeof(char)+1, 1); //пропускаем 2 символа
        M:
                a=fgetc(in);
                for( ;a!=' ' && a!='\n' && a!='я'; b++){
                        a=fgetc(in);
                }
                if(b>0) numberofel++;
                if(a==' ') goto M;
                if(a=='я'){
                        graph->sm[i]=numberofel;
                        continue;
                }
                if(a!='\n'){
                        numberofel++;
                        goto M;
                }
                graph->sm[i]=numberofel;
        }
        fclose(in);
        in=fopen(path, "r");
        fseek(in, (mnoz+3)*sizeof(char), 0);
}
void Delete_graphs()
{
        delete graph1;
        for(int i=1;i<graph->size+1;i++) delete graph->spisok[i];
        delete graph->spisok;
        delete graph->sm;
        delete graph;
}
void Answer()
{
        int answer;
        if(graph->size==0){
                cout<<"\n\t\t\t\tNevernie dannie!"<<endl;
                return;
        }
        for(int i=1;i<graph->size+1;i++){
                if(graph->spisok[i][0]==-1 && graph->size > 1){
                        cout<<"\n\t\t\t\tOtvet:"<<endl<<"\t\t\t    Ne svyzniy graf!"<<endl;
                        return;
                }
                if(graph->spisok[i][0]==-1 && graph->size == 1){
                        cout<<"\n\t\t\t\tOtvet:"<<endl<<"\t\t\t     Svyzniy graf!"<<endl;
                        return;
                }
        }
        graph->connection=new int[graph->size+1];
        graph->connection[1]=1;
        graph->connection[0]=1;
        Check(1);
        if(graph->connection[0]==graph->size){
                cout<<"\n\t\t\t\tOtvet:"<<endl<<"\t\t\t     Svyzniy graf!"<<endl;
                return;
        }
        else{
                cout<<"\n\t\t\t\tOtvet:"<<endl<<"\t\t\t    Ne svyzniy graf!"<<endl;
                return;
        }
}
void Check(int i)
{
int n;
        for(int j=0; j<graph->sm[i]; j++){
                n=0;
                for(int k=1; k<=graph->connection[0]; k++){
                        if(graph->spisok[i][j]!=graph->connection[k]){
                                n++;
                                continue;
                        }
                        break;
                }
                if(n==graph->connection[0]){
                        graph->connection[0]++;
                        graph->connection[graph->connection[0]]=graph->spisok[i][j];
                        Check(graph->spisok[i][j]);
                }
        }
}
//---------------------------------------------------------------------------
