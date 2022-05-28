#include<stdio.h>
#include <stdlib.h>
#include<string.h>
//结构体部分
typedef struct node
{
    char instruction[20];//请求类型
    int station;//请求的车站
    int clock;//请求发出的时间
    int direction;//请求要求的方向，0顺时针1逆时针
    struct node *next;
}Node;
typedef struct _indication
{
    char *instruction;
    int x;
}indication;
//全局变量部分
int time=0;
int curPos=0;
int direct=2;
int length=30;
//定义函数部分
Node *create (Node* head, char* instruction); //建立链表
int search(Node *head, char* instruction,int x);//遍历链表查找是否为重复指令
Node* addlist(Node *head,char *instruction,int x);//将指令添加至链表
Node* delete_instruction(Node *head,Node *node_delete);//指令完成后从链表删除指令
Node* judge(Node*head);//判断两个请求是否可以同时完成
Node* fcfs(Node* head,int distance);//先来先服务算法
indication get_order();

int main() //主函数只负责判断指令为clock或其它，若是clock表示时间推移，调用fcfs函数执行指令；若不是clock指令，说明时间没有变化，不处理指令，不改变状态，只向链表中添加指令作为节点。
{
    int total=10;//总站点数
    int distance=3;//站间距离
    int target=0;//目标站点指令
    int counterclockwise=0,clockwise=0;
    printf("Time:0\n");
    printf("BUS:\n");
    printf("position:0\n");
    Node *head=NULL;
    char* instruction ;
    instruction=(char*)malloc(100);
    head=create(head,instruction);
    //按行读入指令
    indication request = get_order();
    //printf("%s, %d\n", request.instruction, request.x);//测试用
    while(strcmp(request.instruction,"end")!=0)
    {
        //get_order();//读取指令函数
        if(strcmp(request.instruction,"clock")==0) //时间推移指令，进行指令处理
        {
            time++;
            head=fcfs(head,distance);
            //printf("%s, %d", request.instruction, request.x);

        }
        else//否则添加指令到链表
        {
            if(search(head,request.instruction,request.x)==0)
            {
                //遍历链表，如果没有相同节点，证明为新请求，将其添加到链表中，否则为重复请求，舍去；
                head= addlist(head,request.instruction,request.x);//添加指令节点
            }
        }
        request=get_order();
    }
}
Node *create (Node* head, char* instruction)
{
    //current：每次生成新节点
    Node* current;
    Node* tmp;
    current=(Node *)malloc(sizeof(Node));
    strcpy(current->instruction,instruction);
    current->next=NULL;
    if(head==NULL)
    {
        head=head;
    }
    else
    {
        tmp=head;//初始化头节点
        while(tmp->next!=NULL)
        {
            tmp=tmp->next;//从头开始遍历列表，找到列表尾巴停止
        }
        tmp->next=current;//把原来链表的尾部和新建立的current连起来
    }
    return head;
}
int search(Node *head, char* instruction,int x)
{
    int flag=0;
    if(head!=NULL)
    {
        Node* tmp;
        tmp=head;
        while(tmp!=NULL)
        {
            if(strcmp(tmp->instruction,instruction)==0&&tmp->station==x)
            {
                flag=1;
            }
            else
            {
                tmp=tmp->next;
            }
        }
    }
    return flag;
}
Node* addlist(Node *head,char *instruction,int x)//尾插法
{
    Node* newNode;
    strcpy(newNode->instruction,instruction);
    newNode->station=x;
    if(head==NULL)
    {
        head=newNode;
    }
    else
    {
        Node *tmp;
        tmp=head;
        while (tmp->next != NULL)
        {
            tmp=tmp->next;//找到最后一个节点
        }
        tmp->next = newNode;
        newNode->next = NULL;
    }

    return head;
}
Node* delete_instruction(Node*head,Node *node_delete)
{
    Node *previous;
    previous==NULL;
    Node *current=head;
    if(head==NULL)
    {
        printf("链表空");
    }
    while(current!=NULL&&current!=node_delete)
    {
        previous=current;
        current=current->next;
    }
    if(current==node_delete)
    {
        if(current==head)//删除头结点情况
        {
            head=current->next;
        }
        else//删除的非头结点
        {
            previous->next=current->next;
        }
    }
    else
    {
        printf("没有找到要删除的节点");
    }
    return head;
}
Node* judge(Node*head) //该函数用来判断两个请求是否可以同时执行
{
    struct node *prior;
    prior=head;
    head=head->next;
    if((head->clock==prior->clock)&&(head->station==prior->station))
    {
        //顺、逆同时同地出现的特殊情况：
        if((prior->instruction=="clockwise"&&head->instruction=="counterclockwise")|| (prior->instruction=="counterclockwise"&&head->instruction=="clockwise"))
        {
            head=delete_instruction(prior,head);//选择执行前一个指令，删除后一个指令
            time++;
        }
            //正常情况，前后指令可以同时执行，在执行完前一个指令时时间不增加，到执行下一个指令时再time++
        else
        {
            head=delete_instruction(prior,prior);//执行完毕，删除该节点
        }
    }
    else//前后指令需要分开执行
    {
        head=delete_instruction(prior,prior);//执行完毕，删除该节点
        time++;
    }
    return head;
}
Node* fcfs(Node* head,int distance)//该函数为按照先来先服务算法进行指令顺序执行
{
    /*if(head==NULL)
    {
        printf("TIME:%d\n",time);
        printf("BUS:");
        printf("position:%d\n",curPos);
    }*/
    if(head!=NULL)
    {
        //printf("TIME:%d\n",time);
        //printf("BUS:");
        //printf("position:%d\n",curPos);

        //有未完成指令时执行(head->instruction):
        //先判断状态：
        if(direct==2)//停止状态
        {
            //从停止开始遇到某站点顺/逆时针请求，按最近的路线（顺、逆时针）去接（送）
            if(strcmp(head->instruction,"clockwise")==0)//排在第一的为顺时针指令
            {
                if((head->station-1)*distance==curPos) //请求在当前位置发出
                {
                    direct=0;//开始顺时针出发
                    //head= judge(head);
                }
                else//请求不在当前站点
                {
                    if((curPos - ((head->station-1)*distance)) < ((head->station-1)*distance + length -curPos))//发送请求的位置距离当前位置顺时针距离更短
                    {
                        direct=0;  //顺时针走
                        curPos++;
                    }
                    else if((curPos - ((head->station-1)*distance)) > ((head->station-1)*distance + length -curPos))
                    {
                        direct=1;//逆时针走
                        curPos--;
                    }
                }
            }
            else if(strcmp(head->instruction,"counterclockwise")==0)//排在第一的为逆时针指令
            {
                if(head->station*distance==curPos)
                {
                    direct=1;//开始逆时针出发
                    //head=judge(head);
                }
                else
                {
                    if((head->station*distance-curPos)<=(curPos-head->station*distance+10))
                    {
                        direct=0;  //顺时针走
                        curPos++;
                    }
                    else if((head->station*distance-curPos)>(curPos-head->station*distance+10))
                    {
                        direct=1;//逆时针走
                        curPos--;
                    }
                }

            }
            else if (strcmp(head->instruction,"target")==0)//排在第一的为target指令
            {
                if(head->station*distance==curPos)
                {
                    direct=1;//开始逆时针出发
                    //head=judge(head);
                }
                else
                {
                    if((head->station*distance-curPos)<=(curPos-head->station*distance+10))
                    {
                        direct=0;  //顺时针走
                        curPos++;
                    }
                    else if((head->station*distance-curPos)>(curPos-head->station*distance+10))
                    {
                        direct=1;//逆时针走
                        curPos--;
                    }
                    else //如果请求在当前站点发生
                    {
                        direct=2;//继续停止
                        //head=judge(head);
                    }
                }
            }
        }
        else if(direct==0)//顺时针行进状态
        {
            curPos++;
            if((head->station-1)*distance==curPos)
            {	//对于先来先服务策略，车一次停站只完成一个请求，即使在这个站点上即有乘车请求，
                //车内也有到该站的请求也只能按算法完成其中的一个。但是如果下一个请求恰好在同一站点，则可以一次停站完成2个或2个以上的请求。
                //也就是说只停1秒完成多个请求。
                direct=2;
                time++;
                if(strcmp(head->instruction,"target")==0)
                {
                    direct=0;
                }
                else if(strcmp(head->instruction,"clockwise")==0)
                {
                    direct=0;
                }
                else if(strcmp(head->instruction,"counterclockwise")==0)
                {
                    direct=1;
                }
                //head=judge(head);
                head=delete_instruction(head,head);
            }

            else if(direct==1) //逆时针行进状态
            {
                curPos--;
                if((head->station-1)*distance==curPos)
                {
                    direct=2;
                    if(strcmp(head->instruction,"target")==0)
                    {
                        direct=1;
                    }
                    else if(strcmp(head->instruction,"clockwise")==0)
                    {
                        direct=0;
                    }
                    else if(strcmp(head->instruction,"counterclockwise")==0)
                    {
                        direct=1;
                    }
                    //head=judge(head);
                    head=delete_instruction(head,head);
                }
            }
        }
    }
//printf("%d %d\n",curPos,time);
    return head;
}
indication get_order()
{
    char str[200];
    gets(str);
    const char s[2] = " ";
    char *token;
    indication request;

    /* 获取第一个子字符串 */
    if(str=="clock")
    {
        strcpy(token,str);
    }
    else
    {
        token = strtok(str, s);
    }
    request.instruction = token;//此instruction即为终端输入的请求的类型
    if(strcmp(request.instruction, "clock") == 0){
        request.x = -1;
    }
    else{
        /* 继续获取其他的子字符串 */
        token = strtok(NULL, s);
        request.x= atoi (token);//此x即为请求发出的站点
    }

    return request;
}


////#include "csapp.h"
//#include <stdio.h>
//
//int main(){
//
//    printf("Hello World!\n");
//
//    return 0;
//}

