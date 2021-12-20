/**
 * \file Graphe.h
 * \brief Gestion d'un graphe.
 * \author IFT-2008 && Szepol
 * \version 0.1
 * \date mars 2021
 *
 *  Travail pratique numéro 2
 *
 */

#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
//Vous pouvez ajouter d'autres librairies de la STL

namespace reseau_interurbain
{

/**
* \struct Ponderations
* \brief Une struture utilisée pour stocker les pondérations utilisées sur les arcs
*/
struct Ponderations
{
	float duree;		// La durée du trajet en heures (ex. 3.15 heures entre Québec et Montréal)
	float cout;			// Le cout du trajet en dollars (ex. 70.50 $ entre Québec et Montréal)

	/**
	 * @brief Constructeur de la structure ponderation utilisee pour donne une ponderation pour un arc orienter
	 * connectant deux points
	 * @param d La duree du trajet en heures
	 * @param c Le cout du trajet en dollars
	 */
	Ponderations(float d, float c) : duree(d), cout(c) {}
};

/**
 * \class Graphe
 * \brief Classe représentant un graphe oriente
 *
 *      On y implemente un nombre de sommets lors de la construction, il est
 *      aussi possible de changer le nombre de sommet avec la methode resize,
 *      une fois le graphe construit, il est possible d'ajouter des arcs entre
 *      un sommet d'origine <b>a</b> vers un sommet destination <b>b</b>, chaque
 *      arc contient une ponderation.<br>
 *      L'index des sommets du graphe se trouve dans l'ensemble {0, ..., n-1}
 *      (ou n est le nombre de sommets).<br>
 *      <b>Attributs:</b><br>
 *      std::vector<std::string> <em>noms</em> Le vecteur qui contient l'ensemble des noms des sommets <br>
 *      std::vector<std::list<Arc>> <em>listesAdj</em> Le vecteur des listes d'adjacences de chaque sommets. <br>
 *      size_t <em>nbSommets</em> Entier positif (non strict) qui correspond au nombre de sommets <br>
 *      size_t <em>nbArcs</em> Entier positif (non strict) qui correspond au nombre d'arc <br>
 *      @throws std::logic_error <br>
 */
class Graphe
{
public:
// TODO: Ajouter documentation
	Graphe(size_t nbSommets = 10);
	~Graphe();

	// Change la taille du graphe en utilisant un nombre de sommet = nouvelleTaille
	// Vous pouvez supposer que cette méthode va être appliquée uniquement sur un graphe vide.
	void resize(size_t nouvelleTaille);

	// Donne un nom à un sommet en utlisant son numéro (indice dans le vector).
	// Exception logic_error si sommet supérieur à nbSommets
	void nommer(size_t sommet, const std::string& nom);

	// Ajoute un arc au graphe
	// Exception logic_error si source ou destination supérieur à nbSommets
	// Exception logic_error si l'arc existe déjà dans le graphe
	void ajouterArc(size_t source, size_t destination, float duree, float cout);

	// Supprime un arc du graphe
	// Exception logic_error si source ou destination supérieur à nbSommets
	// Exception logic_error si l'arc n'existe pas dans le graphe
	void enleverArc(size_t source, size_t destination);

	// Vérifie si un arc existe
	// Exception logic_error si source ou destination supérieur à nbSommets
	bool arcExiste(size_t source, size_t destination) const;

	// Retourne la liste de successeurs d'un sommmet
	// Exception logic_error si sommet supérieur à nbSommets
	std::vector<size_t> listerSommetsAdjacents(size_t sommet) const;

	// Retourne le nom d'un sommet
	// Exception logic_error si sommet supérieur à nbSommets
	std::string getNomSommet(size_t sommet) const;

	// Retourne le numéro d'un sommet
	// Exception logic_error si nom n'existe pas dans le graphe
	size_t getNumeroSommet(const std::string& nom) const;

	// Retourne le nombre de sommet du graphe
	int getNombreSommets() const;

	// Retourne le nombre des arcs du graphe
	int getNombreArcs() const;

	// Retourne les pondérations se trouvant dans un arc (source -> destination)
	// Exception logic_error si source ou destination supérieur à nbSommets
	// Exception logic_error si l'arc n'existe pas dans le graphe
	Ponderations getPonderationsArc(size_t source, size_t destination) const;

	//Ne touchez pas à cette fonction !
	friend std::ostream& operator<<(std::ostream& out, const Graphe& g)
	{
		out << "Le graphe contient " << g.nbSommets << " sommet(s) et " 
			<< g.nbArcs << " arc(s)" << std::endl << std::endl;
		for (size_t i = 0; i < g.nbSommets; ++i) 
		{
			out << "Sommet " << g.noms[i] << ": " << std::endl << "Voisins: ";

			if (g.listesAdj[i].size() == 0) 
				out << "Rien";
			else 
			{
				for (auto it = g.listesAdj[i].begin(); it != g.listesAdj[i].end(); ++it) 
					out << g.noms[it->destination] << ", ";
			}
			out << std::endl;
		}
		return out;
	}

	//Vous pouvez ajoutez d'autres méthodes publiques si vous sentez leur nécessité

private:

	std::vector<std::string> noms; /*!< les noms des sommets */

	struct Arc
	{
		size_t destination;
		Ponderations poids;

		Arc(size_t dest, Ponderations p) : destination(dest), poids(p) {}
	};

	std::vector<std::list<Arc> > listesAdj; /*!< les listes d'adjacence */


	size_t nbSommets;	// Le nombre de sommets dans le graphe
	size_t nbArcs;		// Le nombre des arcs dans le graphe


	//Vous pouvez ajoutez des méthodes privées si vous sentez leur nécessité
    void verifyNode(size_t sommet) const;
};
} // namespace reseau_interurbain

