#include <iostream>
using namespace std;
int boardAns[3][3] = { 1,2,3,4,5,6,7,8,0 };
int N = 0;
int calculateManhattan(int arr[3][3], int ex[3][3])
{
	int sol = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			if (arr[i][j] == 0)
				continue;
			if (arr[i][j] != ex[i][j])
			{
				for (int k = 0; k < 3; k++)
					for (int l = 0; l < 3; l++)
					{
						if (arr[i][j] == ex[k][l])
							sol += (abs(k - i) + abs(l - j));
					}
			}
		}
	return sol;
}

struct Node
{
	int board[3][3];
	int m;
	int p;
	int emptyI;
	int emptyJ;
	int lastI;
	int lastJ;
	int s;
};

Node* pq;

Node temp;
void swim(int k)
{
	while (k > 1 && pq[k / 2].p >= pq[k].p)
	{

		swap(pq[k], pq[k / 2]);
		k /= 2;
	}
}
int asd = 0;
void sink(int k)
{
	while (2 * k <= N)
	{
		int j = 2 * k;
		if (j < N && pq[j + 1].p <= pq[j].p)
			j++;
		if (pq[k].p <= pq[j].p)
			break;
		swap(pq[k], pq[j]);
		k = j;
	}
}
int xd = 0;
void insert(int newBoard[3][3])
{
	++N;
	if (xd == 0)
	{
		pq[N].s = 0;
		xd++;
	}
	else
		pq[N].s = temp.s + 1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			pq[N].board[i][j] = newBoard[i][j];
			if (newBoard[i][j] == 0)
			{
				pq[N].emptyI = i;
				pq[N].emptyJ = j;
			}
		}

	pq[N].p = calculateManhattan(pq[N].board, boardAns) + pq[N].s;
	swim(N);
}


void delMax()
{
	swap(pq[1], pq[N--]);
	sink(1);
	pq[N + 1] = {};

}
int lastI = -1;
int lastJ = -1;
bool swapAndTest(Node& child, int i, int j, int nI, int nJ)
{
	if (nI < 0 || nI > 2 || nJ < 0 || nJ > 2 || lastI == nI && lastJ == nJ)
		return false;

	else
	{
		swap(child.board[i][j], child.board[nI][nJ]);
		child.emptyI = nI;
		child.emptyJ = nJ;
	}
	return true;
}

void Solve()
{
	while (true)
	{
		asd++;
		Node* childs = new Node[4];
		temp = pq[1];
		cout << "*****" << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				cout << pq[1].board[i][j] << " ";
			cout << endl;
		}
		delMax();

		for (int k = 0; k < 4; k++)
		{

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
				{
					childs[k].board[i][j] = temp.board[i][j];
				}
			childs[k].emptyI = temp.emptyI;
			childs[k].emptyJ = temp.emptyJ;
		}
		//UP
		if (swapAndTest(childs[0], childs[0].emptyI, childs[0].emptyJ, childs[0].emptyI - 1, childs[0].emptyJ))
		{
			insert(childs[0].board);

		}
		//DOWN

		if (swapAndTest(childs[1], childs[1].emptyI, childs[1].emptyJ, childs[1].emptyI + 1, childs[1].emptyJ))
		{
			insert(childs[1].board);

		}
		//RIGHT


		if (swapAndTest(childs[2], childs[2].emptyI, childs[2].emptyJ, childs[2].emptyI, childs[2].emptyJ + 1))
		{
			insert(childs[2].board);
		}
		//LEFT

		if (swapAndTest(childs[3], childs[3].emptyI, childs[3].emptyJ, childs[3].emptyI, childs[3].emptyJ - 1))
		{
			insert(childs[3].board);
		}
		lastI = temp.emptyI;
		lastJ = temp.emptyJ;
		if (calculateManhattan(pq[1].board, boardAns) == 0)
			break;
	}
}

int main()
{
	pq = new Node[1000000];

	int b[3][3];
	for (int k = 0; k < 3; k++)
		for (int j = 0; j < 3; j++)
		{
			cin >> b[k][j];

		}
	insert(b);
	temp.s = 0;
	Solve();
	cout << pq[1].s;
	int x = N;
}