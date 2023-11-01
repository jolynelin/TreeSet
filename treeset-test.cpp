#include "treeset.hpp"
#include <iostream>
#include <cs70/testinglogger.hpp>
#include <sstream>

using namespace std;

bool testDefaultConstructor() {
    TestingLogger log("Default Constructor");

    TreeSet<std::string> myTree;

    affirm(myTree.size() == 0);
    affirm(myTree.height() == -1);
    return log.summarize();
}

bool testOneParaConstructor() {
    TestingLogger log("One Parameter Constructor");

    TreeSet<std::string> myTree{LEAF};

    affirm(myTree.size() == 0);
    affirm(myTree.height() == -1);
    return log.summarize();
}

bool testInsert1() {
    TestingLogger log("Insert 1 element to BST");

    TreeSet<std::string> myTree;
    myTree.insert("a");

    affirm(myTree.size() == 1);
    affirm(myTree.height() == 0);
    return log.summarize();
}

bool testInsert2() {
    TestingLogger log("Insert 3 elements to BST");

    TreeSet<std::string> myTree;
    myTree.insert("a");
    myTree.insert("b");
    myTree.insert("c");
    myTree.insert("d");
    myTree.insert("e");
    myTree.insert("f");

    affirm(myTree.size() == 6);
    return log.summarize();
}

bool testInsert3() {
    TestingLogger log("Insert element twice");

    TreeSet<std::string> myTree;
    myTree.insert("a");
    myTree.insert("a");

    affirm(myTree.size() == 1);
    return log.summarize();
}

bool testInsertInt() {
    TestingLogger log("Insert 6 int elements to BST");

    TreeSet<int> myTree;
    myTree.insert(1);
    myTree.insert(2);
    myTree.insert(3);
    myTree.insert(4);
    myTree.insert(5);
    myTree.insert(6);

    affirm(myTree.size() == 6);
    return log.summarize();
}

bool testInsertDouble() {
    TestingLogger log("Insert double element twice");

    TreeSet<double> myTree;
    myTree.insert(1.1);
    myTree.insert(1.1);

    affirm(myTree.size() == 1);
    return log.summarize();
}

bool testRootInsert1() {
    TestingLogger log("Root insert 1 element to BST");

    TreeSet<std::string> myTree;
    myTree.insert("a");

    affirm(myTree.size() == 1);
    affirm(myTree.height() == 0);
    return log.summarize();
}

bool testRootInsert2() {
    TestingLogger log("Root insert 3 elements to BST");

    TreeSet<int> myTree{ROOT};
    myTree.insert(60);
    myTree.insert(50);
    myTree.insert(55);

    TreeSet<int>::const_iterator iter = myTree.begin();

    affirm(*iter == 50);
    affirm(myTree.size() == 3);
    return log.summarize();
}

bool testRootInsert3() {
    TestingLogger log("Root Insert element twice");

    TreeSet<std::string> myTree{ROOT};
    myTree.insert("a");
    myTree.insert("a");

    TreeSet<std::string>::const_iterator iter = myTree.begin();

    affirm(*iter == "a");
    affirm(myTree.size() == 1);
    return log.summarize();
}

bool testExists1() {
    TestingLogger log("Exists in empty tree");

    TreeSet<std::string> myTree;

    affirm(myTree.size() == 0);
    affirm(myTree.height() == -1);
    affirm(!myTree.exists("a"));
    return log.summarize();
}

bool testExists2() {
    TestingLogger log("Exists in tree");

    TreeSet<std::string> myTree;
    myTree.insert("a");

    affirm(myTree.size() == 1);
    affirm(myTree.exists("a"));
    return log.summarize();
}

bool testExistsInt() {
    TestingLogger log("Exists in empty tree with int elements");

    TreeSet<int> myTree;

    affirm(myTree.size() == 0);
    affirm(myTree.height() == -1);
    affirm(!myTree.exists(1));
    return log.summarize();
}

