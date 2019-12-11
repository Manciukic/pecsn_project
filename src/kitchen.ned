package final_project;

simple Kitchen
{
    parameters:
        double rate = default(1);
        string randFunc = default("const");
        string queueType = default("fifo");
    gates:
    	input in;
    	output out;
}
