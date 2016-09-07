#ifndef PARAM_HPP
#define	PARAM_HPP

/**
 * Param.hpp
 * 
 * Die Klasse verarbeitet die Kommandozeilenparameter
 * welche beim Start des Programms übergeben wurde.
 * 
 * @author Jerome Wirth, s0532939
 * @date 05.07.2013
 */

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Param {
public:
    Param(int argc, char **argv);
    ~Param();
    
    void checkParam();
    void printParam();
    
    string getFile();
    int getDepth();
    int getTablength();
    bool getNOATTR();
    bool getNOTEXT();
    
private:
    int count;
    char **value;
    
    int depth;
    int tablength;
    bool noattr;
    bool notext;
    string file;
};

#endif	/* PARAM_HPP */

