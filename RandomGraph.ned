//Network from distrlab_topology
network RandomGraph
{
    parameters:
        int initiator = default(1000);
        bool rule3IsActive = default(false);
        int nodeSizeX = default(70);
        int nodeSizeY = default(70);
    	int totalNodes = default(5); 			//To plithos twn komvwn. Arxikopoieitai apo to omnetpp.ini arxeio.
		double connectedness = default(0.5);	//Analoga me authn thn pithanothta tha dhmiourgeitai h oxi syndesi anamesa se dyo komvous.
    
    submodules:
        node[totalNodes]: Node
        {
            id = 1000 + index; //Dhlwnoume vector apo Node me megethos oso h prohgoymenh parametros.
        }
        
        
    connections: //Connections Delay 50ms
		for i = 0..totalNodes-1, for j = i+1..totalNodes-1	//Gia kathe dynato zeugari komvwn tou diktyou
		{
			node[i].inoutGateVector++ <--> {  delay = 50ms; } <--> node[j].inoutGateVector++ if uniform(0,1)<connectedness; //na ginei syndesi symfwna me thn synthiki pou dhlwnetai sto if
		}
}
