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


/* CONSTRUCTEURS ET DESCTRUCTEURS : */
AdjMat::AdjMat () : m_size(0), m_graph(NULL) {
}


AdjMat::~AdjMat () {
    int i;


    if ( m_size ) {
        for (i = 0; i < m_size; ++i) {
            delete[] m_graph[i];
        }
        delete[] m_graph;
    }

}
/* -------------------------------------------------------------------------- */


/* ACCESSEURS */
vector < s_summit > AdjMat::getTabSummit() {
	return m_tabSummit;
}


s_summit AdjMat::getTabSummit(int i) {
	s_summit s;


	if ( (i >= 0) && (m_tabSummit.size() > 0 ) && (i < (int) m_tabSummit.size()) ) {
		return m_tabSummit[i];

	} else {
		cerr << "ERREUR sur l'ouverture de tabSummit !" << endl;
		return s;

	}
}


int AdjMat::getSize() {
	return m_size;
}


int** AdjMat::getGraph() {
	return m_graph;
}
/* -------------------------------------------------------------------------- */


/* PROCEDURE : sortDescEnd - Trie les ordres finaux en decroissant tout en conservant les id */
void AdjMat::sortDescEnd() {
    int i;
    vector< string > vTemp;


    // Sauvegarde des id
    for (i = 0 ; i < m_size; ++i) {
        vTemp.push_back(m_tabSummit[i].id);
    }

    // Tri par ordre des indice de fin en decroissant
    sort(m_tabSummit.rbegin(), m_tabSummit.rend(), orderEnd);

    // Restauration des id
    for (i = 0 ; i < m_size; ++i) {
        m_tabSummit[i].id = vTemp[i];
    }
}
/* -------------------------------------------------------------------------- */


/* PROCEDURE : sortAscBeg - Trie les ordres de debut en croissant sans conservation des id */
void AdjMat::sortAscBeg() {
    sort(m_tabSummit.begin(), m_tabSummit.end(), orderBeg);
}
/* -------------------------------------------------------------------------- */


/* METHODE D'INITIALISATION DE LA CLASSE */

/* PROCEDURE : initData - Initialisation des donnees */
void AdjMat::initData (vector< s_summit >& v, int** m) {
    m_size = (int) v.size();
    m_tabSummit = v;


    m_graph = new int*[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_graph[i] = new int[m_size];
        for (int j = 0; j < m_size; ++j) {
            m_graph[i][j] = m[i][j];
        }
    }

}
/* -------------------------------------------------------------------------- */


/* METHODES DE RECHERCHE DE COMPOSANTES FORTEMENT CONNEXES (STRONGLY CONNECTED COMPONENT) */

/* FONCTION : initSCC - Initialise les donnees pour trouver plus facilement les CFC */
vector< s_summit > AdjMat::initSCC () {
    int i;

    DFS();
    sortDescEnd();

    DFSD();
    for (i = 0; i < m_size; ++i) {
        m_tabSummit[i].important = isImportant(i);
    }

    sortAscBeg();

    return m_tabSummit;
}
/* -------------------------------------------------------------------------- */


/* PROCEDURE : DFS - Parcours en profondeur du graphe (Depth First Search) */
void AdjMat::DFS () {
    int i;
    int temps;

    temps = 0;


    for (i = 0; i < m_size; ++i) {
        /* Pour tous les points */

        if ( m_tabSummit[i].status == -1 ) {
            /* Si l'etat est marque comme non atteint, on fait un appel recursif */
            DFSHidden(i, temps);
        }
    }
}


void AdjMat::DFSHidden (int i, int& t) {
    int j;


    m_tabSummit[i].status = 0;
    /* On marque l'etat atteint */
    ++t;
    m_tabSummit[i].beg = t;
    /* On le marque comme le t-ieme rencontre */

    for (j = 0; j < m_size; ++j) {
        if ( (m_tabSummit[j].status == -1) && (m_graph[i][j]) ) {
            /* Si on trouve un successeur non atteint, on fait un appel recursif */
            DFSHidden(j, t);
        }
    }

    m_tabSummit[i].status = 1;
    /* Une fois termine, on marque l'etat comme explore */
    ++t;
    m_tabSummit[i].end = t;
    /* On marque le temps qu'il a fallu pour l'explorer */
}
/* -------------------------------------------------------------------------- */


