/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjMat.cpp
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../headers/AdjMat.h"


/*=================================
Constructeurs et Desctructeurs
===================================*/
AdjMat::AdjMat () : m_size(0) {
}


AdjMat::~AdjMat () {
    int i;

    if (m_size) {
        for (i = 0; i < m_size; i++) {
            delete[] m_graph[i];
        }
        delete[] m_graph;

    }

}


/*=================================
Initialisation
===================================*/
void AdjMat::initData (vector< s_summit >& v, int** m) {
    m_size = (int) v.size();
    m_tabSummit = v;


    m_graph = new int*[m_size];
    for (int i = 0; i < m_size; i++) {
        m_graph[i] = new int[m_size];
        for (int j = 0; j < m_size; j++) {
            m_graph[i][j] = m[i][j];
        }
    }

}


vector< s_summit > AdjMat::initSCC () {
    int i;

    DFS();
    sortDescEnd();
    DFSD();

    for (i = 0; i < m_size; i++) {
        /* Determination de l'importance des points */
        m_tabSummit[i].important = isImportant(i);
    }

    sortAscBeg();

    return m_tabSummit;
}

/*=================================
Accesseurs
===================================*/

vector < s_summit > AdjMat::getTabSummit() {
	return m_tabSummit;
}

s_summit AdjMat::getTabSummit(int i) {
	s_summit s;
	if ((m_tabSummit.size() > 0 ) && (i >= 0) && (i < (int)m_tabSummit.size() ) ){
		return m_tabSummit[i];
	}
	else {
		cerr << "ERREUR sur l'ouverture de tabSummit !!" << endl;
		return s;
	}
}

/*=================================
Parcours en profondeur
===================================*/
void AdjMat::DFS () {
    int i;
    int temps;

    temps = 0;


    for (i = 0; i < m_size; i++) {
        /* Pour tous les points */

        if ( m_tabSummit[i].status == -1 ) {
            /* Si l'etat est marque comme non atteint, on fait un appel recursif */
            DFSHidden(i, temps);
        }
    }
}


void AdjMat::DFSHidden (int i, int& t) { // Parcours en profondeur du graphe (recursif)
    int j;


    m_tabSummit[i].status = 0;
    /* On marque l'etat atteint */
    t++;
    m_tabSummit[i].beg = t;
    /* On le marque comme le t-ieme rencontre */

    for (j = 0; j < m_size; j++) {
        if ( (m_tabSummit[j].status == -1) && (m_graph[i][j]) ) {
            /* Si on trouve un successeur non atteint, on fait un appel recursif */
            DFSHidden(j, t);
        }
    }

    m_tabSummit[i].status = 1;
    /* Une fois termine, on marque l'etat comme explore */
    t++;
    m_tabSummit[i].end = t;
    /* On marque le temps qu'il a fallu pour l'explorer */
}


void AdjMat::DFSD () {
    int i;
    int temps;

    temps = 0;

    for (i = 0; i < m_size; i++) {
        /* Reinitialisation des donnees */
        m_tabSummit[i].status = -1;
        m_tabSummit[i].beg = 0;
        m_tabSummit[i].end = 0;
    }

    for (i = 0; i < m_size; i++) {
        /* Parcours dans le nouvel ordre */
        if (m_tabSummit[m_tabSummit[i].num].status == -1) {
            DFSDHidden(m_tabSummit[i].num, temps);
        }
    }


}


void AdjMat::DFSDHidden (int i, int& t) { // Parcours en profondeur du graphe dual (recursif)
    int j;

    m_tabSummit[i].status = 0;
    /* On marque l'etat atteint */
    t++;
    m_tabSummit[i].beg = t;
    /* On le marque comme le t-ieme rencontre */

    for (j = 0; j < m_size; j++) {
        if ( (m_tabSummit[j].status == -1) && (m_graph[j][i]) ) { // Successeur non atteint
            DFSDHidden(j, t);
        }
    }

    m_tabSummit[i].status = 1;
    /* Une fois termine, on marque l'etat comme explore */
    t++;
    m_tabSummit[i].end = t;
    /* On marque le temps qu'il a fallu pour l'explorer */
}


