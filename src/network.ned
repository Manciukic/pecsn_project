package final_project;

network Network
{
    submodules:
        customerSpawn : CustomerSpawn;
        cashier : Cashier;
        kitchen : Kitchen;
        exit : Exit;
    connections:
        customerSpawn.out --> cashier.in;
        cashier.outKitchen --> kitchen.in;
        cashier.outExit --> exit.in++;
        kitchen.out --> exit.in++;
}
