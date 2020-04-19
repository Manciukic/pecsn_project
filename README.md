# Project 9 - "Faculty bar"

Analysis of simulations of a queue in a faculty bar using Omnet++.

## Problem description
Consider a system that manages the orders of customers in a bar. Orders are issued to a cashier, which
has two queues: one for normal users and one for VIP users. VIP users have non-preemptive priority
over normal users. Users belonging to the same queue are served according to a FIFO policy.
Orders can be of simple or compound type. Simple orders are completed directly by the cashier, with
a service rate r_cashier. Composite orders are first served by the cashier, with a service rate r_cashier, and
then are passed to the kitchen, which queues them and serves them in FIFO order, with a service rate
r_kitchen: Both normal and VIP users can issue both types of orders.
