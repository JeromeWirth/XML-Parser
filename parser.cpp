#include "parser.hpp"

/**
 * Die Funktion erstellt einen Parser, die Variable "tier"
 * wird mit 0 initialisiert um den Elementen einen richtigen Wert zuweisen
 * zu können.
 * 
 * @param noattr Der boolesche Wert gibt an, ob Attribute angezeigt werden sollen
 * @param notext Der boolesche Wert gibt an, ob Text angezeigt werden soll
 */
Parser::Parser(bool noattr = false, bool notext = false) {
    tier = 0;

    this->noattr = noattr;
    this->notext = notext;
}

/**
 * Der Dekonstruktor für die Klasse
 */
Parser::~Parser() {
}

/**
 * Die Funktion liest einen String solange ein, bis er die größe 0 hat.
 * Anhand des ersten Zeichen des Strings wird entschieden, wie der String
 * weiter verarbeitet werden soll.
 * 
 * Sollte das erste Zeichen ein Leerzeichen oder Tab sein, so wird dieser String
 * erstmal normalisiert und dann weiter verarbeitet.
 */
void Parser::processInput() {
    while (s.size() != 0) {
        cout << "STRING: " << s << endl;
        cout << "STRING SIZE: " << s.size() << endl;
        cout << "ERSTES ZEICHEN: " << s[0] << endl;
        cout << "----------------------" << endl;
        normalize();

        // Bei einem Leeren String:
        if (s.size() == 0) {
            cout << "Error: String enthaelt keine Werte" << endl;
        } else if (s[0] == '<') {
            //Wenn weiterers zeichen ein ! oder ? ist
            if (s[1] == '!' || s[1] == '?' || s[1] == '-') {
                cout << "Pruefe auf Kommentar oder Anweisung" << endl;
                processSystemTag();
            } else if (s[1] == '/') {
                processEndTag();
            } else {
                cout << "'<' gefunden parse Starttag" << endl;
                string temp = s.substr(0, s.find('>') + 1);
                cout << "STRING FUER STARTTAG: " << temp << endl;
                cout << "-----------------" << endl;
                processStartTag(temp);
            }
        } else {
            // Wenn kein < gefunden wurde, aber der String Zeichen enthält
            // handelt es sich um den Elementwert!
            processTagValue();
        }
    }
}

/**
 * Der Funktion übergibt man einen String, welcher von der Klasse
 * verarbeitet werden soll
 * @param input Der zu anaylsierende String
 */
void Parser::setInput(string input) {
    this->s = input;
    cout << endl;
    cout << "String: " << s << endl;
    cout << "-------------------" << endl;
}

/**
 * Die Funktion "normalisiert" den String, das heisst, wenn der String
 * Leerzeichen oder Tabs vor dem ersten Zeichen hat, werden die Leerzeichen/Tabs
 * solange gelöscht, bis man am ersten Zeichen angekommen ist und der String weiter
 * verarbeiten kann, oder der String leer ist, dann ist der String zuende verarbeitet.
 */
void Parser::normalize() {
    int i = 0;
    if (s[i] == ' ' || s[i] == '\t') {
        cout << "String beinhaltet ein Leerzeichen als erstes Zeichen." << endl;
        cout << "Starte Normalisierung!" << endl;

        while (s[i] == ' ' || s[i] == '\t') {
            i++;
        }
        s = s.substr(i);
        cout << "Neuer String: " << s << endl;
    }
}

/**
 * Die Funktion analysiert den Starttag, wenn processInput() eine öffnende eckige
 * Klammer gefunden hat, teilt die funktion den String auf und übermittelt den String
 * in dem sich nur der Starttag (also alles zwischen '<' und '>') befindet, an die Funktion
 * processStartTag.
 * Wenn der String fertig verarbeitet wurde, wird er von dem ursprünglichen String
 * subtrahiert.
 * 
 * @param start Der String der den gesamten Starttag beinhaltet
 */
