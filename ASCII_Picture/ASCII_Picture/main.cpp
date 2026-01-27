#include "common.h"

int main() {
    int num;
    while (true) {
        cout << "------------------------------------------------------------------------" << endl;
		cout << "1.ºÚ°××Ö·û»­ 2.²ÊÉ«×Ö·û»­¢Ù 3.²ÊÉ«×Ö·û»­¢Ú 4.²ÊÉ«ÊÓÆµ×Ö·û»­´øÒôÆµ 0.ÍË³ö" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << "ÇëÊäÈë²âÊÔÐòºÅ£º";
		cin >> num;
		if (num == 0) break;
        else if (num == 1) {
            test1("classic_picture/sky.png", 8);
        }
        else if (num == 2) {
            test2("classic_picture/sky.png", 8);
        }
        else if (num == 3) {
            test2("classic_picture/Chamber.png", 8);
        }
        else if (num == 4) {
            test4("video2_frames", "video2_frames/video2_audio.wav", 150, 15, 8);
        }
        else {
            cout << "ÊäÈëÓÐÎó£¬ÇëÖØÐÂÊäÈë£¡" << endl;
		}
        system("cls");
    }
    // test1("classic_picture/sky.png", 8);
    // test2("classic_picture/sky.png", 8);
    // test2("classic_picture/Chamber.png", 8);
    // test3("video2_frames", 150, 15, 8);
    // test4("video2_frames", "video2_frames/video2_audio.wav", 150, 15, 8);

    return 0;
}