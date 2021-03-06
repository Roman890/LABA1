
#include <iostream>
#include <fstream>

#define cp1251_O 238
#define cp866_O 174
#define koi8_O 207

using namespace std;
static const unsigned char Cp1251ToCp866[128] = {

        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,

        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
      // Ё
        208, 209, 210, 211, 212, 213, 214, 215, 240, 216, 217, 218, 219, 220, 221, 222,
      // ё
        223, 242, 243, 244, 245, 246, 247, 248, 241, 249, 250, 251, 252, 253, 254, 255,
      // А    Б    В    Г    Д    Е    Ж    З    И    Й    К    Л    М    Н    О    П
        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
      // Р    С    Т    У    Ф    Х    Ц    Ч    Ш    Щ    Ъ    Ы    Ь    Э    Ю    Я
        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
      // a    б    в    г    д    е    ж    з    и    й    к    л    м    н    о    п
        160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
      // р    с    т    у    ф    х    ц    ч    ш    щ    ъ    ы    ь    э    ю    я
        224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,

};

static const unsigned char Cp1251ToKoi8R[128] = {

        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,

        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
      // Ё
        160, 161, 162, 164, 165, 166, 167, 168, 179, 169, 170, 171, 172, 173, 174, 175,
      // ё
        176, 177, 178, 180, 181, 182, 183, 184, 163, 185, 186, 187, 188, 189, 190, 191,
      // А    Б    В    Г    Д    Е    Ж    З    И    Й    К    Л    М    Н    О    П
        225, 226, 247, 231, 228, 229, 246, 250, 233, 234, 235, 236, 237, 238, 239, 240,
      // Р    С    Т    У    Ф    Х    Ц    Ч    Ш    Щ    Ъ    Ы    Ь    Э    Ю    Я
        242, 243, 244, 245, 230, 232, 227, 254, 251, 253, 255, 249, 248, 252, 224, 241,
      // a    б    в    г    д    е    ж    з    и    й    к    л    м    н    о    п
        193, 194, 215, 199, 196, 197, 214, 218, 201, 202, 203, 204, 205, 206, 207, 208,
      // р    с    т    у    ф    х    ц    ч    ш    щ    ъ    ы    ь    э    ю    я
        210, 211, 212, 213, 198, 200, 195, 222, 219, 221, 223, 217, 216, 220, 192, 209

};

static const unsigned char Cp866ToCp1251[128] = {
      // А    Б    В    Г    Д    Е    Ж    З    И    Й    К    Л    М    Н    О    П
        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
      // Р    С    Т    У    Ф    Х    Ц    Ч    Ш    Щ    Ъ    Ы    Ь    Э    Ю    Я
        208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
      // a    б    в    г    д    е    ж    з    и    й    к    л    м    н    о    п
        224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,

        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,

        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,

        160, 161, 162, 163, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 175, 176,
      // р    с    т    у    ф    х    ц    ч    ш    щ    ъ    ы    ь    э    ю    я
        240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
      // Ё    ё
        168, 184, 177, 178, 179, 180, 181, 182, 183, 185, 186, 187, 188, 189, 190, 191

};

static const unsigned char Cp866ToKoi8R[128] = {
      // А    Б    В    Г    Д    Е    Ж    З    И    Й    К    Л    М    Н    О    П
        225, 226, 247, 231, 228, 229, 246, 250, 233, 234, 235, 236, 237, 238, 239, 240,
      // Р    С    Т    У    Ф    Х    Ц    Ч    Ш    Щ    Ъ    Ы    Ь    Э    Ю    Я
        242, 243, 244, 245, 230, 232, 227, 254, 251, 253, 255, 249, 248, 252, 224, 241,
      // a    б    в    г    д    е    ж    з    и    й    к    л    м    н    о    п
        193, 194, 215, 199, 196, 197, 214, 218, 201, 202, 203, 204, 205, 206, 207, 208,

        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,

        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,

        160, 161, 162, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176,
      // р    с    т    у    ф    х    ц    ч    ш    щ    ъ    ы    ь    э    ю    я
        210, 211, 212, 213, 198, 200, 195, 222, 219, 221, 223, 217, 216, 220, 192, 209,
      // Ё    ё
        179, 163, 177, 178, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191

};

static const unsigned char Koi8RToCp1251[128] = {

        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,

        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
      // ё
        160, 161, 162, 184, 163, 164, 165, 166, 167, 169, 170, 171, 172, 173, 174, 175,
      // Ё
        176, 177, 178, 168, 179, 180, 181, 182, 183, 185, 186, 187, 188, 189, 190, 191,
      // ю    а    б    ц    д    е    ф    г    х    и    й    к    л    м    н    о
        254, 224, 225, 246, 228, 229, 244, 227, 245, 232, 233, 234, 235, 236, 237, 238,
      // п    я    р    с    т    у    ж    в    ь    ы    з    ш    э    щ    ч    ъ
        239, 255, 240, 241, 242, 243, 230, 226, 252, 251, 231, 248, 253, 249, 247, 250,
      // Ю    А    Б    Ц    Д    Е    Ф    Г    Х    И    Й    К    Л    М    Н    О
        222, 192, 193, 214, 196, 197, 212, 195, 213, 200, 201, 202, 203, 204, 205, 206,
      // П    Я    Р    С    Т    У    Ж    В    Ь    Ы    З    Ш    Э    Щ    Ч    Ъ
        207, 223, 208, 209, 210, 211, 198, 194, 220, 219, 199, 216, 221, 217, 215, 218

};

