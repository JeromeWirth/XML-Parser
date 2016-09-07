/**
 * XMLV - Programm zum Parsen von XML-Dateien
 * 
 * Das Programm liest eine .xml-Datei ein,
 * analysiert die Elemente, schreibt sie dann in ein Klasse
 * und gibt sie dann wieder aus.
 * 
 * Mithilfe von Kommandozeilenparametern wird der Datei-Name,
 * sowie andere Optionen (tablength, noattr, notext und depth)
 * ausgegeben.
 * 
 * @author Jerome Wirth, s0532939
 * @date 05.07.2013
 */

#include <iostream>
#include <string>
#include <fstream>
#include "parser.hpp"
#include "param.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    Param param(argc, argv);
    param.checkParam();
    Parser p(param.getNOATTR(), param.getNOTEXT());

    string file;
    string input;
    ifstream inputFile;
    
    cout << "TABLELENGTH: " << param.getTablength();
    cout << "DEPTH: " << param.getDepth();
    cout << "NOATTR: " << param.getNOATTR();
    cout << "NOTEXT: " << param.getNOTEXT();
    
    if (param.getFile().size() == 0) {
        cout << "Error: Keine XML-Datei angegeben" << endl;
    } else {
        file = param.getFile();
        inputFile.open(file.c_str());
        // Prüfe, ob die Datei existiert
        if (!inputFile.good()) {
            cout << "Error: Datei laesst sich nicht oeffnen." << endl;
        } else {
            // Datei lässt sich öffnen, fange an zu Parsen
            while (getline(inputFile, input)) {
                p.setInput(input);
                p.processInput();
            }
            cout << "========================" << endl;
            p.printElements(param.getTablength(), param.getDepth());
            cout << "===========================" << endl;
        }
    }    
    
    cout << "TABLENGTH: " << param.getTablength() << endl;
}