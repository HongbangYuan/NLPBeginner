#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<malloc.h>

typedef struct instruction_node
{
    char instruction[20];
    char instruction_name[20];
    int instruction_num;
    struct instruction_node *next;
}linklist;

int main(){

    int TOTAL_STATION = 10;
    int DISTANCE = 2;
    char STRATEGY[20] = "FCFS";

    int i;
    int time=0;
    int position=0;
    char target[15]={0};
    char clockwise[15]={0};
    char counterclockwise[15]={0};
    char instruction[30]={0};
    char direction[30]="static_direction";
    char current_instruction[30]={0};
    char current_instruction_name[30]={0};
    int current_instruction_num;
    int current_instruction_loc;
    char instruction_name[30]={0};
    char instruction_num_str[30]={0};
    int instruction_num_int;
    int name_index=0;
    int num_index=0;
    int flag=0;
    linklist* head;
    linklist* p;
    linklist* r;

    for(i=0;i<=TOTAL_STATION-1;i++){
        target[i]='0';
        clockwise[i]='0';
        counterclockwise[i]='0';
    }

    printf("Time:%d\n",time);
    printf("BUS:\n");
    printf("position:%d\n",position);
    printf("target:%s\n",target);
    printf("STATION:\n");
    printf("clockwise:%s\n",clockwise);
    printf("counterclockwise:%s\n",counterclockwise);

    head=(linklist*)malloc(sizeof(linklist));
    head->next=NULL;
    r=head;

    gets(instruction);

    while(strcmp(instruction,"end")!=0){

        if(strcmp(instruction,"clock")==0){

            time=time+1;

            if(strcmp(current_instruction,"")==0){
                if(head->next!=NULL){
                    strcpy(current_instruction,head->next->instruction);
                    strcpy(current_instruction_name,head->next->instruction_name);
                    current_instruction_num=head->next->instruction_num;
                    current_instruction_loc=(head->next->instruction_num-1)*DISTANCE;

                    if(TOTAL_STATION*DISTANCE%2==1){
                        if(position>=0 && position<=TOTAL_STATION*DISTANCE/2){
                            if(current_instruction_loc<=(position+TOTAL_STATION*DISTANCE/2) && current_instruction_loc>=position){
                                strcpy(direction,"clockwise");
                            }
                            else{
                                strcpy(direction,"counterclockwise");
                            }
                        }
                        else{
                            if(current_instruction_loc>=(position-TOTAL_STATION*DISTANCE/2) && current_instruction_loc<=position){
                                strcpy(direction,"counterclockwise");
                            }
                            else{
                                strcpy(direction,"clockwise");
                            }


                        }
                    }

                    if(TOTAL_STATION*DISTANCE%2==0){
                        if(position>=0 && position<TOTAL_STATION*DISTANCE/2){
                            if(current_instruction_loc<=(position+TOTAL_STATION*DISTANCE/2) && current_instruction_loc>=position){
                                strcpy(direction,"clockwise");
                            }
                            else{
                                strcpy(direction,"counterclockwise");
                            }
                        }
                        else{
                            if(current_instruction_loc>=(position-TOTAL_STATION*DISTANCE/2) && current_instruction_loc<=position){
                                strcpy(direction,"counterclockwise");
                            }
                            else{
                                strcpy(direction,"clockwise");
                            }


                        }
                    }
                }
            }

            if(strcmp(current_instruction_name,"clockwise")==0 && head->next!=NULL){
                if(position!=current_instruction_loc){
                    if(strcmp(direction,"clockwise")==0){
                        position=position+1;
                        position=(position+TOTAL_STATION*DISTANCE)%(TOTAL_STATION*DISTANCE);
                    }
                    else{
                        position=position-1;
                        position=(position+TOTAL_STATION*DISTANCE)%(TOTAL_STATION*DISTANCE);
                    }
                }
                else{
                    clockwise[current_instruction_num-1]='0';
                    memset(current_instruction, 0x00, sizeof (char) * 30);
                    memset(current_instruction_name, 0x00, sizeof (char) * 30);
                    strcpy(direction,"static_direction");
                    current_instruction_num=-1;
                    current_instruction_loc=-1;
                    head=head->next;
                }
            }




            if(strcmp(current_instruction_name,"counterclockwise")==0 && head->next!=NULL){
                if(position!=current_instruction_loc){
                    if(strcmp(direction,"clockwise")==0){
                        position=position+1;
                        position=(position+TOTAL_STATION*DISTANCE)%(TOTAL_STATION*DISTANCE);
                    }
                    else{
                        position=position-1;
                        position=(position+TOTAL_STATION*DISTANCE)%(TOTAL_STATION*DISTANCE);
                    }
                }
                else{
                    counterclockwise[current_instruction_num-1]='0';
                    memset(current_instruction, 0x00, sizeof (char) * 30);
                    memset(current_instruction_name, 0x00, sizeof (char) * 30);
                    strcpy(direction,"static_direction");
                    current_instruction_num=-1;
                    current_instruction_loc=-1;
                    head=head->next;
                }
            }




            if(strcmp(current_instruction_name,"target" )==0 && head->next!=NULL){
                if(position!=current_instruction_loc){
                    if(strcmp(direction,"clockwise")==0){
                        position=position+1;
                        position=(position+TOTAL_STATION*DISTANCE)%(TOTAL_STATION*DISTANCE);
                    }

                    if(strcmp(direction,"counterclockwise")==0){
                        position=position-1;
                        position=(position+TOTAL_STATION*DISTANCE)%(TOTAL_STATION*DISTANCE);
                    }
                }
                else{
                    target[current_instruction_num-1]='0';
                    memset(current_instruction, 0x00, sizeof (char) * 30);
                    memset(current_instruction_name, 0x00, sizeof (char) * 30);
                    strcpy(direction,"static_direction");
                    current_instruction_num=-1;
                    current_instruction_loc=-1;
                    head=head->next;
                }
            }



            printf("Time:%d\n",time);
            printf("BUS:\n");
            printf("position:%d\n",position);
            printf("target:%s\n",target);
            printf("STATION:\n");
            printf("clockwise:%s\n",clockwise);
            printf("counterclockwise:%s\n",counterclockwise);

        }
        else{
            memset(instruction_name, 0x00, sizeof (char) * 30);
            memset(instruction_num_str, 0x00, sizeof (char) * 30);
            instruction_num_int=0;
            name_index=0;
            num_index=0;
            flag=0;

            for(i=0;i<=29;i++){
                if(instruction[i]!='\0'){
                    if(instruction[i]==' '){
                        flag=1;
                    }
                    if(flag==0){
                        instruction_name[name_index]=instruction[i];
                        name_index=name_index+1;
                    }
                    else{
                        instruction_num_str[num_index]=instruction[i];
                        num_index=num_index+1;
                    }
                }
                else{
                    break;
                }
            }
            instruction_num_int =atoi(instruction_num_str);

            if(strcmp(instruction_name,"target")==0){
                target[instruction_num_int-1]='1';
            }

            if(strcmp(instruction_name,"clockwise")==0){
                clockwise[instruction_num_int-1]='1';
            }

            if(strcmp(instruction_name,"counterclockwise")==0){
                counterclockwise[instruction_num_int-1]='1';
            }

            p=(linklist*)malloc(sizeof(linklist));
            strcpy(p->instruction,instruction);
            strcpy(p->instruction_name,instruction_name);
            p->instruction_num=instruction_num_int;
            r->next=p;
            r=p;
            r->next=NULL;

        }




        gets(instruction);
    }


}