/*****************************************************************//**
 * \file    Node.cpp
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

#include "Node.h"

namespace reseau_interurbain
{
namespace domain
{
/**
 * \brief .
 * 
 * \param p_name
 * \param p_x
 * \param p_y
 */
Node::Node(const std::string& p_name, int p_x, int p_y)
	: m_name(p_name), m_x(p_x), m_y(p_y)
{

}
/**
 * \brief .
 * 
 * \param p_node
 * \param p_length
 * \param p_cost
 * \return 
 */
bool Node::AddArc(Node* p_node, float p_length, float p_cost)
{
	if (ArcExists(p_node))
		return true;
	m_vArcs.push_back(Arc(p_node, p_length, p_cost));
	return false;
}
/**
 * \brief .
 * 
 * \param p_node
 * \return 
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
 * \brief .
 * 
 * \param p_node
 * \param p_length
 * \param p_cost
 * \return 
 */
bool Node::ChangePonderation(Node * p_dest, float p_length, float p_cost)
{
	auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
		[&p_dest](const Arc& x) {return x.m_dest == p_dest; });
	if (it == m_vArcs.end())
		return true;
	it->m_weight.duree = p_length;
	it->m_weight.cout = p_cost;
	return false;
}
/**
 * \brief .
 * 
 * \param p_name
 */
void Node::RenameNode(const std::string& p_name)
{
	m_name = p_name;
}
bool Node::ArcExists(Node* p_dest) const
{
	auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
		[&p_dest](const Arc& x) {return x.m_dest == p_dest; });
	if (it == m_vArcs.end())
		return false;
	return true;
}
/**
 * \brief .
 * 
 * \return 
 */
const std::string& Node::GetName() const
{
	return m_name;
}
/**
 * \brief .
 * 
 * \return 
 */
std::vector<Node*> Node::GetAdjNodes() const
{
	std::vector<Node*> v;
	for (auto it : m_vArcs)
		v.push_back(it.m_dest);
	return v;
}
/**
 * \brief .
 * 
 * \param p_dest
 * \return 
 */
const Ponderations& Node::GetPonderation(Node * p_dest) const
{
	auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
		[&p_dest](const Arc& x) {return x.m_dest == p_dest; });
	if (it == m_vArcs.end())
		return Ponderations(0, 0);
	return it->m_weight;
}
/**
 * \brief .
 * 
 * \return 
 */
int Node::GetX() const
{
	return m_x;
}
/**
 * \brief .
 * 
 * \return 
 */
int Node::GetY() const
{
	return m_y;
}
} // namespace domain
} // namespace reseau_interurbain

