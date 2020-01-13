package final_project;

simple ServiceCenter extends TimerModule
{
    parameters:
		@signal[vipQueueLength](type="long");
		@signal[normalQueueLength](type="long");
		@signal[fifoQueueLength](type="long");
        @signal[vipWaitingTime](type="double");
        @signal[normalWaitingTime](type="double");
        @signal[normalResidenceTime](type="double"); //It is computed for normal orders in priority queue at the end of the simulation to estimate the possibility of starvation.
        
        @statistic[vipQueueLength](title="Length of the VIP queue"; source="vipQueueLength"; record=timeavg);
        @statistic[normalQueueLength](title="Length of the normal queue"; source="normalQueueLength"; record=timeavg);
        @statistic[fifoQueueLength](title="Length of the fifo queue"; source="fifoQueueLength"; record=timeavg, vector);
        @statistic[vipWaitingTime](title="Waiting Time for normal customers"; source="vipWaitingTime"; record=vector,count,mean);
        @statistic[normalWaitingTime](title="Waiting Time for VIP customers"; source="normalWaitingTime"; record=vector,count,mean);
        @statistic[normalResidenceTime](title="Residence time for normal costumers"; source="normalResidenceTime"; record=last);  
        
        @display("i=block/queue");
}
