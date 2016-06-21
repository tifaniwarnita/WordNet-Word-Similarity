#ifndef NODE_H
#define NODE_H

#include <string>


class Node {
public:
    //! CONSTRUCTOR AND DESTRUCTOR
    /** Default constructor */
    Node();
    /** Constructor with parameter */
    Node(std::string _word);
    /** Constructor with parameter */
    Node(unsigned int _distance, std::string _word);
    /** Default destructor */
    virtual ~Node();

    //! GETTER AND SETTER
    /** Access distance
     * \return The current value of distance
     */
    unsigned int getDistance() { return distance; }
    /** Set distance
     * \param _distance New value to set
     */
    void setDistance(unsigned int _distance) { distance = _distance; }
    /** Access word
     * \return The current value of word
     */
    std::string getWord() { return word; }
    /** Set word
     * \param _word New value to set
     */
    void setWord(std::string _word) { word = _word; }
    /** Access left node
     * \return The current value of left node
     */
    Node *getLeft() { return left; }
    /** Set left node
     * \param _left New value to set
     */
    void setLeft(Node *_left) { left = _left; }
    /** Access right node
     * \return The current value of right node
     */
    Node *getRight() { return right; }
    /** Set right node
     * \param _right New value to set
     */
    void setRight(Node *_right) { right = _right; }

protected:

private:
    unsigned int distance; //!< Distance from leaf
    std::string word; //!< Node representation in std::string
    Node *left; //!< Pointer to left node
    Node *right; //!< Pointer to right node
};

#endif // NODE_H
