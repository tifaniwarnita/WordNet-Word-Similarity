#ifndef BINARYTREE_H
#define BINARYTREE_H


#include <vector>
#include "Node.h"

class BinaryTree {
public:
    //! CONSTRUCTOR AND DESTRUCTOR
    /** Default constructor */
    BinaryTree();
    /** Default destructor */
    virtual ~BinaryTree();

    //! GETTER AND SETTER
    /** Access root
     * \return The current value of *root
     */
    Node *getRoot() { return root; }
    /** Set root
     * \param _root New value to set
     */
    void setRoot(Node *_root) { root = _root; }
    /** Access depth
     * \return The current value of depth
     */
    unsigned int getDepth() { return depth; }
    /** Set depth
     * \param _depth New value to set
     */
    void setDepth(unsigned int _depth) { depth = _depth; }

    //! OTHER OPERATIONS
    void insert(std::vector<std::string> words);
    Node *search(std::string word);
    void destroyTree();
    void printTree();

protected:

private:
    //! OTHER OPERATIONS
    void destroyTree(Node *leaf);
    void insert(Node *newNode);
    void insert(Node *newNode, Node *leaf);
    Node *search(std::string word, Node *leaf);
    void printTree(Node *leaf);

    //! MEMBERS
    Node *root; //!< Member variable "*root"
    unsigned int depth; //!< Member variable "depth"
};

#endif // BINARYTREE_H
