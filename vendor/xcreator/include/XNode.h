#ifndef XNODE_H
#define XNODE_H

/*
        Copyright (c) 2022 Skynet Cyberdyne

        This software is provided 'as-is', without any express or implied
        warranty. In no event will the authors be held liable for any damages
        arising from the use of this software.

        Permission is granted to anyone to use this software for any purpose,
        excluding commercial applications, and to alter it and redistribute it
        freely, subject to the following restrictions:

        1. The origin of this software must not be misrepresented; you must not
           claim that you wrote the original software. If you use this software
           in a product, an acknowledgment in the product documentation would
           be appreciated but is not required.

        2. Altered source versions must be plainly marked as such, and must not
           be misrepresented as being the original software.

        3. This notice may not be removed or altered from any source
           distribution.
*/

//! All that is needed.
#include <iostream>
#include <vector>

//* Create a node structure. See XNodeView for implementation example.
//! This is a complex class, wich has evolved over a period of time.
//! A copy class like : *A=*B, simply don't work because of the std::vector<XWidget*> related stuff that is member of the class.
//! Removing a last node until all nodes are done, will reduce the *A pointer to zero. And what is gone is gone.
//!
//! The complexity puzzle is solved by adding a "bool selected" flag for each Node.
//! In each while loop cyclus, the flag for a certain Node is set until all Nodes of the puzzle are processed.
//! In the same cyclus, a one dimensional Node array is proccesed to simplyfy the unselect methode we need to do after the Node puzzle is processed.

