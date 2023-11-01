#ifndef TREE_SET_INCLUDED_HPP
#define TREE_SET_INCLUDED_HPP

#include <string>
#include <ostream>
#include <stack>
#include <cs70/randuint32.hpp>

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

enum bst_style { LEAF, ROOT, RANDOMIZED };

template <typename T>
class TreeSet {
 private:
    // Forward declarations
    class ConstIterator;
    struct Node;

 public:
    friend struct Node;
    friend class ConstIterator;

    using const_iterator = ConstIterator;

    /**
     * \brief Constructs an empty LEAF tree
     */
    TreeSet();

    /**
     * \brief Constructs an empty tree for one of bst_style
     */
    explicit TreeSet(bst_style style);

    /**
     * \brief Constructs an empty tree for one of bst_style
     */
    TreeSet(bst_style style, size_t random);

    /**
     * \brief Deallocates the list
     */
    ~TreeSet();

    // We are disallowing copying for this list
    TreeSet(const TreeSet<T>&) = delete;
    TreeSet<T>& operator=(const TreeSet<T>&) = delete;

    /**
     * \brief returns the number of nodes in a tree
     */
    size_t size() const;

    /**
     * \brief Creates and inserts a new Node into a BST
     * \param value  The string for the Node
     */
    void insert(const T& value);

    /**
     * \brief Checks if a string value is in a BST
     * \param value  The string we are searching for
     */
    bool exists(const T& value) const;

    /**
     * \brief returns the height of a BST
     * (number of edges in longest path)
     */
    int height() const;

    /**
     * \brief Returns the average depth of the tree
     */
    double averageDepth() const;

    /**
     * \brief returns True if this and other have same values
     * regardless of shape
     * \param other  The tree to compare
     */
    bool operator==(const TreeSet& other) const;

    /**
     * \brief returns True if this and other do not
     * have the same values
     * \param other  The tree to compare
     */
    bool operator!=(const TreeSet& other) const;

    /**
     * \brief prints a BST
     * \param os the ostream to print to
     */
    ostream& printToStream(ostream& os) const;

    /**
     * \brief prints the size od BST ??
     * \param os the ostream to print to
     */
    ostream& printSizesToStream(ostream& os) const;

    /**
     * \brief prints a BST
     * \param os the ostream to print to
     */
    ostream& showStatistics(ostream& os) const;

    /**
     * \brief Returns a constant iterator to the
     * first (least) node of a BST
     * \warning Calling begin on an empty tree yields a null iterator
     */
    const_iterator begin() const;

    /**
     * \brief Returns a constant iterator past-the-end of a BST
     * \warning Calling end on an empty tree yields a null iterator
     */
    const_iterator end() const;

 private:
    Node* root_;         // tree root
    bst_style style_;    // stores the type of insert for the tree
    RandUInt32 random_;  // random number

    /**
     * \brief recursive helper function for destructor
     */
    void destroy(Node* node);

    /**
     * \brief recursive helper function for insert
     */
    void insertHelper(const T& value, Node*& node);

    /**
     * \brief Creates and inserts a new Node into a root BST
     * \param value  The string for the Node
     * \param tree   The original root
     */
    static void rootInsertHelper(const T& value, Node*& tree);

    /**
     * \brief Creates and inserts a new Node into a random BST
     * \param value  The string for the Node
     * \param tree   The original root
     */
    void randomInsertHelper(const T& value, Node*& tree);

    /**
     * \brief Takes care of right rotation
     * \param top is the original root node whose left will become
     * the new root
     *
     *  “adapted from code provided in CS 70, Week 10, Lesson 2”
     */
    static void rotateRight(Node*& top);

    /**
     * \brief Takes care of left rotation
     * \param top is the original root node whose right will become
     * the new root
     */
    static void rotateLeft(Node*& top);

    /**
     * \brief recursive helper function for insert
     */
    bool existsHelper(const T& value, const Node* node) const;

    /**
     * \brief recursive helper function for printToStream
     */
    ostream& printToStreamHelp(ostream& os, const Node* tree) const;

    /**
     * \brief recursive helper function for printSizeToStream
     */
    ostream& printSizeToStreamHelp(ostream& os, const Node* tree) const;

    /**
     * \brief helper function for begin
     */
    const_iterator beginHelper(const_iterator& iter, Node* tree) const;

    /**
     * \brief helper function for height
     */
    int heightHelper(const Node* tree) const;

    /**
     * \brief helper function for averageDepth
     */
    double avgDepthHelper(const Node* tree, size_t depth) const;

    /**
     * \brief helper that return the size of the subtree
     * if tree points to nullptr, return 0
     */
    static size_t nodeSize(const Node* tree);

    struct Node {
        /**
         * \brief Constructs a Node
         */
        Node(T value);

        friend class ConstIterator;
        friend class TreeSet;

        T value_;
        Node* left_ = nullptr;  // default null
        Node* right_ = nullptr;
        size_t subSize_;  // number of nodes in the subtree including this
    };

    class ConstIterator {
        friend class TreeSet<T>;

     public:
        using value_type = T;
        using reference = const value_type&;
        using pointer = const value_type*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        /**
         * \brief Constructs an invalid iterator
         * \warning A default-constructed iterator can only be reassigned, or
         * destroyed
         */
        ConstIterator() = default;
        ConstIterator(const ConstIterator& orig) = default;
        ConstIterator& operator=(const ConstIterator& rhs) = default;
        ~ConstIterator() = default;

        /**
         * \brief Returns a reference to the item at the current position
         * \returns A reference to the item at the current position
         * \warning Dereferencing the iterator returned by end has undefined
         * behavior
         */
        const T& operator*() const;

        /**
         * \brief Advances the iterator to the next position
         * \returns A reference to the iterator
         * \warning Advancing the iterator returned by end has undefined
         * behavior
         */
        ConstIterator& operator++();

        /**
         * \brief Compares the positions of two iterators
         * \returns True if the two iterators have the same position, false
         * otherwise
         * \warning Comparing iterators from different IntLists has
         * undefined behavior
         */
        bool operator==(const ConstIterator& rhs) const;

        /**
         * \brief Compares the positions of two iterators
         * \returns False if the two iterators have the same position, true
         * otherwise
         * \warning Comparing iterators from different IntLists has
         * undefined behavior
         */
        bool operator!=(const ConstIterator& rhs) const;

        /**
         * \brief Allows the iterator class to use arrow notation
         */
        const T* operator->() const;

     private:
        /**
         * \brief helper function for ++
         */
        const_iterator& leftTreePath(const_iterator& iter, Node* curr) const;

        stack<Node*> stack_;
    };
};

/**
 * \brief defines how to print a TreeSet
 * (using TreeSet::printToStream)
 * \param os the ostream to print to
 * \param tree the tree to print
 */
template <typename T>
ostream& operator<<(ostream& os, const TreeSet<T>& tree);

#include "treeset-private.hpp"

#endif  // TREE_SET_INCLUDED_HPP