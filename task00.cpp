#include<iostream>

template<class T>
class Stack;
template<class T>
class Queue;

template<class T>
class Node {
public:
    Node(T var, Node* fo) :data(var), next(fo) {};
    friend Stack<T>;
    friend Queue<T>;
private:
    T data;
    Node* next;
};


template<class T>
class Stack {
public:
    Stack() :tail(nullptr) {};
    void Push(T var) {
        tail = new Node<T>(var, tail);
    }
    void Pop() {
        if (tail == nullptr) {
            throw std::runtime_error("empty stack!");
        }
        auto temp = tail;
        tail = tail->next;
        delete temp;
        temp = nullptr;
    }
    T Top() {
        if (tail == nullptr) {
            throw std::runtime_error("empty stack!");
        }
        return tail->data;
    }
    bool Empty() {
        return tail == nullptr;
    }
private:
    Node<T>* tail;
};

template<class T>
class Queue {
public:
    Queue() :head(nullptr), tail(nullptr) {};
    void Push(T var) {
        if (tail == nullptr) {
            head = tail = new Node<T>(var, nullptr);
        }
        else {
            tail = tail->next = new Node<T>(var, nullptr);
        }
    }
    void Pop() {
        if (head == nullptr) {
            throw std::runtime_error("empty stack!");
        }
        if (head->next == nullptr) {
            delete head;
            tail = head = nullptr;
        }
        else {
            auto temp = head;
            head = head->next;
            delete temp;
            temp = nullptr;
        }
    }
    T Top() {
        if (head == nullptr) {
            throw std::runtime_error("empty stack!");
        }
        return head->data;
    }
    bool Empty() {
        return tail == nullptr;
    }
private:
    Node<T>* head;
    Node<T>* tail;
};




template<class T>
class Tree;

template<class T>
class TreeNode {
public:
    template<class... Args>
    TreeNode(T var, int k, Args... args) : data(var), k(k) {
        assert(sizeof...(args) == k);
        child = new TreeNode * [k] {args...};
    }
    friend Tree<T>;
    void AllocateChild(TreeNode* newChild, int pos) {
        assert(pos < k && pos >= 0);
        child[pos] = newChild;
    }
    // private:
    T data;
    int k;
    TreeNode** child;
};


template<class T>
class Tree {
public:
    Tree(int k = 2) :k(k), root(nullptr) {};

    //先序遍历
    //在使用lambda表达式都情况下，args完全可以省略，加入args是为了处理普通函数的情况（不过貌似没有意义）
    //1、2可以不加判断，但会导致多个空结点入栈，对于稀疏树会浪费时间与空间
    template<class F, class... Args>
    void PreOrder(TreeNode<T>* root, const F& func, Args&... args) {
        assert(k == 2);
        Stack<TreeNode<T>*> s;
        TreeNode<T>* cur = root;
        TreeNode<T>* temp;
        while (cur != nullptr || !s.Empty()) {
            while (cur != nullptr) {
                if (cur->child[1] != nullptr) { //1
                    s.Push(cur->child[1]);
                }
                temp = cur->child[0];//这是为了允许func中进行删除操作
                func(cur, args...);
                cur = temp;
            }
            if (!s.Empty()) { //2
                cur = s.Top();
                s.Pop();
            }
        }
    }

    //中序遍历
    //在使用lambda表达式都情况下，args完全可以省略，加入args是为了处理普通函数的情况（不过貌似没有意义）
    template<class F, class... Args>
    void MiddleOrder(TreeNode<T>* root, const F& func, Args&... args) {
        assert(k == 2);
        Stack<TreeNode<T>*> s;
        TreeNode<T>* cur = root;
        TreeNode<T>* temp;
        while (cur != nullptr || !s.Empty()) {
            while (cur != nullptr) {
                s.Push(cur);
                cur = cur->child[0];
            }
            cur = s.Top();
            s.Pop();
            temp = cur->child[1];//这是为了允许func中进行删除操作
            func(cur, args...);
            cur = temp;
        }
    }