//! Node class to create a node type tree structure.
class XNode {
public:
    //! Empty contructor. Could be used to kick off.
    XNode(){}
    //! Adds a Node to a given ParentNode.
    XNode(XNode *theParentNode){
        theParentNode->addChildNode(this);
        myParentNode=theParentNode;
        myHasParentNode=true;
    }
    //! Destructor. Not used.
    ~XNode(){
        delete this;
    }
    //! Set the Parent of this Node.
    void setParentNode(XNode *theParentNode){
        if(theParentNode==NULL){
            std::cout<<"error from function void setParentNode(XNode *theParentNode){}, no parent is given"<<std::endl;
        }
        theParentNode->addChildNode(this);
    }
    //! Add a ChildNode to this Node.
    void addChildNode(XNode *theChild){
        if(theChild==NULL){
            std::cout<<"error from function void addChildNode(XNode *theChild){}, no child is given"<<std::endl;
        }
        theChild->myParentNode=this;
        myChildNodeVec.push_back(theChild);
    }
    //! Set the Node name.
    void setNodeName(std::string theText){
        myNodeName=theText;
    }
    //! Return the Node name.
    std::string NodeName(){
        if(myNodeName==""){
            std::cout<<"warning from function  std::string NodeName(){}, no name is specified"<<std::endl;
        }
        return myNodeName;
    }
    //! Print node name + a sign at the front. Basicly used to create a Node graph.
    void printNodeName(std::string theFrontSign){
        std::cout<<"theNodeText:"<<theFrontSign+myNodeName<<std::endl;
    }
    //! Return the Child Node vector.
    std::vector<XNode*> ChildNodeVec(){
        return myChildNodeVec;
    }
    //! Remove all Child Nodes of this Node.
    void clearChildNodeVec(){
        myChildNodeVec.clear();
    }
    //! If this Node has a Child Node vector, remove the first Child Node of the vector, like pop_front().
    void ChildNodeVecPopFront(){
        if(myChildNodeVec.size()==0){
            std::cout<<"warning from function void ChildNodeVecPopFront(){}, vector size=0"<<std::endl;
        }
        std::vector<XNode*> myChildNodeVecCopy;
        for(uint i=0; i<myChildNodeVec.size(); i++){
            if(i>0){
                myChildNodeVecCopy.push_back(myChildNodeVec.at(i));
            }
        }
        myChildNodeVec=myChildNodeVecCopy;
    }
    void ChildNodeVecPopBack(){
        if(myChildNodeVec.size()==0){
            std::cout<<"warning from function void ChildNodeVecPopBack(){}, vector size=0"<<std::endl;
        }
        if(myChildNodeVec.size()>0){
            myChildNodeVec.pop_back();
        }
    }
    void removeChildNode(XNode *theNode){
        if(myChildNodeVec.size()==0){
            std::cout<<"warning from function void removeChildNode(XNode *theNode){}, vector size=0"<<std::endl;
        }
        std::vector<XNode*> myChildNodeVecCopy;
        for(uint i=0; i<myChildNodeVec.size(); i++){
             if(myChildNodeVec.at(i)!=theNode){
                 myChildNodeVecCopy.push_back(myChildNodeVec.at(i));
             }
        }
        myChildNodeVec=myChildNodeVecCopy;
    }
    //! Return the Parent Node of this Node.
    XNode* ParentNode(){
        if(myParentNode==NULL){
            std::cout<<"error in function XNode* ParentNode(){}, myParentNode==NULL"<<std::endl;
        }
        return myParentNode;
    }
    //! Returns true if this Node has a Child Node or more.
    bool hasChildNode(){
        if(myChildNodeVec.size()>0){
            return 1;
        }
        return 0;
    }
    //! If this Node has a Child Node vector. In the vector select the first unselected item.
    void setFirstUnselectedChildVecNodeSelected(){
        for(uint i=0; i<myChildNodeVec.size(); i++){
            if(!myChildNodeVec.at(i)->isNodeSelected()){
                myChildNodeVec.at(i)->setNodeSelected();
                std::cout<<"Setting first found unselected node, selected at :"<<i<<std::endl;
                break;
            }
        }
    }
    //! If this Node has a Child Node vector. In the vector select the first unselected item. Return this item.
    XNode* setFirstUnselectedChildVecNodeSelectedReturnNode(){
        for(uint i=0; i<myChildNodeVec.size(); i++){
            if(!myChildNodeVec.at(i)->isNodeSelected()){
                myChildNodeVec.at(i)->setNodeSelected();
                // std::cout<<"Setting first found unselected node, selected at :"<<i<<std::endl;
                return myChildNodeVec.at(i);
            }
        }
        std::cout<<"error function XNode* setFirstUnselectedChildVecNodeSelectedReturnNode(){}"<<std::endl;
        return NULL;
    }
    //! If this Node has a Child Node vector. In the vector pick up the first unselected Node and return this Node.
    XNode* FirstUnselectedChildVecNode(){
        for(uint i=0; i<myChildNodeVec.size(); i++){
            if(!myChildNodeVec.at(i)->isNodeSelected()){
                // std::cout<<"First unselected node, name:"<<aNode->NodeText()<<std::endl;
                return myChildNodeVec.at(i);
            }
        }
        std::cout<<"error function XNode* FirstUnselectedChildVecNode(){}"<<std::endl;
        return NULL;
    }
    //! Check if the Child Node vector has unselected Nodes inside.
    bool hasUnselectedChildVecNode(){
        for(uint i=0; i<myChildNodeVec.size(); i++){
            if(!myChildNodeVec.at(i)->isNodeSelected()){
                return 1;
            }
        }
        return 0;
    }
    //! Check if this Node has a Parent Node.
    bool hasParentNode(){
        return myHasParentNode;
    }
    //! Set this Node selected.
    void setNodeSelected(){
        mySelect=1;
    }
    //! Set this Node unselected.
    void setNodeUnselect(){
        mySelect=0;
    }
    //! Check if this Node is selected.
    bool isNodeSelected(){
        return mySelect;
    }

private:
    //! Store the parent Node if there is one.
    XNode *myParentNode;
    //! Just a extra flag. Could be removed in future by adding : myParentNode==NULL.
    bool myHasParentNode=0;
    //! Select flag, used to create a Node structure graph.
    bool mySelect=0;
    //! Child Node pointer list. This is just a list of pointers, pointing to a XNode.
    std::vector<XNode*> myChildNodeVec;
    std::string myNodeName;
};