/* PROCEDURE : DFSD - Parcours en profondeur du graphe dual */
void AdjMat::DFSD () {
    int i;
    int temps;

    temps = 0;

    for (i = 0; i < m_size; ++i) {
        /* Reinitialisation des donnees */
        m_tabSummit[i].status = -1;
        m_tabSummit[i].beg = 0;
        m_tabSummit[i].end = 0;
    }

    for (i = 0; i < m_size; ++i) {
        /* Parcours dans le nouvel ordre */
        if ( m_tabSummit[m_tabSummit[i].num].status == -1 ) {
            DFSDHidden(m_tabSummit[i].num, temps);
        }
    }


}


void AdjMat::DFSDHidden (int i, int& t) {
    int j;

    m_tabSummit[i].status = 0;
    /* On marque l'etat atteint */
    ++t;
    m_tabSummit[i].beg = t;
    /* On le marque comme le t-ieme rencontre */

    for (j = 0; j < m_size; ++j) {
        if ( (m_tabSummit[j].status == -1) && (m_graph[j][i]) ) { // Successeur non atteint
            DFSDHidden(j, t);
        }
    }

    m_tabSummit[i].status = 1;
    /* Une fois termine, on marque l'etat comme explore */
    ++t;
    m_tabSummit[i].end = t;
    /* On marque le temps qu'il a fallu pour l'explorer */
}
/* -------------------------------------------------------------------------- */


/* METHODES DE RECHERCHE DES PLUS COURTS CHEMINS (DIJKSTRA) */

/* FONCTION : initDist - Utilise l'algorithme de Dijkstra pour determiner les plus courts chemins */
vector< s_summit > AdjMat::initDist (int x) {
    /* Variables */
    int i;
    int n, nbExplore; /* Nombre de sommets explores */
    int cpt_stability; /* Indique le nombre de fois où la fonction de recherche de min renvoie x (evite les recherche de min inutiles) */
    int distTemp;

    /* Source Unique Initialisation */
    for (i = 0; i < m_size; ++i) {
        m_tabSummit[i].status = -1;
        m_tabSummit[i].beg = INT_MAX;
        m_tabSummit[i].end = -1;
    }

    m_tabSummit[x].beg = 0;
    nbExplore = 0;
    cpt_stability = 0;


    while ( (cpt_stability < 2) && (nbExplore < m_size) ) { /* Tant qu'on n'a pas explore tout les sommets accessibles */
        n = extractMin(x); /* On extrait le minimum */

        if ( n == x ) {
            ++cpt_stability;
        }

        if ( m_tabSummit[n].status == -1 ) {
            m_tabSummit[n].status = 0;  // F = F - x
            ++nbExplore;

            for ( i = 0; i < m_size; ++i) {
                if ( m_graph[n][i] ) {
                    distTemp = m_tabSummit[n].beg + m_tabSummit[i].freq;
                    if ( m_tabSummit[i].beg > distTemp ) { // Relacher

                        m_tabSummit[i].beg = distTemp;
                        m_tabSummit[i].end = n; // On indique que le pere le plus proche de i est n
                    }
                }
            }

        }
    }

    return m_tabSummit;
}
/* -------------------------------------------------------------------------- */


/* FONCTION : extractMin - Chercher le sommet non explore avec la distance la plus courte du point de depart */
int AdjMat::extractMin(int x) {
    int i, imin;
    int valmin;

    valmin = INT_MAX;
    imin = x;


    for (i = 0; i < m_size; ++i) {
        if ( (m_tabSummit[i].status == -1) && (m_tabSummit[i].beg < valmin) ) {
            valmin = m_tabSummit[i].beg;
            imin = i;
        }
    }

    return imin;
}
/* -------------------------------------------------------------------------- */


/* METHODES DE DETERMINATION D'IMPORTANCE */

