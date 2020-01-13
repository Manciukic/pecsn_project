package final_project;

simple Kitchen extends ServiceCenter
{
    parameters:
    	string queueType = default("fifo");
   	@class(Kitchen);
    gates:
        input in;
        output out;
}