//* Manipulation and usage of a node structure.
//* Implementation example :
/*
                        XNode *aNode0=new XNode();
                        aNode0->setNodeName("Node 0");
                        XNode *aNode01=new XNode(aNode0);
                        aNode01->setNodeName("Node 01");
                        XNode *aNode02=new XNode(aNode0);
                        aNode02->setNodeName("Node 02");
                        XNode *aNode03=new XNode(aNode0);
                        aNode03->setNodeName("Node 03");

                        XNode *aNode001=new XNode(aNode01);
                        aNode001->setNodeName("Node 001");

                        XNode *aNode002=new XNode(aNode02);
                        aNode002->setNodeName("Node 002");
                        // Print the original node structure in terminal:
                        XNodeView().printNode(aNode0);
*/
//! Terminal output:
/*
                        Processing Node layout
                        Printing the selectedNodeList
                        Node 001
                        Node 01
                        Node 002
                        Node 02
                        Node 03
                        Resetting the selectedNodeList to initial state
                         - Node 0
                             |- Node 01
                                  |- Node 001
                             |- Node 02
                                  |- Node 002
                             |- Node 03
*/
//* Print the node structure when one of the nodes is removed by this function:
//! XNodeView().removeNode(aNode0,aNode001);
//! Terminal output:
/*
                        Processing Node layout at removal
                        Resetting the selectedNodeList to initial state
                        Processing Node layout
                        Printing the selectedNodeList
                        Node 01
                        Node 002
                        Node 02
                        Node 03
                        Resetting the selectedNodeList to initial state
                         - Node 0
                             |- Node 01
                             |- Node 02
                                  |- Node 002
                             |- Node 03
*/

//! The tool to manipulate the XNode class.
class XNodeView {
public:
    XNodeView(){}

