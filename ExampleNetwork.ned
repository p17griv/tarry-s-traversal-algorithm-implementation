//Network example from presentation of Dr. Borzoo Bonakdarpour - Distributed Algorithms (CAS 769) - McMaster University
network ExampleNetwork 
{
    parameters:
        int initiator = default(1000);
        bool rule3IsActive = default(false);
        int nodeSizeX = default(70);
        int nodeSizeY = default(70);
        @display("bgb=1000,600");
        
    submodules:
        p: Node {
            id = 1000;
            @display("p=192,190");
        }
        q: Node {
            id = 1001;
            @display("p=522,190");
        }
        t: Node {
            id = 1002;
            @display("p=522,457");
        }
        s: Node {
            id = 1003;
            @display("p=192,457");
        }
        r: Node {
            id = 1004;
            @display("p=821,190");
        }

    connections:
        //Connections Delay 50ms
        p.inoutGateVector++ <--> {  delay = 50ms; } <--> q.inoutGateVector++;
        p.inoutGateVector++ <--> {  delay = 50ms; } <--> t.inoutGateVector++;
        p.inoutGateVector++ <--> {  delay = 50ms; } <--> s.inoutGateVector++;
        q.inoutGateVector++ <--> {  delay = 50ms; } <--> t.inoutGateVector++;
        q.inoutGateVector++ <--> {  delay = 50ms; } <--> r.inoutGateVector++;
        t.inoutGateVector++ <--> {  delay = 50ms; } <--> s.inoutGateVector++;
}
