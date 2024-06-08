#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <chrono>
#include <thread>

enum choice { paper = 0, scissor = 1, rock = 2 };
struct player
{
	std::string username;
	std::string id;
	int score;
	choice choix;
	bool win = false;
	
	player() : score(0) {}
	player(const std::string& n, const std::string& i) : username(n), id(i), score(0) {}
	player(const std::string& n, const std::string& i, const int s ): username(n), id(i), score(0) {}
	void setScore(const int& s) { score = s; }
	int getScore() const { return score; }

	void setChoice(const choice c) { choix = c; }

	void displayChoice()
	{
		if (choix == scissor)
		{
			std::cout << R"(
				_______
			---'   ____)____
					  ______)
				   __________)
				  (____)
			---.__(___)
			)";
		}
		else if (choix == paper)
		{
			std::cout << R"(
				 _______
			---'    ____)____
					   ______)
					  _______)
					 _______)
			---.__________)
			)";
		}
		else if (choix == rock)
		{
			std::cout << R"(
				_______
			---'   ____)
				  (_____)
				  (_____)
				  (____)
			---.__(___)
			)";
		}		
	}

	std::string getUsername() const { return username; }
	std::string getId() const { return id; }
};
class board
{
private:
	player p1, p2;
	int session; // Le nombre de tours que les joueur a fait
	choice choixDeLaPartie; // a chaque fois l'un des joueur a choisie ce variable capte leur choix
	
public:
	board(){}

	void displayTableOfChoice()
	{
		std::cout << std::endl <<  "Veuillez choisir votre choix : " << std::endl;
		std::cout << " S --> scissor || R --> rock || P --> paper " << std::endl;
	}

	choice getChoice()
	{
		char c;
		choice ch; // Le choix choisir
		bool valide = false;
		
		do
		{
			c = _getch();
			if (c == 'S' || c == 's')
			{
				ch = scissor;
				valide = true;
			}
			else if (c == 'R' || c == 'r')
			{
				ch = rock;
				valide = true;
			}
			else if (c == 'P' || c == 'p')
			{
				ch = paper;
				valide = true;
			}
			else std::cout << " Invalide choice!!! svp choisire S - P - R" << std::endl;
		} while (!valide);
		return ch;
	}

	void displayChoices()
	{
		std::cout << " Player 1 : ";
		p1.displayChoice();
		std::cout << " X ";
		p2.displayChoice();
		std::cout << " : Player 2 ";
	}

	void chek()
	{
		choice c1, c2;
		c1 = p1.choix;
		c2 = p2.choix;

		if (c1 == rock && c2 == paper) p2.score++;
		else if (c1 == rock && c2 == scissor) p1.score++;
		//else if (c1 == paper && c2 == paper) return 0;
		else if (c1 == paper && c2 == rock) p1.score++;
		else if (c1 == paper && c2 == scissor) p2.score++;
		//else if (c1 == scissor && c2 == scissor) return 0;
		else if (c1 == scissor && c2 == rock) p2.score++;
		else if (c1 == scissor && c2 == paper) p1.score++;
	}

	void displayWiner()
	{
		if (p1.win) std::cout << "Player 1 Win : \n";
		else if (p2.win) std::cout << "Player 2 Win : \n";
	}

	void displayScores()
	{
		std::cout << "Player 1 score : " << p1.score << "  " << "Player 2 score : " << p2.score << std::endl;
	}

	void run()
	{
		do
		{
			system("cls");
			displayScores();
			displayTableOfChoice();
			std::cout << "Player 1 choice : ";
			choixDeLaPartie = getChoice();
			p1.setChoice(choixDeLaPartie);
			std::cout << "Player 2 choice : ";
			choixDeLaPartie = getChoice();
			p2.setChoice(choixDeLaPartie);
			displayChoices();
			std::this_thread::sleep_for(std::chrono::seconds(1));
			chek();

		} while (1);

	}

	
};

int main()
{
	board b;
	b.run();
	return 0;
}