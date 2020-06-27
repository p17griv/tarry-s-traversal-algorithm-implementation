//Network from distrlab_topology
network Chain
{
    parameters:
        int totalNodes = default(5); //To plithos twn komvwn. Arxikopoieitai apo to omnetpp.ini arxeio.
        int initiator = default(1000);
        bool rule3IsActive = default(false);
        int nodeSizeX = default(70);
        int nodeSizeY = default(70);
    
    submodules:
        node[totalNodes]: Node
        {
            id = 1000 + index; //Dhlwnoume vector apo Node me megethos oso h prohgoymenh parametros.
        }
            
    //connections allowunconnected:
    connections:
		for i = 0..totalNodes-2 //Gia kathe komvo apo ton prwto mexri ton PRO-teleutaio
		{
		    //Connections Delay 50ms
			node[i].inoutGateVector++ <--> {delay=50ms;} <--> node[i+1].inoutGateVector++; //mia nea porta tou trexontos syndeetai me mia porta tou epomenou.
		}
}