bool testExistsDouble() {
    TestingLogger log("Exists in tree with double elements");

    TreeSet<double> myTree;
    myTree.insert(1.1);

    affirm(myTree.size() == 1);
    affirm(myTree.exists(1.1));
    return log.summarize();
}

bool testExistsLeafyTree() {
    TestingLogger log("Exists in empty Leaf tree");

    TreeSet<std::string> myTree{LEAF};

    affirm(myTree.size() == 0);
    affirm(myTree.height() == -1);
    affirm(!myTree.exists("a"));
    return log.summarize();
}

bool testPrint1() {
    TestingLogger log("Print empty tree");

    TreeSet<std::string> myTree;
    stringstream ss;
    ss << myTree;

    affirm(ss.str() == "-");
    affirm(myTree.size() == 0);
    return log.summarize();
}

bool testPrint2() {
    TestingLogger log("Print single node");

    TreeSet<std::string> myTree;
    myTree.insert("a");

    stringstream ss;
    ss << myTree;

    affirm(ss.str() == "(-, a, -)");
    affirm(myTree.size() == 1);
    affirm(myTree.exists("a"));
    return log.summarize();
}

bool testPrintInt() {
    TestingLogger log("Print single node of int");

    TreeSet<int> myTree;
    myTree.insert(2);

    stringstream ss;
    ss << myTree;

    affirm(ss.str() == "(-, 2, -)");
    affirm(myTree.size() == 1);
    affirm(myTree.exists(2));
    return log.summarize();
}

bool testPrintDouble() {
    TestingLogger log("Print single node of double");

    TreeSet<double> myTree;
    myTree.insert(1.2);

    stringstream ss;
    ss << myTree;

    affirm(ss.str() == "(-, 1.2, -)");
    affirm(myTree.size() == 1);
    affirm(myTree.exists(1.2));
    return log.summarize();
}

bool testPrintSize1() {
    TestingLogger log("Size print of an empty tree");

    TreeSet<std::string> myTree;
    stringstream ss;
    ss << myTree;

    affirm(ss.str() == "-");
    affirm(myTree.size() == 0);
    return log.summarize();
}

bool testPrintSize2() {
    TestingLogger log("Size print single node");

    TreeSet<int> myTree;
    myTree.insert(2);

    stringstream ss;
    myTree.printSizesToStream(ss);

    affirm(ss.str() == "(0, 1, 0)");
    affirm(myTree.size() == 1);
    affirm(myTree.exists(2));
    return log.summarize();
}

bool testPrintSize3() {
    TestingLogger log("Size print three node");

    TreeSet<int> myTree{ROOT};
    myTree.insert(60);
    myTree.insert(50);
    myTree.insert(55);
    stringstream ss;
    myTree.printSizesToStream(ss);

    affirm_expected(ss.str(), "((0, 1, 0), 3, (0, 1, 0))");
    affirm(myTree.size() == 3);
    return log.summarize();
}

bool testBegin0() {
    TestingLogger log("Iterator on empty tree");

    TreeSet<std::string> myTree;
    TreeSet<std::string>::const_iterator iter = myTree.begin();

    affirm(myTree.size() == 0);
    return log.summarize();
}

bool testBegin1() {
    TestingLogger log("Iterator on single Node tree");

    TreeSet<std::string> myTree;
    myTree.insert("a");
    TreeSet<std::string>::const_iterator iter = myTree.begin();

    affirm(*iter == "a");
    return log.summarize();
}

bool testBegin2() {
    TestingLogger log("Iterator on balanced tree");

    TreeSet<std::string> myTree;
    myTree.insert("m");
    myTree.insert("b");
    myTree.insert("a");
    myTree.insert("c");
    myTree.insert("x");
    myTree.insert("y");
    TreeSet<std::string>::const_iterator iter = myTree.begin();

    affirm(*iter == "a");
    return log.summarize();
}

bool testBegin3() {
    TestingLogger log("Iterator on linked list");

    TreeSet<std::string> myTree;
    myTree.insert("e");
    myTree.insert("d");
    myTree.insert("c");
    myTree.insert("b");
    myTree.insert("a");
    TreeSet<std::string>::const_iterator iter = myTree.begin();

    affirm(*iter == "a");
    return log.summarize();
}

