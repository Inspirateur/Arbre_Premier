#include <SFML/Graphics.hpp>
#include "Tree.h"
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

int nextPrime(int prime, vector<int>* primes) {
	int n = prime;
	bool isPrime = false;
	unsigned int i;

	while (!isPrime) {
		++n;
		isPrime = true;
		i = 0;

		while (isPrime && primes->at(i)*primes->at(i) <= n ) {
			if (remainder(n, primes->at(i)) == 0) {
				isPrime = false;
			}
			++i;
		}
	}

	return n;
}

vector<int>* getSeed(int n) {
	vector<int>* seed = new vector<int>();
	vector<int>* primes = new vector<int>();
	int prime = 2;
	while (n > 1) {
		if (remainder(n, prime) == 0) {
			cout << n << " / " << prime << endl;
			n = n / prime;
			seed->push_back(prime);
		}
		else {
			primes->push_back(prime);
			prime = nextPrime(prime, primes);
		}
	}
	return seed;
}

int main(){
	sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");

	vector<int>* seed = getSeed(10000);
	//reverse(seed->begin(), seed->end());

	Tree* tree = new Tree(seed, 1050, 800);

	int fps = 60;
	sf::Time spf = sf::seconds(1.0 / float(fps));
	sf::Clock clock;
	sf::Time elapsed = clock.restart();
	while (window.isOpen()){
		if (elapsed < spf) {
			sf::sleep(spf - elapsed);
		}
		elapsed = clock.restart();
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		tree->update();
		window.clear();
		tree->draw(&window);
		window.display();
	}

	return 0;
}

