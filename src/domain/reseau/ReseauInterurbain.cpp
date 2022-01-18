/*****************************************************************//**
 * \file    ReseauInterurbain.cpp
 * \brief   
 * 
 * \author  Szepol
 * \date    January 2022
 * \license This project is released under MIT license.
 *********************************************************************/

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <sstream>
#include <fstream>
#include "ReseauInterurbain.h"
#include <functional>
#include <limits>
#include <numeric>

namespace reseau_interurbain
{
namespace domain
{
/**
 * \brief Interurban network constructor, initializes the graph requiring a node.
 * 
 * \param p_nomReseau string Name of the node
 * \param p_x int Position along the horizontal axis
 * \param p_y int Position along the vertical axis
 * \param p_networkName string Name of the interurban network
 */
ReseauInterurbain::ReseauInterurbain(std::string p_nodeName, int p_x, int p_y, std::string p_networkName = "Sans nom") : m_network(p_nodeName, p_x, p_y), m_networkName(p_networkName)
{

}
/**
 * \brief Default destructor for the interurban network.
 */
ReseauInterurbain::~ReseauInterurbain()
{

}

/**
 * \brief Permet de charger un reseau avec un fichier selon le format suivant :
 *
 * Reseau Interurbain: Nom du reseau <br>
 * Nombre de villes <br>
 * Liste des villes: <br>
 * Ville A <br>
 * ... <br>
 * Ville B <br>
 * Liste des trajets: <br>
 * Ville A <br>
 * Ville B <br>
 * Duree Cout <br>
 * ... <br>
 *
 * ex. Creation d'un reseau avec le nom MonReseau contenant deux ville (Pemiere Ville, Deuxieme Ville)
 * avec un seul trajet de premiere ville a deuxieme ville avec une duree de 3.5 et un cout de 50.
 *
 * Reseau Interurbain: MonReseau <br>
 * 2 villes <br>
 * Liste des villes: <br>
 * Permiere ville <br>
 * Deuxieme ville <br>
 * Liste des trajets: <br>
 * Premiere ville <br>
 * Deuxieme ville <br>
 * 3.5 50 <br>
 * @param fichierEntree correspond au flux du fichier entrant
 */
/*void ReseauInterurbain::chargerReseau(std::ifstream& fichierEntree)
{
    if (!fichierEntree.is_open())
        throw std::logic_error("ReseauInterurbain::chargerReseau: Le fichier n'est pas ouvert !");

    std::string buff;

    getline(fichierEntree, nomReseau);
    nomReseau.erase(0, 20); // Enlève: Reseau Interurbain:

    int nbVilles;

    fichierEntree >> nbVilles;
    getline(fichierEntree, buff); //villes

    unReseau.resize(nbVilles);

    getline(fichierEntree, buff); //Liste des villes

    size_t i = 0;

    getline(fichierEntree, buff); //Premiere ville

    while (buff != "Liste des trajets:")
    {
        unReseau.nommer(i, buff);
        getline(fichierEntree, buff);
        i++;
    }

    while (!fichierEntree.eof())
    {
        getline(fichierEntree, buff);
        std::string source = buff;
        getline(fichierEntree, buff);
        std::string destination = buff;

        getline(fichierEntree, buff);
        std::istringstream iss(buff);

        float duree;
        iss >> duree;

        float cout;
        iss >> cout;

        unReseau.ajouterArc(unReseau.getNumeroSommet(source), unReseau.getNumeroSommet(destination), duree, cout);
    }
}*/

/**
 * \brief Algorithme de dijsktra qui permet de retrouver le plus court chemin entre deux villes en utilisant soit la durée
 * en heures ou soit le coût en dollars comme pondération sur les trajets. L'algorithme utilise un vecteur de listes d'adjacences
 * et un vecteur de structure chemin. (Comme on effectue une recherche dans l'ensemble des noeuds non solutionnes a chaque
 * iteration l'algorithme a un temps d'execution sigma(n^2)
 * @param origine Chaine de caractere qui correspond au sommet de depart pour l'algorithme
 * @param destination Chaine de caractere qui correspond au sommet rechercher
 * @param dureeCout Determine si l'algorithme doit utiliser la duree ou le cout comme poids <br> (true = duree, false = cout)
 * @return Retourne le chemin au sommet de destination, le chemin permet de determiner si il existe un plus court chemin entre
 * le point d'origine et le point de destination, le trajet parcourut, la duree et le cout.
 */
Chemin ReseauInterurbain::rechercheCheminDijkstra(const std::string& p_origin, const std::string& p_dest, bool dureeCout) const
{
    // On initialize chaque sommet du chemin avec duree et cout total infini et reussi a faux
    std::vector<Node*> unsolvedNodes(m_network.GetAllNodes());
    std::map<Node*, Chemin> nodes;
    for (auto it = unsolvedNodes.begin(); it != unsolvedNodes.end(); it++)
    {
        nodes[*it] = { std::vector<std::string>(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), false };
        // Remove the origin node from unsolved node vector
        if ((*it)->GetName() == p_origin)
        {
            unsolvedNodes.erase(it);
            it--;
        }
    }

    // On met le sommet d'origine a zero (donc notre sommet de depart)
    nodes.at(m_network.GetNode(p_origin)).dureeTotale = 0;
    nodes.at(m_network.GetNode(p_origin)).coutTotal = 0;

    std::function<std::vector<Node*>::iterator(std::vector<Node*>&)> min;
    std::function<std::vector<Node*>(std::vector<Node*>)> adj;

    // Fonction lambda pour trouver la valeur minimal des sommets qui se trouve dans
    // l'ensemble des sommets non solutionnes
    min = [&dureeCout, &nodes](std::vector<Node*>& unsolved) {
        auto temp = std::make_pair(unsolved.end(), std::numeric_limits<float>::max());
        for (auto n = unsolved.begin(); n != unsolved.end(); n++) {
            if (!nodes[*n].reussi) {
                if (dureeCout) {
                    if (nodes[*n].dureeTotale < temp.second) {
                        temp = std::make_pair(n, nodes[*n].dureeTotale);
                    }
                }
                else {
                    if (nodes[*n].coutTotal < temp.second) {
                        temp = std::make_pair(n, nodes[*n].coutTotal);
                    }
                }
            }
        }
        return temp.first;
    };

    // Fonction lambda qui prend un vecteur (sommets adjacents) et effectue un filtrage
    // retournant un nouveau vecteur de sommets qui ne sont pas solutionnes
    adj = [&nodes](const std::vector<Node*>& adjacent) {
        std::vector<Node*> temp;
        for (auto n : adjacent) {
            if (!nodes[n].reussi)
                temp.push_back(n);
        }
        return temp;
    };

    // Algorithme de dijsktra qui mets a jours le plus court chemin entre
    // le point de depart et chaque points de notre graphe
    while (!unsolvedNodes.empty()) {
        auto u = min(unsolvedNodes);
        if (u == unsolvedNodes.end())
            break;
        nodes[*u].reussi = true;

        for (auto& n : adj(m_network.GetAdjNodes(*u)))
        {
            if (dureeCout) {
                float temp = nodes[*u].dureeTotale + m_network.GetPonderationsArc(*u, n).duration;
                if (temp < nodes[n].dureeTotale) {
                    nodes[n].dureeTotale = temp;
                    nodes[n].listeVilles.clear();
                    for (auto& t : nodes[*u].listeVilles)
                        nodes[n].listeVilles.push_back(t);
                    nodes[n].listeVilles.push_back(m_network.GetNodeName(*u));
                }
            }
            else {
                float temp = nodes[*u].coutTotal + m_network.GetPonderationsArc(*u, n).cost;
                if (temp < nodes[n].coutTotal) {
                    nodes[n].coutTotal = temp;
                    nodes[n].listeVilles.clear();
                    for (auto& t : nodes[*u].listeVilles)
                        nodes[n].listeVilles.push_back(t);
                    nodes[n].listeVilles.push_back(m_network.GetNodeName(*u));
                }
            }
        }
        unsolvedNodes.erase(u);
    }

    // Puisque dijsktra n'inclus pas le sommet de fin dans la trace de celle-ci on ajoute la destination
    // a chaque trace
    for (auto it = m_network.GetAllNodes().begin(); it != m_network.GetAllNodes().end(); it++) {
        nodes[*it].listeVilles.push_back(m_network.GetNodeName(*it));
    }

    return nodes.at(m_network.GetNode(p_dest));
}
/**
 * \brief Algorithme de Kosaraju qui permet de retrouver les  différentes composantes fortement connexes du réseau.
 * @return Retourne  un  vecteur  de  vecteurs  de  chaînes  caractères.  Chaque  sous-vecteur  représente
 * une composante fortement connexe du reseau interurbain
 */
std::vector<std::vector<std::string> > ReseauInterurbain::algorithmeKosaraju() {
    std::vector<std::vector<std::string>> composantesConnexes;
    std::map<Node*, bool> visited;

    // Obtient le graphe inverse de notre graphe de depart (unReseau)
    std::map<Node*, std::vector<Node*>> inverse;
    for (auto it = m_network.GetAllNodes().begin(); it != m_network.GetAllNodes().end(); it++)
    {
        visited[*it] = false;
        for (auto j : m_network.GetAdjNodes(*it))
        {
            inverse[j].push_back(*it);
        }
    }

    // Definition de la fonction lambda explore qui effectue un parcours en profondeur complet du graphe inverse
    // afin d'obtenir un empilement correspondant au parcours de celui-ci (appeler plus bas)
    std::list<Node*> pile;
    std::function<void(Node*)> explore;
    explore = [&inverse, &visited, &pile, &explore](Node* x) {
        if (!visited[x]) {
            visited[x] = true;
            for (auto& n : inverse[x]) {
                if (!visited[n])
                    explore(n);
            }
            pile.push_back(x);
        }
    };
    // Trouve les composantes puits. Empile le parcours en profondeur complet du graphe inverse sur une pile
    for (auto it = visited.begin(); it != visited.end(); ++it)
    {
        if (!(it->second))
            explore(it->first);
    }

    // Redefinition de la fonction lambda explore pour effectuer un parcours en profondeur complet du graphe (appeler plus bas)
    std::vector<std::string> parcours;
    auto& network = m_network;
    explore = [&network, &visited, &parcours, &explore](Node* x) {
        parcours.push_back(network.GetNodeName(x));
        if (visited[x]) {
            visited[x] = false;
            for (auto& n : network.GetAdjNodes(x)) {
                if (visited[n])
                    explore(n);
            }
        }
    };
    // Trouve les ensembles fortement connexe. Fait un parcours en profondeur complet du graphe,
    // mais selon l’ordre des nœuds empilés par le parcours du graphe inverse
    while (!pile.empty()) {
        auto n = pile.back();
        pile.pop_back();
        if (visited[n]) {
            explore(n);
            composantesConnexes.push_back(parcours);
            parcours.clear();
        }
    }

    return composantesConnexes;
}
} // namespace domain
} // namespace reseau_interurbain
