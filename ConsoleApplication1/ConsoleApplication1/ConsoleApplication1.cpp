#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>

#define PRINT_MATCH false
#define PRINT_SEARCH false

using namespace std;

class Efficiency {
public:
	Efficiency(std::string file_name) : file_name(file_name)
	{
		file.open(this->file_name, ios::in);
		if (!file.is_open())
			std::cout << "file is not open \n";

		//push_lib_from_file();
		push_test_lib();
		lib_temp = lib_vector;

		//delete_lib();

		/*write_to_file("output.txt", lib_vector);
		write_to_file("deleted_lib.txt", lib_deleted);

		print_all_vector(lib_deleted);*/
	}
	

	void push_lib_from_file()
	{
		string line{};
		while (getline(file, line))
		{
			lib_vector.push_back({ get_libs(line)[0], get_libs(line)[1] });
		}
	}

	//bool search_row(vector<vector<string>>&vector, string search_param, int idx, bool last_param_control)
	bool search_row(vector<vector<string>>&vector, string search_param, int idx)
	{
		for (int i = 0; i < vector[idx].size(); i++)
			if (vector[idx][i] == search_param)
				//if (last_param_control && vector[idx][i] == vector[idx].back())
					//return false;

				return true;

		return false;
	}
	int row_control(string parent_lib, string child_lib, int row_idx)
	{
		int parent_index = -1;
		int child_index = -1;

		for (int i = 0; i < lib_temp.size(); i++)
		{
			if (i == row_idx)
				continue;

			for (int k = 0; k < lib_temp[i].size(); k++)
			{
				if (lib_temp[i][k] == child_lib)
					child_index = k;
				if (lib_temp[i][k] == parent_lib)
					parent_index = k;
				if (child_index != -1 && parent_index != -1 && parent_index < child_index)
					return i;
			}
			parent_index = -1;
			child_index = -1;
		}
		return -1;
	}
	bool find_last_element(int idx)
	{
		// controls "x" row 
		// if last element is first element another row (y)
		// search all element of y row from x rows
		// if found, pass this line
		// else y row will add to end of x row 

		string search_lib = lib_vector[idx].back();
		
		vector <int> parent_idx;

		for (int i = 0; i < lib_vector.size(); i++)
		{
			if (lib_vector[i].front() == search_lib)
				parent_idx.push_back(i);
		}
		for (int i = 0; i < parent_idx.size(); i++)
		{
			bool all_elem_dif = true;
			for (int k = 1; k < lib_vector[parent_idx[i]].size(); k++)
			{
				bool same_element = search_row(lib_vector, lib_vector[parent_idx[i]][k], idx);
				if (same_element)
				{
					all_elem_dif = false;
					continue;
				}
			}
			if (all_elem_dif)
			{
				cout << "idx= " << idx << " row number: " << parent_idx[i] << "\n";
				// y row will  add  to x row here.
				lib_vector[5].insert(lib_vector[5].end(), lib_vector[parent_idx[i]].begin() + 1, lib_vector[parent_idx[i]].end());
			}

			cout << "\n";
		}

		return false;
	}
	void push_test_lib()
	{

		lib_vector.push_back({ "1.h", "2.h" });                         // 0
		lib_vector.push_back({ "1.h", "2.h" });                         // 0
		lib_vector.push_back({ "1.h", "2.h", "3.h" });                  // 1
		lib_vector.push_back({ "1.h", "2.h", "17.h"});                  // 2
		lib_vector.push_back({ "1.h", "2.h", "16.h", "17.h"});          // 3 
		lib_vector.push_back({ "1.h", "2.h", "3.h", "17.h"});           // 4
		lib_vector.push_back({ "1.h", "2.h", "18.h", "3.h", "17.h"});   // 5
		lib_vector.push_back({ "1.h", "2.h", "8.h"});                   // 6
		lib_vector.push_back({ "2.h", "3.h" });                         // 7
		lib_vector.push_back({ "17.h", "18.h" });                       // 8                   
		lib_vector.push_back({ "17.h", "18.h", "16.h"});                // 9
		lib_vector.push_back({ "17.h", "16.h"});                        // 10
		lib_vector.push_back({ "2.h", "7.h" });                         // 11
		lib_vector.push_back({ "2.h", "17.h" });                        // 12
		lib_vector.push_back({ "4.h", "3.h", "1.h", "2.h" });           // 13

		

		//cout << boolalpha << row_control("2.h", "3.h", 7);

		//print_all_vector(lib_vector);

		//cout << boolalpha << find_last_element(5);
		//print_all_vector(lib_vector);


	}

