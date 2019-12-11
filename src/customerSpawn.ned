package final_project;

simple CustomerSpawn
{
    parameters:
        double normalRate = default(1);
        double vipRate = default(0.1);
        double vipOffset = default(0);
        double pCompound = default(0.1);
        string randFunc = default("const");
        @display("i=abstract/people2");
    gates:
        output out;
}
