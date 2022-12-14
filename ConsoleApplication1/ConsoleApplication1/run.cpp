#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>

#define PRINT_MATCH false

using namespace std;

class Efficiency {
public:

	Efficiency(std::string file_name) : file_name(file_name)
	{

		file.open(this->file_name, ios::in);
		if (!file.is_open())
			std::cout << "file is not open \n";

		//push_test_lib(); // test another scenario using this method.

		push_lib_from_file();
		lib_vector = lib_file;
		delete_same_line(); 
		lib_file = lib_vector; // because lines push lib_vector without sameline.
		fill_temp(); 
		run_algorithm(); 
		write_to_file("output.txt", lib_update); // writes efficient lib 
		write_to_file("deleted_lib.txt", lib_deleted); // writes deleted lib 
		write_to_file("lib_vector.txt", lib_vector); // writes lib that contains all node
		cout << "Before   size= " << lib_file.size() << "\n"; // display size before running algorithm
		cout << "Deleted  size= " << lib_deleted.size() << "\n"; // display deleted library size
		cout << "After    size= " << lib_update.size() << "\n";// display size after running algorithm

	}
	void run_algorithm()
	{
		//(void*)getchar();
		for (int i = 0; i < lib_file.size(); i++)
		{
			int is_delete = search_parent_child(lib_vector[i][0], lib_vector[i][1], i);
			bool is_cricular = circular_dependency_control(i);

			if (is_cricular == false && is_delete != -1)
				lib_deleted.push_back(lib_file[i]);
			else
				lib_update.push_back(lib_file[i]);
			
			is_delete = false;
		}
	}

	bool is_add_node = false;
	bool is_same_line = false;

	void delete_same_line()
	{
		// if found same line, this method remove them.
		int size = lib_vector.size();
		bool same = false;
		vector<vector<string>> tmp;

		for (int i = 0; i < lib_vector.size(); i++)
		{
			same = control_same_line(i, lib_vector);
			if (!same)
				tmp.push_back({lib_vector[i]});
		}
		lib_vector = tmp;
	}

	void fill_temp()
	{
		// add node to end of node 
		int size = lib_vector.size();

		for (int i = 0; i < size; i++)
		{
			is_add_node = false;
			is_same_line = false;

			if (line_circular_control(i))
				continue;

			is_add_node = add_node_to_node(i);
			
			if (is_add_node)
			{
				//(void*)getchar();
				fill_temp();
			}
		}
		//(void*)getchar();
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
	
	int search_parent_child(string parent_lib_name, string child_lib_name, int parent_id)
	{
		
		vector <vector<string>> temp_vec;
		//cout << "parent_lib_name: " << parent_lib_name << " child_lib_name: " << child_lib_name << "\n";

		int parent_idx = -1;
		int child_idx = -1;
		
		for (int i = 0; i < lib_vector.size(); i++)
		{
			for (int k = 0; k < lib_vector[i].size(); k++)
			{
				if (lib_vector[i][k] == parent_lib_name)
					parent_idx = k;

				else if (lib_vector[i][k] == child_lib_name)
					child_idx = k;
			}
			if (parent_idx != -1 && child_idx != -1 && parent_idx < child_idx-1)
			{
				//cout << parent_idx << "\t" << child_idx << "\n";
				//cout << "row_idx: " << i << " parent_idx: " << parent_idx << " child_idx: " << child_idx << " i: " << i << "\n";
				/*
				cout << "[DEBUG]: Deleted: " << lib_vector[i][parent_idx] << " " << lib_vector[i][child_idx] << " i: " << i << "\n";
				cout << "i: " << parent_id << "\n";
				*/
				
				//cout << "row_idx: " << i << " parent_lib: " << lib_vector[i][parent_idx] << " child_idx: " << lib_vector[i][child_idx] << " i: " << i << "\n";
				return parent_id;
			}

			parent_idx = -1;
			child_idx = -1;
		}

		return -1;
	}

	bool control_same_line(int row_id, vector<vector<string>>& vector)
	{
		for (int i = row_id; i < lib_vector.size(); i++)
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
				//cout << "ayni eleman tespit edildi \n";
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
					//cout << "elemanlar ayni degil. sona ekleme gerceklesti...\n";
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

	vector<vector<string>> lib_update; // efficient library list
	vector<vector<string>> lib_file;   // readed library list from file
	vector<vector<string>> lib_vector; // temp vector
	vector<vector<string>> lib_deleted;

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
	Efficiency x("dependency.txt");
	//Efficiency x("test.txt");
	std::cout << "[INFO]: Program ended! \n\n";
}