	bool circular_dependency_control(string parent, string child, int idx)
	{
		for (int i = 0; i < lib_vector.size(); i++)
		{
			if (i == idx)
				continue;

			if (lib_vector[i][0] == child && lib_vector[i][1] == parent)
			{
				return true;
			}
		}
		return false;
	}
	void delete_lib()
	{
		for (int i = 0; i < lib_vector.size(); i++)
		{
			bool is_delete = search_parent_child(lib_vector[i][0], lib_vector[i][1], i, lib_parent, lib_child);
			bool is_cricular  = circular_dependency_control(lib_vector[i][0], lib_vector[i][1], i);
			
			cout <<	"id= "   << i << "\t";
			cout <<	"is_cricular= " << boolalpha << is_cricular << "\t";
			cout <<	"is_delete= "   << boolalpha << is_delete   << "\n";

			if (is_cricular == false && is_delete == true)
			{
				lib_deleted.push_back({ lib_vector[i][0], lib_vector[i][1] });
				delete_idx.push_back(i);

				//lib_vector.erase(lib_vector.begin() + i);
				//i = 0;
			}

			//for(auto i : delete_idx)
			//{
			//	cout << i <<"\n";
			//}

		}
	}

	static std::string* get_libs(std::string line)
	{
		/* 
		// gives libs as a string list like below
		// line = "ChannelHandler.h" -> "GmdssEnums.h";
		// lib1 = ChannelHandler.h 
		// lib2 = GmdssEnums.h
		// return {lib1, lib2};
		*/

		//"ChannelHandler.h" -> "GmdssEnums.h"

		size_t point1 = line.find("\"");
		size_t point2 = line.find("\"", point1 + 1);
		size_t point3 = line.find("\"", point2 + 1);
		size_t point4 = line.find("\"", point3 + 1);

		size_t lib1_range = point2 - point1;
		size_t lib2_range = point4 - point3;

		std::string* libs = new std::string[2];

		libs[0] = line.substr(point1 + 1, lib1_range - 1);
		libs[1] = line.substr(point3 + 1, lib2_range - 1);

		return libs;
	}

	bool match_parent_child(string parent_lib_name, string child_lib_name, 
		vector<vector<string>>& lib_parent, vector<vector<string>>& lib_child)
	{
		for (int i = 0; i < lib_parent.size(); i++)
		{
			for (int k = 0; k < lib_child.size(); k++)
			{
				if (lib_child[k][0] == lib_parent[i][1])
				{
					if (PRINT_MATCH)
					{
						cout << "Founded match parent chield\n";
						cout << "lib_child  index= " << k << "\n";
						cout << "lib_parent index= " << i << "\n\n";
					}
					return true;
				}
			}
		}
		return false;
	}
	
	bool search_parent_child(string parent_lib_name, string child_lib_name, int parent_id,
		vector<vector<string>>& lib_parent, vector<vector<string>>& lib_child)
	{
		if (PRINT_SEARCH)
		{
			cout << "Searching lib..\n";
			cout << "parent lib = " << parent_lib_name << "\n";
			cout << "child lib  = " << child_lib_name << "\n";
			cout << "index      = " << parent_id << "\n\n";
		}

		for (int i = 0; i < lib_vector.size(); i++)
		{
			if (i == parent_id)
				continue;

			if (lib_vector[i][0] == parent_lib_name)
				lib_parent.push_back(lib_vector[i]);

			for (int k = 0; k < lib_vector[i].size(); k++)
				if (lib_vector[i][k] == child_lib_name)
					lib_child.push_back(lib_vector[i]);
		}
		return match_parent_child(parent_lib_name, child_lib_name, lib_parent, lib_child);
	}

	void print_all_vector(vector<vector<string>>& vector)
	{
		cout << "\n-----------------------------------\n";
		for (int i = 0; i < vector.size(); i++) {
			for (int j = 0; j < vector[i].size(); j++)
			{
				int size = static_cast <int>(vector[i][j].length());
				std::cout << "[" << i << "][" << j << "]" << vector[i][j] << setw(50 - size) << " ";
			}
			cout << "\n";
		}
		cout << "\n";
		cout << "[INFO]: Vector Size= " << lib_vector.size() << "\n";
		cout << "---------------------------------------------------";
	}

private:
	void delete_line()
	{
		/*
			this function will delete included library from file 
		*/

		string str = "selman tercioglu\nahmet deneme\ntest\n";
		cout << "*******************************\n";
		cout << str << "";
		cout << "*******************************\n";

		size_t nFPos = str.find("selman tercioglu");
		//size_t nFPos = test.find("selman tercioglu");
		size_t secondNL = str.find('\n', nFPos);
		size_t firstNL = str.rfind('\n', nFPos);

		if (firstNL == string::npos)
		{
			firstNL = 0;
			str.erase(firstNL, secondNL + 1 - firstNL);
		}
		else {
			str.erase(firstNL, secondNL - firstNL);
		}
		cout << str << "";
		cout << "*******************************\n";
	}
	
	vector<vector<string>> lib_update;// efficient library list
	vector<vector<string>> lib_vector;
	vector<vector<string>> lib_temp;
	vector<vector<string>> lib_parent;
	vector<vector<string>> lib_child;
	vector<vector<string>> lib_deleted;
	vector <int> delete_idx;

	std::ifstream file;
	std::string file_name{};

