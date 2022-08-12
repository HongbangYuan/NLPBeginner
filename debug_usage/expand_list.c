#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
//二叉树链式存储结构
typedef struct Node
{
    char data;
    struct Node *Lchild;
    struct Node *Rchild;
}TreeNode;
//递归算法：
void Preorder(TreeNode *T);//先序遍历
void Inorder(TreeNode *T);//中序遍历
void Postorder(TreeNode *T); //后序遍历

int flag=0;

void CreatePreorder(TreeNode *T)//先序遍历创建
{
    char ch;
    scanf("%c",&ch);
    if(ch == '#' | ch == '\n') {
        flag =1;
        T = NULL;
    }
    else
    {
        T = malloc(sizeof(TreeNode));
        T->data = ch;
        if (flag!=1){
            CreatePreorder(T->Lchild);
        }
        if (flag!=1){
            CreatePreorder(T->Rchild);
        }
    }
    return;
}
void Preorder(TreeNode *T)
{
    if(T!=NULL)//根左右
    {
        printf("%c ",T->data);//先访问根
        // 再递归左右
        Preorder(T->Lchild) ;
        Preorder(T->Rchild);
    }
}
void Inorder(TreeNode *T)
{
    if(T!=NULL)//左根右
    {
        Inorder(T->Lchild);
        printf("%c ",T->data);
        Inorder(T->Rchild);
    }
}
void Postorder(TreeNode *T)
{
    if(T!=NULL)//左右根
    {
        Postorder(T->Lchild);
        Postorder(T->Rchild);
        printf("%c ",T->data);
    }
}

int main()
{
    TreeNode *T;
    T = malloc(sizeof(TreeNode));
    CreatePreorder(T);
    Preorder(T);
    printf("\n");
    Inorder(T);
    printf("\n");
    Postorder(T);
}
