#pragma once
/* BPlusTree.h

(1) һ��v�׵�B+���ɸ���㡢�ڲ�����Ҷ�ӽ����ɡ�
(2) ����������Ҷ�ӽ�㣬Ҳ������������������������ڲ���㡣
(3) ÿ���ڲ�������v - 2v���������һ���ڲ�������k������������ֻ��k+1��ָ��������ָ�롣
(4) Ҷ�ӽ������������ͬһ���ϡ�
(5) ���Ҷ�ӽ������������������һ�鰴��ֵ����ļ�¼�����Ҷ�ӽ���Ǵ�������������һ��̼�¼��ÿ���̼�¼����һ�����Լ�ָ��ʵ�ʼ�¼��ָ�롣
(6) �ڲ����ļ�ֵ��Ҷ�ӽ�������ֵ���Ǵ�С��������ġ�
(7) ���м����У�ÿ�������������е����еļ���С���������ÿ�������������е����еļ������ڵ����������

*/


/* B+ ���Ľ� �ڲ�����м�����С��Ŀv��
   csdn��Ҳ�е�˵���ǽ׶���Ϊ�ڲ�����м��������Ŀ2v��
   Ҷ�ӽ����������ݸ������ڲ����������������һ���ģ�Ҳ��2v
*/
#define ORDER_V 2    /* v���ڲ��ڵ��м�����С��Ŀ������˵������Сֵ���Ȱ�v�̶�Ϊ2�о���һЩ�������� */

#define MAXNUM_KEY (ORDER_V * 2)    /* �ڲ����������������Ϊ2v */
#define MAXNUM_POINTER (MAXNUM_KEY + 1)    /* �ڲ���������ָ��������ָ�������Ϊ2v */
#define MAXNUM_DATA (ORDER_V * 2)    /* Ҷ�ӽ����������ݸ�����Ϊ2v */

/* ��ֵ������*/
typedef int KEY_TYPE;    /* ������˵��b+����ֵӦ��ɶ���Ͷ��ܴ棬���Ǻ��鷳TvT ������int�͡����� Ҷ�ӽ�����ݴ洢��ֵ*/


/* ������� */
enum NODE_TYPE
{
    NODE_TYPE_ROOT = 1,    // �����
    NODE_TYPE_INTERNAL = 2,    // �ڲ����
    NODE_TYPE_LEAF = 3,    // Ҷ�ӽ��
};

#define NULL 0
#define INVALID 0

#define FLAG_LEFT 1
#define FLAG_RIGHT 2

/* ������ݽṹ��Ϊ�ڲ�����Ҷ�ӽ��ĸ��� */
class CNode
{
public:

    CNode();
    virtual ~CNode();

    //��ȡ�����ý������   // 1 ���� 2 �ڲ���㣻 3 Ҷ��
    NODE_TYPE GetType() { return m_Type; }  
    void SetType(NODE_TYPE type) { m_Type = type; }

    // ��ȡ��������Ч���ݸ���
    int GetCount() { return m_Count; }  // int m_Count  ��Ч���ݸ��������м���ָ����������Ҷ�ӽ��ָ���ݸ���
    void SetCount(int i) { m_Count = i; }

    // ��ȡ������ĳ��Ԫ�أ����м���ָ��ֵ����Ҷ�ӽ��ָ����
    virtual KEY_TYPE GetElement(int i) { return 0; }
    virtual void SetElement(int i, KEY_TYPE value) { }

    // ��ȡ������ĳ��ָ�룬���м���ָָ�룬��Ҷ�ӽ��������
    virtual CNode* GetPointer(int i) { return NULL; }
    virtual void SetPointer(int i, CNode* pointer) { }

    // ��ȡ�����ø����
    CNode* GetFather() { return m_pFather; }
    void SetFather(CNode* father) { m_pFather = father; }

    // ��ȡһ��������ֵܽ��
    CNode* GetBrother(int& flag);

    // ɾ�����
    void DeleteChildren();

protected:

    NODE_TYPE m_Type;    // ������ͣ�ȡֵΪNODE_TYPE����

    int m_Count;    // ��Ч���ݸ��������м���ָ����������Ҷ�ӽ��ָ���ݸ���

    CNode* m_pFather;     // ָ�򸸽���ָ�룬��׼B+���в�û�и�ָ�룬������Ϊ�˸����ʵ�ֽ����Ѻ���ת�Ȳ���

};

/* �ڲ�������ݽṹ */
class CInternalNode : public CNode
{
public:

    CInternalNode();
    virtual ~CInternalNode();

    // ��ȡ�����ü�ֵ������ֱ�ۿ���1��ʼ��ʵ���ڽ���д�0��ʼ
    KEY_TYPE GetElement(int i)
    {
        if ((i > 0) && (i <= MAXNUM_KEY)) //С�ڵ������ļ�ֵ��
        {
            return m_Keys[i - 1];
        }
        else
        {
            return INVALID;
        }
    }