void Parser::processStartTag(string start) {
    if (start.find('<') != string::npos && start.find('>') != string::npos) {
        cout << "Analysiere Start-Tag" << endl;
        cout << "------------------" << endl;
        string temp;

        //Enthält das Tag Attribute?
        if (start.find(' ') != string::npos) {
            cout << "Tag Enthaelt Attribute:" << endl;

            string eleName, attrName, attrValue;

            eleName = getString('<', ' ');
            eleName = "<" + eleName + ">";

            attrName = getString(' ', '=');
            attrValue = getString('\"', '\"');

            cout << "Elementnamen: " << eleName << endl;
            cout << "Attributenamen: " << attrName << endl;
            cout << "Attributwert: " << attrValue << endl;

            setNewElement(eleName, attrName, attrValue);

        } else {
            // Element ohne Attribute
            temp = getString('<', '>');
            temp = "<" + temp + ">";

            cout << "Tag enthaelt nur Namen: " << temp << endl;

            setNewElement(temp, "", "");
        }

        // Nachdem StartTag verarbeitet wurde, kann dieser vom
        // ursprünglichen String entfernt werden
        s = s.substr(start.size());
        cout << "Uebriger String:" << s << endl;

    } else {
        cout << "Error: Syntaxfehler im Tag" << endl;
    }
}

/**
 * Die funktion analysiert den Tag auf Zeichen, welche auf Kommentare und Systemanweisungen
 * hindeuten, dann wird der String ignoriert, oder falls erkannt wurde das es ein
 * Syntaxfehler in dem Tag gibt, eine Fehlermeldung ausgegeben.
 */
void Parser::processSystemTag() {
    if (s.find("<--") != string::npos && s.find("-->") != string::npos) {
        cout << "Kommentar gefunden, wird ignoriert" << endl;
        s = "";
    } else if (s.find("<?") != string::npos && s.find("?>")) {
        cout << "Systemanweisung gefunden, wird ignoriert" << endl;
        s = "";
    } else if (s.find("<!DOCTYPE") != string::npos) {
        cout << "DOCTYPE-Anweisung gefunden, wird ignoriert." << endl;
        s = "";
    } else {
        cout << "Eror: Syntaxfehler bei Kommentar/Systemtag." << endl;
    }
}

/**
 * Die Klasse arbeitet mit ganzen Strings mit dieser Funktion wird der String
 * zwischen den beiden angegeben strings aufgeteilt.
 * 
 * @param a Startzeichenkette, ab dem der String aufgeteilt werden soll
 * @param b Endzeichenkette, bis wohin der String aufgeteilt werden soll
 * @return String, welche zwischen den beiden Zeichenkette war.
 */
string Parser::getString(string a, string b) {
    size_t posStart;
    size_t posEnd;

    string temp;

    if (a == b) {
        posStart = s.find(a) + 1;
        posEnd = s.rfind(b);
    } else {
        posStart = s.find(a) + 1;
        posEnd = s.find(b);
    }

    temp = s.substr(posStart, (posEnd - posStart));

    return temp;
}

/**
 * Die Klasse arbeitet mit ganzen Strings mit dieser Funktion wird der String
 * zwischen den beiden angegeben Chars aufgeteilt.
 * 
 * @param a Startzeichen, ab dem der String aufgeteilt werden soll
 * @param b Endzeichen, bis wohin der String aufgeteilt werden soll
 * @return String, welche zwischen den beiden Zeichen war.
 */
string Parser::getString(char a, char b) {
    size_t posStart;
    size_t posEnd;

    string temp;

    if (a == b) {
        posStart = s.find(a) + 1;
        posEnd = s.rfind(b);
    } else {
        posStart = s.find(a) + 1;
        posEnd = s.find(b);
    }

    temp = s.substr(posStart, (posEnd - posStart));

    return temp;
}

/**
 * Es wurde ein schließendes Tag gefunden, und nun wird geprüft, zu welchen öffnenden Tag
 * das Tag gehört.
 * 
 * Da das letzte öffnende Tag als erstes geschlossen werden muss, wird die vector-List,
 * in welchen sich die Elemente befinden, von hinten nach vorne geprüft.
 * Wenn man dann auf ein Element gestoßen ist, welches noch nicht Valid ist, also noch kein
 * schliessendes Tag hat, und der Name der beiden Tags gleich ist, wird das schliessenden Tag,
 * diesem Tag zugewiesen.
 */
