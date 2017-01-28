#include <iostream>
#include <cmath>

typedef unsigned long long int ulli;

using std::cout;
using std::endl;

// Object representing a single link in a linked list
struct Link
{
    ulli value;
    Link *next;

    Link( ulli _value )
    {
        value = _value;
    }
};

// Object representing a linked list object
struct LinkedList
{
    Link *head;

    // All links are deleted when 'delete' is called on this object
    ~LinkedList()
    {
        Link *next;

        while ( head->next != nullptr )
        {
            next = head->next;
            delete head;
            head = next;
        }
    }
};

// Function pointer to reduce the amount of calls to retrieve sqrt from cmath
double (*sqrt_global)(double) = sqrt;
unsigned short is_prime(ulli, LinkedList*);

int main()
{
    // Sets the max limit of the prime checker
    const ulli max_limit = 20000000;

    // Count of the total amount of primes 
    ulli primes_ct = 0;

    LinkedList* linked_list = new LinkedList();

    Link *first_link = new Link( 3 );
    linked_list->head = first_link;

    Link *last_prime = new Link( 5 );
    first_link->next = last_prime;

    // Add 3 to the counter because 2, 3, and 5 are prime
    primes_ct += 3;

    // Iterate over all odd numbers from 7 to max_limit and check if they are prime
    // Utilize the list of already known primes to speed up calculations
    for (ulli i = 7; i < max_limit + 1; i += 2)
    {
        // Do not check any numbers ending in 5 because they are not prime
        // Otherwise, check if the number is prime
        if (i % 5 != 0 && is_prime(i, linked_list))
        {
            last_prime->next = new Link( i );
            last_prime = last_prime->next;
            primes_ct++;
        }
    }

    cout << primes_ct << endl;

    return 0;
}

// Checks if a single number is prime
unsigned short is_prime(ulli num, LinkedList *linked_list)
{
    // Precalculate the sqrt of number before doing the for loop to increase efficiency
    ulli root = sqrt_global(num);

    Link *link = linked_list->head;

    // Iterate until reaching the sqrt of the number (guarantees primeness) 
    while (link->value <= root)
    {
        // A number is not prime if it is divisble by another prime
        if (num % link->value == 0)
        {
            return 0;
        }

        link = link->next;
    }

    // The number has been proven prime if the primes from the divisor list exceed the square root
    return 1;
}
