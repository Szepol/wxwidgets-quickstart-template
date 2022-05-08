/*****************************************************************//**
 * \file    Graphe.cpp
 * \brief   
 * 
 * \author  Szepol
 * \date    January 2022
 * \license This project is released under MIT license.
 *********************************************************************/

#include <domain/reseau/Graph.h>
#include <algorithm>

namespace reseau_interurbain
{
namespace domain
{
/**
 * \brief Constructor for the graph class, must be initialized with a node
 * 
 * \param p_name Name of the node in the graph
 * \param p_x Position along the horizontal axis
 * \param p_y Position along the vertical axis
 */
Graph::Graph(const std::string& p_name, int p_x, int p_y) : m_vNodes(1, new Node(p_name, p_x, p_y)), m_nArcs(0)
{
    
}
/**
 * \brief Destructor for the graph class
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
 * \brief RenameNode methods allow change a specified node's name with a new name passed in argument.
 * If the pointer of node isn't inside the list of existing null returns true, and false otherwise.
 * 
 * \param p_src Node* pointer to the node to rename
 * \param p_name std::string string of the new name
 */
bool Graph::RenameNode(Node* p_src, const std::string& p_name)
{
    if (!NodeExists(p_src))
        return true;
    p_src->RenameNode(p_name);
    return false;
}
/**
 * \brief Method to creates a new node and add an arcs from a source node to the newly created node
 * 
 * \param p_src Node* pointer to the source node of the arc
 * \param p_name String name of the new node to point toward
 * \param p_x Position along the horizontal axis of the destination node
 * \param p_y Position along the vertical axis of the destination node
 * \param p_duration Float duration in hours of the trip
 * \param p_cost Float cost in dollars of the trip
 * \return bool if an error was encountered during the process (true means there was an error)
 */
bool Graph::AddNode(Node* p_src, const std::string& p_name, int p_x, int p_y, float p_duration, float p_cost)
{
    // If the name is alreadly taken or the source node isn't in the graph return true;
    if (GetNode(p_name) != nullptr || !NodeExists(p_src))
        return true;
    Node* node(new Node(p_name, p_x, p_y));
    m_vNodes.push_back(node);
    p_src->AddArc(node, p_duration, p_cost);
    m_nArcs++;
    return false;
}
/**
 * \brief Method to add a directed arc from a node source pointing at a node destination, 
 * specifying the duration and cost
 * 
 * \param p_src Node* pointer to the source node
 * \param p_dest Node* pointer to the destination node
 * \param p_duration Float duration in hours of the trip
 * \param p_cost Float cost in dollars of the trip
 * \return bool if an error was encountered during the process (true means there was an error)
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
 * \brief Method to remove the directed arc from source node poiting toward destination node.
 * 
 * \param p_src Node* pointer to the source node
 * \param p_dest Node* pointer to the destination node
 * \return bool if an error was encountered during the process (true means there was an error)
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
 * \brief Method that returns if arc from source node pointing to destination node exists.
 * 
 * \param p_src Node* pointer to the source node
 * \param p_dest Node* pointer to the destination node
 * \return bool if the arc exists(true) or not (false)
 */
bool Graph::ArcExists(Node* p_src, Node* p_dest) const
{
    if (!NodeExists(p_src) || !NodeExists(p_dest))
        return false;
    return p_src->ArcExists(p_dest);
}
/**
 * \brief Method that returns the vector of nodes that the source node points to.
 * 
 * \param p_src Node* pointer to the source node
 * \return vector of Node pointers of all the nodes the source node is pointing to.
 */
std::vector<Node*> Graph::GetAdjNodes(Node* p_src) const
{
    return p_src->GetAdjNodes();
}
/**
 * \brief Method that returns the name of the node
 * 
 * \param p_src Node* pointer to the source node
 * \return String name of the node.
 */
const std::string& Graph::GetNodeName(Node* p_src) const
{
    return p_src->GetName();
}
/**
 * \brief Method to find node using its name, returns a pointer to the node <br>
 * (returns nullptr when no node has the specified name)
 * 
 * \param p_name String name of the node to find
 * \return Node* pointer to the unique node that has the specified name
 */
Node* Graph::GetNode(const std::string& p_name) const
{
    auto it = std::find_if(m_vNodes.begin(), m_vNodes.end(), 
        [&p_name](const Node* arc) {return arc->GetName() == p_name; });
    if (it == m_vNodes.end())
        return nullptr;
    return (*it);
}
/**
 * \brief Method to get all the nodes in the graph
 * 
 * \return vector of node pointers of all the nodes in the graph
 */
std::vector<Node*> Graph::GetAllNodes() const
{
    return m_vNodes;
}
/**
 * \brief Method that returns the number of node in the graph
 * 
 * \return int number of node in the graph
 */
int Graph::GetNodeCount() const
{
    return m_vNodes.size();
}
/**
 * \brief Method that returns the number of arcs in the graph
 * 
 * \return int number of arcs in the graph
 */
int Graph::GetArcCount() const
{
    return m_nArcs;
}
/**
 * \brief Method that returns the ponderations of arc 
 * 
 * \param p_src Node* pointer to the source node
 * \param p_dest Node* pointer to the destination node
 * \return Ponderations the ponderation object of the arc from source node pointing to destination node
 */
Ponderations Graph::GetPonderationsArc(Node* p_src, Node* p_dest) const
{
    if (!NodeExists(p_src) || !NodeExists(p_dest) || !p_src->ArcExists(p_dest))
        return Ponderations(0, 0);
    return p_src->GetPonderation(p_dest);
}
/**
 * \brief privated method to get if node exists inside the graph
 * 
 * \param p_src Node* pointer to the node to verify
 * \return bool If the node exists returns true and false otherwise
 */
bool Graph::NodeExists(Node* p_src) const
{
    auto it = std::find(m_vNodes.begin(), m_vNodes.end(), p_src);
    return !(it == m_vNodes.end());
}
} // namespace domain
} // namespace reseau_interurbain
