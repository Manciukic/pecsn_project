package final_project;

simple CustomerSpawn
{
    parameters:
        double rate = default(1);
        double pVip = default(0.1);
        double pCompound = default(0.1);
        string randFunc = default("const");
        @display("i=abstract/people2");
    gates:
        output out;
}
