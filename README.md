# small-and-simple-cloud-computation-scenario.
simple cloud computation scenario using Socket programming

Consider the following simple and small cloud computation scenario:-
Suppose there are four computers, viz., M1– M4, as shown in Fig. 1. M1 acts as an End-Client which
can send service requests to M2 which acts as the Service Coordination Server (SCS). The service request
sent by the client is actually a computation service request where some mathematical computation is
requested on some data. However, the input data is not sent by the client machine rather; it’s service request
includes some data-ID which uniquely identifies some data. The SCS has access to M3 acting as a Compute
Server and M4 acting as a Data Server. All data are kept at the data server, each individual data uniquely
identified by it’s data-ID (for example data kept in a file in tabular format where each row of the table is an
individual data identified by the unique row-id). The compute server can perform a limited set of
mathematical computations. Each of these computations take data as input which should be in the same
format as that of the individual data kept in the data server. The SCS, after receiving the service request
from the client, first retrieves the required data from the data server and then sends the appropriate
computation request along with the input data to the compute server. When compute server returns back
the result, the SCS forwards it to the client back.
