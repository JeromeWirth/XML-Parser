#ifndef PARSER_HPP
#define	PARSER_HPP

/**
 * Parser.hpp
 * 
 * Die Klasse erzeugt einen Parser, es werden ganze Zeile einer 
 * Datei eingelesen, und dann Zeichen für Zeichen geprüft, 
 * dann wird der eingelesene String in die Elementtypen übertragen.
 * 
 * Der String wird nach jeden erfolgreich gefundenen Elementtyp gekürzt 
 * und der restliche String wird überprüft.
 * 
 * Wenn der ganze String durchlaufen wurde, kann man der Klasse einen
 * neuen String übergeben.
 * 
 * @author Jerome Wirth, s0532939
 * @date 05.07.2013
 */

#include <iostream>
#include <string>
#include <vector>
#include "element.hpp"

using namespace std;

class Parser {
    
public:
    Parser(bool noattr, bool notext);
    ~Parser();
    
    void processInput();
    void setInput(string input);
    void normalize();
    void processStartTag(string start);
    void processEndTag();
    void processTagValue();
    void processSystemTag();
    void printElements(int t, int d);
    
    void setNewElement(string eleName, string attrName, string attrValue);
    
    string getString(string a, string b);
    string getString(char a, char b);
    int validElements();
    
private:
    int tier;
    string s;
    Element e;
    vector<Element> elementList;
    vector<Element>::reverse_iterator it;
    bool noattr;
    bool notext;
};

#endif	/* PARSER_HPP */

