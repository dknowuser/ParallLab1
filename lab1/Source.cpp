#include <mpi.h>
#include <conio.h>
#include <iostream>

using namespace std;

struct Message {
	int rank;
	unsigned int value;
};

unsigned int doFibonacci(const unsigned int number) {
	unsigned int result[2] = {1, 1};

	if ((number == 1) || (number == 2)) {
		return 1;
	}
	else {
		int position = 1;
		short index = 0;
		while (position < number) {
			result[index] = result[0] + result[1];
			index = (index + 1) % 2;
			position++;
		};
		return result[index];
	};

	return 0;
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, proc_count, received_rank;
	Message msg = {0, 0};
	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &(msg.rank));

	if (!msg.rank) {
		for (unsigned int i = 1; i < proc_count; i++) {
			MPI_Recv(&msg, 2, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			cout << "Received message from processor " << msg.rank;
			cout << " Fibonacci number value: " << msg.value << endl;
		}
	}
	else {
		msg.value = doFibonacci(msg.rank);
		MPI_Send(&msg, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
	};

	MPI_Finalize();
	return 0;
}