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

namespace reseau_interurbain
{
namespace domain
{

/**
 * \class Graphe
 * \brief Classe representing a oriented graph<br>
 * When constructing a graph object we also need to construct atleast one node object. <br>
 * Once the graph is constructed it's possible tp add nodes and connect these nodes with oriented <br>
 * arcs. Each arc has a ponderation.<br><br>
 * 
 * TODO: <br>
 * Add a method to remove Node from the graph.<br>
 * Change the class so that the graph stays valid at all time (shouldn't be able to remove an arc and leave a unconnected node)<br>
 *
 */
class Graph
{
public:
	Graph(const std::string& p_name, int p_x, int p_y);
	~Graph();

	bool RenameNode(Node* p_src, const std::string& p_name);
	bool AddNode(Node* p_src, const std::string& p_name, int p_x, int p_y, float p_length, float p_cost);
	bool AddArc(Node* p_src, Node* p_dest, float p_length, float p_cost);
	bool RemoveArc(Node* p_src, Node* p_dest);
	bool ArcExists(Node* p_src, Node* p_dest) const;
	std::vector<Node*> GetAdjNodes(Node* p_src) const;
	const std::string& GetNodeName(Node* sommet) const;
	Node* GetNode(const std::string& p_name) const;
	std::vector<Node*> GetAllNodes() const;
	int GetNodeCount() const;
	int GetArcCount() const;
	Ponderations GetPonderationsArc(Node* p_src, Node* p_dest) const;

private:
	std::vector<Node*> m_vNodes;
	size_t m_nArcs;

	bool NodeExists(Node* p_src) const;
};
} // namespace domain
} // namespace reseau_interurbain