bool testBeginInt() {
    TestingLogger log("Checking begin of tree of int");

    TreeSet<int> myTree;
    myTree.insert(5);
    myTree.insert(4);
    myTree.insert(1);
    myTree.insert(3);
    myTree.insert(20);
    myTree.insert(21);
    TreeSet<int>::const_iterator iter = myTree.begin();

    affirm(*iter == 1);
    return log.summarize();
}

bool testBeginDouble() {
    TestingLogger log("Checking begin of tree of double");

    TreeSet<double> myTree;
    myTree.insert(5.0);
    myTree.insert(4.0);
    myTree.insert(1.0);
    myTree.insert(3.0);
    myTree.insert(20.0);
    myTree.insert(21.0);
    TreeSet<double>::const_iterator iter = myTree.begin();

    affirm(*iter == 1.0);
    return log.summarize();
}

bool testIncrement1() {
    TestingLogger log("Increment on two node tree");

    TreeSet<std::string> myTree;
    myTree.insert("a");
    myTree.insert("b");
    TreeSet<std::string>::const_iterator iter = myTree.begin();
    ++iter;

    affirm(*iter == "b");
    return log.summarize();
}

bool testIncrement2() {
    TestingLogger log("Increment on two node tree");

    TreeSet<std::string> myTree;
    myTree.insert("m");
    myTree.insert("b");
    myTree.insert("a");
    myTree.insert("c");
    myTree.insert("x");
    myTree.insert("y");
    TreeSet<std::string>::const_iterator iter = myTree.begin();

    ++iter;
    affirm(*iter == "b");

    ++iter;
    affirm(*iter == "c");

    ++iter;
    affirm(*iter == "m");

    ++iter;
    affirm(*iter == "x");

    ++iter;
    affirm(*iter == "y");

    return log.summarize();
}

bool testIncrementInt() {
    TestingLogger log("Increment on two node tree with int");

    TreeSet<int> myTree;
    myTree.insert(1);
    myTree.insert(2);
    TreeSet<int>::const_iterator iter = myTree.begin();
    ++iter;

    affirm(*iter == 2);
    return log.summarize();
}

bool testEquals1() {
    TestingLogger log("Begin iterators equal");

    TreeSet<std::string> myTree;
    myTree.insert("a");
    TreeSet<std::string>::const_iterator iter1 = myTree.begin();
    TreeSet<std::string>::const_iterator iter2 = myTree.begin();

    affirm(iter1 == iter2);
    return log.summarize();
}

bool testEquals2() {
    TestingLogger log("Iterators not equal");

    TreeSet<std::string> myTree;
    myTree.insert("a");
    myTree.insert("b");
    TreeSet<std::string>::const_iterator iter1 = myTree.begin();
    TreeSet<std::string>::const_iterator iter2 = myTree.begin();
    ++iter1;

    affirm(iter1 != iter2);
    return log.summarize();
}

bool testEqualsDouble() {
    TestingLogger log("Iterators not equal for Double tree");

    TreeSet<double> myTree;
    myTree.insert(1.1);
    myTree.insert(1.2);
    TreeSet<double>::const_iterator iter1 = myTree.begin();
    TreeSet<double>::const_iterator iter2 = myTree.begin();
    ++iter1;

    affirm(iter1 != iter2);
    return log.summarize();
}

bool testEnd0() {
    TestingLogger log("End iterator on empty tree");
    TreeSet<std::string> myTree;
    TreeSet<std::string>::const_iterator iter = myTree.end();

    affirm(myTree.size() == 0);
    return log.summarize();
}

bool testEnd1() {
    TestingLogger log("End iterator on balanced tree");

    TreeSet<std::string> myTree;
    myTree.insert("m");
    myTree.insert("b");
    myTree.insert("a");
    myTree.insert("c");
    myTree.insert("x");
    myTree.insert("y");
    TreeSet<std::string>::const_iterator iter = myTree.end();

    return log.summarize();
}

