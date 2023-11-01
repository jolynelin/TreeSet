#include "treeset.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <system_error>
#include <cerrno>
#include <chrono>
#include <random>
#include <cstddef>

/**
 * \brief Fill a std::vector of words using content from a file.
 * \param words The vector to fill.
 * \param filename The file to read.
 */
void readWords(std::vector<std::string>& words, std::string filename) {
    std::cerr << "Reading words from " << filename << "...";
    try {
        std::ifstream in;
        in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        in.open(filename);
        in.exceptions(std::ifstream::badbit);
        std::string word;
        for (;;) {
            in >> word;
            if (!in.good()) {
                break;
            }
            words.push_back(word);
        }
        std::cerr << " done!\n";
    } catch (std::system_error& e) {
        // The error exceptions thrown by our standard library aren't very
        // meaningful, so we catch them and rethrow them with more information.
        throw std::system_error(
            std::make_error_code(std::errc(errno)),
            "Error reading '" + filename + "' (" + e.code().message() + +")");
    }
}

/**
 * \brief Fill a TreeSet<std::string> using content from a vector of words.
 *        The order that the words are inserted is exactly the order in the
 *        vector.  The vector is emptied of words as part of this process.
 * \param dict The TreeSet<std::string> to insert into.
 * \param words The vector from which the words will be taken.
 */
void insertAsRead(TreeSet<std::string>& dict, std::vector<std::string>& words) {
    for (const auto& word : words) {
        dict.insert(word);
    }
    words.clear();
}

/**
 * \brief Fill a TreeSet<std::string> using content from a vector of words.
 *        The words are inserted in a random order.  The vector is emptied of
 *        words as part of this process.
 * \param dict The TreeSet<std::string> to insert into.
 * \param words The vector from which the words will be taken.
 */
void insertShuffled(TreeSet<std::string>& dict,
                    std::vector<std::string>& words) {
    std::random_device rdev;
    std::mt19937 prng{rdev()};  // This is only a 32-bit seed (weak!), but meh.
    std::shuffle(words.begin(), words.end(), prng);
    insertAsRead(dict, words);
}

/**
 * \brief This is a helper function, you can ignore it.  Bit it inserts the
 *        middle element, and the recurses to insert all the nodes to the left
 *        and to the right.  It'll build a balanced tree.
 */
void insertBalancedHelper(TreeSet<std::string>& dict,
                          std::vector<std::string>& words, size_t start,
                          size_t pastEnd) {
    if (start >= pastEnd) {
        return;
    }
    size_t size = pastEnd - start;
    size_t mid = start + size / 2;
    dict.insert(words[mid]);
    insertBalancedHelper(dict, words, start, mid);
    insertBalancedHelper(dict, words, mid + 1, pastEnd);
}

/**
 * \brief Fill a TreeSet<std::string> using content from a vector of words.
 *        It builds a very balanced tree because it firsts sorts the data,
 *        recursively puts the mittle element at the root.
 * \param dict The TreeSet<std::string> to insert into.
 * \param words The vector from which the words will be taken.
 */
void insertBalanced(TreeSet<std::string>& dict,
                    std::vector<std::string>& words) {
    std::sort(words.begin(), words.end());
    insertBalancedHelper(dict, words, 0, words.size());
    words.clear();
}

/**
 * \brief Main program,
 */
int main(int argc, const char** argv) {
    // Defaults
    enum { AS_READ, SHUFFLED, BALANCED } insertionOrder = AS_READ;
    bst_style insertScheme = LEAF;
    std::string dictFile = "/home/student/data/smalldict.words";
    std::string fileToCheck = "/home/student/data/ispell.words";

    // Process Options and command-line arguments
    std::list<std::string> args(argv + 1, argv + argc);
    while (!args.empty() && args.front()[0] == '-') {
        if (args.front() == "-n") {
            insertionOrder = AS_READ;
        } else if (args.front() == "-s") {
            insertionOrder = SHUFFLED;
        } else if (args.front() == "-r") {
            insertScheme = RANDOMIZED;
        } else if (args.front() == "-m") {
            insertScheme = ROOT;
        } else if (args.front() == "-b") {
            insertionOrder = BALANCED;
        } else if (args.front() == "-d") {
            args.pop_front();
            if (args.empty()) {
                std::cerr << "-d expects a filename\n";
                return 1;
            }
            dictFile = args.front();
        } else {
            std::cerr << "invalid option, " << args.front() << std::endl;
            return 1;
        }
        args.pop_front();
    }
    if (!args.empty()) {
        fileToCheck = args.front();
        args.pop_front();
        if (!args.empty()) {
            std::cerr << "extra argument(s), " << args.front() << std::endl;
            return 1;
        }
    }

    // Read the dictionary into a vector
    std::vector<std::string> words;
    readWords(words, dictFile);

    // Create our search tree (and time how long it all takes)
    if (insertScheme == RANDOMIZED) {
        std::cerr << "Randomized";
    } else if (insertScheme == ROOT) {
        std::cerr << "Root";
    } else {
        std::cerr << "Leaf";
    }
    std::cerr << "-inserting into dictionary ";
    auto startTime = std::chrono::high_resolution_clock::now();

    TreeSet<std::string> dict{insertScheme};
    if (insertionOrder == AS_READ) {
        std::cerr << "(in order read)...";
        insertAsRead(dict, words);
    } else if (insertionOrder == SHUFFLED) {
        std::cerr << "(in shuffled order)...";
        insertShuffled(dict, words);
    } else if (insertionOrder == BALANCED) {
        std::cerr << "(in perfect-balance order)...";
        insertBalanced(dict, words);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> secs = endTime - startTime;
    std::cerr << " done!\n";

    // Print some stats about the process

    std::cout << " - insertion took " << secs.count() << " seconds\n - ";
    dict.showStatistics(std::cout);
    auto iter = dict.begin();
    std::advance(iter, dict.size() / 2);
    std::cout << " - median word in dictionary: '" << *iter << "'\n\n";

    // Read some words to check against our dictionary (and time it)

    readWords(words, fileToCheck);
    std::cerr << "Looking up these words in the dictionary...";
    size_t inDict = 0;
    startTime = std::chrono::high_resolution_clock::now();
    for (const auto& word : words) {
        if (dict.exists(word)) {
            ++inDict;
        }
    }

    endTime = std::chrono::high_resolution_clock::now();
    secs = endTime - startTime;
    std::cerr << " done!\n";

    // Show some stats

    std::cout << " - looking up took " << secs.count() << " seconds\n - ";
    std::cout << words.size() << " words read, " << inDict
              << " in dictionary\n\n";

    return 0;
}