void Parser::processEndTag() {
    cout << "</ gefunden, analysiere schliessendes Tag." << endl;
    cout << "EndTagWert: " << getString('/', '>') << endl;

    string search = getString('/', '>');

    // Durchsuche die Arraylist von Hinten nach vorne und finde das erste Element mit dem gesuchten string
    for (it = elementList.rbegin(); it != elementList.rend(); ++it) {
        if ((*it).getEleName().find(search) != string::npos && (*it).getValid() != true) {
            cout << "ELEMENT: " << (*it).getEleName() << " WIRD AUF VALID GESETZT" << endl;
            (*it).setValid(true);
            break;
        }
    }

    // Setzte Hierarchieebene wieder eins zurück, nachdem das schliessende Tag
    // erfolgreich gefunden wurde
    tier--;

    // EndTag wurde analysiert, entferne ihn vom ursprünglichen String
    s = s.substr(s.find('>') + 1);
}

/**
 * Wenn ein Zeichen gefunden wurde, welches keine öffnende oder schliessende Klammer
 * ist, wird davon ausgegangen, dass es sich um den Elementwert handel.
 * 
 * Dazu wird geprüft, ob sich in dem String noch eine klammer befindet oder ob
 * nur noch Text in dem string steht, nach der verarbeitung wird dieser String
 * wieder vom ursprünglichen String abgezogen.
 */
void Parser::processTagValue() {
    cout << "Kein oeffnendes Tag gefunden, anaysiere ElementWert" << endl;
    if (s.find('<') != string::npos) {
        // Schliessendes Tag gefunden, ElementWert befindet sich davor
        cout << "Im String befinden sich ELEVALUE und TAGCLOSE" << endl;
        cout << "ElementWert: " << s.substr(0, s.find('<')) << endl;

        // Der Elementwert gehört IMMER zu dem letzten Element,
        // welche zuletzt geöffnet wurde, falls dieses Element noch kein EleValue hat
        // Durchsuche die Arraylist von Hinten nach vorne und finde das erste Element mit dem gesuchten string
        if (!notext) {
            for (it = elementList.rbegin(); it != elementList.rend(); ++it) {
                if ((*it).getEleValue().size() == 0) {
                    cout << "ELEMENT: " << (*it).getEleName() << " KRIEGT VALUE" << endl;
                    (*it).setEleValue(s.substr(0, s.find('<')));
                    break;
                }
            }
        }
        s = s.substr(s.find('<'));
    } else {
        cout << "ElementWert: " << s << endl;
        if (!notext) {
            for (it = elementList.rbegin(); it != elementList.rend(); ++it) {
                if ((*it).getEleValue().size() == 0) {
                    cout << "ELEMENT: " << (*it).getEleName() << " KRIEGT VALUE" << endl;
                    (*it).setEleValue(s);
                    break;
                }
            }
        }
        s = "";
    }
    cout << endl;
}

/**
 * Durchläuft alle Elemente vom vector und führt die print()-Funktion aus
 * 
 * @param t Wieviele Leerstellen sollen vor jedem Tag stehen
 * @param d Bis zu welcher Hierarchieebene sollen die Tags ausgegeben werden
 */
void Parser::printElements(int t, int d) {
    for (int i = 0; i < elementList.size(); ++i) {
        elementList.at(i).print(t, d);
    }
}

/**
 * Die Funktion erstellt ein neues Element und fügt diese dann zu dem vector hinzu
 * 
 * @param eleName Der Elementnamen des Elements
 * @param attrName Der Attribut Namen des Elements
 * @param attrValue Der Attribut Wert des Elements
 */
void Parser::setNewElement(string eleName, string attrName, string attrValue) {
    e.setEleName(eleName);
    if (!noattr) {
        e.setAttrName(attrName);
        e.setAttrValue(attrValue);
    }

    e.setTier(tier);

    // Wenn alle Daten für das StartTag gefunden, füge es in die VectorListe
    cout << "ELEMENT WIRD IN DIE ARRAYLIST GESCHOBEN" << endl;
    elementList.push_back(e);
    cout << "TIER WIRD VON: " << tier;
    tier++;
    cout << " AUF " << tier << " GESETZT!" << endl;
    cout << "------------------" << endl;
}

/**
 * Durchlauft den vector und prüft, ob die Elemente auch ein
 * geschlossenenes Tag besitzen
 * 
 * @return Die anzahl, an nicht gültigen Tags. 
 */
int Parser::validElements() {
    int count = 0;
    for (int i = 0; i < elementList.size(); ++i) {
        if (elementList.at(i).getValid() != true) {
            count++;
        }
    }
    
    return count;
}