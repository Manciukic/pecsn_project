package final_project;

simple Exit
{
    parameters:
        @signal[simpleNormalResponseTime](type="double");
        @signal[simpleVipResponseTime](type="double");
        @signal[compoundNormalResponseTime](type="double");
        @signal[compoundVipResponseTime](type="double");
        @statistic[simpleNormalResponseTime](title="Response Time for simple orders of normal customers"; source="simpleNormalResponseTime"; record=vector,count,mean);
        @statistic[simpleVipResponseTime](title="Response Time for simple orders of VIP customers"; source="simpleVipResponseTime"; record=vector,count,mean);
        @statistic[compoundNormalResponseTime](title="Response Time for compound orders of normal customers"; source="compoundNormalResponseTime"; record=vector,count,mean);
        @statistic[compoundVipResponseTime](title="Response Time for compound orders of VIP customers"; source="compoundVipResponseTime"; record=vector,count,mean);
        @display("i=block/arrival");
        
        @statistic[simpleResponseTimeRatio](title="Ratio between simple response times";source=1-((mean(simpleVipResponseTime))/mean(simpleNormalResponseTime)); record=last); 
        @statistic[compoundResponseTimeRatio](title="Ratio between compound response times";source=1-((mean(compoundVipResponseTime))/mean(compoundNormalResponseTime)); record=last); 
        
    gates:
        input in[];
}
