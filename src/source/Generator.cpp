/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Generator.h
OBJET            : Genere des fichiers de donnee
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */
#include "../headers/Generator.h"


Generator::Generator() : database("../test/noms.dat"), destination("../test/gene"),
        nbPerson(0), nbRelation(0), nbQuestion(0) {

    FILE* fichier = fopen(database.c_str(), "r");
    nbPersonMax = 0;

    if (fichier == NULL) {
        cerr << endl << "Fichier de donnees introuvable !" << endl;
        exit (-1);

    } else {
        while (!feof(fichier)) {
            fscanf(fichier, "%*[^\r\n]\n");
            nbPersonMax++;
        }
        fclose(fichier);

    }

}

Generator::~Generator() {
}

void Generator::changeOptionAutomatic(string db, string dest, int nP, int nR, int nQ) {
    database = db;
    destination = dest;
    nbPerson = nP;
    nbRelation = nR;
    assert( nbRelation <= (nbPerson * nbPerson - nbPerson) );
    nbQuestion = nQ;
    assert( nbQuestion <= (nbPerson * nbPerson - nbPerson) );

}

void Generator::changeOptionManual() {
    string choice;
    FILE* fichier;
    cout << "Options actuelles :" << endl;
    cout << "\tBase de donnees          : " << database << endl;
    cout << "\tFichier de destination   : " << destination << endl;
    cout << "\tNombre de personnes      : " << nbPerson << " (max : " << nbPersonMax << ")" << endl;
    cout << "\tNombre de relations      : environ " << nbRelation << " (max : " << nbPerson * nbPerson - nbPerson << ")" << endl;
    cout << "\tNombre de questions      : environ " << nbQuestion << " (max : " << nbPerson * nbPerson - nbPerson << ")" << endl;
    cout << endl << endl;


    cout << "Voulez-vous changer la database et la destination ? (o/n) ";
    cin >> choice;

    if (choice == "o" || choice == "O" || choice == "oui" || choice == "Oui") {
        cout << "Base de donnees : ";
        cin >> database;

        fichier = fopen(database.c_str(), "r");

        if (fichier == NULL) {
            cerr << endl << "Fichier de donnees introuvable !" << endl;
            exit (-1);

        } else {
            nbPersonMax = 0;
            while (!feof(fichier)) {
                fscanf(fichier, "%*[^\r\n]\n");
                nbPersonMax++;
            }
            fclose(fichier);
        }

        cout << "Fichier de destination : ";
        cin >> destination;

        cout << "Changements effectues" << endl << endl;

    } else {
        cout << "Aucun changement effectue." << endl << endl;

    }


    cout << "Voulez-vous changer les parametres chiffres ? (o/n) ";
    cin >> choice;

    if (choice == "o" || choice == "O" || choice == "oui" || choice == "Oui") {
        do {
            cout << "Nombre de personnes (max : " << nbPersonMax << ") : ";
            cin >> nbPerson;
        } while (nbPerson > nbPersonMax);

        do {
            cout << "Nombre de relations (max : " << nbPerson * nbPerson - nbPerson << ") : ";
            cin >> nbRelation;
        } while ( nbRelation > (nbPerson * nbPerson - nbPerson) );

        do {
            cout << "Nombre de questions (max : " << nbPerson * nbPerson - nbPerson << ") : ";
            cin >> nbQuestion;
        } while ( nbQuestion > (nbPerson * nbPerson - nbPerson) );

    } else {
        cout << "Aucun changement effectue." << endl << endl;

    }
}


