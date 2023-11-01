#include <iostream>
#include <stack>
#include <algorithm>  // for max()

using namespace std;

// NOTE FOR THE GRUTOR
// beginHelper() and leftTreePath() are the same function
// Making it a friend function or a shared function between classes creates
// issues with accessing private member variables, using const qualifiers, etc
// so we opted to leave the slight code duplication in favor of clarity

// Also we opted to use the defualt constructor for the iterator
// (i.e. create an empty stack) because adding the tree root can be
// done cleanly in the member functions, so there's not much point
// to writing a parameterized one

template <typename T>
TreeSet<T>::TreeSet() : root_{nullptr}, style_{LEAF} {
}

template <typename T>
TreeSet<T>::TreeSet(bst_style style) : root_{nullptr}, style_{style} {
}

template <typename T>
TreeSet<T>::TreeSet(bst_style style, size_t seed)
    : root_{nullptr}, style_{style}, random_{RandUInt32(seed)} {
}

template <typename T>
TreeSet<T>::~TreeSet() {
    if (!(root_ == nullptr)) {
        destroy(root_);
    }
}

template <typename T>
void TreeSet<T>::destroy(Node* node) {
    bool leftExists = node->left_ != nullptr;
    bool rightExists = node->right_ != nullptr;

    // recurse through existing subtrees
    if (!leftExists && rightExists) {
        destroy(node->right_);
    } else if (leftExists && !rightExists) {
        destroy(node->left_);
    } else if (leftExists && rightExists) {
        destroy(node->left_);
        destroy(node->right_);
    }

    delete node;  // delete current node after
}

template <typename T>
size_t TreeSet<T>::size() const {
    if (root_ == nullptr) {
        return 0;
    } else {
        return root_->subSize_;
    }
}

template <typename T>
void TreeSet<T>::insert(const T& value) {
    if (!exists(value)) {  // check if value is already in tree
        if (style_ == LEAF) {
            insertHelper(value, root_);
        } else if (style_ == ROOT) {
            rootInsertHelper(value, root_);
        } else {
            randomInsertHelper(value, root_);
        }
    }
}

template <typename T>
void TreeSet<T>::insertHelper(const T& value, Node*& tree) {
    if (tree == nullptr) {
        tree = new Node{value};
        // recurse through subtree
    } else if (value < tree->value_) {
        insertHelper(value, tree->left_);
    } else {
        insertHelper(value, tree->right_);
    }
    ++tree->subSize_;
}

template <typename T>
void TreeSet<T>::randomInsertHelper(const T& value, Node*& tree) {
    int randomInt = random_.get(nodeSize(tree) + 1);
    bool doRootInsert = (randomInt == 0);

    if (tree == nullptr) {
        tree = new Node{value};
    } else if (doRootInsert) {
        rootInsertHelper(value, tree);
    } else {
        if (value < tree->value_) {
            randomInsertHelper(value, tree->left_);
        } else {
            randomInsertHelper(value, tree->right_);
        }
    }
    ++tree->subSize_;
}

template <typename T>
void TreeSet<T>::rootInsertHelper(const T& value, Node*& tree) {
    if (tree == nullptr) {
        tree = new Node{value};

    } else if (value < tree->value_) {
        rootInsertHelper(value, tree->left_);
        rotateRight(tree);
    } else {
        rootInsertHelper(value, tree->right_);
        rotateLeft(tree);
    }
    ++tree->subSize_;
}

template <typename T>
void TreeSet<T>::rotateRight(Node*& top) {
    Node* oldRoot = top;
    Node* newRoot = top->left_;  // root for orginal left subtree

    // the subtree of the soon-to-be new root
    // soon-to-be oldroot's left subtree
    Node* newRight = newRoot->right_;

    // update the size of the new root's tree
    newRoot->subSize_ = oldRoot->subSize_;
    // update the size of the old root's tree
    oldRoot->subSize_ =
        nodeSize(newRoot->right_) + nodeSize(oldRoot->right_) + 1;

    // oldRoot's left points to the newroot's OG right subtree
    oldRoot->left_ = newRight;
    // newRoot's right points to oldroot
    newRoot->right_ = oldRoot;

    top = newRoot;
}

template <typename T>
void TreeSet<T>::rotateLeft(Node*& top) {
    Node* oldRoot = top;
    Node* newRoot = top->right_;
    Node* newLeft = newRoot->left_;

    // update the size of the new root's tree
    newRoot->subSize_ = oldRoot->subSize_;
    // update the size of the old root's tree
    oldRoot->subSize_ = nodeSize(newRoot->left_) + nodeSize(oldRoot->left_) + 1;

    oldRoot->right_ = newLeft;
    newRoot->left_ = oldRoot;

    top = newRoot;
}

template <typename T>
size_t TreeSet<T>::nodeSize(const Node* tree) {
    if (tree == nullptr) {
        return 0;
    } else {
        return tree->subSize_;
    }
}

template <typename T>
bool TreeSet<T>::exists(const T& value) const {
    return existsHelper(value, root_);
}

template <typename T>
bool TreeSet<T>::existsHelper(const T& value, const Node* tree) const {
    if (tree == nullptr) {
        return false;  // value not in tree
    } else if (tree->value_ == value) {
        return true;  // value in tree

        // recurse if not at leaf
    } else if (value < tree->value_) {
        return existsHelper(value, tree->left_);
    } else {
        return existsHelper(value, tree->right_);
    }
}

template <typename T>
int TreeSet<T>::height() const {
    return heightHelper(this->root_);
}

