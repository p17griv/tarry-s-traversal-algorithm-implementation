//Network from distrlab_topology
network BinaryTree
{
    parameters:
        int initiator = default(1000);
        bool rule3IsActive = default(false);
        int nodeSizeX = default(70);
        int nodeSizeY = default(70);
        int height = default(2);			//to ypsos tou dentrou tha dinetai ws parametros sto omnetpp.ini
        int totalNodes = 2^(height+1)-1;	//to plithos tha ypologizetai apo to ypsos
        									//ara den vazoume default() gia na mhn ginetai override apo to omnetpp.ini
     
    submodules:
        node[totalNodes]: Node
        {
            id = 1000 + index; //Dhlwnoume vector apo Node me megethos oso h prohgoymenh parametros.
        }				
        
    //connections allowunconnected:
    connections:
		for i=0..2^height-2					//Gia osous komvous den einai fylla
		{
		    //Connections Delay 50ms
			node[i].inoutGateVector++ <--> {delay=50ms;} <--> node[2*i+1].inoutGateVector++; //nea syndesh me to aristero paidi
			node[i].inoutGateVector++ <--> {delay=50ms;} <--> node[2*i+2].inoutGateVector++; //nea syndesh me to deksi paidi
		}
}