void Generator::generateFile() {
    srand(time(NULL));

    /* Variables */
    int i, j;
    int random;
    char nom[50];
    char id[50];


    FILE* fichier;

    int** matrice;
    vector< string > database_nom;
    vector< string > database_id;

    int nbLink, nbQuest;
    vector< string > liste_id;


    /* Initialisation du fichier de noms */
    fichier = fopen(database.c_str(), "r");

    if (fichier == NULL) {
        cerr << endl << "Fichier de donnees introuvable !" << endl;
        exit (-1);

    } else {

        while (!feof(fichier)) {
            fscanf(fichier, "%[^,\n], %[^\r\n]\n", nom, id);
            database_nom.push_back(nom);
            database_id.push_back(id);
        }
        fclose(fichier);
    }

    assert(nbPerson < (int) database_nom.size());
    /* On verifie que le nombre de personne est bien inferieur au nombre de personne dans la database */

    if (nbPerson > 0) {

        fichier = fopen(destination.c_str(), "w+");

        /* Nombre de personne */
        fprintf(fichier, "%d\n", nbPerson);

        /* Personnes */
        i = 0;
        while (i < nbPerson) {
            random = rand()%database_nom.size();
            strcpy(nom, database_nom[random].c_str());
            strcpy(id, database_id[random].c_str());

            if (find(liste_id.begin(), liste_id.end(), id) == liste_id.end()) {
                /* Si la personne n'est pas encore dans la liste */

                random = rand()%FREQ_MAX;
                /* Determination de la frequence au hasard */
                fprintf(fichier, "%s, %s, %d\n", nom, id, random);
                liste_id.push_back(id);
                /* Stockage des id choisies */
                i++;
            }
        }


        /* Initialisation de la matrice */
        matrice = new int*[nbPerson];
        for (i = 0; i < nbPerson; i++) {
            matrice[i] = new int[nbPerson];
        }


        /* Matrice de relation */
        nbLink = generateMatrix(nbPerson, matrice, (int) convertNumToRatio(nbPerson, nbRelation));

        /* Nombre de relation */
        fprintf(fichier, "%d\n", nbLink);

        for (i = 0; i < nbPerson; i++) {
            for (j = 0; j < nbPerson; j++) {
                if ((matrice[i][j])) {
                    fprintf(fichier, "%s, %s\n", liste_id[i].c_str(), liste_id[j].c_str());
                }
            }
        }


        /* Matrice de question */
        nbQuest = generateMatrix(nbPerson, matrice, (int) convertNumToRatio(nbPerson, nbQuestion));

        /* Nombre de question */
        fprintf(fichier, "%d\n", nbQuest);
        for (i = 0; i < nbPerson; i++) {
            for (j = 0; j < nbPerson; j++) {
                if (matrice[i][j]) {
                    fprintf(fichier, "%s -> %s\n", liste_id[i].c_str(), liste_id[j].c_str());
                }
            }
        }


        /* Liberation de la memoire*/
        for (i = 0; i < nbPerson; i++) {
            delete[] matrice[i];
        }

        delete[] matrice;


        fclose(fichier);
    } else {
        cout << "Le graphe doit posseder au moins 1 personne ! ";
    }
}


void Generator::generateDatabase() {

    fb_account* accounts;	// accounts array after retrival
    int n_accounts = 0;			// number of found accounts
    int nAdd = 0; // number of added accounts

    char email[256];
    char password[256];
    char facebookId[256];
    char name[256];
    char id[256];

    string choice;
    string newDatabaseName;


    map< string, string > alreadyInTheDatabase;
    FILE* fileOut;


    cout << "Compte (e-mail) : ";
    cin >> email;
    cout << "Password : ";
    cin >> password;
    cout << "Id dont on veut recuperer la liste d'amis : ";
    cin >> facebookId;

    cout << endl << "Le fichier database actuel est : " << database << endl;
    cout << "Voulez-vous completer ce fichier ? (o/n) ";
    cin >> choice;


    if (choice == "o" || choice == "O" || choice == "oui" || choice == "Oui") {
        newDatabaseName = database;
        fileOut = fopen(newDatabaseName.c_str(), "a+");

        while (!feof(fileOut)) {
            fscanf(fileOut, "%[^,\n], %[^\r\n]\n", name, id);
            alreadyInTheDatabase[id] = name;
        }

    } else {
        do {
        cout << "Veuillez entrer le nom de la nouvelle database : ";
        cin >> newDatabaseName;
        } while (newDatabaseName == database);

        fileOut = fopen(newDatabaseName.c_str(), "w+");
    }

    cout << endl;

    // Get the list of friends for the given account
    n_accounts = get_friends_list(email, password, facebookId, &accounts);


    // Add the list of friends
    if (n_accounts > 0) {
        // printf("Found %d accounts.\n", n_accounts);

        for (int i = 0; i < n_accounts; i++) {
            if ( alreadyInTheDatabase.find(accounts[i].id) == alreadyInTheDatabase.end() ) {
                fprintf(fileOut, "%s, %s\n", accounts[i].name, accounts[i].id);
                nAdd++;
            }
        }
        cout << "Ajout de " << nAdd << " compte(s)." << endl;
    }

    fclose(fileOut);

    if (newDatabaseName == database) {
        nbPersonMax += nbAdd;
    }
}


int Generator::generateMatrix(int n, int** m, int r) {
    int i, j;
    int cpt;
    int random;

    cpt = 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            random = rand()%(RATIO+1);
            if ( (random >= r) || (i == j) ) {
                m[i][j] = 0;
            } else {
                m[i][j] = 1;
                cpt++;
            }
        }
    }

    return cpt;
}


float Generator::convertNumToRatio(int n, int nbSum) {
    return (nbSum * RATIO) / (n * n - n);
}

string Generator::getDestination() {
    return destination;
}

