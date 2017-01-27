#include <iostream>
#include <cmath>

typedef unsigned long long int ulli;

// Save typing time
using namespace std;

// Structure for a linked list object
struct LinkedList
{
    ulli value;
    LinkedList *next;

    // Initialize the first link
    LinkedList(ulli _value)
    {
        value = _value;
        next = nullptr;
    }

    // Triggers the deletion of all links when the first one is deleted
    ~LinkedList()
    {
      cout << next->value << endl;
      delete next;
    }
};

// Declare the prime checkings function to it is within scope for the main function
unsigned short is_prime(ulli, LinkedList*);

// Creates a global variable containing the sqrt function to reduce the amount of calls to cmath for the sqrt function
double (*sqrt_global)(double) = sqrt;

// Do our calculations
int main()
{
    // Sets the max limit of the prime checker
    const ulli max_limit = 20000000;

    // Keeps track of how many primes we have
    ulli primes_ct = 0;

    // Create the first link of the linked list
    LinkedList *first_prime = new LinkedList(3);

    // Create the last link of the linked list (will constantly change)
    LinkedList *last_prime = new LinkedList(5);

    // Give first_prime.next a reference to our current last_prime
    first_prime->next = last_prime;

    // Create an intermediary when creating a new last_prime
    LinkedList *old_last_prime = last_prime;

	// Add 3 to counter because 2, 3, and 5 are prime
	primes_ct += 3;

	// Iterate over all odd numbers from 7 to max_limit and check if they are prime
	// Utilize the list of already known primes to speed up calculations
	for (ulli i = 7; i < max_limit + 1; i += 2)
	{
        // Discard all numbers ending in 5 because they are not prime
        // Then check if number is prime
        if (i % 5 != 0 && is_prime(i, first_prime))
        {
            old_last_prime = last_prime;
            last_prime = new LinkedList(i);
            old_last_prime->next = last_prime;
            primes_ct++;
        }
	}

	// Print the number of primes to cout
  cout << primes_ct << endl;

  // Start the link deletion process
  delete first_prime;

	return 0;
}

// Checks if a single number is prime
unsigned short is_prime(ulli num, LinkedList *first_prime_link)
{
	// Precalculate the sqrt of number before doing the for loop to increase efficiency
	ulli root = sqrt_global(num);

  // Create a pointer to the first link
  LinkedList *link = first_prime_link;

  // Iterate over linked list with a while loop until we reach the end
  while (link->value <= root)
  {
      // Number is not prime if it is divisble by another prime
      if (num % link->value == 0)
      {
          return 0;
      }

      // Get the next link from the list
      link = link->next;
  }

	// The number has been proven prime if the primes from the divisor list exceeds the square root
	return 1;
}
