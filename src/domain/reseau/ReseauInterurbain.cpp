/**
 * \file ReseauInterurbain.cpp
 * \brief Implémentattion de la classe ReseauInterurbain.
 * \author IFT-2008 & Samuel Lopez-Lachance - 111 281 733
 * \version 0.1
 * \date mars 2021
 *
 *  Travail pratique numéro 2
 *
 */
#include <sstream>
#include <fstream>
#include "ReseauInterurbain.h"
#include <functional>
#include <limits>
#include <numeric>

namespace reseau_interurbain
{
/**
 * \brief Constructeur du reseau interurbain. Il recoit en entree le nom du reseau et
 * le nombre de ville (Celle-ci est initialiser a 10 par defaut).
 * @param p_nomReseau une chaine de caracteres correspondant au nom du reseau
 * @param p_nbVilles un entier positif (non strict) correspondant au nombre de ville
 */
ReseauInterurbain::ReseauInterurbain(std::string p_nomReseau, size_t p_nbVilles) : nomReseau(p_nomReseau), unReseau(p_nbVilles) 
{

}
/**
 * \brief Destructeur par default de notre reseau interurbain.
 */
ReseauInterurbain::~ReseauInterurbain()
{

}

/**
 * \brief Permet de changer la taille du reseau, cependant la methode supprime toutes les donnees
 * du reseau courant (arcs et noms de sommets). Elle nous permet d'obtenir un nouveau reseau vide de taille desire
 * @param nouvelleTaille entier positive (non strict) qui correspond a la taille desire du reseau
 */
void ReseauInterurbain::resize(size_t nouvelleTaille) 
{
    unReseau.resize(nouvelleTaille);
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
void ReseauInterurbain::chargerReseau(std::ifstream & fichierEntree)
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

    while(buff != "Liste des trajets:")
    {
        unReseau.nommer(i, buff);
        getline(fichierEntree, buff);
        i++;
    }

    while(!fichierEntree.eof())
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
}

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
Chemin ReseauInterurbain::rechercheCheminDijkstra(const std::string& origine, const std::string& destination, bool dureeCout) const 
{
    // On initialize chaque sommet du chemin avec duree et cout total infini et reussi a faux
    std::vector<Chemin> nodes(unReseau.getNombreSommets(),
        {std::vector<std::string>(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), false});

    // On met le sommet d'origine a zero (donc notre sommet de depart)
    nodes.at(unReseau.getNumeroSommet(origine)).dureeTotale = 0;
    nodes.at(unReseau.getNumeroSommet(origine)).coutTotal = 0;

    // Initialise l'ensemble des sommets non solutionnes
    std::vector<size_t> unsolved(unReseau.getNombreSommets());
    std::iota(unsolved.begin(), unsolved.end(), 0);

    std::function<std::vector<size_t>::iterator (std::vector<size_t>&)> min;
    std::function<std::vector<size_t>(std::vector<size_t>)> adj;

    // Fonction lambda pour trouver la valeur minimal des sommets qui se trouve dans
    // l'ensemble des sommets non solutionnes
    min = [&dureeCout, &nodes] (std::vector<size_t>& unsolved) {
        auto temp = std::make_pair(unsolved.end(), std::numeric_limits<float>::max());
        for(auto n = unsolved.begin(); n != unsolved.end() ; n++) {
            if (!nodes[*n].reussi) {
                if (dureeCout) {
                    if (nodes[*n].dureeTotale < temp.second) {
                        temp = std::make_pair(n, nodes[*n].dureeTotale);
                    }
                } else {
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
    adj = [&nodes] (const std::vector<size_t>& adjacent) {
        std::vector<size_t> temp;
        for (auto n : adjacent) {
            if (!nodes[n].reussi)
                temp.push_back(n);
        }
        return temp;
    };

    // Algorithme de dijsktra qui mets a jours le plus court chemin entre
    // le point de depart et chaque points de notre graphe
    while(!unsolved.empty()) {
        auto u = min(unsolved);
        if (u == unsolved.end())
            break;
        nodes[*u].reussi = true;

        for(auto& n : adj(unReseau.listerSommetsAdjacents(*u)))
        {
            if (dureeCout) {
                float temp = nodes[*u].dureeTotale + unReseau.getPonderationsArc(*u, n).duree;
                if (temp < nodes[n].dureeTotale) {
                    nodes[n].dureeTotale = temp;
                    nodes[n].listeVilles.clear();
                    for (auto& t : nodes[*u].listeVilles)
                        nodes[n].listeVilles.push_back(t);
                    nodes[n].listeVilles.push_back(unReseau.getNomSommet(*u));
                }
            } else {
                float temp = nodes[*u].coutTotal + unReseau.getPonderationsArc(*u, n).cout;
                if (temp < nodes[n].coutTotal) {
                    nodes[n].coutTotal = temp;
                    nodes[n].listeVilles.clear();
                    for (auto& t : nodes[*u].listeVilles)
                        nodes[n].listeVilles.push_back(t);
                    nodes[n].listeVilles.push_back(unReseau.getNomSommet(*u));
                }
            }
        }
        unsolved.erase(u);
    }

    // Puisque dijsktra n'inclus pas le sommet de fin dans la trace de celle-ci on ajoute la destination
    // a chaque trace
    for (int i = 0; i < unReseau.getNombreSommets(); i++) {
        nodes[i].listeVilles.push_back(unReseau.getNomSommet(i));
    }

    return nodes.at(unReseau.getNumeroSommet(destination));
}
/**
 * \brief Algorithme de Kosaraju qui permet de retrouver les  différentes composantes fortement connexes du réseau.
 * @return Retourne  un  vecteur  de  vecteurs  de  chaînes  caractères.  Chaque  sous-vecteur  représente
 * une composante fortement connexe du reseau interurbain
 */
std::vector<std::vector<std::string> > ReseauInterurbain::algorithmeKosaraju() {
    std::vector<std::vector<std::string>> composantesConnexes;
    std::vector<bool> visited(unReseau.getNombreSommets(), false);

    // Obtient le graphe inverse de notre graphe de depart (unReseau)
    std::vector<std::vector<size_t>> inverse(unReseau.getNombreSommets());
    for(int i = 0; i < unReseau.getNombreSommets(); i++)
    {
        for (auto j : unReseau.listerSommetsAdjacents(i))
        {
            inverse.at(j).push_back(i);
        }
    }

    // Definition de la fonction lambda explore qui effectue un parcours en profondeur complet du graphe inverse
    // afin d'obtenir un empilement correspondant au parcours de celui-ci (appeler plus bas)
    std::list<size_t> pile;
    std::function<void(size_t)> explore;
    explore = [&inverse, &visited, &pile, &explore] (size_t x) {
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
        if (!visited[std::distance(visited.begin(),it)])
            explore(std::distance(visited.begin(),it));
    }

    // Redefinition de la fonction lambda explore pour effectuer un parcours en profondeur complet du graphe (appeler plus bas)
    std::vector<std::string> parcours;
    auto& reseau = unReseau;
    explore = [&reseau, &visited, &parcours, &explore] (size_t x) {
        parcours.push_back(reseau.getNomSommet(x));
        if (visited[x]) {
            visited[x] = false;
            for (auto& n : reseau.listerSommetsAdjacents(x)) {
                if (visited[n])
                    explore(n);
            }
        }
    };
    // Trouve les ensembles fortement connexe. Fait un parcours en profondeur complet du graphe,
    // mais selon l’ordre des nœuds empilés par le parcours du graphe inverse
    while(!pile.empty()) {
        size_t n = pile.back();
        pile.pop_back();
        if(visited.at(n)) {
            explore(n);
            composantesConnexes.push_back(parcours);
            parcours.clear();
        }
    }

    return composantesConnexes;
}
}// namespace reseau_interurbain

