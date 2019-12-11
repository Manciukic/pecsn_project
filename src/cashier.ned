package final_project;

simple Cashier
{
    parameters:
        double rate = default(1);
        string randFunc = default("const");

        @signal[vipWaitingTime](type="double");
        @signal[normalWaitingTime](type="double");
        @statistic[vipWaitingTime](title="Waiting Time for normal customers"; source="vipWaitingTime"; record=vector,count,mean);
        @statistic[normalWaitingTime](title="Waiting Time for VIP customers"; source="normalWaitingTime"; record=vector,count,mean);
        @display("i=block/queue");
    gates:
        input in;
        output outExit;
        output outKitchen;
}