    //后序遍历
    //在使用lambda表达式都情况下，args完全可以省略，加入args是为了处理普通函数的情况（不过貌似没有意义）
    //合理利用指向空结点（否则代码会较复杂，可读性变差）
    template<class F, class... Args>
    void PostOrder(TreeNode<T>* root, const F& func, Args&... args) {
        assert(k == 2);
        Stack<std::pair<TreeNode<T>*, int>> s;
        TreeNode<T>* cur = root;
        while (cur != nullptr || !s.Empty()) {
            while (cur != nullptr) {
                s.Push(std::make_pair(cur, 0));
                cur = cur->child[0];
            }
            cur = s.Top().first;
            if (s.Top().second == 0) {
                s.Pop();
                s.Push(std::make_pair(cur, 1));
                cur = cur->child[1];
            }
            else {
                s.Pop();
                func(cur, args...);
                cur = nullptr;
            }
        }
    }

    //层序遍历
    //在使用lambda表达式都情况下，args完全可以省略，加入args是为了处理普通函数的情况（不过貌似没有意义）
    //适用于任意K叉树！
    //k=2时，将queue改成stack，并将左右节点入栈顺序调换，就成了先序遍历
    //缺点是会出现大量入栈后立即出栈的操作，不够高效
    template<class F, class... Args>
    void LevelOrder(TreeNode<T>* root, const F& func, Args&... args) {
        Queue<TreeNode<T>*> q;
        TreeNode<T>* cur = root;
        if (cur != nullptr) {
            q.Push(cur);
        }
        while (!q.Empty()) {
            cur = q.Top();
            q.Pop();
            for (int i = 0;i < this->k;++i) {
                if (cur->child[i] != nullptr) {
                    q.Push(cur->child[i]);
                }
            }
            func(cur, args...);
        }
    }

    void Show(TreeNode<T>* root, int option = 1) {
        auto func = [](TreeNode<T>* cur) {
            std::cout << cur->data << " ";
            };
        SwitchOption(option, func, root);
        std::cout << std::endl;
    }

    int Size(TreeNode<T>* root, int option = 0) {
        int count = 0;
        auto func = [&count](TreeNode<T>* cur) {
            ++count;
            };
        SwitchOption(option, func, root);
        return count;
    }

    //删除subRoot及其子树，将root指针对应孩子指针置为null
    //若subRoot指向内存与this->root一致，则将this->root置为null
    //否则必须将root设置为subRoot的父亲，不然会导致今后可能会再次访问到的野指针
    void Delete(TreeNode<T>* subRoot, TreeNode<T>* root, int option = 0) {
        auto func = [](TreeNode<T>*& cur) { //用指针引用，方便将原指针置为null
            delete cur;
            cur = nullptr; //但即使这样做，依然有野指针存在，虽然之后已经无法访问到
            };
        if (subRoot == this->root) {
            this->root = nullptr;
        }
        else {
            for (int i = 0;i < this->k;++i) {
                if (root->child[i] == subRoot) {
                    root->child[i] = nullptr;
                    break;
                }
            }
        }
        SwitchOption(option, func, subRoot);
    }

    //删除hock及其子树，将root指针对应孩子指针指向subTree
    //若hock指向内存与this->root一致，则将this->root指向subTree
    //否则必须将root设置为hock的父亲，不然会导致今后可能会再次访问到的野指针
    //生成的新tree与subTree共用一部分内存，并没有新的内存空间的开辟
    //意味着之后修改subTree会影响到新tree
    //不要试图将一个tree的子树Bound到自身的结点上！
    //当subTree为空树时，效果与Delete一致
    void Bound(TreeNode<T>* hock, TreeNode<T>* root, Tree<T>& subTree, int subK = 2, int option = 0) {
        this->k = subK > this->k ? subK : this->k;
        auto func = [](TreeNode<T>*& cur) { //用指针引用，方便将原指针置为null
            delete cur;
            cur = nullptr; //但即使这样做，依然有野指针存在，虽然之后已经无法访问到
            };
        if (hock == this->root) {
            this->root = subTree.root;
        }
        else {
            for (int i = 0;i < this->k;++i) {
                if (root->child[i] == hock) {
                    root->child[i] = subTree.root;
                    break;
                }
            }
        }
        SwitchOption(option, func, hock);
    }

