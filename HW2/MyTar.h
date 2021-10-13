#ifndef MYTAR_H
#define MYTAR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct TarHeader{
    /// Tar Header 的部分
    char filename[100];
    char filemode[8];
    char userid[8];
    char groupid[8];
    char filesize[12];
    char mtime[12];
    char checksum[8];
    char type;
    char lname[100];

    /// USTAR 的部分
    char USTAR_id[6];
    char USTAR_ver[2];
    char username[32];
    char groupname[32];
    char devmajor[8];
    char devminor[8];
    char prefix[155];
    char pad[12];
};

class MyTar{

public:
    static const int USTAR = 1;  // USTAR = 1 代表 tar file 是 USTAR format.
    static const int NO_USTAR = 0;   // NO_USTAR = 0 代表 tar file 不是 USTAR format

    MyTar(const char *file);
    ~MyTar();

    int isUStar();  // 檢查 tar file 案事不是 USTART format
    int startRead();  // 開始讀 tar file
    void showContent();  // 顯示tar file 的內容
    int getFileNum();  // 取得private值（tar file 內有幾個檔案）

private:
    ifstream inputStream;
    vector<TarHeader> tarVector;  // 在vector內儲存 每個檔案的tar header
    int usBlockSize;  // 代表 USTAR format 的 block size
    int fileNum;   // tar file 內有幾個檔案

    string getFileMode(int);  // 返回 tar file 內的檔案的file mode
    int hex2Dec(const char*, int);  // 十六進位轉十進位
};

#endif // MYTAR_H