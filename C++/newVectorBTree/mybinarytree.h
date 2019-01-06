#ifndef MYBINARYTREE_H
#define MYBINARYTREE_H
#include <vector>
#include <cmath>
#define lChild(i) (2*i + 1)
#define rChild(i) (2*i + 2)
#define getParent(i) (i - 1)/2
#define midPoint(start, end) (start + end -1)/2

enum TREE_ERROR {TREE_EMPTY, TREE_BAD_SIZE};

template <typename D>
struct Node {
    D data;
    int count;
    bool status;

    Node(const D &d=D(), const int &c=1, const bool &s=true);
    ~Node();
    Node(const Node<D> &other);
    Node<D>& operator=(const Node<D> &other);
};

template <typename D>
Node<D>::Node(const D &d, const int &c, const bool &s) {
    data = d;
    count = c;
    status = s;
}

template <typename D>
Node<D>::~Node() {
    data = D();
    count = 0;
    status = false;
}

template <typename D>
Node<D>::Node(const Node<D> &other) {
    data = other.data;
    count = other.count;
    status = other.status;
}

template <typename D>
Node<D>& Node<D>::operator=(const Node<D> &other) {
    if(this != &other) {
        data = other.data;
        count = other.count;
        status = other.status;
    }
    return *this;
}

template <typename T>
class myBinaryTree {
    std::vector<Node<T>*> tree, container, bin;
    std::vector<int> indices;
    int nCount, dCount;
    void inOrderPop(int index, std::vector<Node<T>*> &v, const int &end);
    int goLeftAllTheWayDown(const int &ind) const;
    int goRightAllTheWayDown(const int &ind) const;
    void copy(const myBinaryTree<T> &other);
    void deleteAll();
    void rebalance(bool must=false);
    bool pushToBinFromContainer(const int &index);
    void reInsert(int start, int end, int ind);
    int exists(const T &data) const;
    int height(const int &index);
    bool setTreeSize(const size_t &d);
    int setIndex(const T &data);
public:
    myBinaryTree();
    ~myBinaryTree();
    myBinaryTree(const myBinaryTree<T> &other);
    myBinaryTree<T>& operator=(const myBinaryTree<T> &other);
    bool empty() const;
    void insert(const T &d, int c=1);
    myBinaryTree<T>& operator<<(const T &d);
    myBinaryTree<T>& operator>>(Node<T> &d);
    bool deleteData(const T &d);
    int dataCount() const;
    int nodeCount() const;
    int height();
    void flush(std::vector<Node<T>*> &v);
    void print(std::ostream &out, const size_t &index) const;
};

// Public
template <typename T>
myBinaryTree<T>::myBinaryTree() {
    nCount = dCount = 0;
}

template <typename T>
myBinaryTree<T>::~myBinaryTree() {
    deleteAll();
}

template <typename T>
myBinaryTree<T>::myBinaryTree(const myBinaryTree<T> &other) {
    copy(other);
}

template <typename T>
myBinaryTree<T>& myBinaryTree<T>::operator=(const myBinaryTree<T> &other) {
    if(this != &other) {
        deleteAll();
        copy(other);
    }
    return *this;
}

template <typename T>
bool myBinaryTree<T>::empty() const {
    return !nCount;
}

template <typename T>
void myBinaryTree<T>::insert(const T &d, int c) {
    int ind = exists(d);
    dCount += c;
    if(ind != -1) {
        tree[ind]->count += c;
    } else {
        ind = setIndex(d);
        (ind >= tree.size()) && setTreeSize(ind);
        tree[ind] = new Node<T>(d,c);
        ++nCount;
        rebalance();
    }
}

template <typename T>
myBinaryTree<T>& myBinaryTree<T>::operator<<(const T &d) {
    insert(d);
    return *this;
}

template <typename T>
myBinaryTree<T>& myBinaryTree<T>::operator>>(Node<T> &d) {
    if(empty())
        throw TREE_EMPTY;
    size_t index=0;
    while(lChild(index)<tree.size() && tree[index] && tree[lChild(index)])
        index=lChild(index);
    d = *(tree[index]);
    deleteData(tree[index]->data);
    return *this;
}

template <typename T>
bool myBinaryTree<T>::deleteData(const T &d) {
    if(empty())
        throw TREE_EMPTY;
    container.clear();
    flush(container);

    int m=0;
    if(container[m]->data == d) {
        nCount -= 1;
        dCount -= container[m]->count;
        container.push_back(nullptr);
        std::swap(container[m], container[container.size()-1]);
        container.pop_back();
        tree.clear();
        reInsert(0, container.size(), 0);
    }
    return true;
}

template <typename T>
int myBinaryTree<T>::dataCount() const {
    return dCount;
}

template <typename T>
int myBinaryTree<T>::nodeCount() const {
    return nCount;
}

template <typename T>
int myBinaryTree<T>::height() {
    return height(0);
}

template <typename T>
void myBinaryTree<T>::flush(std::vector<Node<T>*> &v) {
    if(tree.empty())
        throw TREE_EMPTY;
    size_t index, end;
    index = goLeftAllTheWayDown(0), end = goRightAllTheWayDown(0);
    inOrderPop(index, v, end);
}

template <typename T>
void myBinaryTree<T>::print(std::ostream &out, const size_t &index) const {
    if(tree[index] && index < tree.size()) {
        print(out, lChild(index));
        out << "tree[" << index << "] = (" << tree[index]->data << ", " << tree[index]->count << ")" << std::endl;
        print(out, rChild(index));
    }
}

