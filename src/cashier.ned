package final_project;

simple Cashier
{
    parameters:
        double rate = default(1);
        string randFunc = default("const");
    gates:
        input in;
        output outExit;
        output outKitchen;
}
