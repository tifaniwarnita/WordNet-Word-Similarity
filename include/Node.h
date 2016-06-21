#ifndef NODE_H
#define NODE_H


class Node {
public:
    /** Default constructor */
    Node();
    /** Default destructor */
    ~Node();

    /** Access distance
     * \return The current value of distance
     */
    unsigned int getDistance() { return distance; }
    /** Set distance
     * \param val New value to set
     */
    void setDistance(unsigned int val) { distance = val; }
    /** Access word
     * \return The current value of word
     */
    string getWord() { return word; }
    /** Set word
     * \param val New value to set
     */
    void setWord(string val) { word = val; }

protected:

private:
    unsigned int distance; //!< Member variable "distance"
    string word; //!< Member variable "word"
};

#endif // NODE_H