// Private
template <typename T>
void myBinaryTree<T>::inOrderPop(int index, std::vector<Node<T>*> &v, const int &end) {
    int prev;
    while(index>=0 && index<tree.size()) {
        if(tree[index] && tree[index]->status) {
            tree[index]->status = false;
            v.push_back(tree[index]);
            if(index == end)
                break;
        }
        prev = index;
        index = rChild(index) < tree.size() && tree[rChild(index)] && tree[rChild(index)]->status
                ? goLeftAllTheWayDown(rChild(index)) : getParent(index);
        if(index == prev)
            break;
    }
}

template <typename T>
int myBinaryTree<T>::goLeftAllTheWayDown(const int &ind) const {
    int index = ind;
    while(lChild(index)<tree.size() && tree[index] && tree[lChild(index)])
        index=lChild(index);
    return index;
}

template <typename T>
int myBinaryTree<T>::goRightAllTheWayDown(const int &ind) const {
    int index = ind;
    while(rChild(index)<tree.size() && tree[index] && tree[rChild(index)])
        index=rChild(index);
    return index;
}

template <typename T>
void myBinaryTree<T>::copy(const myBinaryTree<T> &other) {
    std::copy(other.tree.begin(), other.tree.end(), std::back_inserter(tree));
    nCount = other.nCount;
    dCount = other.dCount;
}

template <typename T>
void myBinaryTree<T>::deleteAll() {
    for(size_t i=0; i<tree.size(); ++i)
        if(tree[i]) {                   //std::cout << "deleting tree[" << i << "].." << std::endl;
            delete tree[i];
            tree[i]=nullptr;
        }
    tree.clear();
    container.clear();
    bin.clear();
    indices.clear();
    nCount = dCount = 0;
}

template <typename T>
void myBinaryTree<T>::rebalance(bool must) {
    if(!must && std::abs(static_cast<double>(height(1) - height(2))) <= 1)
        return ;
    container.clear();
    flush(container);
    tree.clear();
    reInsert(0, container.size(), 0);
}

template <typename T>
bool myBinaryTree<T>::pushToBinFromContainer(const int &index) {
    container.push_back(nullptr);
    bin.push_back(container[index]);
    std::swap(container[index], container[container.size()-1]);
    container.pop_back();
    return true;
}

template <typename T>
void myBinaryTree<T>::reInsert(int start, int end, int ind) {
    int mid = (start+end)/2;
    if(find(tree.begin(), tree.end(), container[mid])!=tree.end())
        return ;
    else {
        (ind >= tree.size()) && setTreeSize(ind);
        tree[ind] = container[mid];
        reInsert(start, mid, lChild(ind));
        reInsert(mid, end, rChild(ind));
    }
}

//template <typename T>
//void myBinaryTree<T>::reInsert() {
//    Node<T> *data;
//    int mid, i, index;
//    bin.clear();
//    while(!container.empty()) {
//        mid = midPoint(0, container.size()), i=0;
//        container[mid] && pushToBinFromContainer(mid);
//        data = container[0];
//        while(container[midPoint(0,mid)] && container[midPoint(0,mid)]!=data)
//            pushToBinFromContainer(mid=midPoint(0,mid));
//        container[0] && pushToBinFromContainer(0);
//        mid = midPoint(0, container.size());
//        data = container[container.size()-1];
//        while(container[midPoint(mid, container.size())] &&
//              container[midPoint(mid, container.size())]!=data)
//            pushToBinFromContainer(mid=midPoint(mid, container.size()));
//        container.size()-1 && container[container.size()-1] && pushToBinFromContainer(container.size()-1);
//        while(!container.empty()) {
//            data = container[container.size()-1];
//            if(data) {
//                bin.push_back(data);
//                ++i;
//            }
//            container.pop_back();
//        }
//        while(i--) {
//            container.push_back(bin[bin.size()-1]);
//            bin.pop_back();
//        }
//    }
//    for(size_t j=0; j<bin.size(); ++j) {
//        data = bin[j];
//        index = setIndex(data->data);
//        setTreeSize(index);
//        tree[index] = data;
//        data->status = true;
//    }
//}

template <typename T>
int myBinaryTree<T>::exists(const T &data) const {
    int index=0;
    while(index < tree.size() && tree[index] && tree[index]->data != data)
        index = tree[index]->data > data ? rChild(index) : lChild(index);
    return index < tree.size() && tree[index] ? index : -1;
}

template <typename T>
int myBinaryTree<T>::height(const int &index) {
    if(index>=tree.size() || !tree[index])
        return 0;
    int hCount = 0, node, n;
    indices.clear();
    indices.push_back(index);
    while(1) {
        node = indices.size();
        if(!node)
            break;
        ++hCount;
        while(node) {
            n = indices[indices.size()-1];
            indices.pop_back();
            if(lChild(n)<tree.size() && tree[lChild(n)])
                indices.push_back(lChild(n));
            if(rChild(n)<tree.size() && tree[rChild(n)])
                indices.push_back(rChild(n));
            --node;
        }
    }
    return hCount;
}

template <typename T>
bool myBinaryTree<T>::setTreeSize(const size_t &d) {
    while(d - tree.size()+1)
        tree.push_back(nullptr);
    return d;
}

template <typename T>
int myBinaryTree<T>::setIndex(const T &data) {
    if(empty())
        return 0;
    size_t child=0, parent=0;
    while(parent < tree.size()) {
        if(tree[parent]) {
            child = tree[parent]->data < data ? lChild(parent) : rChild(parent); // change DIR here #2
            parent = child;
        } else
            break;
    }
    return child;
}

#endif // MYBINARYTREE_H
