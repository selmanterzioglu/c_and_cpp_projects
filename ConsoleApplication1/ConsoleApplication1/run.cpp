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


		//push_test_lib();

		push_lib_from_file();
		lib_vector = lib_file;
		fill_temp();
		run_algorithm();
		write_to_file("output.txt", lib_update);
		write_to_file("deleted_lib.txt", lib_deleted);
		cout << "Before   size= " << lib_file.size() << "\n";
		cout << "Deleted  size= " << lib_deleted.size() << "\n";
		cout << "After    size= " << lib_update.size() << "\n";

	}
	void run_algorithm()
	{
		for (int i = 0; i < lib_file.size(); i++)
		{

			/*cout << lib_parent.size() << "\n";
			cout << lib_child.size() << "\n";*/

			bool is_delete = search_parent_child(lib_vector[i][0], lib_vector[i][1], i, lib_parent, lib_child);
			bool is_cricular = circular_dependency_control(i);

			//if (is_cricular == false && is_delete == true)
			if (!is_delete)
				lib_deleted.push_back(lib_file[i]);
			else
				lib_update.push_back(lib_file[i]);
		}
	}

	bool is_add_node = false;
	bool is_same_line = false;

	void fill_temp()
	{
		int size = lib_vector.size();
		for (int i = 0; i < size; i++)
		{
			cout << "lib_vector.size(): " << lib_vector.size() << "\n";
			cout << "lib_vector: ";
			print_all_vector(lib_vector);

			if (line_circular_control(i))
				continue;

			is_same_line = control_same_line(i, lib_vector);

			if (is_same_line)
			{
				lib_vector.erase(lib_vector.begin() + i);
				cout << "same  line detected !! idx= ["<< i << "] \n";
				
				cout << "is_add_node:  " << boolalpha << is_add_node << "\n";
				cout << "is_same_line: " << boolalpha << is_same_line << "\n";

				(void*)getchar();
				fill_temp();
				continue;
			}

			is_add_node = add_node_to_node(i);
			
			if (is_add_node)
			{
				cout << "add_note is true! id= " << i << "\n";

				cout << "is_add_node:  " << boolalpha << is_add_node << "\n";
				cout << "is_same_line: " << boolalpha << is_same_line << "\n";

				(void*)getchar();
				fill_temp();
			}

			if (is_add_node && is_same_line)
				cout << "ikiside true";
		}
		
		cout << "\n\n\n\nfill_temp func ended..!!!!\n";
		(void*)getchar();
	}

	void push_lib_from_file()
	{
		string line{};
		while (getline(file, line))
		{
			lib_file.push_back({ get_libs(line)[0], get_libs(line)[1] });
		}
	}

	bool search_row(vector<vector<string>>&vector, string search_param, int idx)
	{
		// search element on idx row. --> vector[idx] = {elem1, elem2};
		// if found, return true

		for (int i = 0; i < vector[idx].size(); i++)
			if (vector[idx][i] == search_param)
				return true;

		return false;
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



	bool control_same_line(int row_id, vector<vector<string>>& vector)
	{
		for (int i = 0; i < lib_vector.size(); i++)
		{
			if (row_id == i)
				continue;

			if (lib_vector[row_id] == vector[i])
				return true;
		}
		return false;
	}

	bool control_vectors_line(vector<vector<string>>& current_vector, vector<vector<string>>& compare_vector, int compare_id)
	{
		for (int i = 0; i < current_vector.size(); i++)
		{
			if (current_vector[i].size() != compare_vector[compare_id].size())
				continue;

			int counter = 0;

			for (int k = 0; k < current_vector[i].size(); k++)
				if (current_vector[i][k] == compare_vector[compare_id][k])
					++counter;

			if (counter == current_vector[i].size())
			{
				cout << "ayni eleman tespit edildi \n";
				return true;
			}
		}
		return false;
	}
		
	bool add_node_to_node(int idx)
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
			if(idx == i)
				continue;

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
				// push  current line to back, because this should't delete from vector.
				//lib_vector.push_back({ lib_vector[idx]});

				vector <vector<string>> temp;

				temp.push_back({ lib_vector[idx]});
				int temp_size = temp.size() -1;
				temp[temp_size].insert(temp[temp_size].end(), lib_vector[parent_idx[i]].begin() + 1, lib_vector[parent_idx[i]].end());

				if (control_vectors_line(lib_vector, temp, temp_size))
					return false;
				else
				{
					cout << "elemanlar ayni degil. sona ekleme gerceklesti...\n";
					lib_vector.push_back({temp[temp_size]});
					return true;
				}

				//lib_vector[idx].insert(lib_vector[idx].end(), lib_vector[parent_idx[i]].begin() + 1, lib_vector[parent_idx[i]].end());
				//cout << "last_size: " << temp.size();



				// y row will  add  to x row here.
				//lib_vector[idx].insert(lib_vector[idx].end(), lib_vector[parent_idx[i]].begin() + 1, lib_vector[parent_idx[i]].end());
				return true;
			}
			//cout << "\n";
		}

		return false;
	}
	
	void push_test_lib()
	{
		lib_vector.push_back({ "1.h", "2.h", "3.h"});                   // 0
		lib_vector.push_back({ "3.h", "1.h", "7.h"});                   // 1
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
		lib_vector.push_back({ "10.h", "11.h"});                        // 14
		lib_vector.push_back({ "11.h", "12.h"});                        // 15
		lib_vector.push_back({ "10.h", "12.h"});                        // 16
		//lib_vector.push_back({ "10.h", "11.h", "12.h" });               // 17
		lib_vector.erase(lib_vector.begin() + 1);
		print_all_vector(lib_vector);

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

	void print_all_vector(vector<vector<string>>& vector)
	{
		cout << "\n-----------------------------------\n";
		for (int i = 0; i < vector.size(); i++) {
			for (int j = 0; j < vector[i].size(); j++)
			{
				int size = static_cast <int>(vector[i][j].length());
				//std::cout << "[" << i << "][" << j << "] " << vector[i][j] << setw(50 - size) << " ";
				std::cout << "[" << i << "][" << j << "] " << vector[i][j] << setw(size) << " ";
			}
			cout << "\n";
		}
		cout << "\n";
		cout << "[INFO]: Vector Size= " << lib_vector.size() << "\n";
		cout << "\n-----------------------------------\n";
	}

private:

	int row_recursive_control(string parent_lib, string child_lib, int current_line_idx)
	{
		int parent_index = -1;
		int child_index = -1;

		for (int i = 0; i < lib_vector[current_line_idx].size(); i++)
		{
			if (lib_vector[current_line_idx][i] == child_lib)
				child_index = i;
			if (lib_vector[current_line_idx][i] == parent_lib)
				parent_index = i;
			if (child_index != -1 && parent_index != -1 && parent_index > child_index)
				return i;
			parent_index = -1;
			child_index = -1;
		}
		return -1;
	}

	bool line_circular_control(int current_line_idx)
	{
		for (int i = 0; i < lib_vector[current_line_idx].size(); i++)
		{
			if (i == current_line_idx)
				continue;

			for (int k = i + 1; k < lib_vector[current_line_idx].size(); k++)
			{
				int recursive_dependency = row_recursive_control(lib_vector[current_line_idx][i], lib_vector[current_line_idx][k], k);

				if (recursive_dependency != -1)
					return true;
			}
		}
		return false;
	}
	bool circular_dependency_control(int row_idx)
	{
		bool is_all_row = false;
		for (int i = 0; i < lib_vector.size(); i++)
		{
			bool is_cricular = line_circular_control(row_idx);

			if (is_cricular)
				is_all_row = true;
		}
		return is_all_row;
	}

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
	
	vector<vector<string>> lib_update; // efficient library list
	vector<vector<string>> lib_file; // efficient library list
	vector<vector<string>> lib_vector; // temp vector
	vector<vector<string>> lib_deleted;
	vector<vector<string>> lib_parent;
	vector<vector<string>> lib_child;
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

int main()
{

	std::cout << "[INFO]: Program is running...\n";
	Efficiency x("test.txt");
	std::cout << "[INFO]: Program ended! \n\n";

	//vector <vector<string>> vector1;
	//vector <vector<string>> vector2;

	//vector1.push_back({ "ahmet", "selman" });     // 0
	//vector1.push_back({ "selman", "tercioglu" }); // 1


	//vector2.push_back({ "selman", "tercioglu" }); // 1

	
}