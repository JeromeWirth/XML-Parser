/* 
 * File:   param.cpp
 * Author: Jerry
 * 
 * Created on 5. Juli 2013, 12:39
 */

#include "param.hpp"

/**
 * Initialisiert das Objekt mit den Werten, welche als Kommandozeilenparameter
 * übergeben wurden und die Klassenvariablen kriegen standartwerte.
 * 
 * @param argc Anzahl der Elemente, welche übergeben wurden
 * @param argv Werte, welche übergeben wurden
 */
Param::Param(int argc, char **argv) {
    this->count = argc;
    this->value = argv;
    
    this->depth = 0;
    this->noattr = false;
    this->notext = false;
    this->tablength = 3;
}

/**
 * Der Dekonstruktor der Klasse
 */
Param::~Param() {
}

/**
 * Überprüft die Parameter und setzte die Klassenvariablen auf die
 * richtigen Werte.
 * 
 * Dazu wird der Wert in argv[i] als erstes in ein String geschrieben, damit man
 * die Funktionen für das Suchen in einem String nutzen kann, und so schneller herausfinden kann,
 * ob eine Option angegeben wurde
 */
void Param::checkParam() {
    if(count <= 1) {
        cout << "PROGRAMMINFORMATIONEN" << endl;
    }    
    for(int i = 1; i < count; i++) {
        string temp = value[i];
        
        if(temp.find(".xml") != string::npos) {
            cout << "XML-Datei angegeben" << endl;
            file = temp;
        } else if (temp.find("depth") != string::npos) {
            cout << "Depth-Option angegeben" << endl;
            temp = temp.substr(temp.find('=')+1);
            depth = atoi(temp.c_str());
            cout << "DEPTH: " << depth << endl;
        } else if (temp.find("noattr") != string::npos) {
            cout << "noattr-Option angegeben" << endl;
            noattr = true;
        } else if (temp.find("notext") != string::npos) {
            cout << "notext-Option angegeben" << endl;
            notext = true;
        } else if (temp.find("tablength") != string::npos) {
            cout << "tablength angegeben" << endl;
            temp = temp.substr(temp.find('=')+1);
            tablength = atoi(temp.c_str());
            cout << "TABLENGTH: " << tablength << endl;
        } else {
            cout << "Keine gueltige Optione, bitte lesen Sie mit dem parameter -h" << endl;
            cout << "welche Zusatzparameter angegeben werden koennen." << endl;
        }
    }
}

/**
 * Gibt die Kommandozeilenparameter wieder auf der Konsole aus
 */
void Param::printParam() {
    
    cout << "Gebe Kommandozeilenparameter aus:" << endl;
    
    for(int i = 1; i < count; i++) {
        cout << value[i] << endl;
    }
}

/**
 * Gibt den String zurück, welche den Wert für die xml-Datei enthält
 * 
 * @return Die zu öffnende .xml-Datei
 */
string Param::getFile() {
    return file;
}

/**
 * Gibt den Wert zurück, bis zu welcher Hierarchiebene die XML-Elemente
 * ausgegeben werden sollen
 * 
 * @return Hierarchiebene, bis zu welchen die Elemente ausgegebn werden sollen 
 */
int Param::getDepth() {
    return depth;
}

/**
 * Gibt den Wert zurück, wieviele Leerzeichen vor jedem Element stehen sollen
 * 
 * @return Leerzeichen, die vor einem Element stehen sollen 
 */
int Param::getTablength() {
    return tablength;
}

/**
 * Gibt den Wert zurück, ob die Option "noattr" angegeben wurde
 * 
 * @return Sollen Attribute mit ausgegeben werden? 
 */
bool Param::getNOATTR() {
    return noattr;
}

/**
 * Gibt den Wert zurück, ob die Option "notext" angegeben wurde
 * 
 * @return Soll Text ausgegeben werden?
 */
bool Param::getNOTEXT() {
    return notext;
}
