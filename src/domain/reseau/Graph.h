/*****************************************************************//**
 * \file    Graph.h
 * \brief   
 * 
 * \author  Szepol
 * \date    January 2022
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include "Node.h"
//Vous pouvez ajouter d'autres librairies de la STL

namespace reseau_interurbain
{
namespace domain
{

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
class Graph
{
public:
	// When creating a new graph, you create a single node by default, and thus we need its coordinate
	Graph(const std::string& p_name, int p_x, int p_y);

	~Graph();

	// Rename an existing node inside the graph
	bool RenameNode(Node* p_src, const std::string& p_name);

	// Creates a new node and add an arcs from a source node to the newly created node
	bool AddNode(Node* p_src, const std::string& p_name, int p_x, int p_y, float p_length, float p_cost);

	// Adds a directed arc from a node source pointing at a node destination, specifying the
	// length and cost
	bool AddArc(Node* p_src, Node* p_dest, float p_length, float p_cost);

	// Remove the directed arc from source node poiting toward destination node.
	bool RemoveArc(Node* p_src, Node* p_dest);

	// Vérifie si un arc existe
	// Exception logic_error si source ou destination supérieur à nbSommets
	bool ArcExists(Node* p_src, Node* p_dest) const;

	// Return the vector of nodes that the source node points to.
	std::vector<Node*> GetAdjNodes(Node* p_src) const;

	// Return the name of the node
	const std::string& GetNodeName(Node* sommet) const;

	// Retourne le numéro d'un sommet
	// Exception logic_error si nom n'existe pas dans le graphe
	Node* GetNode(const std::string& nom) const;

	std::vector<Node*> GetAllNodes() const;

	// Return the number of nodes in the graph
	int GetNodeCount() const;

	// Return the number of arc in the graph
	int GetArcCount() const;

	// Return the ponderations of arc 
	Ponderations GetPonderationsArc(Node* p_src, Node* p_dest) const;

	/*//Ne touchez pas à cette fonction !
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
	*/

private:

	std::vector<Node*> m_vNodes;

	size_t m_nArcs;		// Number of arcs in the graph


	bool NodeExists(Node* p_src) const;
};
} // namespace domain
} // namespace reseau_interurbain