/* FONCTION : isImportant - Determine l'importance d'un point */
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

    if ( (nbFather == 0) || (nbChild == 0) ) {
        /* Cas pas de pere ou pas de fils, il s'agit d'un point isole */
        important = false;

    } else if ( (nbFather == 1) && (nbChild == 1) ) {
        /* Cas pere et fils unique, mais le meme point, il s'agit d'un point accessible que via son pere
           L'enlever ne changera donc pas le reste de la composante */
        i = 0;
        while ( important && (i < m_size) )  {
            if ( (m_graph[x][i] == 1) && (m_graph[i][x] == 1) ) {
                important = false;

            }
            ++i;
        }
    }



    /* A ce point, le point est toujours suppose important s'il n'a pas remplit les conditions ci dessus
       Il peut conserver ce status d'important si l'enlever implique que
       - un de ses fils dans la meme CFC ne se retrouve pas sans pere dans la meme CFC => le point deviendrait non accessible
       - un de ses peres dans la meme CFC ne se retrouve pas sans fils dans la meme CFC => le point deviendrait non co-accessible

       Il faut cependant comme condition que son fils ou pere a qui on enleve le lien
       ait lui aussi au moins un pere et un fils
       Sinon, il est forcement isole dans une CFC */

    /* L'idee est donc de regarder si,
       - pour tous ses fils qui ont au moins un pere ET un fils, il ne soit pas le seul pere
       - pour tous ses peres qui ont au moins un pere ET un fils, il ne soit pas le seul fils */

    if ( important ) {
        important = false;
        /* On le met a "pas important", et il va essayer de regagner ce rang en remplissant une des conditions */

        i = 0;
        /* Pour tous les fils de x */
        while ( (!important) && (i < m_size) ) {
            if ( m_graph[x][i] && (areInTheSameSCC(x,i)) ) {
                nbNeighborhood(i, nbFather, nbChild);
                /* On va compter le nombre de ses peres et fils */

                if ( (nbFather > 0) && (nbChild > 0) ) {
                    if ( nbFather == 1 ) {
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
                            ++j;
                        }

                        if ( !sameCFC ) {
                            /* Si, au final, on a pas rencontre un frere de x de la meme CFC, alors le point est important */
                            important = true;
                        }

                    }

                }

            }

            ++i;
        }


        i = 0;
        /* (S'il est toujours pas important, on lui donne une 2e chance de regagner son rang) */
        /* Pour tous les peres de x */
        while ( !important && (i < m_size) ) {
            if ( (m_graph[i][x]) && (areInTheSameSCC(x,i)) ) {
                /* Pour tous les peres i de x */
                nbNeighborhood(i, nbFather, nbChild);
                /* On va compter le nombre de ses peres et fils */

                if ( (nbFather > 0 ) && (nbChild > 0 ) ) {
                    if ( nbChild == 1 ) {
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
                            ++j;
                        }

                        if ( !sameCFC ) {
                            /* Si, au final, on a pas rencontre un frere de x de la meme CFC, alors le point est important */
                            important = true;
                        }

                    }

                }

            }
            ++i;
        }

    }

    return important;
    /* Vrai si le point x a passe tous les test, faux sinon */
}
/* -------------------------------------------------------------------------- */


/* PROCEDURE : nbNeighborhood - Compte le nombre de fils et de pere d'un point */
void AdjMat::nbNeighborhood(int x, int& nbF, int& nbC) {
    int i;

    nbF = 0;
    nbC = 0;
    i = 0;


    while ( ((nbF < 2) || (nbC < 2)) && (i < m_size) ) {
        if ( m_graph[x][i] ) {
            ++nbC;
        }
        if ( m_graph[i][x] ) {
            ++nbF;
        }
        ++i;
    }
}
/* -------------------------------------------------------------------------- */


/* FONCTION : areInTheSameSCC - Indique si deux sommets sont dans la meme CFC */
bool AdjMat::areInTheSameSCC(int x, int y) {
    int i;
    int xBegin, xEnd;
    int yBegin, yEnd;
    int iBegin, iEnd;

    bool sameSCC; /* Indique respectivement si x et y sont descendants de i */

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

        ++i;
    }

    return sameSCC;
}
/* -------------------------------------------------------------------------- */
