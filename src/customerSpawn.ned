package final_project;

simple CustomerSpawn
{
    parameters:
        double rate = default(1);
        double pVip = default(0.1);
        double pCompound = default(0.1);
        string randFunc = default("const");
    gates:
        output out;
}
