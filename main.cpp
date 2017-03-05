
#include <iostream>
#include <fstream>


using namespace std;
static const unsigned char Cp1251ToCp866[128] = {

	176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,

	192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
  // �
	208, 209, 210, 211, 212, 213, 214, 215, 240, 216, 217, 218, 219, 220, 221, 222,
  // �
	223, 242, 243, 244, 245, 246, 247, 248, 241, 249, 250, 251, 252, 253, 254, 255,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
  // a    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,

};

static const unsigned char Cp1251ToKoi8R[128] = {

	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,

	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
  // �
	160, 161, 162, 164, 165, 166, 167, 168, 179, 169, 170, 171, 172, 173, 174, 175,
  // �
	176, 177, 178, 180, 181, 182, 183, 184, 163, 185, 186, 187, 188, 189, 190, 191,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	225, 226, 247, 231, 228, 229, 246, 250, 233, 234, 235, 236, 237, 238, 239, 240,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	242, 243, 244, 245, 230, 232, 227, 254, 251, 253, 255, 249, 248, 252, 224, 241,
  // a    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	193, 194, 215, 199, 196, 197, 214, 218, 201, 202, 203, 204, 205, 206, 207, 208,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	210, 211, 212, 213, 198, 200, 195, 222, 219, 221, 223, 217, 216, 220, 192, 209

};

static const unsigned char Cp866ToCp1251[128] = {
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
  // a    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,

	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,

	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,

	160, 161, 162, 163, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 175, 176,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
  // �    �
	168, 184, 177, 178, 179, 180, 181, 182, 183, 185, 186, 187, 188, 189, 190, 191

};

static const unsigned char Cp866ToKoi8R[128] = {
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	225, 226, 247, 231, 228, 229, 246, 250, 233, 234, 235, 236, 237, 238, 239, 240,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	242, 243, 244, 245, 230, 232, 227, 254, 251, 253, 255, 249, 248, 252, 224, 241,
  // a    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	193, 194, 215, 199, 196, 197, 214, 218, 201, 202, 203, 204, 205, 206, 207, 208,

	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,

	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,

	160, 161, 162, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	210, 211, 212, 213, 198, 200, 195, 222, 219, 221, 223, 217, 216, 220, 192, 209,
  // �    �
	179, 163, 177, 178, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191

};

static const unsigned char Koi8RToCp1251[128] = {

	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,

	144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
  // �
	160, 161, 162, 184, 163, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 175,
  // �
	176, 177, 178, 168, 179, 180, 181, 182, 183, 185, 186, 187, 188, 189, 190, 191,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	254, 224, 225, 246, 228, 229, 244, 227, 245, 232, 233, 234, 235, 236, 237, 238,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	239, 255, 240, 241, 242, 243, 230, 226, 252, 251, 231, 248, 253, 249, 247, 250,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	222, 192, 193, 214, 196, 197, 212, 195, 213, 200, 201, 202, 203, 204, 205, 206,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	207, 223, 208, 209, 210, 211, 198, 194, 220, 219, 199, 216, 221, 217, 215, 218

};

static const unsigned char Koi8RToCp866[128] = {
	176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,

	192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
  // �
	208, 209, 210, 241, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222,
  // �
	223, 242, 243, 240, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	238, 160, 161, 230, 164, 165, 228, 163, 229, 168, 169, 170, 171, 172, 173, 174,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	175, 239, 224, 225, 226, 227, 166, 162, 236, 235, 167, 232, 237, 233, 231, 234,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	158, 128, 129, 150, 132, 133, 148, 131, 149, 136, 137, 138, 139, 140, 141, 142,
  // �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
	143, 159, 144, 145, 146, 147, 134, 130, 156, 155, 135, 152, 157, 153, 151, 154

};

class Coder 
{
	int symvol[128]; 
	char* letter[3];
	char finalTable[128];
	int baseKod, deep, indent;
	ifstream f1;
	ofstream f2;
public:
	// ����������� �� ���������
	Coder()
	{
		int j = 0;
		int number = 1;
		for (int i = 0; i <= 128; i++)
		{
			symvol[i] = 0;
		}
		while(j < 3)
		{
		  letter[j] = new char[number];
		  for (int i = 0; i < number; i++) 
		  {
			 letter[j][i] = 0;
		  }
		 number = number * 6;
		 j++;
		}
	}
	// ����������
	~Coder()
	{
		for (int j = 0; j <= 3; j++)
		{
			delete[] letter[j];
		}
	}
	// ������ ����
	void read()
	{
		char c;
		f1.open("input.txt");
		while (!f1.eof())
		{
			f1 >> c;
			if (c > 128) ++symvol[c - 128];
		}
		f1.close();
	}

	// ���� ���� ����� ������������� ������
	int find_symvol() 
	{
		int max = 0;
		for (int i = 0; i < 128; i++)
		{
			if (symvol[max] < symvol[i]) max = i;
		}
		letter[0][0] = max + 127;
		return max;
	}
	// ������������ ������ �� ��� ��������� ���������
	void generateLetter()
	{
		int max = 1;
			for (int i = 0; i <=3; i++) {
				for (int j = 0; j < max; j++) {
					letter [i][j * 6] = Cp1251ToCp866[letter[i][j] -128];
					letter [i][j * 6] = Cp1251ToKoi8R[letter[i][j] -128];
					letter [i][j * 6] = Cp866ToCp1251[letter[i][j] -128];
					letter [i][j * 6] = Cp866ToKoi8R[letter[i][j] -128];
					letter [i][j * 6] = Koi8RToCp1251[letter[i][j] -128];
					letter [i][j * 6] = Koi8RToCp866[letter[i][j] -128];
				}
				max = max * 6;
			}
	}

	
};

int main(int argc, char *argv[])
{
	Coder d;
	d.read();
	d.find_symvol();
	d.generateLetter();
	return 0;
}

	
