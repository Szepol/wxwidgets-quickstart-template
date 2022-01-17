/*****************************************************************//**
 * \file    Graphe.cpp
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

#include "Graph.h"
#include <algorithm>

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
Graph::Graph(const std::string& p_name, int p_x, int p_y) : m_vNodes(1, new Node(p_name, p_x, p_y)), m_nArcs(0)
{
    
}
/**
 * \brief .
 * 
 */
Graph::~Graph()
{
    for(auto it = m_vNodes.begin(); it != m_vNodes.end();)
    { 
        delete (*it);
        m_vNodes.erase(it);
    }
}
/**
 * \brief .
 * 
 * \param p_src
 * \param p_name
 */
bool Graph::RenameNode(Node* p_src, const std::string& p_name)
{
    if (!NodeExists(p_src))
        return true;
    p_src->RenameNode(p_name);
    return false;
}
/**
 * \brief .
 * 
 * \param p_src
 * \param p_name
 * \param p_x
 * \param p_y
 * \param p_length
 * \param p_cost
 * \return 
 */
bool Graph::AddNode(Node* p_src, const std::string& p_name, int p_x, int p_y, float p_length, float p_cost)
{
    // If the name is alreadly taken or the source node isn't in the graph return true;
    if (GetNode(p_name) != nullptr || !NodeExists(p_src))
        return true;
    Node* node(new Node(p_name, p_x, p_y));
    m_vNodes.push_back(node);
    p_src->AddArc(node, p_length, p_cost);
    m_nArcs++;
    return false;
}
/**
 * \brief .
 * 
 * \param p_src
 * \param p_dest
 * \param p_length
 * \param p_cost
 * \return 
 */
bool Graph::AddArc(Node* p_src, Node* p_dest, float p_length, float p_cost)
{
    if (p_src->ArcExists(p_dest) || !NodeExists(p_src) || !NodeExists(p_dest))
        return true;
    auto it = std::find(m_vNodes.begin(), m_vNodes.end(), p_src);
    (*it)->AddArc(p_dest, p_length, p_cost);
    m_nArcs++;
    return false;
}
/**
 * \brief .
 * 
 * \param p_src
 * \param p_dest
 * \return 
 */
bool Graph::RemoveArc(Node* p_src, Node* p_dest)
{
    if (p_src->ArcExists(p_dest) || !NodeExists(p_src) || !NodeExists(p_dest))
        return true;
    p_src->RemoveArc(p_dest);
    m_nArcs--;
    return false;
}
/**
 * \brief .
 * 
 * \param p_src
 * \param p_dest
 * \return 
 */
bool Graph::ArcExists(Node* p_src, Node* p_dest) const
{
    if (!NodeExists(p_src) || !NodeExists(p_dest))
        return false;
    return p_src->ArcExists(p_dest);
}
/**
 * \brief .
 * 
 * \param p_src
 * \return 
 */
std::vector<Node*> Graph::GetAdjNodes(Node* p_src) const
{
    return p_src->GetAdjNodes();
}
/**
 * \brief .
 * 
 * \param p_src
 * \return 
 */
const std::string& Graph::GetNodeName(Node* p_src) const
{
    return p_src->GetName();
}
/**
 * \brief .
 * 
 * \param p_nom
 * \return 
 */
Node* Graph::GetNode(const std::string& p_nom) const
{
    auto it = std::find_if(m_vNodes.begin(), m_vNodes.end(), 
        [&p_nom](const Node* arc) {return arc->GetName() == p_nom; });
    if (it == m_vNodes.end())
        return nullptr;
    return (*it);
}
/**
 * \brief .
 * 
 * \return 
 */
std::vector<Node*> Graph::GetAllNodes() const
{
    return m_vNodes;
}
/**
 * \brief .
 * 
 * \return 
 */
int Graph::GetNodeCount() const
{
    return m_vNodes.size();
}
/**
 * \brief .
 * 
 * \return 
 */
int Graph::GetArcCount() const
{
    return m_nArcs;
}
/**
 * \brief .
 * 
 * \param p_src
 * \param p_dest
 * \return 
 */
Ponderations Graph::GetPonderationsArc(Node* p_src, Node* p_dest) const
{
    if (!NodeExists(p_src) || !NodeExists(p_dest) || !p_src->ArcExists(p_dest))
        return Ponderations(0, 0);
    return p_src->GetPonderation(p_dest);
}
/**
 * \brief .
 * 
 * \param p_src
 * \return 
 */
bool Graph::NodeExists(Node* p_src) const
{
    auto it = std::find(m_vNodes.begin(), m_vNodes.end(), p_src);
    return !(it == m_vNodes.end());
}
} // namespace domain
} // namespace reseau_interurbain
