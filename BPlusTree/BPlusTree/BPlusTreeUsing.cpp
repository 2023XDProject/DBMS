/*
* 此文件附加未来可能在文件系统中要中用到的关于b+树的插入删除查找等等方法的使用
* 不过好像文件系统到b+树索引还需要做一些工作
* 我问了xyh 他说的很模糊 感觉也没有解释的很明白b+树在数据库里面到底怎么调用 “反正就是这么用上了”——xyh （）
*/



#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "BPlusTree.h"


// 随机建立一棵树
void Test1(BPlusTree* pTree, int count)
{
    pTree->ClearTree();

    //srand( (unsigned)time( NULL ) );//应该也不需要随机创建一棵树？？？
    for (int i = 0; i < count; i++)
    {
        int x = rand() % 999 + 1;
        (void)pTree->Insert(x);
    }

    printf("successed!\n");
}

// 在树中查找某数据
void Test2(BPlusTree* pTree, int data)
{
    char sPath[255] = { 0, };

    (void)pTree->Search(data, sPath);
    printf("\n%s", sPath);
}

// 在树中插入某数据
void Test3(BPlusTree* pTree, int data)
{
    bool success = pTree->Insert(data);
    if (true == success)
    {
        printf("\nsuccessed!\n");
    }
    else
    {
        printf("\nfailed!\n");
    }
}

// 在树中删除某数据
void Test4(BPlusTree* pTree, int data)
{
    bool success = pTree->Delete(data);
    if (true == success)
    {
        printf("\nsuccessed!\n");
    }
    else
    {
        printf("\nfailed!\n");
    }
}

// 对树进行旋转
BPlusTree* Test5(BPlusTree* pTree)
{
    BPlusTree* pNewTree = pTree->RotateTree();
    delete pTree;
    printf("\nsuccessed!\n");
    return pNewTree;
}

// 打印
void Test6(BPlusTree* pTree)
{
    pTree->PrintTree();
}

// 对树进行检查（是否符合b+树/是否创建成功）
void Test7(BPlusTree* pTree)
{
    bool success = pTree->CheckTree();
    if (true == success)
    {
        printf("\nsuccessed!\n");
    }
    else
    {
        printf("\nfailed!\n");
    }
}

//创建的时候：BPlusTree* pTree = new BPlusTree;
