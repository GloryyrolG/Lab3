#include "Huffman.h"

using namespace std;

int main() {
    bool flag;
    int op;
    string freqFile, aFile, tarFile;
    MyHuffmanCode a;
    for (; 1; ) {
        printf("Please input the frequency file:\n");
        cin >> freqFile;
        if (a.setFcode(freqFile) == -1) {
            continue;
        }
        for (; 1; ) {
            printf("Please input the file operated:\n");
            cin >> aFile;
            if (!a.setFin(aFile)) {
                break;
            }
        }
        printf("Please input the target file:\n");
        cin >> tarFile;
        a.setFout(tarFile);
        for (flag = 0; !flag; ) {
            printf("Please input the operation:\n");
            printf("1. Encode\t2. Decode\t3. Quit(1/3): ");
            scanf("%d", &op);
            switch (op) {
                case 1: {
                    a.encode();
                    printf("Successful!\n");
                    break;
                }
                case 2: {
                    a.decode();
                    printf("Successful!\n");
                    break;
                }
                case 3: {
                    flag = 1;
                    break;
                }
                default: {
                    printf("Error!\n");
                    break;
                }
            }
        }
    }
    return 0;
}
