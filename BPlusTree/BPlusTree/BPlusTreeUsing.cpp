/*
* ���ļ�����δ���������ļ�ϵͳ��Ҫ���õ��Ĺ���b+���Ĳ���ɾ�����ҵȵȷ�����ʹ��
* ���������ļ�ϵͳ��b+����������Ҫ��һЩ����
* ������xyh ��˵�ĺ�ģ�� �о�Ҳû�н��͵ĺ�����b+�������ݿ����浽����ô���� ������������ô�����ˡ�����xyh ����
*/



#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "BPlusTree.h"


// �������һ����
void Test1(BPlusTree* pTree, int count)
{
    pTree->ClearTree();

    //srand( (unsigned)time( NULL ) );//Ӧ��Ҳ����Ҫ�������һ����������
    for (int i = 0; i < count; i++)
    {
        int x = rand() % 999 + 1;
        (void)pTree->Insert(x);
    }

    printf("successed!\n");
}

// �����в���ĳ����
void Test2(BPlusTree* pTree, int data)
{
    char sPath[255] = { 0, };

    (void)pTree->Search(data, sPath);
    printf("\n%s", sPath);
}

// �����в���ĳ����
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

// ������ɾ��ĳ����
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

// ����������ת
BPlusTree* Test5(BPlusTree* pTree)
{
    BPlusTree* pNewTree = pTree->RotateTree();
    delete pTree;
    printf("\nsuccessed!\n");
    return pNewTree;
}

// ��ӡ
void Test6(BPlusTree* pTree)
{
    pTree->PrintTree();
}

// �������м�飨�Ƿ����b+��/�Ƿ񴴽��ɹ���
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

//������ʱ��BPlusTree* pTree = new BPlusTree;