static const unsigned char Koi8RToCp866[128] = {
        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,

        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
      // ё
        208, 209, 210, 241, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222,
      // Ё
        223, 242, 243, 240, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
      // ю    а    б    ц    д    е    ф    г    х    и    й    к    л    м    н    о
        238, 160, 161, 230, 164, 165, 228, 163, 229, 168, 169, 170, 171, 172, 173, 174,
      // п    я    р    с    т    у    ж    в    ь    ы    з    ш    э    щ    ч    ъ
        175, 239, 224, 225, 226, 227, 166, 162, 236, 235, 167, 232, 237, 233, 231, 234,
      // Ю    А    Б    Ц    Д    Е    Ф    Г    Х    И    Й    К    Л    М    Н    О
        158, 128, 129, 150, 132, 133, 148, 131, 149, 136, 137, 138, 139, 140, 141, 142,
      // П    Я    Р    С    Т    У    Ж    В    Ь    Ы    З    Ш    Э    Щ    Ч    Ъ
        143, 159, 144, 145, 146, 147, 134, 130, 156, 155, 135, 152, 157, 153, 151, 154

};

class Coder
{
        int symvol[128];
        unsigned char* letter[4];
        ifstream f1;
        ofstream f2;
public:
        // конструктор по умолчанию
        Coder()
        {
                int j = 0;
                int number = 1;
                for (int i = 0; i < 128; i++)
                {
                        symvol[i] = 0;
                }
                while(j < 4)
                {
                  letter[j] = new unsigned char[number];
                  for (int i = 0; i < number; i++)
                  {
                         letter[j][i] = 0;
                  }
                 number = number * 6;
                 j++;
                }
        }
        // деструктор
        ~Coder()
        {
                for (int j = 0; j < 4; j++){delete[] letter[j];}
        }
        // читаем файл
        void read()
        {
                unsigned char c;
                f1.open("input.txt");
                if (!f1)
                {
                        cout << "Can not open" << endl;
                }
                while (!f1.eof())
                {
                        f1 >> c;
                        if (c >= 128) {++symvol[c - 128];}
                }
                f1.close();
        }

        // ищем чаще всего встречающийся символ
        void find_symvol()
        {
                int max = 0;
                for (int i = 0; i < 128; i++)
                {
                        if (symvol[max] < symvol[i]) max = i;
                }
                letter[0][0] = max+128;
                return ;
        }
        // перекодируем символ во все возможные кодировки
        void generateLetter()
        {
                int max = 1;
                        for (int i = 1; i < 4; i++)
                        {
                                for (int j = 0; j < max; j++)
                                {
                                        letter [i][j * 6 + 0] = Cp1251ToCp866[letter[i-1][j] - 128];
                                        letter [i][j * 6 + 1] = Cp1251ToKoi8R[letter[i-1][j] -128];
                                        letter [i][j * 6 + 2] = Cp866ToCp1251[letter[i-1][j] -128];
                                        letter [i][j * 6 + 3] = Cp866ToKoi8R[letter[i-1][j] -128];
                                        letter [i][j * 6 + 4] = Koi8RToCp1251[letter[i-1][j] -128];
                                        letter [i][j * 6 + 5] = Koi8RToCp866[letter[i-1][j] -128];
                                }
                                max = max * 6;
                        }
        }

        void findcorrect()
        {
                int max = 1;
                for (int i = 0; i < 4; i++)
                {
                        for (int j = 0; j < max; j++)
                        {
                                if (cp1251_O == letter[i][j])
                                {
                                        changefile(i, j);
                                        cout << "CP1251" << endl;
                                        cout << "Change code" << endl;
                                        return;
                                }
                                if (cp866_O == letter[i][j])
                                {
                                        changefile(i, j);
                                        cout << "CP866" << endl;
                                        cout << "Change code" << endl;
                                        return;
                                }
                                if (koi8_O == letter[i][j])
                                {
                                        changefile(i, j);
                                        cout << "koi8r" << endl;
                                        cout << "Change code" << endl;
                                        return;
                                }
                        }
                        max = max * 6;
                }
        }

        void changefile(int deep, int width)
        {
                unsigned char finalTabel[128];
                unsigned char c;
                char t;
                f1.open("input.txt");
                f2.open("output.txt");
                int buf[3];
                for (int k = deep; k !=0; k--)
                {
                        buf[k-1] = width % 6;
                        width = width / 6;// получили последовательность применяемых правил
                }
                for (int i = 0; i < 128; i++)
                {
                        finalTabel[i] = i + 128;
                        for (int j = 0; j < deep; j++)
                        {
                                if (buf[j] == 0)
                                        finalTabel[i] = Cp1251ToCp866[finalTabel[i] - 128];
                                if (buf[j] == 1)
                                        finalTabel[i] = Cp1251ToKoi8R[finalTabel[i] - 128];
                                if (buf[j] == 2)
                                        finalTabel[i] = Cp866ToCp1251[finalTabel[i] - 128];
                                if (buf[j] == 3)
                                        finalTabel[i] = Cp866ToKoi8R[finalTabel[i] - 128];
                                if (buf[j] == 4)
                                        finalTabel[i] = Koi8RToCp1251[finalTabel[i] - 128];
                                if (buf[j] == 5)
                                        finalTabel[i] = Koi8RToCp866[finalTabel[i] - 128];
                        }
                }
                while (!f1.eof())
                {
                        f1.get(t);
                        c = (unsigned char)t;
                        if (c >= 128)
                        {
                                c = finalTabel[c - 128];
                        }
                        f2 << c;
                }
                f1.close();
                f2.close();
        }
};
int main()
{
        Coder d;
        d.read();
        d.find_symvol();
        d.generateLetter();
        d.findcorrect();
        return 0;
}