    //考虑二叉搜索树，中序从小到大，无重复元素
    //插入操作，利用中序遍历找到与插入元素大小相邻的相邻元素
    //必有或较小相邻元素的右子节点为空，或者较大相邻元素的左子节点为空（否则可以导出矛盾）
    //同时，不可能两个均为空
    //因此，只要找到非空的那个，插入即可（无需改变树的其它部位的结构）
    //不过，其实这样效率很低，因为遍历必然将所有元素都遍历，复杂度为O(n)
    void MiddleOrderInsert(T v) {
        TreeNode<T>* newNode = new TreeNode<T>(v, 2, nullptr, nullptr);
        if (root == nullptr) {
            root = newNode;
        }
        else {
            TreeNode<T>* less = nullptr, * more = nullptr;
            bool isDuplicate = false;
            auto func = [&](TreeNode<T>* cur) {
                if (isDuplicate) {
                    return;
                }
                if (cur->data < v) {
                    if (less == nullptr || cur->data > less->data) {
                        less = cur;
                    }
                }
                else if (cur->data > v) {
                    if (more == nullptr || cur->data < more->data) {
                        more = cur;
                    }
                }
                else {
                    isDuplicate = true;
                }
                };
            PreOrder(this->root, func);
            if (isDuplicate) {
                return;
            }
            else if (less != nullptr && less->child[1] == nullptr) {
                less->AllocateChild(newNode, 1);
            }
            else {
                more->AllocateChild(newNode, 0);
            }
        }
    }

protected:
    template<class F, class... Args>
    void SwitchOption(int option, const F& func, TreeNode<T>* root, Args&... args) {
        switch (option)
        {
        case 0:
            PreOrder(root, func, args...);
            break;
        case 1:
            MiddleOrder(root, func, args...);
            break;
        case 2:
            PostOrder(root, func, args...);
            break;
        case 3:
            LevelOrder(root, func, args...);
        default:
            break;
        }
    }

public:
    TreeNode<T>* root;
    int k;
};






int main() {
    Tree<int>tree(2);
    tree.MiddleOrderInsert(1);
    tree.MiddleOrderInsert(5);
    tree.MiddleOrderInsert(6);
    tree.MiddleOrderInsert(2);
    tree.MiddleOrderInsert(-1);
    tree.MiddleOrderInsert(2);
    tree.MiddleOrderInsert(-2);

    tree.Show(tree.root, 0);
    tree.Show(tree.root, 1);
    tree.Show(tree.root, 2);
    tree.Show(tree.root, 3);
    std::cout << tree.Size(tree.root, 0);
    std::cout << tree.Size(tree.root, 1);

    Tree<int>tree2(2);
    tree2.MiddleOrderInsert(10);
    tree2.MiddleOrderInsert(9);
    tree2.MiddleOrderInsert(8);
    tree2.Bound(tree2.root->child[0], tree2.root, tree, 2, 0);
    std::cout << tree2.Size(tree2.root, 3);

    tree2.Delete(tree2.root->child[0], tree2.root, 0);
    std::cout << tree2.Size(tree2.root, 2);
    tree2.Delete(tree2.root->child[1], tree2.root, 1);
    std::cout << tree2.Size(tree2.root, 3);
    tree2.Delete(tree2.root, tree2.root, 2);
    std::cout << tree2.Size(tree2.root, 3);



    return 0;
}
