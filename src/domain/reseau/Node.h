/*****************************************************************//**
 * \file    Node.h
 * \brief   
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
 * .
 */
class Node
{
public:
	Node(const std::string& p_name, int p_x, int p_y);
	~Node() {};

	bool AddArc(Node* p_dest, float p_length = 0, float p_cost = 0);
	bool RemoveArc(Node* p_dest);
	bool ChangePonderation(Node* p_dest, float p_length = 0, float p_cost = 0);
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

