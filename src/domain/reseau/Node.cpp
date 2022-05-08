/*****************************************************************//**
 * \file    Node.cpp
 * \brief   Implementation of the Node class, acts as the
 * most basic element in the interurban network 
 * 
 * \author  Szepol
 * \date    January 2022
 * \license This project is released under MIT license.
 *********************************************************************/

#include <domain/reseau/Node.h>

namespace reseau_interurbain
{
namespace domain
{
/**
 * \brief Node constructor, requires a name and a position along the x, y axis.
 * 
 * \param p_name string Name of the node.
 * \param p_x int Position along the horizontal axis
 * \param p_y int Position along the vertical axis.
 */
Node::Node(const std::string& p_name, int p_x, int p_y)
	: m_name(p_name), m_x(p_x), m_y(p_y)
{

}
/**
 * \brief Allows to add an arc pointing toward a destination node, with a certain ponderation.
 * 
 * \param p_dest Node* pointer to the destination node.
 * \param p_duration float travel duration for the ponderation of the arc.
 * \param p_cost float travel cost for the ponderation of the arc.
 * \return boolean False is returned if the code was executed without any error.
 */
bool Node::AddArc(Node* p_dest, float p_duration, float p_cost)
{
	if (ArcExists(p_dest) || p_dest == this)
		return true;
	m_vArcs.push_back(Arc(p_dest, p_duration, p_cost));
	return false;
}
/**
 * \brief Removes an arc pointing at the destination node.
 * 
 * \param p_dest Node* pointer to the destination node.
 * \return boolean False is returned if the code was executed without any error.
 */
bool Node::RemoveArc(Node* p_dest)
{
	auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
		[&p_dest](const Arc& x) {return x.m_dest == p_dest; });
	if (it == m_vArcs.end())
		return true;
	m_vArcs.erase(it);
	return false;
}
/**
 * \brief Changes the ponderation of the arc pointing at destination node.
 * 
 * \param p_dest Node* pointer to the destination node.
 * \param p_duration float travel duration for the ponderation of the arc.
 * \param p_cost float travel cost for the ponderation of the arc.
 * \return boolean False is returned if the code was executed without any error.
 */
bool Node::ChangePonderation(Node * p_dest, float p_duration, float p_cost)
{
	auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
		[&p_dest](const Arc& x) {return x.m_dest == p_dest; });
	if (it == m_vArcs.end())
		return true;
	it->m_weight.duration = p_duration;
	it->m_weight.cost = p_cost;
	return false;
}
/**
 * \brief Method to change the node's name.
 * 
 * \param p_name string New name of the node.
 */
void Node::RenameNode(const std::string& p_name)
{
	m_name = p_name;
}
/**
 * \brief Method to get if there's an arc from the current node pointing
 * toward the destination node.
 * 
 * \param p_dest Node* pointer to the destination node.
 * \return boolean false is returned if the code was executed without any error.
 */
bool Node::ArcExists(Node* p_dest) const
{
	auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
		[&p_dest](const Arc& x) {return x.m_dest == p_dest; });
	if (it == m_vArcs.end())
		return false;
	return true;
}
/**
 * \brief Method to get the name of the node.
 * 
 * \return string Name of the Node.
 */
const std::string& Node::GetName() const
{
	return m_name;
}
/**
 * \brief Method to get the adjacent Nodes of the current node.
 * 
 * \return vector<Node*> vector of pointers of the nodes of the current node arcs.
 */
std::vector<Node*> Node::GetAdjNodes() const
{
	std::vector<Node*> adjacentNodes;
	for (auto it : m_vArcs)
		adjacentNodes.push_back(it.m_dest);
	return adjacentNodes;
}
/**
 * \brief Method to get the ponderation of an arc pointing toward destination node.
 * 
 * \param p_dest Node* pointer to the destination node.
 * \return ponderation passed by constant reference, if the arc doesn't exist will return a empty ponderation (cost = 0 and duration = 0)
 */
const Ponderations& Node::GetPonderation(Node * p_dest) const
{
	// TODO: Define behavior when passing unconnected Node.
	auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
		[&p_dest](const Arc& x) {return x.m_dest == p_dest; });
	return it->m_weight;
}
/**
 * \brief Method to get the horizontal position of the node.
 * 
 * \return int horizontal position of the node.
 */
int Node::GetX() const
{
	return m_x;
}
/**
 * \brief Method to get the vertical position of the node.
 * 
 * \return int vertical position of the node.
 */
int Node::GetY() const
{
	return m_y;
}
} // namespace domain
} // namespace reseau_interurbain

