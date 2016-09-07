#ifndef ELEMENT_HPP
#define	ELEMENT_HPP

/**
 * Element.hpp
 * 
 * Die Klasse legt ein neues XML-Element an,
 * sie beinhaltet Elementnamen, Elementwert, Attributnamen und
 * Attributwert, des weiteren wird die Hierarchieeben gespeichert.
 * 
 * @author Jerome Wirth, s0532939
 * @date 05.07.2013
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Element {
public:
    Element();
    ~Element();
    
    void setEleName(string s);
    void setEleValue(string s);
    void setAttrName(string s);
    void setAttrValue(string s);
    void setTier(int i);
    void setValid(bool b);
    
    string getEleName();
    string getEleValue();
    bool getValid();
    
    void print(int t, int d);
    
private:
    string eleName;
    string eleValue;
    string attrName;
    string attrValue;
    int tier;
    bool valid;
};

#endif	/* ELEMENT_HPP */

