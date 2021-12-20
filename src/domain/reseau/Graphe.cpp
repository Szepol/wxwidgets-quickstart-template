/**
 * \file Graphe.cpp
 * \brief Implémentation d'un graphe orienté.
 * \author IFT-2008 & Samuel Lopez-Lachance - 111 281 733
 * \version 0.1
 * \date mars 2021
 *
 *  Travail pratique numéro 2
 *
 */

#include "Graphe.h"
#include <algorithm>

namespace reseau_interurbain
{
/**
* \brief Constructeur avec parametres de notre graphe. Il prend en entre un nombre de sommet et initialise
* ses attributs avec ce nombre de sommets
* @param p_nbSommets entier positif (non strict) correspondant a la dimension du graphe
*/
Graphe::Graphe(size_t p_nbSommets) : nbSommets(p_nbSommets), nbArcs(0), noms(p_nbSommets), listesAdj(p_nbSommets) 
{

}

/**
* \brief Destructeur pas defaut du graphe
*/
Graphe::~Graphe() 
{

}

/**
* \brief Permet de changer la taille du graphe, en indiquant le nombre de sommets desire. Cette methode supprime
* tous les donnees (arc, et noms de sommet) du graphe et redimensionne le graphe.
* @param nouvelleTaille entier positif (non strict) correspondant a la nouvelle dimension du graphe
*/
void Graphe::resize(size_t nouvelleTaille) 
{
    noms.clear();
    noms.resize(nouvelleTaille);
    listesAdj.clear();
    listesAdj.resize(nouvelleTaille);
    nbSommets = nouvelleTaille;
    nbArcs = 0;
}

/**
* \brief Permet de nommer un sommet dans le graphe.
* @param sommet Entier positif (non strict) qui correspond au sommet a nommer
* @param nom Chaine de caractere qui correspond au nom a mettre au sommet
* @throw std::logic_error Si le sommet ne se trouve pas dans le graphe
*/
void Graphe::nommer(size_t sommet, const std::string& nom) 
{
    verifyNode(sommet);
    noms.at(sommet) = nom;
}

/**
* \brief Permet d'ajouter un arc partant d'un sommet source vers un sommet destination avec une
* certaine ponderation creer avec la duree et le cout.
* @param source Entier positif (non strict) qui correspond au sommet de depart de l'arc
* @param destination Entier positif (non strict) qui correspond au sommet de fin de l'arc
* @param duree Reel positif (non strict) qui correspond a la duree de la ponderation de l'arc
* @param cout Reel positif (non strict) qui correspond au cout de la ponderationd de l'arc
* @throw std::logic_error Si le sommet source ne se trouve pas dans le graphe
* @throw std::logic_error Si le sommet destination ne se trouve pas dans le graphe
* @throw std::logic_error Si l'arc du sommet source au sommet destination n'existe pas dans le graphe
*/
void Graphe::ajouterArc(size_t source, size_t destination, float duree, float cout) 
{
    if (arcExiste(source, destination))
        throw std::logic_error("Ajout d'arc deja existant");
    listesAdj.at(source).push_back(Arc(destination,Ponderations(duree,cout)));
    nbArcs++;
}

/**
* \brief Permet d'enlever un arc d'un sommet source vers un sommet destination.
* @param source Entier positif (non strict) qui correspond au sommet de depart de l'arc
* @param destination Entier positif (non strict) qui correspond au sommet de fin de l'arc
* @throw std::logic_error Si le sommet source ne se trouve pas dans le graphe
* @throw std::logic_error Si le sommet destiation ne se trouve pas dans le graphe
* @throw std::logic_error Si l'arc du sommet source au sommet destination n'existe pas dans le graphe
*/
void Graphe::enleverArc(size_t source, size_t destination) 
{
    if (!arcExiste(source, destination))
        throw std::logic_error("Utilisation d'un arc inexistant");
    auto it = std::find_if(listesAdj.at(source).begin(), listesAdj.at(source).end(),
                            [&destination](const Arc& x) {return x.destination == destination;});
    listesAdj.at(source).erase(it);
}

/**
* \brief Permet de determiner l'existance d'un arc partant d'un point source allant vers un point destination
* @param source Entier positif (non strict) qui correspond a l'indice du sommet de depart de l'arc
* @param destination Entier positif (non strict) qui correspond a l'indice du sommet de fin de l'arc
* @return Retourne s'il existe un arc du sommet source vers le sommet destination
* @throw std::logic_error Si le sommet source ne se trouve pas dans le graphe
* @throw std::logic_error Si le sommet destination ne se trouve pas dans le graphe
*/
bool Graphe::arcExiste(size_t source, size_t destination) const 
{
    verifyNode(source);
    verifyNode(destination);
    auto it = std::find_if(listesAdj.at(source).begin(), listesAdj.at(source).end(),
                            [&destination](const Arc& x)  { return (x.destination == destination); });
    return !(it == listesAdj.at(source).end());
}

/**
* \brief Donne un vecteur qui contient tous les sommets destination des arc qui parte d'un point
* @param sommet Entier positif (non strict) qui correspond a l'indice du sommet de depart des arcs
* @return vecteur des sommets adjacents au point en parametre.
* @throw std::logic_error Si le sommet ne se trouve pas dans le graphe
*/
std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const 
{
    verifyNode(sommet);
    std::vector<size_t> v;
    for (auto it : listesAdj.at(sommet))
        v.push_back(it.destination);
    return v;
}

/**
* \brief Permet de retrouver le nom d'un sommet en passant l'indice du sommet en parametre
* @param sommet Entier positif (non strict) correspondant a l'indice du sommet rechercher.
* @return Retourne le nom du sommet se trouvant a l'indice demander.
* @throw std::logic_error Si le sommet ne se trouve pas dans le graphe
*/
std::string Graphe::getNomSommet(size_t sommet) const 
{
    verifyNode(sommet);
    return noms.at(sommet);
}

/**
* \brief Permet de retrouver le sommet avec un nom (si plusieurs sommet on le meme nom, on donne le premier sommet
* qui avec le nom rechercher
* @param nom chaine de caractere qui correspod au nom du sommet rechercher
* @return Entier positif qui correspond a l'indice du premier sommet qui a le nom rechercher
* @throw std::logic_error Si le nom du sommet ne se trouve pas dans le graphe
*/
size_t Graphe::getNumeroSommet(const std::string& nom) const 
{
    auto it = std::find(noms.begin(), noms.end(), nom);
    if (it == noms.end())
        throw std::logic_error("Nom de sommet invalide");
    return std::distance(noms.begin(), it);
}

/**
* \brief Accesseur qui permet de retrouver le nombre de sommet qui se trouve dans le graphe
* @return Retourne un entier positif (non strict) correspondant au nombre de sommets dans le graphe
*/
int Graphe::getNombreSommets() const 
{
    return nbSommets;
}

/**
* \brief Accesseur qui permet de retrouver le nombre d'arc qui se trouve dans le graphe
* @return Retourne un entier positif (non strict) correspondant au nombre d'arcs dans le graphe
*/
int Graphe::getNombreArcs() const 
{
    return nbArcs;
}

/**
* \brief Prend deux sommets et retourne la ponderation de l'arc qui se trouve entre les deux sommets.
* @param source Entier positif (non strict) correspondant au sommet de depart de l'arc
* @param destination Entier positif (non strict) correspondant au sommet de fin de l'arc
* @return Retourne la ponderation de l'arc entree en parametre
* @throw std::logic_error Si le sommet source ne se trouve pas dans le graphe
* @throw std::logic_error Si le sommet destination ne se trouve pas dans le graphe
* @throw std::logic_error Si l'arc du sommet source au sommet destination n'existe pas dans le graphe
*/
Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const 
{
    if (!arcExiste(source, destination))
        throw std::logic_error("Utilise un arc inexistant");
    auto it = std::find_if(listesAdj.at(source).begin(), listesAdj.at(source).end(),
                            [&destination](const Arc& x)  { return (x.destination == destination); });
    return it->poids;
}

/**
* \brief Prend un sommet et lance une exception si l'indice du sommet ne se trouve pas dans la graphe
* @param sommet un entier positif (non strict) qui correspond a l'index du sommet.
* @throws std::logic_error Si le sommet en parametre ne se trouve pas dans le graphe.
*/
void Graphe::verifyNode(size_t sommet) const 
{
    if (sommet >= nbSommets)
        throw std::logic_error("Utilise un sommet inexistant");
}
} // namespace reseau_interurbain
