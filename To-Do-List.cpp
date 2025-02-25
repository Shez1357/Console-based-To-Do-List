#include <iostream> 
#include <conio.h> //This allows me to detect keystrokes
#include <string>
#include <map>//This allows me to create a dict.
using namespace std;

//Stores user tasks
std::map<int, string> Task;
//Global variables
string objective;
int TaskCounter;
char key;
char key2;

int Menu();

//Esc to go back to a previous screen. for RemoveTask().
int EscLogic(){
	string removalNum;
while (true) {
	if (_kbhit()) {
		key = _getch();

		if (key == 27) { // ESC key to exit
			std::cout << "\033[2J\033[3J\033[H";
			Menu();
		}
		if (key == 8) { // Backspace handling
			if (!removalNum.empty()) {
				removalNum.pop_back();
				std::cout << "\b \b";
			}
			continue;
		}
		if (key == '\r' || key == '\n') { // Enter key

			if (Task.size() == 0) {
				std::cout << "\033[2J\033[3J\033[H";
				std::cout << "\033[1;31mThe list is empty!\033[0m" 
					"\nWhat would you like to remove: ";
				continue;
			}
			if (!removalNum.empty()) {
				int removeID = std::stoi(removalNum); // Convert input to integer
				if (Task.erase(removeID)) {
					std::cout << "\033[2J\033[3J\33[H";
					std::cout << "\033[1;32mTask " << removeID << " removed successfully.\033[0m" << std::endl;
				}
				else {
					std::cout << "\033[2J\033[3J\33[H";
					std::cout << "\033[1;31mTask " << removeID << " not found!\033[0m" << std::endl;;
				}
			}
			else {
				std::cout << "\033[2J\033[3J\33[H";
				std::cout << "\033[1;31mInvalid input.\033[0m" << std::endl;

			} 

			// Reset input and prompt again
			removalNum.clear();
			for (auto const& element : Task) {
				std::cout << element.first << "." << element.second << std::endl;
			}
			std::cout << "What would you like to remove: ";
			continue;
		}

		if (isdigit(key)) { // Ensure only digits are added
			removalNum += key;
			std::cout << key;
		}
	}
}

return 0;

}

//Esc to go back to a previous screen. for AddTask().
int EscLogicTask() {
	while (true) {
		if (_kbhit()) {

			key = _getch();

			if (key == 27) {
				return 0;
			}
			//Handles backspace
			if (key == 8) {
				if (!objective.empty()) {
					objective.pop_back();
					std::cout << "\b \b";
				}
				continue;
			}


			if (key == '\r' || key == '\n') {
				if (objective.empty()) {
					std::cout << "\033[2J\033[3J\033[H";
					std::cout << "\033[1;31mPlease enter something!\033[0m"
						"\nWhat would you like to add: ";
					continue;
				}

				//Adds it to the map.
				Task[++TaskCounter] = objective;
				objective.clear();
				std::cout << "\033[2J\033[3J\033[H";
				std::cout << "\033[1;032mTask sucessfully added.\033[0m" << std::endl;
				std::cout << "What would you like to add: ";
				continue;
			}
			// Add the pressed key to the objective string and display it in the console.
			objective += key;
			std::cout << key;
			
		}
		
	}

	
	return 0;

}

int AddTask() {
	std::cout << "\033[2J\033[3J\033[H";

	std::cout << "What would you like to add: ";
	EscLogicTask();
	std::cout << "\033[2J\033[3J\033[H";
	return 0;
}

int RemoveTask() {
	while (true) {
		std::cout << "\033[2J\033[3J\033[H";
		std::cout << "Your To-Do List: " << std::endl;
		//prints out my map.
		for (auto const& element : Task) {
			std::cout << element.first << "." << element.second << std::endl;
		}	
		std::cout << "What would you like to remove: ";
		EscLogic();
	}
}


int ViewList() {
	char key = 0;
	do {
		std::cout << "\033[2J\033[3J\033[H";
		std::cout << "Your To-Do List:" << std::endl;
		for (auto const& element : Task) {
			std::cout << element.first << "." << element.second << std::endl;
		}
		key = getch();
	} while (key != 27);

	if (key == 27) {
		std::cout << "\033[2J\033[3J\033[H";
		return 0;
	}
}
int Menu() {
	
	while (true) {
		
		int MenuNavigation;
		bool valid = false;
		std::cout << "Your To-Do List Menu:" << std::endl;
		std::cout << "1.Add Task" << std::endl;
		std::cout << "2.Remove Task" << std::endl;
		std::cout << "3.View List" << std::endl;
		std::cout << "4.Exit" << std::endl;
		do {
			std::cout << "\n(ESC to go back)" << std::endl;
			std::cout << "What would you like to do: ";
			std::cin >> MenuNavigation;
			if (!std::cin.fail()) {
				valid = true;
			}
			else {//Prevents the program from crashing.
				std::cout << "\033[2J\033[3J\033[H";
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
		}while(!valid);
		switch (MenuNavigation) {
		case 1:
			AddTask();
			break;
		case 2:
			RemoveTask();
			break;
		case 3:
			ViewList();
			break;
		case 4:
			exit(0);
			break;
		default:
			std::cout << "\033[2J\033[3J\033[H";
			std::cout << "\033[1;031mError... Invalid option try again!\033[0m" << std::endl;
		}

		
	}

}
//Start of the program.
int main() {
	Menu();
}