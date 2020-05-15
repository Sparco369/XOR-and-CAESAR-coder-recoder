#include <string>
#include <iostream>
#include <fstream>
//#include <conion>
using namespace std;
/*Шифровщик и дешифровщик XOR*/
string XOR(string data, char key[]){
string xorstring = data;
for (int i = 0; i < xorstring.size(); i++){
	xorstring[i] = data[i] ^ key[i % (sizeof(key)/sizeof(char))];
	}	
return xorstring;
}

/*Шифровщик и дешифровщик CAESAR*/
const int ABCSize = 26; //Размер алфавита
const char low_ch[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; //Массив строчных букв, которые шифруются также строчными
const char high_ch[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; //Массив заглавных букв, которые шифруются также заглавными

 string cipher(const std::string &input_s, const int shift){ //Функция осуществляет сдвиг строки по алфавиту на указанную величину
 bool Ok; //Был ли символ определен как буква алфавита и затем зашифрован
 string output_s(""); //Зашифрованная строка, вначале инициализируется пустой строкой
 for(unsigned i = 0; i < input_s.length(); i++)
  { //Для всех символов шифруемой строки
  Ok = false; //Вначале сбрасываем значение флага
  for(int j = 0; j < ABCSize; j++)
   { //Перебираем все буквы алфавита на поиск соответствия
   if (input_s[i] == low_ch[j]) //Если символ оказался строчной буквой алфавита
    {
    j += shift; //Сдвигаем букву по алфавиту на указанное значение
    while (j >= ABCSize) j -= ABCSize; //Если значение вышло за диапазон,
    while (j < 0) j += ABCSize; //корректируем его
    output_s += low_ch[j]; //Добавляем полученный символ в конец зашифрованной строки
    Ok = true; //Символ был благополучно зашифрован и добавлен в строку
    break; //Перебор для данного символа можно закончить
    }
   else if (input_s[i] == high_ch[j]) //То же самое, если символ оказался заглавной буквой алфавита
    {
    j += shift;
    if (j >= ABCSize) j -= ABCSize;
    else if (j < 0) j += ABCSize;
    output_s += high_ch[j];
    Ok = true;
    break;
    }
   }
  if (!Ok) output_s += input_s[i]; //Если символ не является буквой алфавита,записываем его без изменений
  }
 return output_s; //По окончании возвращаем получившуюся строку
 }

int main()
{
	ifstream in("input.txt");//Входные данные
    ofstream outxor("output_xor.txt");//Место хранения зашифрованых исходных данных в XOR
	ofstream outcaesar("output_caesar.txt");//Место хранения зашифрованых исходных данных в CAESAR
	ofstream outxordec("output_decryption_xor.txt");//Место хранения расшиффрованных данных из XOR
	ofstream outcaesardec("output_decryption_caesar.txt");//Место хранения расшиффрованных данных из CAESAR

	string cod;//Хранение символов
	int a;
	int b;
	int shift;
	bool def;
	
	cout <<"Enter '1' for encryption, '0' for decryption ";  
	cin >> def;	
	
	/*Шифрование исходного текста на Английском языке в XOR или CAESAR */
	if (def == true){
		cout << "Enter '1' for  XOR encryption or '2' for CAESAR encryption: ";
		cin >> a;
		switch(a){
			case 1:{
			char key [] = " ";//массив для хранения ключа
			cout << "Enter the key for encryption: ";
			cin >> key;//Ввод ключа
			cin.getline(key, 10);//Считывание строки с ключом
			while(in){
			getline(in , cod);//Считывание данных с файла input.txt
			};
			in.close();
			//cout << XOR(cod, key);//Вывод и применение шифратора
			outxor.write(XOR(cod, key).data(), XOR(cod, key).size());//Запись зашифрованных данных в файл output_xor.txt
			break;
			}
				case 2:{
				while(in){
				getline(in , cod);//Считывание данных с файла input.txt
				};
				in.close();
				cout << "Enter the number of shifts: ";
				cin >> shift;
				cout << "Input string to cipher: ";	
				cout << cipher(cod, shift) << ' ';
				outcaesar.write(cipher(cod, shift).data(),cipher(cod, shift).size());	
				break;
				}
		default:{
		cout << "Invalid number entered. Try again: ";
		cin >> a;
		break;
		}
		}
		getchar();
	}
	
		/*Дешифрование из XOR или CAESAR в текст*/
		else{
			cout << "Enter '1' for  XOR decryption or '2' for CAESAR decryption: ";
			cin >> b;
			
			switch(b){
				case 1:{
				char key [] = " ";//массив для хранения ключа
				cout << "Enter the key for decryption: ";
				cin >> key;//Ввод ключа
				cin.getline(key, 10);//Считывание строки с ключом
				while(in){
				getline(in , cod);//Считывание данных с файла input.txt
				};
				in.close();
				cout << XOR(cod, key);//Вывод и применение дешифратора
				outxordec.write(XOR(cod, key).data(), XOR(cod, key).size());//Запись в файл расшифрованных данных в файл output_decryption_xor.txt
				break;
				}
					case 2:{
					bool Done = false; //Завершен ли процесс дешифровки
					cout << "Enter the number of shifts: ";
					while(in){
					getline(in , cod);//Считывание данных с файла input.txt
					};
					in.close();
					for (int i = 0; i < ABCSize and !Done; i++) //Пробуем разные величины сдвига до тех пор, пока не расшифруем или не проверим все возможные его значения
					{
					cout << cipher(cod, i);
					outcaesardec.write(cipher(cod, i).data(),cipher(cod, i).size());
					} 
					break;
					}
					
			default:{
		    cout << "Invalid number entered. Try again: ";
			cin >> b;
			break;
			}
		getchar();
		}
	}
return 0;
}
