package final_project;

simple Exit
{
    parameters:
        @signal[simpleNormalResponseTime](type="double");
        @signal[simpleVipResponseTime](type="double");
        @signal[compoundNormalResponseTime](type="double");
        @signal[compoundVipResponseTime](type="double");
        @statistic[simpleNormalResponseTime](title="Response Time for simple orders of normal customers"; source="simpleNormalResponseTime"; record=vector,max,min,count,mean);
        @statistic[simpleVipResponseTime](title="Response Time for simple orders of VIP customers"; source="simpleVipResponseTime"; record=vector,max,min,count,mean);
        @statistic[compoundNormalResponseTime](title="Response Time for compound orders of normal customers"; source="compoundNormalResponseTime"; record=vector,max,min,count,mean);
        @statistic[compoundVipResponseTime](title="Response Time for compound orders of VIP customers"; source="compoundVipResponseTime"; record=vector,max,min,count,mean);
    gates:
        input in[];
}
