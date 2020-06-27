#include "Node.h"

Define_Module(Node);

void Node::initialize()
{
    id = par("id");
    rule3IsActive = bool(getParentModule()->par("rule3IsActive"));
    sizeX = int(getParentModule()->par("nodeSizeX"));
    sizeY = int(getParentModule()->par("nodeSizeY"));
    numOfGates = gateSize("inoutGateVector");
    if(id == int(getParentModule()->par("initiator"))) //if current node is the initiator
    {
        myDispStr = this->getDisplayString();
        myDispStr.setTagArg("b",0,sizeX);
        myDispStr.setTagArg("b",1,sizeY);
        myDispStr.setTagArg("b",3,"red");
        this->setDisplayString(myDispStr.str()); //make node red
        scheduleAt(simTime()+1,new cMessage("I am the initiator!")); //send a self message
    }
}

void Node::handleMessage(cMessage *msg)
{
    int i;
    int currentNeighborId; //the neighbor node that i am checking in each loop
    int senderId; //the node who send me the msg

    //a new msg is created with different content just to count the number of total sends
    //and compare the result with theory

    int newMsgInt;
    std::string newMsgString;

    if(!msg->isSelfMessage()) //if msg is a not self message from scheduleAt
    {
        newMsgInt = std::stoi(msg->getName()) + 1; //convert msg to int and add 1
        newMsgString = std::to_string(newMsgInt); //convert int to string
        bubble("I have the token!!");
        if(haveParent == false) //if i have not already defined someone as my parent
        {
            parentId = ((Node*)msg->getSenderModule())->id; //set as my parent the node that send me the msg
            haveParent = true;
        }
        senderId = ((Node*)msg->getSenderModule())->id; //get the id of the sender
    }
    else //i am the initiator
    {
        newMsgString = "0";
        if(numOfGates > 0) //if its connected with someone else
        {
            bubble(msg->getName());
            myDispStr.setTagArg("b",0,sizeX);
            myDispStr.setTagArg("b",1,sizeY);
            myDispStr.setTagArg("b",3,"orange");
            this->setDisplayString(myDispStr.str()); //make node orange
        }
        else
        {
            bubble("I am alone :(");
        }
        parentId = this->id; //set as parent id my id
        senderId = 0; //nobody send me
        haveParent = true;
    }

    //convert string to char array and create cMessage
    int n = newMsgString.length();
    char newMsgCharArray[n + 1];
    strcpy(newMsgCharArray, newMsgString.c_str());
    cMessage *message = new cMessage(newMsgCharArray);

    for (i=0; i<numOfGates; i++) //for each gate...
    {
        //get the id of the node at the current gate
        currentNeighborId = ((Node*)gate("inoutGateVector$o",i)->getPathEndGate()->getOwnerModule())->id;

        if(currentNeighborId != parentId) //if current output gate not leading to parent
        {
            if(numOfSends < numOfGates) //if i still have neighbors to send except parent
            {
                std::vector<int>::iterator it;
                it = find(alreadySendTo.begin(), alreadySendTo.end(), currentNeighborId);
                //search for currentNeighborId in the alreadySendTo vector

                if (it != alreadySendTo.end()) //if i have already send to this node
                {
                    //RULE 1: A process never forwards the token through the same channel twice.
                    continue;
                }
                else
                {
                    //if rule3IsActive is true
                    //and the sender of the msg is not my parent
                    //and the sender id value is not 0 (i am not the initiator)
                    if(rule3IsActive && senderId != parentId && senderId != 0)
                    {
                        //RULE 3: When a process receives the token, it immediately sends it back through the same channel
                        //if this is allowed by Rules 1 and 2. --> Depth-first Search

                        //if the current neighbor that i am looking is the sender
                        //and the last message i send was not to him
                        if(currentNeighborId == senderId && lastSendToId != senderId)
                        {
                            numOfSends++;
                            lastSendToId = currentNeighborId;
                            send(message->dup(),gate("inoutGateVector$o",i)); //send the token
                            alreadySendTo.push_back(currentNeighborId);
                            break;
                        }
                        //if the current neighbor that i am looking is NOT the sender
                        //but the last message i send was to him
                        else if(lastSendToId == senderId)
                        {
                            numOfSends++;
                            lastSendToId = currentNeighborId;
                            send(message->dup(),gate("inoutGateVector$o",i)); //send the token
                            alreadySendTo.push_back(currentNeighborId);
                            break;
                        }
                        else
                        {
                                numOfSends++;
                                continue;
                        }
                    }
                    else
                    {
                        numOfSends++;
                        lastSendToId = currentNeighborId;
                        send(message->dup(),gate("inoutGateVector$o",i)); //send the token
                        alreadySendTo.push_back(currentNeighborId);
                        break;
                    }
                }
            }
            else //i have send to all my neighbors except parent
            {
                if(id == int(getParentModule()->par("initiator"))) //if i am the initiator
                {
                    myDispStr.setTagArg("b",3,"red");
                    this->setDisplayString(myDispStr.str()); //make node red again
                    bubble("Finished!");
                    if(rule3IsActive)
                        EV<<message->getName()<<" total sends with rule 3 activated!"<<endl<<"(2N-2 messages?)"<<endl;
                    else
                        EV<<message->getName()<<" total sends with rule 3 deactivated!"<<endl<<"(2E messages?)"<<endl;
                }
            }
        }
        else
        {
            if(id != int(getParentModule()->par("initiator"))) //if i am not the initiator
            {
                //make connection to parent blue
                cDisplayString connectionDispStringOut = gate("inoutGateVector$o",i)->getDisplayString();
                connectionDispStringOut.setTagArg("ls",0,"blue");
                connectionDispStringOut.setTagArg("ls",1,"3");
                gate("inoutGateVector$o",i)->setDisplayString(connectionDispStringOut.str()); //make connection blue

                if(numOfSends == numOfGates -1) //if i have send to all neighbors except parent
                {
                    myDispStr.setTagArg("b",3,"green");
                    myDispStr.setTagArg("b",0,sizeX);
                    myDispStr.setTagArg("b",1,sizeY);
                    this->setDisplayString(myDispStr.str()); //make node green

                    numOfSends++;
                    send(message->dup(),gate("inoutGateVector$o",i)); //send to parent
                    //RULE 2: A process only forwards the token to its parent when there is no other option.
                    alreadySendTo.push_back(currentNeighborId);
                    break;
                }
            }
        }
    }
    delete message;
    delete msg;
}