	void write_to_file(string output_file_name, vector<vector<string>>& vector)
	{
		ofstream output_file(output_file_name);
		if (output_file.is_open())
		{
			for (int i = 0; i < vector.size(); i++)
			{
				for (int j = 0; j < vector[i].size(); j++)
				{
					int size = static_cast <int>(vector[i][j].length());
					if(j== 0)
						output_file << "\"" << vector[i][j] << "\" -> " << setw(50 - size) << " ";
					
					else
						output_file << "\"" << vector[i][j] << "\"" << setw(50 - size) << " ";
				}
				output_file << "\n";
			}
		}
	}
};

/*


void test()
{
	vector<vector<string>> lib_vector;
	//
	//algoritma alternatifleri
	//mehmet'i iceren bir listeye al.
	//bu listedekilerle test'in icerdiklerini karsilastir.
	//ayni olmasi durumunda mehmet'i sil.

	lib_vector.push_back({ "fatih", "mehmet" });
	lib_vector.push_back({ "ali", "mehmet" });

	lib_vector.push_back({ "test", "ali" });
	lib_vector.push_back({ "test", "fatma" });

	lib_vector.push_back({ "test", "mehmet" });

	//lib_vector.erase(lib_vector.begin() + 2);
}

vector<vector<string>> lib_vector;
vector<vector<string>> lib_parent;
vector<vector<string>> lib_child;

bool match_parent_child(string parent_lib_name, string child_lib_name)
{
	for (int i = 0; i < lib_parent.size(); i++)
	{
		for (int k = 0; k < lib_child.size(); k++)
		{
			if (lib_child[k][0] == lib_parent[i][1])
			{
				if (PRINT_MATCH)
				{
					cout << "lib_child  index= " << k << "\n";
					cout << "lib_parent index= " << i << "\n\n";
				}
				return true;
			}
		}
	}
	return false;
}

bool search_parent_child(string parent_lib_name, string child_lib_name, int parent_id)
{
	if (PRINT_SEARCH)
	{
		cout << "Searching lib..\n";
		cout << "parent lib = " << parent_lib_name << "\n";
		cout << "child lib  = " << child_lib_name << "\n";
		cout << "index      = " << parent_id << "\n\n";
	}

	for (int i = 0; i < lib_vector.size(); i++)
	{
		if (i == parent_id)
			continue;

		if (lib_vector[i][0] == parent_lib_name)
			lib_parent.push_back(lib_vector[i]);

		for (int k = 0; k < lib_vector[i].size(); k++)
			if (lib_vector[i][k] == child_lib_name)
				lib_child.push_back(lib_vector[i]);
	}
	return match_parent_child(parent_lib_name, child_lib_name);
}
void test_push_back()
{
	lib_vector.push_back({ "fatih", "mehmet" });
	lib_vector.push_back({ "ali", "mehmet" });
	lib_vector.push_back({ "test", "ali" });
	lib_vector.push_back({ "test", "mehmet" }); // unneccessary 
	lib_vector.push_back({ "test", "ayse" });   // unneccessary 
	lib_vector.push_back({ "fatih", "ayse" });
}

void print_all_vector(bool all_list, bool parent_list, bool child_list)
{
	if (all_list)
	{
		cout << "all list\n";
		for (int i = 0; i < lib_vector.size(); i++) {
			for (int j = 0; j < lib_vector[i].size(); j++)
				std::cout << "[" << i << "][" << j << "]" << lib_vector[i][j] << "\t";
			cout << "\n";
		}
	}
	if (parent_list)
	{
		cout << "\nparent list\n";
		for (int i = 0; i < lib_parent.size(); i++) {
			for (int j = 0; j < lib_parent[i].size(); j++)
				std::cout << "[" << i << "][" << j << "]" << lib_parent[i][j] << "\t";
			cout << "\n";
		}
	}
	if (child_list)
	{
		cout << "\nchild list\n";
		for (int i = 0; i < lib_child.size(); i++) {
			for (int j = 0; j < lib_child[i].size(); j++)
				std::cout << "[" << i << "][" << j << "]" << lib_child[i][j] << "\t";
			cout << "\n";
		}
	}
	cout << "\n\n";

	//for (int i = 0; i < lib_vector.size(); i++) {
	//    for (int j = 0; j < lib_vector[i].size(); j++)
	//        std::cout << lib_vector[i][j] << "\t[" << i << "][" << j << "]\n";
	//}

}

int main()
{
	//std::string line =  "\"ChannelHandler.h\" -> \"GmdssEnums.h\"";
	//Efficiency x("dependency.txt");


	//test_push_back();
	//
	//print_all_vector(true,false,false);

	//for (int i = 0; i < lib_vector.size(); i++)
	//{
	//    bool is_delete = search_parent_child(lib_vector[i][0], lib_vector[i][1], i);
	//    if (is_delete)
	//        lib_vector.erase(lib_vector.begin() + 3);
	//}

	//print_all_vector(true,false,false);
}

*/



bool recursive_control(vector<vector<string>>& vector, int idx, string parent, string child)
{
	for (int i = 0; i < vector[idx].size(); i++)
	{
		for (int k = 0; k < vector.size(); k++)
		{
			if (k == idx)
				continue;
			if (vector[k][0] == child, vector[k][1] == parent)
			{
				return true;
			}
		}
	}
	return false;
}
int main()
{
	Efficiency x("test.txt");

}