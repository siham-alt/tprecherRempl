#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;


int remplacerDansMot(string& mot, const string& cherche, const string& remplace) {
    int nb = 0;
    size_t pos = mot.find(cherche);

    while (pos != string::npos) {
        mot.replace(pos, cherche.size(), remplace);   
        nb++;
        pos += remplace.size();                       
        pos = mot.find(cherche, pos);                 
    }
    return nb;
}

// =====================================================
// Lecture du fichier : tous les mots vont dans un vector
// =====================================================
vector<string> chargerMots(const string& nomFichier) {
    vector<string> mots;
    ifstream fichier(nomFichier);

    if (!fichier) {
        return mots;
    }

    string mot;
    while (fichier >> mot) {
        mots.push_back(mot);
    }
    return mots;
}

// =====================================================
// Recherche + remplacement dans un fichier
// =====================================================
void traiterFichier(const string& nomFichier,
                    const string& cherche,
                    const string& remplace) {

    vector<string> mots = chargerMots(nomFichier);

    if (mots.empty()) {
        cout << "Fichier introuvable ou vide : " << nomFichier << endl;
        return;
    }

    int motsModifies = 0;
    int totalRemplacements = 0;
    vector<string> exemples;                  

    auto debut = high_resolution_clock::now();

    for (string& m : mots) {
        string avant = m;
        int n = remplacerDansMot(m, cherche, remplace);
        if (n > 0) {
            motsModifies++;
            totalRemplacements += n;
            if (exemples.size() < 20)
                exemples.push_back(avant + " -> " + m);
        }
    }

    auto fin = high_resolution_clock::now();
    auto temps = duration_cast<microseconds>(fin - debut);

    cout << "\n====================================" << endl;
    cout << "Fichier : " << nomFichier << endl;
    cout << "Nombre de mots : " << mots.size() << endl;
    cout << "Mot cherche : " << cherche << endl;
    cout << "Remplace par : " << remplace << endl;
    cout << "Temps d'execution : " << temps.count() << " microsecondes ("
         << temps.count() / 1000000.0 << " secondes)" << endl;
    cout << "Mots modifies : " << motsModifies << endl;
    cout << "Remplacements effectues : " << totalRemplacements << endl;
    cout << "Remplacement effectue dans le vecteur (fichier non modifie)" << endl;
    if (!exemples.empty()) {
        cout << "\nQuelques modifications :" << endl;
        for (const string& e : exemples)
            cout << " - " << e << endl;
    }
}

// =====================================================
// MAIN
// =====================================================
int main() {
    string cherche = "cpt";
    string remplace;

    cout << "Mot a remplacer : " << cherche << endl;
    cout << "Remplacer par : ";
    cin >> remplace;
    
    traiterFichier("mots.txt", cherche, remplace);

    return 0;
}
