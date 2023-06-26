// C++ program for building suffix array of a given text
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include<fstream>

using namespace std;

// Structure to store information of a suffix
struct suffix
{
	int index; // To store original index
	int rank[2]; // To store ranks and next rank pair
};

// A comparison function used by sort() to compare two suffixes
// Compares two pairs, returns 1 if first pair is smaller
int cmp(struct suffix a, struct suffix b)
{
	return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) :
		(a.rank[0] < b.rank[0] ? 1 : 0);
}

// This is the main function that takes a string 'txt' of size n as an
// argument, builds and return the suffix array for the given string
int *buildSuffixArray(char *txt, int n)
{
	// A structure to store suffixes and their indexes
	struct suffix* suffixes= new suffix[n];

	// Store suffixes and their indexes in an array of structures.
	// The structure is needed to sort the suffixes alphabetically
	// and maintain their old indexes while sorting
	for (int i = 0; i < n; i++)
	{
		suffixes[i].index = i;
		suffixes[i].rank[0] = txt[i] - 'a';
		suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
	}

	// Sort the suffixes using the comparison function
	// defined above.
	sort(suffixes, suffixes + n, cmp);

	// At this point, all suffixes are sorted according to first
	// 2 characters.  Let us sort suffixes according to first 4
	// characters, then first 8 and so on
	int* ind= new int[n];  // This array is needed to get the index in suffixes[]
				 // from original index.  This mapping is needed to get
				 // next suffix.
	for (int k = 4; k < 2 * n; k = k * 2)
	{
		// Assigning rank and index values to first suffix
		int rank = 0;
		int prev_rank = suffixes[0].rank[0];
		suffixes[0].rank[0] = rank;
		ind[suffixes[0].index] = 0;

		// Assigning rank to suffixes
		for (int i = 1; i < n; i++)
		{
			// If first rank and next ranks are same as that of previous
			// suffix in array, assign the same new rank to this suffix
			if (suffixes[i].rank[0] == prev_rank &&
				suffixes[i].rank[1] == suffixes[i - 1].rank[1])
			{
				prev_rank = suffixes[i].rank[0];
				suffixes[i].rank[0] = rank;
			}
			else // Otherwise increment rank and assign
			{
				prev_rank = suffixes[i].rank[0];
				suffixes[i].rank[0] = ++rank;
			}
			ind[suffixes[i].index] = i;
		}

		// Assign next rank to every suffix
		for (int i = 0; i < n; i++)
		{
			int nextindex = suffixes[i].index + k / 2;
			suffixes[i].rank[1] = (nextindex < n) ?
				suffixes[ind[nextindex]].rank[0] : -1;
		}

		// Sort the suffixes according to first k characters
		sort(suffixes, suffixes + n, cmp);
	}

	// Store indexes of all sorted suffixes in the suffix array
	int *suffixArr = new int[n];
	for (int i = 0; i < n; i++)
		suffixArr[i] = suffixes[i].index;

	// Return the suffix array
	return  suffixArr;
}

// A utility function to print an array of given size
void printArr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

// Driver program to test above functions
int main(int argc,char** argv)
{
	/*cout << "Enter fasta file : ";
	cin >> argv[1];
	cout << "Enter file to recive suffix : ";
	cin >> argv[2];*/

	char* text;
	int pos;
	fstream file;
	file.open(argv[1], ios::out | ios::in);

	file.seekg(0, ios::end);
	pos= file.tellg();

	//cout << pos << endl;

	char *x;
	x = (char*)malloc(1 * sizeof(char));

	text = (char*)malloc(pos * sizeof(char));
	
	file.seekg(0, ios::beg);


	int count = 0;

	for (int i = 0; i < pos; i++) {

	file.seekg(i, ios::beg);
		file.get(x[0]);

		if (x[0] == 10)
			continue;

		text[count] = x[0];
		count++;
	}

	file.close();
	
	int *suffixArr = buildSuffixArray(text, count);

	cout <<"Suffix count is : "<< count<<endl;
	/*
	FILE *fptr = fopen(argv[2], "w");
	fwrite(suffixArr, sizeof(int), count, fptr);
	fclose(fptr);
	*/

	/*
		FILE *fp;
		int c;

		fp = fopen("suffix.txt", "r");
		int y = 0;
		while (1) {
			c = fgetc(fp);
			if (feof(fp)) {
				break;
			}
			if (y % 4 == 0)
				printf("%d", c);

			y++;
		}
		fclose(fp);*/

    FILE *fptr = fopen("suffixNum.txt", "w");

		for (int i = 0; i < count; i++)
		fprintf(fptr,"%d ",suffixArr[i]);

	//printArr(suffixArr, count);
	return 0;
}