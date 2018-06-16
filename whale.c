#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  arquivo "data.db"
#define  dados "file.db"


int main(int argc, char const *argv[]){
  FILE *PA;
  int i  = 0, c = 2;
  PA = fopen(arquivo,"rb+");if(PA == NULL){fopen(arquivo,"ab+");}
  FILE *Pe;
  Pe = fopen(dados,"rb+");if(Pe == NULL){fopen(dados,"ab+");}

  //esse if testa a existencia do arquivo, caso não exista ele é criado.
//função de cadastro de dados.

void rubiel(){
  FILE *Pe;
  Pe = fopen(dados,"rb+");if(Pe == NULL){fopen(dados,"ab+");}

  char ip[100];
  char conta[100];
  char token[100];
  char telefone[100];
  char telefone_twilio[100];
  char email[100];
  char senha[100];

  printf("Digite seu ip: ");
  gets(ip);
  printf("Digite a sua conta do Twilio: ");
  gets(conta);
  printf("Digite seu token: ");
  gets(token);
  printf("Digite seu telefone: ");
  gets(telefone);
  printf("Digite o seu telefone Twlio: ");
  gets(telefone_twilio);
  printf("Digite o seu email: ");
  gets(email);
  printf("Digite a senha do seu email: ");
  gets(senha);
  fprintf(Pe, "%s\n%s\n%s\n%s\n%s\n%s\n%s",ip,conta,token,telefone,telefone_twilio,email,senha);
  fclose(Pe);
}

//função de menu.

void menu(){
  printf("\n               .-'\n          '--./ /     _.---.\n          '-,  (__..-`       \\\n             \\          .     |\n              `,.__.   ,__.--/\n                '._/_.'___.-`\n            __                 ___              \n           /\\ \\  by_Pysociety /\\_ \\             \n __  __  __\\ \\ \\___       __  \\//\\ \\       __   \n/\\ \\/\\ \\/\\ \\\\ \\  _ `\\   /'__`\\  \\ \\ \\    /'__`\\ \n\\ \\ \\_/ \\_/ \\\\ \\ \\ \\ \\ /\\ \\L\\.\\_ \\_\\ \\_ /\\  __/ \n \\ \\___x___/' \\ \\_\\ \\_\\\\ \\__/.\\_\\/\\____\\\\ \\____\\\n  \\/__//__/    \\/_/\\/_/ \\/__/\\/_/\\/____/ \\/____/\n\n=== Dev: Daniel Carvalho, Daniel Martins, Kaio Prates ===\n=======================jun/18============================\n\nBem vindo ao While:\n\n*Para adicionar dados ao arquivo use o esquema:\n \n./whale -a d01m01tmafl0\n            \n                      data:  dia = d01                                 \n                             mes = m01\n                  turnos:\n                             manha = tma\n                             tarde = tta\n                             noite = tno\n                  flags:\n                             ativado = fl1\n                             desativado = fl0\n\n*Para pesquisar dados do arquivo use o esquema:\n           ./whale -p d01 m01\n\n*Para deletar todo o arquivo:\n           ./whale -d\n\n*Para excluir um dado:\n           ./whale -e d01 m01\n\n*Para substituir um arquivo:\n           ./whale -n d01m01tmafl0 d02m02tnofl1\n\n*Para imprimir uma determinada quantidade de arquivos:\n           ./whale -q número de arquivos\n\n*Para criar um banco de dados:\n           ./whale -c \n\n*Para pesquisar o numero total de dias gravados:\n           ./whale -?\n\n*Para pesquisar o numero de acionamentos em um determinado mes:\n           ./whale -t mês\n\n*Para numero de acionamentos por mês e estatísticas:\n           ./whale -m  \n\n*Para ver o Ranking por turnos:\n           .whale -r \n\n*Para cadastro de novo usuário\n              ./whale -u \n\n*Para esta tela:\n           ./whale -h \n\n===============================================================\nCopyright (c) 2018 DeltreeC: Software Foundation.\nAll Rights Reserved.\n===============================================================\n");
}
//função de criação.
void create(){
  fopen(arquivo,"wb+");
}
  //função de append,

  void append(){
    fseek(PA,0,SEEK_END);//aponta o ponteiro para o fim do arquivo.
    while(!i){//aqui tem uma gambiarra, esse i é um flag que recebe 1 caso arqv seja nulo, ou seja no fim da frase.
      if(argv[c] != NULL){//aqui vamos gravar palavra por palavra.
        fprintf(PA, "%s",argv[c]);}
             else{i++;}
             c++;}
             }//aqui printamos o \n so para dar a quebra de linha ao receber a proxima frase.
    //essa função imprime x numeros a partir da posição atual do ponteiro. é a função que vamos usar para printar as pesquisas.
    void put(int x){
      char pesq[1];
      for(int i = 0; i < x; i ++){fread(&pesq,sizeof(char)*1,1,PA);printf("%s",pesq);}
      printf("\n");
    }
    //função para imprimir um numero determinado de dados.
    void putf(){
      char pesq[1];
      int x = atoi(argv[2])*12;
      int d = 0;
      for(int i = 0; i < x; i ++){
        fread(&pesq,sizeof(char)*1,1,PA);printf("%s",pesq);
        d++;
        if(d == 12){printf("\n");d=0;}
      }
      printf("\n");
    }

    //função de pesquisa -- teste -- agora recebe dia e mes exemplo ./programa -p d01 m01
    void query(){
      rewind(PA);
      char pesq[6];
      strcat(argv[2],argv[3]);
      strcpy(pesq,argv[2]);

      while(!feof(PA)){
        char aux[6];
        fread(&aux,sizeof(char)*6,1,PA);
        if(!strcmp(pesq,aux)){put(6);}
      }
    }

    //função exclusão --- testes --- funciona agora da mesma forma da pesquisa com dia e mes.
    void exclu(){
      rewind(PA);
      char pesq[6];
      strcat(argv[2],argv[3]);
      strcpy(pesq,argv[2]);
      while(!feof(PA)){
        char aux[6];
        fread(&aux,sizeof(char)*6,1,PA);
        if(!strcmp(pesq,aux)){fprintf(PA,"000000");break;}
      }
    }

    //função de alteração de dados, entrada: ./programa -n [data antiga] [data nova], ./programa -n d01m01tnofl0 d02m02tnofl2
    void alter(){
      rewind(PA);
      char pesq[12];
      char new[12];

      strcpy(pesq,argv[2]);
      strcpy(new,argv[3]);

      while(!feof(PA)){
        char aux[12];
        fread(&aux,sizeof(char)*12,1,PA);
        if(!strcmp(pesq,aux)){
          printf("--sucess--\n");
          fseek(PA,-sizeof(char)*12,SEEK_CUR);
          fprintf(PA,"%s",new);
          break;}
      }

    }





//função delete, recebe so um argumento ./programa -d

void delete(){remove("data.db");}

//função que conta o numero de itens no banco de dados

void cont(){
  rewind(PA);
  int d = 0;
  while(!feof(PA)){
    char aux[12];
    fread(&aux,sizeof(char)*12,1,PA);
    d++;
    }
    printf("---Total de itens %d ---\n",d);
  }
//função para pesquisa de indices de ativação em um mes
void cturn(){
    rewind(PA);
    char turn[3];
    strcpy(turn,argv[2]);
    int d = 0;
    if(!strcmp(turn,"m01")){printf("--- Janeiro ---\n");}
    if(!strcmp(turn,"m02")){printf("--- Fevereiro ---\n");}
    if(!strcmp(turn,"m03")){printf("--- Março ---\n");}
    if(!strcmp(turn,"m04")){printf("--- Abril ---\n");}
    if(!strcmp(turn,"m05")){printf("--- Maio ---\n");}
    if(!strcmp(turn,"m06")){printf("--- Junho ---\n");}
    if(!strcmp(turn,"m07")){printf("--- Julho ---\n");}
    if(!strcmp(turn,"m08")){printf("--- Agosto ---\n");}
    if(!strcmp(turn,"m09")){printf("--- Setembro ---\n");}
    if(!strcmp(turn,"m10")){printf("--- Outubro ---\n");}
    if(!strcmp(turn,"m11")){printf("--- Novembro ---\n");}
    if(!strcmp(turn,"m12")){printf("--- Dezembro ---\n");}
    while(!feof(PA)){
      char x[3];
      fread(&x,sizeof(char)*3,1,PA);
      if(!strcmp(x,turn)){
        fseek(PA,sizeof(char)*3,SEEK_CUR);
        fread(&x,sizeof(char)*3,1,PA);
        if(!strcmp(x,"fl1")){d++;}
      }
      }
      printf("--- total de acionamentos: %d\n",d);
    }

//rank pelo acionamento no turno
void rank(){
int index[3]={0,0,0};
    int pos[3]={1,2,3};
    char *shift[]={"tma","tta","tno"};
    char *shif[]={"Manha","Tarde","Noite"};
    for(int i = 0; i < 3;i++){
    char turno[3];
    rewind(PA);
    strcpy(turno,shift[i]);
    int e = 0;
    if(!strcmp(turno,"tma")){printf("\t--- Manha ");}
    if(!strcmp(turno,"tta")){printf("\t--- Tarde ");}
    if(!strcmp(turno,"tno")){printf("\t--- Noite ");}

    while(!feof(PA)){
      char x[3];
      fread(&x,sizeof(char)*3,1,PA);
      if(!strcmp(x,turno)){
        //fseek(PA,sizeof(char)*3,SEEK_CUR);
        fread(&x,sizeof(char)*3,1,PA);
        if(!strcmp(x,"fl1")){e++;}
      }
      }
      printf("--- total de acionamentos: %d\n",e);
      index[i]=e;
    }
    //ordenando os turnos.
    for(int i=3;i>0;i--){
      for(int j = i-1; j > 0;j--){
        int aux;
        if(index[i]>index[j]){
          aux = index[i];
          index[i] = index[j];
          index[j]=aux;
          aux = pos[i];
          pos[i]=pos[j];
          pos[j]=aux;
        }
      }
    }
    printf("\n\tOs Turnos com mais incidência de alarmes foram:\n\t %s, %s, %s\n",shif[pos[0]],shif[pos[1]],shif[pos[2]]);
    }



// pesquisa em todos os meses
void pmes(){
    int index[12]={0,0,0,0,0,0,0,0,0,0,0,0};
    int pos[12]={1,2,3,4,5,6,7,8,9,10,11,12};
    char *mes[]={"m01","m02","m03","m04","m05","m06","m07","m08","m09","m10","m11","m12"};
    char *mesm[]={"Janeiro","Fevereiro","Março","Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};
    for(int i = 0; i < 12;i++){
    char turn[3];
    rewind(PA);
    strcpy(turn,mes[i]);
    int e = 0;
    if(!strcmp(turn,"m01")){printf("\t--- Janeiro ");}
    if(!strcmp(turn,"m02")){printf("\t--- Fevereiro ");}
    if(!strcmp(turn,"m03")){printf("\t--- Março ");}
    if(!strcmp(turn,"m04")){printf("\t--- Abril ");}
    if(!strcmp(turn,"m05")){printf("\t--- Maio ");}
    if(!strcmp(turn,"m06")){printf("\t--- Junho ");}
    if(!strcmp(turn,"m07")){printf("\t--- Julho ");}
    if(!strcmp(turn,"m08")){printf("\t--- Agosto ");}
    if(!strcmp(turn,"m09")){printf("\t--- Setembro ");}
    if(!strcmp(turn,"m10")){printf("\t--- Outubro ");}
    if(!strcmp(turn,"m11")){printf("\t--- Novembro ");}
    if(!strcmp(turn,"m12")){printf("\t--- Dezembro ");}
    while(!feof(PA)){
      char x[3];
      fread(&x,sizeof(char)*3,1,PA);
      if(!strcmp(x,turn)){
        fseek(PA,sizeof(char)*3,SEEK_CUR);
        fread(&x,sizeof(char)*3,1,PA);
        if(!strcmp(x,"fl1")){e++;}
      }
      }
      printf("--- total de acionamentos: %d\n",e);
      index[i]=e;
    }
    //ordenando os meses.
    for(int i=12;i>0;i--){
      for(int j = i-1; j > 0;j--){
        int aux;
        if(index[i]>index[j]){
          aux = index[i];
          index[i] = index[j];
          index[j]=aux;
          aux = pos[i];
          pos[i]=pos[j];
          pos[j]=aux;
        }
      }
    }
    printf("\n\tOs meses com mais incidência de alarmes foram:\n\t %s, %s, %s\n",mesm[pos[1]-1],mesm[pos[2]-1],mesm[pos[3]-1]);
    }

  //escolha das funções
  char opc[2];
  int op;
  strcpy(opc,argv[1]);
  if(strcmp(opc,"-a")==0){op = 1;}
  if(strcmp(opc,"-p")==0){op = 2;}
  if(strcmp(opc,"-d")==0){op = 3;}
  if(strcmp(opc,"-e")==0){op = 4;}
  if(strcmp(opc,"-n")==0){op = 5;}
  if(strcmp(opc,"-h")==0){op = 6;}
  if(strcmp(opc,"-c")==0){op = 7;}
  if(strcmp(opc,"-q")==0){op = 8;}
  if(strcmp(opc,"-?")==0){op = 9;}
  if(strcmp(opc,"-t")==0){op = 10;}
  if(strcmp(opc,"-m")==0){op = 11;}
  if(strcmp(opc,"-r")==0){op = 12;}
  if(strcmp(opc,"-u")==0){op = 13;}

  switch (op) {
    case 1:
    append();
    break;
    case 2:
    query();
    break;
    case 3:
    delete();
    break;
    case 4:
    exclu();
    break;
    case 5:
    alter();
    break;
    case 6:
    menu();
    break;
    case 7:
    create();
    break;
    case 8:
    putf();
    break;
    case 9:
    cont();
    break;
    case 10:
    cturn();
    break;
    case 11:
    pmes();
    break;
    case 12:
    rank();
    break;
    case 13:
    rubiel();
    break;
  }
  fclose(Pe);
  fclose(PA);
  return 0;
}