    //! Test input.
    void testSample(){
         XNode *aNode0=new XNode();
         aNode0->setNodeName("Node 0");
         XNode *aNode01=new XNode(aNode0);
         aNode01->setNodeName("Node 01");
         XNode *aNode02=new XNode(aNode0);
         aNode02->setNodeName("Node 02");
         XNode *aNode03=new XNode(aNode0);
         aNode03->setNodeName("Node 03");

         XNode *aNode001=new XNode(aNode01);
         aNode001->setNodeName("Node 001");

         XNode *aNode0001=new XNode(aNode001);
         aNode0001->setNodeName("Node 0001");

         XNode *aNode002=new XNode(aNode02);
         aNode002->setNodeName("Node 002");

         XNodeView().printNode(aNode0);
         XNodeView().removeNode(aNode0,aNode0001);
    }
    //! Print Node structure.
    void printNode(XNode *theNode){
        std::cout<<processNodeTextGraph(theNode)<<std::endl;
    }
    //! Return the widget structure as string.
    std::string printNodeToString(XNode *theNode){
        return processNodeTextGraph(theNode);
    }
    //! Print Node structure after one Node is removed.
    //! theNode can be just a node or a toplevel node. theNodeToDelete has to be a (can be deep nested) child member of theNode.
    void printNodeAndRemoveOne(XNode* theNode, XNode *theNodeToDelete){
        processNodeTextGraphAndRemoveNode(theNode,theNodeToDelete);
        std::cout<<processNodeTextGraph(theNode)<<std::endl;
    }
    //! theNode is problably your topNode containing Child Nodes.
    //! theNodeName is the Child Node to find by name input.
    XNode* findNodeByName(XNode *theNode, std::string theNodeName){
        std::cout<<"Finding node by name"<<std::endl;
        std::cout<<processNodeTextGraph(theNode)<<std::endl;
        return findNodeByName(theNodeName);
    }
    //! Find and remove the Node by given Node name.
    void removeNode(XNode *theNode, XNode *theNodeToRemove){
        std::cout<<"Removing node"<<std::endl;
        processNodeTextGraphAndRemoveNode(theNode,theNodeToRemove);
        std::cout<<processNodeTextGraph(theNode)<<std::endl;
    }
    //! Find and remove the Node by given Node name.
    void removeNodeByName(XNode *theNode, std::string theNodeName){
        std::cout<<"Removing node by name"<<std::endl;
        processNodeTextGraphAndRemoveNode(theNode,findNodeByName(theNodeName));
        std::cout<<processNodeTextGraph(theNode)<<std::endl;
    }

private:
    std::vector<XNode*> mySelectedNodeList;
    XNode* findNodeByName(std::string theNodeName){
        if(theNodeName==""){
            std::cout<<"warning from function XNode* findNodeByName(std::string theNodeName){}, empty Node name"<<std::endl;
        }
        for(uint i=0; i<mySelectedNodeList.size(); i++){
            if(mySelectedNodeList.at(i)->NodeName()==theNodeName){
                return mySelectedNodeList.at(i);
            }
        }
        std::cout<<"error from function XNode* findNodeByName(std::string theNodeName){}, no Node found by this name."<<std::endl;
        return NULL;
    }
    //! Print the list off all selected Nodes. This list is available after the processNodeTextGraph function is executed.
    void printSelectedNodeList(){
        std::cout<<"Printing the selectedNodeList"<<std::endl;
        for(uint i=0; i<mySelectedNodeList.size(); i++){
            std::cout<<mySelectedNodeList.at(i)->NodeName()<<std::endl;
        }
    }
    //! Reset the select flag for each Node to zero. The mySelectNodeList is a one dimensional Node list made by the processNodeTextGraph function.
    //! Basicly a fast and simple pointer overview list.
    void resetNodeSelection(){
        std::cout<<"Resetting the selectedNodeList to initial state"<<std::endl;
        for(uint i=0; i<mySelectedNodeList.size(); i++){
            mySelectedNodeList.at(i)->setNodeUnselect();
        }
    }
    //! Processing the Node structure graph. Return's a std::string to display in terminal.
    std::string processNodeTextGraph(XNode *theNode){
        std::cout<<"Processing Node layout"<<std::endl;
        mySelectedNodeList.clear();
        std::string theNodeStructureText;
        std::string theFrontText=" - ";

        //! theNode->printNodeText(theFrontText); // For debugging, Print toplevelNode.
        theNodeStructureText.append(theFrontText+theNode->NodeName()+'\n');

        while(1){ // Do it infinite.
            if(theNode->hasUnselectedChildVecNode()){
                theNode=theNode->FirstUnselectedChildVecNode();

                uint theSize=theFrontText.size();
                theFrontText.clear();
                theFrontText.resize(theSize+2,' ');
                theFrontText.push_back('|');
                theFrontText.push_back('-');
                theFrontText.push_back(' ');
                //* theNode->printNodeText(theFrontText); // For debugging.
                theNodeStructureText.append(theFrontText+theNode->NodeName()+'\n');

            } else {  // At deepest child node. No more child's left.

                if(theNode->hasParentNode()){
                    theNode=theNode->ParentNode(); // Go back one level.
                    theFrontText.erase(0,5);
                    if(theNode->hasUnselectedChildVecNode()){
                        XNode *aNode=theNode->setFirstUnselectedChildVecNodeSelectedReturnNode();
                        mySelectedNodeList.push_back(aNode);
                    }
                } else {
                    // Nothing left, leave this while loop.
                    break;
                }
            }
        }
        printSelectedNodeList();
        resetNodeSelection();
        return theNodeStructureText;
    }
    //! A copy off processNodeTextGraph, removing the text graph code, and adding code to remove a Node.
    void processNodeTextGraphAndRemoveNode(XNode *theNode, XNode *theNodeToDelete){
        std::cout<<"Processing Node layout at removal"<<std::endl;
        mySelectedNodeList.clear();
        while(1){ // Do it infinite.
            if(theNode->hasUnselectedChildVecNode()){
                //theNode=theNode->ChildNodeVec().front(); // Goto first child node at front of vector.
                theNode=theNode->FirstUnselectedChildVecNode();
            } else {  // At deepest child node. No more child's left.

                if(theNode->hasParentNode()){
                    theNode=theNode->ParentNode(); // Go back one level.
                    if(theNode->hasUnselectedChildVecNode()){
                        XNode *aNode=theNode->setFirstUnselectedChildVecNodeSelectedReturnNode();

                        if(aNode==theNodeToDelete){
                            theNode=aNode->ParentNode();
                            theNode->clearChildNodeVec();
                        } else {
                            mySelectedNodeList.push_back(aNode);
                        }

                    }
                } else {
                    // Nothing left, leave this while loop.
                    break;
                }
            }
        }
        resetNodeSelection();
    }
};

#endif // XNODE_H