    void SetElement(int i, KEY_TYPE key)
    {
        if ((i > 0) && (i <= MAXNUM_KEY))
        {
            m_Keys[i - 1] = key;  
        }
    }

    // ��ȡ������ָ�룬���ⲿ�������������ִ�1��ʼ
    CNode* GetPointer(int i)
    {
        if ((i > 0) && (i <= MAXNUM_POINTER))
        {
            return m_Pointers[i - 1];
        }
        else
        {
            return NULL;
        }
    }

    void SetPointer(int i, CNode* pointer)
    {
        if ((i > 0) && (i <= MAXNUM_POINTER))
        {
            m_Pointers[i - 1] = pointer;
        }
    }

    // �ڽ��pNode�ϲ����value
    bool Insert(KEY_TYPE value, CNode* pNode);
    // ɾ����value
    bool Delete(KEY_TYPE value);

    // ���ѽ��
    KEY_TYPE Split(CInternalNode* pNode, KEY_TYPE key);
    // ��Ͻ��(�ϲ����)
    bool Combine(CNode* pNode);
    // ����һ�����һ��Ԫ�ص������
    bool MoveOneElement(CNode* pNode);

protected:

    KEY_TYPE m_Keys[MAXNUM_KEY];           // ������
    CNode* m_Pointers[MAXNUM_POINTER];     // ָ������

};

/* Ҷ�ӽ�����ݽṹ */
class CLeafNode : public CNode
{
public:

    CLeafNode();
    virtual ~CLeafNode();

    // ��ȡ����������
    KEY_TYPE GetElement(int i)
    {
        if ((i > 0) && (i <= MAXNUM_DATA))
        {
            return m_Datas[i - 1];
        }
        else
        {
            return INVALID;
        }
    }

    void SetElement(int i, KEY_TYPE data)
    {
        if ((i > 0) && (i <= MAXNUM_DATA))
        {
            m_Datas[i - 1] = data;
        }
    }

    // ��ȡ������ָ�룬��Ҷ�ӽ�������壬ֻ��ʵ�и�����麯��
    CNode* GetPointer(int i)
    {
        return NULL;
    }

    // ��������
    bool Insert(KEY_TYPE value);
    // ɾ������
    bool Delete(KEY_TYPE value);

    // ���ѽ��
    KEY_TYPE Split(CNode* pNode);
    // ��Ͻ��
    bool Combine(CNode* pNode);

public:
    // ����������������ʵ��˫������
    CLeafNode* m_pPrevNode;                 // ǰһ�����
    CLeafNode* m_pNextNode;                 // ��һ�����

protected:

    KEY_TYPE m_Datas[MAXNUM_DATA];    // ��������

};

/* B+�����ݽṹ */
class BPlusTree
{
public:

    BPlusTree();
    virtual ~BPlusTree();

    // ����ָ��������
    bool Search(KEY_TYPE data, char* sPath);
    // ����ָ��������
    bool Insert(KEY_TYPE data);
    // ɾ��ָ��������
    bool Delete(KEY_TYPE data);

    // �����
    void ClearTree();

    // ��ӡ��
    void PrintTree();

    // ��ת��
    BPlusTree* RotateTree();

    // ������Ƿ�����B+���Ķ���
    bool CheckTree();

    void PrintNode(CNode* pNode);

    // �ݹ����㼰�������Ƿ�����B+���Ķ���
    bool CheckNode(CNode* pNode);

    // ��ȡ�����ø����
    CNode* GetRoot()
    {
        return m_Root;
    }

    void SetRoot(CNode* root)
    {
        m_Root = root;
    }

    // ��ȡ���������
    int GetDepth()
    {
        return m_Depth;
    }

    void SetDepth(int depth)
    {
        m_Depth = depth;
    }

    // ��ȼ�һ
    void IncDepth()
    {
        m_Depth = m_Depth + 1;
    }

    // ��ȼ�һ
    void DecDepth()
    {
        if (m_Depth > 0)
        {
            m_Depth = m_Depth - 1;
        }
    }

public:
    // ����������������ʵ��˫������   CLeafNode Ҷ�ӽ�����ݽṹ row 157
    CLeafNode* m_pLeafHead;                 // ͷ���
    CLeafNode* m_pLeafTail;                   // β���

protected:

    // Ϊ���������Ҷ�ӽ��
    CLeafNode* SearchLeafNode(KEY_TYPE data);
    //��������м���
    bool InsertInternalNode(CInternalNode* pNode, KEY_TYPE key, CNode* pRightSon);
    // ���м�����ɾ����
    bool DeleteInternalNode(CInternalNode* pNode, KEY_TYPE key);

    CNode* m_Root;    // �����
    int m_Depth;      // �������
};

