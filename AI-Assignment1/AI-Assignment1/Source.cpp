#include <iostream>
#include <string>
#include <queue>
#include <set>
using namespace std;

class Node
{
public:
	int state;
	int action;
	int cost;
	Node *parent;

	Node(int s, int a, int c, Node *p)
	{
		state = s;
		action = a;
		cost = c;
		parent = p;
	}

};

void GraphSearch(string initialState, string goalState)
{
	int initial=-1;
	int goal=-1;
	queue<Node*> frontier;
	queue<Node*> exploredSet;
	int m = 8;
	int n = 3; 
	int t = 2;
	string states[8]= { "AgentInRoom1, Room1Dusty, Room2Dusty",
		  "AgentInRoom1, Room1Dusty, Room2Clean",
		  "AgentInRoom1, Room1Clean, Room2Dusty",
		  "AgentInRoom1, Room1Clean, Room2Clean",
		  "AgentInRoom2, Room1Dusty, Room2Dusty",
		  "AgentInRoom2, Room1Dusty, Room2Clean",
		  "AgentInRoom2, Room1Clean, Room2Dusty",
		  "AgentInRoom2, Room1Clean, Room2Clean" };
	string actions[3]= { "Clean","MoveToRoom1","MoveToRoom2" };
	int transitionTable[8][3] = { {2, 0, 4},
			{3, 1, 5},
			{2, 2, 6},
			{3, 3, 7},
			{5, 0, 4},
			{5, 1, 5},
			{7, 2, 6},
			{7, 3, 7} };

	for (int i = 0; i < m; i++)
	{
		if (initialState == states[i])
		{
			initial = i;
		}
	}
	if (initial == -1)
	{
		cout << "you entered invalid initial state!";
	}
	for (int i = 0; i < m; i++)
	{
		if (goalState == states[i])
		{
			goal = i;
			//cout << goal << endl;
		}
	}
	if (goal == -1)
	{
		cout << "you entered an invalid goal state!";
	}
	
	frontier.push(new Node(initial, -1, 0, nullptr));

	bool added[8] = { false,false,false,false,false,false,false,false };
	while (!frontier.empty())
	{
		if (frontier.front()->state == goal)
		{
			exploredSet.push(frontier.front());
			break;
		}
		added[frontier.front()->state] = true;
			

		for (int i = 0; i < 3; i++)
			{
				if (!added[transitionTable[frontier.front()->state][i]]) {
			     	frontier.push(new Node(transitionTable[frontier.front()->state][i], i, 0, frontier.front()));
					added[frontier.front()->state] = true;
				}
			}
			exploredSet.push(frontier.front());
			frontier.pop();
			
		}

	exploredSet.pop();
	while (!exploredSet.empty())
	{
		cout << actions[exploredSet.front()->action]<<endl;
		exploredSet.pop();
	}
	
}

int main()
{
	cout << "Enter initial state: ";
	string initial,goal;
	getline(cin, initial);
	cout << "Enter goal state: ";
	getline(cin, goal);
	GraphSearch(initial, goal);
	
	system("pause");
}