void AdjMat::sortDescEnd() {
    int i;
    //int tmp, continuer;

    vector< string > vTemp;
    /*tmp = 0;
    continuer = 1;*/

    // Sauvegarde des id
    for (i = 0 ; i < m_size; i++) {
        vTemp.push_back(m_tabSummit[i].id);
    }

    // Tri par ordre des indice de fin en decroissant
    sort(m_tabSummit.rbegin(), m_tabSummit.rend(), orderEnd);

    // Restauration des id
    for (i = 0 ; i < m_size; i++) {
        m_tabSummit[i].id = vTemp[i];
    }

    /*
    while (continuer) {
        continuer--;
        for (i = 0; i < m_size-1; i++) {
            if (m_tabSummit[i].end < m_tabSummit[i+1].end) {
                tmp = m_tabSummit[i+1].end;
                m_tabSummit[i+1].end = m_tabSummit[i].end;
                m_tabSummit[i].end = tmp;

                tmp = m_tabSummit[i+1].beg;
                m_tabSummit[i+1].beg = m_tabSummit[i].beg;
                m_tabSummit[i].beg = tmp;

                tmp = m_tabSummit[i+1].num;
                m_tabSummit[i+1].num = m_tabSummit[i].num;
                m_tabSummit[i].num = tmp;

                continuer++;
            }
        }
    }*/

}


void AdjMat::sortAscBeg() {
    sort(m_tabSummit.begin(), m_tabSummit.end(), orderBeg);
}


