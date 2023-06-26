// C++ program for building suffix array of a given text
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <vector>
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
int* buildSuffixArray(char* txt, int n)
{
	// A structure to store suffixes and their indexes
	struct suffix* suffixes = new suffix[n];

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
	int* ind = new int[n];  // This array is needed to get the index in suffixes[]
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
	int* suffixArr = new int[n];
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
void search(char* pat, char* txt, int* suffArr, int n, std::string id)
{
	int m = strlen(pat);  // get length of pattern, needed for strncmp()
	



	//ofstream outdata("output_final.txt", ios::app);
	ofstream outdata("ffff.txt" , ios::app);

	// Do simple binary search for the pat in txt using the
	// built suffix array
	int l = 0, r = n - 1;  // Initialize left and right indexes
	while (l <= r)
	{
		//outdata << "Id\t";
		//outdata << "chromosome\t";
		//outdata << "index\n";


		// See if 'pat' is prefix of middle suffix in suffix array
		int mid = l + (r - l) / 2;
		int res = strncmp(pat, txt + suffArr[mid], m);

		// If match found at the middle, print it and return
		if (res == 0)
		{
			string num_chromosome = "";

			if (mid >= 0 && mid <= 85779) {
				num_chromosome = "chrom_01";
			}
			else if (mid > 85779 && mid <= 315998) {
				num_chromosome = "chrom_02";
			}			
			else if (mid > 315998 && mid <= 1129209) {
				num_chromosome = "chrom_03";
			}			
			else if (mid > 1129209 && mid <= 1445829) {
				num_chromosome = "chrom_04";
			}
			else if (mid > 1445829 && mid <= 2977762) {
				num_chromosome = "chrom_05";
			}
			else if (mid > 2977762 && mid <= 3554636) {
				num_chromosome = "chrom_06";
			}
			else if (mid > 3554636 && mid <= 3824797) {
				num_chromosome = "chrom_07";
			}
			else if (mid > 3824797 && mid <= 4915737) {
				num_chromosome = "chrom_08";
			}
			else if (mid > 4915737 && mid <= 5478380) {
				num_chromosome = "chrom_09";
			}
			else if (mid > 5478380 && mid <= 5918268) {
				num_chromosome = "chrom_10";
			}			
			else if (mid > 5918268 && mid <= 6664019) {
				num_chromosome = "chrom_11";
			}			
			else if (mid > 6664019 && mid <= 7330835) {
				num_chromosome = "chrom_12";
			}
			else if (mid > 7330835 && mid <= 8409012) {
				num_chromosome = "chrom_13";
			}			
			else if (mid > 8409012 && mid <= 9333443) {
				num_chromosome = "chrom_14";
			}			
			else if (mid > 9333443 && mid <= 10117776) {
				num_chromosome = "chrom_15";
			}			
			else if (mid > 10117776 && mid <= 11209067) {
				num_chromosome = "chrom_16";
			}			
			else if (mid > 11209067 && mid <= 12157133) {
				num_chromosome = "chrom_17";
			}
			//cout << id << "\t" << suffArr[mid] << "\t" << num_chromosome << "\n";
			outdata << id << "\t" << suffArr[mid] << "\t" << num_chromosome << "\n";
		}

		// Move to left half if pattern is alphabetically less than
		// the mid suffix
		if (res < 0) r = mid - 1;

		// Otherwise move to right half
		else l = mid + 1;
	}

	// We reach here if return statement in loop is not executed
	//cout << "\nPattern not found";
	outdata.close();
}


int main(int argc, char** argv)
{
	cout << "START Reading Genome File (: \n";
	char* text;
	int pos;
	fstream file;
	//file.open("testG.fsa", ios::out | ios::in); // Test File Genome
	file.open("genome.fsa", ios::out | ios::in); // File Of All Genome

	file.seekg(0, ios::end);
	pos = file.tellg();

	//cout << pos << endl;

	char* x;
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
	cout << "End Reading Genome File (: \n";


	int* suffixArr = buildSuffixArray(text, count);
	cout << "END PROJECT" << endl;

	//ifstream input_file("testFastaQ.TXT"); // For Testing
	ifstream input_file("N115-1n_S7_L001_R1.fastq"); // Real File
	if (input_file.is_open())
	{
		string line = "";
		string l = "";
		int counter = 0;
		char* id;
		id = &line[0];
		while (getline(input_file, line)) {

				if (counter % 4 == 0){
					l = line;
				}
				if (counter % 4 == 1) {
					char* pat;
					pat = &line[0];
					search(pat, text, suffixArr, count, l);
				}
			//lines.push_back(line);
			counter++;
		}
		input_file.close();
	}

	else
	{
		printf("Unable To Open The File ):");
		exit(0);
	}



	//char pat[] = "MR";   // pattern to be searched in text

	// search pat in txt using the built suffix array
	//search(pat, text, suffixArr, count);

	return 0;
}