template <typename T>
int TreeSet<T>::heightHelper(const Node* tree) const {
    if (tree == nullptr) {
        return -1;  // -1 height if empty
    } else {        // find max height with recursion
        return 1 + max(heightHelper(tree->left_), heightHelper(tree->right_));
    }
}

template <typename T>
double TreeSet<T>::averageDepth() const {
    if (this->root_ != nullptr) {
        return avgDepthHelper(this->root_, 0) / root_->subSize_;
    } else {
        return 0;
    }
}

template <typename T>
double TreeSet<T>::avgDepthHelper(const Node* tree, size_t depth) const {
    if (tree->left_ == nullptr && tree->right_ == nullptr) {
        return depth;  // if leaf

        // recurse through tree
    } else if (tree->left_ == nullptr) {  // right subtree only
        return avgDepthHelper(tree->right_, depth + 1) + depth;
    } else if (tree->right_ == nullptr) {  // left subtree only
        return avgDepthHelper(tree->left_, depth + 1) + depth;
    } else {  // both subtrees exist
        return avgDepthHelper(tree->left_, depth + 1)
               + avgDepthHelper(tree->right_, depth + 1) + depth;
    }
}

template <typename T>
bool TreeSet<T>::operator==(const TreeSet& other) const {
    ConstIterator iter1 = this->begin();
    ConstIterator iter2 = this->end();
    ConstIterator iter3 = other.begin();
    ConstIterator iter4 = other.end();
    return equal(iter1, iter2, iter3, iter4);
}

template <typename T>
bool TreeSet<T>::operator!=(const TreeSet& other) const {
    return !(*this == other);
}

template <typename T>
ostream& TreeSet<T>::printToStream(ostream& os) const {
    return printToStreamHelp(os, root_);
}

template <typename T>
ostream& TreeSet<T>::printSizesToStream(ostream& os) const {
    return printSizeToStreamHelp(os, root_);
}

template <typename T>
ostream& TreeSet<T>::printToStreamHelp(ostream& os, const Node* tree) const {
    if (tree == nullptr) {
        os << "-";  // empty tree
    } else {
        os << "(";
        printToStreamHelp(os, tree->left_);
        os << ", ";
        os << tree->value_;
        os << ", ";
        printToStreamHelp(os, tree->right_);
        os << ")";
    }
    return os;
}

template <typename T>
ostream& TreeSet<T>::printSizeToStreamHelp(ostream& os,
                                           const Node* tree) const {
    if (tree == nullptr) {
        os << "0";  // empty tree has size 0
    } else {
        os << "(";
        printSizeToStreamHelp(os, tree->left_);
        os << ", ";
        os << tree->subSize_;
        os << ", ";
        printSizeToStreamHelp(os, tree->right_);
        os << ")";
    }
    return os;
}

template <typename T>
ostream& TreeSet<T>::showStatistics(ostream& os) const {
    os << root_->subSize_ << " nodes, height ";
    os << this->height() << ", average depth ";
    os << this->averageDepth() << endl;
    return os;
}

template <typename T>
typename TreeSet<T>::ConstIterator TreeSet<T>::begin() const {
    const_iterator iter = ConstIterator();
    return beginHelper(iter, this->root_);
}

template <typename T>
typename TreeSet<T>::ConstIterator TreeSet<T>::beginHelper(const_iterator& iter,
                                                           Node* tree) const {
    if (tree == nullptr) {
        return iter;
    } else {  // push parent to stack and recurse to child
        iter.stack_.push(tree);
        return beginHelper(iter, tree->left_);
    }
}

template <typename T>
typename TreeSet<T>::ConstIterator TreeSet<T>::end() const {
    const_iterator iter;  // empty stack
    return iter;
}

//////////////////////////
// Iterator functions
//////////////////////////

template <typename T>
typename TreeSet<T>::ConstIterator::reference
TreeSet<T>::ConstIterator::operator*() const {
    return stack_.top()->value_;
}

template <typename T>
typename TreeSet<T>::ConstIterator& TreeSet<T>::ConstIterator::operator++() {
    Node* curr = stack_.top();
    stack_.pop();
    leftTreePath(*this, curr->right_);
    return *this;
}

// const_iterator& leftTreePath(const_iterator& iter, Node* curr) const;

template <typename T>
typename TreeSet<T>::const_iterator& TreeSet<T>::ConstIterator::leftTreePath(
    const_iterator& iter, Node* curr) const {
    if (curr == nullptr) {
        return iter;
    } else {  // push parent to stack and recurse to child
        iter.stack_.push(curr);
        return leftTreePath(iter, curr->left_);
    }
}

template <typename T>
bool TreeSet<T>::ConstIterator::operator==(const ConstIterator& rhs) const {
    return (stack_ == rhs.stack_);
}

template <typename T>
bool TreeSet<T>::ConstIterator::operator!=(const ConstIterator& rhs) const {
    return !(*this == rhs);
}

template <typename T>
typename TreeSet<T>::ConstIterator::pointer
TreeSet<T>::ConstIterator::operator->() const {
    return &(**this);
}

//////////////////////////
// Node functions
//////////////////////////

template <typename T>
TreeSet<T>::Node::Node(T value)
    : value_{value}, left_{nullptr}, right_{nullptr}, subSize_{0} {
}

//////////////////////////
// Other functions
//////////////////////////

template <typename T>
ostream& operator<<(ostream& os, const TreeSet<T>& tree) {
    return tree.printToStream(os);
}