bool testEnd2() {
    TestingLogger log("End iterators equal");

    TreeSet<std::string> myTree;
    myTree.insert("m");
    myTree.insert("b");
    TreeSet<std::string>::const_iterator iter1 = myTree.end();
    TreeSet<std::string>::const_iterator iter2 = myTree.end();

    affirm(iter1 == iter2);
    return log.summarize();
}

bool testEndInt() {
    TestingLogger log("End iterators equal for int tree");

    TreeSet<int> myTree;
    myTree.insert(1);
    myTree.insert(2);
    TreeSet<int>::const_iterator iter1 = myTree.end();
    TreeSet<int>::const_iterator iter2 = myTree.end();

    affirm(iter1 == iter2);
    return log.summarize();
}
bool testBeginEnd0() {
    TestingLogger log("Begin and End iterator on empty tree");
    TreeSet<std::string> myTree;
    TreeSet<std::string>::const_iterator iter1 = myTree.begin();
    TreeSet<std::string>::const_iterator iter2 = myTree.end();

    affirm(myTree.size() == 0);
    affirm(iter1 == iter2);
    return log.summarize();
}

bool testBeginEnd1() {
    TestingLogger log("Begin and End iterator on empty tree");
    TreeSet<std::string> myTree;
    myTree.insert("a");
    TreeSet<std::string>::const_iterator iter1 = myTree.begin();
    TreeSet<std::string>::const_iterator iter2 = myTree.end();

    affirm(myTree.size() == 1);
    affirm(iter1 != iter2);
    return log.summarize();
}

bool testAdvanceToEnd() {
    TestingLogger log("Advanced and End iterator on non-empty tree");
    TreeSet<std::string> myTree;
    myTree.insert("a");
    TreeSet<std::string>::const_iterator iter1 = myTree.begin();
    TreeSet<std::string>::const_iterator iter2 = myTree.end();
    ++iter1;

    affirm(myTree.size() == 1);
    affirm(iter1 == iter2);
    return log.summarize();
}

bool testTreeEqual1() {
    TestingLogger log("Test two empty trees are equal");
    TreeSet<std::string> myTree1;
    TreeSet<std::string> myTree2;

    affirm(myTree1 == myTree2);
    return log.summarize();
}

bool testTreeEqual2() {
    TestingLogger log("Test two trees with 2 nodes are equal");
    TreeSet<std::string> myTree1;
    myTree1.insert("a");
    myTree1.insert("b");
    TreeSet<std::string> myTree2;
    myTree2.insert("b");
    myTree2.insert("a");

    affirm(myTree1 == myTree2);
    return log.summarize();
}

bool testTreeNotEqual1() {
    TestingLogger log("Test two equal size trees are not equal");
    TreeSet<std::string> myTree1;
    myTree1.insert("x");
    myTree1.insert("y");
    TreeSet<std::string> myTree2;
    myTree2.insert("b");
    myTree2.insert("a");

    affirm(myTree1 != myTree2);
    return log.summarize();
}

bool testTreeNotEqual2() {
    TestingLogger log("Test two different size trees are not equal");
    TreeSet<std::string> myTree1;
    myTree1.insert("a");
    TreeSet<std::string> myTree2;
    myTree2.insert("b");
    myTree2.insert("a");

    affirm(myTree1 != myTree2);
    return log.summarize();
}

bool testHeight0() {
    TestingLogger log("Height of empty tree");

    TreeSet<std::string> myTree;

    affirm(myTree.height() == -1);
    return log.summarize();
}

bool testHeight1() {
    TestingLogger log("Height of single Node tree");

    TreeSet<std::string> myTree;
    myTree.insert("a");

    affirm(myTree.height() == 0);
    return log.summarize();
}

bool testHeight2() {
    TestingLogger log("Height of balanced tree");

    TreeSet<std::string> myTree;
    myTree.insert("m");
    myTree.insert("b");
    myTree.insert("a");
    myTree.insert("c");
    myTree.insert("x");
    myTree.insert("y");

    affirm(myTree.height() == 2);
    return log.summarize();
}

