package final_project;

network Network
{
    @display("bgb=410,148");
    submodules:
        customerSpawn: CustomerSpawn {
            @display("p=61,91");
        }
        cashier: Cashier {
            @display("p=161,91");
        }
        kitchen: Kitchen {
            @display("p=260,30");
        }
        exit: Exit {
            @display("p=355,91");
        }
    connections:
        customerSpawn.out --> cashier.in;
        cashier.outKitchen --> kitchen.in;
        cashier.outExit --> exit.in++;
        kitchen.out --> exit.in++;
}