void AdjMat::printMat () { // Affiche la matrice adjacente
    int i, j;


    cout << endl;
    for (i = 0; i < m_size; i++) {
        for (j = 0; j < m_size; j++) {
            cout << m_graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


vector< s_summit > AdjMat::initDist (int x) {
    /* Variables */
    int i;
    int n, nbExplore; // nombre de sommet explore
    int cpt_stability; // Indique le nombre de fois où la fonction de recherche de min renvoie x (evite les recherche de min inutiles)

    /* Source Unique Initialisation */
    for (i = 0; i < m_size; i++) {
        m_tabSummit[i].status = -1;
        m_tabSummit[i].beg = INT_MAX;
        m_tabSummit[i].end = -1;
    }

    m_tabSummit[x].beg = 0;
    nbExplore = 0;
    cpt_stability = 0;


    while ( (cpt_stability < 2) && (nbExplore < m_size) ) { // F != null
        n = extractMin(x); // x = ExtraireMin(F)

        if (n == x) {
            cpt_stability++;
        }

        if (m_tabSummit[n].status == -1) {
            m_tabSummit[n].status = 0;  // F = F - x
            nbExplore++;

            for ( i = 0; i < m_size; i++) {
                if (m_graph[n][i]) {
                    if (m_tabSummit[i].beg > m_tabSummit[n].beg + m_tabSummit[i].freq) { // Relacher

                        m_tabSummit[i].beg = m_tabSummit[n].beg + m_tabSummit[i].freq;
                        m_tabSummit[i].end = n; // On indique que le pere le plus proche de i est n
                    }
                }
            }

        }
    }

    return m_tabSummit;
}


int AdjMat::extractMin(int x) {
    int i, imin;
    int valmin;

    valmin = INT_MAX;
    imin = x;
    for (i = 0; i < m_size; i++) {
        if ((m_tabSummit[i].status == -1) && (m_tabSummit[i].beg < valmin)) {
            valmin = m_tabSummit[i].beg;
            imin = i;
        }
    }


//    if (valmin != INT_MAX)
//        return imin;
//    else
//        return 0;
    return imin;
}


bool AdjMat::isImportant(int x) {
    bool important;
    bool sameCFC;
    int i, j;
    int nbFather, nbChild; /* Respectivement nombre de pere, nombre de fils */

    /* Initialisation, on suppose le point important */
    important = true;
    nbFather = 0;
    nbChild = 0;



    /* On regarde s'il a au moins un père et un fils distinct
       Si non, il n'est pas important
       On compte donc le nombre de pere et de fils de x */
    nbNeighborhood(x, nbFather, nbChild);

    /* Si, en sortant de la boucle, on trouve
       - qu'il n'a pas de pere, ou pas de fils
       - qu'il a un seul pere et un seul fils, mais qu'il s'agit du meme point
       Alors, le point n'est pas important */

    if ((nbFather == 0) || (nbChild == 0)) {
        /* Cas pas de pere ou pas de fils, il s'agit d'un point isole */
        important = false;

    } else if ((nbFather == 1) && (nbChild == 1)) {
        /* Cas pere et fils unique, mais le meme point, il s'agit d'un point accessible que via son pere
           L'enlever ne changera donc pas le reste de la composante */
        i = 0;
        while (important && (i < m_size) )  {
            if ((m_graph[x][i] == 1) && (m_graph[i][x] == 1)) {
                important = false;


            }
            i++;
        }
    }



    /* A ce point, le point est toujours suppose important s'il n'a pas remplit les conditions ci dessus
       Il peut conserver ce status d'important si l'enlever implique que
       - un de ses fils ne se retrouve pas sans pere dans la meme CFC => le point deviendrait non accessible
       - un de ses peres ne se retrouve pas sans fils dans la meme CFC => le point deviendrait non co-accessible

       Il faut cependant comme condition que son fils ou pere a qui on enleve le lien
       ait lui aussi au moins un pere et un fils
       Sinon, il est forcement isole dans une CFC */

    /* L'idee est donc de regarder si,
       - pour tous ses fils qui ont au moins un pere ET un fils, il ne soit pas le seul pere
       - pour tous ses peres qui ont au moins un pere ET un fils, il ne soit pas le seul fils */

    /* Seul pere ou fils d'un numero de la MEME CFC soit que son end est inferieur au end actuel */

    if (important) {
        important = false;
        /* On le met a "pas important", et il va essayer de regagner ce rang en remplissant une des conditions */

        i = 0;
        /* Pour tous les fils de x */
        while ( (!important) && (i < m_size) ) {
            if ( m_graph[x][i] && (areInTheSameSCC(x,i)) ) {
                nbNeighborhood(i, nbFather, nbChild);
                /* On va compter le nombre de ses peres et fils */

                if ((nbFather > 0 ) && (nbChild > 0 )) {
                    if (nbFather == 1) {
                        /* Si le fils a qu'un pere, alors le pere est important */
                        important = true;


                    } else {
                        sameCFC = false; /* Indique si on a rencontre un pere de la meme CFC */
                        j = 0;
                        /* S'il y a plusieurs pere, si aucun d'eux n'est dans la CFC, alors le point est important */
                        while ( (!sameCFC) && (j < m_size) ) {

                            if ( (m_graph[j][i]) && (j != x) && (areInTheSameSCC(i, j)) ) {
                                /* Parcours des peres de i */
                                /* On regarde si j est dans la meme CFC que i */
                                sameCFC = true; /* On dit qu'on a vu un pere dans la meme CFC, le point n'est pas important */

                            }
                            j++;
                        }

                        if (!sameCFC) {
                            /* Si, au final, on a pas rencontre un frere de x de la meme CFC, alors le point est important */
                            important = true;


                        }


                    }

                }

            }

            i++;
        }


        i = 0;
        /* (S'il est toujours pas important, on lui donne une 2e chance de regagner son rang) */
        /* Pour tous les peres de x */
        while (!important && (i < m_size) ) {
            if ( (m_graph[i][x]) && (areInTheSameSCC(x,i)) ) {
                /* Pour tous les peres i de x */
                nbNeighborhood(i, nbFather, nbChild);
                /* On va compter le nombre de ses peres et fils */

                if ((nbFather > 0 ) && (nbChild > 0 )) {
                    if (nbChild == 1) {
                        /* Si le pere a un seul fils, alors x est important */
                        important = true;

                    } else {

                        sameCFC = false; /* Indique si on a rencontre un fils de la meme CFC */
                        j = 0;

                        /* S'il y a plusieurs fils, si aucun d'eux n'est dans la CFC, alors le point est important */
                        while ( (!sameCFC) && (j < m_size) ) {

                            if ( ((m_graph[i][j]) &&  (j != x)) && (areInTheSameSCC(i, j)) ) {
                                /* Parcours des fils de i */
                                /* On regarde si j est dans la meme CFC */
                                sameCFC = true; /* On dit qu'on a vu un fils dans la meme CFC */
                            }

                            j++;
                        }

                        if (!sameCFC) {
                            /* Si, au final, on a pas rencontre un frere de x de la meme CFC, alors le point est important */
                            important = true;
                        }

                    }
                }

            }
            i++;
        }
    }


    return important;
}


void AdjMat::nbNeighborhood(int x, int& nbF, int& nbC) {
    int i;

    nbF = 0;
    nbC = 0;
    i = 0;


    while ( ((nbF < 2) || (nbC < 2)) && (i < m_size) ) {
        if (m_graph[x][i]) {
            nbC++;
        }
        if (m_graph[i][x]) {
            nbF++;
        }
        i++;
    }
}


bool AdjMat::areInTheSameSCC(int x, int y) {
    int i;
    int xBegin, xEnd;
    int yBegin, yEnd;
    int iBegin, iEnd;

    bool sameSCC; // Indique respectivement si x et y sont descendants de i

    xBegin = m_tabSummit[x].beg;
    xEnd = m_tabSummit[x].end;
    yBegin = m_tabSummit[y].beg;
    yEnd = m_tabSummit[y].end;

    sameSCC = false;


    i = 0;
    while ( (!sameSCC) && (i < m_size) ) {
        iBegin = m_tabSummit[i].beg;
        iEnd = m_tabSummit[i].end;
        /* Recherche d'un intervalle englobant les 2 points */

        if ( iBegin <= xBegin && iEnd >= xEnd && iBegin <= yBegin && iEnd >= yEnd ) {
            sameSCC = true;
        }

        i++;
    }

    return sameSCC;
}
