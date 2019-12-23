package final_project;

simple Cashier
{
    parameters:
        double rate = default(1);
        string randFunc = default("const");

		@signal[vipQueueLength](type="double");
		@signal[normalQueueLength](type="double");
        @signal[vipWaitingTime](type="double");
        @signal[normalWaitingTime](type="double");
        @statistic[vipQueueLength](title="Length of the VIP queue"; source="vipQueueLength"; record=timeavg);
        @statistic[normalQueueLength](title="Length of the normal queue"; source="normalQueueLength"; record=timeavg);
        @statistic[vipWaitingTime](title="Waiting Time for normal customers"; source="vipWaitingTime"; record=vector,count,mean);
        @statistic[normalWaitingTime](title="Waiting Time for VIP customers"; source="normalWaitingTime"; record=vector,count,mean);
        @display("i=block/queue");
    gates:
        input in;
        output outExit;
        output outKitchen;
}
