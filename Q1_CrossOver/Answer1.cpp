#include <iostream>
#include <iomanip>
#include <math.h>
#define LT 5
#define ST 2
#define PRECISION 2

using namespace std;

class Price{
    public:
        int value;
        Price* nextP;
};

class SharePool{
    public:
        Price* head = NULL;
        Price* tail = NULL;
        Price* stTail = NULL;
        int LTSum = 0;
        int STSum = 0;
        void addShare(int price, int day){
            Price* np = new Price();
            np->value = price;
            LTSum += price;
            if (day == 1){
                head = np;
                tail = np;
                stTail = np;
            }
            else{
                head->nextP = np;
                head = np;
                if (day == (LT-ST)+1){
                    stTail = np;
                }
                if (day > (LT-ST)){
                    STSum += price;
                }
                if (day > LT){
                    LTSum -= tail->value;
                    STSum -= stTail->value;
                    stTail = stTail->nextP;
                    Price* delP = tail;
                    tail = tail->nextP;
                    delete(delP);
                }
            }
        }
        int getLTSum(){
            return LTSum;
        }
        int getSTSum(){
            return STSum;
        }
};

int main(){
    int n;
    cin >> n;
    SharePool* sp = new SharePool();
    int price;
    //For the following 2 arrays : [0]=LTSum [1]=STSum
    int yday[2];
    int tday[2];
    float LTMAY, LTMAT;
    float STMAY, STMAT;
    for(int day = 1; day <= n; day++){
        cin >> price;
        sp->addShare(price, day);
        if (day == LT){
            yday[0] = sp->getLTSum();
            yday[1] = sp->getSTSum();
        }
        if (day > LT){
            tday[0] = sp->getLTSum();
            tday[1] = sp->getSTSum();
            LTMAY = yday[0]*1.0/LT;
            LTMAT = tday[0]*1.0/LT;
            STMAY = yday[1]*1.0/ST;
            STMAT = tday[1]*1.0/ST;
            LTMAY = round(LTMAY * 100)/100.0;
            LTMAT = round(LTMAT * 100)/100.0;
            STMAY = round(STMAY * 100)/100.0;
            STMAT = round(STMAT * 100)/100.0;
            if (((STMAY)>(LTMAY))&&((STMAT)<=(LTMAT))){
                cout << day << " " << fixed << setprecision(PRECISION) << STMAT << " " << fixed << setprecision(PRECISION) << LTMAT << endl;
                yday[0] = tday[0];
                yday[1] = tday[1];
                continue;
            }
            if (((STMAY)<(LTMAY))&&((STMAT)>=(LTMAT))){
                cout << day << " " << fixed << setprecision(PRECISION) << STMAT << " " << fixed << setprecision(PRECISION) << LTMAT << endl;
                yday[0] = tday[0];
                yday[1] = tday[1];
                continue;
            }
            if (((STMAY)==(LTMAY))&&((STMAT)!=(LTMAT))){
                cout << day << " " << fixed << setprecision(PRECISION) << STMAT << " " << fixed << setprecision(PRECISION) << LTMAT << endl;
                yday[0] = tday[0];
                yday[1] = tday[1];
                continue;
            }
        }
    }
    return 0;
}
