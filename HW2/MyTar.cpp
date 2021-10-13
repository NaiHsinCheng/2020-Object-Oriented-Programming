#include "MyTar.h"

MyTar::MyTar(const char *file){
    this->usBlockSize = 512;  //USTAR基本上每個block的大小為512bytes，所以檔案大小為512的倍數
    this->fileNum = -1;
    this->inputStream.open(file, ifstream::in | ifstream::binary);

    // 如果檔案讀取失敗 就結束程式
    if(!this->inputStream.is_open()){
        cout << "Cannot open: No such file or directory" << endl;
        exit(0);
    }
}

MyTar::~MyTar(){
    this->inputStream.close();
    this->tarVector.clear();
}

// 檢查 tar file 是不是 USTART format
int MyTar::isUStar(){
    this->inputStream.seekg(0, ios::end);		//設置文件流的文件流指針的位置（讀寫的位置）
										//ios::end從文件尾巴開始計算偏移量(移到文件最後一個字)
    int fileSize = this->inputStream.tellg();	//返回文件讀取位置的當前字節編號

    // 如果檔案大小不是512的倍數的話 這個檔案不是 USTAR format
    if(fileSize % this->usBlockSize == 0){
        this->inputStream.seekg(257, ios::beg);	//ios::beg從文件頭開始計算偏移量(257 byte of the file)
        char buffer[6];

        //USTAR format在Header的部份的第257個bytes向後數6個bytes的內容為"ustar "
        if(this->inputStream.read(buffer, 6)){	
            string str(buffer);
            if(str == "ustar "){			// 如果 USTAR_id != "ustar " 這個檔案不是 USTAR format
                return MyTar::USTAR;
            }
        }
    }

    return MyTar::NO_USTAR;
}

// 開始讀 tar file
int MyTar::startRead(){

    //如果檔案大小不是512的倍數 則不是USTAR format
    if(MyTar::USTAR != this->isUStar()){
        return MyTar::NO_USTAR;
    }

    // 把文件流指針（讀寫位置）指向檔案的起頭
    this->inputStream.seekg(0, ios::beg);

    while(this->inputStream){
        struct TarHeader buffer;

        if(this->inputStream.read((char*)&buffer, this->usBlockSize)){	//讀入block size大小的資料存進buffer
            this->tarVector.push_back(buffer);		//把buffer(TarHeader)存入tarVector

            int fileSize = this->hex2Dec(buffer.filesize, sizeof(buffer.filesize));		//把file size從char[]改成十進位int

            /* header data是tar file內檔案的內容
             * 存入tarVector後 要跳過這個內容區塊
             * jumpBock代表有多少block要跳過
             */
            int jumpBlock = ceil((double)fileSize / (double)this->usBlockSize); 	//計算要跳的block數
																		//ceil(x)返回大於x的最小整數 
            this->inputStream.seekg(jumpBlock * this->usBlockSize, ios::cur);		//從現在的位置跳到下一個位置
        }
    }

    // 如果tarVector的大小大於0 代表讀取成功
    return this->tarVector.size() > 0 ? MyTar::USTAR : MyTar::NO_USTAR;
}

// 顯示tar file 的內容
void MyTar::showContent(){
    cout << "Total " << this->getFileNum() << " " << (this->getFileNum() > 1 ? "files." : "file.") << endl;
    cout << left << setw(12) << "filemode" << setw(32) << "username" << setw(32) << "groupname" << setw(6) << "size" << setw(100) << "filename" << endl;	//left向左對齊

    for(int i = 0; i < this->getFileNum(); i++){
        struct TarHeader buffer = this->tarVector.at(i);	//第i個檔案的TarHeader

        // 確認檔案是目錄 然後輸出file mode
        cout << left << setw(12) << (buffer.type == '5' ? 'd' : '-') + this->getFileMode(atoi(buffer.filemode));		//atoi(str) 把str轉為整數

        // 輸出使用者名稱
        cout << left << setw(32) << buffer.username;

        // 輸出 group name
        cout << left << setw(32) << buffer.groupname;

        // 輸出檔案大小
        cout << left << setw(6) << this->hex2Dec(buffer.filesize, sizeof(buffer.filesize));
        //cout << left << setw(6) << this->hex2Dec(atoi(buffer.filesize));

        // 輸出檔案名稱
        cout << left << setw(100) << buffer.filename << endl;
    }
}

// tar file 內有幾個檔案
//USTART內部文件的組成大致上是Header + Content + Header2 + Contetnt2 + .....
//Header佔一個block，Content則視其大小決定，Content若有不足一個block，後方則補0x00
int MyTar::getFileNum(){

    //如果 fileNum > -1 直接return
    if(this->fileNum >= 0){
        return this->fileNum;
    }

     //如果 checksum 是 NULL 那 block 也會是NULL
	//一直檢查直到checksum不是NULL  然後return檔案的數量
    for(int i = this->tarVector.size() - 1; i > -1; i--){	//tarVector.size()取得tarVector目前持有的元素個數
        bool zeroFlag = true;	//zeroFlag = true 代表checksum=0
        struct TarHeader buffer = this->tarVector.at(i);	//目前tar檔案的tar header

        for(int j = 0; j < (int)sizeof(buffer.checksum); j++){
            if(buffer.checksum[j] != 0x00){	//checksum!=0，zeroFlag = false
                zeroFlag = false;

                break;
            }
        }

        if(!zeroFlag){		//如果checksum!=0 
            //fileNum的值會是i+1
            this->fileNum = i + 1;
            break;
        }
    }

    return this->fileNum;
}

// 返回 tar file 內的檔案的file mode
string MyTar::getFileMode(int modeNum){
    char r = 'r', w = 'w', x = 'x', no = '-';
    string fileMode[3];

    int index = 2;
    while(modeNum > 0){
        int subMode = modeNum % 10;
        modeNum /= 10;

        /// Check the read priviledge section.
        if(subMode >= 4){
            fileMode[index] += r;
            subMode -= 4;
        }
        else{
            fileMode[index] += no;
        }

        /// Check the write priviledge section.
        if(subMode >= 2){
            fileMode[index] += w;
            subMode -= 2;
        }
        else{
            fileMode[index] += no;
        }

        /// Check the execution priviledge section.
        if(subMode >= 1){
            fileMode[index] += x;
            subMode -= 1;
        }
        else{
            fileMode[index] += no;
        }

        --index;
    }

    return fileMode[0] + fileMode[1] + fileMode[2];
}

// 十六進位轉十進位
int MyTar::hex2Dec(const char* sizeArray, int length){
    int n = 0;
    int ans = 0;

    // i = length - 2 因為sizeArray最後的char是空的 所以為了無視他 多減一個1
    for(int i = length - 2; i > -1; i--){
        int num = sizeArray[i] >= 'a' && sizeArray[i] <= 'f' ? sizeArray[i] - 'a' + 10 : sizeArray[i] - '0';

        ans += num * pow(16, n);
        ++n;
    }

    // return bytes
    return ans /= 8;
}