bool testHeight3() {
    TestingLogger log("Height of linked list");

    TreeSet<std::string> myTree;
    myTree.insert("e");
    myTree.insert("d");
    myTree.insert("c");
    myTree.insert("b");
    myTree.insert("a");

    affirm(myTree.height() == 4);
    return log.summarize();
}

bool testDepth0() {
    TestingLogger log("Depth of empty tree");

    TreeSet<std::string> myTree;

    affirm(myTree.averageDepth() == 0);
    return log.summarize();
}

bool testDepth1() {
    TestingLogger log("Depth of single Node tree");

    TreeSet<std::string> myTree;
    myTree.insert("a");

    affirm(myTree.averageDepth() == 0);
    return log.summarize();
}

bool testDepth2() {
    TestingLogger log("Depth of balanced tree");

    TreeSet<std::string> myTree;
    myTree.insert("m");
    myTree.insert("b");
    myTree.insert("a");
    myTree.insert("c");
    myTree.insert("x");
    myTree.insert("y");
    affirm(myTree.size() == 6);
    affirm(myTree.averageDepth() == 4.0 / 3.0);
    return log.summarize();
}

bool testDepth3() {
    TestingLogger log("Depth of linked list");

    TreeSet<std::string> myTree;
    myTree.insert("e");
    myTree.insert("d");
    myTree.insert("c");
    myTree.insert("b");
    myTree.insert("a");
    affirm(myTree.averageDepth() == 2);
    return log.summarize();
}

bool testRootTreeSubsize() {
    TestingLogger log("Getting subsizes for a leaf insert tree");

    TreeSet<std::string> myTree;
    myTree.insert("m");
    myTree.insert("b");
    myTree.insert("a");
    myTree.insert("c");
    myTree.insert("x");
    myTree.insert("y");

    stringstream ss;
    myTree.printSizesToStream(ss);

    affirm_expected(ss.str(),
                    "(((0, 1, 0), 3, (0, 1, 0)), 6, (0, 2, (0, 1, 0)))");

    return log.summarize();
}

bool testRandomTree() {
    TestingLogger log("test two random trees");

    TreeSet<std::string> myTree1{RANDOMIZED, 42};
    TreeSet<std::string> myTree2{RANDOMIZED, 42};
    myTree1.insert("m");
    myTree1.insert("b");
    myTree1.insert("a");
    myTree1.insert("c");
    myTree1.insert("x");
    myTree1.insert("y");

    myTree2.insert("m");
    myTree2.insert("b");
    myTree2.insert("a");
    myTree2.insert("c");
    myTree2.insert("x");
    myTree2.insert("y");
    affirm(myTree1 == myTree2);
    return log.summarize();
}

int main() {
    TestingLogger alltests("All tests");
    testDefaultConstructor();
    testInsert1();
    testInsert2();
    testInsert3();
    testExists1();
    testExists2();
    testPrint1();
    testPrint2();
    testBegin0();
    testBegin1();
    testBegin2();
    testBegin3();
    testIncrement1();
    testIncrement2();
    testEquals1();
    testEquals2();
    testEnd0();
    testEnd1();
    testEnd2();
    testBeginEnd0();
    testBeginEnd1();
    testAdvanceToEnd();
    testTreeEqual1();
    testTreeEqual2();
    testTreeNotEqual1();
    testTreeNotEqual2();
    testHeight0();
    testHeight1();
    testHeight2();
    testHeight3();
    testDepth0();
    testDepth1();
    testDepth2();
    testDepth3();
    testInsertInt();
    testInsertDouble();
    testExistsInt();
    testExistsDouble();
    testPrintInt();
    testPrintDouble();
    testBeginInt();
    testBeginDouble();
    testIncrementInt();
    testEqualsDouble();
    testEndInt();
    testExistsLeafyTree();
    testOneParaConstructor();
    testRootInsert1();
    testRootInsert2();
    testRootInsert3();
    testPrintSize1();
    testPrintSize2();
    testPrintSize3();
    testRootTreeSubsize();
    testRandomTree();

    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
