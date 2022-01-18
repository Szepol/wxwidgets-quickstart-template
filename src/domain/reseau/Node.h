/*****************************************************************//**
 * \file    Node.h
 * \brief   Defines Node class and Ponderations structure, acts as the
 * most basic element in the interurban network 
 * 
 * \author  Szepol
 * \date    January 2022
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <string>
#include <vector>

namespace reseau_interurbain
{
namespace domain
{
/**
* \struct Ponderations
* \brief Struct used to store the ponderations used by the arcs
*/
struct Ponderations
{
	float duration;		// Duration of the trip in hours
	float cost;			// Cost of the trip in dollars

	/**
	 * @brief Constructor of the ponderations structure used to give a ponderation to an oriented arc
	 * connecting 2 nodes
	 * @param d Duration of trip in hours
	 * @param c Cost of the trip in dollars
	 */
	Ponderations(float d, float c) : duration(d), cost(c) {}
};
/**
 * \class Node
 * \brief Interurban network node stores all the arcs coming out from the node, the position of the node
 * and the name of the node. 
 */
class Node
{
public:
	Node(const std::string& p_name, int p_x, int p_y);
	~Node() {};

	bool AddArc(Node* p_dest, float p_duration, float p_cost);
	bool RemoveArc(Node* p_dest);
	bool ChangePonderation(Node* p_dest, float p_duration, float p_cost);
	void RenameNode(const std::string& p_name);
	bool ArcExists(Node* p_dest) const;
	const std::string& GetName() const;
	std::vector<Node*> GetAdjNodes() const;
	const Ponderations& GetPonderation(Node* p_dest) const;
	int GetX() const;
	int GetY() const;

private:
	struct Arc
	{
		Ponderations m_weight;
		Node* m_dest;
		Arc( Node* p_dest, float p_length, float p_cost)
			: m_dest(p_dest), m_weight(p_length, p_cost) {};
	};
	std::string m_name;
	std::vector<Arc> m_vArcs;
	int m_x;
	int m_y;
};
} // namespace domain
} // namespace reseau_interurbain

