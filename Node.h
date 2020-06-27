#ifndef __DISTRASSIGNMENT01V1_NODE_H_
#define __DISTRASSIGNMENT01V1_NODE_H_

#include <omnetpp.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace omnetpp;

class Node : public cSimpleModule
{
protected:
    int id;
    int parentId;
    int numOfSends = 0;
    int numOfGates = 0;
    std::vector<int> alreadySendTo; //keeps the ids of the nodes that current node has send to
    bool haveParent = false; //true if current node defined someone as his parent
    int lastSendToId;
    bool rule3IsActive;
    int sizeX;
    int sizeY;
    cDisplayString myDispStr;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
