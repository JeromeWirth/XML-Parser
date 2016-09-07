#include "element.hpp"

/**
 * Der Konstruktor der Elementklasse, da das Element bei
 * initialisierung noch kein geschlossenes Tag hat wird Valid auf false gesetzt.
 */
Element::Element() {
    valid = false;
}

/**
 * Der dekonstruktor von der Klasse
 */
Element::~Element() {
}


/**
 * Setzt den Namen des Elementes
 * @param s Name des Elementes
 */
void Element::setEleName(string s) {
    this->eleName = s;
}

/**
 * Setzte den Elementwert des Elementes
 * @param s Elementwert des Elements
 */
void Element::setEleValue(string s) {
    this->eleValue = s;
}

/**
 * Setzt den Attributnamen des Elements
 * @param s Attributnamen des Elements
 */
void Element::setAttrName(string s) {
    this->attrName = s;
}

/**
 * Setzt den Attributwert des Elementes
 * @param s Attributwert des Elementes
 */
void Element::setAttrValue(string s) {
    this->attrValue = s;
}

/**
 * Setzt die Hierarchieebene des Elementes
 * @param i Hierarchiebene des Elementes
 */
void Element::setTier(int i) {
    this->tier = i;
}

/**
 * Setzt das Element auf gültig/ungültig
 * @param b Gültigkeit des Elementes
 */
void Element::setValid(bool b) {
    this->valid = b;
}

/**
 * Gibt den Elementnamen zurück
 * @return Elementnamen
 */
string Element::getEleName() {
    return eleName;
}

/**
 * Gibt den Elementwert zurück
 * @return Elementwert
 */
string Element::getEleValue() {
    return eleValue;
}

/**
 * Gibt die Gültigkeit des Elementes zurück
 * @return Gültigkeit
 */
bool Element::getValid() {
    return valid;
}

/**
 * Gibt das Element auf der Konsole aus, dabei wird berücksichtigt, welche Optionen
 * als Kommandozeilenparameter übergeben wurden.
 * 
 * @param t Leerzeichen, welche vor dem Tag stehen
 * @param d Hierarchieebene, bis zu dem das Tag ausgegeben werden soll
 */
//TODO: setw funktioniert nicht richtig
void Element::print(int t, int d) {
    int temp = 0;
    temp = (tier * t) + 1;
    if(d == 0) {
        cout << setw(temp) << eleName << " " << attrName << ":" << attrValue << " " << eleValue <<  "temp: " << temp << endl;
    } else {
        if(tier <= d) {
            cout <<  setw(temp) << eleName << " " << attrName << ":" << attrValue << " " << eleValue <<  "temp: " << temp << endl;
        }
    }
    
}

