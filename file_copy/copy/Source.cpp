#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<fstream>

void init(std::string *f_name, std::string *dir1_name, std::string *dir2_name) 
{
	std::cout << "Введите путь до директории, в которой хранится файл: ";
	getline(std::cin, *dir1_name);
	std::cout << "Введите имя файла(в формате имя.расширение), который нужно скопировать: ";
	getline(std::cin, *f_name);

	std::cout << "Введите дерикторию, в которую нужно скопировать файл: ";
	getline(std::cin, *dir2_name);
}
void Copy(std::string f_name, std::string dir1_name, std::string dir2_name)
{
	std::ifstream File_for_copy;
	std::ofstream copy_file;
	File_for_copy.open(dir1_name + f_name, std::ios::binary | std::ios::in);
	copy_file.open(dir2_name + ("Копия_" + f_name), std::ios::binary | std::ios::out);

	if (File_for_copy.is_open())
	{
		char ch;
		while (File_for_copy.get(ch))
		{

			copy_file.put(ch);
		}
	}
	else std::cout << "Файл не найден!";
	File_for_copy.close();
	copy_file.close();
}
void main()
{
	 setlocale(LC_ALL, "Russian");
	
	 std::string dir_to_file_for_copy, Copy_dir;
	 std::string file_name;

	 

	 init(&file_name, &dir_to_file_for_copy, &Copy_dir);
	 Copy(file_name, dir_to_file_for_copy, Copy_dir);
	 


	
	 int x;
}